#ifndef UART_INIT
#define UART_INIT
#include<math.h>
#include<avr/io.h>

#define F_CPU 12000000
#define EVEN_PARITY 0
#define ODD_PARITY  1
#define DOUBLE_SPEED 1
#define NO_DOUBLE_SPEED 0
#define BIT_SIZE_5 5
#define BIT_SIZE_6 6
#define BIT_SIZE_7 7
#define BIT_SIZE_8 8
#define BIT_SIZE_9 9
#define STOP_BIT_1 1
#define STOP_BIT_2 2
#define INTERUPPT_ENABLE 0
#define INTERUPPT_DISABLE 1

/*
unsigned char RecieveUART0(void){
	while(!(UCSR0A &(1<<RXC0)));
	return UDR0;
}
*/
void TransmitUART0(int data){
	while(!(UCSR0A &(1<<UDRE0)));
	UDR0=data;
}

void IntializeUART0(int baud,char AsyncDoubleSPeed,char DatasizeInBits, char ParityEVENorODD, char stopBits,char USARTInterruptEnable){

	uint16_t UBBRValue=lrint(((((F_CPU/16)+(baud/2)) /(baud))-1));
	
	//(((( F_CPU / 16) + ( USART_BAUDRATE / 2)) / ( USART_BAUDRATE )) - 1)

	if(AsyncDoubleSPeed==DOUBLE_SPEED) { UCSR0A |=(1<<U2X0);}

	//Put the upper part of the baud number here (bits 8 to 11)
	UBRR0H = (unsigned char) (UBBRValue >> 8);

	//Put the remaining part of the baud number here
	UBRR0L = (unsigned char) UBBRValue;

	//Enable the receiver and transmitter
	UCSR0B |= (1 << RXEN0) | (1 << TXEN0);

	//Interuptt Enable
	if(USARTInterruptEnable==INTERUPPT_ENABLE) UCSR0B|=(1<<RXCIE0);
	
	//Set 2 stop bits 
	if(stopBits==STOP_BIT_2) {UCSR0C|=(1<<USBS0);}

	if(ParityEVENorODD==EVEN_PARITY){UCSR0C |= (1 << UPM01);}
	if(ParityEVENorODD==ODD_PARITY){UCSR0C |= (3 << UPM00);}

	if(DatasizeInBits==BIT_SIZE_6) UCSR0C |= (1 << UCSZ00); //6-bit data length
	if(DatasizeInBits==BIT_SIZE_7) UCSR0C |= (1 << UCSZ01); //7-bit data length, or
	if(DatasizeInBits==BIT_SIZE_8) UCSR0C |= (1 << UCSZ01)|(1 << UCSZ00); //8-bit data length, or
	if(DatasizeInBits==BIT_SIZE_9) UCSR0C |= (1 << UCSZ02)|(1 << UCSZ01)|(1 << UCSZ00); ; //8-bit data length, or

}
#endif
