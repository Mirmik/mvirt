
#include "mvirt/init.h"
#include "simple.h"
// BEGIN C++ support (1/2)
extern unsigned long __preinit_array_start;
extern unsigned long __preinit_array_end;
extern unsigned long __init_array_start;
extern unsigned long __init_array_end;
extern unsigned long _ctor_start;
extern unsigned long _ctor_end;
extern unsigned long __fini_array_start;
extern unsigned long __fini_array_end;

static void call_constructors(unsigned long *start, unsigned long *end) __attribute__((noinline));
static void call_constructors(unsigned long *start, unsigned long *end)
{
  unsigned long *i;
  void (*funcptr)();
  for ( i = start; i < end; i++)
  {
    funcptr=(void (*)())(*i);
    funcptr();
  }
}
// END C++ support (1/2)

extern void hmain();

extern "C" void boot2(){

// BEGIN C++ support (2/2)
  //Call C++ global constructors
  call_constructors(&__preinit_array_start, &__preinit_array_end);
  call_constructors(&__init_array_start, &__init_array_end);
  call_constructors(&_ctor_start, &_ctor_end);
  // END C++ support (2/2)

	second_init();
	drivers_init();
	hmain();
	
	systemError("MAIN FUNCTION END. Kernel bewilderment :)");	
}
