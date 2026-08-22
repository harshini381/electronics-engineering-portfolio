USART RX – Receive and Echo

Project Overview

This project demonstrates UART/EUSART communication using the PIC18F47Q10 microcontroller.

The program receives a character through the EUSART2 receiver and transmits the received character back through the EUSART2 transmitter. This provides a simple UART receive-and-echo implementation for testing serial communication between the microcontroller and a PC or serial terminal.

Hardware

- PIC18F47Q10 Microcontroller
- PC / Serial Terminal
- UART communication interface

Pin Configuration

| Function | PIC Pin |
|---|---|
| EUSART2 TX | RD0 |
| EUSART2 RX | RD1 |

Clock Configuration

The microcontroller uses the internal high-frequency oscillator:

- Oscillator: HFINTOSC
- Frequency: 64 MHz
- External oscillator: Disabled

UART Configuration

The EUSART2 peripheral is configured for asynchronous serial communication.

- EUSART module: EUSART2
- TX pin: RD0
- RX pin: RD1
- Baud rate: approximately 9600 baud
- 8-bit data communication
- Receiver enabled
- Transmitter enabled

The Peripheral Pin Select (PPS) registers are configured to route EUSART2 signals to the required pins.

Program Operation

1. Configure RD0 as the EUSART2 TX output.
2. Configure RD1 as the EUSART2 RX input.
3. Configure the EUSART2 baud-rate generator.
4. Enable the EUSART2 serial port.
5. Enable the transmitter and receiver.
6. Wait until a character is received.
7. Read the received character from `RC2REG`.
8. Wait for the transmitter to become ready.
9. Send the received character through `TX2REG`.
10. Repeat continuously.

Key Concepts Demonstrated

- Embedded C programming
- PIC18F47Q10 microcontroller
- EUSART/UART communication
- UART receiver configuration
- UART transmitter configuration
- Peripheral Pin Select (PPS)
- GPIO configuration
- Baud-rate configuration
- Polling-based serial communication
- Microcontroller peripheral initialization

Development Tools

- MPLAB X IDE
- XC8 Compiler
- PIC18F47Q10

## Source Code

The `rx.c` file in this folder contains the complete Embedded C implementation.
