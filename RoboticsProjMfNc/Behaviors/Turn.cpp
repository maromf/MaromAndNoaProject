/*
 * Turn.cpp
 *
 *  Created on: Jul 25, 2015
 *      Author: colman
 */

#include "Turn.h"

Turn::Turn(Robot *robot, float yaw) : Behavior(robot) {
	_yaw = yaw;
}

Turn::~Turn() {
	// TODO Auto-generated destructor stub
}

bool Turn::startCond()
{
	cout << "Turning" << endl;
	return true;
}

bool Turn::stopCond()
{
	double yawDelta = _yaw - _robot->getYaw();
	return (_yaw == _robot->getYaw() || yawDelta <= Utils::COMPROMISED_YAW);
}

void Turn::action()
{
	int leftRightMark = 1;

	if (_yaw - _robot->getYaw() < 0)
	{
		leftRightMark = -1;
	}

	_robot->setSpeed(0, leftRightMark * Utils::YAW_TURN_DELTA);
}
