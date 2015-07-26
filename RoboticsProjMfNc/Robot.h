/*
 * Robot.h
 *
 *  Created on: May 26, 2015
 *      Author: colman
 */

#ifndef ROBOT_H_
#define ROBOT_H_

#include <libplayerc++/playerc++.h>
#include <string>
#include <vector>
#include "Framework/Location.h"
#include "Utils.h"
using namespace PlayerCc;
using namespace std;

class Robot {
	private:
		PlayerClient _pc;
		Position2dProxy _pp;
		LaserProxy _lp;
		Location* _position;
		float _lastX, _lastY, _lastYaw;

		void configRobot();

	public:
		Robot(string ip, int port);
		virtual ~Robot();

		void setSpeed(float linear, float angular);
		float getX();
		float getY();
		float getYaw();
		void invokeRead();
		bool isAt(Location* point, double delta);
		Location* getCurrentLocation();
		double getLaserDistance(int index);

		std::vector<double>* getLaserScan();
		int deg_to_index(double deg);
};


#endif /* ROBOT_H_ */
