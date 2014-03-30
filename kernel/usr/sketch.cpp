#include "mvirt.h"

//FATFS *fs;
//extern SDMMC_InfoHandle hSDMMCInfo;
//int i=0;


int a=0;


void idle(){};

CSH_t SH(idle,64,64);

void blink ()
{a=(a+1)%2;
if (a==1) {red_led_on();green_led_off();}
else   {red_led_off();green_led_on();}
}

void setup ()
{
	
Serial0.print("OHAYO GODZAIMASHITA!!!");
prln("MIRMIK WAS HERE!!!");	
	
SH.newTimer(blink,1000,REPEAT);	
};

void loop ()
{
SH.start();
};
