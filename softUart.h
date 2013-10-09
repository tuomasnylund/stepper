#ifndef _SOFTUART_H_
#define _SOFTUART_H_

#define UART_RX_PORT PORTB
#define UART_RX_DDR  DDRB
#define UART_RX_PIN  PINB
#define UART_RX_BIT  PB4

#define RX_STATE()   (UART_RX_PIN & (1<<UART_RX_BIT))

/* 0,1,2,3,4,5,6,7 */

typedef enum
{
    WAIT_FOR_START_BIT,
    BYTE,
    STOP_BIT
} E_softUartStates;

void    softUartInit(void);
uint8_t softUartNewChar(void);
uint8_t softUartGetChar(void);

#endif /* _SOFTUART_H_ */
