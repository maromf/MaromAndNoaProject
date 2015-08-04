/*
 * MoveForward.cpp
 *
 *  Created on: May 26, 2015
 *      Author: colman
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

	/*bool MoveForward::checkObstacleInFront()
	{
		bool isObstacleInFront = false;
		int minIndex = _robot->deg_to_index(MIN_ANGLE);
		int maxIndex = _robot->deg_to_index(MAX_ANGLE);

		std::vector<double>* scan = _robot->getLaserScan();

		for (int i = minIndex; i <= maxIndex; i++)
		{
			if (scan->at(i) < MAX_DIST_TO_OBSTACLE)
			{
				isObstacleInFront = true;
				break;
			}
		}

		return isObstacleInFront;
	}*/


bool MoveForward::startCond()
{
	return !atGoalLocation() && !checkObstacles();
}

bool MoveForward::stopCond()
{
	return checkObstacles() || atGoalLocation() || checkIfDistanceIncrees();
}

// TODO: maybe use the original code up
bool MoveForward::checkObstacles()
{
	for (int i = Utils::degreesToIndex((Utils::TOTAL_DEGREES / 2) - 25);
		  	 i < Utils::degreesToIndex((Utils::TOTAL_DEGREES / 2) + 25);
			 i += Utils::degreesToIndex(3))
		{
			if (_robot->getLaserDistance(i) < Utils::MINIMUM_DISTANCE_FROM_WALL)
			{
				return true;
			}
		}

	return false;
}

bool MoveForward::checkIfDistanceIncrees() {
	double d = _robot->getCurrentLocation()->getDistance(_goal);
	if(d > _lastD)
		return true;
	else {
		return false;
	}
}

bool MoveForward::atGoalLocation()
{
	return (_robot->isAt(_goal, Utils::WAY_POINT_CONCER_DELTA));
}

void MoveForward::action()
{
	double d = _robot->getCurrentLocation()->getDistance(_goal);
	double speed = Utils::SLOW_FORWARD_SPEED;
	_lastD = d;
	//if(d < Utils::FAST_FORWARD_DELTA) {
	//	speed = Utils::MIDDEL_FORWARD_SPEED;
	//}

	//if(d < Utils::MIDDEL_FORWARD_DELTA) {
	//	speed = Utils::SLOW_FORWARD_SPEED;
	//}

	_robot->invokeRead();
	_robot->setSpeed(speed, 0);
	_robot->invokeRead();
	_robot->setLocation(_robot->getOdometryLocation());
}

