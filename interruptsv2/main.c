
/*
 * sarode.c
 *
 *  Created on: 31-May-2019
 *      Author: Mayuresh
*/

#include<stdint.h>
#include<stdbool.h>
#include"inc/hw_memmap.h"
#include"inc/hw_types.h"
#include"inc/hw_sysctl.h"
#include"inc/hw_gpio.h"
#include "inc/hw_ints.h"
#include"driverlib/sysctl.h"
#include"driverlib/gpio.h"
#include"driverlib/uart.h"
#include"driverlib/pin_map.h"
#include "driverlib/interrupt.h"

char k;
void UARTIntHandler(void)
{
    k=UARTCharGetNonBlocking(UART0_BASE);
    if(k=='R'){
        k = GPIO_PIN_1;
    }
    else if(k=='G'){
        k = GPIO_PIN_3;
    }
    else{
        k = GPIO_PIN_2;
    }
    //UARTCharPut(UART0_BASE,k);

}

int main(void)
R{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE,GPIO_PIN_0 | GPIO_PIN_1);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
    UARTConfigSetExpClk(UART0_BASE,SysCtlClockGet(), 9600,(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
    IntMasterEnable();
    IntEnable(INT_UART0);
    UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);

    while(1){
        GPIOPinWrite(GPIO_PORTF_BASE,k,0XFF);
        SysCtlDelay(1000000);
        GPIOPinWrite(GPIO_PORTF_BASE,k,0X00);
        SysCtlDelay(1000000);

    }
    return 0;
}
