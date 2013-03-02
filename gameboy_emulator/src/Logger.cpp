/*
 * Logger.cpp
 *
 *  Created on: 27 Feb 2013
 *      Author: muz0
 */

#include "Logger.h"
#include <iostream>
#include <ctime>
using namespace std;
Logger::Logger() {
	// TODO Auto-generated constructor stub

}

Logger::~Logger() {
	// TODO Auto-generated destructor stub
}

void Logger::log(string message){
	const time_t curr = time(NULL);
	const tm* local = localtime(&curr);
	cout << message << " ";
	cout << local->tm_hour << "h:" << local->tm_min << "m:" << local->tm_sec << "s"  << endl;
}
