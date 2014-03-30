
#include "mvirt.h"

void OS_config()
{
Serial0.begin(115200);
stdio=&Serial0;
delay(20);
}

void hmain(void)
{
about();
OS_config();
setup();
while(1) loop();

systemError("MAIN FUNCTION END. Kernel bewilderment :)");
}


