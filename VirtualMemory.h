#ifndef VIRTUALMEMORY_H
#define VIRTUALMEMORY_H
#include "Common.h"

int memsize = 67108864/sizeof(_DATA_WORD); //default to 64MiB ram
typedef struct _VirtualMemory{
	union{
		_DATA_WORD* mem; //get mem via word size
		char* bytemem;
	} addressable;
} VirtualMem;


VirtualMem* mem_Create();
void mem_destroy(VirtualMem* vm);
void vmem_set_word(VirtualMem* vm, int position, _DATA_WORD val);
_DATA_WORD vmem_get_word(VirtualMem* vm, int position);
#endif
