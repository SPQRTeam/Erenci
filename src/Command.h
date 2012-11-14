/**
 * Erenci
 * LabRoCoCo: labrococo.dis.uniroma1.it
 * @author: Lorenzo Tognalini: lorenzo.togna@gmail.com
 *
 */

#ifndef COMMAND_H
#define COMMAND_H

#include <QString>

namespace Command{

	/// (to execute a file with several robot poses (with extension .dat) - e.g. execute foo)
	static const QString EXECUTE = "execute";

	/// (terminate the program)
	static const QString EXIT = "exit";

	/// (retrieve the robot joints values - e.g: getjoints j1 ... jn)
	static const QString GET_JOINTS = "getjoints";

	/// (retrieve the robot joints stiffness values - e.g: getstiffness j1 ... jn)
	static const QString GET_STIFFNESS = "getstiffness";

	/// (the robot will get up from the floor - e.g. getup foo. Possible getup are: [FaceDown, FaceUp])
	static const QString GET_UP = "getup";
	static const QString PARAM_GET_UP_FACE_UP = "FaceUp";
	static const QString PARAM_GET_UP_FACE_DOWN = "FaceDown";

	/// (the robot executes the kick - e.g: kick foo. Possible kicks are: [BackLeft, BackRight, ForwardLeft, ForwardRight, SideLeft, SideRight])
	static const QString KICK = "kick";
	static const QString PARAM_KICK_BL = "BackLeft";
	static const QString PARAM_KICK_BR = "BackRight";
	static const QString PARAM_KICK_FL = "ForwardLeft";
	static const QString PARAM_KICK_FR = "ForwardRight";
	static const QString PARAM_KICK_SL = "SideLeft";
	static const QString PARAM_KICK_SR = "SideRight";

	/// (list of all possibles commands)
	static const QString LIST = "ls";

	/// (the robot moves its head in the given position - e.g. movehead yaw pitch velocity)
	static const QString MOVE_HEAD = "movehead";

	/// (this command will be sent from a remote tool, it is better if you do not use it here)
	static const QString PLAY = "play";

	/// (to retrieve current Nao image for sending it remotely)
	static const QString RETRIEVE_IMAGE = "retrieveimage";

	/// (the robot executes the save - e.g. save foo. Possible saves are: [CloseLeft, CloseRight, FarLeft, FarRight])
	static const QString SAVE = "save";
	static const QString PARAM_SAVE_CL = "CloseLeft";
	static const QString PARAM_SAVE_CR = "CloseRight";
	static const QString PARAM_SAVE_FL = "FarLeft";
	static const QString PARAM_SAVE_FR = "FarRight";

	/// (the robot says the string you give him)
	static const QString SAY = "say";

	/// (to set one or more robot joints - e.g: setjoints j1 v1 ... jn vn.
	static const QString SET_JOINTS = "setjoints";
			 //Joints names: HeadPitch, HeadYaw, LAnklePitch, LAnkleRoll, LElbowRoll, LElbowYaw, LHipPitch, LHipRoll, LHipYawPitch, LKneePitch,
				   //LShoulderPitch, LShoulderRoll, RAnklePitch, RAnkleRoll, RElbowRoll, RElbowYaw, RHipPitch, RHipRoll, RHipYawPitch, RKneePitch,
				   //RShoulderPitch, RShoulderRoll)

	/// (to set robot joints stiffness - e.g: setstiffness j1 v1 ... jn vn)
	static const QString SET_STIFFNESS = "setstiffness";

	/// (to set audio volume [0-1])
	static const QString SET_VOLUME = "setvolume";

	/// (in order to simulate robot readings, for t seconds, given a frequency - e.g.: simulatedreadings t f r1 x1 y1 t1 ... rn xn yn tn. Possible readings are: [Ball, MineGoal, OpponentGoal])
	static const QString SIMULATED_READINGS = "simulatedreadings";
	static const QString PARAM_SIM_READ_BALL = "Ball";
	static const QString PARAM_SIM_READ_MY_GOAL = "MineGoal";
	static const QString PARAM_SIM_READ_OPP_GOAL = "OpponentGoal";

	/** (the robot simulates a walk that follow a given path with a specified velocity - e.g.: simulatedwalk p v.
	  * Possibles paths are: walk for 1 meter in a specified direction
	  * [NegativeX = 0, NegativeXY = 1, NegativeY = 2, X = 3, XNegativeY = 4, XY = 5, Y = 6, YNegativeX = 7]
	  * or walk in a square of 1 meter [path = 8])
	  */
	static const QString SIMULATED_WALK = "simulatedwalk";

	/// (the robot sits on itself)
	static const QString SIT = "sit";

	/// (the robot stands itself)
	static const QString STAND = "stand";

	/// (the robot walk will be stopped)
	static const QString STOP_WALK = "stopwalk";

	/// (the robot starts walking with Aldebaran walkspeed - e.g. walk x y theta)
	static const QString WALK = "walk";

	/// (the robot starts walking with Aldebaran walkpos - e.g. walkpos x y theta)
	static const QString WALK_POS = "walkpos";


}

#endif // COMMAND_H
