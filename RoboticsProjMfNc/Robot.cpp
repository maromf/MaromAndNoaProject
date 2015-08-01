/*
 * Robot.cpp
 *
 *  Created on: May 26, 2015
 *      Author: colman
 */

#include "Robot.h"
	Robot::Robot(string ip, int port) : _pc(ip, port), _pp(&_pc), _lp(&_pc) {
		// TODO Auto-generated constructor stub
		_pp.SetMotorEnable(true);
		_lastYaw = 0;
		_position = 0;
		_robotRatio = 1;
		_map = 0;
	}

	bool Robot::configRobot(Map* map, Location* start, double startYaw) {

		_map = map;

		double roboWorldResulotion = ConfigManager::Instance()->getGridResulotionCM();
		setRatio(roboWorldResulotion);

		// Fix reading BUG
		for(int i = 0; i < 15; i++) {
			setOdometry(start, startYaw);
			invokeRead();
		}

		_lastYaw = fitYaw(_pp.GetYaw());
		_position = fitLocation(_pp.GetXPos(),_pp.GetYPos());

		return true;
	}

	Robot::~Robot() {
		// TODO Auto-generated destructor stub
	}

	void Robot::setSpeed(float linear, float angular)
	{
		_pp.SetSpeed(linear, angular);
	}

	void Robot::setYaw(double yaw) {
		_lastYaw = yaw;
	}

	void Robot::setLocation(Location* location) {
		_position = location;
	}

	double Robot::getX()
	{
		return _pp.GetXPos();
	}

	double Robot::getY()
	{
		return _pp.GetYPos();
	}

	double Robot::getYaw()
	{
		return _lastYaw;
	}

	double Robot::fitYaw(double yaw) {
		double tempYaw = yaw;
		return Utils::NegativeYawToPositive(Utils::radiansToDegrees(tempYaw));
	}

	Location* Robot::getCurrentLocation()
	{
		return _position;
	}


	Location* Robot::fitLocation(int x, int y)
	{
		Location* cur;
		cur = setLocationRatio(x, y);
		cur = Utils::NegativeCoordinateLocationToPositive(cur,_map->getWidth(), _map->getHeight());
		return cur;
	}

	void Robot::setRatio(double ratio) {
		_robotRatio = ratio;
	}

	void Robot::setOdometry(Location* location, double yaw) {
		_position = location;
		_lastYaw = yaw;

		double robotYaw = Utils::PositiveYawToNegative(yaw);

		invokeRead();

		Location* odoLocation = Utils::PositiveCoordinateLocationToNegative(location,_map->getWidth(), _map->getHeight());
		double newX = reversFromRobotRatio(odoLocation->getX());
		double newY = reversFromRobotRatio(odoLocation->getY());
		_pp.SetOdometry(newX, newY, Utils::degreesToRadians(robotYaw));
	}

	Location* Robot::getOdometryLocation() {
		return fitLocation(getX(), getY());
	}

	double Robot::getOdometryYaw() {
		return fitYaw(_pp.GetYaw());
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

