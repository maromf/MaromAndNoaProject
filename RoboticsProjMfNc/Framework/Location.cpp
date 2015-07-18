/**
 * Location.cpp
 *
 *  Purpose: Calculates the area of a circle and the volume
    of a sphere.

 *  Created on: Jun 23, 2015
 *  @author:    MaromF
 *  @version:   1.0
 */

#include "Location.h"

	Location::Location(int xCoord, int yCoord) {
			setX(xCoord);
			setY(yCoord);
	}

	Location::Location() {
			setX(0);
			setY(0);
	}

	Location::~Location() {
		// TODO Auto-generated destructor stub
	}

	int Location::getX(){
		return x;
	}

	int Location::getY(){
		  return y;
	}

	void Location::setX(int xCoord){
		  x = xCoord;
	}

	void Location::setY(int yCoord){
		  y = yCoord;
	}

	bool Location::operator== (Location b) const {
		if((x - b.getX()) && (y == b.getY()))
			return true;
		else{
			return false;
		}
	}

