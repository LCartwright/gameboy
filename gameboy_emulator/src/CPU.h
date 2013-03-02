/*
 * CPU.h
 *
 *  Created on: 7 Feb 2013
 *      Author: muz0
 */

#ifndef CPU_H_
#define CPU_H_
#include <stdint.h>
#include "Flags.h"
#include "Logger.h"
#include "Clock.h"

class CPU {

	static const int CYCLE_4 = 4;
	static const int CYCLE_8 = 8;
	static const int CYCLE_12 = 12;
	static const int CYCLE_16 = 16;

	union {
		uint16_t AF;
		uint8_t A;
		uint8_t F;
	};
	union {
		uint16_t BC;
		uint8_t B;
		uint8_t C;
	};
	union {
		uint16_t DE;
		uint8_t D;
		uint8_t E;
	};
	union {
		uint16_t HL;
		uint8_t H;
		uint8_t L;
	};
	uint16_t SP;
	uint16_t PC;

	uint16_t * pAF;
	uint16_t * pBC;
	uint16_t * pDE;
	uint16_t * pHL;
	uint16_t * pSP;
	uint16_t * pPC;

	uint8_t * pA;
	uint8_t * pF;

	uint8_t * pB;
	uint8_t * pC;

	uint8_t * pD;
	uint8_t * pE;

	uint8_t * pH;
	uint8_t * pL;

	uint8_t memory [0xFFFF];

	Flags flags;
	Logger logger;
	Clock clock;

	void testFlags();
	void decode(uint8_t);
	void fetch();

	void push_bc();
	void push_de();
	void push_hl();
	void push_af();

	void pop_bc();
	void pop_de();
	void pop_hl();
	void pop_af();
public:
	CPU();
	virtual ~CPU();
};

#endif /* CPU_H_ */
