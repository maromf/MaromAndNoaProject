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

namespace MNProj {

	Location::Location(int xCoord, int yCoord) {
			setX(xCoord);
			setY(yCoord);
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

} /* namespace MNProj */
