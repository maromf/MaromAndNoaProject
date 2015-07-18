/*
 * Main.cpp
 *
 *  Created on: May 26, 2015
 *      Author: colman
 */

#include <libplayerc++/playerc++.h>
#include <iostream>
#include "Robot.h"
#include "Map.h"
#include "Framework/Location.h"
#include "PathAlgorithem/PathPlannerAlgo.h"
#include "ConfigManager.h"

using namespace PlayerCc;

namespace MNProj{
	PathPlannerAlgo* algo;
	Map* m;
	Location* start;
	Location* end;

	int main()
	{
		ConfigManager::Instance()->getGoalY();
		m = new Map();
		m->generateImageGrid();
		start = new Location(ConfigManager::Instance()->getStartX(), ConfigManager::Instance()->getStartY());
		end = new Location(ConfigManager::Instance()->getGoalX(), ConfigManager::Instance()->getGoalY());
		algo = new PathPlannerAlgo(*m,*start);
		algo->generatePath(*end);
		Robot robot("localhost", 6665);
		return 0;
	}
};




