#ifndef VIRTUALMEMORY_H
#define VIRTUALMEMORY_H
#include "Common.h"


typedef struct _VirtualMemory{
	union{
		_DATA_WORD* mem; //get mem via word size
		char* bytemem;
	} addressable;
} VirtualMem;



VirtualMem* memCreate(int byteMemSize);

void mem_destroy(VirtualMem* vm);
void vmem_set_word(VirtualMem* vm, int position, _DATA_WORD val);
_DATA_WORD vmem_get_word(VirtualMem* vm, int position);
#endif
