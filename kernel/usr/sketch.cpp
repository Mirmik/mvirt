#include "mvirt.h"

//FATFS *fs;
//extern SDMMC_InfoHandle hSDMMCInfo;
//int i=0;


int a=0;

char c;

Console cons(&Serial0);

void idle(){
cons.listen();
};

CSH_t SH(idle,64,64);


void blink2 ()
{static int b;
	b=(b+1)%2;
if (b==1) {green_led_on();//green_led_off();
	}
else   {green_led_off();//green_led_on();
	}
}

void blink ()
{a=(a+1)%2;
if (a==1) {red_led_on();//green_led_off();
	}
else   {red_led_off();//green_led_on();
	}
}
void task1(){
//prln(uart0_irq);
//prln(uart0_irq_rx);

	}


extern unsigned long _bss_start;
extern unsigned long _bss_end;
int temp=1;

void setup ()
{stdio=&Serial0;
	//UART0->IER=7;
//Serial0.print("OHAYO GODZAIMASHITA!!!");
command("about",about);
command("blink",blink2);
command("task1",task1);
command("list",command_print);
prln("MirmikMirmikMirmik");
SH.newTimer(task1,100,REPEAT);	
	
//Serial0.end();	
//while(1);	
SH.newTimer(blink,1000,REPEAT);	
};

void loop ()
{
SH.start();
};
