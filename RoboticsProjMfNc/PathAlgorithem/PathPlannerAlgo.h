/*
 * PathPlannerAlgo.h
 *
 *  Created on: Jul 16, 2015
 *      Author: colman
 */

#ifndef PATHPLANNERALGO_H_
#define PATHPLANNERALGO_H_

#include "../Framework/Location.h"
#include "../Map.h"
#include "AlgoNode.h"
#include <vector>
using namespace std;

namespace MNProj {


class PathPlannerAlgo {

	static const int DIRECT_MOV_SCORE = 10;
	static const int DIAGONAL_MOV_SCORE = 14;

    static std::vector<pair<Location,int> > directions;

public:
	PathPlannerAlgo(Map map,Location start);
	virtual ~PathPlannerAlgo();

    std::vector<Location> generatePath(Location end);
private:
    void initDirections();
    std::vector<AlgoNode> getNeighborsNodes(AlgoNode current);
    Map _map;
	Location _startLocation;
	Location _endLocation;
};

} /* namespace MNProj */

#endif /* PATHPLANNERALGO_H_ */
