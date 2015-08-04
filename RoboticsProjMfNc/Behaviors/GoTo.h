/**
 * GoTo.h
 *
 *  Purpose: representing the Behavior of going to point,
 *  use the turn behavior and the move forward for getting to point.

 *  Created on: Jul 24, 2015
 *  @author:    MaromF NoaC
 *  @version:   1.0
 */

#ifndef GOTO_H_
#define GOTO_H_

#include "../LocalizationModel/LocalizationManager.h"
#include "MoveForward.h"
#include "Turn.h"

class GoTo: public Behavior {
private:
	LocalizationManager* _localManager; // LocalizationManager
	Location* _goal;                    // The goal point
	double _yaw;                        // The angel to the goal point

	MoveForward* _moveForward;
	Turn* _turn;

public:
	GoTo(Robot* robot, LocalizationManager* localManager, Location* goal); // Ctor
	virtual ~GoTo();

	/**
	    Returns the X coordinate.

	    @return The X coordinate (int).
	*/
	virtual bool startCond();
	virtual bool stopCond();
	virtual void action();

	void initializeBehaviors();
	bool atGoalLocation();
};

#endif /* GOTO_H_ */
