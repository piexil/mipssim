/* 
	Mips Simulator written in C99
*/
#include "MipsMachine.h"
#include <stdio.h>

int main(int argc, char* argv[]){
	printf("MIPS Simulator written by Robert Ross\n");
	FILE* fin = NULL;
	if(argc <= 1){
		printf("Usage: %s filename\n",argv[0]);
	}
	printf("Starting simulation");
	MipsMachine* machine = machine_create();
	if(machine){
	
	}
}
