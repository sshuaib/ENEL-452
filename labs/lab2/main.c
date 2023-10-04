#include "stm32f10x.h"
#include "init.h"

int main()
{
	
		clockInit();
	 //tim3_IO_init();
	 //tim3GPIOSetup(50);
		configUSARTsetup();
		ledinit();
	
	/*while(1)
	{
		blueButton();
		
	}*/
	
	//uint8_t input = 0x21;
	
	while(1)
	{
		/*
		while (input <= 0x7E)
		{
			send(input);
			delay(100000);
			input++;
		}
		input = 0x21;
		*/
		
		if(receive() == 0x83)
		{
			led1ON();
		}
		else if (receive() == 0x70)
		{
			led1OFF();
		}
	}
		
}
