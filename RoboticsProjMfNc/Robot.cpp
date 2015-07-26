/*
 * Robot.cpp
 *
 *  Created on: May 26, 2015
 *      Author: colman
 */

#include "Robot.h"
	Robot::Robot(string ip, int port) : _pc(ip, port), _pp(&_pc), _lp(&_pc) {
		// TODO Auto-generated constructor stub
		_lastX = _pp.GetXPos();
		_lastY = _pp.GetYPos();
		_lastYaw = _pp.GetYaw();
		_position = new Location(_pp.GetXPos(),_pp.GetYPos());

		configRobot();
	}

	void Robot::configRobot() {

		_pp.SetMotorEnable(true);

		// Fix reading BUG
		for(int i = 0; i < 15; i++)
			invokeRead();
	}

	Robot::~Robot() {
		// TODO Auto-generated destructor stub
	}

	void Robot::setSpeed(float linear, float angular)
	{
		_pp.SetSpeed(linear, angular);
	}

	float Robot::getX()
	{
		return _position->getX();
	}

	float Robot::getY()
	{
		return _position->getY();
	}

	float Robot::getYaw()
	{
		return Utils::NegativeYawToPositive(_pp.GetYaw());
	}

	Location* Robot::getCurrentLocation()
	{
		Location* cur = new Location(getX(), getY());
		return cur;
	}

	std::vector<double>* Robot::getLaserScan()
	{
		std::vector<double>* scan = new std::vector<double>(_lp.GetCount());
		for (unsigned int i = 0; i < _lp.GetCount(); i++)
		{
			scan->push_back(_lp[i]);
		}
		return scan;
	}

	void Robot::invokeRead(){
	 for (int i = 0; i < 2; i++)
			_pc.Read();

	}

	bool Robot::isAt(Location* point, double delta) {
		return (_position->getDistance(point) <= delta);
	}

	double Robot::getLaserDistance(int index) {
		return _lp.GetRange(index);
	}

	int Robot::deg_to_index(double deg)
	{
		return (deg + 120) / 0.36;
	}

