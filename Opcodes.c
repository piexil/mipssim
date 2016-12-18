#include "Opcodes.h"
//standard opcodes
void rtype(MipsMachine* mac, _INST_WORD opcode){

}
void loadWord(MipsMachine* mac, _INST_WORD opcode){

}
void storeWord(MipsMachine* mac, _INST_WORD opcode){

}
void andI(MipsMachine* mac, _INST_WORD opcode){

}
void orI(MipsMachine*, _INST_WORD);
void luI(MipsMachine*, _INST_WORD);
void branchEQ(MipsMachine*, _INST_WORD);
void branchNEQ(MipsMachine*, _INST_WORD);
void setIfLessThanI(MipsMachine*, _INST_WORD);
void addI(MipsMachine*, _INST_WORD);
void jump(MipsMachine*, _INST_WORD);
void jumpAndLink(MipsMachine*, _INST_WORD);

//rtpe FUNC codes
void add(MipsMachine*, _INST_WORD);
void sub(MipsMachine*, _INST_WORD);
void and(MipsMachine*, _INST_WORD);
void or(MipsMachine*, _INST_WORD);
void sll(MipsMachine*, _INST_WORD);
void srl(MipsMachine*, _INST_WORD);
void jumpReg(MipsMachine*, _INST_WORD);
void sysCall(MipsMachine*, _INST_WORD);

