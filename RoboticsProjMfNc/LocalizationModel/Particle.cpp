/*
 * Particle.cpp
 *
 *  Created on: Jun 27, 2015
 *      Author: colman
 */

#include "Particle.h"

#define READINGS_NUM 682
#define LASER_RANGE 4


/**
 * Constructor of Particle. Get the x, y and yaw. set start belief to 1
 */
Particle::Particle(double x, double y, double yaw)
{
	this->position = new Location(x, y);
	this->yaw = yaw;
	this->belief = 1.0;
}

/**
 * The function calculate the probability according to delta
 */
double Particle::probByMov(Location* delta, double yawDelta){
	double distance = sqrt(pow(delta->getX(), 2) + pow(delta->getY(), 2));
	float yawProbability = abs(yawDelta);

	float propability = 0.25;

	if (distance <= MAX_DISTANCE)
		propability += 0.25;
	if (yawProbability <= MAX_YAW)
		propability += 0.25;
	if (yawProbability == 0)
		propability += 0.25;

	return propability;
}

/*
 *  The function calculate the probability according to laser scans
 */
double Particle::prodByScan(Location* delta, std::vector<double>* laser, Map* grid)
{
	double gridres = ConfigManager::Instance()->getGridResulotionCM();
	float distance = sqrt(pow(delta->getX() * gridres, 2) + pow(delta->getY() * gridres, 2));
	int errors = 0;

	for (int i = 0; i < READINGS_NUM; i++) {
		double laserDistance = laser->at(i) * gridres;
		double laserInRadians = indexToRadians(i);
		int row = position->getX() + round(getXDelta(yaw + laserInRadians, laserDistance));
		int col = position->getY() + round(getYDelta(yaw + laserInRadians, laserDistance));

		if (row < 0 || col < 0 || row >= grid->getHeight() || col >= grid->getWidth()) {
			errors++;
			break;
		}

		int currentCellType = grid->getRobotWorldGrid()->getCellState(row, col);
		bool blocked = laserDistance < LASER_RANGE * gridres;
		int cellType = Map::FREE_CELL;
		if (blocked)
			cellType = Map::OCCUPIED_CELL;
		if (currentCellType != cellType) {
			errors++;
		}
	}

	double probability = (double)((double)errors / (double)READINGS_NUM);
	return (double)(1 - probability);
}

/**
 * The function calculate the the delta according the quarter of next location and set the position of the particle
 */
void Particle::setPositionDelta(Location* nextLocation, Location* delta, double yawDelta){
	int quarter = Utils::getQuarter(position, nextLocation);
	double finalDeltaX = delta->getX(), finalDeltaY = delta->getY();

	switch (quarter)
	{
		case Utils::SECOND:
		{
			finalDeltaX = -finalDeltaX;
			finalDeltaY = -finalDeltaY;
			break;
		}
		case Utils::THIRD:
		{
			finalDeltaY = -finalDeltaY;
			break;
		}
		case Utils::FIRST:
		{
			finalDeltaX = -finalDeltaX;
			break;
		}
	}

	position->setX(position->getX() + finalDeltaX);
	position->setY(position->getY() + finalDeltaY);
	yaw = yaw + modDouble(yawDelta, 360);
}

/**
 * The function update the current particle. set the belief and positionDelta
 */
void Particle::Update(Location* delta, double yawDelta, std::vector<double>* laser, Map* grid, Location* nextLocation)
{
	float predBel = probByMov(delta, yawDelta) * belief;
	belief = NRMALIZATION * prodByScan(delta,laser, grid) * predBel;
	setPositionDelta(nextLocation, delta, yawDelta);
}

/**
 * Operator < for compare between particles. Do according to belief
 */
bool Particle::operator<(const Particle& secondParticle) const{
	return (this->belief > secondParticle.belief);
}

/**
 * The function return the particle belief
 */
double Particle::getBelief(){
	return belief;
}

/**
 * The function return the position of particle
 */
Location* Particle::getPosition(){
	return position;
}

double Particle::getYaw()
{
	return yaw;
}

/**
 * The function do mod between doubles
 */
double Particle::modDouble(double first, double second){
	return first - ((int)first/second)*second;
}

double Particle::getXDelta(double degree, double distance)
{
	return cos(degree) * distance;
}

double Particle::getYDelta(double degree, double distance)
{
	return sin(degree) * distance;
}

double Particle::indexToRadians(int index)
{
		return ((index * 0.36 - 120) * M_PI) / 180;
}

Particle::~Particle() {}



