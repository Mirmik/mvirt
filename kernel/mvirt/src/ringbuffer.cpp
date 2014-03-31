


#include "mvirt.h"


ring_buffer::ring_buffer(size_t sz)
{	printd("ring_buffer constructor\r\n");
	size=sz;
	buffer=(char*)kmalloc(sz);
	tail=0;
	head=0;
}


int ring_buffer::take()
{
 // ds('b');
if (head == tail) return -1;
char c = buffer[tail];
tail = (tail + 1) % size;
return c;

}

int ring_buffer::store(char c)
{
size_t i;
i = (head + 1) % size;
  
  //ds('a');
  
  if (i == tail) return(0);
  
  buffer[head] = c;
  head = i;
return 1;
}


int ring_buffer::available()
{
return((head-tail+size)%size);	
}
