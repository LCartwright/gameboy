/*
 * Registers.h
 *
 *  Created on: 9 Feb 2013
 *      Author: muz0
 */

#ifndef REGISTERS_H_
#define REGISTERS_H_
#include <stdint.h>
#include "Flags.h"

class Registers {
	//Register declarations go here
	//Flags go here;
	uint8_t F;
	Flags flags;
public:
	Registers();
	virtual ~Registers();
};

#endif /* REGISTERS_H_ */
