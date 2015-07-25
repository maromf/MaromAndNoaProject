/*
 * Waypoints.h
 *
 *  Created on: Jul 17, 2015
 *      Author: Noa
 */

#ifndef WAYPOINTS_H_
#define WAYPOINTS_H_

#include "Location.h"
#include <vector>
using namespace std;

class Waypoints {
private:
	std::vector<Location*> _waypoints;
public:
	Waypoints(std::vector<Location*>* astarVector);
	std::vector<Location*> getWaypoint();
};

#endif /* WAYPOINTS_H_ */
