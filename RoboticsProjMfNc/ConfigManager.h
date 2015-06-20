/*
 * ConfigManager.h
 *
 *  Created on: Jun 19, 2015
 *      Author: colman
 */

#ifndef CONFIGMANAGER_H_
#define CONFIGMANAGER_H_

#include <fstream>
using namespace std;

class ConfigManager {
public:
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
	const char* CONFIG_PATH = "\parameters.txt";
	char* _mapPath;
	int _startX, _startY, _startYaw, _goalX, _goalY, _robotSizeX, _robotSizeY;
	double _mapResulotionCM, _gridResulotionCM;
	void inizializeData();
};

#endif /* CONFIGMANAGER_H_ */
