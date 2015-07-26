/*
 * GoTo.h
 *
 *  Created on: Jul 26, 2015
 *      Author: colman
 */

#ifndef GOTO_H_
#define GOTO_H_

#include "Behavior.h"

class GoTo: public Behavior {
private:
	Location* _goal;

public:
	GoTo(Robot* robot, Location* goal);
	virtual ~GoTo();

	virtual bool startCond();
	virtual bool stopCond();
	virtual void action();
};

#endif /* GOTO_H_ */
