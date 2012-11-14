/**
 * Erenci
 * LabRoCoCo: labrococo.dis.uniroma1.it
 * @author: Lorenzo Tognalini: lorenzo.togna@gmail.com
 *
 */

#ifndef MOTIONMAKER_H
#define MOTIONMAKER_H

#include <QWidget>
#include <QListWidget>
#include "JointsController.h"
#include "Pose.h"

namespace Ui {
    class MotionMaker;
}

class MotionMaker : public QWidget
{
    Q_OBJECT

public:
    explicit MotionMaker(QWidget *parent = 0);
    ~MotionMaker();

	void setJointsController(JointsController * jc);	/** do not own 'jc' */
	void setConnection(Connection * connection);		/** do not own 'connection' */
	QListWidget * getPoses(); //TODO this is just wrong, should be const

	/**
	 * TAKE MANAGEMENT of 'pose'
	 * add a given pose. adjusting identifier and idIndex if needed
	 */
	void addPose(Pose * pose);

signals:
	void itemListChanged();

public slots:
	void pushPose();
	void insertPose();
	void updatePose();
	void updateTime();
	void clonePose();
	void removePose();
	void reflectPose(); //reflect currently selected item
	void reflectPose(unsigned int itemNum); //reflect item at position itemNum
	void reflectAll();
	void movePoseUp();
	void movePoseDown();

	void playMotion();
	void playStep();
	void goToPose();
	void captureAndPush();

	void editPoseInline(QListWidgetItem * item);

	void toggleButtonEnabling(int code);

private:
	Ui::MotionMaker		* ui;
	JointsController	* jc;
	Connection			* connection;

	int posesIdIndex;
	JointsOrder jointsOrder;

	int getNextPoseId();
	QString composeItemPose();
	QString prepareProxyPose(QString itemPose, bool includeTime = true, double timeScale = 1.0);

};

#endif // MOTIONMAKER_H
