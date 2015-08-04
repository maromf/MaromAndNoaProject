/**
 * Turn.cpp
 *
 *  Purpose: representing the Behavior of turning in place.

 *  Created on: Jul 24, 2015
 *  @author:    MaromF NoaC
 *  @version:   1.0
 */

#include "Turn.h"

Turn::Turn(Robot *robot, double yaw) : Behavior(robot) {
	setYaw(yaw);
}

void Turn::setYaw(double yaw)
{
	_yaw = yaw;
}

bool Turn::startCond()
{
	// If the robot is at not at the correct angle then start;
	return !inPosition();
}

bool Turn::stopCond()
{
	// If the robot is at correct angle then stop;
	return inPosition();
}

bool Turn::inPosition()
{
	_robot->invokeRead();

	// The robot current angle
	double r = _robot->getYaw();

	// the delta between the needed angle to the current.
	double yawDelta = abs(_yaw - r);

	// If the angles is equal
	bool n = _yaw == r;

	// If the delta is smaller then the permitted angle delta.
	bool d = yawDelta <= Utils::COMPROMISED_YAW;
	return n || d;
}

void Turn::action()
{
	// turn left mark
	int leftRightMark = 1;

	// If the angels delta is negative
	if (_yaw - _robot->getYaw() < 0)
	{
		// turn right mark
		leftRightMark = -1;
	}

	// Speed is fast.
	double speed = Utils::FAST_YAW_TURN_DELTA;

	// If the angles delta is smaller then the fast turn delta
	if(abs(_yaw - _robot->getYaw()) < Utils::FAST_YAW_DELTA) {

		// Speed is middle
		speed = Utils::MIDDEL_YAW_TURN_DELTA;
	}

	// If the angles delta is smaller then the middle turn delta
	if(abs(_yaw - _robot->getYaw()) < Utils::MIDDEL_YAW_DELTA) {

		// Speed is slow
		speed = Utils::SLOW_YAW_TURN_DELTA;
	}

	_robot->invokeRead();

	// Set the robot speed
	_robot->setSpeed(0, leftRightMark * speed);
	_robot->invokeRead();

	// set the robot angle
	_robot->setYaw(_robot->getOdometryYaw());

}
