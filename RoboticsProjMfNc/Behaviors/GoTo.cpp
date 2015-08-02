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

	//initialize();
}

GoTo::~GoTo() {
	delete[] _goal;
}

bool GoTo::atGoalLocation()
{
	return (_robot->isAt(_goal , Utils::WAY_POINT_CONCER_DELTA));
}

bool GoTo::startCond()
{
	return !atGoalLocation();
}

bool GoTo::stopCond()
{
	return atGoalLocation();
}

void GoTo::action()
{
	while (!atGoalLocation())
	{
		_robot->invokeRead();
		initializeBehaviors();

		if (_turn->startCond())
		{
			while (!_turn->stopCond())
			{
				_turn->action();
			}

			_robot->setSpeed((double) 0, (double) 0);
		}

		_robot->invokeRead();

		if(_moveForward->startCond())
		{
			while (!_moveForward->stopCond())
			{
				_moveForward->action();
			}
			_robot->setSpeed((double) 0, (double) 0);
		}
	}
}

void GoTo::initializeBehaviors()
{
	_yaw = Utils::calcYaw(_robot->getCurrentLocation(), _goal);
	_turn = new Turn(_robot, _yaw);
	_moveForward = new MoveForward(_robot, _goal);

	//addNext(_turn);
	//addNext(_moveForward);
}
