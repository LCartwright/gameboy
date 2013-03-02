/*
 * Clock.h
 *
 *  Created on: 2 Mar 2013
 *      Author: muz0
 */

#ifndef CLOCK_H_
#define CLOCK_H_
#include "Logger.h"
class Clock {
	Logger logger;
public:
	Clock();
	virtual ~Clock();
	void cycle(int);
};

#endif /* CLOCK_H_ */
