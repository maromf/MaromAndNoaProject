/**
 * Grid.cpp
 *
 *  Purpose: representing grid matrix of int.
 *  Gives comfortable access to data.

 *  Created on: Jul 24, 2015
 *  @author:    MaromF NoaC
 *  @version:   1.0
 */

#include "Grid.h"


Grid::Grid(int width, int height) {
	_gridWidth = width;
	_gridHeight = height;

	// initialize the grid.
	initGrid(width,height);
}

Grid::Grid(Grid* gridToCopy) {

	_gridWidth = gridToCopy->getWidth();
	_gridHeight = gridToCopy->getHeight();

	// initialize the grid.
	initGrid(_gridWidth,_gridHeight);

	// Runs over the given grid and copy the cells value.
	for(int i = 0; i < this->getWidth(); i++) {
		for(int j = 0; j < this->getHeight(); j++) {
			setCellState(i,j,gridToCopy->getCellState(i,j));
		}
	}
}

int Grid::getWidth() {
	return _gridWidth;
}

int Grid::getHeight() {
	return _gridHeight;
}

int Grid::getCellState(int x, int y) {

	// If the given x,y are out of the grid grid bound.
	if ((x >= getWidth()) || (y >= getHeight())) {
		cout << "getLocation: x- " << x <<  ", y- " << y << " do not exist on grid, return -1!";
		return -1;
	} else {
		// Gets the cell value, position on array is (y * width + x).
		return _world[(y * getWidth()) + x];
	}
}

void Grid::setCellState(int x, int y, int state) {

	// If the given x,y are out of the grid grid bound.
	if ((x >= getWidth()) || (y >= getHeight())) {
		cout << "setLocation: x- " << x << ", y- " << y<< " do not exist on grid!";
	} else {

		// Sets the cell value, position on array is (y * width + x).
		_world[(y * getWidth()) + x] = state;
	}
}

void Grid::initGrid(int width, int height) {

	_world = std::vector<int>();
	int freeCell = FREE_CELL_VALUE;

	// Runs over the grid width and height and push to the grid (represented by array) FREE cells.
	for(int i = 0; i < width; i++) {
		for(int j = 0; j < height; j++) {
			_world.push_back(freeCell);
		}
	}
}

Grid::~Grid() {
}
