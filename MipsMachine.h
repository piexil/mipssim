#ifndef MIPSMACHINE_H
#define MIPSMACHINE_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "Common.h"

#include "VirtualMemory.h"


typedef struct _Registers{
	int32_t gpregisters[32];
	int32_t pc;
	int32_t ir;
	union{
		struct{
			int32_t hi;
			int32_t lo;
		};
		int64_t hilo;
	};
} RegFile;

typedef struct _MipsMachine{
	RegFile* rf;
	VirtualMem* mem;
	int limit;
} MipsMachine;

typedef struct _exec {
	uint16_t magic;
	uint16_t version;
	uint32_t flags;	
	uint32_t entry;
	uint32_t data[10];
} exec;

void (*oplookup[64])(MipsMachine*,_INST_WORD);

MipsMachine* machine_create();
void initRegisters(MipsMachine*);
void 	startsim(MipsMachine*,FILE*);
#endif
