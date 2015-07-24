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
	Map::Map(char* path) {
		_RatioRoboToReal = 1;
		generateImageGrid(path);
	}

    void Map::generateImageGrid(char* path) {


    	// Generates grid out of the image.
    	realWorldGrid = loadManager.generateImgGrid(path);


    	// The pixels resolution - loaded from configuration.
		double pixelsResulotion = ConfigManager::Instance()->getMapResulotionCM();

		// The robot size - loaded from configuration.
		int roboSizeX = ConfigManager::Instance()->getRobotSizeX();
		int roboSizeY = ConfigManager::Instance()->getRobotSizeY();

		// The robot grid resolution - loaded from configuration.
		double roboWorldResulotion = ConfigManager::Instance()->getGridResulotionCM();


		_RatioRoboToReal = roboWorldResulotion / pixelsResulotion;

		// activate spending occupied cells in grid.
		wallThicking(realWorldGrid, pixelsResulotion, roboSizeX, roboSizeY);

		printToPng(realWorldGrid, "Player/WallThicking.png");


		// fit grid resolution.
		RoboWorldGrid = fitResolution(realWorldGrid, pixelsResulotion, roboWorldResulotion);

//		printToConsole(RoboWorldGrid);

		printToPng(RoboWorldGrid, "Player/Resolution.png");
    }

	int Map::getHeight() {
		return RoboWorldGrid->getHeight();
	}

	int Map::getWidth(){
		return RoboWorldGrid->getWidth();
	}

	int Map::getRealWorldHeight() {
		return realWorldGrid->getHeight();
	}

	int Map::getRealWorldWidth(){
		return realWorldGrid->getWidth();
	}

	Location* Map::RobotWorldToRealLocation(Location location) {
		int newX = location.getX() * _RatioRoboToReal;
		int newY = location.getY() * _RatioRoboToReal;

		Location* roboLocation = new Location(newX, newY);
		return roboLocation;
	}

	Location* Map::RealToRobotWorldLocation(Location location) {
		int newX = location.getX() / _RatioRoboToReal;
		int newY = location.getY() / _RatioRoboToReal;

		Location* realLocation = new Location(newX, newY);
		return realLocation;
	}

	bool Map::isFree(Location l) {
		return ((l.getX() >= getWidth()) || (l.getY() >= getHeight()))?false:
				((RoboWorldGrid->getCellState(l.getX(), l.getY()) == FREE_CELL)?true:false);
	}

	void Map::wallThicking(Grid* grid, double pixelsResulotion, int roboSizeX, int roboSizeY)
	{
		Grid* tempGrid;
//		(loadManager.getImagePixleRows(),
//				std::vector<int>(loadManager.getImagePixleColumns()));

		// Gets the bigger between the X and Y elements of the robot size.
		int maxRoboSize = (roboSizeX > roboSizeY) ? roboSizeX : roboSizeY;

		// The size of the cells to color around the each occupied cell according to given resolution.
		int buffer = ceil(maxRoboSize / pixelsResulotion);

		// Creating temp grid to run on, to private endless recursive painting on the grid.
		tempGrid = new Grid(*grid);

		// Running on grid cells.
		for (int i = 0; i < grid->getHeight(); i++)
		{
			for (int j = 0; j < grid->getWidth(); j++)
			{
				Location tempLocation = Location(j,i);

				// If cell is occupied then color all his buffered section.
				if(tempGrid->getCellState(j,i) == OCCUPIED_CELL)
					colorizeBufferSection(grid,buffer,tempLocation);
			}
		}
	}

	void Map::colorizeBufferSection(Grid* grid, int buffer, Location startCoord)
	{
		// Getting the row and column to start from. if their new value is out of bounds sets the to be 0.
		int newCol = ((startCoord.getX()-buffer) < 0)?0:(startCoord.getX() - buffer);
		int newRow = ((startCoord.getY()-buffer) < 0)?0:(startCoord.getY() - buffer);

		int limitCol = ((startCoord.getX() + buffer) >= grid->getWidth())?grid->getWidth():(startCoord.getX() + buffer);
		int limitRow = ((startCoord.getY() + buffer) >= grid->getHeight())?grid->getHeight():(startCoord.getY() + buffer);

		// Running on the given section to paint.
		for (int i = newRow; i < limitRow; i++)
		{
			for (int j = newCol; j < limitCol; j++)
			{
				grid->setCellState(j,i,OCCUPIED_CELL);
			}
		}

	}

	Grid* Map::fitResolution(Grid* grid,
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

		Grid* newGrid;
		newGrid = new Grid(newColumnsLenght, newRowsLenght);

		for (int i = 0; i < newRowsLenght; i++)
		{
			// Get the Y coordinate of the real world out of the robot grid x index.
			int realWorldY = ((int)(i * roboWorldRatio)) ;
			for (int j = 0; j < newColumnsLenght; j++)
			{
				// Get the X coordinate of the real world out of the robot grid y index.
				int realWorldX = ((int)(j * roboWorldRatio));

				// Indicates the real world grid location
				Location temLocation = Location(realWorldX, realWorldY);


				// If section is occupied then sets the current cell as occupied, else - free.
				if(checkIfOccupied(grid, temLocation, roboWorldRatio))
					newGrid->setCellState(j,i,OCCUPIED_CELL);
				else
					newGrid->setCellState(j,i,FREE_CELL);
			}
		}

		return newGrid;
	}


	bool Map::checkIfOccupied(Grid* grid,Location location, int buffer)
	{
		// Running on given section at the given grid.
		for(int i = location.getY(); i < (location.getY() + buffer); i++)
		{
			// If row is out of the grid bounds then break.
			if (i >= grid->getHeight())
				break;
			for(int j = location.getX(); j < (location.getX() + buffer); j++)
			{
				// If column is out of the grid bounds then break.
				if (j >= grid->getWidth())
					break;

				// If cell is occupied then return true.
				if (grid->getCellState(j,i) == OCCUPIED_CELL)
					return true;
			}
		}

		// There is no occupied cell at the section then return false.
		return false;
	}


    void Map::setPath(std::vector<Location*> path) {
		for(int i = 0; i < path.size(); i++)
		{
			RoboWorldGrid->setCellState(path[i]->getX(),path[i]->getY(), PATH_CELL);
		}
    }

    void Map::PrintPng(const char* file) {
    	printToPng(RoboWorldGrid, file);
    }

	void Map::printToConsole(Grid* grid) {

		for(int i = 0; i < grid->getHeight(); i++)
		{
			for(int j = 0; j < grid->getWidth(); j++)
			{
				cout << grid->getCellState(j,i);
			}
			cout << "\n";
		}

	}

	void Map::printToPng(Grid* grid, const char* file) {

		loadManager.SaveImgFromGrid(grid,file);
	}

	Map::~Map() {
		// TODO Auto-generated destructor stub
	}


