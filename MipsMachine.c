
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
	exec_t * exec = malloc(sozeof(exec_t));
	fread(exec,sizeof(exec_t),1,file);
	exec->magic = ntohs(exec->magic);
	exec->version = ntohs(exec->version);
    exec->flags = ntohl(exec->flags);
    exec->entry = ntohl(exec->entry);
    exec->data[0] = ntohl(exec->data[0]);
    exec->data[1] = ntohl(exec->data[1]);
    exec->data[2] = ntohl(exec->data[2]);
    exec->data[3] = ntohl(exec->data[3]);
    exec->data[4] = ntohl(exec->data[4]);
    exec->data[5] = ntohl(exec->data[5]);
    exec->data[6] = ntohl(exec->data[6]);
    exec->data[7] = ntohl(exec->data[7]);
    exec->data[8] = ntohl(exec->data[8]);
    exec->data[9] = ntohl(exec->data[9]);
	if(exec->magic != oxFACE){
		fprintf(stderr,"error: file is not R2K obj module (MN: 0x%04x)\n",exec-magic);
	}
	prinft("")
	//start executing
}

void execute(MipsMachine* mac, _INST_WORD opcode){
}

