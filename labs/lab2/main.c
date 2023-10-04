#include "stm32f10x.h"
#include "init.h"

int main()
{
	clockInit();
	serialOpen();
	ledinit();
	uint8_t num_count = 0x21;
	
	while(1)
		{
			while (num_count < 0x7E)
				{
					send(num_count);
					delay(110000);
					num_count++;
				}
			num_count = 0x21;

			if (receive() == 0x50)
			{
				led1ON();
			}
			else
				led1OFF();
		}
			
}
