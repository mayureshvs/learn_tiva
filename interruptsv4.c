/*
 * uart_interrupt.c
 *
 *  Created on: 29-May-2019
 *      Author: Mayuresh
 */
#include "stdint.h"
#include "stdbool.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_gpio.h"
#include "inc/hw_ints.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/uart.h"
#include "driverlib/pin_map.h"
#include "driverlib/interrupt.h"
uint32_t c=0;
char request[25];
int i=0, turn=0;
bool state1=0,state2=0,state;

void ISR(void)
{
        request[i]=UARTCharGetNonBlocking(UART0_BASE);
        i++;
        state=1;        //to check some data is recieved
}


int main()
{
    //uint32_t *i=0,*j=0;

    int k=0;
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE,GPIO_PIN_0 | GPIO_PIN_1);
    UARTConfigSetExpClk(UART0_BASE,SysCtlClockGet(), 9600,(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
    IntMasterEnable();
   // IntEnable(INT_UART0);
    UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);
    //IntRegister(INT_UART0,ISR);                             //ISR is a name of function used as interrupt handler
    //UARTIntRegister(UART0_BASE, ISR);
    UARTFIFODisable(UART0_BASE);
    UARTFIFOEnable(UART0_BASE);
    UARTFIFOLevelSet(UART0_BASE,UART_FIFO_TX4_8,UART_FIFO_RX4_8);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
    //UARTFIFOLevelGet(UART0_BASE,i,j);
    while(1)
    {
    while(state)
        {
        for( k=0;k<25;k++)
        {
            if(request[k]=='R' || request[k]=='G' || request[k]=='B')
                    {
                        c=request[k];
                        state1=~state1;
                        break;
                    }
        }
        for(k=0;k<25;k++)
                {
                    if(request[k]=='o')
                            {
                                if (request[++k]=='n')
                                {
                                    turn = 0xFF;          // turn on
                                    state2=~state2;
                                    break;
                                }
                                else if(request[++k]=='f')
                                    turn = 0x00;           //turn off
                                    state2=~state2;
                                    break;
                            }
                }
        if(!(state1^state2))
        {
           // turn_led(c,turn);
            switch(c)
                {
                case 'R':
                    GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1,turn);
                    i=0;
                    break;
                case 'G':
                    GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_2,turn);
                    i=0;
                    break;
                case 'B':
                    GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3,turn);
                    i=0;
                     break;

                }
        }
        //GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3,0xFF);
       //SysCtlDelay(1000000);


    }
    state=0;
    }
}


