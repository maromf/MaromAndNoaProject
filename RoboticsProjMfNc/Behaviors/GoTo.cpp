/**
 * GoTo.cpp
 *
 *  Purpose: representing the Behavior of going to point,
 *  use the turn behavior and the move forward for getting to point.

 *  Created on: Jul 24, 2015
 *  @author:    MaromF NoaC
 *  @version:   1.0
 */

#include "GoTo.h"

GoTo::GoTo(Robot* robot, LocalizationManager* localManager, Location* goal) : Behavior(robot){
	_localManager = localManager;
	_goal = goal;
}

GoTo::~GoTo() {
	delete[] _goal;
}

bool GoTo::atGoalLocation()
{
	// Check if the robot is at goal location with distance delta.
	return (_robot->isAt(_goal , Utils::WAY_POINT_CONCER_DELTA));
}

bool GoTo::startCond()
{
	// If the robot is at goal location then do not start;
	return !atGoalLocation();
}

bool GoTo::stopCond()
{
	// If the robot is at goal location then stop;
	return atGoalLocation();
}

void GoTo::action()
{
	// While the robot has not reached his goal point.
	while (!atGoalLocation())
	{
		_robot->invokeRead();

		// Initialize the turn and move forward according to goal.
		initializeBehaviors();

		// If can and need to turn
		if (_turn->startCond())
		{

			// While not reach the goal angle
			while (!_turn->stopCond())
			{
				NormalizeLocation();
				// Turn the robot
				_turn->action();
			}

			// The robot at the correct angel, stop the robot
			_robot->setSpeed((double) 0, (double) 0);
		}

		_robot->invokeRead();

		// If can and need to move forward
		if(_moveForward->startCond())
		{
			// While not reach the goal point
			while (!_moveForward->stopCond())
			{
				// Move forward
				_moveForward->action();
			}

			// The robot reached the goal point or got into obstacle, stop the robot
			_robot->setSpeed((double) 0, (double) 0);
		}
	}
}

void GoTo::NormalizeLocation() {
	Location* prevLocation = _localManager->GetProbablyPosition();
	double deltaX = abs(prevLocation->getX() - _robot->getCurrentLocation()->getX());
	double deltaY = abs(prevLocation->getY() - _robot->getCurrentLocation()->getY());
	Location* deltaLocation = new Location(deltaX, deltaY);

	double probYawDelta = abs(_localManager->GetProbablyYaw() - _robot->getYaw())
	_localManager->updateAll(deltaLocation, probYawDelta,  _robot->getLaserScan() , _goal);
	_robot->invokeRead();
	Location* probRobotLocation = _localManager->GetProbablyPosition();
	_normalizeLocation = probRobotLocation;
	_normalizeDistance = _normalizeLocation->getDistance(_robot->getCurrentLocation());

	printProbLocation();

	_yaw = Utils::calcYaw(_normalizeLocation, _goal);
	_turn->setYaw(_yaw);

	_robot->invokeRead();
	_robot->setOdometry(_normalizeLocation , _localManager->GetProbablyYaw());
	_robot->invokeRead();

	// sets the robot location.
	_robot->setLocation(_robot->getOdometryLocation());

	_robot->invokeRead();

	_robot->setYaw(_robot->getOdometryYaw());
}

void GoTo::printProbLocation() {
	cout << "position: " << _normalizeLocation-> getX() << "," << _normalizeLocation-> getY() << endl;
}

void GoTo::initializeBehaviors()
{
	// Calculates the needed angle to turn.
	_yaw = Utils::calcYaw(_robot->getCurrentLocation(), _goal);

	// Initialize the turn behavior.
	_turn = new Turn(_robot, _yaw);

	// Initialize the move forward behavior.
	_moveForward = new MoveForward(_robot, _goal);
}
