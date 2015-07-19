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
#include <queue>
#include <map>
#include "prioritySort.h"
using namespace std;



class PathPlannerAlgo {

	static const int DIRECT_MOV_SCORE = 10;
	static const int DIAGONAL_MOV_SCORE = 14;
	static const int OPEN_NODE = 1;
	static const int CLOSED_NODE = 2;

public:
	PathPlannerAlgo(Map* map,Location* start);
	virtual ~PathPlannerAlgo();

    std::vector<Location*> generatePath(Location* end);
private:
    void initDirections();
    std::vector<AlgoNode> getNeighborsNodes(AlgoNode current);
    std::vector<Location*> retrivePath(AlgoNode node);
    Map* _map;
	Location* _startLocation;
	Location* _endLocation;
    std::priority_queue<AlgoNode,std::vector<AlgoNode>, prioritySort> openQueue;
	std::vector<pair<Location,int> > directions;
    std::map<std::pair<int,int>, int> visitedNodes;
};

#endif /* PATHPLANNERALGO_H_ */
