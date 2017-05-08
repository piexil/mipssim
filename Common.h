#ifndef COMMON_H
#define COMMON_H

#include <stdint.h>

typedef int32_t _DATA_WORD;
typedef uint32_t _UDATA_WORD;
typedef int32_t _INST_WORD;

//opcode definitions
//R_TYPE
#define  _RTYPE	0x0
#define _ADD	0x20
#define _SUB	0x22
#define _AND	0x24
#define _OR 	0x25
#define _SLL	0x0
#define	_SLT	0x2A
#define	_SRL	0x2
#define	_JR	    0x8
#define _TRAP	0xC //aka syscall
//I_TYPE
#define _LW	    0x23
#define	_SW 	0x2B
#define	_ANDI	0xC
#define _ORI	0xD
#define	_LUI	0xF
#define	_BEQ	0x4
#define	_BNE	0x5
#define	_SLTI	0xA
#define	_ADDI	0x8
//J_TYPE
#define	_J	    0x2
#define	_JAL	0x3

#endif
