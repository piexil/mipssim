#ifndef MIPSMACHINE_H
#define MIPSMACHINE_H
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
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

void (*oplookup[64])(MipsMachine*,_INST_WORD);

MipsMachine* machine_create();
void 	startsim(MipsMachine*,FILE*);
#endif
