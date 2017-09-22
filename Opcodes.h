#ifndef OPCODES_H
#define OPCODES_H
#define sExt(x) (int32_t)x 
#include "MipsMachine.h"

typedef struct _decoded_opcode_rtrype {
    unsigned short opcode;
    unsigned short rs;
    unsigned short rt;
    unsigned short rd;
    unsigned short shiftAmount;
    unsigned short function;
   
} rType;
typedef struct _decoded_opcode_itype {
    unsigned short opcode;
    unsigned short rs;
    unsigned short rt;
    int16_t immediate;
} iType;
typedef struct _decoded_opcode_jump{
    unsigned short opcode;
    uint32_t address;
} jumpType;

void (*rtypelookup[64])(MipsMachine*,rType*);
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
void setLessThanU(MipsMachine* mac, _INST_WORD opcode);
//rtpe FUNC codes
void add(MipsMachine*,rType*);
void sub(MipsMachine*,rType*);
void r_and(MipsMachine*,rType*);
void ror(MipsMachine*,rType*);
void sll(MipsMachine*,rType*);
void srl(MipsMachine*,rType*);
void jumpReg(MipsMachine*,rType*);
void sysCall(MipsMachine*,rType*);


void intializeRType();
#endif
