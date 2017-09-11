
#include <stdio.h>
#include "MipsMachine.h"
#include "Opcodes.h"

int memSize = 67108864;
MipsMachine* machine_create(){
	MipsMachine* mac = malloc(sizeof(MipsMachine));
	mac->rf = malloc(sizeof(RegFile));
	mac->mem =memCreate(memSize);
	return mac;
}

void initRegisters(MipsMachine* m){
	for(int i = 0; i < 32; i++){
		m->rf->gpregisters[i] = 0;
	}
	m->rf->pc = m->rf->ir = 0;
	m->rf->hilo = 0;
}
void startsim(MipsMachine* machine, FILE* file){
	//intialize opcode lookup table
	oplookup[_RTYPE] = rtype;
	oplookup[_LW] = loadWord;
	oplookup[_ANDI] = andI;
	oplookup[_ORI] = orI;
	oplookup[_LUI] = luI;
	oplookup[_BEQ] = branchEQ;
	oplookup[_BNE] = branchNEQ;
	oplookup[_SLTI] = setIfLessThanI;
	oplookup[_ADDI] = addI;
	oplookup[_J] = jump;
	oplookup[_JAL] = jumpAndLink; 
	//load file into memory
	printf("Loading File into Memory\n");
	int numData, numInstruct = -1;
	exec *excte = malloc(sizeof(exec));
	fread(excte,sizeof(exec),1,file);
	excte->magic = ntohs(excte->magic);
	excte->version = ntohs(excte->version);
    excte->flags = ntohl(excte->flags);
    excte->entry = ntohl(excte->entry);
    excte->data[0] = ntohl(excte->data[0]);
    excte->data[1] = ntohl(excte->data[1]);
    excte->data[2] = ntohl(excte->data[2]);
    excte->data[3] = ntohl(excte->data[3]);
    excte->data[4] = ntohl(excte->data[4]);
    excte->data[5] = ntohl(excte->data[5]);
    excte->data[6] = ntohl(excte->data[6]);
    excte->data[7] = ntohl(excte->data[7]);
    excte->data[8] = ntohl(excte->data[8]);
    excte->data[9] = ntohl(excte->data[9]);
	if(excte->magic != 0xFACE){
		fprintf(stderr,"error: file is not R2K obj module (MN: 0x%04x)\n",excte->magic);
	}
	printf("version: %u\n",excte->version);
	printf("flags: %u\n",excte->flags);
	printf("text: %u\n",excte->data[0]);
	printf("rdata: %u\n",excte->data[1]);
	printf("data: %u\n",excte->data[2]);
	printf("sdata: %u\n",excte->data[3]);
	printf("rel: %u\n",excte->data[4]);
	printf("ext ref: %u\n",excte->data[5]);
	printf("sym: %u\n",excte->data[6]);
	printf("string: %u\n",excte->data[7]);
	//start executing
}

void execute(MipsMachine* mac, _INST_WORD opcode){

}

