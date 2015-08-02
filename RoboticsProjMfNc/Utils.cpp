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

	return (yaw * M_PI) / PAI_DEGREES;
}

double Utils::radiansToDegrees(double radians)
{
	double yaw = (radians * PAI_DEGREES) / M_PI;

	return yaw;
}

//double Utils::calcYaw(Location* curPos, Location* goal)
//{
//	double dx = curPos->getX() - goal->getX();
//	double dy = curPos->getY() - goal->getY();
//	double n = NegativeYawToPositive(radiansToDegrees(atan2(dx, dy)));
//	double nn = calculateNeededYaw(curPos, goal);
//	return nn;
//}

double Utils::calcYaw(Location* curPos, Location* goal)
{
	//double dx = goal->getX() - curPos->getX();
	//double dy = goal->getY() - curPos->getY();
	//double angleInDegrees = atan2(dy, dx) * 180 / M_PI;
	//double angleInDegrees = atan2(curPos->getY() - goal->getY(), curPos->getX() - goal->getX()) * 180 / M_PI;
	double angleInDegrees = calculateNeededYaw(curPos, goal);
	return angleInDegrees;
}

//double Utils::calculateNeededYaw(Location* curPos, Location* goal)
//{
//	double yDeltaToPoint = abs(goal->getY() - curPos->getY());
//	double distanceToPoint = curPos->getDistance(goal);
//	double neededYaw = acos(yDeltaToPoint / distanceToPoint);
//
//	switch(getQuarter(curPos, goal)) {
//		case FIRST:
//			return radiansToDegrees(M_PI_2 - neededYaw);
//		case SECOND:
//			return radiansToDegrees(M_PI - neededYaw);
//		case THIRD:
//			return radiansToDegrees(M_PI + M_PI_2 - neededYaw);
//		case FOURTH:
//			return radiansToDegrees(M_PI * 2 - neededYaw);
//		default:
//			return neededYaw;
 //  }
//}

double Utils::calculateNeededYaw(Location* curPos, Location* goal)
{
	double yDeltaToPoint = abs(goal->getY() - curPos->getY());
	double xDeltaToPoint = abs(goal->getX() - curPos->getX());
	//double distanceToPoint = curPos->getDistance(goal);
	//double neededYaw = acos(yDeltaToPoint / distanceToPoint);

	double neededYaw = atan2(yDeltaToPoint , xDeltaToPoint);
	neededYaw = (neededYaw < 0) ? ( ((M_PI * 2) + neededYaw)) : neededYaw;
	neededYaw = radiansToDegrees(neededYaw);

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

//int Utils::getQuarter(Location* pos, Location* goal) {
//	if (pos->getY() > goal->getY()) {
//		if (pos->getX() > goal->getX())
//			return SECOND;
//		else
//			return FIRST;
//	} else {
//		if (pos->getX() > goal->getX())
//			return THIRD;
//		else
//			return FOURTH;
//	}
//}

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

double Utils::NegativeYawToPositive(double negative)
{
	return (negative < 0) ? ( ((PAI_DEGREES * 2) + negative)) : negative;
}

double Utils::PositiveYawToNegative(double positive)
{
	return (positive > PAI_DEGREES) ? ((-1) * ((PAI_DEGREES * 2) - positive)) : positive;
}

Location* Utils::NegativeCoordinateLocationToPositive(Location* negative, int width, int height)
{
	double posX = negative->getX() + floor(width / 2);
	double posY = (-1) * (negative->getY() - floor(height / 2));
	return new Location(posX, posY);
}

Location* Utils::PositiveCoordinateLocationToNegative(Location* positive, int width, int height)
{
	double posX = positive->getX() - (width / 2);
	double posY = (-1) * (positive->getY() - (height / 2));
	return new Location(posX, posY);
}
