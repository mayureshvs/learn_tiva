/**
 * main.c
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

    SysCtlPeripheralEnable(GPIO_PORTA_BASE);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    UARTEnable(UART0_BASE);
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    UARTEnable(UART0_BASE);
    GPIOPinTypeUART(GPIO_PORTA_BASE,GPIO_PIN_0 | GPIO_PIN_1);
    UARTConfigSetExpClk(UART0_BASE,SysCtlClockGet(), 9600,(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));


    if(UARTCharsAvail(GPIO_PORTA_BASE))
    {
       k=UARTCharGetNonBlocking(GPIO_PORTA_BASE);
       UARTCharPut(GPIO_PORTA_BASE,k);
    }
    return 0;
}
