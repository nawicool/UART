#define F_CPU 18432000UL

#include<avr/io.h>
#include"UARTINTERRUPT.h"
#include<avr/interrupt>
#include<util/delay.h>
volatile unsigned char recievedByte;
int main(void){
	
	DDRB|=1<<PINB0;
	InitializeUART0(9600,0,8,NONE,1,TRUE);
	sei();
	while(1){
		_delay_ms(500);
		TransmitUART0('a');
	}
	
	
}
ISR(USART0_RX_vect){
	
	recievedByte=UDR0;
	PORTB^=(1<<PINB0)
	
}
