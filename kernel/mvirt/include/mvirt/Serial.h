
#ifndef SERIAL_H
#define SERIAL_H

#include "mvirt.h"
#include "ringbuffer.h"

void ISR_UART0()__attribute__((uses));

extern uint32_t uart0_irq_ls,uart0_irq_rx,uart0_irq_tx;

extern HARD_Serial_t Serial0;

class HARD_Serial_t : public Stream
{
	public:
	DEVICE_UartRegs* uart; 
	
HARD_Serial_t(DEVICE_UartRegs* p, uint32_t tx_size,uint32_t rx_size);
HARD_Serial_t();
	
ring_buffer *tx; 	
ring_buffer *rx;		
void begin();

size_t write(uint8_t c);
 int available();
 int read();
 int peek();
 void flush();
 
 
void end();
bool send();
inline char receive();
 
void begin(uint32_t baud);
boolean transmitting;

	
 using Stream::write; // pull in write(str) and write(buf, size) from Print
 operator bool() { return true; }

};




#endif
