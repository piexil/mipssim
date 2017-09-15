#include "VirtualMemory.h"
#include <stdio.h>
#include <stdlib.h>
#define byte_word(vm,p) *((_DATA_WORD*)(vm->addressable.bytemem + p))
VirtualMem* memCreate(int byteMemSize){
    VirtualMem* mem = malloc(sizeof(VirtualMem));
    if(mem){
        mem->addressable.bytemem = malloc(byteMemSize);
        if(!mem->addressable.bytemem){
            free(mem);
            printf("Error allocating memory.\n");
            return (VirtualMem*)0;
        }
    }
    return mem;
}


void mem_destroy(VirtualMem* vm){
    free(vm->addressable.bytemem);
    free(vm);
}

void vmem_set_word(VirtualMem* vm, int position, _DATA_WORD val){
    byte_word(vm,position) = val;
}
_DATA_WORD vmem_get_word(VirtualMem* vm, int position){
    return byte_word(vm,position);
}