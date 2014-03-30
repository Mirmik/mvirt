#ifndef COMMAND_LIST_H
#define COMMAND_LIST_H

#include "mvirt.h"

 extern list_head command_head;
  
 struct command_t
 {
char* mnem; 
list_head list;
size_t func;
 };
 
  void command_add (char* a, size_t c);
 void command_print();
 
class list_t 
{public:
char* mnem; 
list_head list;
size_t address;
size_t type;
};



#endif
