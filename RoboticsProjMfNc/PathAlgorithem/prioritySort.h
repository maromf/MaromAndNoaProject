/*
 * prioritySort.h
 *
 *  Created on: Jul 17, 2015
 *      Author: colman
 */

#ifndef PRIORITYSORT_H_
#define PRIORITYSORT_H_

#include "AlgoNode.h"

namespace MNProj {

class prioritySort {
public:
	prioritySort();
	virtual ~prioritySort();

	bool operator() (AlgoNode a, AlgoNode b) const;
};

} /* namespace MNProj */

#endif /* PRIORITYSORT_H_ */
