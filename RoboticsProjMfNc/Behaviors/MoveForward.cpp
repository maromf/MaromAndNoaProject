/**
 * MoveForward.cpp
 *
 *  Purpose: representing the Behavior of moving forward.

 *  Created on: Jul 24, 2015
 *  @author:    MaromF NoaC
 *  @version:   1.0
 */
#include "MoveForward.h"
#define MIN_ANGLE -30
#define MAX_ANGLE 30
#define MAX_DIST_TO_OBSTACLE 0.5
#define FORWARD_SPEED 0.2

MoveForward::MoveForward(Robot *robot, Location *goal) : Behavior(robot) {
	_goal = goal;
	_lastD = 1380;
}

MoveForward::~MoveForward() {
	delete[] _goal;
}

bool MoveForward::startCond()
{
	// If the robot is at goal location or if there is obstacle ahead then do not start;
	return !atGoalLocation() && !checkObstacles();
}

bool MoveForward::stopCond()
{
	// If the robot is at goal location, if there is obstacle ahead or if the distance increase then stop;
	return checkObstacles() || atGoalLocation() || checkIfDistanceIncrees();
}

// TODO: maybe use the original code up
bool MoveForward::checkObstacles()
{
	// Runs over the index degrees ( -25 to 25 from robots angle).
	for (int i = Utils::degreesToIndex((Utils::TOTAL_DEGREES / 2) - 25);
		  	 i < Utils::degreesToIndex((Utils::TOTAL_DEGREES / 2) + 25);
			 i += Utils::degreesToIndex(3))
		{
		    // If laser scans at index i is smaller then minimum distance then there is obstacle in front.
			if (_robot->getLaserDistance(i) < Utils::MINIMUM_DISTANCE_FROM_WALL)
			{
				return true;
			}
		}

	return false;
}

bool MoveForward::checkIfDistanceIncrees() {

	// The current distance from goal point.
	double d = _robot->getCurrentLocation()->getDistance(_goal);

	// If previous distance is smaller then the current then the distance does increase.
	if(d > _lastD)
		return true;
	else {
		return false;
	}
}

bool MoveForward::atGoalLocation()
{
	// Check if the robot is at goal location with distance delta.
	return (_robot->isAt(_goal, Utils::WAY_POINT_CONCER_DELTA));
}

void MoveForward::action()
{
	double d = _robot->getCurrentLocation()->getDistance(_goal);
	double speed = Utils::SLOW_FORWARD_SPEED;

	// Sets the previous distance to be the current.
	_lastD = d;

	_robot->invokeRead();

	// Sets the robot direct speed.
	_robot->setSpeed(speed, 0);
	_robot->invokeRead();

	// sets the robot location.
	_robot->setLocation(_robot->getOdometryLocation());
}

