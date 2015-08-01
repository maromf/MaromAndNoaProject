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
#include "Map.h"
using namespace PlayerCc;
using namespace std;

class Robot {
	private:
		PlayerClient _pc;
		Position2dProxy _pp;
		LaserProxy _lp;
		Location* _position;
		double _lastYaw;
		double _robotRatio;
		Map* _map;

		double fitYaw(double yaw);
		Location* fitLocation(int x, int y);

		double getX();
		double getY();

		Location* setLocationRatio(double x, double y);

		double reversFromRobotRatio(int pos);



	public:
		Robot(string ip, int port);
		virtual ~Robot();

		bool configRobot(Map* map, Location* start, double startYaw);
		void setSpeed(float linear, float angular);
		double getYaw();
		void invokeRead();
		bool isAt(Location* point, double delta);
		Location* getCurrentLocation();
		double getLaserDistance(int index);
		void setRatio(double ratio);

		void setYaw(double yaw);

		void setLocation(Location* location);

		void setOdometry(Location* location, double yaw);

		Location* getOdometryLocation();
		double getOdometryYaw();

		std::vector<double>* getLaserScan();
		int deg_to_index(double deg);
};


#endif /* ROBOT_H_ */
