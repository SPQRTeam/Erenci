/**
 * Erenci
 * LabRoCoCo: labrococo.dis.uniroma1.it
 * @author: Lorenzo Tognalini: lorenzo.togna@gmail.com
 *
 */

#include "Pose.h"
#include <QStringList>
#include <QDebug>

const double Pose::JOINT_TOLLERANCE = 4.0;
const int Pose::ID_NOT_SET = -1;
const int Pose::TIME_NOT_SET = -1;
const QString Pose::JOINT_NOT_SET = QString("NULL");

Pose::Pose(MotionMaker * parent, QString stringified):// QObject(parent),
	identifier(ID_NOT_SET),
	time(TIME_NOT_SET){

	setParent((QObject*)parent); //TODO: this totally sucks

	JointsOrder orders = JointsController::getJointsOrder();
	for(unsigned int i = 0; i < orders.size(); i++){
		joints[orders.at(i)] = Pose::JOINT_NOT_SET;
	}

	//this initialize values if a correctly parsed string is provided
	if(! stringified.isNull()){
		unstringify(stringified);
	}

}

Pose::~Pose(){

}

bool Pose::isJointNUll(QString jointName){
	if(joints[jointName].compare(JOINT_NOT_SET) == 0){
		return true;
	}
	return false;
}

bool Pose::isTimeSet(){
	if (time != TIME_NOT_SET){
		return true;
	}
	return false;
}

bool Pose::isIdSet(){
	if (identifier != ID_NOT_SET){
		return true;
	}
	return false;
}

void Pose::setIdentifier(int identifier){
	this->identifier = identifier;
}

void Pose::setTime(double time){
	this->time = time;
}

int	Pose::getIdentifier(){
	return this->identifier;
}

double	Pose::getTime(){
	return this->time;
}

void Pose::setJoint(QString jointName, double value){
	if ( joints.find(jointName) == joints.end() ) {
		qWarning() << "Joint not found in pose: " << jointName;
	}else{
		JointsLimits limits = JointsController::getJointsLimits();
		double min = limits[jointName].first;
		double max = limits[jointName].second;
		if((value >= min) && (value <= max)){
			this->joints[jointName] = QString::number(value, 'f', 2);
		}else{
            if((value >= (min - JOINT_TOLLERANCE)) && (value <= (max + JOINT_TOLLERANCE))){
                if (value >= max){
					this->joints[jointName] = QString::number(max, 'f', 2);
					qDebug() << "Corrected Joint out of max range:" << jointName << QString::number(value, 'f', 2) << " to "
                             << this->joints[jointName];
                }else{
					this->joints[jointName] = QString::number(min, 'f', 2);
					qDebug() << "Corrected Joint out of min range:" << jointName << QString::number(value, 'f', 2) << " to "
                             << this->joints[jointName];
                }
            }else{
				qWarning() << "Joint out of range:" << jointName << QString::number(value, 'f', 2);
            }
		}
	}
}

void Pose::reflect(){

	QString supportVal;
	//head
	//joints[JointsController::JOINT_HEAD_PITCH] = same
	joints[JointsController::JOINT_HEAD_YAW] = QString::number(-(joints[JointsController::JOINT_HEAD_YAW].toDouble()), 'f', 2);

	//ankle pitch
	supportVal = joints[JointsController::JOINT_LEFT_ANKLE_PITCH];
	setJoint(JointsController::JOINT_LEFT_ANKLE_PITCH, joints[JointsController::JOINT_RIGHT_ANKLE_PITCH].toDouble());
	setJoint(JointsController::JOINT_RIGHT_ANKLE_PITCH, supportVal.toDouble());

	//ankle roll
	supportVal = joints[JointsController::JOINT_LEFT_ANKLE_ROLL];
	setJoint(JointsController::JOINT_LEFT_ANKLE_ROLL, -joints[JointsController::JOINT_RIGHT_ANKLE_ROLL].toDouble());
	setJoint(JointsController::JOINT_RIGHT_ANKLE_ROLL, -supportVal.toDouble());

	//hip pitch
	supportVal = joints[JointsController::JOINT_LEFT_HIP_PITCH];
	setJoint(JointsController::JOINT_LEFT_HIP_PITCH, joints[JointsController::JOINT_RIGHT_HIP_PITCH].toDouble());
	setJoint(JointsController::JOINT_RIGHT_HIP_PITCH, supportVal.toDouble());

	//hip roll
	supportVal = joints[JointsController::JOINT_LEFT_HIP_ROLL];
	setJoint(JointsController::JOINT_LEFT_HIP_ROLL, joints[JointsController::JOINT_RIGHT_HIP_ROLL].toDouble());
	setJoint(JointsController::JOINT_RIGHT_HIP_ROLL, supportVal.toDouble());

	//hip yaw pitch
	//joints[JointsController::JOINT_LEFT_HIP_YAW_PITCH] = same;
	//joints[JointsController::JOINT_RIGHT_HIP_YAW_PITCH] = not used;

	//knee pitch
	supportVal = joints[JointsController::JOINT_LEFT_KNEE_PITCH];
	setJoint(JointsController::JOINT_LEFT_KNEE_PITCH, joints[JointsController::JOINT_RIGHT_KNEE_PITCH].toDouble());
	setJoint(JointsController::JOINT_RIGHT_KNEE_PITCH, supportVal.toDouble());

	//shoulders pitch
	supportVal = joints[JointsController::JOINT_LEFT_SHOULDER_PITCH];
	setJoint(JointsController::JOINT_LEFT_SHOULDER_PITCH, joints[JointsController::JOINT_RIGHT_SHOULDER_PITCH].toDouble());
	setJoint(JointsController::JOINT_RIGHT_SHOULDER_PITCH, supportVal.toDouble());

	//shoulders roll
	supportVal = joints[JointsController::JOINT_LEFT_SHOULDER_ROLL];
	setJoint(JointsController::JOINT_LEFT_SHOULDER_ROLL, -joints[JointsController::JOINT_RIGHT_SHOULDER_ROLL].toDouble());
	setJoint(JointsController::JOINT_RIGHT_SHOULDER_ROLL, -supportVal.toDouble()) ;

	//elbows roll
	supportVal = joints[JointsController::JOINT_LEFT_ELBOW_ROLL];
	setJoint(JointsController::JOINT_LEFT_ELBOW_ROLL, -joints[JointsController::JOINT_RIGHT_ELBOW_ROLL].toDouble());
	setJoint(JointsController::JOINT_RIGHT_ELBOW_ROLL, -supportVal.toDouble());

	//elbows yaw
	supportVal = joints[JointsController::JOINT_LEFT_ELBOW_YAW];
	setJoint(JointsController::JOINT_LEFT_ELBOW_YAW, -joints[JointsController::JOINT_RIGHT_ELBOW_YAW].toDouble());
	setJoint(JointsController::JOINT_RIGHT_ELBOW_YAW, -supportVal.toDouble());
}

QString Pose::stringify(){
	QString s("");
	s += QString::number(getIdentifier(), 'f', 0);
	s += " ";
	s += QString::number(getTime(), 'f', 3);
	JointsOrder order = JointsController::getJointsOrder();
	for(unsigned int i = 0; i<order.size(); i++){
		s += " ";
		s += joints[order.at(i)];
	}
	return s;
}

void  Pose::unstringify(QString stringified){
	QStringList tokens = stringified.split(' ',QString::SkipEmptyParts);
	setIdentifier(tokens.at(0).toDouble());
	setTime(tokens.at(1).toDouble());

	JointsOrder order = JointsController::getJointsOrder();
	for(unsigned int i = 0; i < order.size(); i++){
		joints[order.at(i)] = tokens.at(i+2);
	}

}
