/*
 * Turn.h
 *
 *  Created on: Jul 25, 2015
 *      Author: colman
 */

#ifndef TURN_H_
#define TURN_H_

#include "Behavior.h"
#include "../Robot.h"

class Turn : Behavior {
private:
	float _yaw;
public:
	Turn(Robot * robot, float yaw);
	virtual ~Turn();

	virtual bool startCond();
	virtual bool stopCond();
	virtual void action();
};

#endif /* TURN_H_ */
