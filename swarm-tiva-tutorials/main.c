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
    char k;
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE,GPIO_PIN_0 | GPIO_PIN_1);
    UARTEnable(UART0_BASE);
    UARTConfigSetExpClk(UART0_BASE,SysCtlClockGet(), 9600,(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
while(1)
{
    if(UARTCharsAvail((UART0_BASE)))
    {
       k=UARTCharGetNonBlocking(UART0_BASE);
       UARTCharPut(UART0_BASE,k);
    }

}
    return 0;
}
