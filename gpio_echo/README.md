### Example of using the GPIO driver.

This example allows you to check the I/O GPIO pins functionality, and also the GPIO interrupts handling. 
The output pin (GPIO_PIN_OUT) should be connected to the input pin (GPIO_PIN_IN).

Description of the example execution:
1) At the beginning of execution, the "Start GPIO_echo test" message is displayed in the console.
2) The BSP driver is initialized, and the GPIO pins are configured.
3) Port "gpio0" is opened.
4) The configuration is set for the output pin (the pin number is defined in the GPIO_PIN_OUT macro) and for the input
pin (GPIO_PIN_IN). The input pin settings are specified in the IN_MODE macro.
5) The state of the output pin is changed several times. If the example works correctly: when the output pin state
changes, output pin state is printed, the last event from the input pin is recieved, which should be captured according
to output pin state changing, input pin state is printed, output and input pins state must match.
6) Port "gpio0" is closed.
7) If the example completes successfully, the message “Test successfully finished.” is displayed in the console.

If any errors occur during the execution of the example, a message about the error will be displayed in the console, 
and the execution of the example is stopped.

Code notation:

GPIO_PIN_OUT - the number of the GPIO pin configured for the output
GPIO_PIN_IN - GPIO pin number configured for input
IN_MODE - settings for input pin
DELAY_S - delay between changing the state of the output pin in seconds
GPIO_EVENT_DELAY_M - delay for waiting the event in GPIO input pin in milliseconds

For details please refer to the [documentation](https://click.kaspersky.com/?hl=en-us&link=online_help&pid=kos&version=1.1).

### Prerequisites
Before you begin, ensure that you have met the following requirements:
- You have installed the latest version of [KasperskyOS Community Edition](https://os.kaspersky.com/development/download/)
- You have Debian GNU/Linux "Buster" 10 x64

### Usage
To build the example and run the resulting image use the cross-build.sh script.

© 2022 AO Kaspersky Lab
