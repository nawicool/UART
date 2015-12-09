#include "header.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int main(){
	int revieved_byte=1;
	
	DDRC|=(1<<PINC7);
	PORTC&=~(1<<PINC7);
	
	IntializeUART0(9600,NO_DOUBLE_SPEED, BIT_SIZE_8,EVEN_PARITY,STOP_BIT_2,INTERUPPT_ENABLE);
	sei();
	while(1){		
	TransmitUART0(revieved_byte);
	revieved_byte=revieved_byte+1;
	if(revieved_byte>255) revieved_byte=1;
	_delay_ms(20); 
	
	}
	return 0;
}
 
 ISR (USART0_RX_vect){
	 int recieved_lokal;
	 recieved_lokal=UDR0; //empfangenes Datenbyte abspeichern
	 if(recieved_lokal%2==0){
	 PORTC|=(1<<PINC7);
	 _delay_ms(500);
	 }
	 else {
		   PORTC&=~(1<<PINC7);
		  _delay_ms(100);
	  }
	  
	 }
	 
	 
