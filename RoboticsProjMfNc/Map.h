/**
 * map.h
 *
 *  Purpose: Initialize and handle the map grid and image.
 *           Handle with map optimization, real world to Robot world and the opposite direction.

 *  Created on: Jun 20, 2015
 *  @author:    MaromF
 *  @version:   1.0
 */

#ifndef MAP_H_
#define MAP_H_


#include "MapLoader/LoadManager.h"
#include "Framework/Location.h"
#include <iostream>
#include <math.h>

using namespace std;
class Map {

	static const int FREE_CELL = 0;
	static const int OCCUPIED_CELL = 1;
	static const int UNKNOWN_CELL = 2;
	static const int PATH_CELL = 3;
	static const int START_CELL = 4;
	static const int END_CELL = 5;

	public:
		Map(char* path);            // Ctor
		virtual ~Map();   // Dtor

		/**
		    This method  responsible of generating the realWorldImage Grid.
		    The method gets the image file from the configuration model, reads its and transforms it into grid.
		    The method build the grid according to the given resolution from the configuration model.
		*/
		void generateImageGrid(char* path);

		/**
		    This method gets a grid, pixelResulotion and the robot size.
		    The method scan the given grid and extends all the occupied area according to the given robot size.

		    @param grid - The img grid to thick (vector<vector<int>>).
		    @param pixelsResulotion - The resolution of each pixel in the loaded image (CM) (double).
		    @param roboSizeX - The robot vertical Size (CM) (int).
		    @param roboSizeY - The robot horizontal Size (CM) (int).
		*/
		void wallThicking(Grid* grid, double pixelsResulotion, int roboSizeX, int roboSizeY);

		int getHeight();

		int getWidth();

		int getRealWorldHeight();

		int getRealWorldWidth();

		Location* RobotWorldToRealLocation(Location location);

		Location* RealToRobotWorldLocation(Location location);

		bool isFree(Location l);

		/**
		    This method gets a grid, pixel Resolution and Robot world Resolution.
		    The method creates and return new grid in fixed resolution according to the given resolutions.

		    @param grid - The img grid to thick (vector<vector<int>>).
		    @param pixelsResulotion - The resolution of each pixel in the loaded image (CM) (double).
		    @param roboWorldResulotion - The resolution of each cell at the robo world grid (CM) (double).
		    @return The new fixed grid.
		*/
		Grid* fitResolution(Grid* grid,
				double pixelsResulotion, double roboWorldResulotion);

		void PrintPng(const char* file);

		void setPath(std::vector<Location*> path);

private:
			LoadManager loadManager;
			Grid* realWorldGrid; // The real world grid
			Grid* RoboWorldGrid;  // The Robot world grid

			double _RatioRoboToReal;
			/**
			    This method gets grid and a region,
			    and changes the values ​​of the cells in this region to occupied.

			    @param grid - The img grid to run on (vector<vector<int>>).
			    @param buffer - The buffer that indicates the region on the grid (int).
			    @param startCoord - The start coordinate of the section (Location).
			    @param limitCoord - The limit of the grid - his size (Location).
			*/
			void colorizeBufferSection(Grid* grid, int buffer, Location startCoord);

			/**
			    This method gets grid and a region, and Returns true if one or more cells in the given region are occupied.
			    If all cells in the given region are free - returns true.

			    @param grid - The img grid to run on (vector<vector<int>>).
			    @param buffer - The buffer that indicates the region on the grid (int).
			    @param startCoord - The start coordinate of the section (Location).
			    @param limitCoord - The limit of the grid - his size (Location).
			*/
			bool checkIfOccupied(Grid* grid,Location location, int buffer);

			void printToConsole(Grid* grid);

			void printToPng(Grid* grid, const char* file);
};


#endif /* MAP_H_ */
