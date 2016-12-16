#include <stdio.h>>
#include "MipsMachine.h"

MipsMachine* machine_create(){
	MipsMachine* mac = malloc(sizeof(MipsMachine));
	mac->rf = malloc(sizeof(RegFile));
	return mac;
}


