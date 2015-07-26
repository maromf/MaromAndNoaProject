/*
 * Utils.h
 *
 *  Created on: Jul 25, 2015
 *      Author: colman
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <cmath>

using namespace std;

class Utils {
public:
	static const double TOTAL_SCAN_SPAN = 666;
	static const double TOTAL_DEGREES = 240;
	static const double COMPROMISED_YAW = 2;
	static const double LASER_MAX_DETECTION_RANGE = 4.095;
	static const double COMPROMISED_DISTANCE = 9;
	static const double MINIMUM_DISTANCE_FROM_WALL = 0.5;
	static const double YAW_TURN_DELTA = 0.16;
	static const double MOVEMENT_DELTA = 0.4;
	static const double WAY_POINT_CONCER_DELTA = 9;

	static int indexToDegrees(int index);
	static int degreesToIndex(int degrees);
	static double degreesToRadians(double degrees);
	static double radiansToDegrees(double radians);
};

#endif /* UTILS_H_ */
