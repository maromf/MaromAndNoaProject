/*
 * Utils.cpp
 *
 *  Created on: Jul 25, 2015
 *      Author: colman
 */

#include "Utils.h"

int Utils::degreesToIndex(int degrees)
{
	return degrees * (TOTAL_SCAN_SPAN / TOTAL_DEGREES);
}

int Utils::indexToDegrees(int index)
{
	return index * (TOTAL_DEGREES / TOTAL_SCAN_SPAN);
}

double Utils::degreesToRadians(double degrees)
{
	double yaw = degrees;

	return (yaw * M_PI) / 180;
}

double Utils::radiansToDegrees(double radians)
{
	double yaw = (radians * 180) / M_PI;

	return yaw;
}

double Utils::calcYaw(Location* curPos, Location* goal)
{
	double dx = curPos->getX() - goal->getX();
	double dy = curPos->getY() - goal->getY();
	return radiansToDegrees(atan2(dx, dy));
}
