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
	return true;
}

void Turn::action()
{
	_robot->setSpeed(0, 0);
}
