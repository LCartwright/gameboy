/*
 * Flags.cpp
 *
 *  Created on: 9 Feb 2013
 *      Author: muz0
 */

#include "Flags.h"

Flags::Flags() {
	//Do nothing!
}

Flags::Flags(uint8_t * pF) {

	this->pF = pF;
}

Flags::~Flags() {

}

void Flags::setZ(){
	*pF |= 0x80;
}

void Flags::setC(){
	*pF |= 0x10;
}

void Flags::setN(){
	*pF |= 0x40;
}

void Flags::setH(){
	*pF |= 0x20;
}

void Flags::unSetZ(){
	*pF &= ~(0x80);
}

void Flags::unSetC(){
	*pF &= ~(0x10);
}

void Flags::unSetN(){
	*pF &= ~(0x40);
}

void Flags::unSetH(){
	*pF &= ~(0x20);
}

bool Flags::getZ(){
	return (((*pF&0x80) == 0x80)? true : false);
}

bool Flags::getC(){
	return (((*pF&0x10) == 0x10)? true : false);
}

bool Flags::getN(){
	return (((*pF&0x40) == 0x40)? true : false);
}

bool Flags::getH(){
	return (((*pF&0x20) == 0x20)? true : false);
}

void Flags::flipZ(){
	*pF ^= 0x80;
}

void Flags::flipC(){
	*pF ^= 0x10;
}

void Flags::flipN(){
	*pF ^= 0x40;
}

void Flags::flipH(){
	*pF ^= 0x20;
}
