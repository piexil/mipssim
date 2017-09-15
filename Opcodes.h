#ifndef OPCODES_H
#define OPCODES_H

#include "MipsMachine.h"

typedef struct _decoded_opcode_rtrype {
    unsigned short opcode;
    unsigned short rs;
    unsigned short rt;
    unsigned short rd;
    unsigned short shiftAmount;
   
} rType;
typedef struct _decoded_opcode_itype {
    unsigned short opcode;
    unsigned short rs;
    unsigned short rt;
    uint16_t immediate;
} iType;
typedef struct _decoded_opcode_jump{
    unsigned short opcode;
    uint32_t address;
} jumpType;

void (*rtypelookup[64])(MipsMachine*, _INST_WORD);
//opcode decoders
rType* rtypeDecode(_INST_WORD);
iType* itypeDecode(_INST_WORD);
jumpType* jumpDecode(_INST_WORD);
//standard opcodes
void rtype(MipsMachine*, _INST_WORD);
void loadWord(MipsMachine*, _INST_WORD);
void storeWord(MipsMachine*, _INST_WORD);
void andI(MipsMachine*, _INST_WORD);
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
void r_and(MipsMachine*, _INST_WORD);
void ror(MipsMachine*, _INST_WORD);
void sll(MipsMachine*, _INST_WORD);
void srl(MipsMachine*, _INST_WORD);
void jumpReg(MipsMachine*, _INST_WORD);
void sysCall(MipsMachine*, _INST_WORD);

void intializeRType();
#endif
