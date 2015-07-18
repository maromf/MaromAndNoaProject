/*
 * Particle.cpp
 *
 *  Created on: Jun 27, 2015
 *      Author: colman
 */

#include "Particle.h"


Particle::Particle(double xPos, double yPos, double yaw) {
	_belief = 0;
	_yaw = 0;
	_xPos = 0;
	_yPos = 0;
}

Particle::~Particle() {
	// TODO Auto-generated destructor stub
}

