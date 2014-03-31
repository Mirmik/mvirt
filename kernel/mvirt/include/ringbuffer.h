

#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include "types.h"


class ring_buffer
{
	
public:
size_t tail;
size_t head;
size_t size;
char* buffer;
ring_buffer(size_t a);
int available();
int store(char c);
int take();
};




#endif
