/*
 * Utils.h
 *
 *  Created on: Jul 25, 2015
 *      Author: colman
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <cmath>
#include  <math.h>
#include "Framework/Location.h"

using namespace std;

class Utils {
public:
	enum Quarter {FIRST = 1, SECOND, THIRD, FOURTH};

	static const double TOTAL_SCAN_SPAN = 666;
	static const double TOTAL_DEGREES = 240;
	static const double PAI_DEGREES = 180;
	static const double COMPROMISED_YAW = 1.5;
	static const double LASER_MAX_DETECTION_RANGE = 4.095;
	static const double COMPROMISED_DISTANCE = 1.2;
	static const double MINIMUM_DISTANCE_FROM_WALL = 0.5;
	static const double YAW_TURN_DELTA = 0.16;
	static const double MOVEMENT_DELTA = 0.4;
	static const double WAY_POINT_CONCER_DELTA = 1;
	static const double METER_TO_CM = 1000;

	static int indexToDegrees(int index);
	static int degreesToIndex(int degrees);
	static double degreesToRadians(double degrees);
	static double radiansToDegrees(double radians);
	static double calcYaw(Location* curPos, Location* goal);
	static double calculateNeededYaw(Location* curPos, Location* goal);
	static int getQuarter(Location* pos, Location* goal);
	static double NegativeYawToPositive(double negative);
	static double PositiveYawToNegative(double positive);
	static Location* NegativeCoordinateLocationToPositive(Location* negative, int width, int height);
	static Location* PositiveCoordinateLocationToNegative(Location* positive, int width, int height);
};

#endif /* UTILS_H_ */
