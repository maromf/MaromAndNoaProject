/**
 * MoveForward.h
 *
 *  Purpose: representing the Behavior of moving forward.

 *  Created on: Jul 24, 2015
 *  @author:    MaromF NoaC
 *  @version:   1.0
 */

#ifndef MOVEFORWARD_H_
#define MOVEFORWARD_H_

#include "Behavior.h"
#include <vector>

using namespace std;

class MoveForward : public Behavior {
	private:
		Location* _goal; // The goal point to reach.
		double _lastD;   // The previous distance from goal.

		/**
		 * Determines if there is an obstacle ahead.
		 */
		bool checkObstacles();

		/**
		 * Determines if the robot reached the goal location.
		 */
		bool atGoalLocation();

		/**
		 * Determines if the distance from goal is bigger then the previous.
		 */
		bool checkIfDistanceIncrees();

	public:
		MoveForward(Robot *robot, Location *goal); // Ctor
		virtual ~MoveForward();                    // Dtor

		/**
		    Determines if the Behavior can start operating.
		*/
		virtual bool startCond();

		/**
		    Determines if the Behavior needs to stop.
		*/
		virtual bool stopCond();

		/**
		    Operating the move forward.
		*/
		virtual void action();
	};


#endif /* MOVEFORWARD_H_ */
