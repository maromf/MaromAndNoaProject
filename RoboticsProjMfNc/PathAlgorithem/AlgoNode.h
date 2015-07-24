/*
 * AlgoNode.h
 *
 *  Created on: Jul 16, 2015
 *      Author: colman
 */

#ifndef ALGONODE_H_
#define ALGONODE_H_

#include "../Framework/Location.h"
#include <stdlib.h>
#include <cmath>

class AlgoNode {
	static const int DIRECT_MOV_SCORE = 10;
	static const int DIAGONAL_MOV_SCORE = 14;
public:
	AlgoNode(Location* position, int GGrade);

	Location* getLocation();
	int getGrade();
	int getHGrade();
	int getGGrade();
	void setGGrade(int grade);
	void reGenerateGrade(Location* end);
	void calcRecorsiveHGrade(Location* end);
	void calcSquaredHGrade(Location* end);
	void calcFixingHGrade(Location* end);
	AlgoNode* getFatherNode();
	void setFatherNode(AlgoNode* node);
	bool operator< (AlgoNode* a) const;
	virtual ~AlgoNode();

private:
	Location* _currentPosition;
	int _GGrade;
	int _HGrade;
	AlgoNode* _fatherNode;

	int recorsiveHGrade(Location* end);
	int squaredDistance(Location* location);
};


#endif /* ALGONODE_H_ */
