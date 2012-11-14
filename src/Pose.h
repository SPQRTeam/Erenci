/**
 * Erenci
 * LabRoCoCo: labrococo.dis.uniroma1.it
 * @author: Lorenzo Tognalini: lorenzo.togna@gmail.com
 *
 */

#ifndef POSE_H
#define POSE_H

#include <QObject>
#include "JointsController.h"

class MotionMaker;

/**
  * This class represent a Pose
  */
class Pose : public QObject
{
    Q_OBJECT
public:

    static const double     JOINT_TOLLERANCE;
	static const int		ID_NOT_SET;
	static const int		TIME_NOT_SET;
	static const QString	JOINT_NOT_SET;

	explicit Pose(MotionMaker *parent = 0, QString stringified = QString());
	~Pose();

	bool	isJointNUll(QString jointName);
	bool	isTimeSet();
	bool	isIdSet();

	/// if no identifier set return ID_NOT_SET
	int		getIdentifier();
	void	setIdentifier(int identifier);

	/// if no time set return TIME_NOT_SET`
	double	getTime();
	void	setTime(double time);

	void	setJoint(QString jointName, double value);

	/// reflect joint values between left and right sides( inverting head values and swapping arts ones ), time will not vary,
	void	reflect();

	QString stringify();
	/// extract values from the string as it seen and ordered in the list of pose view and put them in the pose
	void	unstringify(QString strigified);

signals:

public slots:

private:

	/// all joints name-value
	Joints joints;

	/// an (not)uniq identifier for this pose
	int identifier;

	/// interpolation duration
	double time;

};

#endif // POSE_H
