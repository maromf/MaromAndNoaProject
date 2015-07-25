/*
 * PathPlannerAlgo.cpp
 *
 *  Created on: Jul 16, 2015
 *      Author: colman
 */

#include "PathPlannerAlgo.h"


PathPlannerAlgo::PathPlannerAlgo(Map* map, Location* start) {
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

std::vector<Location*> PathPlannerAlgo::generatePath(Location* end) {

	std::vector<Location*> Locations;

	_endLocation = end;

	int counter = 0;
	AlgoNode* currentNode = new AlgoNode(_startLocation, 0);
	openQueue.push(currentNode);

	while (!openQueue.empty()) {
		AlgoNode* node = openQueue.top();
		if((node->getLocation()->getX() == _endLocation->getX()) &&
		   (node->getLocation()->getY() == _endLocation->getY())) {
			return retrivePath(node);
		}
		counter ++;
		openQueue.pop();

		visitedNodes[std::make_pair(node->getLocation()->getX(),node->getLocation()->getY())] =
				std::make_pair(node, PathPlannerAlgo::CLOSED_NODE);

		std::vector<AlgoNode*> neighbors = getNeighborsNodes(node);
		for (int i = 0;  i < neighbors.size(); ++ i) {
			AlgoNode* neighborNode = neighbors[i];
			int x = neighborNode->getLocation()->getX();
			int y = neighborNode->getLocation()->getY();

			visitedNodes[std::make_pair(x,y)] = std::make_pair(neighborNode, PathPlannerAlgo::OPEN_NODE);
			neighborNode->setFatherNode(node);
			openQueue.push(neighborNode);
		}
	}

	return Locations;
}

std::vector<AlgoNode*> PathPlannerAlgo::getNeighborsNodes(AlgoNode* current) {

	std::vector<AlgoNode*>* neighbors = 0;
	neighbors = new std::vector<AlgoNode*>;
	for (int i = 0;  i < directions.size(); ++ i) {
		int newX = current->getLocation()->getX() + directions[i].first.getX();
		int newY = current->getLocation()->getY() + directions[i].first.getY();

		if( ( newX < 0 ) || ( newY < 0 ))
			continue;

		if( ( newX > (_map->getWidth() - 1) ) || ( ( newY > (_map->getHeight()) - 1) ))
			continue;

		Location* tempLocation = new Location(newX,newY);
		if (!_map->isFree(*tempLocation))
			continue;

		if((visitedNodes.count(std::make_pair(newX,newY)) == 1) &&
			(visitedNodes[std::make_pair(newX,newY)].second == PathPlannerAlgo::CLOSED_NODE)){
			continue;
		}


		int newG = current->getGGrade() + directions[i].second;

		if((visitedNodes.count(std::make_pair(newX,newY)) == 1) &&
			(visitedNodes[std::make_pair(newX,newY)].second == PathPlannerAlgo::OPEN_NODE)){

			int tempHGrade = visitedNodes[std::make_pair(newX,newY)].first->calcFixingHGrade(_endLocation);

			if(visitedNodes[std::make_pair(newX,newY)].first->getGrade() < (newG + tempHGrade) ) {
				continue;
			}
			else {
				if((visitedNodes[std::make_pair(newX,newY)].first->getGrade() == (newG + tempHGrade)) &&
				   (visitedNodes[std::make_pair(newX,newY)].first->getHGrade() < tempHGrade)) {
					continue;
				} else {
					visitedNodes[std::make_pair(newX,newY)].first->setGGrade(newG);
					visitedNodes[std::make_pair(newX,newY)].first->reGenerateGrade(_endLocation);
				}
			}

		} else {
			AlgoNode* neighbor = new AlgoNode(tempLocation, newG);

			neighbor->calcFixingHGrade(_endLocation);
			neighbors->push_back(neighbor);
		}
	}

	return *neighbors;
}

std::vector<Location*> PathPlannerAlgo::retrivePath(AlgoNode* node) {
	std::vector<Location*> path;
	AlgoNode* tempNode = node;
	while(tempNode -> getGGrade() != 0) {
		path.push_back(tempNode->getLocation());
		tempNode = tempNode->getFatherNode();
	}
	path.push_back(tempNode->getLocation());
	return path;
}

PathPlannerAlgo::~PathPlannerAlgo() {
	// TODO Auto-generated destructor stub
}

