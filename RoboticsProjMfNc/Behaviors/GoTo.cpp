/*
 * GoTo.cpp
 *
 *  Created on: Jul 26, 2015
 *      Author: colman
 */

#include "GoTo.h"

GoTo::GoTo(Robot* robot, Location* goal) : Behavior(robot){
	_goal = goal;

}

GoTo::~GoTo() {
	// TODO Auto-generated destructor stub
}

