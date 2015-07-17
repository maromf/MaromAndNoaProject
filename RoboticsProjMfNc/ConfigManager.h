/*
 * ConfigManager.h
 *
 *  Created on: Jun 19, 2015
 *      Author: Noa
 */

#ifndef CONFIGMANAGER_H_
#define CONFIGMANAGER_H_

#include <fstream>
#include <iostream>
#include <vector>
#include <stdlib.h>
using namespace std;

class ConfigManager {
public:
	// Get the current configuration manager - singelton.
	static ConfigManager* Instance();
	char* getMapPath();
	int getStartX();
	int getStartY();
	int getStartYaw();
	int getGoalX();
	int getGoalY();
	int getRobotSizeX();
	int getRobotSizeY();
	double getMapResulotionCM();
	double getGridResulotionCM();

private:
	ConfigManager(){}
	static ConfigManager *_instance;
	const char* CONFIG_PATH = "./parameters.txt";
	char* _mapPath;
	int _startX, _startY, _startYaw, _goalX, _goalY, _robotSizeX, _robotSizeY;
	double _mapResulotionCM, _gridResulotionCM;
	void inizializeData();

	// Set configuration property from the configuration file, line: configuration file line.
	void setProperty(string line);

	// Set property value into manager property from configuration file line.
	// propName: property name, propValue: property value (all the values in one string separated with spaces)
	// return value: if the setting succeeded or not.
	bool setPropertyValue(string propName, string propValue);

	// Split string - relays on spaces.
	vector<string> splitline(string str);
};

#endif /* CONFIGMANAGER_H_ */
