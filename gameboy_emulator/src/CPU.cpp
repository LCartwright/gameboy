/*
 * CPU.cpp
 *
 *  Created on: 7 Feb 2013
 *      Author: muz0
 */

#include "CPU.h"
#include "Logger.h"
#include <iostream>
using namespace std;


CPU::CPU() {
	logger = Logger();
	clock = Clock();

	for(int i=0; i<=0xFFFF;i++){memory[i] = 0;}

	AF = 0x01B0;
	pAF = &AF;
	pA = &A;
	pF = &F;

	//BC = 0xFFFF;
	BC = 0x0013;
	pBC = &BC;
	pB = &B;
	pC = &C;

	DE = 0x00D8;
	pDE = &DE;
	pD = &D;
	pE = &E;

	HL = 0x014D;
	pHL = &HL;
	pH = &H;
	pL = &L;

	SP = 0xFFFE;
	pSP = &SP;

	PC = 0x0000;
	pPC = &PC;

	//Interupt Pointers
	pIME = &IME;
	*pIME = false; //False by default?
	pIF = &memory[0xFF0F];
	pIE = &memory[0xFFFF];

	flags = Flags(&F);

	// Log all states of flags, could do in debugger

	// Need a propper testing class, test pup pops etc
	cout << "test" << *pSP << " " << *pB <<  *pC << endl;
	push_bc();
	//cout << "test" << endl;
	cout << "test" << memory[*pSP] << " " << endl;
	pop_bc();
	cout << "test" << memory[*pSP] << " " << endl;

	//testFlags();
}

CPU::~CPU() {
	// TODO Auto-generated destructor stub
}

void CPU::fetch(){
	decode(memory[*pPC]);
}

/* NOP 0x00 */
void CPU::nop(){
	++*pPC;
	clock.cycle(CYCLE_4);
}

/* STOP 0x10 */
void CPU::stop(){
	//TODO
	//Looks like this needs to be event based
	//Loop until flag interupt?
	++*pPC;
	clock.cycle(CYCLE_4);
}

/* HALT 0x76 */
void CPU::halt(){
	//TODO
	//Looks like this needs to be event based
	//Loop until flag interupt?
	++*pPC;
	clock.cycle(CYCLE_4);
}

/* DI 0xF3 */
void CPU::di(){
	*pIME = false;
	++*pPC;
	clock.cycle(CYCLE_4);
}

/* EI 0xFB */
void CPU::ei(){
	*pIME = true;
	++*pPC;
	clock.cycle(CYCLE_4);
}

/* PUSH BC 0xC5 */
void CPU::push_bc(){
	--*pSP;
	memory[*pSP] = *pB;
	--*pSP;
	memory[*pSP] = *pC;
	++*pPC;
	clock.cycle(CYCLE_16);
}

/* PUSH DE 0xD5 */
void CPU::push_de(){
	--*pSP;
	memory[*pSP] = *pD;
	--*pSP;
	memory[*pSP] = *pE;
	++*pPC;
	clock.cycle(CYCLE_16);
}

/* PUSH HL 0xE5 */
void CPU::push_hl(){
	--*pSP;
	memory[*pSP] = *pH;
	--*pSP;
	memory[*pSP] = *pL;
	++*pPC;
	clock.cycle(CYCLE_16);
}

/* PUSH AF 0xF5 */
void CPU::push_af(){
	--*pSP;
	memory[*pSP] = *pA;
	--*pSP;
	memory[*pSP] = *pF;
	++*pPC;
	clock.cycle(CYCLE_16);
}

/* POP BC 0xC1 */
void CPU::pop_bc(){
	*pC = memory[*pSP];
	++*pSP;
	*pB = memory[*pSP];
	++*pSP;
	++*pPC;
	clock.cycle(CYCLE_12);
}

/* POP DE 0xD1 */
void CPU::pop_de(){
	*pE = memory[*pSP];
	++*pSP;
	*pD = memory[*pSP];
	++*pSP;
	++*pPC;
	clock.cycle(CYCLE_12);
}

/* POP HL 0xE1 */
void CPU::pop_hl(){
	*pL = memory[*pSP];
	++*pSP;
	*pH = memory[*pSP];
	++*pSP;
	++*pPC;
	clock.cycle(CYCLE_12);
}

/* POP AF 0xF1 */
void CPU::pop_af(){
	*pF = memory[*pSP];
	++*pSP;
	*pA = memory[*pSP];
	++*pSP;
	++*pPC;
	clock.cycle(CYCLE_12);
}

/* DEC BC 0x0B */
void CPU::dec_bc(){
	if(*pBC != 0){
		--*pBC;
	}
	++pPC;
	clock.cycle(CYCLE_8);
}

/* DEC DE 0x1B */
void CPU::dec_de(){
	if(*pDE != 0){
		--*pDE;
	}
	++pPC;
	clock.cycle(CYCLE_8);
}

/* DEC HL 0x2B */
void CPU::dec_hl(){
	if(*pHL != 0){
		--*pHL;
	}
	++pPC;
	clock.cycle(CYCLE_8);
}

/* DEC SP 0x3B */
void CPU::dec_sp(){
	if(*pSP != 0){
		--*pSP;
	}
	++pPC;
	clock.cycle(CYCLE_8);
}

/* INC BC 0x03 */
void CPU::inc_bc(){
	if(*pBC != 0xFFFF){
		++*pBC;
	}
	++pPC;
	clock.cycle(CYCLE_8);
}

/* INC DE 0x13 */
void CPU::inc_de(){
	if(*pDE != 0xFFFF){
		++*pDE;
	}
	++pPC;
	clock.cycle(CYCLE_8);
}

/* INC HL 0x23 */
void CPU::inc_hl(){
	if(*pHL != 0xFFFF){
		++*pHL;
	}
	++pPC;
	clock.cycle(CYCLE_8);
}

/* INC SP 0x33 */
void CPU::inc_sp(){
	if(*pSP != 0xFFFF){
		++*pSP;
	}
	++pPC;
	clock.cycle(CYCLE_8);
}

/* LOAD BC 16bit 0x01 */
void CPU::load_bc_d16(){
	*pB = memory[++*pPC];
	*pC = memory[++*pPC];
	++*pPC;
	clock.cycle(CYCLE_12);
}

/* LOAD DE 16bit 0x11 */
void CPU::load_de_d16(){
	*pD = memory[++*pPC];
	*pE = memory[++*pPC];
	++*pPC;
	clock.cycle(CYCLE_12);
}

/* LOAD HL 16bit 0x21 */
void CPU::load_hl_d16(){
	*pH = memory[++*pPC];
	*pL = memory[++*pPC];
	++*pPC;
	clock.cycle(CYCLE_12);
}

/* LOAD SP 16bit 0x31 */
void CPU::load_sp_d16(){
	uint8_t high = memory[++*pPC];
	uint8_t low = memory[++*pPC];
	*pSP = high << low;
	++*pPC;
	clock.cycle(CYCLE_12);
}

/* LOAD BC A 0x02 */
void CPU::load_bc_a(){
	memory[*pBC] = *pA;
	++*pPC;
	clock.cycle(CYCLE_8);
}

/* LOAD DE A 0x12 */
void CPU::load_de_a(){
	memory[*pDE] = *pA;
	++*pPC;
	clock.cycle(CYCLE_8);
}

/* LOAD B d8 0x06 */
void CPU::load_b_d8(){
	*pB = memory[++*pPC];
	++*pPC;
	clock.cycle(CYCLE_8);
}

/* LOAD D d8 0x16 */
void CPU::load_d_d8(){
	*pD = memory[++*pPC];
	++*pPC;
	clock.cycle(CYCLE_8);
}

/* LOAD H d8 0x26 */
void CPU::load_h_d8(){
	*pH = memory[++*pPC];
	++*pPC;
	clock.cycle(CYCLE_8);
}

/* LOAD (HL) d8 0x36 */
void CPU::load_hl_d8(){
	memory[*pHL] = memory[++*pPC];
	++*pPC;
	clock.cycle(CYCLE_12);
}

/* LOAD A (BC) 0x0A */
void CPU::load_a_bc(){
	*pA = memory[*pBC];
	++*pPC;
	clock.cycle(CYCLE_8);
}

/* LOAD A (BC) 0x1A */
void CPU::load_a_de(){
	*pA = memory[*pDE];
	++*pPC;
	clock.cycle(CYCLE_8);
}

/* LOAD C d8 0x0E */
void CPU::load_c_d8(){
	*pC = memory[++*pPC];
	++*pPC;
	clock.cycle(CYCLE_8);
}

/* LOAD E d8 0x1E */
void CPU::load_e_d8(){
	*pE = memory[++*pPC];
	++*pPC;
	clock.cycle(CYCLE_8);
}

/* LOAD L d8 0x2E */
void CPU::load_l_d8(){
	*pL = memory[++*pPC];
	++*pPC;
	clock.cycle(CYCLE_8);
}

/* LOAD A d8 0x3E */
void CPU::load_a_d8(){
	*pA = memory[++*pPC];
	++*pPC;
	clock.cycle(CYCLE_8);
}

/* LOAD B, B 0x40 */
void CPU::load_b_b(){
	//B will always be B
	++*pPC;
	clock.cycle(CYCLE_4);
}

/* LOAD B, C 0x41 */
void CPU::load_b_c(){
	*pB = *pC;
	++*pPC;
	clock.cycle(CYCLE_4);
}

/* LOAD B, D 0x42 */
void CPU::load_b_d(){
	*pB = *pD;
	++*pPC;
	clock.cycle(CYCLE_4);
}

/* LOAD B, E 0x43 */
void CPU::load_b_e(){
	*pB = *pE;
	++*pPC;
	clock.cycle(CYCLE_4);
}

/* LOAD B, H 0x44 */
void CPU::load_b_h(){
	*pB = *pH;
	++*pPC;
	clock.cycle(CYCLE_4);
}

/* LOAD B, L 0x45 */
void CPU::load_b_l(){
	*pB = *pL;
	++*pPC;
	clock.cycle(CYCLE_4);
}

/* LOAD B, (HL) 0x46 */
void CPU::load_b_hl(){
	*pB = memory[*pHL];
	++*pPC;
	clock.cycle(CYCLE_8);
}

/* LOAD B, A 0x47 */
void CPU::load_b_a(){
	*pB = *pA;
	++*pPC;
	clock.cycle(CYCLE_4);
}

/* LOAD C, B 0x48 */
void CPU::load_c_b(){
	*pC = *pB;
	++*pPC;
	clock.cycle(CYCLE_4);
}

/* LOAD C, C 0x49 */
void CPU::load_c_c(){
	//C will always be C
	++*pPC;
	clock.cycle(CYCLE_4);
}

/* LOAD C, D 0x4A */
void CPU::load_c_d(){
	*pC = *pD;
	++*pPC;
	clock.cycle(CYCLE_4);
}

/* LOAD C, E 0x4B */
void CPU::load_c_e(){
	*pC = *pE;
	++*pPC;
	clock.cycle(CYCLE_4);
}

/* LOAD C, H 0x4C */
void CPU::load_c_h(){
	*pC = *pH;
	++*pPC;
	clock.cycle(CYCLE_4);
}

/* LOAD C, L 0x4D */
void CPU::load_c_l(){
	*pC = *pL;
	++*pPC;
	clock.cycle(CYCLE_4);
}

/* LOAD C, (HL) 0x4E */
void CPU::load_c_hl(){
	*pC = memory[*pHL];
	++*pPC;
	clock.cycle(CYCLE_8);
}

/* LOAD C, A 0x4F */
void CPU::load_c_a(){
	*pC = *pA;
	++*pPC;
	clock.cycle(CYCLE_4);
}

/* LOAD D, B 0x50 */
void CPU::load_d_b(){
	*pD = *pB;
	++*pPC;
	clock.cycle(CYCLE_4);
}

/* LOAD D, C 0x51 */
void CPU::load_d_c(){
	*pD = *pC;
	++*pPC;
	clock.cycle(CYCLE_4);
}

/* LOAD D, D 0x52 */
void CPU::load_d_d(){
	//D will always be D
	++*pPC;
	clock.cycle(CYCLE_4);
}

/* LOAD D, E 0x53 */
void CPU::load_d_e(){
	*pD = *pE;
	++*pPC;
	clock.cycle(CYCLE_4);
}

/* LOAD D, H 0x54 */
void CPU::load_d_h(){
	*pD = *pH;
	++*pPC;
	clock.cycle(CYCLE_4);
}

/* LOAD D, L 0x55 */
void CPU::load_d_l(){
	*pD = *pL;
	++*pPC;
	clock.cycle(CYCLE_4);
}

/* LOAD D, (HL) 0x56 */
void CPU::load_d_hl(){
	*pD = memory[*pHL];
	++*pPC;
	clock.cycle(CYCLE_8);
}

/* LOAD D, A 0x57 */
void CPU::load_d_a(){
	*pD = *pA;
	++*pPC;
	clock.cycle(CYCLE_4);
}

/* LOAD E, B 0x58 */
void CPU::load_e_b(){
	*pE = *pB;
	++*pPC;
	clock.cycle(CYCLE_4);
}

/* LOAD E, C 0x59 */
void CPU::load_e_c(){
	*pE = *pC;
	++*pPC;
	clock.cycle(CYCLE_4);
}

/* LOAD E, D 0x5A */
void CPU::load_e_d(){
	*pE = *pD;
	++*pPC;
	clock.cycle(CYCLE_4);
}

/* LOAD E, E 0x5B */
void CPU::load_e_e(){
	//E will always be E
	++*pPC;
	clock.cycle(CYCLE_4);
}

/* LOAD E, H 0x5C */
void CPU::load_e_h(){
	*pE = *pH;
	++*pPC;
	clock.cycle(CYCLE_4);
}

/* LOAD E, L 0x5D */
void CPU::load_e_l(){
	*pE = *pL;
	++*pPC;
	clock.cycle(CYCLE_4);
}

/* LOAD E, (HL) 0x5E */
void CPU::load_e_hl(){
	*pE = memory[*pHL];
	++*pPC;
	clock.cycle(CYCLE_8);
}

/* LOAD E, A 0x5F */
void CPU::load_e_a(){
	*pE = *pA;
	++*pPC;
	clock.cycle(CYCLE_4);
}

/* LOAD H, B 0x60 */
void CPU::load_h_b(){
	*pH = *pB;
	++*pPC;
	clock.cycle(CYCLE_4);
}

/* LOAD H, C 0x61 */
void CPU::load_h_c(){
	*pH = *pC;
	++*pPC;
	clock.cycle(CYCLE_4);
}

/* LOAD H, D 0x62 */
void CPU::load_h_d(){
	*pH = *pD;
	++*pPC;
	clock.cycle(CYCLE_4);
}

/* LOAD H, E 0x63 */
void CPU::load_h_e(){
	*pH = *pE;
	++*pPC;
	clock.cycle(CYCLE_4);
}

/* LOAD H, H 0x64 */
void CPU::load_h_h(){
	//H will always be H
	++*pPC;
	clock.cycle(CYCLE_4);
}

/* LOAD H, L 0x65 */
void CPU::load_h_l(){
	*pH = *pL;
	++*pPC;
	clock.cycle(CYCLE_4);
}

/* LOAD H, (HL) 0x66 */
void CPU::load_h_hl(){
	*pH = memory[*pHL];
	++*pPC;
	clock.cycle(CYCLE_8);
}

/* LOAD H, A 0x67 */
void CPU::load_h_a(){
	*pH = *pA;
	++*pPC;
	clock.cycle(CYCLE_4);
}

/* LOAD L, B 0x68 */
void CPU::load_l_b(){
	*pL = *pB;
	++*pPC;
	clock.cycle(CYCLE_4);
}

/* LOAD L, C 0x69 */
void CPU::load_l_c(){
	*pL = *pC;
	++*pPC;
	clock.cycle(CYCLE_4);
}

/* LOAD L, D 0x6A */
void CPU::load_l_d(){
	*pL = *pD;
	++*pPC;
	clock.cycle(CYCLE_4);
}

/* LOAD L, E 0x6B */
void CPU::load_l_e(){
	*pL = *pE;
	++*pPC;
	clock.cycle(CYCLE_4);
}

/* LOAD L, H 0x6C */
void CPU::load_l_h(){
	*pL = *pH;
	++*pPC;
	clock.cycle(CYCLE_4);
}

/* LOAD L, L 0x6D */
void CPU::load_l_l(){
	//L will always be L
	++*pPC;
	clock.cycle(CYCLE_4);
}

/* LOAD L, HL 0x6E */
void CPU::load_l_hl(){
	*pL = memory[*pHL];
	++*pPC;
	clock.cycle(CYCLE_8);
}

/* LOAD L, 0x6F */
void CPU::load_l_a(){
	*pL = *pA;
	++*pPC;
	clock.cycle(CYCLE_4);
}

/* LOAD (HL), B 0x70 */
void CPU::load_hl_b(){
	*pHL = *pB;
	++*pPC;
	clock.cycle(CYCLE_8);
}

/* LOAD (HL), C 0x71 */
void CPU::load_hl_c(){
	*pHL = *pC;
	++*pPC;
	clock.cycle(CYCLE_8);
}

/* LOAD (HL), D 0x72 */
void CPU::load_hl_d(){
	*pHL = *pD;
	++*pPC;
	clock.cycle(CYCLE_8);
}

/* LOAD (HL), E 0x73 */
void CPU::load_hl_e(){
	*pHL = *pE;
	++*pPC;
	clock.cycle(CYCLE_8);
}

/* LOAD (HL), H 0x74 */
void CPU::load_hl_h(){
	*pHL = *pH;
	++*pPC;
	clock.cycle(CYCLE_8);
}

/* LOAD (HL), L 0x75 */
void CPU::load_hl_l(){
	*pHL = *pL;
	++*pPC;
	clock.cycle(CYCLE_8);
}

/* LOAD (HL), A 0x77 */
void CPU::load_hl_a(){
	*pHL = *pA;
	++*pPC;
	clock.cycle(CYCLE_8);
}

/* LOAD A, B 0x78 */
void CPU::load_a_b(){
	*pA = *pB;
	++*pPC;
	clock.cycle(CYCLE_4);
}

/* LOAD A, C 0x79 */
void CPU::load_a_c(){
	*pA = *pC;
	++*pPC;
	clock.cycle(CYCLE_4);
}

/* LOAD A, D 0x7A */
void CPU::load_a_d(){
	*pA = *pD;
	++*pPC;
	clock.cycle(CYCLE_4);
}
/* LOAD A, E 0x7B */
void CPU::load_a_e(){
	*pA = *pE;
	++*pPC;
	clock.cycle(CYCLE_4);
}

/* LOAD A, H 0x7C */
void CPU::load_a_h(){
	*pA = *pH;
	++*pPC;
	clock.cycle(CYCLE_4);
}

/* LOAD A, L 0x7D */
void CPU::load_a_l(){
	*pA = *pL;
	++*pPC;
	clock.cycle(CYCLE_4);
}

/* LOAD A, (HL) 0x7E */
void CPU::load_a_hl(){
	*pA = memory[*pHL];
	++*pPC;
	clock.cycle(CYCLE_8);
}

/* LOAD A, A 0x7F */
void CPU::load_a_a(){
	//A will always be A
	++*pPC;
	clock.cycle(CYCLE_4);
}

/* AND B 0xA0 */
void CPU::and_b(){
	*pA &= *pB;
	if(*pA == 0){
		flags.setZ();
	}else{
		flags.unSetZ();
	}
	flags.unSetN();
	flags.setH();
	flags.unSetC();
	++*pPC;
	clock.cycle(CYCLE_4);
}

/* AND C 0xA1 */
void CPU::and_c(){
	*pA &= *pC;
	if(*pA == 0){
		flags.setZ();
	}else{
		flags.unSetZ();
	}
	flags.unSetN();
	flags.setH();
	flags.unSetC();
	++*pPC;
	clock.cycle(CYCLE_4);
}

/* AND D 0xA2 */
void CPU::and_d(){
	*pA &= *pD;
	if(*pA == 0){
		flags.setZ();
	}else{
		flags.unSetZ();
	}
	flags.unSetN();
	flags.setH();
	flags.unSetC();
	++*pPC;
	clock.cycle(CYCLE_4);
}

/* AND E 0xA3 */
void CPU::and_e(){
	*pA &= *pE;
	if(*pA == 0){
		flags.setZ();
	}else{
		flags.unSetZ();
	}
	flags.unSetN();
	flags.setH();
	flags.unSetC();
	++*pPC;
	clock.cycle(CYCLE_4);
}

/* AND H 0xA4 */
void CPU::and_h(){
	*pA &= *pH;
	if(*pA == 0){
		flags.setZ();
	}else{
		flags.unSetZ();
	}
	flags.unSetN();
	flags.setH();
	flags.unSetC();
	++*pPC;
	clock.cycle(CYCLE_4);
}

/* AND L 0xA5 */
void CPU::and_l(){
	*pA &= *pL;
	if(*pA == 0){
		flags.setZ();
	}else{
		flags.unSetZ();
	}
	flags.unSetN();
	flags.setH();
	flags.unSetC();
	++*pPC;
	clock.cycle(CYCLE_4);
}

/* AND (HL) 0xA6 */
void CPU::and_hl(){
	*pA &= memory[*pHL];
	if(*pA == 0){
		flags.setZ();
	}else{
		flags.unSetZ();
	}
	flags.unSetN();
	flags.setH();
	flags.unSetC();
	++*pPC;
	clock.cycle(CYCLE_8);
}

/* AND A 0xA7 */
void CPU::and_a(){
	*pA &= *pA;
	if(*pA == 0){
		flags.setZ();
	}else{
		flags.unSetZ();
	}
	flags.unSetN();
	flags.setH();
	flags.unSetC();
	++*pPC;
	clock.cycle(CYCLE_4);
}

/* XOR B 0xA8 */
void CPU::xor_b(){
	*pA ^= *pB;
	if(*pA == 0){
		flags.setZ();
	}else{
		flags.unSetZ();
	}
	flags.unSetN();
	flags.unSetH();
	flags.unSetC();
	++*pPC;
	clock.cycle(CYCLE_4);
}

/* XOR C 0xA9 */
void CPU::xor_c(){
	*pA ^= *pC;
	if(*pA == 0){
		flags.setZ();
	}else{
		flags.unSetZ();
	}
	flags.unSetN();
	flags.unSetH();
	flags.unSetC();
	++*pPC;
	clock.cycle(CYCLE_4);
}

/* XOR D 0xAA */
void CPU::xor_d(){
	*pA ^= *pD;
	if(*pA == 0){
		flags.setZ();
	}else{
		flags.unSetZ();
	}
	flags.unSetN();
	flags.unSetH();
	flags.unSetC();
	++*pPC;
	clock.cycle(CYCLE_4);
}

/* XOR E 0xAB */
void CPU::xor_e(){
	*pA ^= *pE;
	if(*pA == 0){
		flags.setZ();
	}else{
		flags.unSetZ();
	}
	flags.unSetN();
	flags.unSetH();
	flags.unSetC();
	++*pPC;
	clock.cycle(CYCLE_4);
}

/* XOR H 0xAC */
void CPU::xor_h(){
	*pA ^= *pH;
	if(*pA == 0){
		flags.setZ();
	}else{
		flags.unSetZ();
	}
	flags.unSetN();
	flags.unSetH();
	flags.unSetC();
	++*pPC;
	clock.cycle(CYCLE_4);
}

/* XOR L 0xAD */
void CPU::xor_l(){
	*pA ^= *pL;
	if(*pA == 0){
		flags.setZ();
	}else{
		flags.unSetZ();
	}
	flags.unSetN();
	flags.unSetH();
	flags.unSetC();
	++*pPC;
	clock.cycle(CYCLE_4);
}

/* XOR (HL) 0xAE */
void CPU::xor_hl(){
	*pA ^= memory[*pHL];
	if(*pA == 0){
		flags.setZ();
	}else{
		flags.unSetZ();
	}
	flags.unSetN();
	flags.unSetH();
	flags.unSetC();
	++*pPC;
	clock.cycle(CYCLE_8);
}

/* XOR A 0xAF */
void CPU::xor_a(){
	*pA ^= *pA;
	if(*pA == 0){
		flags.setZ();
	}else{
		flags.unSetZ();
	}
	flags.unSetN();
	flags.unSetH();
	flags.unSetC();
	++*pPC;
	clock.cycle(CYCLE_4);
}

/* OR B 0xB0 */
void CPU::or_b(){
	*pA |= *pB;
	if(*pA == 0){
		flags.setZ();
	}else{
		flags.unSetZ();
	}
	flags.unSetN();
	flags.unSetH();
	flags.unSetC();
	++*pPC;
	clock.cycle(CYCLE_4);
}

/* OR C 0xB1 */
void CPU::or_c(){
	*pA |= *pC;
	if(*pA == 0){
		flags.setZ();
	}else{
		flags.unSetZ();
	}
	flags.unSetN();
	flags.unSetH();
	flags.unSetC();
	++*pPC;
	clock.cycle(CYCLE_4);
}

/* OR D 0xB2 */
void CPU::or_d(){
	*pA |= *pD;
	if(*pA == 0){
		flags.setZ();
	}else{
		flags.unSetZ();
	}
	flags.unSetN();
	flags.unSetH();
	flags.unSetC();
	++*pPC;
	clock.cycle(CYCLE_4);
}

/* OR E 0xB3 */
void CPU::or_e(){
	*pA |= *pE;
	if(*pA == 0){
		flags.setZ();
	}else{
		flags.unSetZ();
	}
	flags.unSetN();
	flags.unSetH();
	flags.unSetC();
	++*pPC;
	clock.cycle(CYCLE_4);
}

/* OR H 0xB4 */
void CPU::or_h(){
	*pA |= *pH;
	if(*pA == 0){
		flags.setZ();
	}else{
		flags.unSetZ();
	}
	flags.unSetN();
	flags.unSetH();
	flags.unSetC();
	++*pPC;
	clock.cycle(CYCLE_4);
}

/* OR L 0xB5 */
void CPU::or_l(){
	*pA |= *pL;
	if(*pA == 0){
		flags.setZ();
	}else{
		flags.unSetZ();
	}
	flags.unSetN();
	flags.unSetH();
	flags.unSetC();
	++*pPC;
	clock.cycle(CYCLE_4);
}

/* OR (HL) 0xB6 */
void CPU::or_hl(){
	*pA |= memory[*pHL];
	if(*pA == 0){
		flags.setZ();
	}else{
		flags.unSetZ();
	}
	flags.unSetN();
	flags.unSetH();
	flags.unSetC();
	++*pPC;
	clock.cycle(CYCLE_8);
}

/* OR A 0xB7 */
void CPU::or_a(){
	*pA |= *pA;
	if(*pA == 0){
		flags.setZ();
	}else{
		flags.unSetZ();
	}
	flags.unSetN();
	flags.unSetH();
	flags.unSetC();
	++*pPC;
	clock.cycle(CYCLE_4);
}

void CPU::decode(uint8_t opcode){
	switch (opcode){
		//00 - 0F
		case 0x00:nop();break;
		case 0x01:load_bc_d16();break;
		case 0x02:load_bc_a();break;
		case 0x03:inc_bc();break;
		case 0x04:break;
		case 0x05:break;
		case 0x06:load_b_d8();break;
		case 0x07:break;
		case 0x08:break;
		case 0x09:break;
		case 0x0A:load_a_bc();break;
		case 0x0B:dec_bc();break;
		case 0x0C:break;
		case 0x0D:break;
		case 0x0E:load_c_d8();break;
		case 0x0F:break;

		//10 - 1F
		case 0x10:stop();break;
		case 0x11:load_de_d16();break;
		case 0x12:load_de_a();break;
		case 0x13:inc_de();break;
		case 0x14:break;
		case 0x15:break;
		case 0x16:load_d_d8();break;
		case 0x17:break;
		case 0x18:break;
		case 0x19:break;
		case 0x1A:load_a_de();break;
		case 0x1B:dec_de();break;
		case 0x1C:break;
		case 0x1D:break;
		case 0x1E:load_e_d8();break;
		case 0x1F:break;

		//20 - 2F
		case 0x20:break;
		case 0x21:load_hl_d16();break;
		case 0x22:break;
		case 0x23:inc_hl();break;
		case 0x24:break;
		case 0x25:break;
		case 0x26:load_h_d8();break;
		case 0x27:break;
		case 0x28:break;
		case 0x29:break;
		case 0x2A:break;
		case 0x2B:dec_hl();break;
		case 0x2C:break;
		case 0x2D:break;
		case 0x2E:load_l_d8();break;
		case 0x2F:break;

		//30 - 3F
		case 0x30:break;
		case 0x31:load_sp_d16();break;
		case 0x32:break;
		case 0x33:inc_sp();break;
		case 0x34:break;
		case 0x35:break;
		case 0x36:load_hl_d8();break;
		case 0x37:break;
		case 0x38:break;
		case 0x39:break;
		case 0x3A:break;
		case 0x3B:dec_sp();break;
		case 0x3C:break;
		case 0x3D:break;
		case 0x3E:load_a_d8();break;
		case 0x3F:break;

		//40 - 4F
		case 0x40:load_b_b();break;
		case 0x41:load_b_c();break;
		case 0x42:load_b_d();break;
		case 0x43:load_b_e();break;
		case 0x44:load_b_h();break;
		case 0x45:load_b_l();break;
		case 0x46:load_b_hl();break;
		case 0x47:load_b_a();break;
		case 0x48:load_c_b();break;
		case 0x49:load_c_c();break;
		case 0x4A:load_c_d();break;
		case 0x4B:load_c_e();break;
		case 0x4C:load_c_h();break;
		case 0x4D:load_c_l();break;
		case 0x4E:load_c_hl();break;
		case 0x4F:load_c_a();break;

		//50 - 5F
		case 0x50:load_d_b();break;
		case 0x51:load_d_c();break;
		case 0x52:load_d_d();break;
		case 0x53:load_d_e();break;
		case 0x54:load_d_h();break;
		case 0x55:load_d_l();break;
		case 0x56:load_d_hl();break;
		case 0x57:load_d_a();break;
		case 0x58:load_e_b();break;
		case 0x59:load_e_c();break;
		case 0x5A:load_e_d();break;
		case 0x5B:load_e_e();break;
		case 0x5C:load_e_h();break;
		case 0x5D:load_e_l();break;
		case 0x5E:load_e_hl();break;
		case 0x5F:load_e_a();break;

		//60 - 6F
		case 0x60:load_h_b();break;
		case 0x61:load_h_c();break;
		case 0x62:load_h_d();break;
		case 0x63:load_h_e();break;
		case 0x64:load_h_h();break;
		case 0x65:load_h_l();break;
		case 0x66:load_h_hl();break;
		case 0x67:load_h_a();break;
		case 0x68:load_l_b();break;
		case 0x69:load_l_c();break;
		case 0x6A:load_l_d();break;
		case 0x6B:load_l_e();break;
		case 0x6C:load_l_h();break;
		case 0x6D:load_l_l();break;
		case 0x6E:load_l_hl();break;
		case 0x6F:load_l_a();break;

		//70 - 7F
		case 0x70:load_hl_b();break;
		case 0x71:load_hl_c();break;
		case 0x72:load_hl_d();break;
		case 0x73:load_hl_e();break;
		case 0x74:load_hl_h();break;
		case 0x75:load_hl_l();break;
		case 0x76:halt();break;
		case 0x77:load_hl_a();break;
		case 0x78:load_a_b();break;
		case 0x79:load_a_c();break;
		case 0x7A:load_a_d();break;
		case 0x7B:load_a_e();break;
		case 0x7C:load_a_h();break;
		case 0x7D:load_a_l();break;
		case 0x7E:load_a_hl();break;
		case 0x7F:load_a_a();break;

		//80 - 8F
		case 0x80:break;
		case 0x81:break;
		case 0x82:break;
		case 0x83:break;
		case 0x84:break;
		case 0x85:break;
		case 0x86:break;
		case 0x87:break;
		case 0x88:break;
		case 0x89:break;
		case 0x8A:break;
		case 0x8B:break;
		case 0x8C:break;
		case 0x8D:break;
		case 0x8E:break;
		case 0x8F:break;

		//90 - 9F
		case 0x90:break;
		case 0x91:break;
		case 0x92:break;
		case 0x93:break;
		case 0x94:break;
		case 0x95:break;
		case 0x96:break;
		case 0x97:break;
		case 0x98:break;
		case 0x99:break;
		case 0x9A:break;
		case 0x9B:break;
		case 0x9C:break;
		case 0x9D:break;
		case 0x9E:break;
		case 0x9F:break;

		//A0 - AF
		case 0xA0:and_b();break;
		case 0xA1:and_c();break;
		case 0xA2:and_d();break;
		case 0xA3:and_e();break;
		case 0xA4:and_h();break;
		case 0xA5:and_l();break;
		case 0xA6:and_hl();break;
		case 0xA7:and_a();break;
		case 0xA8:xor_b();break;
		case 0xA9:xor_c();break;
		case 0xAA:xor_d();break;
		case 0xAB:xor_e();break;
		case 0xAC:xor_h();break;
		case 0xAD:xor_l();break;
		case 0xAE:xor_hl();break;
		case 0xAF:xor_a();break;

		//B0 - BF
		case 0xB0:or_b();break;
		case 0xB1:or_c();break;
		case 0xB2:or_d();break;
		case 0xB3:or_e();break;
		case 0xB4:or_h();break;
		case 0xB5:or_l();break;
		case 0xB6:or_hl();break;
		case 0xB7:or_a();break;
		case 0xB8:break;
		case 0xB9:break;
		case 0xBA:break;
		case 0xBB:break;
		case 0xBC:break;
		case 0xBD:break;
		case 0xBE:break;
		case 0xBF:break;

		//C0 - CF
		case 0xC0:break;
		case 0xC1:pop_bc();break;
		case 0xC2:break;
		case 0xC3:break;
		case 0xC4:break;
		case 0xC5:push_bc();break;
		case 0xC6:break;
		case 0xC7:break;
		case 0xC8:break;
		case 0xC9:break;
		case 0xCA:break;
		case 0xCB:break;
		case 0xCC:break;
		case 0xCD:break;
		case 0xCE:break;
		case 0xCF:break;

		//D0 - DF
		case 0xD0:break;
		case 0xD1:pop_de();break;
		case 0xD2:break;
		case 0xD3:logger.log("D3 decoded, shoudn't occur");break;
		case 0xD4:break;
		case 0xD5:push_de();break;
		case 0xD6:break;
		case 0xD7:break;
		case 0xD8:break;
		case 0xD9:break;
		case 0xDA:break;
		case 0xDB:logger.log("DB decoded, shoudn't occur");break;
		case 0xDC:break;
		case 0xDD:break;
		case 0xDE:logger.log("DE decoded, shoudn't occur");break;
		case 0xDF:break;

		//E0 - EF
		case 0xE0:break;
		case 0xE1:pop_hl();break;
		case 0xE2:break;
		case 0xE3:logger.log("E3 decoded, shoudn't occur");break;
		case 0xE4:logger.log("E4 decoded, shoudn't occur");break;
		case 0xE5:push_hl();break;
		case 0xE6:break;
		case 0xE7:break;
		case 0xE8:break;
		case 0xE9:break;
		case 0xEA:break;
		case 0xEB:logger.log("EB decoded, shoudn't occur");break;
		case 0xEC:logger.log("EC decoded, shoudn't occur");break;
		case 0xED:logger.log("ED decoded, shoudn't occur");break;
		case 0xEE:break;
		case 0xEF:break;

		//F0 - FF
		case 0xF0:break;
		case 0xF1:pop_af();break;
		case 0xF2:break;
		case 0xF3:di();break;
		case 0xF4:logger.log("F4 decoded, shoudn't occur");break;
		case 0xF5:push_af();break;
		case 0xF6:break;
		case 0xF7:break;
		case 0xF8:break;
		case 0xF9:break;
		case 0xFA:break;
		case 0xFB:ei();break;
		case 0xFC:logger.log("FC decoded, shoudn't occur");break;
		case 0xFD:logger.log("FD decoded, shoudn't occur");break;
		case 0xFE:break;
		case 0xFF:break;

		default: logger.log("Opcode Not Found"); break;
	}
}

void CPU::testFlags(){
	logger.log("Z flag testing");
	flags.setZ();
	cout << flags.getZ();logger.log("SetZOnce");
	flags.setZ();
	cout << flags.getZ();logger.log("SetZTwice");
	flags.unSetZ();
	cout << flags.getZ();logger.log("UnSetZOnce");
	flags.unSetZ();
	cout << flags.getZ();logger.log("UnSetZTwice");
	flags.flipZ();
	cout << flags.getZ();logger.log("flipZ");
	flags.flipZ();
	cout << flags.getZ();logger.log("flipZ");

	logger.log("C flag testing");
	flags.setC();
	cout << flags.getC();logger.log("SetCOnce");
	flags.setC();
	cout << flags.getC();logger.log("SetCTwice");
	flags.unSetC();
	cout << flags.getC();logger.log("UnSetCOnce");
	flags.unSetC();
	cout << flags.getC();logger.log("UnSetCTwice");
	flags.flipC();
	cout << flags.getC();logger.log("flipC");
	flags.flipC();
	cout << flags.getC();logger.log("flipC");
	logger.log("I am a banana!");

	flags.setC();
	flags.setH();
	flags.setN();
	flags.setZ();
	cout << flags.getC() << flags.getH() << flags.getN() << flags.getZ();
}

