#include "VirtualMemory.h"
#include <stdio.h>
#include <stdlib.h>
VirtualMem* memCreate(int byteMemSize){
    VirtualMem* mem = malloc(sizeof(VirtualMem));
    if(mem){
        mem->addressable.bytemem = malloc(sizeof(byteMemSize));
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

}
_DATA_WORD vmem_get_word(VirtualMem* vm, int position){
    return vm->addressable.mem[position];
}