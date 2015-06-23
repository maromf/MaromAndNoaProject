/*
 * Main.cpp
 *
 *  Created on: May 26, 2015
 *      Author: colman
 */

#include <libplayerc++/playerc++.h>
#include <iostream>
#include "Robot.h"
#include "ConfigManager.h"

using namespace PlayerCc;

int main()
{
    ConfigManager::Instance()->getGoalY();
	Robot robot("localhost", 6665);
	return 0;
}




