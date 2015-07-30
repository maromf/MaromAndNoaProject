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
		_robotRatio = 1;
		_map = 0;
	}

	bool Robot::configRobot(Map* map) {

		_map = map;

		_pp.SetMotorEnable(true);

		double roboWorldResulotion = ConfigManager::Instance()->getGridResulotionCM();
		setRatio(roboWorldResulotion);

		// Fix reading BUG
		for(int i = 0; i < 15; i++)
			invokeRead();

		return true;
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

	void Robot::setRatio(double ratio) {
		_robotRatio = ratio;
	}

	void Robot::setOdometry(Location* location, double yaw) {
		_position = location;

		double robotYaw = Utils::PositiveYawToNegative(yaw);

		invokeRead();

		Location* odoLocation = Utils::PositiveCoordinateLocationToNegative(location,_map->getWidth(), _map->getHeight());
		double newX = reversFromRobotRatio(odoLocation->getX());
		double newY = reversFromRobotRatio(odoLocation->getY());
		_pp.SetOdometry(newX, newY, Utils::degreesToRadians(robotYaw));
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
		Location* location;
		location = setLocationRatio(_pp.GetXPos(), _pp.GetYPos());
		location = Utils::NegativeCoordinateLocationToPositive(location,_map->getWidth(), _map->getHeight());
		return (location->getDistance(point) <= delta);
	}

	Location* Robot::setLocationRatio(double x, double y) {
		double newX = (x * Utils::METER_TO_CM) / (_robotRatio * 10);
		double newY = (y * Utils::METER_TO_CM) / (_robotRatio * 10);
		Location* location = new Location(newX, newY);
		return location;
	}

	double Robot::reversFromRobotRatio(int pos) {
		double newPos = (pos / 10);
		return newPos;
	}

	double Robot::getLaserDistance(int index) {
		return _lp.GetRange(index);
	}

	int Robot::deg_to_index(double deg)
	{
		return (deg + 120) / 0.36;
	}

