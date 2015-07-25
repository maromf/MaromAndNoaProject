/*
 * AlgoNode.cpp
 *
 *  Created on: Jul 16, 2015
 *      Author: colman
 */

#include "AlgoNode.h"



AlgoNode::AlgoNode(Location* position, int GGrade) {
	_currentPosition = position;
	_GGrade = GGrade;
	_HGrade = 0;
	_fatherNode = this;
}

Location* AlgoNode::getLocation() {
	return _currentPosition;
}

int AlgoNode::getHGrade(){
	return _HGrade;
}

void AlgoNode::setGGrade(int grade){
	_GGrade = grade;
}

int AlgoNode::getGGrade(){
	return _GGrade;
}

int AlgoNode::getGrade(){
	return _GGrade + _HGrade;
}

void AlgoNode::reGenerateGrade(Location* end) {
	_HGrade = calcFixingHGrade(end);
}

void AlgoNode::calcRecorsiveHGrade(Location* end){
	_HGrade = recorsiveHGrade(end);
}

int AlgoNode::recorsiveHGrade(Location* end) {
	if (end->getY() == _currentPosition->getY())
		return abs(end->getX() - _currentPosition->getX()) * DIRECT_MOV_SCORE;
	else if (end->getX() == _currentPosition->getX())
		return abs(end->getY() - _currentPosition->getY()) * DIRECT_MOV_SCORE;
	else {
		int tempX = _currentPosition->getX() + (end->getX() > _currentPosition->getX())?1:-1;
		int tempY = _currentPosition->getY() + (end->getY() > _currentPosition->getX())?1:-1;
		Location* temp = new Location(tempX,tempY);
	    return (recorsiveHGrade(temp) + DIAGONAL_MOV_SCORE);
	}
}

int AlgoNode::calcFixingHGrade(Location* end){
	int deltaY = abs(end->getY() - _currentPosition->getY());
	int deltaX = abs(end->getX() - _currentPosition->getX());

	int diractFactor = 0;
	int diagonalFactor = 0;;

	if (end->getY() == _currentPosition->getY())
		diractFactor = deltaX;
	else if (end->getX() == _currentPosition->getX())
		diractFactor = deltaY;
	else if(deltaY == deltaX){
		diagonalFactor = deltaX;
	} else {
		int diractFactor = abs(deltaY - deltaX);
		int diagonalFactor = (deltaY < deltaX)?deltaY:deltaX;
	}

	return ((diractFactor * DIRECT_MOV_SCORE) + (diagonalFactor * DIAGONAL_MOV_SCORE));
}


void AlgoNode::calcSquaredHGrade(Location* end){
   _HGrade = (squaredDistance(end));
}

int AlgoNode::squaredDistance(Location* location) {
	double x = abs(_currentPosition->getX() - location->getX());
	double y = abs(_currentPosition->getY() - location->getY());

	return (pow(x, 2) + pow(y,2));
}

AlgoNode* AlgoNode::getFatherNode() {
	return _fatherNode;
}

void AlgoNode::setFatherNode(AlgoNode* node) {
	_fatherNode = node;
}


bool AlgoNode::operator< (AlgoNode* a) const {
	if((_HGrade + _GGrade) == a->getGrade())
		return (_HGrade < a->getHGrade())?true:false;
	else {
		return ((_HGrade + _GGrade) < a->getGrade())?true:false;
	}
}

AlgoNode::~AlgoNode() {
	// TODO Auto-generated destructor stub
}

