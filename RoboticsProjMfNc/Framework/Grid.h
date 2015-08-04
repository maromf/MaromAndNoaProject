/**
 * Grid.h
 *
 *  Purpose: representing grid matrix of int.
 *  Gives comfortable access to data.

 *  Created on: Jul 24, 2015
 *  @author:    MaromF NoaC
 *  @version:   1.0
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

	Grid(int width, int height); // Ctor
	Grid(Grid* gridToCopy); // Copy Ctor

	/*
	 * Get the grid columns number.
	 */
	int getWidth();

	/*
	 * Get the grid rows number.
	 */
	int getHeight();

	/*
	 * Get the value of the given position at the grid.
	 */
	int getCellState(int x, int y);

	/*
	 * Set the value of the given position at the grid.
	 */
	void setCellState(int x, int y, int state);

	virtual ~Grid();

private:
	int _gridWidth;  // Grid columns number.
	int _gridHeight; // Grid rows number.
	vector<int> _world; // The vector in witch the data saved.

	/*
	 * Initialize the Grid
	 */
	void initGrid(int width, int height);


};

#endif /* GRID_H_ */
