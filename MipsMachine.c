#include "Common.h""
MipsMachine* machine_create(){
	MipsMachine* mac = malloc(sizeof(MipsMachine));
	mac->rf = malloc(sizeof(RegFile));
	mac->mem = mem_Create(67108864);
	return mac;
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
	
	//start executing
}

void execute(MipsMachine* mac, _INST_WORD opcode){

}

