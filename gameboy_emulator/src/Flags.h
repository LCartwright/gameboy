/*
 * Flags.h
 *
 *  Created on: 9 Feb 2013
 *      Author: muz0
 */

#ifndef FLAGS_H_
#define FLAGS_H_
#include <stdint.h>
class Flags {

public:
	uint8_t * pF;
	Flags();
	Flags(uint8_t *);
	virtual ~Flags();

	void setZ();//bit 7 Zero
	void setC();//bit 4 Carry
	void setN();//bit 6 Add/Sub
	void setH();//bit 5 Half Carry

	void unSetZ();
	void unSetC();
	void unSetN();
	void unSetH();

	bool getZ();
	bool getC();
	bool getN();
	bool getH();

	void flipZ();
	void flipC();
	void flipN();
	void flipH();
};

#endif /* FLAGS_H_ */
