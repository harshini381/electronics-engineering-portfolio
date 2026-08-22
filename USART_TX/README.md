USART TX – Serial Data Transmission

Project Overview

This project demonstrates UART/EUSART serial data transmission using the PIC18F47Q10 microcontroller.

The program initializes the EUSART2 peripheral and transmits a string through the UART transmitter. In this implementation, the message "Hello " is transmitted through the EUSART2 TX pin.

Hardware

- PIC18F47Q10 Microcontroller
- PC / Serial Terminal
- UART communication interface

Pin Configuration

| Function | PIC Pin |
|---|---|
| EUSART2 TX | RD0 |
| EUSART2 RX | RD1 |

The TX pin is used for serial data transmission.

Clock Configuration

The microcontroller uses its internal high-frequency oscillator:

- Oscillator: HFINTOSC
- Frequency: 64 MHz
- External oscillator: Disabled

UART Configuration

EUSART2 is configured for asynchronous serial communication.

- EUSART module: EUSART2
- TX pin: RD0
- RX pin: RD1
- Baud rate: approximately 9600 baud
- Transmitter enabled
- Asynchronous mode

The Peripheral Pin Select (PPS) registers are configured to route the EUSART2 signals to the required pins.

Program Operation

1. Configure RD0 as the EUSART2 TX output.
2. Configure the UART-related pins as digital pins.
3. Configure the EUSART2 baud-rate generator.
4. Enable the EUSART2 serial port.
5. Enable the transmitter.
6. Pass a string to the UART transmission function.
7. Wait until the transmitter is ready.
8. Send each character through `TX2REG`.
9. Continue until the complete string has been transmitted.

Example Output

The program sends:

```text
Hello

```
