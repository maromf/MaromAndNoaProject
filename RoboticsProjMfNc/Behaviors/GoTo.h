/*
 * GoTo.h
 *
 *  Created on: Jul 26, 2015
 *      Author: colman
 */

#ifndef GOTO_H_
#define GOTO_H_

#include "../LocalizationModel/LocalizationManager.h"
#include "MoveForward.h"
#include "Turn.h"

class GoTo: public Behavior {
private:
	LocalizationManager* _localManager;
	Location* _goal;
	double _yaw;

	MoveForward* _moveForward;
	Turn* _turn;

public:
	GoTo(Robot* robot, LocalizationManager* localManager, Location* goal);
	virtual ~GoTo();

	virtual bool startCond();
	virtual bool stopCond();
	virtual void action();

	void initializeBehaviors();
	bool atGoalLocation();
};

#endif /* GOTO_H_ */
