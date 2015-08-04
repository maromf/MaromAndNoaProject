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
#include "ConfigManager.h"
#include "Manager.h"

using namespace std;
using namespace PlayerCc;

	Manager* manager;
	Robot* robo;


	int main(int argc, const char * argv[])
	{
		robo = new Robot("10.10.245.63", 6665);
		manager = new Manager(robo, ConfigManager::Instance());

		if(manager->initialize()) {
			if(manager->startRuning()) {
				manager->finish("Player/FinalPath.png");
				cout << "Running was ended successfully!";
			} else {
               cout << "Running was unsuccessful, robot was not reached his destination!";
			}
		} else {
			cout << "Running was not started, map was not initialized!";
		}

		return 0;
	}








