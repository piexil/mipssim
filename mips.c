/* 
	Mips Simulator written in GNUC11
*/
#include <stdio.h>
#include "MipsMachine.h"
#include "Common.h"
int main(int argc, char* argv[]){
	printf("MIPS Simulator\n");
	fprintf(stderr,"_DATA_WORD %lu \n", sizeof(_DATA_WORD));
	fprintf(stderr,"_INST_WORD %lu \n", sizeof(_INST_WORD));
	FILE* fin = NULL;
	if(argc <= 1){
		printf("Usage: %s filename\n",argv[0]);
		return 1;
	}
	if((fin = fopen(argv[1], "r")) == NULL){
		printf("File %s not found\n", argv[1]);
		return 1;
	}
	fprintf(stderr,"Starting simulation\n");
	MipsMachine* machine = machine_create();
	fprintf(stderr,"Machine Created.\n");
	initRegisters(machine);
	fprintf(stderr,"Registers Intialized\n");
	
	if(machine){
		startsim(machine, fin);
	}
}
