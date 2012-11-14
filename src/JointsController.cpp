/**
 * Erenci
 * LabRoCoCo: labrococo.dis.uniroma1.it
 * @author: Lorenzo Tognalini: lorenzo.togna@gmail.com
 *
 */

#include <QDebug>
#include "JointsController.h"
#include "ui_JointsController.h"
#include "Erenci.h"
#include "Command.h"

const QString JointsController::JOINT_HEAD_PITCH			= QString("headpitch");
const QString JointsController::JOINT_HEAD_YAW				= QString("headyaw");
const QString JointsController::JOINT_LEFT_ANKLE_PITCH		= QString("lanklepitch");
const QString JointsController::JOINT_LEFT_ANKLE_ROLL		= QString("lankleroll");
const QString JointsController::JOINT_LEFT_ELBOW_ROLL		= QString("lelbowroll");
const QString JointsController::JOINT_LEFT_ELBOW_YAW		= QString("lelbowyaw");
const QString JointsController::JOINT_LEFT_HIP_PITCH		= QString("lhippitch");
const QString JointsController::JOINT_LEFT_HIP_ROLL			= QString("lhiproll");
const QString JointsController::JOINT_LEFT_HIP_YAW_PITCH	= QString("lhipyawpitch");
const QString JointsController::JOINT_LEFT_KNEE_PITCH		= QString("lkneepitch");
const QString JointsController::JOINT_LEFT_SHOULDER_PITCH	= QString("lshoulderpitch");
const QString JointsController::JOINT_LEFT_SHOULDER_ROLL	= QString("lshoulderroll");
const QString JointsController::JOINT_RIGHT_ANKLE_PITCH		= QString("ranklepitch");
const QString JointsController::JOINT_RIGHT_ANKLE_ROLL		= QString("rankleroll");
const QString JointsController::JOINT_RIGHT_ELBOW_ROLL		= QString("relbowroll");
const QString JointsController::JOINT_RIGHT_ELBOW_YAW		= QString("relbowyaw");
const QString JointsController::JOINT_RIGHT_HIP_PITCH		= QString("rhippitch");
const QString JointsController::JOINT_RIGHT_HIP_ROLL		= QString("rhiproll");
const QString JointsController::JOINT_RIGHT_HIP_YAW_PITCH	= QString("rhipyawpitch");
const QString JointsController::JOINT_RIGHT_KNEE_PITCH		= QString("rkneepitch");
const QString JointsController::JOINT_RIGHT_SHOULDER_PITCH	= QString("rshoulderpitch");
const QString JointsController::JOINT_RIGHT_SHOULDER_ROLL	= QString("rshoulderroll");

JointsController::JointsController(QWidget *parent) :
	QWidget(parent), ui(new Ui::JointsController){

	ui->setupUi(this);

	joints[QString(JOINT_HEAD_PITCH)]			= ui->pickerHeadPitch;
	joints[QString(JOINT_HEAD_YAW)]				= ui->pickerHeadYaw;
	joints[QString(JOINT_LEFT_ANKLE_PITCH)]		= ui->pickerLAnklePitch;
	joints[QString(JOINT_LEFT_ANKLE_ROLL)]		= ui->pickerLAnkleRoll;
	joints[QString(JOINT_LEFT_ELBOW_ROLL)]		= ui->pickerLElbowRoll;
	joints[QString(JOINT_LEFT_ELBOW_YAW)]		= ui->pickerLElbowYaw;
	joints[QString(JOINT_LEFT_HIP_PITCH)]		= ui->pickerLHipPitch;
	joints[QString(JOINT_LEFT_HIP_ROLL)]		= ui->pickerLHipRoll;
	joints[QString(JOINT_LEFT_HIP_YAW_PITCH)]	= ui->pickerLHipYawPitch;
	joints[QString(JOINT_LEFT_KNEE_PITCH)]		= ui->pickerLKneePitch;
	joints[QString(JOINT_LEFT_SHOULDER_PITCH)]	= ui->pickerLShoulderPitch;
	joints[QString(JOINT_LEFT_SHOULDER_ROLL)]	= ui->pickerLShoulderRoll;
	joints[QString(JOINT_RIGHT_ANKLE_PITCH)]	= ui->pickerRAnklePitch;
	joints[QString(JOINT_RIGHT_ANKLE_ROLL)]		= ui->pickerRAnkleRoll;
	joints[QString(JOINT_RIGHT_ELBOW_ROLL)]		= ui->pickerRElbowRoll;
	joints[QString(JOINT_RIGHT_ELBOW_YAW)]		= ui->pickerRElbowYaw;
	joints[QString(JOINT_RIGHT_HIP_PITCH)]		= ui->pickerRHipPitch;
	joints[QString(JOINT_RIGHT_HIP_ROLL)]		= ui->pickerRHipRoll;
	joints[QString(JOINT_RIGHT_HIP_YAW_PITCH)]	= ui->pickerRHipYawPitch;
	joints[QString(JOINT_RIGHT_KNEE_PITCH)]		= ui->pickerRKneePitch;
	joints[QString(JOINT_RIGHT_SHOULDER_PITCH)]	= ui->pickerRShoulderPitch;
	joints[QString(JOINT_RIGHT_SHOULDER_ROLL)]	= ui->pickerRShoulderRoll;

	//this redundant map is only made to speed up setJoints operation
	pickerNamesToJoints[QString("pickerHeadPitch")] = JOINT_HEAD_PITCH;
	pickerNamesToJoints[QString("pickerHeadYaw")] = JOINT_HEAD_YAW;
	pickerNamesToJoints[QString("pickerLAnklePitch")] = JOINT_LEFT_ANKLE_PITCH;
	pickerNamesToJoints[QString("pickerLAnkleRoll")] = JOINT_LEFT_ANKLE_ROLL;
	pickerNamesToJoints[QString("pickerLElbowRoll")] = JOINT_LEFT_ELBOW_ROLL;
	pickerNamesToJoints[QString("pickerLElbowYaw")] = JOINT_LEFT_ELBOW_YAW;
	pickerNamesToJoints[QString("pickerLHipPitch")] = JOINT_LEFT_HIP_PITCH;
	pickerNamesToJoints[QString("pickerLHipRoll")] = JOINT_LEFT_HIP_ROLL;
	pickerNamesToJoints[QString("pickerLHipYawPitch")] = JOINT_LEFT_HIP_YAW_PITCH;
	pickerNamesToJoints[QString("pickerLKneePitch")] = JOINT_LEFT_KNEE_PITCH;
	pickerNamesToJoints[QString("pickerLShoulderPitch")] = JOINT_LEFT_SHOULDER_PITCH;
	pickerNamesToJoints[QString("pickerLShoulderRoll")] = JOINT_LEFT_SHOULDER_ROLL;
	pickerNamesToJoints[QString("pickerRAnklePitch")] = JOINT_RIGHT_ANKLE_PITCH;
	pickerNamesToJoints[QString("pickerRAnkleRoll")] = JOINT_RIGHT_ANKLE_ROLL;
	pickerNamesToJoints[QString("pickerRElbowRoll")] = JOINT_RIGHT_ELBOW_ROLL;
	pickerNamesToJoints[QString("pickerRElbowYaw")] = JOINT_RIGHT_ELBOW_YAW;
	pickerNamesToJoints[QString("pickerRHipPitch")] = JOINT_RIGHT_HIP_PITCH;
	pickerNamesToJoints[QString("pickerRHipRoll")] = JOINT_RIGHT_HIP_ROLL;
	pickerNamesToJoints[QString("pickerRHipYawPitch")] = JOINT_RIGHT_HIP_YAW_PITCH;
	pickerNamesToJoints[QString("pickerRKneePitch")] = JOINT_RIGHT_KNEE_PITCH;
	pickerNamesToJoints[QString("pickerRShoulderPitch")] = JOINT_RIGHT_SHOULDER_PITCH;
	pickerNamesToJoints[QString("pickerRShoulderRoll")] = JOINT_RIGHT_SHOULDER_ROLL;

	//init pickers limits values
	JointsLimits limits = getJointsLimits();
	for(JointsLimits::iterator it = limits.begin(); it != limits.end(); it++){
		std::pair<double, double> vals = (std::pair<double, double>)(*it).second;
		joints[(*it).first]->setLimits(vals.first, vals.second);
	}

	connect(ui->btnUpdateJoints, SIGNAL(clicked(bool)), this, SLOT(updateJoints()));
	connect(ui->checkStiffness, SIGNAL(stateChanged(int)), this, SLOT(switchStiffness(int)));

	//associating a connection for each picker/joint command pair
	std::map<QString, DoublePicker *>::iterator it;
	for(it = joints.begin(); it != joints.end(); it++){
		connect(((DoublePicker*)((*it).second)) , SIGNAL(valueChanged(double)), this, SLOT(setJoint(double)));
		connect(((DoublePicker*)((*it).second)) , SIGNAL(activationChanged(bool)), this, SLOT(setJointStiffness(bool)));
	}
}

JointsController::~JointsController(){
	this->joints.clear(); //dont delete pointed widgets whose are owned by the ui
    delete ui;
}

void JointsController::setConnection(Connection * connection){
	this->connection = connection;
}

void JointsController::setJoint(double value){
	QString joint = pickerNamesToJoints[((DoublePicker*)QObject::sender())->objectName()];
	this->setJoint(joint,value);
}

void JointsController::setJointStiffness(bool value){
	QString joint = pickerNamesToJoints[((DoublePicker*)QObject::sender())->objectName()];
	this->setJointStiffness(joint,value);
}

void JointsController::setJoint(QString joint, double value){
	QString cmd = Command::SET_JOINTS;
	cmd.append(" ");
	cmd.append(joint);
	cmd.append(" ");
	cmd.append(QString::number(value));
	QString res = this->sendCommand(cmd);
	qDebug() << res;
}

void JointsController::setJointStiffness(QString joint, bool activate){
	QString cmd = Command::SET_STIFFNESS;
	cmd.append(" ");
	cmd.append(joint);
	cmd.append(" ");
	double value;
	if(activate){
		value = 1;
	}else{
		value = 0;
	}
	cmd.append(QString::number(value));
	QString res = this->sendCommand(cmd);
	qDebug() << res;
}

double JointsController::getJointMinValue(QString joint){
	return ((DoublePicker*)this->joints[joint])->getMinValue();
}
double JointsController::getJointMaxValue(QString joint){
	return ((DoublePicker*)this->joints[joint])->getMaxValue();
}

void JointsController::setStiffness(bool enabled){
	//TODO: this is a bad trick to be sure command is executed. find alternative way
	if(ui->checkStiffness->isChecked() != enabled){
		//set check without trigging switchStiffness
		ui->checkStiffness->setCheckState(Qt::Checked);
	}

	QString cmd = Command::SET_STIFFNESS;
	std::map<QString, DoublePicker *>::iterator it;
	if(enabled){
		for(it = joints.begin(); it != joints.end(); it++){
			cmd.append(" ");
			cmd.append((*it).first);
			cmd.append(" ");
			cmd.append(QString("0.8"));
		}
	}else{
		for(it = joints.begin(); it != joints.end(); it++){
			cmd.append(" ");
			cmd.append((*it).first);
			cmd.append(" ");
			cmd.append(QString::number(0));
		}
	}
	this->sendCommand(cmd);

}

void JointsController::switchStiffness(int state){
	QString cmd = Command::SET_STIFFNESS;
	std::map<QString, DoublePicker *>::iterator it;
	bool enabled = false;
	if(state == Qt::Checked){
		enabled = true;
		for(it = joints.begin(); it != joints.end(); it++){
			cmd.append(" ");
			cmd.append((*it).first);
			cmd.append(" ");
			cmd.append(QString::number(ui->spinStiffness->value()));
		}
	}else if(state == Qt::Unchecked){
		enabled = false;
		for(it = joints.begin(); it != joints.end(); it++){
			cmd.append(" ");
			cmd.append((*it).first);
			cmd.append(" ");
			cmd.append(QString::number(0));
		}
	}else{
		//PArtially checked.. do nothing?
	}
	this->sendCommand(cmd);

	//toggling each picker/joint stiffness state ( only state )
	for(it = joints.begin(); it != joints.end(); it++){
		DoublePicker * picker = ((DoublePicker*)((*it).second));

		bool oldState = picker->blockSignals(true);
		picker->setActivated(enabled);
		picker->blockSignals(oldState);

	}
}

void JointsController::updateJoints(){
	QString jointsValues;
	QString cmd = QString(Command::GET_JOINTS);
	std::map<QString, DoublePicker *>::iterator it;
	for(it = joints.begin(); it != joints.end(); it++){
		cmd.append(" ");
		cmd.append((*it).first);
	}
	jointsValues = connection->query(cmd);

	if(!jointsValues.isEmpty()){
		bool parsed = parseAndSetJointsValues(jointsValues);
		if(!parsed){
			qWarning() << "ERROR: Parsing error after " << Command::GET_JOINTS;
		}
	}else{
		qWarning() << "ERROR: No answer from connection after " << Command::GET_JOINTS;
	}
	this->updateStiffness();
}

bool JointsController::parseAndSetJointsValues(QString jointsValues){
	QStringList tokens= jointsValues.trimmed().split(' ');

	if((tokens.at(0) == Command::GET_JOINTS) && ((unsigned int)tokens.size() == (joints.size()*2) +3) ){
		qDebug() << tokens;
		for(int i=3; i<tokens.length(); i+=2){
			((DoublePicker *)joints[tokens.at(i)])->setValue(tokens.at(i+1).toDouble());
		}
	}else{
		qWarning() << "ERROR: parsing result of 'getjoints' command";
		return false;
	}
	return true;
}

void JointsController::updateStiffness(){

	//TODO: read stiffness
	QString stiffValues;
	QString cmd = QString(Command::GET_STIFFNESS);
	std::map<QString, DoublePicker *>::iterator it;
	for(it = joints.begin(); it != joints.end(); it++){
		cmd.append(" ");
		cmd.append((*it).first);
	}
	stiffValues = connection->query(cmd);

	if(!stiffValues.isEmpty()){
		bool parsed = parseAndSetStiffness(stiffValues);
		if(!parsed){
			qWarning() << "ERROR: Parsing error after " << Command::GET_STIFFNESS;
		}
	}else{
		qWarning() << "ERROR: No answer from connection after " << Command::GET_STIFFNESS;
	}

}

bool JointsController::parseAndSetStiffness(QString stiffValues){
	bool allZero = true;
	bool allSame = true;

	double value = -1;

	QStringList tokens= stiffValues.trimmed().split(' ');

	if((tokens.at(0) == Command::GET_STIFFNESS) && ((unsigned int)tokens.size() == (joints.size()*2) +3) ){
		qDebug() << tokens;
		int i = 3;
		value = tokens.at(i+1).toDouble();
		i = 5;
		while( (i<tokens.length()) && (allSame) ){
			double jStiff = tokens.at(i+1).toDouble();
			if(value != jStiff ){
				allSame = false;
				allZero = false;
				value = -1;
			}
			i+=2;
		}
	}else{
		qWarning() << "ERROR: parsing result of 'getstiffness' command";
		return false;
	}

	if(value > 0.0001){
		allZero = false;
	}

	if(allSame){
		if(allZero){
			ui->checkStiffness->setCheckState(Qt::Unchecked);
			ui->spinStiffness->setValue(value);
		}else{
			ui->checkStiffness->setCheckState(Qt::Checked);
			ui->spinStiffness->setValue(value);
		}
	}else{
		ui->checkStiffness->setCheckState(Qt::PartiallyChecked);
	}

	return true;
}

QString JointsController::sendCommand(QString cmd){
	QString res;
	if(this->connection != 0){
		res = this->connection->query(cmd);
	}else{
		qWarning() << "ERROR: No connection set for JointsController";
	}
	return res;
}

///////////// GETERS ////////////////

Joints JointsController::getJoints(){
	Joints list;
	std::map<QString, DoublePicker *>::iterator it;
	for(it = joints.begin(); it != joints.end(); it++){
		QString s = ((DoublePicker*)((*it).second))->getTextValue();
		list[(*it).first] = QString(s);
	}
	return list;
}

JointsOrder JointsController::getJointsOrder(){
	JointsOrder list;
	list.push_back(JointsController::JOINT_HEAD_PITCH);
	list.push_back(JointsController::JOINT_HEAD_YAW);
	list.push_back(JointsController::JOINT_LEFT_ANKLE_PITCH);
	list.push_back(JointsController::JOINT_LEFT_ANKLE_ROLL);
	list.push_back(JointsController::JOINT_LEFT_ELBOW_ROLL);
	list.push_back(JointsController::JOINT_LEFT_ELBOW_YAW);
	list.push_back(JointsController::JOINT_LEFT_HIP_PITCH);
	list.push_back(JointsController::JOINT_LEFT_HIP_ROLL);
	list.push_back(JointsController::JOINT_LEFT_HIP_YAW_PITCH);
	list.push_back(JointsController::JOINT_LEFT_KNEE_PITCH);
	list.push_back(JointsController::JOINT_LEFT_SHOULDER_PITCH);
	list.push_back(JointsController::JOINT_LEFT_SHOULDER_ROLL);
	list.push_back(JointsController::JOINT_RIGHT_ANKLE_PITCH);
	list.push_back(JointsController::JOINT_RIGHT_ANKLE_ROLL);
	list.push_back(JointsController::JOINT_RIGHT_ELBOW_ROLL);
	list.push_back(JointsController::JOINT_RIGHT_ELBOW_YAW);
	list.push_back(JointsController::JOINT_RIGHT_HIP_PITCH);
	list.push_back(JointsController::JOINT_RIGHT_HIP_ROLL);
	list.push_back(JointsController::JOINT_RIGHT_HIP_YAW_PITCH);
	list.push_back(JointsController::JOINT_RIGHT_KNEE_PITCH);
	list.push_back(JointsController::JOINT_RIGHT_SHOULDER_PITCH);
	list.push_back(JointsController::JOINT_RIGHT_SHOULDER_ROLL);
	return list;
}

JointsLimits JointsController::getJointsLimits(){
	JointsLimits limits;
	limits[JOINT_HEAD_PITCH]			= std::make_pair<double, double>(-37.5,	 28.5);
	limits[JOINT_HEAD_YAW]				= std::make_pair<double, double>(-118.5, 118.5);
	limits[JOINT_LEFT_ANKLE_PITCH]		= std::make_pair<double, double>(-67.15, 51.86);
	limits[JOINT_LEFT_ANKLE_ROLL]		= std::make_pair<double, double>(-43.06, 21.79);
	limits[JOINT_LEFT_ELBOW_ROLL]		= std::make_pair<double, double>(-88.5,	 -1.5);
	limits[JOINT_LEFT_ELBOW_YAW]		= std::make_pair<double, double>(-118.5, 118.5);
	limits[JOINT_LEFT_HIP_PITCH]		= std::make_pair<double, double>(-100.63,26.73);
	limits[JOINT_LEFT_HIP_ROLL]			= std::make_pair<double, double>(-20.74, 44.29);
	limits[JOINT_LEFT_HIP_YAW_PITCH]	= std::make_pair<double, double>(-64.62, 41.44);
	limits[JOINT_LEFT_KNEE_PITCH]		= std::make_pair<double, double>(-4.29,	 120.04);
	limits[JOINT_LEFT_SHOULDER_PITCH]	= std::make_pair<double, double>(-118.5, 118.5);
	limits[JOINT_LEFT_SHOULDER_ROLL]	= std::make_pair<double, double>(1.5,	 93.5);
	limits[JOINT_RIGHT_ANKLE_PITCH]		= std::make_pair<double, double>(-66.97, 52.40);
	//TODO check if ok ankle roll
	limits[JOINT_RIGHT_ANKLE_ROLL]		= std::make_pair<double, double>(-21.27, 44.03);
	limits[JOINT_RIGHT_ELBOW_ROLL]		= std::make_pair<double, double>(1.5,	 88.5);
	limits[JOINT_RIGHT_ELBOW_YAW]		= std::make_pair<double, double>(-118.5, 118.5);
	limits[JOINT_RIGHT_HIP_PITCH]		= std::make_pair<double, double>(-100.54,26.82);
	limits[JOINT_RIGHT_HIP_ROLL]		= std::make_pair<double, double>(-41.30, 22.76);
	limits[JOINT_RIGHT_HIP_YAW_PITCH]	= std::make_pair<double, double>(-64.62, 41.44);
	limits[JOINT_RIGHT_KNEE_PITCH]		= std::make_pair<double, double>(-4.90,  120.47);
	limits[JOINT_RIGHT_SHOULDER_PITCH]	= std::make_pair<double, double>(-118.5, 118.5);
	limits[JOINT_RIGHT_SHOULDER_ROLL]	= std::make_pair<double, double>(-93.5,	 -1.5);
	return limits;
}
