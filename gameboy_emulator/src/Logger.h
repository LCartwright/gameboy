/*
 * Logger.h
 *
 *  Created on: 27 Feb 2013
 *      Author: muz0
 */

#ifndef LOGGER_H_
#define LOGGER_H_
#include <string>
using namespace std;
class Logger {
public:
	Logger();
	virtual ~Logger();
	void log(string);
};

#endif /* LOGGER_H_ */
