#include "Opcodes.h"

//standard opcodes
void intializeRType(){
	rtypelookup[_ADD]  = add;
	rtypelookup[_SUB]  = sub;
	rtypelookup[_AND]  = r_and;
	rtypelookup[_OR]   = ror;
	rtypelookup[_SLL]  = sll;
	rtypelookup[_SRL]  = srl;
	rtypelookup[_JR]   = jumpReg;
	rtypelookup[_TRAP] = sysCall;
}
void rtype(MipsMachine* mac, _INST_WORD opcode){
	
}
void loadWord(MipsMachine* mac, _INST_WORD opcode){

}
void storeWord(MipsMachine* mac, _INST_WORD opcode){

}
void andI(MipsMachine* mac, _INST_WORD opcode){

}
void orI(MipsMachine* mac, _INST_WORD opcode){

}
void luI(MipsMachine* mac, _INST_WORD opcode){

}
void branchEQ(MipsMachine* mac, _INST_WORD opcode){

}
void branchNEQ(MipsMachine* mac, _INST_WORD opcode){

}
void setIfLessThanI(MipsMachine* mac, _INST_WORD opcode){

}
void addI(MipsMachine* mac, _INST_WORD opcode){

}
void jump(MipsMachine* mac, _INST_WORD opcode){

}
void jumpAndLink(MipsMachine* mac, _INST_WORD opcode){

}

//rtpe FUNC codes
void add(MipsMachine* mac, _INST_WORD opcode){

}
void sub(MipsMachine* mac, _INST_WORD opcode){

}
void r_and(MipsMachine* mac, _INST_WORD opcode){

}
void ror(MipsMachine* mac, _INST_WORD opcode){

}
void sll(MipsMachine* mac, _INST_WORD opcode){

}
void srl(MipsMachine* mac, _INST_WORD opcode){

}
void jumpReg(MipsMachine* mac, _INST_WORD opcode){

}
void sysCall(MipsMachine* mac, _INST_WORD opcode){

}

