/**
 * Erenci
 * LabRoCoCo: labrococo.dis.uniroma1.it
 * @author: Lorenzo Tognalini: lorenzo.togna@gmail.com
 *
 */

#ifndef JOINTSCONTROLLER_H
#define JOINTSCONTROLLER_H

#include <QWidget>
#include <map>
#include <vector>
#include <QString>
#include "DoublePicker.h"
#include "Connection.h"

typedef std::map<QString, QString>	Joints;
typedef std::vector<QString>		JointsOrder;
typedef std::map<QString, std::pair<double, double> > JointsLimits;

namespace Ui {
    class JointsController;
}

class JointsController : public QWidget
{
    Q_OBJECT

public:

	static const QString JOINT_HEAD_PITCH;
	static const QString JOINT_HEAD_YAW;
	static const QString JOINT_LEFT_ANKLE_PITCH;
	static const QString JOINT_LEFT_ANKLE_ROLL;
	static const QString JOINT_LEFT_ELBOW_ROLL;
	static const QString JOINT_LEFT_ELBOW_YAW;
	static const QString JOINT_LEFT_HIP_PITCH;
	static const QString JOINT_LEFT_HIP_ROLL;
	static const QString JOINT_LEFT_HIP_YAW_PITCH;
	static const QString JOINT_LEFT_KNEE_PITCH;
	static const QString JOINT_LEFT_SHOULDER_PITCH;
	static const QString JOINT_LEFT_SHOULDER_ROLL;
	static const QString JOINT_RIGHT_ANKLE_PITCH;
	static const QString JOINT_RIGHT_ANKLE_ROLL;
	static const QString JOINT_RIGHT_ELBOW_ROLL;
	static const QString JOINT_RIGHT_ELBOW_YAW;
	static const QString JOINT_RIGHT_HIP_PITCH;
	static const QString JOINT_RIGHT_HIP_ROLL;
	static const QString JOINT_RIGHT_HIP_YAW_PITCH;
	static const QString JOINT_RIGHT_KNEE_PITCH;
	static const QString JOINT_RIGHT_SHOULDER_PITCH;
	static const QString JOINT_RIGHT_SHOULDER_ROLL;

	explicit JointsController(QWidget *parent = 0);
	~JointsController();

	double getJointMinValue(QString joint);
	double getJointMaxValue(QString joint);

public slots:
	void setConnection(Connection * connection); /** Will not own 'connection' */

	//communications with connection
	void setJoint(QString joint, double value);		/** send to the connection a single joint value */
	void setJointStiffness(QString joint, bool activate);/** send to the connection a single joint stiffness value */
	void updateJoints();							/** update the spin values as got from connection */
	void updateStiffness();							/** uncheck stiff if all 0 else check if all same and check else tristate*/
	void switchStiffness(int state);				/** set stiffness on robot according to ui value*/
	void setStiffness(bool enabled);				/** toggle stiffness checkbox (and set it on robot at [0.0|0.8] ) */

	//getters
	Joints				getJoints();
	static JointsOrder	getJointsOrder();
	static JointsLimits getJointsLimits();

private slots:
	QString sendCommand(QString cmd); /** send a command through the connection */
	void	setJoint(double value); /** use qt reflection to get the calling object to take the value to send to the connection */
	void	setJointStiffness(bool value);/** send a set stifness for a single joint, use qt reflection to get the calling object to take the value to send to the connection */

private:
    Ui::JointsController *ui;
	Connection * connection;

	std::map<QString, DoublePicker *> joints;
	std::map<QString, QString> pickerNamesToJoints;

	bool parseAndSetJointsValues(QString jointsValues);
	bool parseAndSetStiffness(QString stiffValues);
};


#endif // JOINTSCONTROLLER_H
