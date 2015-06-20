/*
 * ConfigManager.cpp
 *
 *  Created on: Jun 19, 2015
 *      Author: Noa
 */

#include "ConfigManager.h"

ConfigManager* ConfigManager::_instance = 0;

ConfigManager* ConfigManager::Instance()
{
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
	if (file.is_open())
	{
		string temp;
		file >> temp >> _mapPath;
		file >> temp >> _startX;
		file >> temp >> _startY;
		file >> temp >> _startYaw;
		file >> temp >> _goalX;
		file >> temp >> _goalY;
		file >> temp >> _robotSizeX;
		file >> temp >> _robotSizeY;
		file >> temp >> _mapResulotionCM;
		file >> temp >> _gridResulotionCM;
		file.close();
	}
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
