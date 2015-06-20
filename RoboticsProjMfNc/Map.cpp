/*
 * Map.cpp
 *
 *  Created on: Jun 20, 2015
 *      Author: colman
 */

#include "Map.h"
namespace MNProj{
	Map::Map() {
		// TODO Auto-generated constructor stub

	}


	void wallThiking(int* grid)
	{
		int roboSizeX = ConfigManager::Instance()->getRobotSizeX();
		int roboSizeY = ConfigManager::Instance()->getRobotSizeY();
		int max = (roboSizeX > roboSizeY)?roboSizeX:roboSizeY;

		int pixelsResulotion = ConfigManager::Instance()->getMapResulotionCM();


	}

	void colorizeBufferSection(int* grid, int buffer, int x, int y)
	{
		int newX = ((x-buffer) < 0)?0:(x - buffer);
		int newY = ((y-buffer) < 0)?0:(y - buffer);

	}

	void fitResulotion(int* grid){

	}

	Map::~Map() {
		// TODO Auto-generated destructor stub
	}
}

