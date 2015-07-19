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
#include "Robot.h"
#include "Map.h"
#include "Framework/Location.h"
#include "PathAlgorithem/PathPlannerAlgo.h"
#include "ConfigManager.h"

class RobotManager {
public:
	RobotManager(Robot* robot, Map* map);
	bool configRobot();
	void startRobot();
	virtual ~RobotManager();

private:
	Map* _map;
	Robot* _robot;
};


#endif /* ROBOTMANAGER_H_ */
