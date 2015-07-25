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
#include "Framework/Waypoints.h"
#include "PathAlgorithem/PathPlannerAlgo.h"
#include "ConfigManager.h"

using namespace PlayerCc;

	PathPlannerAlgo* algo;
	Map* m;
	Waypoints* wP;
	Location* start;
	Location* end;

	int main(int argc, const char * argv[])
	{
		m = new Map(ConfigManager::Instance()->getMapPath());
		start = new Location(ConfigManager::Instance()->getStartX(), ConfigManager::Instance()->getStartY());
		end = new Location(ConfigManager::Instance()->getGoalX(), ConfigManager::Instance()->getGoalY());

		Location* roboStart = m->RealToRobotWorldLocation(*start);
		Location* roboEnd = m->RealToRobotWorldLocation(*end);

		algo = new PathPlannerAlgo(m,roboStart);
		std::vector<Location*> path = algo->generatePath(roboEnd);

		wP = new Waypoints(&path);
		std::vector<Location*> wayPoints = wP->getWaypoint();

        m->setPath(path);
        m->setStartAndEnd(roboStart, roboEnd);
        m->setWayPoints(wayPoints);
        m->PrintPng("Player/path.png");
//		Robot robot("localhost", 6665);
		return 0;
	}




