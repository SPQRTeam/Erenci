/**
 * Erenci
 * LabRoCoCo: labrococo.dis.uniroma1.it
 * @author: Lorenzo Tognalini: lorenzo.togna@gmail.com
 *
 */

#ifndef VISION_H
#define VISION_H

#include <QWidget>
#include "Connection.h"

namespace Ui {
    class Vision;
}

class Vision : public QWidget{
    Q_OBJECT

public:
    explicit Vision(QWidget *parent = 0);
    ~Vision();

public slots:
	void subscribeNaoCamera();
	void unsubscribeNaoCamera();

	void connectNaoqi();
	void disconnectNaoqi();

	void setConnection(Connection * connection); /** does not own 'connection' management */

private:
	Ui::Vision *ui;
	Connection * connection;

	int socketId;
};

#endif // VISION_H
