
int main()
{
	int revieved_data=1;
	DDRC|=(1<<PINC7);
	PORTC|=(1<<PINC7);
	unsigned int UBRR_Value=77; //9600 Baud
	UBRR0H=(unsigned char) (UBRR_Value>>8);
	UBRR0L=(unsigned char) (UBRR_Value);
	//Enable Reciever & Transmitter
	UCSR0B=(1<<RXEN0)|(1<<TXEN0);
	//2 Stop BITS
	UCSR0C =(1<<USBS0);
	//8 BITS
	UCSR0C=(1<<UCSZ01)|(1<<UCSZ00);
	
	while(1){
		revieved_data++;
		while(!(UCSR0A &(1<<UDRE0)));
		UDR0 =revieved_data;
		
		
		while(!(UCSR0A &(1<<RXC0)));
		revieved_data = UDR0 ;
		if(revieved_data <=50){
			PORTC^=(1<<PINC7);
			_delay_ms(20);
		}
		else if((revieved_data >50) && (revieved_data <=120)){
			PORTC^=(1<<PINC7);
			_delay_ms(50);
		}
		
		else if((revieved_data >120)&& (revieved_data <=200)){
			PORTC^=(1<<PINC7);
			_delay_ms(100);
			
			
		}
		
		else if((revieved_data >200)&& (revieved_data <=205)){
		PORTC^=(1<<PINC7);
		_delay_ms(1000);
		}
		else 
			revieved_data=1;
	
	
}
}
