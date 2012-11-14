/**
 * Erenci
 * LabRoCoCo: labrococo.dis.uniroma1.it
 * @author: Lorenzo Tognalini: lorenzo.togna@gmail.com
 *
 */

#include "Vision.h"
#include "ui_Vision.h"
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <QDebug>
#include <QImage>
#include <QPixmap>

Vision::Vision(QWidget *parent) :
								QWidget(parent),
								ui(new Ui::Vision){
    ui->setupUi(this);

	//connect(ui->btnConnect, SIGNAL(clicked()), this, SLOT(connectNaoqi()));
	//connect(ui->btnDisconnect, SIGNAL(clicked()), this, SLOT(disconnectNaoqi()));

	ui->btnConnect->setEnabled(true);
	ui->btnDisconnect->setDisabled(true);
	ui->btnAcquire->setDisabled(true);
	ui->btnStop->setDisabled(true);
	ui->graphicsVideo->setDisabled(true);

}

Vision::~Vision(){
	disconnectNaoqi();
    delete ui;
}

void Vision::connectNaoqi(){

//	struct sockaddr_in myAddress;
//	socklen_t len;

//	socketId = socket(AF_INET,SOCK_STREAM,0);

//	myAddress.sin_family = AF_INET;
//	myAddress.sin_port = htons(30001);
//	myAddress.sin_addr.s_addr = inet_addr(connection->getIP().toStdString().c_str());

//	len = sizeof(myAddress);

//	if (::connect(socketId,(sockaddr*) &myAddress,len) == -1){
//		qWarning() << "Impossible to connect to the socket [port = 30001]. Unfortunately, you cannot retrieve Nao image from server...";
//		return;
//	}

//	ui->btnConnect->setDisabled(true);
//	ui->btnDisconnect->setEnabled(true);
}

void Vision::disconnectNaoqi(){

//	::close(socketId);

//	ui->btnConnect->setEnabled(true);
//	ui->btnDisconnect->setDisabled(true);
}

void Vision::subscribeNaoCamera(){

	//unsigned char buffer[3072000];
	//int ret = recv(socketId, buffer, 3072000, MSG_WAITALL);

	//QImage image(buffer,280,352,280,QImage::Format_Indexed8);
	//QImage image(buffer, 320, 240, QImage::Format_RGB888 );
	//QPixmap * pixmap = new QPixmap();

}

void Vision::unsubscribeNaoCamera(){

}

void Vision::setConnection(Connection *connection){
	this->connection = connection;
}
