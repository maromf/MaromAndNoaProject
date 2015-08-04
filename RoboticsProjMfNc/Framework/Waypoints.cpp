/**
 * Waypoints.cpp
 *
 *  Purpose: generates the optimal way points across the given path, for minimal turning.

 *  Created on: Jun 17, 2015
 *  @author:    Noa Cohen
 *  @version:   1.0
 */

#include "Waypoints.h"

Waypoints::Waypoints(std::vector<Location*>* astarVector)
{
	int deltaX1, deltaX2, deltaY1, deltaY2;

	// The delta of the the first point from the second.
	deltaX1 = astarVector->at(1)->getX() - astarVector->at(0)->getX();
	deltaY1 = astarVector->at(1)->getY() - astarVector->at(0)->getY();

	// First push to the way points the end location.
	_waypoints.push_back(astarVector->at(0));

	// Runs over the given path
	for(int i = 1; i < astarVector->size() - 1; i++)
	{
		// The delta of the the current point from the the point ahead.
		deltaX2 = astarVector->at(i + 1)->getX() - astarVector->at(i)->getX();
		deltaY2 = astarVector->at(i + 1)->getY() - astarVector->at(i)->getY();

		// If the current delta is different from the previous
		// then the direction is change and this is way point
		if (deltaX1 != deltaX2 || deltaY1 != deltaY2)
		{
			// Push the way point.
			_waypoints.push_back(astarVector->at(i));
		}

		// sets the previous delta to be the current one.
		deltaX1 = deltaX2;
		deltaY1 = deltaY2;
	}
}

std::vector<Location*> Waypoints::getWaypoint()
{
	return _waypoints;
}
