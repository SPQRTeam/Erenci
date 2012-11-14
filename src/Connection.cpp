/**
 * Erenci
 * LabRoCoCo: labrococo.dis.uniroma1.it
 * @author: Lorenzo Tognalini: lorenzo.togna@gmail.com
 *
 */

#include "Connection.h"
#include <QDebug>
#include <QTcpSocket>
#include <QHostAddress>
#include <QString>
#include <QMessageBox>

Connection::Connection(QObject *parent) : QObject(parent),
										ip(QString()){

	socket = 0;
	socket = new QTcpSocket(this);

	connect(socket,SIGNAL(disconnected()),this,SLOT(disconnect()));

}

Connection::~Connection(){

	socket->disconnectFromHost();
	if (socket->state() == QAbstractSocket::UnconnectedState ||
			socket->waitForDisconnected(1000)){
		qDebug("disconnected!");
	}
	delete this->socket;
	qDebug() << "Connection deleted";
}

bool Connection::connectToNao(QString ip){
	qDebug() << "creating Connection...";

	QHostAddress address(ip.trimmed());

	socket->connectToHost(address, Connection::port);
	if (socket->waitForConnected(5000)){
		qDebug() << "Connection created";
		this->ip = ip;
		return true;
	}else{
		qDebug() << "Connection failed";
		return false;
	}

}

QString Connection::getError(){
	return socket->errorString();
}

QString Connection::getIP(){
	return this->ip;
}

void Connection::disconnect(){
	this->ip = QString();
	emit disconnected();
}

QString Connection::query(QString query){
	this->write(query);
	return this->read();
}


void Connection::write(QString content){
	qDebug() << "SENT:" << content;
	content.append("\n");
	socket->write(content.toStdString().c_str());
	socket->flush();
}

QString	Connection::read(){
	int maxSize = 2048;
	char * data = new char[maxSize];
	socket->waitForReadyRead(10000);
	qint64 numChars = socket->readLine(data, maxSize);
	QString msg;
	if(numChars > 0){
		msg = QString(data);
	}else{
		qWarning() << "WARNING: Connection: no data recived after read";
	}
	//QString msg("getjoints headpitch 1.1 headyaw 2.2 lanklepitch 3.3 lankleroll 4.4 lelbowroll 5.5 lelbowyaw 6.6 lhippitch 7.7 lhiproll 8.8 lhipyawpitch 9.9 lkneepitch 10.10 lshoulderpitch 11.11 lshoulderroll 12.12 ranklepitch 13.13 rankleroll 14.14 relbowroll 15.15 relbowyaw 16.16 rhippitch 17.17 rhiproll 18.18 rhipyawpitch 19.19 rkneepitch 20.20 rshoulderpitch 21.21 rshoulderroll 22.22");
	msg.truncate(msg.size()-1);
	qDebug() << "RCVD:" << msg;
	if(msg.isEmpty()){
		msg.append("0");
	}
	return msg;
}




