

#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include "types.h"


class ring_buffer
{
public:
ring_buffer(size_t a);
char* buffer;
byte tail;
byte head;
byte size;
byte transmitting;
};




#endif
