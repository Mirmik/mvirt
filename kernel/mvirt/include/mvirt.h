#ifndef MVIRT_H
#define MVIRT_H

#include "classlist.h"
#include "malloc.h"

extern Stream* stdio;
extern Debug_t Debug;

#define OSCILATOR_FREQUENCY 24000000

#define command(a,b) command_add(a,(size_t)b)
#define ds(a)  debug_serial_putchar(a)

#define kmalloc malloc
#define kfree free

#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
#include <inttypes.h>

void setup();
void loop();

extern uint32_t uart0_irq,timer1_irq,timer0_irq;

/*
 * container_of - cast a member of a structure out to the containing structure
 * @ptr:	the pointer to the member.
 * @type:	the type of the container struct this is embedded in.
 * @member:	the name of the member within the struct.
 *
 */
#define container_of(ptr, type, member) ({			\
	const typeof( ((type *)0)->member ) *__mptr = (ptr);	\
	(type *)( (char *)__mptr - offsetof(type,member) );})
//#include "_syslist.h"


#include "debug_serial.h"
#include "types.h"
#include "linuxlist.h"
#include "hardware.h"

#include "mvirt/time.h"
#include "mvirt/delay.h"
#include "mvirt/init.h"
#include "simple.h"
#include "virtboard.h"
#include "string.h"
#include "interrupts.h"
#include "command_list.h"
#include "csh.h"

#include "mvirt/Stream.h"
#include "_console.h"

#include "mvirt/Debug.h"
#include "mvirt/Serial.h"
extern uint32_t timer0_irq;

#define MACHINE_NAME "virt2real-mvirt"
#define OS_VERSION "0.3"


static void DoNothing(){};







#endif
