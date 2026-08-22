# USART Button Counter

## Project Overview

This project demonstrates UART communication, command processing, GPIO button interfacing, and event counting using the PIC18F47Q10 microcontroller.

The microcontroller receives commands through EUSART2. When the command `start` is received, button presses are detected and a counter value is transmitted through UART. When the command `stop` is received, counting is stopped and the counter is reset.

## Hardware

- PIC18F47Q10 Microcontroller
- Push button
- PC / Serial Terminal
- UART communication interface

## Pin Configuration

| Function | PIC Pin |
|---|---|
| EUSART2 TX | RD0 |
| EUSART2 RX | RD1 |
| Push Button | RE2 |

## Clock Configuration

The microcontroller uses the internal high-frequency oscillator:

- Oscillator: HFINTOSC
- Frequency: 64 MHz
- External oscillator: Disabled

## UART Configuration

EUSART2 is configured for asynchronous serial communication.

- EUSART module: EUSART2
- TX pin: RD0
- RX pin: RD1
- Baud rate: approximately 9600 baud
- Transmitter enabled
- Receiver enabled

Peripheral Pin Select (PPS) is used to route the EUSART2 signals to the required pins.

## Button Configuration

The push button is connected to RE2.

The pin is configured as:

- Digital input
- Weak pull-up enabled
- Active-low button operation

When the button is pressed, RE2 reads LOW.

## Command Processing

The program receives characters through EUSART2 and stores them in a character buffer.

Two commands are recognized:

### `start`

Sets the control flag and enables button counting.

### `stop`

Stops button counting and resets the counter to zero.

The received command is processed when a newline character is detected.

## Button Counter Operation

When the `start` command has been received:

1. The program monitors the RE2 button input.
2. When the button is pressed, the counter is incremented.
3. The updated counter value is transmitted through UART.
4. The program waits until the button is released before detecting another press.

This prevents a single button press from being counted repeatedly while the button remains pressed.

## Program Flow

```text
PC / Serial Terminal
        |
        |  "start"
        v
     EUSART2
        |
        v
 PIC18F47Q10
        |
        v
   Enable Counter
        |
        v
    Button RE2
        |
     Press
        |
        v
 Increment Count
        |
        v
   UART Transmission
