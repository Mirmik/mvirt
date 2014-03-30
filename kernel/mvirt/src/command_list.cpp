

#include "command_list.h"


LIST_HEAD (command_head);

 void command_add (char* a,size_t c)
 {command_t* temp=new(command_t);
 list_add_tail(&temp->list,&command_head);
 temp->mnem=a;
 temp->func=c;
 }


void command_print()
{list_t* p;
list_for_each_entry(p,&command_head,list)
{
pr(p->mnem); 
prln();
};
};

