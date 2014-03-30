#ifndef DEBUG_H
#define DEBUG_H


#include "mvirt/Stream.h"
#include "types.h"
class Debug_t : public Stream
{
size_t write(uint8_t c);
 int available(){return 0;};
 int read(){return -1;};
 int peek(){return -1;};
 void flush(){};

	
   using Stream::write; // pull in write(str) and write(buf, size) from Print
   operator bool() { return true; }

};



#endif
