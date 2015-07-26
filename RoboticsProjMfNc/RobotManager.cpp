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

bool RobotManager::configRobot() {
  return true;
}


bool RobotManager::startRobot(){

	if(!configRobot())
		return false;

	for (int i = 0; i < _points.size(); i++) {
		Location* currPoint = _points[i];
		//GoTo* behavior;

		_robot->invokeRead();

		while (_robot->isAt(currPoint,Utils::WAY_POINT_CONCER_DELTA)) {
		//	behavior = new GoTo(_robot, _localizationManager, currPoint);

			_robot->invokeRead();

		//	if (behavior->startCondition()) {
		//		while (!behavior->stopCondition()) {
		//			behavior->action();
		//		}
		//	}
		}
	}

	return true;
}

RobotManager::~RobotManager() {
	// TODO Auto-generated destructor stub
}

