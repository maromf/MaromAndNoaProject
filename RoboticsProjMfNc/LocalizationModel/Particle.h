/*
 * Particle.h
 *
 *  Created on: Jun 27, 2015
 *      Author: colman
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_

#include <cmath>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "../Framework/Location.h"
#include "../Map.h"
#include "../Robot.h"
#include "../ConfigManager.h"
//#include "../Utils/AngleHelper.h"

using namespace std;

class Particle {
private:
	static const double NRMALIZATION = 1.5;
	Location* position;
	double belief;
	double yaw;
	double probByMov(Location* position, double yawDelta);
	double prodByScan(Location* delta, std::vector<double>* laser, Map* grid);
	static const float MAX_DISTANCE = 100;
	static const float MAX_YAW = 8;

public:
	Particle();
	Particle(double x, double y, double yaw);
	void setPositionDelta(Location* nextLocation, Location* delta, double yawDelta);
	void Update(Location* position, double yawDelta, std::vector<double>* laser, Map* grid, Location* nextLocation);
	double getBelief();
	Location* getPosition();
	double getYaw();
	double modDouble(double first, double second);
	virtual ~Particle();

	static double getXDelta(double degree, double distance);
	static double getYDelta(double degree, double distance);
	static double indexToRadians(int index);

	virtual bool operator<(const Particle& secondParticle) const;
};


#endif /* PARTICLE_H_ */


