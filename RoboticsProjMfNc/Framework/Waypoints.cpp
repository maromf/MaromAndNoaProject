/*
 * Waypoints.cpp
 *
 *  Created on: Jul 17, 2015
 *      Author: colman
 */

#include "Waypoints.h"

Waypoints::Waypoints(vector<Location*> astarVector)
{
	int deltaX1, deltaX2, deltaY1, deltaY2;
	deltaX1 = astarVector[1]->getX() - astarVector[0]->getX();
	deltaY1 = astarVector[1]->getY() - astarVector[0]->getY();

	for(int i = 1; i < astarVector.size() - 1; i++)
	{
		deltaX2 = astarVector[i + 1]->getX() - astarVector[i]->getX();
		deltaY2 = astarVector[i + 1]->getX() - astarVector[i]->getX();

		if (deltaX1 != deltaX2 || deltaY1 != deltaY2)
		{
			_waypoints.push_back(astarVector[i + 1]);
		}

		deltaX1 = deltaX2;
		deltaY1 = deltaY2;
	}
	}

vector<Location*> Waypoints::getWaypoint()
{
	return _waypoints;
}
