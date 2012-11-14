/**
 * Erenci
 * LabRoCoCo: labrococo.dis.uniroma1.it
 * @author: Lorenzo Tognalini: lorenzo.togna@gmail.com
 *
 */

#include "AdvancedControllers.h"
#include "ui_AdvancedControllers.h"
#include "Command.h"

AdvancedControllers::AdvancedControllers(QWidget *parent) :
														QWidget(parent),
														ui(new Ui::AdvancedControllers){
    ui->setupUi(this);

	ui->pickerDirection->setLimits(-1, 1);
	ui->pickerWalkX->setLimits(-1, 1);
	ui->pickerWalkY->setLimits(-1, 1);

	ui->pickerDirection->setValue(0);
	ui->pickerWalkX->setValue(0);
	ui->pickerWalkY->setValue(0);

	ui->pickerDirection->showActivationCheck(false);
	ui->pickerWalkX->showActivationCheck(false);
	ui->pickerWalkY->showActivationCheck(false);

	connect(ui->txtSay,SIGNAL(returnPressed()), this, SLOT(commandSay()));
	connect(ui->btnSay, SIGNAL(clicked()), this, SLOT(commandSay()));
	connect(ui->sliderVolume, SIGNAL(valueChanged(int)), this, SLOT(commandChangeVolume(int)));
	connect(ui->chkMute, SIGNAL(toggled(bool)), this, SLOT(commandSwitchMute(bool)));

	connect(ui->btnSitDown, SIGNAL(clicked()), this, SLOT(commandSit()));
	connect(ui->btnStandUp, SIGNAL(clicked()), this, SLOT(commandStand()));
	connect(ui->btnGetUp, SIGNAL(clicked()), this, SLOT(commandGetUp()));

	connect(ui->btnSaveLeftClose, SIGNAL(clicked()), this, SLOT(commandSaveCloseL()));
	connect(ui->btnSaveRightClose, SIGNAL(clicked()), this, SLOT(commandSaveCloseR()));
	connect(ui->btnSaveRightFar, SIGNAL(clicked()), this, SLOT(commandSaveFarR()));
	connect(ui->btnSaveLeftFar, SIGNAL(clicked()), this, SLOT(commandSaveFarL()));

	connect(ui->btnKickBackLeft, SIGNAL(clicked()), this, SLOT(commandKickBackL()));
	connect(ui->btnKickBackRight, SIGNAL(clicked()), this, SLOT(commandKickBackR()));
	connect(ui->btnKickFrontLeft, SIGNAL(clicked()), this, SLOT(commandKickFrontL()));
	connect(ui->btnKickFrontRight, SIGNAL(clicked()), this, SLOT(commandKickFrontR()));
	connect(ui->btnKickSideLeft, SIGNAL(clicked()), this, SLOT(commandKickSideL()));
	connect(ui->btnKickSideRight, SIGNAL(clicked()), this, SLOT(commandKickSideR()));

	connect(ui->btnWalk, SIGNAL(clicked()), this, SLOT(commandWalk()));
	connect(ui->btnWalkStop, SIGNAL(clicked()), this, SLOT(commandStop()));

}

AdvancedControllers::~AdvancedControllers(){
    delete ui;
}

void AdvancedControllers::setConnection(Connection * connection){
	this->connection = connection;
}

//////////////////// COMMANDS ////////////////////////////////

void AdvancedControllers::commandSay(){
	sendCommand(Command::SAY, ui->txtSay->text().trimmed());
}

void AdvancedControllers::commandChangeVolume(int value){
	QString val = QString::number(value/(double)ui->sliderVolume->maximum());
	sendCommand(Command::SET_VOLUME,val);
}

void AdvancedControllers::commandSwitchMute(bool isChecked){
	if(isChecked){
		commandChangeVolume(0);
		ui->sliderVolume->setDisabled(true);
	}else{
		commandChangeVolume(ui->sliderVolume->value());
		ui->sliderVolume->setEnabled(true);
	}
}

void AdvancedControllers::commandSit(){
	sendCommand(Command::SIT);
}

void AdvancedControllers::commandStand(){
	sendCommand(Command::STAND);
}

void AdvancedControllers::commandGetUp(){
	QString param;
	if(ui->optGetUpFaceUp->isChecked()){
		param = QString(Command::PARAM_GET_UP_FACE_UP);
	}else{
		param = QString(Command::PARAM_GET_UP_FACE_DOWN);
	}
	sendCommand(Command::GET_UP,param);
}

void AdvancedControllers::commandSaveFarL(){
	sendCommand(Command::SAVE, Command::PARAM_SAVE_FL);
}

void AdvancedControllers::commandSaveFarR(){
	sendCommand(Command::SAVE, Command::PARAM_SAVE_FR);
}

void AdvancedControllers::commandSaveCloseL(){
	sendCommand(Command::SAVE, Command::PARAM_SAVE_CL);
}

void AdvancedControllers::commandSaveCloseR(){
	sendCommand(Command::SAVE, Command::PARAM_SAVE_CR);
}

void AdvancedControllers::commandKickFrontR(){
	sendCommand(Command::KICK, Command::PARAM_KICK_FR);
}

void AdvancedControllers::commandKickFrontL(){
	sendCommand(Command::KICK, Command::PARAM_KICK_FL);
}

void AdvancedControllers::commandKickBackR(){
	sendCommand(Command::KICK, Command::PARAM_KICK_BR);
}

void AdvancedControllers::commandKickBackL(){
	sendCommand(Command::KICK, Command::PARAM_KICK_BL);
}

void AdvancedControllers::commandKickSideR(){
	sendCommand(Command::KICK, Command::PARAM_KICK_SR);
}

void AdvancedControllers::commandKickSideL(){
	sendCommand(Command::KICK, Command::PARAM_KICK_SL);
}

void AdvancedControllers::commandWalk(){
	QString params;
	params.append(QString::number(ui->pickerWalkX->getValue()));
	params.append(" ");
	params.append(QString::number(ui->pickerWalkY->getValue()));
	params.append(" ");
	params.append(QString::number(ui->pickerDirection->getValue()));
	sendCommand(Command::WALK, params);
}

void AdvancedControllers::commandStop(){
	sendCommand(Command::STOP_WALK);
}


void AdvancedControllers::sendCommand(QString command, QString params){
	this->connection->query(QString(command).append(" ").append(params));
}

void AdvancedControllers::sendCommand(QString command){
	this->connection->query(QString(command));
}
