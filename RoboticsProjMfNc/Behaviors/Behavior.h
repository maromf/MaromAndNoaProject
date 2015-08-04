/**
 * Behavior.h
 *
 *  Purpose: representing the Behavior of the robot on filed ( movment and turn).

 *  Created on: Jul 24, 2015
 *  @author:    MaromF NoaC
 *  @version:   1.0
 */

#ifndef BEHAVIOR_H_
#define BEHAVIOR_H_

#include "../Robot.h"
#include <vector>
#include "../Framework/Location.h"
#include "../Utils.h"
using namespace std;

class Behavior {
private:
	vector<Behavior *> _nextBehaviors;

protected:
	Robot *_robot;

public:
	virtual bool startCond() = 0;
	virtual bool stopCond() = 0;
	virtual void action() = 0;

	Behavior *addNext(Behavior *beh);
	Behavior *selectNext();

	Behavior(Robot *robot);
	virtual ~Behavior();
};

#endif
