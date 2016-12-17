#include <stdlib.h>
#include <stdint.h>
#include "VirtualMemory.h"
#include "Common.h"

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

void (*oplookup[20])(_INST_WORD);

MipsMachine* machine_create();
void 	startsim(MipsMachine*,FILE*);

