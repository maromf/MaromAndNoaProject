/*
 * RobotManager.h
 *
 *  Created on: Jul 18, 2015
 *      Author: colman
 */

#ifndef ROBOTMANAGER_H_
#define ROBOTMANAGER_H_

#include <libplayerc++/playerc++.h>
#include <iostream>
#include <vector>
#include "Robot.h"
#include "Map.h"
#include "Utils.h"
#include "Framework/Location.h"
#include "LocalizationModel/LocalizationManager.h"
#include "ConfigManager.h"

using namespace std;

class RobotManager {
public:
	RobotManager(Robot* robot, Map* map, LocalizationManager* localization, std::vector<Location*> points);
	bool configRobot();
	bool startRobot();
	virtual ~RobotManager();

private:
	Map* _map;
	Robot* _robot;
	LocalizationManager* _localization;
    std::vector<Location*> _points;
};


#endif /* ROBOTMANAGER_H_ */
