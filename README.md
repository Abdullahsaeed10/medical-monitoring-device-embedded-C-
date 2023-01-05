# medical-monitoring-device-embedded-C-
A software written in Embedded C that drives a prototype of heart rate and temperature sensors and visualize them using LCD and on Pc using various communication protocols, using PIC16F887 microcontroller. 

***
## Dependencies:-
#### You can find links for both in the downloads folder
- Proteus version 8.13 
- MikroC IDE
***  

## How to run:-
- Download the project folder
- Open the project in Proteus
- Open the project in MikroC IDE
- Compile and run the project
- upload the hex file on the microcontroller
- You can also see the data being sent to the LCD usign SPI
- You can also see the data being sent to the PC using UART

***
## How to use:-
- The project is divided into 2 parts

### Part 1:-
- This part is used to visualize the data on the LCD
- The data is sent to the LCD using SPI
- The data is sent to the LCD in the form of a string
- The string is sent to the LCD in the form of a byte

### Part 2:-
- This part is used to visualize the data on the PC
- The data is sent to the PC using UART
- The data is sent to the PC in the form of a string
- The string is sent to the PC in the form of a byte

***

## Modes:-
- The project has 3 modes to display the temperature and Heart rate
    - The temperature is displayed in Celsius
    - The Heart rate is displayed in BPM
- The modes are selected using the switch
#### Mode 1:-
- This mode is used to visualize the Temperature and Heart rate
#### Mode 2:-
- This mode is used to visualize the Temperature only 
#### Mode 3:-
- This mode is used to visualize the Heart rate only

***
## ON/OFF Toggle
- The project can be turned on and off using the switch
- The project is turned on when the switch is pressed
- The project is turned off when the switch is not pressed

***
## LCD

- The data is sent to the 74HC595 (Shift Register) via SPI in (serial)
- The data is then sent to the LCD via the 74HC595 (Shift Register) in (parallel)
- The data is then displayed on the LCD

***

### Darlington Configuration
- The Darlington configuration is amplify the current that comes out form the microcontroller to turn ON/OFF the heart rate LED and BUZZER 

***

## UART
- The data is sent to the PC using UART
- The data is sent to the PC in the form of a string
- The string is sent to the PC in the form of a byte

***

#LM35


