/*
 * MoveForward.h
 *
 *  Created on: May 26, 2015
 *      Author: colman
 */

#ifndef MOVEFORWARD_H_
#define MOVEFORWARD_H_

#include "Behavior.h"
#include <vector>

using namespace std;

class MoveForward : public Behavior {
	private:
		//bool checkObstacleInFront();
		Location* _goal;

		bool checkObstacles();
		bool atGoalLocation();

	public:
		MoveForward(Robot *robot, Location *goal);
		virtual ~MoveForward();

		virtual bool startCond();
		virtual bool stopCond();
		virtual void action();
	};


#endif /* MOVEFORWARD_H_ */
