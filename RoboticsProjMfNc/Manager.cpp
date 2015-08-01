/*
 * Manager.cpp
 *
 *  Created on: Jul 25, 2015
 *      Author: colman
 */

#include "Manager.h"

Manager::Manager(Robot* robot, ConfigManager* config) {
	_robot = robot;
	_configuration = config;
	_end = 0;
	_start = 0;
    _map = 0;
    _roboManager = 0;
    _localization = 0;
    _startYaw = 0;
}

bool Manager::initialize() {
	_map = new Map( (const char *)_configuration->getMapPath());
	Location* start = new Location(_configuration->getStartX(), _configuration->getStartY());
	Location* end = new Location(_configuration->getGoalX(), _configuration->getGoalY());

	_start = _map->RealToRobotWorldLocation(*start);
	_end = _map->RealToRobotWorldLocation(*end);

	_startYaw = _configuration->getStartYaw();

	PathPlannerAlgo* algo = new PathPlannerAlgo(_map,_start);
	_path = algo->generatePath(_end);

	Waypoints* wP = new Waypoints(&_path);

	_points = wP->getWaypoint();

	_localization = new LocalizationManager();

	_roboManager = new RobotManager(_robot, _map, _localization, _points);
	return (_path.size() != 0);
}

bool Manager::startRuning() {

	if(!_robot->configRobot(_map, _start, _startYaw))
		return false;

   return _roboManager->startRobot();
}

void Manager::finish(const char* file) {
	_map->setPath(_path);
	_map->setStartAndEnd(_start, _end);
	_map->setWayPoints(_points);
	_map->PrintPng(file);
}

Manager::~Manager() {
	// TODO Auto-generated destructor stub
}

