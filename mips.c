/* 
	Mips Simulator written in GNUC11
*/
#include <stdio.h>
#include "MipsMachine.h"
#include "Common.h"
int main(int argc, char* argv[]){
	printf("MIPS Simulator written by piexil\n");
	printf("_DATA_WORD %lu \n", sizeof(_DATA_WORD));
	printf("_INST_WORD %lu \n", sizeof(_INST_WORD));
	FILE* fin = NULL;
	if(argc <= 1){
		printf("Usage: %s filename\n",argv[0]);
		return 1;
	}
	if((fin = fopen(argv[1], "rb")) == NULL){
		printf("File %s not found\n", argv[1]);
		return 1;
	}
	printf("Starting simulation\n");
	MipsMachine* machine = machine_create();
	if(machine){
		startsim(machine, fin);
	}
}
