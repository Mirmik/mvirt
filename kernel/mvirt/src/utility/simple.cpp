
#include "simple.h"
#include "hardware.h" 


uint8_t statusBit(uint8_t &f,uint8_t a)
{return(f & (1<<a));}

void setBit(uint8_t &f,uint8_t a)
{f=f | (1<<a);}

void clrBit(uint8_t &f,uint8_t a)
{f=f & (~(1<<a)); }


void (*zeroFunc)(void) =0;

void about()
{pr("mvirt enviroment version ");
prln(OS_VERSION);}



extern "C" int SPSR_REGISTER();
extern "C" int CPU_MODE();
void processor_state()
{printd("PROCESSOR STATE: ");dln;
printd("CPSR:\t");debug_serial_printhex_int(PROCESSOR->CPSR);dln
printd("SPSR:\t");debug_serial_printhex_int(PROCESSOR->SPSR);dln
printd("R0:\t");debug_serial_printhex_int(PROCESSOR->R[0]);dln
printd("R1:\t");debug_serial_printhex_int(PROCESSOR->R[1]);dln
printd("R2:\t");debug_serial_printhex_int(PROCESSOR->R[2]);dln
printd("R3:\t");debug_serial_printhex_int(PROCESSOR->R[3]);dln
printd("R4:\t");debug_serial_printhex_int(PROCESSOR->R[4]);dln
printd("R5:\t");debug_serial_printhex_int(PROCESSOR->R[5]);dln
printd("R6:\t");debug_serial_printhex_int(PROCESSOR->R[6]);dln
printd("R7:\t");debug_serial_printhex_int(PROCESSOR->R[7]);dln
printd("R8:\t");debug_serial_printhex_int(PROCESSOR->R[8]);dln
printd("R9:\t");debug_serial_printhex_int(PROCESSOR->R[9]);dln
printd("R10:\t");debug_serial_printhex_int(PROCESSOR->R[10]);dln
printd("R11|FP:\t");debug_serial_printhex_int(PROCESSOR->R[11]);dln
printd("R12:\t");debug_serial_printhex_int(PROCESSOR->R[12]);dln
printd("SP:\t");debug_serial_printhex_int(PROCESSOR->SP);dln
printd("LR:\t");debug_serial_printhex_int(PROCESSOR->LR);dln
printd("PC:\t");debug_serial_printhex_int(PROCESSOR->PC);dln
}

PROCESSOR_t *PROCESSOR;
#include "interrupts.h"

#define SYSERRORLEDPERIOD 100
volatile void systemError_h(const char * c) 
{//asm("mov r0,lr");
printd(c);
IRQ_D();
FIQ_D();
while(1)	
{	
	red_led_on();	
	delay_cpu(SYSERRORLEDPERIOD);	
	red_led_off();	
	delay_cpu(SYSERRORLEDPERIOD);	
}
}	

