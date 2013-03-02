/*
 * Clock.cpp
 *
 *  Created on: 2 Mar 2013
 *      Author: muz0
 */

#include "Clock.h"

Clock::Clock() {
	// TODO Auto-generated constructor stub
	logger = Logger();
}

Clock::~Clock() {
	// TODO Auto-generated destructor stub
}

void Clock::cycle(int count){
	if(count%4 == 0 || count%8==0 || count%12==0 || count%16==0 ){
		for(int i=0; i<count; i++){
				//Do nothing, for now
		}
	}

}

