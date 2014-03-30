


#include "mvirt.h"


ring_buffer::ring_buffer(size_t sz)
{	size=sz;
	buffer=(char*)kmalloc(sz);
	tail=0;
	head=0;
}
