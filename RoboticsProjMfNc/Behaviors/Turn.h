/**
 * Turn.h
 *
 *  Purpose: representing the Behavior of turning in place.

 *  Created on: Jul 24, 2015
 *  @author:    MaromF NoaC
 *  @version:   1.0
 */

#ifndef TURN_H_
#define TURN_H_

#include "Behavior.h"
#include "../Robot.h"
#include <cmath>
#include  <math.h>

class Turn : public Behavior {
private:
	double _yaw;  // the needed angle to reach
public:
	Turn(Robot * robot, double yaw);

	void setYaw(double yaw);

	/**
	    Determines if the Behavior can start operating.
	*/
	virtual bool startCond();

	/**
	    Determines if the Behavior needs to stop.
	*/
	virtual bool stopCond();

	/**
	    Operating the turn.
	*/
	virtual void action();

	/**
	    Determines if the robot reached the needed angle.
	*/
	bool inPosition();
};

#endif /* TURN_H_ */
