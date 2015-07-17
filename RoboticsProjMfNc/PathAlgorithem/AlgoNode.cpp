/*
 * AlgoNode.cpp
 *
 *  Created on: Jul 16, 2015
 *      Author: colman
 */

#include "AlgoNode.h"


namespace MNProj {

AlgoNode::AlgoNode(Location position, int GGrade) {
	_currentPosition = position;
	_GGrade = GGrade;
	_HGrade = 0;
}

Location AlgoNode::getLocation() {
	return _currentPosition;
}

int AlgoNode::getHGrade(){
	return _HGrade;
}

int AlgoNode::getGGrade(){
	return _GGrade;
}

int AlgoNode::getGrade(){
	return _GGrade + _HGrade;
}

void AlgoNode::reGenerateGrade(Location end) {
	_HGrade = calcHGrade(end);
}

int AlgoNode::calcHGrade(Location end){
	if (end.getY() == _currentPosition.getY())
		return abs(end.getX() - _currentPosition.getX()) * DIRECT_MOV_SCORE;
	else if (end.getX() == _currentPosition.getX())
		return abs(end.getY() - _currentPosition.getY()) * DIRECT_MOV_SCORE;
	else {
		int tempX = _currentPosition.getX() + (end.getX() > _currentPosition.getX())?1:-1;
		int tempY = _currentPosition.getY() + (end.getY() > _currentPosition.getX())?1:-1;
	     return (calcHGrade(Location(tempX,tempY)) + DIAGONAL_MOV_SCORE);
	}

}

bool operator<(AlgoNode & a, AlgoNode & b) {
	if(a.getGrade() == b.getHGrade())
		return (a.getHGrade() < b.getHGrade())?true:false;
	else {
		return (a.getGrade() < b.getGrade())?true:false;
	}
}

AlgoNode::~AlgoNode() {
	// TODO Auto-generated destructor stub
}

} /* namespace MNProj */
