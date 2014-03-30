

#include "mvirt/Serial.h"
HARD_Serial_t Serial0(UART0,48,88);

void ISR_UART0(){
uart0_irq++;
if (Serial0.tx->head==Serial0.tx->tail) Serial0.tx->transmitting=0;
else Serial0.send();
IRQ_FLAG_REMOVE(UART0INT);
return;
};


size_t HARD_Serial_t::write(uint8_t c)
{
size_t i = (tx->head + 1) % tx->size;
  while (i == tx->tail) return(-1);
  tx->buffer[tx->head] = c;
  tx->head = i;
  if (transmitting==0 && ((UART0->LSR) & (1<<5))) send();
}

void HARD_Serial_t::send()
{tx->transmitting=1;
char c = tx->buffer[tx->tail];
tx->tail = (tx->tail+1) % tx->size; 
uart->THR = c; }


int HARD_Serial_t::available(void)
{
	return((tx->head - tx->tail + tx->size) % tx->size);
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
{/*switch (streamType){
   case SERIALTYPE: return(((HardwareSerial2*)SSpointer)->peek());
   default: {*/
//  if (_rx_buffer->head == _rx_buffer->tail) {
//    return -1;
//  } else {
//    return _rx_buffer->buffer[_rx_buffer->tail];
//  }
}

int HARD_Serial_t::read(void)
{ /* switch (streamType){
   case SERIALTYPE: return(((HardwareSerial2*)SSpointer)->read());
   default: {*/
//  if (_rx_buffer->head == _rx_buffer->tail) {
//    return -1;
//  } else {
//    unsigned char c = _rx_buffer->buffer[_rx_buffer->tail];
//    _rx_buffer->tail = (unsigned int)(_rx_buffer->tail + 1) % _rx_buffer->size;
//    return c;
//  }
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




