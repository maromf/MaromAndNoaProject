/*
 * RobotManager.cpp
 *
 *  Created on: Jul 18, 2015
 *      Author: colman
 */

#include "RobotManager.h"


RobotManager::RobotManager(Robot* robot, Map* map, LocalizationManager* localization, std::vector<Location*> points) {
	_map = map;
	_robot = robot;
	_localization = localization;
	_points = points;
}


bool RobotManager::startRobot(){

	for (unsigned int i = (_points.size() - 1); i >= 0 ; i--) {
		Location* currPoint = _points[i];
		GoTo* behavior;

		_robot->invokeRead();

		while (!_robot->isAt(currPoint,Utils::WAY_POINT_CONCER_DELTA)) {
			behavior = new GoTo(_robot, _localization, currPoint);

			_robot->invokeRead();

			if (behavior->startCond()) {
				while (!behavior->stopCond()) {
					behavior->action();
				}
			}
		}
	}

	return true;
}

RobotManager::~RobotManager() {
	// TODO Auto-generated destructor stub
}

