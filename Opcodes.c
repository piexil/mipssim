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
	fprintf(stderr,"i: %"PRIx32"\n",itypeRet->immediate);
	return itypeRet;
}
rType* rtypeDecode(_INST_WORD opcode){
	rType* rtypeRet = malloc(sizeof(rType));
	rtypeRet->opcode = (opcode&0xFC000000)>>26;
	rtypeRet->rs = (opcode&0x03E00000)>>21;
	fprintf(stderr,"$rs: %"PRIu32" ",rtypeRet->rs);
	rtypeRet->rd = (opcode&0x001F0000)>>16;
	fprintf(stderr,"$rd: %"PRIu32" ",rtypeRet->rd);
	rtypeRet->rt = (opcode&0x0000F800)>>11;
	fprintf(stderr,"$rt: %"PRIu32" ",rtypeRet->rt);
	rtypeRet->shiftAmount = (opcode&0x000007C0)>>6;
	fprintf(stderr,"shift: %"PRIx32" ",rtypeRet->shiftAmount);
	rtypeRet->function = (opcode&0x0000003F);
	fprintf(stderr,"funct: %"PRIx32"\n",rtypeRet->function);
	return rtypeRet;
}
jumpType* jumptypeDecode(_INST_WORD opcode){
	jumpType* jumptypeRet = malloc(sizeof(jumpType));
	jumptypeRet->opcode = (opcode&0xFC000000)>>26;
	jumptypeRet->address = ((opcode&0x03FFFFFF)<<2); //alignment
	fprintf(stderr,"address: %"PRIx32"\n",jumptypeRet->address);
	return jumptypeRet;
}
void rtype(MipsMachine* mac, _INST_WORD opcode){
	fprintf(stderr,"rtype\n");
	uint32_t func = (opcode&0x0000003F);
	(*rtypelookup[func])(mac,opcode);
	mac->rf->pc+=4;
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
	fprintf(stderr,"jump and link\n");
	jumpType* instruction = jumptypeDecode(opcode);
	mac->rf->gpregisters[31]=mac->rf->pc + 8;
	mac->rf->pc = (mac->rf->pc & 0xF0000000) | (instruction->address);
	free(instruction);
}

//rtpe FUNC codes
void add(MipsMachine* mac, _INST_WORD opcode){
	fprintf(stderr,"add\n");
	rType* instr = rtypeDecode(opcode);
	uint32_t rd = instr->rd;
	uint32_t rs = instr->rs;
	uint32_t rt = instr->rt;
	mac->rf->gpregisters[rd]=mac->rf->gpregisters[rs]+mac->rf->gpregisters[rt];
}
void sub(MipsMachine* mac, _INST_WORD opcode){
	fprintf(stderr,"sub\n");
	rType* instr = rtypeDecode(opcode);
	uint32_t rd = instr->rd;
	uint32_t rs = instr->rs;
	uint32_t rt = instr->rt;
	mac->rf->gpregisters[rd]=mac->rf->gpregisters[rs]-mac->rf->gpregisters[rt];
}
void r_and(MipsMachine* mac, _INST_WORD opcode){
	fprintf(stderr,"and\n");
	rType* instr = rtypeDecode(opcode);
	uint32_t rd = instr->rd;
	uint32_t rs = instr->rs;
	uint32_t rt = instr->rt;
	mac->rf->gpregisters[rd]=mac->rf->gpregisters[rs]&mac->rf->gpregisters[rt];
}
void ror(MipsMachine* mac, _INST_WORD opcode){
	fprintf(stderr,"or\n");
	rType* instr = rtypeDecode(opcode);
	uint32_t rd = instr->rd;
	uint32_t rs = instr->rs;
	uint32_t rt = instr->rt;
	mac->rf->gpregisters[rd]=mac->rf->gpregisters[rs]|mac->rf->gpregisters[rt];
}
void sll(MipsMachine* mac, _INST_WORD opcode){
	fprintf(stderr,"shift left logical\n");
	rType* instr = rtypeDecode(opcode);
	uint32_t rd = instr->rd;
	uint32_t rt = instr->rt;
	mac->rf->gpregisters[rd]=mac->rf->gpregisters[rt]<<instr->shiftAmount;
}
void srl(MipsMachine* mac, _INST_WORD opcode){

}
void jumpReg(MipsMachine* mac, _INST_WORD opcode){

}
void sysCall(MipsMachine* mac, _INST_WORD opcode){

}

