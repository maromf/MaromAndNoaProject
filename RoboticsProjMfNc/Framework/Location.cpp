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

//	bool operator==(const Location & a, const Location & b) {
//		if ((a.getX() == b.getX()) && (a.getY() == b.getY()))
//			return true;
//		else{
//			return false;
//		}
//	}

} /* namespace MNProj */
