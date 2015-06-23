/**
 * Location.h
 *
 *  Purpose: Calculates the area of a circle and the volume
    of a sphere.

 *  Created on: Jun 23, 2015
 *  @author:    MaromF
 *  @version:   1.0
 */

#ifndef LOCATION_H_
#define LOCATION_H_

namespace MNProj {

class Location {
private:
	int x;  // Indicates the position X coordinate.
	int y;  // Indicates the position Y coordinate.

public:

	Location(int xCoord, int yCoord); // Ctor
	virtual ~Location();              // Dtor

	/**
	    Returns the X coordinate.

	    @return The X coordinate (int).
	*/
	int getX();

	/**
	    Returns the Y coordinate.

	    @return The Y coordinate (int).
	*/
	int getY();

	/**
	    Sets the Location X coordinate.

	    @param xCoord - The X coordinate.
	*/
	void setX(int xCoord);

	/**
	    Sets the Location Y coordinate.

	    @param xCoord - The Y coordinate.
	*/
    void setY(int yCoord);
};

} /* namespace MNProj */

#endif /* LOCATION_H_ */
