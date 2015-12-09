#ifndef UART_INIT
#define UART_INIT
#include<math.h>
#include<avr/io.h>

#define F_CPU 12000000
#define EVEN 0
#define ODD  1

unsigned char RecieveUART0(void){
	while(!(UCSR0A &(1<<RXC0)));
	return UDR0;
}

void TransmitUART0(unsigned char data){
	while(!(UCSR0A &(1<<UDRE0)));
	UDR0=data;
}

void IntializeUART0(int Baud,char AsyncDoubleSpeed,char DatasizeInBits,char ParityEVENorODD,char stopBits){
    //Closest match i.e. lrint
	uint16_t UBBRValue=lrint((F_CPU /(16L*Baud)-1));

	// Double Speed
	if(AsyncDoubleSpeed==1)  UCSR0A |=(1<<U2X0);

	//Put the upper part of the baud number here (bits 8 to 11)
	UBRR0H = (unsigned char) (UBBRValue >> 8);
	//Put the remaining part of the baud number here
	UBRR0L = (unsigned char) UBBRValue;

	//Enable the receiver and transmitter
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);

	//Set 2 stop bits and data bit length is 8-bit
	if(stopBits==2) UCSR0C|=(1<<USBS0);

	if(ParityEVENorODD==EVEN) UCSR0C |= (1 << UPM01);
	if(ParityEVENorODD==ODD)  UCSR0C |= ((1 << UPM00)|(1 << UPM01));

	if(DatasizeInBits==6) UCSR0C |= (1 << UCSZ00); //6-bit data length
	if(DatasizeInBits==7) UCSR0C |= (1 << UCSZ01); //7-bit data length, or
	if(DatasizeInBits==8) UCSR0C |= (1 << UCSZ01)|(1 << UCSZ00); //8-bit data length, or
	if(DatasizeInBits==9) UCSR0C |= (1 << UCSZ02)|(1 << UCSZ01)|(1 << UCSZ00); ; //8-bit data length, or

}
#endif

