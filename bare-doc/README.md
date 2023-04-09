# Tapuino-Bare

Thanks for Richard Toth for drawing the basic schematic of Tapuino-Bare and contributing in porting and testing.

## Intro

Tapuino-Bare is created for building Tapuino hardware without using a complete Arduino board. Additionally new hardwares (displays) are intended to make able to attach and, moreover, a signal conditioning circuit is to be used for connecting the Tapuino to several vintage computers with audio level tape in and out. 

Due to the recent changes in chip supply chains, ATmega328 (which is the main part of the most popular Arduino boards such as UNO, Nano and several Pro Micro variants) became hardly or near completely impossible to reach with exremely large delivery times or irreal high price. That's why we with a couple of my friends thought that this great project should be able to compile to other AVR chips we could get more easier. Furthermore, since the present Tapuino code is almost filling up the memories of ATmega328, with new chips we could have more internal memory which would enable additional functions to be included in the code. The main considerations were touching the original code only at the most necessary points. Of course, the modified code can also be compiled to the original hardware (Arduino board) or its bare variant, ATmega328.

The "bare" cores we made possible the code to compile to are coming from MCUdude's [MightyCore](https://github.com/MCUdude/MightyCore) or [MiniCore](https://github.com/MCUdude/MiniCore) packages. At this moment the code can be compiled for the following AVRs:
- ATmega328 (Arduino UNO, Nano or MiniCore)
- ATmega324/644/1284 (MightyCore)
- ATmega32 (MightyCore)

## Hardware

The pinout on 40-pin devices is unified, you can simply swap the AVR in the circuit without any modification need.

For the maximal compatibility with the original Tapuino a 16MHz external crystal or oscillator block is used. The fuse bits have to be programmed in sync with the clock source was built in. With minimal external components a TTL-level serial connection can be formed in order to program the circuit through bootloader directly from the Arduino IDE.

## Building

The building of the firmware simply works from Arduino IDE (1.8.x was used during the development), you must  install first the appropriate MCUdude package according to its documentation. 

You can use Tapuino with or without the Optiboot bootloader. The compiled code sizes even fit into the smallest (32K flash) chips with bootloader.

Prior the building please make a copy of config-user.h.example file with name config-user.h and select your display/language options in this with removing the comments (// at begins) from the appropriate lines.


## Firmware programming

 In case of using bootloader the firmware can be simply uploaded to the AVR from the IDE using only a cheap TTL-level USB/serial adapter dongle. Of course, AVR has to be preprogrammed with the bootloader and the necessary fuse bits prior to firmware uploading, or a preprogrammed chip is to be bought.

If you have a brand new, empty AVR chip, you would need to prepare it for using in the project. This means either programming the compiled binary into the chip or writing only the bootloader into it for later uploading the firmware. The appropriate fuse bits are to be set up in both cases.

Hint: the popular device programmer TL866 can handle these AVRs.