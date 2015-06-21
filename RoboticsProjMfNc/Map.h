/*
 * Map.h
 *
 *  Created on: Jun 20, 2015
 *      Author: Marom
 */

#ifndef MAP_H_
#define MAP_H_


#include "MapLoader/LoadManager.h"
#include "Utils.h"

using namespace std;
namespace MNProj{
	class Map {
	private:
		LoadManager loadManager;
		std::vector<std::vector<int> > realWorldImage; // each cell 2.5x2.5 cm
		std::vector<std::vector<int> > RoboWorldGrid; // each cell 10x10 cm
		void colorizeBufferSection(std::vector<std::vector<int> > grid, int buffer, int row, int col, int rowLimit, int colLimit);
	public:
		Map();
		void generateImageGrid();
		void wallThiking(std::vector<std::vector<int> > grid);
		void fitResulotion(std::vector<std::vector<int> > grid);
		virtual ~Map();
	};
 }

#endif /* MAP_H_ */
