/**
 * Erenci
 * LabRoCoCo: labrococo.dis.uniroma1.it
 * @author: Lorenzo Tognalini: lorenzo.togna@gmail.com
 *
 */
#include "Erenci.h"
#include "ui_Erenci.h"
#include <QString>
#include <QDebug>
#include <QSettings>
#include <QFileDialog>
#include <QMessageBox>
#include <QListWidget>

const QString Erenci::SETTING_NAME_ID_FOR_IP = "ErenciConnectionIP";

Erenci::Erenci(QWidget *parent) : QMainWindow(parent), ui(new Ui::Erenci){

	ui->setupUi(this);

	QCoreApplication::setOrganizationName("LabRoCoCo");
	QCoreApplication::setOrganizationDomain("labrococo.dis.uniroma1.it");
	QCoreApplication::setApplicationName("Erenci");


	//setting status bar

	this->lblStatusSaved = new QLabel(statusBar());
	this->lblStatusSaved->setObjectName(QString("lblStatusSaved"));
	statusBar()->addPermanentWidget(lblStatusSaved);

	this->lblStatusPath = new QLabel(statusBar());
	this->lblStatusPath->setObjectName(QString("lblStatusPath"));
	statusBar()->addPermanentWidget(lblStatusPath);
	statusBar()->showMessage("Ready", 2000);

	//init components

	this->connection = 0;
	ui->motionMaker->setJointsController(ui->jointsController);
	this->persistance = new Persistance(this);
	this->persistance->setModel(ui->motionMaker);

	ui->txtConnect->setText(QSettings().value(Erenci::SETTING_NAME_ID_FOR_IP).toString());
	this->showMaximized();

	//status bar connections
	connect(persistance, SIGNAL(fileSaved(bool)), this, SLOT(setStatusEditsSaved(bool)));

	//actions events
	connect(ui->actionOpen, SIGNAL(triggered()), this->persistance, SLOT(open()));
	connect(ui->actionSave, SIGNAL(triggered()), this->persistance, SLOT(save()));
	connect(ui->actionClose, SIGNAL(triggered()), this->persistance, SLOT(close()));
	connect(ui->actionSaveACopy, SIGNAL(triggered()), this->persistance, SLOT(saveACopy()));
	connect(ui->actionExport, SIGNAL(triggered()), this->persistance, SLOT(exportToDat()));
	connect(ui->actionImport, SIGNAL(triggered()), this->persistance, SLOT(importDat()));
	connect(ui->actionReflectAll, SIGNAL(triggered()), ui->motionMaker, SLOT(reflectAll()));

	connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(showAbout()));
	connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(quit()));

	//connection events
	connect(ui->btnConnect, SIGNAL(clicked()), this, SLOT(createConnection()));
	connect(ui->txtConnect, SIGNAL(returnPressed()), this, SLOT(createConnection()));
	connect(ui->btnDisconnect, SIGNAL(clicked()), this, SLOT(destroyConnection()));

}

Erenci::~Erenci(){
	persistance->close();
	destroyConnection();
	delete ui;
	delete persistance;
}

void Erenci::showAbout(){
	QMessageBox::about(this,
					"SPQR eReNCi",
					"A Remote Nao Console By SPQR Team.\nSapienza University - LabRoCoCo\ncontact: Lorenzo Tognalini: lorenzo.togna@gmail.com");
}

void Erenci::quit(){
	QApplication::quit();
}

///////////////////// STATUS BAR /////////////////////////////////

void Erenci::showStatusMessage(QString message){
	statusBar()->showMessage(message, 2000);
}

void Erenci::showStatusState(QString state){
	this->lblStatusPath->setText(state);
}

void Erenci::setStatusEditsSaved(bool saved){
	if(saved){
		this->lblStatusSaved->setText(QString(""));
	}else{
		this->lblStatusSaved->setText(QString("(NOT SAVED)"));
	}
}

///////////////////// NETWORK CONNECTION ////////////////////////////

void Erenci::createConnection(){
	if(this->connection != 0){
		qDebug() << "connection already present. destroying it!";
		delete this->connection;
	}

	this->connection = new Connection();
	connect(this->connection, SIGNAL(disconnected()), this, SLOT(hideConnectedControls()));

	bool connected = connection->connectToNao(ui->txtConnect->text().trimmed());

	if(connected){
		ui->jointsController->setConnection(this->connection);
		ui->motionMaker->setConnection(this->connection);
		ui->advancedControls->setConnection(this->connection);
		//ui->visionController->setConnection(this->connection);

		ui->btnConnect->setDisabled(true);
		ui->btnDisconnect->setEnabled(true);
		ui->tabControls->setEnabled(true);
		ui->motionMaker->setEnabled(true);
		//ui->visionController->setEnabled(true);
		ui->txtConnect->setDisabled(true);

		//caching the connection nao name
		QSettings * settings = new QSettings();
		settings->setValue(Erenci::SETTING_NAME_ID_FOR_IP, ui->txtConnect->text().trimmed());
		settings->sync();
		delete settings;

	}else{
		QMessageBox errMsg(this);
		errMsg.setModal(true);
		QString msg = connection->getError();
		errMsg.setText(msg);
		errMsg.exec();
	}
}

void Erenci::destroyConnection(){
	if(this->connection != 0){
		delete this->connection;
		this->connection = 0;
		this->hideConnectedControls();
	}else{
		qDebug() << "connection not present for destroying";
	}
}

void Erenci::hideConnectedControls(){
	ui->btnConnect->setDisabled(false);
	ui->btnDisconnect->setEnabled(false);
	ui->tabControls->setEnabled(false);
	ui->motionMaker->setEnabled(false);
	//ui->visionController->setEnabled(false);
	ui->txtConnect->setDisabled(false);
}
