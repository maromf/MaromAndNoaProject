/*
 * PathPlannerAlgo.cpp
 *
 *  Created on: Jul 16, 2015
 *      Author: colman
 */

#include "PathPlannerAlgo.h"


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

	std::vector<Location> Locations;

	AlgoNode currentNode(_startLocation, 0);
	openQueue.push(currentNode);

	while (!openQueue.empty()) {
		AlgoNode node = openQueue.top();
		if(node.getLocation() == end ) {
			return retrivePath(node);
		}

		visitedNodes[std::make_pair(node.getLocation().getX(),node.getLocation().getY())] =
				PathPlannerAlgo::CLOSED_NODE;
		openQueue.pop();

		std::vector<AlgoNode> neighbors = getNeighborsNodes(node);
		for (int i = 0;  i < neighbors.size(); ++ i) {
			AlgoNode neighborNode = neighbors[i];
			int x = neighborNode.getLocation().getX();
			int y = neighborNode.getLocation().getY();

			visitedNodes[std::make_pair(x,y)] = PathPlannerAlgo::OPEN_NODE;
			openQueue.push(neighborNode);
		}
	}

	return Locations;
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

		if(visitedNodes[std::make_pair(newX,newY)] == PathPlannerAlgo::CLOSED_NODE) {
			continue;
		}

		AlgoNode neighbor(tempLocation, current.getGGrade() + directions[i].second);

		neighbor.calcHGrade(_endLocation);
		neighbor.setFatherLocation(current.getLocation());

		neighbors->push_back(neighbor);
	}

	return *neighbors;
}

std::vector<Location> PathPlannerAlgo::retrivePath(AlgoNode node) {
	std::vector<Location> path;
	Location tempLocation = node.getLocation();
	while(!(tempLocation == _startLocation)) {
		path.push_back(tempLocation);
		tempLocation = node.getFatherLocation();
	}
	path.push_back(tempLocation);
	return path;
}

PathPlannerAlgo::~PathPlannerAlgo() {
	// TODO Auto-generated destructor stub
}

