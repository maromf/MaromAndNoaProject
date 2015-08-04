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
#include <algorithm>
#include <queue>

using namespace std;

class LocalizationManager {
private:
	static const int PARTICLE_NUM = 50;
	static const float BELIEF_THRESHOLD = 0.4;
	priority_queue<Particle*> particles;
	void deleteUnreliableParticles(double minBelife);
	bool isGoodNeighbour(Location* neighbourLoc);
	Map* grid;
	void FilterParticles();

public:
	LocalizationManager(Map* gridMap, double yawRobot);
	void updateAll(Location* delta, double yawDelta, double* laserScan, Location* nextLocation);
	void FillParticlesWithNewMutations();
	Location* GetProbablyPosition();
	virtual ~LocalizationManager();
};


#endif /* LOCALIZATIONMANAGER_H_ */
