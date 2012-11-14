/**
 * Erenci
 * LabRoCoCo: labrococo.dis.uniroma1.it
 * @author: Lorenzo Tognalini: lorenzo.togna@gmail.com
 *
 */

#ifndef ERENCI_H
#define ERENCI_H

#include <QMainWindow>
#include <QString>
#include <QLabel>
#include "Connection.h"
#include "Persistance.h"

namespace Ui {
    class Erenci;
}

class Erenci : public QMainWindow
{
    Q_OBJECT

public:
    explicit Erenci(QWidget *parent = 0);
	~Erenci();

public slots:
	//connections
	void createConnection();
	void destroyConnection();
	void hideConnectedControls();

	//status bar
	void showStatusMessage(QString message);
	void showStatusState(QString state);
	void setStatusEditsSaved(bool saved);

	void showAbout();
	void quit();

private:
	static const QString SETTING_NAME_ID_FOR_IP;

	Ui::Erenci			* ui;
	Connection			* connection;
	Persistance			* persistance;

	QLabel				* lblStatusPath;
	QLabel				* lblStatusSaved;
};

#endif // ERENCI_H
