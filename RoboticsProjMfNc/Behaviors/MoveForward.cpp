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
#define FORWARD_SPEED 0.5

	MoveForward::MoveForward(Robot *robot, Location *goal) : Behavior(robot) {
		_goal = goal;
	}

	MoveForward::~MoveForward() {
		// TODO Auto-generated destructor stub
	}

	bool MoveForward::checkObstacleInFront()
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
	}


	bool MoveForward::startCond()
	{
		cout << "Moving forward!" << endl;
		return true;
	}

	bool MoveForward::stopCond()
	{
		if (_robot->getCurrentLocation()->getDistance(_goal) <= Utils::COMPROMISED_DISTANCE)
				return true;

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

	void MoveForward::action()
	{
		_robot->setSpeed(FORWARD_SPEED, 0);
	}

