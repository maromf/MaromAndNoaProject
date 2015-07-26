/*
 * Particle.cpp
 *
 *  Created on: Jun 27, 2015
 *      Author: colman
 */

#include "Particle.h"


Particle::Particle(double xPos, double yPos, double yaw, Map* map) {
	_bel = 0;
	_yaw = 0;
	_xPos = 0;
	_yPos = 0;
	_map = map;
}

double Particle::getBelief() {
   return _bel;
}

void Particle::update(double deltaX, double deltaY, double deltaYaw, std::vector<double> laserArr) {
	_xPos += deltaX;
	_yPos += deltaY;
	_yaw += deltaYaw;

   // _predBel = _bel * predByMov(deltaX,deltaY,deltaYaw);
  // _bel = normalVal * predBel * ProbByMesu(laserArr);
}

double Particle::ProbByMesu(std::vector<double> laserScan) {
	int expectedObsticlesDetected = 0;

	for (unsigned int laserDegree = 0; laserDegree < laserScan.size(); laserDegree += 4) {
		double currentLaserScan = laserScan[laserDegree];

	//	if (isObsticleDetectedAsExpected(currentLaserScan, laserDegree))
	//		expectedObsticlesDetected++;
	}

	return expectedObsticlesDetected / (laserScan.size() / 4);
}

Particle::~Particle() {
	// TODO Auto-generated destructor stub
}


