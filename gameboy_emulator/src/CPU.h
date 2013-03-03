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
	uint16_t SP; //Stack Pointer
	uint16_t PC; //Program Counter
	bool IME; //Interrupt Master Enable

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

	bool * pIME;
	uint8_t * pIF;
	uint8_t * pIE;

	uint8_t memory [0xFFFF];

	Flags flags;
	Logger logger;
	Clock clock;

	void testFlags();
	void decode(uint8_t);
	void fetch();

	void nop();
	void halt();
	void stop();
	void di();
	void ei();

	void push_bc();
	void push_de();
	void push_hl();
	void push_af();

	void pop_bc();
	void pop_de();
	void pop_hl();
	void pop_af();

	void inc_bc();
	void inc_de();
	void inc_hl();
	void inc_sp();

	void dec_bc();
	void dec_de();
	void dec_hl();
	void dec_sp();

	void load_b_b();
	void load_b_c();
	void load_b_d();
	void load_b_e();
	void load_b_h();
	void load_b_l();
	void load_b_hl();
	void load_b_a();

	void load_c_b();
	void load_c_c();
	void load_c_d();
	void load_c_e();
	void load_c_h();
	void load_c_l();
	void load_c_hl();
	void load_c_a();

public:
	CPU();
	virtual ~CPU();
};

#endif /* CPU_H_ */
