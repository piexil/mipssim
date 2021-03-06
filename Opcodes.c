#include "Opcodes.h"
#include <inttypes.h>
#include <stdio.h>
//standard opcodes
void intializeRType(){
	rtypelookup[_ADD]  = add;
	rtypelookup[_ADDU] = addu;
	rtypelookup[_SUB]  = sub;
	rtypelookup[_AND]  = r_and;
	rtypelookup[_OR]   = ror;
	rtypelookup[_SLL]  = sll;
	rtypelookup[_SRL]  = srl;
	rtypelookup[_JR]   = jumpReg;
	rtypelookup[_TRAP] = sysCall;
	rtypelookup[_SLTU] = setLessThanU;
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
	rType* instr = rtypeDecode(opcode);
	fprintf(stderr,"func: %"PRIx32"\n",instr->function);
	(*rtypelookup[instr->function])(mac,instr);
	free(instr);
	mac->rf->pc+=4;
}
void loadWord(MipsMachine* mac, _INST_WORD opcode){
	fprintf(stderr,"loadword\n");
	iType* instruction = itypeDecode(opcode);
	int32_t address = mac->rf->gpregisters[instruction->rs] + sExt(instruction->immediate);
	_DATA_WORD word = vmem_get_word(mac->mem,address);
	mac->rf->gpregisters[instruction->rt] = word;
	free(instruction);
	mac->rf->pc+=4;
}
void storeWord(MipsMachine* mac, _INST_WORD opcode){
	fprintf(stderr,"storeword\n");
	iType* instruction = itypeDecode(opcode);
	int32_t address = mac->rf->gpregisters[instruction->rs] + sExt(instruction->immediate);
	fprintf(stderr,"rs = %"PRIu32" address: 0x%"PRIx32"\n",mac->rf->gpregisters[instruction->rs],address);
	_DATA_WORD word = mac->rf->gpregisters[instruction->rt];
	vmem_set_word(mac->mem,address,word);
	free(instruction);
	mac->rf->pc += 4;
}
void andI(MipsMachine* mac, _INST_WORD opcode){
	fprintf(stderr,"andi\n");
	iType* instruction = itypeDecode(opcode);
	uint32_t rt = instruction->rt;
	uint32_t rs = instruction->rs;
	uint32_t im = instruction->immediate;
	mac->rf->gpregisters[rt] = mac->rf->gpregisters[rs]&sExt(im);
	free(instruction);
	mac->rf->pc += 4;	

}
void orI(MipsMachine* mac, _INST_WORD opcode){
	fprintf(stderr,"ori\n");
	iType* instruction = itypeDecode(opcode);
	uint32_t rt = instruction->rt;
	uint32_t rs = instruction->rs;
	int32_t im = instruction->immediate;
	mac->rf->gpregisters[rt] = mac->rf->gpregisters[rs]|sExt(im);
	free(instruction);
	mac->rf->pc += 4;	
}
void luI(MipsMachine* mac, _INST_WORD opcode){
	fprintf(stderr,"lui\n");
	iType* instruction = itypeDecode(opcode);
	uint32_t rt = instruction->rt;
	int32_t im = instruction->immediate;
	fprintf(stderr,"shifted immediate: %"PRIx32"\n",im<<16);
	mac->rf->gpregisters[rt] = im<<16;
	free(instruction);
	mac->rf->pc += 4;
}
void branchEQ(MipsMachine* mac, _INST_WORD opcode){
	fprintf(stderr,"beq\n");
	iType* instruction = itypeDecode(opcode);
	uint32_t rt = instruction->rt;
	uint32_t rs = instruction->rs;
	uint32_t im = instruction->immediate;
	if(mac->rf->gpregisters[rs] == mac->rf->gpregisters[rt]){
		mac->rf->pc += 4+im;
	}
	else{
		mac->rf->pc += 4;
	}
}
void branchNEQ(MipsMachine* mac, _INST_WORD opcode){

}
void setIfLessThanI(MipsMachine* mac, _INST_WORD opcode){
	fprintf(stderr,"slti\n");
	iType* instruction = itypeDecode(opcode);
	uint32_t rt = instruction->rt;
	uint32_t rs = instruction->rs;
	uint32_t im = instruction->immediate;
	mac->rf->gpregisters[rt] = (mac->rf->gpregisters[rs]<sExt(im)) ? 1 : 0;
	mac->rf->pc += 4;
	free(instruction);
}

void addI(MipsMachine* mac, _INST_WORD opcode){
	fprintf(stderr,"addi\n");
	iType* instruction = itypeDecode(opcode);
	uint32_t rt = instruction->rt;
	uint32_t rs = instruction->rs;
	int32_t im = instruction->immediate;
	fprintf(stderr,"signed immediate:%"PRIi32"\n",instruction->immediate);
	mac->rf->gpregisters[rt] = mac->rf->gpregisters[rs]+sExt(im);
	fprintf(stderr,"result: %"PRIi32"\n",mac->rf->gpregisters[rt]);
	free(instruction);
	mac->rf->pc += 4;
}
void jump(MipsMachine* mac, _INST_WORD opcode){
	fprintf(stderr,"jump\n");
	jumpType* instruction = jumptypeDecode(opcode);
	mac->rf->pc = (mac->rf->pc & 0xF0000000) | (instruction->address); //jumpa ddress is absolute
	free(instruction);
}
void jumpAndLink(MipsMachine* mac, _INST_WORD opcode){
	fprintf(stderr,"jump and link\n");
	jumpType* instruction = jumptypeDecode(opcode);
	mac->rf->gpregisters[31]=mac->rf->pc;
	mac->rf->pc = ((mac->rf->pc + 4) & 0xF0000000) | (instruction->address); //jumpa ddress is absolute
	free(instruction);
}

//rtpe FUNC codes
void add(MipsMachine* mac,rType* instr){
	fprintf(stderr,"add\n");
	uint32_t rd = instr->rd;
	uint32_t rs = instr->rs;
	uint32_t rt = instr->rt;
	mac->rf->gpregisters[rd]=mac->rf->gpregisters[rs]+mac->rf->gpregisters[rt];
}
void addu(MipsMachine* mac,rType* instr){
	fprintf(stderr,"add\n");
	uint32_t rd = instr->rd;
	uint32_t rs = instr->rs;
	uint32_t rt = instr->rt;
	mac->rf->gpregisters[rd]=(_UDATA_WORD)mac->rf->gpregisters[rs]+(_UDATA_WORD)mac->rf->gpregisters[rt];
}
void sub(MipsMachine* mac,rType* instr){
	fprintf(stderr,"sub\n");
	uint32_t rd = instr->rd;
	uint32_t rs = instr->rs;
	uint32_t rt = instr->rt;
	mac->rf->gpregisters[rd]=mac->rf->gpregisters[rs]-mac->rf->gpregisters[rt];
}
void r_and(MipsMachine* mac,rType* instr){
	fprintf(stderr,"and\n");
	uint32_t rd = instr->rd;
	uint32_t rs = instr->rs;
	uint32_t rt = instr->rt;
	mac->rf->gpregisters[rd]=mac->rf->gpregisters[rs]&mac->rf->gpregisters[rt];
}
void ror(MipsMachine* mac,rType* instr){
	fprintf(stderr,"or\n");
	uint32_t rd = instr->rd;
	uint32_t rs = instr->rs;
	uint32_t rt = instr->rt;
	mac->rf->gpregisters[rd]=mac->rf->gpregisters[rs]|mac->rf->gpregisters[rt];
}
void sll(MipsMachine* mac,rType* instr){
	fprintf(stderr,"shift left logical\n");
	uint32_t rd = instr->rd;
	uint32_t rt = instr->rt;
	mac->rf->gpregisters[rd]=mac->rf->gpregisters[rt]<<instr->shiftAmount;
}
void srl(MipsMachine* mac,rType* instr){
	fprintf(stderr,"shift right logical\n");
	uint32_t rd = instr->rd;
	uint32_t rt = instr->rt;
	mac->rf->gpregisters[rd]=mac->rf->gpregisters[rt]>>instr->shiftAmount;
}
void jumpReg(MipsMachine* mac,rType* instr){
	fprintf(stderr,"jumpRegister\n");
	mac->rf->pc=mac->rf->gpregisters[instr->rs];//dont forget jump register will automatically add 4 to PC after invoked
}
void setLessThanU(MipsMachine* mac,rType* instr){
	
}
void sysCall(MipsMachine* mac,rType* instr){
	fprintf(stderr,"syscall\n");
	switch(mac->rf->gpregisters[2]){	//switch on $v0
		case 1:							//print int $a0
			printf("%"PRIu32"",mac->rf->gpregisters[4]);
			break;
		case 4:{							//string
			fprintf(stderr,"string print\n");
			char p = ' ';
			uint32_t address = mac->rf->gpregisters[4];
			while(p!='\0'){
				p = get_byte(mac->mem,address++);
				fprintf(stdout,"%c",p);
			}
			break;
		}
		case 5:							//read int
			fprintf(stderr,"read int\n");	
			scanf("%d",&mac->rf->gpregisters[2]);					
			break;
		default:
			fprintf(stderr, "Unimplemented SYSCALL\n");
			exit(1);
	}
}

