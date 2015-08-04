/**
 * Waypoints.h
 *
 *  Purpose: generates the optimal way points across the given path, for minimal turning.

 *  Created on: Jun 17, 2015
 *  @author:    Noa Cohen
 *  @version:   1.0
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
