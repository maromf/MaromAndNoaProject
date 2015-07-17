/*
 * PathPlannerAlgo.cpp
 *
 *  Created on: Jul 16, 2015
 *      Author: colman
 */

#include "PathPlannerAlgo.h"

namespace MNProj {

PathPlannerAlgo::PathPlannerAlgo(Map map, Location start) {
	_startLocation = start;
	_map = map;
	initDirections();
}

void PathPlannerAlgo::initDirections() {
	directions.push_back(std::make_pair(Location( 1,-1), PathPlannerAlgo::DIAGONAL_MOV_SCORE));
	directions.push_back(std::make_pair(Location( 1, 0), PathPlannerAlgo::DIRECT_MOV_SCORE));
	directions.push_back(std::make_pair(Location( 1, 1), PathPlannerAlgo::DIAGONAL_MOV_SCORE));
	directions.push_back(std::make_pair(Location( 0, 1), PathPlannerAlgo::DIRECT_MOV_SCORE));
	directions.push_back(std::make_pair(Location(-1, 1), PathPlannerAlgo::DIAGONAL_MOV_SCORE));
	directions.push_back(std::make_pair(Location(-1, 0), PathPlannerAlgo::DIRECT_MOV_SCORE));
	directions.push_back(std::make_pair(Location(-1,-1), PathPlannerAlgo::DIAGONAL_MOV_SCORE));
	directions.push_back(std::make_pair(Location( 0,-1), PathPlannerAlgo::DIRECT_MOV_SCORE));
}

std::vector<Location> PathPlannerAlgo::generatePath(Location end) {


	for (int i = 0;  i < PathPlannerAlgo::directions.size(); ++ i) {

	}
}

std::vector<AlgoNode> PathPlannerAlgo::getNeighborsNodes(AlgoNode current) {

	std::vector<AlgoNode>* neighbors = 0;
	neighbors = new std::vector<AlgoNode>;
	for (int i = 0;  i < directions.size(); ++ i) {
		int newX = current.getLocation().getX() + directions[i].first.getX();
		int newY = current.getLocation().getY() + directions[i].first.getY();

		if( ( newX < 0 ) || ( newY < 0 ))
			continue;

		if( ( newX > (_map.getWidth() - 1) ) || ( ( newY > (_map.getHeight()) - 1) ))
			continue;

		Location tempLocation(newX,newY);
		if (!_map.isFree(tempLocation))
			continue;

		AlgoNode neighbor(tempLocation, current.getGGrade() + directions[i].second);

		//neighbors.push_back();
	}

	return *neighbors;
}

PathPlannerAlgo::~PathPlannerAlgo() {
	// TODO Auto-generated destructor stub
}

} /* namespace MNProj */
