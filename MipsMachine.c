
#include <stdio.h>
#include <inttypes.h>
#include "MipsMachine.h"
#include"VirtualMemory.h"
#include "Opcodes.h"

int memSize = 0x7FFFFFFF;
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
	intializeRType();
	//load file into memory
	fprintf(stderr,"Loading File into Memory\n");
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
		return;
	}
	int year = (excte->version>>9)+2000;
	int month = (excte->version&0x1E0) >> 5;
	int day = (excte->version&0x01F);
	fprintf(stderr,"version: %d/%d/%d\n",year,month,day);
	fprintf(stderr,"flags: %x\n",excte->flags);
	fprintf(stderr,"entry: %x\n",excte->entry);
	fprintf(stderr,"text: %u entries\n",excte->data[0]);
	fprintf(stderr,"rdata: %u entries\n",excte->data[1]);
	fprintf(stderr,"data: %u entries\n",excte->data[2]);
	fprintf(stderr,"sdata: %u entries\n",excte->data[3]);
	machine->rf->pc=excte->entry;
	int offset = 13 * 4;
	_DATA_WORD curWord = 0;
	//load the text
	for(int i = 0; i < excte->data[0]; i++){
		curWord = 0;
		fseek(file,offset,SEEK_SET);
		fread(&curWord,sizeof(_DATA_WORD),1,file);
		fprintf(stderr,"loading inst: %"PRIx32" @0x%"PRIx32"\n",ntohl(curWord),TEXT_BEGIN+(i*4));
		vmem_set_word(machine->mem,TEXT_BEGIN+(i*4),ntohl(curWord));
		offset += 4;
	}
	//calculate amount of data
	int totaldata = excte->data[1]+excte->data[2]+excte->data[3];
	//load data
	for(int i = 0; i < totaldata; i++){
		curWord = 0;
		fseek(file,offset,SEEK_SET);
		fread(&curWord,sizeof(_DATA_WORD),1,file);
		fprintf(stderr,"loading data: %"PRIx32" @0x%"PRIx32"\n",ntohl(curWord),DATA_BEGIN+(i*4));
		vmem_set_word(machine->mem,DATA_BEGIN+(i*4),ntohl(curWord));
		offset += 4;
	}
	for(int i = 0; i < 8; i++){
		execute(machine,vmem_get_word(machine->mem,machine->rf->pc));
	}
}

void execute(MipsMachine* mac, _INST_WORD opcode){
	fprintf(stderr,"opcode: %"PRIx32"@0x%"PRIx32"\n",opcode,mac->rf->pc);
	uint32_t op = (opcode&0xFC000000)>>26;
	fprintf(stderr,"operation: %"PRIx32"\n",op);
	(*oplookup[op])(mac,opcode);

}

