



#ifndef MirmOSFUNC_H
#define MirmOSFUNC_H


#define systemError(a) {PROCESSOR_STATE_PRINT();systemError_h(a);} 

extern "C" int SPSR_REGISTER();
extern "C" int CPU_MODE();
extern "C" int STACK_POINTER();

void processor_state();

#define PROCESSOR_STATE_PRINT() \
{get_PROCESSOR(); \
processor_state(); \
get_PROCESSOR_exit();} 

#define get_PROCESSOR()  \
asm("push {r0,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,sp,lr,pc}"); \
SPSR_REGISTER(); \
asm("push {r0}"); \
CPU_MODE();\
asm("push {r0}"); \
PROCESSOR = (PROCESSOR_t *) (STACK_POINTER()); \

#define get_PROCESSOR_exit()  \
asm("add sp, #8");
asm("pop {r0,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,sp,lr,pc}");\


#include "mvirt.h"

struct PROCESSOR_t
{
int CPSR;
int SPSR;
int R[13];
int SP;
int LR;
int PC;
};
extern PROCESSOR_t *PROCESSOR;












volatile void systemError_h(const char * c)__attribute__((noreturn));

#define prlnhex(a) 	stdio->println((int)a,HEX);
#define prhex(a) 	stdio->print((int)a,HEX);
#define pr(a) stdio->print(a);
#define prln(a) stdio->println(a);
#define prtab stdio->write('\t');


uint8_t statusBit(uint8_t &f,uint8_t a);
void setBit(uint8_t &f,uint8_t a);
void clrBit(uint8_t &f,uint8_t a);
void about();
//void AutoExec();

#define DROP_SPACE(c); for (;(*c!=0) && (*c==' '); c++);

#define FIND_FIRST_OPERAND(c,d) \
{for (;(*c!=0) && (*c==' '); c++);\
d=c;							\
for (;(*d!=0) && (*d!=' '); d++);}

#define CUT_FIRST_OPERAND(c,d) \
{FIND_FIRST_OPERAND(c,d); \
if (*d!=0) {*d=0;d++;}}


#endif
