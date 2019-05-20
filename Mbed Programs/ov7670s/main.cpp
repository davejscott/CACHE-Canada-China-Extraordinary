#include <stdio.h>
#include "mbed.h"
#include "ov7670sreg.h"
#include "ov7670s.h"
#include "FastPWM.h"

Serial pc(USBTX, USBRX);
/*#if defined(TARGET_WIZwiki_W7500)
    OV7670 s(A4,A5,D11,PortC,8,D1);
    
#endif*/
OV7670 s(PB_3,PB_10,PA_10,PortC,8,PB_12);

int main()
{
    pc.baud(115200);
    s.Init("BAW",19200);
    
    
 }