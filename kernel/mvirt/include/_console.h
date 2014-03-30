#ifndef _CONSOLE_H
#define _CONSOLE_H

#include "mvirt.h"

#define CONSOLE_BUFFER_SIZE 50

#define SUID 56
#define STANDBY 0
#define STOPBYTEFL 1
#define NOANSWER 7
#define ESCAPE_SEQUENSE 6
#define ESCAPE 5
#define SUPERUSER 3
#define USEANSW 4


class Console{
public:
uint8_t f_INT;
Console(Stream* _strm =(Stream*) stdio);
void listen();
command_t* interpreter(char* buffer);
//char* mach_name;
void on_console_new_listen();
uint8_t mode;
uint8_t now;
uint8_t last;
Stream *strm;
//vnode* nowNode;
char buffer[CONSOLE_BUFFER_SIZE];
//void addrestimate();
//void NoAnswer();
};




#endif
