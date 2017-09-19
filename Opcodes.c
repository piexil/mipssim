#include "Opcodes.h"
#include <inttypes.h>
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
iType* itypeDecode(_INST_WORD opcode){
	iType* itypeRet = malloc(sizeof(iType));
	itypeRet->opcode = (opcode&0xFC000000)>>26;
	itypeRet->rs = (opcode&0x03E00000)>>21;
	fprintf(stderr,"$rs: %"PRIu32" ",itypeRet->rs);
	itypeRet->rt = (opcode&0x001F0000)>>16;
	fprintf(stderr,"$rt: %"PRIu32" ",itypeRet->rt);
	itypeRet->immediate = (opcode&0x0000FFFF);
	fprintf(stderr,"i: %"PRIx32" ",itypeRet->immediate);
	return itypeRet;
}
void rtype(MipsMachine* mac, _INST_WORD opcode){
	fprintf(stderr,"rtype");
}
void loadWord(MipsMachine* mac, _INST_WORD opcode){
	fprintf(stderr,"loadword\n");
	iType* instruction = itypeDecode(opcode);
	uint32_t address = mac->rf->gpregisters[instruction->rs] + instruction->immediate;
	_DATA_WORD word = vmem_get_word(mac->mem,address);
	mac->rf->gpregisters[instruction->rt] = word;
	free(instruction);
	mac->rf->pc+=4;
}
void storeWord(MipsMachine* mac, _INST_WORD opcode){
	fprintf(stderr,"storeword");
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

