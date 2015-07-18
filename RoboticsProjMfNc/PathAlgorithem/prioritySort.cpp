/*
 * prioritySort.cpp
 *
 *  Created on: Jul 17, 2015
 *      Author: colman
 */

#include "prioritySort.h"


prioritySort::prioritySort() {
	// TODO Auto-generated constructor stub

}

prioritySort::~prioritySort() {
	// TODO Auto-generated destructor stub
}

bool prioritySort::operator() (AlgoNode & a, AlgoNode & b) const {
 return (a < b);
}

//bool prioritySort::operator() (AlgoNode a, AlgoNode b) const{
//	return ((a)<(b));
//}

