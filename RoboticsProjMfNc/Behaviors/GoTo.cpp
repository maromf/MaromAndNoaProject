/*
 * GoTo.cpp
 *
 *  Created on: Jul 26, 2015
 *      Author: colman
 */

#include "GoTo.h"

GoTo::GoTo(Robot* robot, LocalizationManager* localManager, Location* goal) : Behavior(robot){
	_localManager = localManager;
	_goal = goal;
	_yaw = Utils::calcYaw(_robot->getCurrentLocation(), _goal);
}

GoTo::~GoTo() {
	delete[] _goal;
}

bool GoTo::startCond()
{

	return true;
}

bool GoTo::stopCond()
{
	return true;
}

void GoTo::action()
{

}
