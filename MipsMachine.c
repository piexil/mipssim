#include <stdio.h>>
#include "MipsMachine.h"
#include "Common.h"
void (*oplookup[20])(_INST_WORD opcode);

MipsMachine* machine_create(){
	MipsMachine* mac = malloc(sizeof(MipsMachine));
	mac->rf = malloc(sizeof(RegFile));
	return mac;
}
void startsim(MipsMachine* machine, FILE* file){
	//intialize opcode lookup table
	oplookup[_JTYPE] = jtype;
	
	//load file into memory

	//start executing
}

void execute(_INST_WORD opcode)
