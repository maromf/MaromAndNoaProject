/*
 * Grid.cpp
 *
 *  Created on: Jul 19, 2015
 *      Author: colman
 */

#include "Grid.h"


Grid::Grid(int width, int height) {
	_gridWidth = width;
	_gridHeight = height;

	initGrid(width,height);
}

Grid::Grid(Grid* gridToCopy) {

	_gridWidth = gridToCopy->getWidth();
	_gridHeight = gridToCopy->getHeight();

	initGrid(_gridWidth,_gridHeight);

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

	if ((x >= getWidth()) || (y >= getHeight())) {
		cout << "getLocation: x- " << x <<  ", y- " << y << " do not exist on grid, return -1!";
		return -1;
	} else {
		return _world[(y * getWidth()) + x];
	}
}

void Grid::setCellState(int x, int y, int state) {
	if ((x >= getWidth()) || (y >= getHeight())) {
		cout << "setLocation: x- " << x << ", y- " << y<< " do not exist on grid!";
	} else {
		_world[(y * getWidth()) + x] = state;
	}
}

void Grid::initGrid(int width, int height) {

	_world = std::vector<int>();
	int freeCell = FREE_CELL_VALUE;
	for(int i = 0; i < width; i++) {
		for(int j = 0; j < height; j++) {
			_world.push_back(freeCell);
		}
	}
}

Grid::~Grid() {
}
