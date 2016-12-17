#include "Common.h"
//standard opcodes
void rtype(_INST_WORD);
void loadWord(_INST_WORD);
void storeWord(_INST_WORD);
void andI(_INST_WORD);
void orI(_INST_WORD);
void luI(_INST_WORD);
void branchEQ(_INST_WORD);
void branchNEQ(_INST_WORD);
void setIfLessThanI(_INST_WORD);
void addI(_INST_WORD);
void jump(_INST_WORD);
void jumpAndLink(_INST_WORD);

//rtpe FUNC codes
void add(_INST_WORD);
void sub(_INST_WORD);
void and(_INST_WORD);
void or(_INST_WORD);
void sll(_INST_WORD);
void srl(_INST_WORD);
void jumpReg(_INST_WORD);
void sysCall(_INST_WORD);
