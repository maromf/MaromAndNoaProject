/*
 * Utils.cpp
 *
 *  Created on: Jul 25, 2015
 *      Author: colman
 */

#include "Utils.h"

/**
 * Calculates degrees to grid index
 */
int Utils::degreesToIndex(int degrees)
{
	return degrees * (TOTAL_SCAN_SPAN / TOTAL_DEGREES);
}

/**
 * Calculates grid index to degrees
 */
int Utils::indexToDegrees(int index)
{
	return index * (TOTAL_DEGREES / TOTAL_SCAN_SPAN);
}

/**
 * calculates degrees to radians
 */
double Utils::degreesToRadians(double degrees)
{
	double yaw = degrees;

	return (yaw * M_PI) / PAI_DEGREES;
}

/**
 * calculates radians to degrees
 */
double Utils::radiansToDegrees(double radians)
{
	double yaw = (radians * PAI_DEGREES) / M_PI;

	return yaw;
}

/**
 * calculates yaw between two locations
 * @param curPos - first location
 * @param goal - second location
 * @return yaw
 */
double Utils::calcYaw(Location* curPos, Location* goal)
{
	double angleInDegrees = calculateNeededYaw(curPos, goal);
	return angleInDegrees;
}

/**
 * calculates yaw according to quarter- yaw always positive
 */
double Utils::calculateNeededYaw(Location* curPos, Location* goal)
{
	double yDeltaToPoint = abs(goal->getY() - curPos->getY());
	double xDeltaToPoint = abs(goal->getX() - curPos->getX());

	double neededYaw = atan2(yDeltaToPoint , xDeltaToPoint);
	neededYaw = (neededYaw < 0) ? ( ((M_PI * 2) + neededYaw)) : neededYaw;
	neededYaw = radiansToDegrees(neededYaw);

	// check the quarter of the goal point
	switch(getQuarter(curPos, goal)) {
		case FIRST:
			return neededYaw;
		case SECOND:
			return PAI_DEGREES - neededYaw;
		case THIRD:
			return PAI_DEGREES + neededYaw;
		case FOURTH:
			return (PAI_DEGREES * 2) - neededYaw;
		default:
			return neededYaw;
    }

}

/**
 * get quarter of the goal point
 */
int Utils::getQuarter(Location* pos, Location* goal) {
	if (pos->getY() > goal->getY()) {
		if (pos->getX() > goal->getX())
			return SECOND;
		else
			return FIRST;
	} else {
		if (pos->getX() > goal->getX())
			return THIRD;
		else
			return FOURTH;
	}
}

/**
 * turn yaw to positive
 * @return positive yaw
 */
double Utils::NegativeYawToPositive(double negative)
{
	return (negative < 0) ? ( ((PAI_DEGREES * 2) + negative)) : negative;
}

/**
 * turn yaw to negative
 * @return negative yaw
 */
double Utils::PositiveYawToNegative(double positive)
{
	return (positive > PAI_DEGREES) ? ((-1) * ((PAI_DEGREES * 2) - positive)) : positive;
}

/**
 * turn negative location to positive
 * @return positive location
 */
Location* Utils::NegativeCoordinateLocationToPositive(Location* negative, int width, int height)
{
	double posX = negative->getX() + floor(width / 2);
	double posY = (-1) * (negative->getY() - floor(height / 2));
	return new Location(posX, posY);
}

/**
 * turn positive location to negative
 * @return negative location
 */
Location* Utils::PositiveCoordinateLocationToNegative(Location* positive, int width, int height)
{
	double posX = positive->getX() - (width / 2);
	double posY = (-1) * (positive->getY() - (height / 2));
	return new Location(posX, posY);
}
