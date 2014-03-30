

#include "mvirt/Serial.h"
HARD_Serial_t Serial0(UART0,100,100);

uint32_t uart0_irq_ls=0,uart0_irq_rx=0,uart0_irq_tx=0;


void ISR_UART0(){
uart0_irq++;
green_led_on();
uint32_t temp;
while(1){
temp=(Serial0.uart->IIR);
if (temp & 1) break;
temp =(temp >> 1) & 3;
//do{
switch(temp){
	case 3: uart0_irq_ls++;break;
	case 2: uart0_irq_rx++;Serial0.receive();break;
	case 1: uart0_irq_tx++;
	if (Serial0.tx->head!=Serial0.tx->tail) Serial0.send();
	break;
	case 0:break;
}

}
green_led_off();
IRQ_FLAG_REMOVE(UART0INT);
return;
};

HARD_Serial_t::HARD_Serial_t(DEVICE_UartRegs* p, uint32_t tx_size,uint32_t rx_size) {
	

	printd("Serial constructor");dln; delay_cpu(10);
	
	uart = p; 

tx = new  ring_buffer(tx_size); 	
rx = new  ring_buffer(rx_size); 	
transmitting=0;

};
HARD_Serial_t::HARD_Serial_t(){dln;
	printd("Serial constructor2"); delay_cpu(10);};


size_t HARD_Serial_t::write(uint8_t c)
{
size_t i = (tx->head + 1) % tx->size;
  while (i == tx->tail) return(-1);
  tx->buffer[tx->head] = c;
  tx->head = i;
  if ( ((uart->IIR & 1)) && ((uart->LSR) & (1<<5))) send();
}

void HARD_Serial_t::send()
{char c = tx->buffer[tx->tail];
tx->tail = (tx->tail+1) % tx->size; 
uart->THR = c; }



void HARD_Serial_t::receive()
{
rx->buffer[rx->head] = uart->RBR;
rx->head = (rx->head+1) % rx->size;}



int HARD_Serial_t::available(void)
{
	return((rx->head - rx->tail + rx->size) % rx->size);
}


void HARD_Serial_t::begin(uint32_t baud)
{
uint32_t a = OSCILATOR_FREQUENCY / baud / 16;  
uart->DLL = a & 0xFF;               // Set baud rate	
uart->DLH = (a>>8) & 0xFF;
expanded_interrupt_attach(0x80, UART0INT, (int)ISR_UART0);
interrupt_enable(UART0INT);
}



int HARD_Serial_t::peek(void)
{if (available()) return(rx->buffer[rx->tail]);
	else return(-1);
}

int HARD_Serial_t::read(void)
{ if (rx->tail != rx->head){
char c =rx->buffer[rx->tail];
rx->tail=(rx->tail+1)%rx->size;	
return (c);	
}
	else return -1;
	
}

/*
char Serial::tx_read(void)
{ 
//  if (_tx_buffer->head == _tx_buffer->tail) {
//    return -1;
//  } else {
//    unsigned char c = _tx_buffer->buffer[_tx_buffer->tail];
//    _tx_buffer->tail = (unsigned int)(_tx_buffer->tail + 1) % _rx_buffer->size;
//    return c;
//  }
}*/

void HARD_Serial_t::flush()
{ /*switch (streamType){
   case SERIALTYPE: return(((HardwareSerial2*)SSpointer)->flush());
   default:;*/}

/*
ShellStream::ShellStream(const ShellStream &shstr)
{connectTo(shstr);}
*/

/*
void ShellStream::connectTo(const ShellStream &shstr){

_rx_buffer=shstr._tx_buffer;
_tx_buffer=shstr._rx_buffer;
}
}

*/




