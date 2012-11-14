/**
 * Erenci
 * LabRoCoCo: labrococo.dis.uniroma1.it
 * @author: Lorenzo Tognalini: lorenzo.togna@gmail.com
 *
 */

//#define DAT_CONVERTION_RAD_TO_DEG_ENABLED 1

#include "Persistance.h"
#include <vector>
#include <math.h>
#include <QDebug>
#include <QString>
#include <QStringList>
#include <QSettings>
#include <QFileDialog>
#include <QMessageBox>
#include "Erenci.h"
#include "JointsController.h"
#include "Pose.h"

const QString Persistance::SETTING_NAME_ID_FILE_PATH = "ErenciFilePath";
const QString Persistance::SETTING_NAME_ID_DAT_PATH = "ErenciDatPath";

Persistance::Persistance(QWidget *parent) : QWidget(parent),
											filePath(""),
											fileOpened(false),
											modelEdited(false){

	//init joints order
	datJointsOrder.push_back(QString("HeadYaw"));
	datJointsOrder.push_back(QString("HeadPitch"));
	datJointsOrder.push_back(QString("LShoulderPitch"));
	datJointsOrder.push_back(QString("LShoulderRoll"));
	datJointsOrder.push_back(QString("LElbowYaw"));
	datJointsOrder.push_back(QString("LElbowRoll"));
	datJointsOrder.push_back(QString("LHipYawPitch"));
	datJointsOrder.push_back(QString("LHipRoll"));
	datJointsOrder.push_back(QString("LHipPitch"));
	datJointsOrder.push_back(QString("LKneePitch"));
	datJointsOrder.push_back(QString("LAnklePitch"));
	datJointsOrder.push_back(QString("LAnkleRoll"));
	datJointsOrder.push_back(QString("RHipYawPitch"));
	datJointsOrder.push_back(QString("RHipRoll"));
	datJointsOrder.push_back(QString("RHipPitch"));
	datJointsOrder.push_back(QString("RKneePitch"));
	datJointsOrder.push_back(QString("RAnklePitch"));
	datJointsOrder.push_back(QString("RAnkleRoll"));
	datJointsOrder.push_back(QString("RShoulderPitch"));
	datJointsOrder.push_back(QString("RShoulderRoll"));
	datJointsOrder.push_back(QString("RElbowYaw"));
	datJointsOrder.push_back(QString("RElbowRoll"));

}

Persistance::~Persistance(){

}

void Persistance::setModel(MotionMaker * model){
	this->model = model;
	connect(this->model, SIGNAL(itemListChanged()), this, SLOT(editingPerformed()));
}

Erenci * Persistance::getController(){
	Erenci * motionEditor = static_cast<Erenci*>(this->parentWidget());
	return motionEditor;
}

void Persistance::editingPerformed(){
	this->modelEdited = true;
	emit fileSaved(false);
}

void Persistance::open(){
	bool wannaOpen = true;

	close();
	//TODO: get if he choosed to not do anything (Cancel) and set wannaOpen false

	if(wannaOpen){
		QString title = "Choose a Poses File to be Opened";
		QString filesType = "RAgent Config File (*.rnc)";\
		QString folder = QSettings().value(SETTING_NAME_ID_FILE_PATH).toString();
		QString path = QFileDialog::getOpenFileName(this,
													title,
													folder,
													filesType);
		if(path.isEmpty()){
			return;
		}

		//caching the last path
		QSettings * settings = new QSettings();
		settings->setValue(SETTING_NAME_ID_FILE_PATH, path);
		settings->sync();
		delete settings;

		this->filePath = path;
		this->fileOpened = true;

		/////// READ FILE
		QFile file(this->filePath);
		if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
			qDebug() << "ERROR: file not save.";
			showMessage("Error: Could not acces to the file. The document has not been read.");
			return;
		}
		QTextStream in(&file);
		model->getPoses()->clear();
		while (!in.atEnd()){
			QString line = in.readLine();
			model->getPoses()->addItem(line);
		}
		file.close();
		//////// END READ FILE

		qDebug() << "OPEN:" << filePath;
		this->getController()->showStatusState(filePath);

		this->modelEdited = false;
		emit fileSaved(true);

	}else{
	}

}

void Persistance::close(){

	if(modelEdited){

		QMessageBox msgBox;
		msgBox.setText("The document has been modified.");
		msgBox.setInformativeText("Do you want to save your changes?");
		msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard);
		msgBox.setDefaultButton(QMessageBox::Save);
		int ret = msgBox.exec();

		if(ret == QMessageBox::Save) { //save and close
			save();
		}
	}
	//really close
	qDebug() << "CLOSED: " << filePath;
	this->getController()->showStatusState(QString(""));
	this->filePath = "";
	this->fileOpened = false;
	this->modelEdited = false;
	model->getPoses()->clear();
}

void Persistance::save(){

	if(!fileOpened){
		QString title = "Save as..";
		QString filesType = "RAgent Config File (*.rnc)";\
		QString folder = QSettings().value(SETTING_NAME_ID_FILE_PATH).toString();
		QString path = QFileDialog::getSaveFileName(this,
													title,
													folder,
													filesType);
		if(path.isEmpty()){
			qDebug() << "choosed no file to save";
			return;
		}
		// what if the users did not specify a suffix...?
		QFileInfo finfo(path);
		if (finfo.suffix().isEmpty()){
			path += QString(".rnc");
		}

		//caching the last path
		QSettings * settings = new QSettings();
		settings->setValue(SETTING_NAME_ID_FILE_PATH, path);
		settings->sync();
		delete settings;

		this->filePath = path;
		this->getController()->showStatusState(filePath);
		this->fileOpened = true;
	}

	this->writeFile(this->filePath);

	this->modelEdited = false;
	emit fileSaved(true);
	qDebug() << "FILE SAVED: " << filePath;
	getController()->showStatusMessage("File Saved!");
}

void Persistance::saveACopy(){

	QString title = "Save Copy as..";
	QString filesType = "RAgent Config File (*.rnc)";\
	QString folder = QSettings().value(SETTING_NAME_ID_FILE_PATH).toString();
	QString path = QFileDialog::getSaveFileName(this,
												title,
												folder,
												filesType);
	if(path.isEmpty()){
		qDebug() << "choosed no file to save copy";
		return;
	}
	//caching the last path
	QSettings * settings = new QSettings();
	settings->setValue(SETTING_NAME_ID_FILE_PATH, path);
	settings->sync();
	delete settings;

	this->writeFile(path);

	qDebug() << "FILE COPY SAVED: " << path;
	getController()->showStatusMessage("File Copy Saved!");
}

void Persistance::writeFile(QString path){
	QFile file(path);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){
		qDebug() << "ERROR: file not save.";
		showMessage("Error: Could not acces to the file. The document has not been saved.");
		return;
	}
	QTextStream out(&file);
	for(int i = 0; i < model->getPoses()->count(); i++){
		out << model->getPoses()->item(i)->text() << "\n";
	}
	file.close();

}

////////////////////// EXTERNAL FORMATS ///////////////

void Persistance::exportToDat(){

	QString title = "Export for OpenRDK SPQR as..";
	QString filesType = "OpenRDK SPQR Poses File (*.dat)";\
	QString folder = QSettings().value(SETTING_NAME_ID_DAT_PATH).toString();
	QString path = QFileDialog::getSaveFileName(this,
												title,
												folder,
												filesType);
	if(path.isEmpty()){
		qDebug() << "choosed no file to save";
		return;
	}
	// what if the users did not specify a suffix...?
	QFileInfo finfo(path);
	if (finfo.suffix().isEmpty()){
		path += QString(".dat");
	}

	//caching the last path
	QSettings * settings = new QSettings();
	settings->setValue(SETTING_NAME_ID_DAT_PATH, path);
	settings->sync();
	delete settings;

	/////// WRITE FILE
	QFile file(path);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){
		qDebug() << "ERROR: file not exported.";
		showMessage("Error: Could not acces to the file. The document has not been exported.");
		return;
	}
	QTextStream out(&file);

	//set num poses
	out << QString::number(model->getPoses()->count()) << "\n\n";

	//set times
	std::vector<QStringList> poses;
	for(int i = 0; i < model->getPoses()->count(); i++){
		QStringList tokens = model->getPoses()->item(i)->text().split(" ");
		out << tokens.at(1) << "\n";
		poses.push_back(tokens);
	}

	out << "\n";

	//set poses grad to rad
	std::vector<QStringList>::iterator it;
	for(it = poses.begin(); it < poses.end(); it++){
		for(int j=2; j<((*it).count()); j++) {
			out << datJointsOrder.at(j-2) << " "; //DOES NOT WORK
			unsigned int f = findIndexInJointOrder(datJointsOrder.at(j-2));
			out << (*it).at(2+f) << "\n";
			file.flush();
		}
		if( (it+1) != poses.end()){
			out << "\n";
		}
	}

	file.close();

	/////// END WRITE FILE

	qDebug() << "EXPORTED: " << path;
	getController()->showStatusMessage(QString("Exported in ").append(path));
}

int Persistance::findIndexInJointOrder(QString key){
	//TODO make it precompiled and statically associated with an associative array
	int index = -1;
	bool found = false;
	JointsOrder jointsOrder = JointsController::getJointsOrder();
	JointsOrder::iterator it = jointsOrder.begin();
	while((!found) && (it < jointsOrder.end())){
		index++;
		if((QString(*it)).compare(key,Qt::CaseInsensitive) == 0){
			found = true;
		}
		it++;
	}
	if(!found){
		qWarning() << "key not found";
		index = -1;
	}
	return index;
}

void Persistance::importDat(){

	QString title = "Import from OpenRDK SPQR ...";
	QString filesType = "OpenRDK SPQR Poses File (*.dat)";\
	QString folder = QSettings().value(SETTING_NAME_ID_DAT_PATH).toString();
	QString path = QFileDialog::getOpenFileName(this,
												title,
												folder,
												filesType);
	if(path.isEmpty()){
		qDebug() << "choosed no file to import";
		return;
	}
	//caching the last path
	QSettings * settings = new QSettings();
	settings->setValue(SETTING_NAME_ID_DAT_PATH, path);
	settings->sync();
	delete settings;

	/////// READ FILE
	QFile file(path);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
		qDebug() << "ERROR: file not imported.";
		showMessage("Error: Could not access the file. The document has not been imported.");
		return;
	}
	QTextStream in(&file);

	model->getPoses()->clear();
	std::vector<Pose *> poses;

	int numPoses = in.readLine().trimmed().toInt();
	int numLine = 0;
	in.readLine();
	while ((numLine < (numPoses)) && !in.atEnd()){ //fill times
		Pose * pose = new Pose(model);
		pose->setTime(in.readLine().trimmed().toDouble());
		poses.push_back(pose);
		numLine++;
	}
	numLine = 0;
	while ((numLine < (numPoses)) && !in.atEnd()){ //fill joints
		in.readLine();
		this->tempMapReset();
		for(int j = 0; (j<22) && !in.atEnd(); j++){

			QStringList joint = in.readLine().trimmed().split(" ");

			QString value = joint.at(1);
			qDebug() << "RAD-str:" << value;

#ifdef DAT_CONVERTION_RAD_TO_DEG_ENABLED

			double rad = joint.at(1).toDouble();
			qDebug() << "RAD-double:" << rad;
			double deg = rad*180/3.14159265;
			qDebug() << "DEG-double:" << deg;
			value = QString::number(deg,'f', 2);
			qDebug() << "DEG-str:" << value;
#endif

			datJointsTemp[joint.at(0)] = value;

		}

		Pose * pose = poses.at(numLine);
		DatJoints::iterator it = datJointsTemp.begin();
		//for each datJointsOrder
		for(unsigned int i = 0; i < datJointsOrder.size(); i++){

			//line.append(" ").append((*it).second);
			pose->setJoint((*it).first.toLower(),(*it).second.toDouble());

			it++;
		}

		numLine++;
	}
	//read joints
	//TODO remove the getPoses call. call a direct method
	model->getPoses()->clear();
	for(unsigned int i = 0; i< poses.size(); i++){
		model->addPose(poses.at(i));
	}
	//TODO: put guard on parsing failed
	file.close();
	/////// END READ FILE

	qDebug() << "IMPORTED: " << path;
	getController()->showStatusMessage(QString("Imported from ").append(path));
}

//TODO: void Persistance::importKME(){}


void Persistance::tempMapReset(){

	//init dat exporting map
	datJointsTemp[QString("HeadYaw")] = QString::number(0.0);
	datJointsTemp[QString("HeadPitch")] = QString::number(0.0);
	datJointsTemp[QString("LShoulderPitch")] = QString::number(0.0);
	datJointsTemp[QString("LShoulderRoll")] = QString::number(0.0);
	datJointsTemp[QString("LElbowYaw")] = QString::number(0.0);
	datJointsTemp[QString("LElbowRoll")] = QString::number(0.0);
	datJointsTemp[QString("LHipYawPitch")] = QString::number(0.0);
	datJointsTemp[QString("LHipRoll")] = QString::number(0.0);
	datJointsTemp[QString("LHipPitch")] = QString::number(0.0);
	datJointsTemp[QString("LKneePitch")] = QString::number(0.0);
	datJointsTemp[QString("LAnklePitch")] = QString::number(0.0);
	datJointsTemp[QString("LAnkleRoll")] = QString::number(0.0);
	datJointsTemp[QString("RHipYawPitch")] = QString::number(0.0);
	datJointsTemp[QString("RHipRoll")] = QString::number(0.0);
	datJointsTemp[QString("RHipPitch")] = QString::number(0.0);
	datJointsTemp[QString("RKneePitch")] = QString::number(0.0);
	datJointsTemp[QString("RAnklePitch")] = QString::number(0.0);
	datJointsTemp[QString("RAnkleRoll")] = QString::number(0.0);
	datJointsTemp[QString("RShoulderPitch")] = QString::number(0.0);
	datJointsTemp[QString("RShoulderRoll")] = QString::number(0.0);
	datJointsTemp[QString("RElbowYaw")] = QString::number(0.0);
	datJointsTemp[QString("RElbowRoll")] = QString::number(0.0);

}

void Persistance::showMessage(QString text){
	QMessageBox msgBox;
	msgBox.setText(text);
	msgBox.exec();
}
