/**
 * Erenci
 * LabRoCoCo: labrococo.dis.uniroma1.it
 * @author: Lorenzo Tognalini: lorenzo.togna@gmail.com
 *
 */

#ifndef ADVANCEDCONTROLLERS_H
#define ADVANCEDCONTROLLERS_H

#include <QWidget>
#include "Connection.h"

namespace Ui {
    class AdvancedControllers;
}

class AdvancedControllers : public QWidget
{
    Q_OBJECT

public:
    explicit AdvancedControllers(QWidget *parent = 0);
    ~AdvancedControllers();

	void setConnection(Connection * connection); /** do not own 'connection' */

public slots:

	void commandSay();
	void commandChangeVolume(int value);
	void commandSwitchMute(bool isChecked);

	void commandSit();
	void commandStand();
	void commandGetUp();

	void commandSaveFarL();
	void commandSaveFarR();
	void commandSaveCloseL();
	void commandSaveCloseR();

	void commandKickFrontR();
	void commandKickFrontL();
	void commandKickBackR();
	void commandKickBackL();
	void commandKickSideR();
	void commandKickSideL();

	void commandWalk();
	void commandStop();

private:
	void sendCommand(QString command, QString params);
	void sendCommand(QString command);
    Ui::AdvancedControllers *ui;

	Connection * connection;
};

#endif // ADVANCEDCONTROLLERS_H
