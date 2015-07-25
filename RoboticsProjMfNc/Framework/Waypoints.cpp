/*
 * Waypoints.cpp
 *
 *  Created on: Jul 17, 2015
 *      Author: colman
 */

#include "Waypoints.h"

Waypoints::Waypoints(std::vector<Location*>* astarVector)
{
	int deltaX1, deltaX2, deltaY1, deltaY2;
	deltaX1 = astarVector->at(1)->getX() - astarVector->at(0)->getX();
	deltaY1 = astarVector->at(1)->getY() - astarVector->at(0)->getY();

	for(int i = 1; i < astarVector->size() - 1; i++)
	{
		deltaX2 = astarVector->at(i + 1)->getX() - astarVector->at(i)->getX();
		deltaY2 = astarVector->at(i + 1)->getY() - astarVector->at(i)->getY();

		if (deltaX1 != deltaX2 || deltaY1 != deltaY2)
		{
			_waypoints.push_back(astarVector->at(i));
		}

		deltaX1 = deltaX2;
		deltaY1 = deltaY2;
	}
}

std::vector<Location*> Waypoints::getWaypoint()
{
	return _waypoints;
}
