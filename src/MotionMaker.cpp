/**
 * Erenci
 * LabRoCoCo: labrococo.dis.uniroma1.it
 * @author: Lorenzo Tognalini: lorenzo.togna@gmail.com
 *
 */

#include "MotionMaker.h"
#include "ui_MotionMaker.h"
#include "Pose.h"
#include <map>
#include <QString>
#include <QMessageBox>

MotionMaker::MotionMaker(QWidget *parent) : QWidget(parent), ui(new Ui::MotionMaker), posesIdIndex(0){
    ui->setupUi(this);
	ui->listPoses->setAlternatingRowColors(true);

	connect(ui->btnPushPose,	SIGNAL(clicked()), this, SLOT(pushPose()));
	connect(ui->btnInsertPose,	SIGNAL(clicked()), this, SLOT(insertPose()));
	connect(ui->btnUpdatePose,	SIGNAL(clicked()), this, SLOT(updatePose()));
	connect(ui->btnUpdateTime,	SIGNAL(clicked()), this, SLOT(updateTime()));
	connect(ui->btnRemove,		SIGNAL(clicked()), this, SLOT(removePose()));
	connect(ui->btnReflectPose, SIGNAL(clicked()), this, SLOT(reflectPose()));
	connect(ui->btnMoveUp,		SIGNAL(clicked()), this, SLOT(movePoseUp()));
	connect(ui->btnMoveDown,	SIGNAL(clicked()), this, SLOT(movePoseDown()));
	connect(ui->btnClonePose,	SIGNAL(clicked()), this, SLOT(clonePose()));
	connect(ui->btnCaptureAndPush, SIGNAL(clicked()), this, SLOT(captureAndPush()));

	connect(ui->btnGoToPose,	SIGNAL(clicked()), this, SLOT(goToPose()));
	connect(ui->btnPlayStep,	SIGNAL(clicked()), this, SLOT(playStep()));
	connect(ui->btnPlay,		SIGNAL(clicked()), this, SLOT(playMotion()));

	connect(ui->listPoses,		SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(editPoseInline(QListWidgetItem*)));

	connect(ui->listPoses,		SIGNAL(currentRowChanged(int)), this, SLOT(toggleButtonEnabling(int)));

	toggleButtonEnabling(-1);
}

MotionMaker::~MotionMaker(){
    delete ui;
}

void MotionMaker::setJointsController(JointsController *jc){
	this->jc = jc;
	this->jointsOrder = this->jc->getJointsOrder();
}

void MotionMaker::setConnection(Connection * connection){
	this->connection = connection;
}

QListWidget * MotionMaker::getPoses(){
	return ui->listPoses;
}

void MotionMaker::addPose(Pose * pose){
	if(pose->isIdSet()){
		if(pose->getIdentifier() > posesIdIndex){
			posesIdIndex = pose->getIdentifier();
		}
	}else{
		pose->setIdentifier(getNextPoseId());
	}
	ui->listPoses->addItem(pose->stringify());
	pose->deleteLater();
}

int MotionMaker::getNextPoseId(){
	this->posesIdIndex++;
	return this->posesIdIndex;
}


void MotionMaker::editPoseInline(QListWidgetItem * item){
	qDebug() << "EDIT";
	item->setFlags(item->flags() | Qt::ItemIsEditable);
}

void MotionMaker::toggleButtonEnabling(int code){
	bool enabled = true;
	if(code == -1){
		enabled = false;
	}
	ui->btnClonePose->setEnabled(enabled);
	ui->btnGoToPose->setEnabled(enabled);
	ui->btnInsertPose->setEnabled(enabled);
	ui->btnMoveDown->setEnabled(enabled);
	ui->btnMoveUp->setEnabled(enabled);
	ui->btnRemove->setEnabled(enabled);
	ui->btnReflectPose->setEnabled(enabled);
	ui->btnUpdatePose->setEnabled(enabled);
	ui->btnUpdateTime->setEnabled(enabled);
}

QString MotionMaker::composeItemPose(){
	QString pose = QString::number(getNextPoseId()); //TODO remove this
	pose.append(" ");
	pose.append(ui->spinTime->cleanText());
	std::map<QString, QString> joints = this->jc->getJoints();
	JointsOrder::iterator it;
	for(it = jointsOrder.begin(); it < jointsOrder.end(); it++){
		pose.append(" ");
		pose.append(joints[*it]);
	}
	return pose;
}

QString MotionMaker::prepareProxyPose(QString itemPose, bool includeTime, double timeScale){

	QStringList tokens = itemPose.split(" ", QString::SkipEmptyParts);
	QString pose;
	if(includeTime){
		if(timeScale != 1.0){ //TODO WRONG COMPARISON
			double time = tokens.at(1).toDouble();
			time *= timeScale;
			QString ts = QString::number(time,'f',3);
			pose.append(ts);
		}else{
			pose.append(tokens.at(1));
		}
		pose.append(" ");
		pose.append("22");
		pose.append(" ");
	}
	int tokensIndex = 2;
	JointsOrder::iterator it;
	for(it = jointsOrder.begin(); it < jointsOrder.end(); it++){
		pose.append(*it);
		pose.append(" ");
		pose.append(tokens.at(tokensIndex));
		pose.append(" ");
		tokensIndex++;
	}
	pose.remove(pose.size()-1, 1);
	return pose;
}

/////////////////////////////// MANAGEMENT COMMANDS //////////////////////////

void MotionMaker::pushPose(){
	ui->listPoses->addItem(composeItemPose());
	emit itemListChanged();
}


void MotionMaker::captureAndPush(){
	jc->updateJoints();
	ui->listPoses->addItem(composeItemPose());
	emit itemListChanged();
}

void MotionMaker::insertPose(){
	if(ui->listPoses->currentRow() >= 0){
		int row = ui->listPoses->currentRow();
		QString s = composeItemPose();
		ui->listPoses->insertItem(row+1,s);
		emit itemListChanged();
	}else{
		pushPose();
	}
}

void MotionMaker::updatePose(){
	if(ui->listPoses->currentRow() >= 0){
		QString s = composeItemPose();
		ui->listPoses->currentItem()->setText(s);
		emit itemListChanged();
	}else{
		//do nothing
	}
}

void MotionMaker::updateTime(){
	if(ui->listPoses->currentRow() >= 0){
		Pose pose(this,ui->listPoses->currentItem()->text());
		pose.setTime(ui->spinTime->value());
		ui->listPoses->currentItem()->setText(pose.stringify());
		emit itemListChanged();
	}else{
		//do nothing
	}
}

void MotionMaker::clonePose(){
	if(ui->listPoses->currentRow() >= 0){
		QString s = ui->listPoses->currentItem()->text();
		ui->listPoses->insertItem(ui->listPoses->currentRow()+1, s);
		emit itemListChanged();
	}else{
		//do nothing
	}
}

void MotionMaker::removePose(){
	if(ui->listPoses->currentRow() >= 0){
		delete ui->listPoses->currentItem();
		emit itemListChanged();
	}
}

void MotionMaker::reflectPose(){
	if(ui->listPoses->currentRow() >= 0){
		int poseNum = ui->listPoses->currentRow();
		reflectPose(poseNum);
	}else{
		//do nothing
	}
}

void MotionMaker::reflectPose(unsigned int itemNum){
	QString poseString = ui->listPoses->item(itemNum)->text();
	Pose pose(this, poseString);
	pose.reflect();
	ui->listPoses->item(itemNum)->setText(pose.stringify());
	emit itemListChanged();
}

void MotionMaker::reflectAll(){
	unsigned int numItems = ui->listPoses->count();
	for(unsigned int i = 0; i < numItems; i++){
		reflectPose(i);
	}
}

void MotionMaker::movePoseUp(){
	if(ui->listPoses->currentRow() > 0){
		int row = ui->listPoses->currentRow();
		QListWidgetItem * item = ui->listPoses->takeItem(row);
		ui->listPoses->insertItem(row-1, item);
		ui->listPoses->setCurrentItem(item);
		emit itemListChanged();
	}
}

void MotionMaker::movePoseDown(){
	if(ui->listPoses->currentRow() >= 0){
		int row = ui->listPoses->currentRow();
		QListWidgetItem * item = ui->listPoses->takeItem(row);
		ui->listPoses->insertItem(row+1, item);
		ui->listPoses->setCurrentItem(item);
		emit itemListChanged();
	}
}

//////////////////////// EXECUTION COMMANDS ///////////////////////

void MotionMaker::playMotion(){
	this->jc->setStiffness(true);
	int numPoses = ui->listPoses->count();
	if(numPoses > 0){
		//TODO use key not setjoints
		QString query = QString("play ");
		query.append(QString::number(numPoses));
		for(int i = 0; i<numPoses; i++){
			QString pose = prepareProxyPose(ui->listPoses->item(i)->text(), true, ui->spinTimeScale->cleanText().toDouble());
			query.append(" ");
			query.append(pose);
		}
		QString result = this->connection->query(query);
		QStringList resTokens = result.split(' ');
		if((result.compare("0") == 0) ||
		   ((resTokens.at(0).compare("play")) &&
		   (resTokens.at(1).toInt() == Connection::RESULT_PARTIALLY_FAILED))){
			QMessageBox errMsg(this);
			errMsg.setText("Command 'play' Failed");
			errMsg.exec();
		}
	}
}

void MotionMaker::playStep(){
	this->jc->setStiffness(true);
	if(ui->listPoses->currentRow() >= 0){
		QString pose = prepareProxyPose(ui->listPoses->currentItem()->text(), true, ui->spinTimeScale->cleanText().toDouble());
		//TODO use key not setjoints
		QString result = this->connection->query(QString("play 1 ").append(pose));
		QStringList resTokens = result.split(' ');
		if((result.compare("0") == 0) ||
		   ((resTokens.at(0).compare("play")) &&
		   (resTokens.at(1).toInt() == Connection::RESULT_PARTIALLY_FAILED))){
			QMessageBox errMsg(this);
			errMsg.setText("Command 'play' Failed");
			errMsg.exec();
		}else{
			ui->listPoses->setCurrentRow(ui->listPoses->currentRow()+1);
		}
	}
}

void MotionMaker::goToPose(){
	this->jc->setStiffness(true);
	if(ui->listPoses->currentRow() >= 0){
		QString pose = prepareProxyPose(ui->listPoses->currentItem()->text(), false);
		//TODO use key not setjoints
		this->connection->query(QString("setjoints ").append(pose));
	}
}
