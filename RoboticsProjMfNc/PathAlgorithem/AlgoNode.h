/*
 * AlgoNode.h
 *
 *  Created on: Jul 16, 2015
 *      Author: colman
 */

#ifndef ALGONODE_H_
#define ALGONODE_H_

#include "../Framework/Location.h"
#include<stdlib.h>
namespace MNProj {

class AlgoNode {
	static const int DIRECT_MOV_SCORE = 10;
	static const int DIAGONAL_MOV_SCORE = 14;
public:
	AlgoNode(Location position, int GGrade);

	Location getLocation();
	int getGrade();
	int getHGrade();
	int getGGrade();
	void reGenerateGrade(Location end);
	int calcHGrade(Location end);
	virtual ~AlgoNode();

private:
	Location _currentPosition;
	int _GGrade;
	int _HGrade;
};

} /* namespace MNProj */

#endif /* ALGONODE_H_ */