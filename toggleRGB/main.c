/*
 * sarode.c
 *
 *  Created on: 27-May-2019
 *      Author: Mayuresh
 */

/*
 * sarode.c
 *
 *  Created on: 27-May-2019
 *      Author: Mayuresh
 */

#include<stdint.h>
#include<stdbool.h>
#include"inc/hw_memmap.h"
#include"inc/hw_types.h"
#include"inc/hw_sysctl.h"
#include"inc/hw_gpio.h"
#include"driverlib/sysctl.h"
#include"driverlib/gpio.h"
#include"driverlib/uart.h"
#include"driverlib/pin_map.h"

int main(void)
{
    int k=1,d=0x00;
    //SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    //SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    //GPIOPinConfigure(GPIO_PA0_U0RX);
    //GPIOPinConfigure(GPIO_PA1_U0TX);
    //GPIOPinTypeUART(GPIO_PORTA_BASE,GPIO_PIN_0 | GPIO_PIN_1);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE,GPIO_PIN_4);
    GPIOPadConfigSet(GPIO_PORTF_BASE,GPIO_PIN_4,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);
    //UARTEnable(UART0_BASE);
    //UARTClockSourceSet(UART0_BASE,UART_CLOCK_SYSTEM);s
    //UARTConfigSetExpClk(UART0_BASE,SysCtlClockGet(), 9600,(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
while(1)
{
    if(k!=(bool)GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_4))
    {
       //k=UARTCharGetNonBlocking(UART0_BASE);
       //UARTCharPut(UART0_BASE,k);
        k=(bool)GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_4);
        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3,d);    //toggle
        d=~d;
        SysCtlDelay(1000);
        //d=~d;


    }

}

}
