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

	MoveForward* _moveForward;          // The move forward behavior
	Turn* _turn;                        // The turn behavior

public:
	GoTo(Robot* robot, LocalizationManager* localManager, Location* goal); // Ctor
	virtual ~GoTo();

	/**
	    Determines if the Behavior can start operating.
	*/
	virtual bool startCond();

	/**
	    Determines if the Behavior needs to stop.
	*/
	virtual bool stopCond();

	/**
	    Operating the turn and then the movement in order to get to the point..
	*/
	virtual void action();

	/**
	 * Initialize the behavior and the turn and move forward.
	 */
	void initializeBehaviors();

	/**
	    Determines if the reached the goal location.
	*/
	bool atGoalLocation();
};

#endif /* GOTO_H_ */
