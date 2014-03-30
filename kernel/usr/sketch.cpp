#include "mvirt.h"

//FATFS *fs;
//extern SDMMC_InfoHandle hSDMMCInfo;
//int i=0;


int a=0;

char c;

void idle(){
if (Serial0.available()) {c=(char)(Serial0.read());};};

CSH_t SH(idle,64,64);

void blink ()
{a=(a+1)%2;
if (a==1) {red_led_on();//green_led_off();
	}
else   {red_led_off();//green_led_on();
	}
}
void task1(){

prln(uart0_irq);
prln(uart0_irq_rx);
prln(uart0_irq_tx);
prln(uart0_irq_ls);
prln(Serial0.peek());
prln(c);
	}


extern unsigned long _bss_start;
extern unsigned long _bss_end;
int temp=1;

void setup ()
{stdio=&Serial0;
//Serial0.print("OHAYO GODZAIMASHITA!!!");

temp=millis()%3+1;

prlnhex(&_bss_end);
prlnhex(&_bss_start);

prln("MIRMIK WAS HERE!!!");	
SH.newTimer(task1,100,REPEAT);	
	
SH.newTimer(blink,1000,REPEAT);	
};

void loop ()
{
SH.start();
};
