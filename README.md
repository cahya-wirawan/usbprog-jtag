# USBProg-jtag
## New and optimized OpenOCD-Firmware for USBProg

The original OpenOCD-Firmware for USBProg is very slow. This project was created as an alternative to this firmware, it is based on [estick-jtag](https://github.com/cahya-wirawan/estick-jtag). Usbprog-jtag is about 18 times faster than the original firmware.

## News
Apr 11, 2010: An early optimized version of OpenOCD 0.4.0 driver for USBProg was created: http://usbprog-jtag.googlecode.com/files/openocd-0.4.0-usbprog-0.1.diff'>openocd-0.4.0-usbprog-0.1.diff

## USBProg's pin
Currently the new pin's configuration is difference than the original. PORTB is configured for JTAG communications:

| Pin | Function | |:--------|:-------------| | 0 | TDI | | 1 | TMS | | 2 | TRST | | 3 | SRST | | 4 | TCK | | 5 | TDO |

And following is the pin configuration of USBProg:
<img src="https://github.com/cahya-wirawan/usbprog-jtag/blob/master/images/USBProg-pin.png" alt="USBProg-pin" 
style="width: 300px;"/>

## How to compile
Currently the revision 1454 of OpenOCD is used, and it needs to be patched with the driver for usbprog-jtag. The OpenOCD's source code can be downloaded from the usbprog-jtag's repository, it was patched already with usbprog-jtag code. Following is the step to get/compile openocd and make usbprog-jtag's firmware: wget http://usbprog-jtag.googlecode.com/files/openocd-r1454-usbprog-0.1.tgz tar xvzf openocd-r1454-usbprog-0.1.tgz cd openocd-r1454-usbprog sh ./bootstrap ./configure --enable-usbprog make

wget http://usbprog-jtag.googlecode.com/files/usbprog-jtag-0.1.bin

This firmware (usbprog-jtag-0.1.bin) can be programmed to the USBProg using normal flashtool

## Test
LM3S2110 CAN Device Evaluation Board was used to test the transfer rate of usbprog-jtag. This Board from Luminary Micro has 64KB of FLASH and 16KB of RAM.

## Run OpenOCD
``` $ openocd -f lm3s2110_usbprog.cfg

Info : eStick JTAG Interface ready Info : JTAG tap: lm3s2110.cpu tap/device found: 0x3ba00477 (Manufacturer: 0x23b, Part: 0xba00, Version: 0x3) Info : JTAG Tap/device matched Warn : no tcl port specified, using default port 6666 ```

## Loading to the RAM
``` $ arm-elf-gdb GNU gdb (GDB) 7.0.1 Copyright (C) 2009 Free Software Foundation, Inc. License GPLv3+: GNU GPL version 3 or later http://gnu.org/licenses/gpl.html This is free software: you are free to change and redistribute it. There is NO WARRANTY, to the extent permitted by law. Type "show copying" and "show warranty" for details. This GDB was configured as "--host=i386-apple-darwin9.8.0 --target=arm-elf". For bug reporting instructions, please see: http://www.gnu.org/software/gdb/bugs/.

(gdb) target remote localhost:3333 Remote debugging using localhost:3333 0xe59ff018 in ?? ()

(gdb) mon reset JTAG tap: lm3s2110.cpu tap/device found: 0x3ba00477 (Manufacturer: 0x23b, Part: 0xba00, Version: 0x3) JTAG Tap/device matched

(gdb) mon sleep 500

(gdb) mon poll

(gdb) monitor soft_reset_halt requesting target halt and executing a soft reset target state: halted target halted due to breakpoint, current mode: Thread xPSR: 0x01000000 pc: 0x000000f0

(gdb) set mem inaccessible-by-default off

(gdb) monitor fast enable

(gdb) monitor verify_ircapture disable verify Capture-IR is disabled

(gdb) mon mwb 0x20000000 0 64

(gdb) mon mdb 0x20000000 64 0x20000000: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 0x20000020: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00

(gdb) load test-ram Loading section .text, size 0x48c lma 0x20000000 Loading section .eh_frame, size 0x4 lma 0x2000048c Loading section .ARM.exidx, size 0x8 lma 0x20000490 Loading section .rodata, size 0x3840 lma 0x20000498 Loading section .data, size 0x100 lma 0x20003cd8 Start address 0x2000042d, load size 15832 Transfer rate: 18 KB/sec, 3166 bytes/write.

(gdb) mon mdb 0x20000000 64 0x00000000: 00 40 00 20 f1 00 00 00 3d 04 00 00 3d 04 00 00 3d 04 00 00 3d 04 00 00 3d 04 00 00 3d 04 00 00 0x00000020: 3d 04 00 00 3d 04 00 00 3d 04 00 00 3d 04 00 00 3d 04 00 00 3d 04 00 00 3d 04 00 00 3d 04 00 00 ```

## Loading to the FLASH
``` $ telnet localhost 4444 Connected to localhost. Escape character is '^]'. Open On-Chip Debugger

halt

flash probe 0 flash 'stellaris' found at 0x00000000

flash erase_sector 0 0 63 erased sectors 0 through 63 on flash bank 0 in 0.277004s

mdb 0x0 64 0x00000000: ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff 0x00000020: ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff

flash write_image test-flash.bin 0 bin
Algorithm flash write 2048 words to 0x0, 16246 remaining Algorithm flash write 2048 words to 0x2000, 14198 remaining Algorithm flash write 2048 words to 0x4000, 12150 remaining Algorithm flash write 2048 words to 0x6000, 10102 remaining Algorithm flash write 2048 words to 0x8000, 8054 remaining Algorithm flash write 2048 words to 0xa000, 6006 remaining Algorithm flash write 2048 words to 0xc000, 3958 remaining Algorithm flash write 1910 words to 0xe000, 1910 remaining wrote 64984 byte from file test-flash.bin in 5.786837s (10.966429 kb/s)

mdb 0x0 64
0x00000000: 00 40 00 20 f1 00 00 00 3d 04 00 00 3d 04 00 00 3d 04 00 00 3d 04 00 00 3d 04 00 00 3d 04 00 00 0x00000020: 3d 04 00 00 3d 04 00 00 3d 04 00 00 3d 04 00 00 3d 04 00 00 3d 04 00 00 3d 04 00 00 3d 04 00 00

verify_image test-flash.bin 0 bin verified 64984 bytes in 0.717032s

```

## Transfer rate comparison
| | USBProg (original firmware) | usbprog-jtag | |:-|:--------------------------------|:-----------------| | FLASH | 0.6 KB/s | 10.97 KB/s | | RAM | 1 KB/s | 18 KB/s |

The test was made with following information: * Mac OS X 10.5.8, 2.33 GHz Intel Core 2 Duo, 2GB RAM * OpenOCD rev 1454 * ARM GNU gdb (GDB) 7.0.1 * AVR gcc version 4.3.2 (GCC) * Firmware was compiled with optimization: -Os * Target board: LM3S2110 CAN Device Evaluation Board * jtag_speed 0 * File size to flash: 64984 bytes * File size to ram: 15832 bytes
