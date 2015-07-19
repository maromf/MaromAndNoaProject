/*
 * Grid.h
 *
 *  Created on: Jul 19, 2015
 *      Author: colman
 */

#ifndef GRID_H_
#define GRID_H_

#include <vector>
#include <iostream>
#include "Location.h"
using namespace std;

class Grid {

public:

	static const int FREE_CELL_VALUE = 0;
	static const int OCCUPIED_CELL_VALUE = 1;

	Grid(int width, int height);
	Grid(Grid* gridToCopy);

	int getWidth();

	int getHeight();

	int getCellState(int x, int y);

	void setCellState(int x, int y, int state);

	virtual ~Grid();

private:
	int _gridWidth;
	int _gridHeight;
	vector<int> _world;

	void initGrid(int width, int height);


};

#endif /* GRID_H_ */
