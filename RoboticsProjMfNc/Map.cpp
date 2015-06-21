/*
 * Map.cpp
 *
 *  Created on: Jun 20, 2015
 *      Author: Marom
 */

#include "Map.h"
namespace MNProj{
	Map::Map() {
		generateImageGrid();
	}

    void Map::generateImageGrid() {
    	char* temp = ConfigManager::Instance()->getMapPath();
    	realWorldImage = loadManager.generateImgGrid(temp);
    }

	void Map::wallThiking(std::vector<std::vector<int> > grid)
	{
		std::vector<std::vector<int> > tempGrid(loadManager.getImagePixleRows(), std::vector<int>(loadManager.getImagePixleColumns()));
		int roboSizeX = ConfigManager::Instance()->getRobotSizeX();
		int roboSizeY = ConfigManager::Instance()->getRobotSizeY();
		int buffer = (roboSizeX > roboSizeY)?roboSizeX:roboSizeY;

		tempGrid = grid;
		for (int i = 0; i < loadManager.getImagePixleRows(); i++)
		{
			for (int j = 0; j < loadManager.getImagePixleColumns(); j++)
			{
				if(tempGrid[i][j] == MNProj::OCCUPIED_CELL)
					colorizeBufferSection(grid,buffer,i,j,loadManager.getImagePixleRows(),loadManager.getImagePixleColumns());
			}
		}

	}

	void Map::colorizeBufferSection(std::vector<std::vector<int> > grid, int buffer, int row, int col, int rowLimit, int colLimit)
	{

		int newRow = ((row-buffer) < 0)?0:(row - buffer);
		int newCol = ((col-buffer) < 0)?0:(col - buffer);

		for (int i = newRow; i < rowLimit; i++)
		{
			for (int j = newCol; j < colLimit; j++)
			{
				grid[i][j] = MNProj::OCCUPIED_CELL;
			}
		}

	}

	void Map::fitResulotion(std::vector<std::vector<int> > grid){
		int pixelsResulotion = ConfigManager::Instance()->getMapResulotionCM();

	}

	Map::~Map() {
		// TODO Auto-generated destructor stub
	}
}

