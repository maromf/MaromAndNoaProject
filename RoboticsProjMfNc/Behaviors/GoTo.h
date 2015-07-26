/*
 * GoTo.h
 *
 *  Created on: Jul 26, 2015
 *      Author: colman
 */

#ifndef GOTO_H_
#define GOTO_H_

#include "Behavior.h"
#include "../LocalizationModel/LocalizationManager.h"

class GoTo: public Behavior {
private:
	LocalizationManager* _localManager;
	Location* _goal;
	double _yaw;

public:
	GoTo(Robot* robot, LocalizationManager* localManager, Location* goal);
	virtual ~GoTo();

	virtual bool startCond();
	virtual bool stopCond();
	virtual void action();
};

#endif /* GOTO_H_ */
