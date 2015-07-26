/*
 * ConfigManager.cpp
 *
 *  Created on: Jun 19, 2015
 *      Author: Noa
 */

#define PROP_SEP ":"

#include "ConfigManager.h"

ConfigManager* ConfigManager::_instance = 0;

ConfigManager* ConfigManager::Instance()
{
	// when Configuration Manager not initialized
	if (_instance == 0)
	{
		_instance = new ConfigManager();
		_instance->inizializeData();
	}

	return _instance;
}

void ConfigManager::inizializeData()
{
	ifstream file;

	file.open(CONFIG_PATH, ios::in);

	if (!file.is_open())
	{
		cout << "Could not open the parameters file.";
	}
	else
	{
		string line;

		// get configuration lines and set the properties
		while (getline(file, line))
		{
			setProperty(line);
		}

		file.close();
	}
}

void ConfigManager::setProperty(string line)
{
	size_t propSplit = line.find(PROP_SEP);

	// check if line is valid (with property separator)
	if (propSplit == string::npos)
	{
		cout << "Property not exists.";
	}
	else
	{
		// split the property name and the property values
		string propName = line.substr(0, propSplit);
		string propValue = line.substr(propSplit + 2);

		// set property value into the manager
		if (!setPropertyValue(propName, propValue))
		{
			// no matching property
			cout << "Property " + propName + "not exists.";
		}
	}
}

bool ConfigManager::setPropertyValue(string propName, string propValue)
{
	bool success = true;

	vector<string> values = splitline(propValue);

	if (propName == "map") {
		_mapPath = const_cast<char*>(values[0].c_str());
	}
	else if (propName == "startLocation") {
		_startX = atoi(values[0].c_str());
		_startY = atoi(values[1].c_str());
		_startYaw = atoi(values[2].c_str());
	}
	else if (propName == "goal") {
		_goalX = atoi(values[0].c_str());
		_goalY = atoi(values[1].c_str());
	}
	else if (propName == "robotSize") {
		_robotSizeX = atoi(values[0].c_str());
		_robotSizeY = atoi(values[0].c_str());
	}
	else if (propName == "MapResolutionCM"){
		_mapResulotionCM = atof(values[0].c_str());
	}
	else if (propName == "GridResolutionCM") {
		_gridResulotionCM = atof(values[0].c_str());
	}
	// no matching title
	else {
		success = false;
	}

	return success;
}

vector<string> ConfigManager::splitline(string str)
{
	string str2;
	vector<string> splitted;
	size_t pos;

	str.erase(str.find_last_not_of(" \n\r\t")+1);

	// put the values in vector - separate relays on spaces.
	// loop end when there is no more spaces.
	while ((pos = str.find_first_of(" ")) != string::npos)
	{
		// cut value and push it into the vector
		str2 = str.substr(0, pos);
		splitted.push_back(str2);

		// delete current value from the big string
		str = str.substr(pos + 1);
	}

	// push the last value.
	splitted.push_back(str);

	return splitted;
}

char* ConfigManager::getMapPath()
{
	return _mapPath;
}
int ConfigManager::getStartX()
{
	return _startX;
}
int ConfigManager::getStartY()
{
	return _startY;
}
int ConfigManager::getStartYaw()
{
	return _startYaw;
}
int ConfigManager::getGoalX()
{
	return _goalX;
}
int ConfigManager::getGoalY()
{
	return _goalY;
}
int ConfigManager::getRobotSizeX()
{
	return _robotSizeX;
}
int ConfigManager::getRobotSizeY()
{
	return _robotSizeY;
}
double ConfigManager::getMapResulotionCM()
{
	return _mapResulotionCM;
}
double ConfigManager::getGridResulotionCM()
{
	return _gridResulotionCM;
}
