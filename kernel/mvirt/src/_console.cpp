




#include "_console.h"

Console::Console(Stream* _strm)
{
mode=0xFF;
now=0;
last=0;
strm=_strm;
//mach_name = (char*)OS_MACHNAME;
}


void Console::on_console_new_listen()
{
strm->print(MACHINE_NAME);strm->print(':');	
}



void Console::listen()
{

	if (mode==0xFF) {on_console_new_listen();						//new listen
	last=0;
	now=0;
	mode=0;
	}
	

  while (strm->available()!=0) 
	{
		char inChar=strm->read();
		switch ( mode)
	{
		
	case 0:
		//Standart mode
		switch (inChar){
		//Control symbols.
		case 0x0A: goto ex;												//LN line
		case 0x0D: if (!statusBit(f_INT,NOANSWER)){ strm->print("\n\r");}; buffer[ last+1]=0x00; goto startint;					//CR carriage return
		case 0x08: 	if ( now > 0) { now--; last--;}    goto ex;													//BS backspase
		case 0x7F: if ( now > 0) { now--; last--;goto print;}    goto ex;	 //BS backspase
		case 0x1B:  mode=1;goto print;							 //ESC mode
		//Printable Symbole
		default: 
		{if ( last<CONSOLE_BUFFER_SIZE) 
		{
		if ( last!= now)                //If symb is not last
			{strm->print("\e[1@"); 										//Past symbol in term
			for (int i= last;i>= now;i--) buffer[i+1]= buffer[i]; //Past symbol in console
			}
		 buffer[ now]=inChar; now++;  last++;goto print;
		}}
		break;}
	case 1:
	
		//ESC mode
		switch (inChar){
		case '[':  mode=2;goto print; 
		default:  mode=0; goto print;
		}
	
	
	case 2: 
	
		//ESC_SEQUENCE mode;
		{
		if (inChar=='A') { mode=0;strm->print("1@");goto ex;};
		if (inChar=='B') { mode=0;strm->print("2J");goto ex;};
		if (inChar=='C') { mode=0;if ( now <  last){ now++;goto print;} strm->write(0x18); goto ex;};
		if (inChar=='D') { mode=0;if ( now > 0) 		  { now--;goto print;} strm->write(0x18); goto ex;};
		 mode=0;
		break;
		}
		
		
		case 3: //debugMode
		
			prhex(inChar);prln();
		if (inChar==0x03) {mode=0xFF; strm->print("debug mode off");}goto ex;
		
		
	}
	print:
	//prhex (inChar) tab
if (!statusBit(f_INT,NOANSWER)){ 	strm->write(inChar); }
	//prln()
	ex:

;	
	
	}
	
  return;


startint:


 mode=0xFF;
 buffer[ last] = 0x00;

if ((size_t)interpreter(buffer)==0){
if (!statusBit(f_INT,NOANSWER)){ 
strm->print("unregistred command: '");
strm->print( buffer);
strm->println("'. Use 'list' command to see comand list.\r");} 
}

}



command_t* Console::interpreter(char* buffer)
{Stream* tempstrm;
command_t *p=0;
char *c=buffer,*d;
CUT_FIRST_OPERAND(c,d);
list_for_each_entry(p,&command_head,list)
{if (!strcmp(c,p->mnem)) goto execute;}
p=0;
goto ex;
execute:
//tempstrm=strmout;
//strmout=strm;
((void (*) (char*,Console*))(p->func))(d,this);
//strmout=tempstrm;

ex: return(p);
}
	
