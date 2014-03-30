
#include "hardware.h"
#include "mvirt/Debug.h"

Debug_t Debug;
Stream * stdio=(Stream*)(&Debug);


size_t Debug_t::write(uint8_t c)
{
 UART0->THR=c;
 while(((UART0->LSR) & (1<<5)) ==0);
}
