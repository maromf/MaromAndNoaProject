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
		std::vector<vector<Utils::CellState> > image; // each cell 2.5x2.5 cm
		std::vector<vector<Utils::CellState> > RoboGrid; // each cell 10x10 cm
	public:
		Map();
		void wallThiking(int* grid);
		void fitResulotion(int* grid);
		virtual ~Map();
	};
 }

#endif /* MAP_H_ */
