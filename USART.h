#include <util/delay.h>
#include "macro.h"
void uart_init()
{
	// SETTING BIT PARITY (8BIT OR 9 BIT)
UCSRC=(1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0);	//8 BIT

 //FOR TX AND RX
UCSRB=(1<<RXEN)|(1<<TXEN);// ENABLING TX,RX.  

UBRRL=0x33; // baud rate(51 for 9600)
}

void tx_data(unsigned char c)
{
//SENDING DATA;
UDR=c;
while(!(UCSRA & (1<<TXC)));  //set the TX flag
//clear the TX flag
UCSRA=(1<<TXC);
}

unsigned char rx_data()
{

// Wait for data to be received 
while ( !(UCSRA & (1<<RXC)) && (get_bit(PINC,0)==0) && (get_bit(PINC,2)==0)  && (get_bit(PINC,1)==0) && get_bit(PINC,3)==0); // set the rx flag
UCSRA=(0<<RXC);// CLEAR THE rx flag
/* Get and return received data from buffer */
return UDR;
}

unsigned char rx_dat()
{

// Wait for data to be received 
while ( !(UCSRA & (1<<RXC)) && (get_bit(PINC,0)==0) /*&& (get_bit(PINC,2)==1)*/); // set the rx flag
UCSRA=(0<<RXC);// CLEAR THE rx flag
/* Get and return received data from buffer */
return UDR;
}



void Tx_String(unsigned char *str)
{
	while(*str)
	{
		tx_data(*str);
		str++;
		_delay_ms(100);
	}
	
}