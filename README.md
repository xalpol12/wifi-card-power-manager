## Wifi Card Power Manager 

Final project for the Network Programming 2024 laboratory at Poznań University of Technology.

## Program execution method
1. Compilation: `gcc -Wall ./wifi_card_power_manager.c -o ./wifi_card_power_manager`
2. Execution: `sudo ./wifi_card_power_manager <wifi_interface>`
The `wifi_card_power_manager.c` file includes all other source files, so only this file should be compiled.

## Source files contents:
### globals.h
Header file containing `#define` for global variables, based on which the linear dependency of the card power on the current signal is calculated. To adjust the algorithm for use with your own wireless network card, measurements should be taken and the values of the strongest and weakest signals, as well as the permissible values ​​of the card power, should be checked.

### wifi_card_power_manager.c 
The main program file containing calls to other functions and handling the program flow. It contains an infinite loop in which the current power and signal are read, then the new card power is calculated according to the linear dependency based on the values provided in the header file `globals.h.`

### calculations.c
Contains functions handling the program logic: reading the current power and signal values ​​of the card, a mapping function for the defined global variables from the `globals.h` file, a function calculating the next power value for the given signal, and a function executing a system call to change the power of the wireless network card.

### pretty_print.c
A function printing the current power and signal values ​​in the terminal. It takes a pointer to a file, and when a `stdout` pointer is provided, the function will print new values ​​with each refresh (similar to the `watch` command) with additional status bars visualizing current levels in relation to total levels. If a file pointer other than `stdout` is passed, the function will write power and signal values to the file line by line.