/*
 * Particle.h
 *
 *  Created on: Jun 27, 2015
 *      Author: colman
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_


class Particle {
private:
	double _xPos, _yPos, _yaw;
	double _bel;
public:
	Particle(double xPos, double yPos, double yaw);
	//double getBelief();
	//void update(double deltaX, double deltaY, double deltaYaw);
	//void printPosition();
	virtual ~Particle();
};


#endif /* PARTICLE_H_ */
