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

bool Turn::startCond()
{
	return !inPosition();
}

bool Turn::stopCond()
{
	return inPosition();
}

bool Turn::inPosition()
{
	_robot->invokeRead();
	double r = _robot->getYaw();
	double yawDelta = abs(_yaw - r);
	bool n = _yaw == r;
	bool d = yawDelta <= Utils::COMPROMISED_YAW;
	return n || d;
}

void Turn::action()
{
	int leftRightMark = 1;

	if (_yaw - _robot->getYaw() < 0)
	{
		leftRightMark = -1;
	}

	double speed = Utils::FAST_YAW_TURN_DELTA;
	if(abs(_yaw - _robot->getYaw()) < Utils::FAST_YAW_DELTA) {
		speed = Utils::MIDDEL_YAW_TURN_DELTA;
	}

	if(abs(_yaw - _robot->getYaw()) < Utils::MIDDEL_YAW_DELTA) {
		speed = Utils::SLOW_YAW_TURN_DELTA;
	}
	_robot->invokeRead();
	_robot->setSpeed(0, leftRightMark * speed);
	_robot->invokeRead();
	_robot->setYaw(_robot->getOdometryYaw());

}
