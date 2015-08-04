/*
 * LocalizationManager.cpp
 *
 *  Created on: Jun 27, 2015
 *      Author: colman
 */

#include "LocalizationManager.h"


/**
 * Constructor of ParticleManager. Create firsts particles
 */
LocalizationManager::LocalizationManager(Map* gridMap, double yawRobot) {
	grid = gridMap;


	Location* startedPos = new Location(ConfigManager::Instance()->getStartX(),
										ConfigManager::Instance()->getStartY());
	startedPos = grid->RealToRobotWorldLocation(*startedPos);
	Particle* robotParticle = new Particle(startedPos->getX(),
										   startedPos->getY(),
										   ConfigManager::Instance()->getStartYaw());

	for (int particleIndex = 0; particleIndex < PARTICLE_NUM -1; particleIndex++) {
		Particle* newParticle = new Particle(
				(rand() % 10 + 1) + grid->getWidth() / 2,
				(rand() % 10 + 1) + grid->getHeight()/ 2, yawRobot);
		particles.push(newParticle);
	}

	particles.push(robotParticle);
}

/**
 * The function passing the all particles, update them, filtered and fill with childrens
 */
void LocalizationManager::updateAll(Location* delta, double yawDelta, std::vector<double>* laserScan, Location* nextLocation){
	Particle* tempParticle;
	priority_queue<Particle*> tempList;
	int particlesSize = particles.size();

	for(int i = 0; i<particlesSize; i++)
	{
		tempParticle = particles.top();
		tempParticle->Update(delta, yawDelta, laserScan, grid, nextLocation);
		tempList.push(tempParticle);
		particles.pop();
	}

	particles = tempList;
	tempList = priority_queue<Particle*>();

	// Check if this particle is reliability
	this->FilterParticles();

	FillParticlesWithNewMutations();
}

/**
 * The function filtered the particles to be the top ten
 */
void LocalizationManager::FilterParticles(){
	priority_queue<Particle*> tempList;

	for(int i = 0; i < 10; i++)
	{
		tempList.push(particles.top());
		particles.pop();
	}

	particles = tempList;
	tempList = priority_queue<Particle*>();
}

/**
 * The function return the Position from the particles with the highest belief
 */
Location* LocalizationManager::GetProbablyPosition(){
	return particles.top()->getPosition();
}

double LocalizationManager::GetProbablyYaw() {
	return particles.top()->getYaw();
}

/**
 * The function fill the particles with the "children" of the filtered
 */
void LocalizationManager::FillParticlesWithNewMutations(){
	int initialSize = particles.size();
	priority_queue<Particle*> tempList;

	for(int i = 0; i< initialSize; i++ )
	{
		Particle* current = particles.top();
		vector<Location*> neighbours =  grid->getNeighbours(current->getPosition());

		for(int i =0; i < neighbours.size(); i++)
		{
			Location* neighbour = neighbours[i];
			Particle* newParticle = new Particle(neighbour->getX(), neighbour->getY(), current->getYaw());
			tempList.push(newParticle);
		}

		tempList.push(current);
		particles.pop();

	}

	particles = tempList;
	tempList = priority_queue<Particle*>();
}

bool LocalizationManager::isGoodNeighbour(Location* neighbourLoc){
	int neighbourUpXIndex = neighbourLoc->getX() -1;
	int neighbourDownXIndex = neighbourLoc->getX() +1;
	int neighbourRightYIndex = neighbourLoc->getY() +1;
	int neighbourLeftYIndex = neighbourLoc->getY() -1;

	Grid* robotgrid = grid->getRobotWorldGrid();

	if(neighbourUpXIndex >= 0){
		if(robotgrid->getCellState(neighbourUpXIndex,neighbourLoc->getY()) == grid->OCCUPIED_CELL)
			return false;
	}
	if(neighbourDownXIndex < grid->getHeight()){
		if(robotgrid->getCellState(neighbourDownXIndex, neighbourLoc->getY()) == grid->OCCUPIED_CELL)
			return false;
	}
	if(neighbourLeftYIndex >=0){
		if(robotgrid->getCellState(neighbourLoc->getX(), neighbourLeftYIndex) == grid->OCCUPIED_CELL)
			return false;
	}
	if(neighbourRightYIndex < grid->getWidth()){
		if(robotgrid->getCellState(neighbourLoc->getX(), neighbourRightYIndex) == grid->OCCUPIED_CELL)
			return false;
	}

	return true;
}

LocalizationManager::~LocalizationManager() {}
