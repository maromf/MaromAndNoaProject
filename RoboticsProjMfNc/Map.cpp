/**
 * map.h
 *
 *  Purpose: Initialize and handle the map grid and image.
 *           Handle with map optimization, real world to Robot world and the opposite direction.

 *  Created on: Jun 20, 2015
 *  @author:    MaromF
 *  @version:   1.0
 */

#include "Map.h"
namespace MNProj{
	Map::Map() {
		generateImageGrid();
	}

    void Map::generateImageGrid() {

    	// The map file path - loaded from configuration.
    	char* temp = ConfigManager::Instance()->getMapPath();

    	// Generates grid out of the image.
    	realWorldImage = loadManager.generateImgGrid(temp);

    	// The pixels resolution - loaded from configuration.
		double pixelsResulotion = ConfigManager::Instance()->getMapResulotionCM();

		// The robot size - loaded from configuration.
		int roboSizeX = ConfigManager::Instance()->getRobotSizeX();
		int roboSizeY = ConfigManager::Instance()->getRobotSizeY();

		// The robot grid resolution - loaded from configuration.
		double roboWorldResulotion = ConfigManager::Instance()->getGridResulotionCM();

		// activate spending occupied cells in grid.
		wallThicking(realWorldImage, pixelsResulotion, roboSizeX, roboSizeY);

		// fit grid resolution.
		RoboWorldGrid = fitResolution(realWorldImage, pixelsResulotion, roboWorldResulotion);
    }

	int Map::getHeight() {
		return RoboWorldGrid.size();
	}

	int Map::getWidth(){
		if (getHeight() == 0)
			return 0;
		else {
			return RoboWorldGrid[0].size();
		}
	}

	bool Map::isFree(Location l) {
		return ((l.getX() >= getWidth()) || (l.getY() >= getHeight()))?false:
				((RoboWorldGrid[l.getY()][l.getX()] == MNProj::FREE_CELL)?true:false);
	}

	void Map::wallThicking(std::vector<std::vector<int> > grid, double pixelsResulotion, int roboSizeX, int roboSizeY)
	{
		std::vector<std::vector<int> > tempGrid(loadManager.getImagePixleRows(),
				std::vector<int>(loadManager.getImagePixleColumns()));

		// Gets the bigger between the X and Y elements of the robot size.
		int maxRoboSize = (roboSizeX > roboSizeY) ? roboSizeX : roboSizeY;

		// The size of the cells to color around the each occupied cell according to given resolution.
		int buffer = ceil(maxRoboSize / pixelsResulotion);

		// The end point of the grid.
		Location gridLimit = Location(loadManager.getImagePixleRows(),loadManager.getImagePixleColumns());

		// Creating temp grid to run on, to private endless recursive painting on the grid.
		tempGrid = grid;

		// Running on grid cells.
		for (int i = 0; i < loadManager.getImagePixleRows(); i++)
		{
			for (int j = 0; j < loadManager.getImagePixleColumns(); j++)
			{
				Location tempLocation = Location(i,j);

				// If cell is occupied then color all his buffered section.
				if(tempGrid[i][j] == MNProj::OCCUPIED_CELL)
					colorizeBufferSection(grid,buffer,tempLocation,gridLimit);
			}
		}
	}

	void Map::colorizeBufferSection(std::vector<std::vector<int> > grid, int buffer, Location startCoord, Location limitCoord)
	{
		// Getting the row and column to start from. if their new value is out of bounds sets the to be 0.
		int newRow = ((startCoord.getX()-buffer) < 0)?0:(startCoord.getX() - buffer);
		int newCol = ((startCoord.getY()-buffer) < 0)?0:(startCoord.getY() - buffer);

		// Running on the given section to paint.
		for (int i = newRow; i < limitCoord.getX(); i++)
		{
			for (int j = newCol; j < limitCoord.getY(); j++)
			{
				// Paint the cell.
				grid[i][j] = MNProj::OCCUPIED_CELL;
			}
		}

	}

	std::vector<std::vector<int> > Map::fitResolution(std::vector<std::vector<int> > grid,
			double pixelsResulotion, double roboWorldResulotion)
	{

		// Indicates the ratio between the image resolution to the robot world resolution.
		double roboWorldRatio = roboWorldResulotion / pixelsResulotion;

		// If the ratio as value after decimal point , round the number up and announce it.
		if (roboWorldRatio != ceil(roboWorldRatio))
		{
			//TODO write warning or make fitable
			roboWorldRatio = ceil(roboWorldRatio);
		}

		// The new robot world grid size according to ratio.
		double newRowsLenght = loadManager.getImagePixleRows() / roboWorldRatio; // must be int
		double newColumnsLenght = loadManager.getImagePixleColumns( )/ roboWorldRatio; // must be int

		// If the rows length as value after decimal point , round the number up and announce it.
		if (newRowsLenght != ceil(newRowsLenght))
		{
			//TODO write warning or make fitable
			newRowsLenght = ceil(newRowsLenght);
		}

		// If the columns length as value after decimal point , round the number up and announce it.
		if (newColumnsLenght != ceil(newRowsLenght))
		{
			//TODO write warning or make fitable
			newColumnsLenght = ceil(newColumnsLenght);
		}

		std::vector<std::vector<int> > newGrid(newRowsLenght, std::vector<int>(newColumnsLenght));

		// The image bound point.
		Location limit = Location((int)loadManager.getImagePixleRows(), (int)loadManager.getImagePixleColumns());

		for (int i = 0; i < newRowsLenght; i++)
		{
			// Get the X coordinate of the real world out of the robot grid x index.
			int realWorldX = ((int)(i * roboWorldRatio)) % (int)newRowsLenght;
			for (int j = 0; j < newColumnsLenght; j++)
			{
				// Get the Y coordinate of the real world out of the robot grid y index.
				int realWorldY = ((int)(j * roboWorldRatio)) % (int)newColumnsLenght;

				// Indicates the real world grid location
				Location temLocation = Location(realWorldX, realWorldY);

				// If section is occupied then sets the current cell as occupied, else - free.
				if(checkIfOccupied(grid, temLocation, roboWorldRatio, limit))
					newGrid[i][j] = MNProj::OCCUPIED_CELL;
				else
					newGrid[i][j] = MNProj::FREE_CELL;
			}
		}

		return newGrid;
	}


	bool Map::checkIfOccupied(std::vector<std::vector<int> > grid,Location location, int buffer, Location limit)
	{
		// Running on given section at the given grid.
		for(int i = location.getX(); i < (location.getX() + buffer); i++)
		{
			// If row is out of the grid bounds then break.
			if (i >= limit.getX())
				break;
			for(int j = location.getY(); j < (location.getY() + buffer); j++)
			{
				// If column is out of the grid bounds then break.
				if (j >= limit.getY())
					break;

				// If cell is occupied then return true.
				if (grid[i][j] == OCCUPIED_CELL)
					return true;
			}
		}

		// There is no occupied cell at the section then return false.
		return false;
	}

	Map::~Map() {
		// TODO Auto-generated destructor stub
	}
}

