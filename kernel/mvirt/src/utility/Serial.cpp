

#include "mvirt/Serial.h"
HARD_Serial_t Serial0(UART0,500,500);

uint32_t uart0_irq_ls=0,uart0_irq_rx=0,uart0_irq_tx=0;


void ISR_UART0(){
int c;
//green_led_on();
uart0_irq++;
uint32_t temp;
while(1){
temp=(Serial0.uart->IIR);
if (temp & 1) break;
temp =(temp >> 1) & 3;
//do{
switch(temp){
	case 3: uart0_irq_ls++; printd("ls_UART_INT"); while(1);break;
	case 2: uart0_irq_rx++; Serial0.rx->store(Serial0.receive());break;
	case 1: uart0_irq_tx++;  
	break;
	case 0:break;
}
Serial0.send();

}
IRQ_FLAG_REMOVE(UART0INT);
//green_led_off();
return;
};

HARD_Serial_t::HARD_Serial_t(DEVICE_UartRegs* p, uint32_t tx_size,uint32_t rx_size) {
	

	printd("Serial constructor");dln; delay_cpu(10);
	
	uart = p; 

tx = new  ring_buffer(tx_size); 	
rx = new  ring_buffer(rx_size); 	

};
HARD_Serial_t::HARD_Serial_t(){dln;
	printd("Serial constructor2"); delay_cpu(10);};


size_t HARD_Serial_t::write(uint8_t c)
{
	 while (!(tx->store(c)));
send();
return 1;
}

bool HARD_Serial_t::send()
{	if (uart-> LSR & (1<<5)){
	int c = tx->take(); 
	if (c!=-1)	{uart->THR=c;
	return 1; }
	else return 0;}
	else return 0;}



inline char HARD_Serial_t::receive()
{return(uart->RBR);}



int HARD_Serial_t::available(void)
{
	return(rx->available());
}


void HARD_Serial_t::begin(uint32_t baud)
{
//uint32_t a = OSCILATOR_FREQUENCY / baud / 16;  
//uart->MDR = 0x0;
//uart->DLL = a & 0xFF;               // Set baud rate	
//uart->DLH = (a>>8) & 0xFF;
expanded_interrupt_attach(0x80, UART0INT, (int)ISR_UART0);
interrupt_enable(UART0INT);
}

void HARD_Serial_t::end()
{
interrupt_disable(UART0INT);
}


int HARD_Serial_t::peek(void)
{//if (available()) return(rx->buffer[rx->tail]);
	//else return(-1);
}

int HARD_Serial_t::read(void)
{return (rx->take());	
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




