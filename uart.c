#include "uart.h"
int main(){
	unsigned char revieved_data=0;
	DDRC|=(1<<PINC7);
	PORTC&=~(1<<PINC7);
	IntializeUART0(9600,0,8,EVEN,2);
	while(1){
		
	TransmitUART0(revieved_data);
	RecieveUART0();
	if(revieved_data <=50){
		PORTC^=(1<<PINC7);
		revieved_data++;
		_delay_ms(20);
	}
	else if((revieved_data >50) && (revieved_data <=120)){
		PORTC^=(1<<PINC7);
		revieved_data++;
		_delay_ms(50);
	}
	
	else if((revieved_data >120)&& (revieved_data <=200)){
		PORTC^=(1<<PINC7);
		revieved_data++;
		_delay_ms(100);
		
		
	}
	
	else if((revieved_data >200)&& (revieved_data <=205)){
		PORTC^=(1<<PINC7);
		revieved_data++;
		_delay_ms(1000);
	}
	else
	revieved_data=1;
	
	
	}
	return 0;
}
