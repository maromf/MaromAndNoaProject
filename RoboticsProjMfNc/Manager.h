/*
 * Manager.h
 *
 *  Created on: Jul 25, 2015
 *      Author: colman
 */

#ifndef MANAGER_H_
#define MANAGER_H_


#include <libplayerc++/playerc++.h>
#include "Robot.h"
#include "Map.h"
#include <vector>
#include <iostream>
#include "Framework/Location.h"
#include "Framework/Waypoints.h"
#include "PathAlgorithem/PathPlannerAlgo.h"
#include "ConfigManager.h"
#include "Framework/Location.h"

using namespace std;

class Manager {
public:
	Manager(Robot* robot, ConfigManager* config);
	bool initialize();
	bool startRuning();
	void finish(const char* file);
	virtual ~Manager();

private:
	Robot* _robot;
	Map* _map;
	Location* _start;
	Location* _end;
	std::vector<Location*> _points;
	ConfigManager* _configuration;
	std::vector<Location*> _path;
};


#endif /* MANAGER_H_ */
