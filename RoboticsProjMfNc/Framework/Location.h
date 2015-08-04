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

#include <cmath>

class Location {
private:
	double x;  // Indicates the position X coordinate.
	double y;  // Indicates the position Y coordinate.

public:

	Location(double xCoord, double yCoord); // Ctor
	Location();
	virtual ~Location();              // Dtor

	/**
	    Returns the X coordinate.

	    @return The X coordinate (int).
	*/
	double getX();

	/**
	    Returns the Y coordinate.

	    @return The Y coordinate (int).
	*/
	double getY();

	/**
	    Sets the Location X coordinate.

	    @param xCoord - The X coordinate.
	*/
	void setX(double xCoord);

	/**
	    Sets the Location Y coordinate.

	    @param xCoord - The Y coordinate.
	*/
    void setY(double yCoord);

	/**
	    Returns the distance of the current location from the given goal location.

	    @return The distance from the given location (double).
	*/
    double getDistance(Location* b);

    /*
     * Compare operator
     */
    bool operator== (Location* b) const;

    bool operator!= (Location* b) const;
};


#endif /* LOCATION_H_ */
