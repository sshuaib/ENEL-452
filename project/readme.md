ENEL 452 Elevator Control System:

Basic Elevator Function:
This elevator is a 3-floor system which is capable of calling an elevator as well as choosing from floors 1 to 3 to go as well. This elevator also has a maintenance mode which completes maintenance tasks in a short period of time and return the elevator to regular operation. The last feature implemented in this elevator is an emergency pushbutton which is the on-board blue USER button which ceases all elevator functions and will not continue until it is pressed again.

Equipment and software used:
- Nucleo STM32F103RB Microcontroller
- PC w/ Keil uVision5 IDE

Interrupts:
- USART2 interrupt on CLI
- EXTI interrupt using on-board blue USER button

How to operate:

1. When entered into PuttY, hit the black reset button which will reset the terminal and pop up the CLI on the terminal.
2. From here, you can call the elevator but the elevator will already be on the first floor.
3. Once the elevator has been called, you can then choose a floor you would like to go to.
4. If you would like to test out maintenance mode enter 'm' which will perform quick maintenance tasks which will exit after a short time and return to elevator functions.
5. Hit the blue USER button at any moment to emergency stop the elevator and cease all functions. To resume elevator functions, press the button again. Emergency STOP will be noted by the on-board LED lighting up and when it is in normal conditions and the button is pressed again the on-board LED will turn off.          

Video link:

https://www.youtube.com/watch?v=y-js3b2Sveg
