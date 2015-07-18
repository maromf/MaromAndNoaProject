/*
 * LocalizationManager.h
 *
 *  Created on: Jun 27, 2015
 *      Author: colman
 */

#ifndef LOCALIZATIONMANAGER_H_
#define LOCALIZATIONMANAGER_H_

#include "Particle.h"
#include <vector>
using namespace std;


class LocalizationManager {
private:
    vector<Particle*> _particles;

public:
	LocalizationManager();
	void update(double deltaX, double deltaY, double deltaYaw);
	void resampleParticles();
	Particle *getBestParticle();

	virtual ~LocalizationManager();
};


#endif /* LOCALIZATIONMANAGER_H_ */
