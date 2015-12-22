# BrewTroller

[![Build Status](https://travis-ci.org/BrewTroller/BrewTroller-Official.svg)](https://travis-ci.org/BrewTroller/BrewTroller-Official)
=====

This is the new home of BrewTroller! (Originally forked from the now defunct OSCSYS). For help with BrewTroller hardware, firmware or anything else BrewTroller related, visit our forums at
[http://brewtroller.com](http://brewtroller.com)

Known Issues
-----
1. ~~BrewTroller 4.x boards with removable plug-in exansion modules may encounter erratic behaviour if the One-Wire master board is not installed.~~
2. Firmware currently builds for boards that have the atmega644p chip installed, but the resulting firmware is too big to fit on chip.


Building
=====

Build Requirements
-----
1. AVR GCC toolchain (Tested with v4.8.3, other versions may work)
2. AVR LIBC (Tested with version 1.8.1, others may work)
3. AVR BINUTILS (Tested with version 2.24, others may work)
4. AVRDUDE (for installing binaries to BrewTroller)
5. CMAKE (Requires version 2.8 or newer)

The recommended way for mac users to install these dependancies is with the [Homebrew](http://brew.sh) package manager.
The commands to install the dependanies are:
  ```
  $ brew tap larsimmisch/avr
  $ brew install avr-libc
  $ brew install cmake
  ```
Windows users can download cmake [here](http://www.cmake.org/download/), and pre-built binaries for the AVR toolchain can be downloaded [here](http://sourceforge.net/projects/mobilechessboar/files/avr-gcc%20snapshots%20%28Win32%29/avr-gcc-4.8_2013-03-06_mingw32.zip/download).  

Compiling
------

To prevent causing serious headaches all builds should be done out-of-source; building from the build directory is recommended.

To build from the build directory execute:

```
$ cmake -Dboard={Hardware profile} -DAVR_MCU={mcu} ../
$ make
```

This ensures that all build artifacts are stored in the build directory and not in the source code directories.

Available Hardware profile options are:

    BT_10_21               --> 1.0 - 2.1
    BT_22_24               --> 2.2 - 2.4
    BT_3X                  --> 3.X
    BT_4P                  --> 4.X Pro
    OT_BX1_HERMS           --> BX1 HERMS
    OT_BX1_HERMSI2CLCD     --> BX1 HERMS + I2CLCD
    OT_BX1_RIMSDF          --> BX1 RIMS / Direct Fired
    OT_BX1_RIMSDFI2CLCD    --> BX1 RIMS / Direct Fired + I2CLCD
    OT_BX1_SINGLEVESSEL    --> BX1 Single Vessel
    OT_BX1_STEAMPWM        --> BX1 Steam or PWM Pump
    OT_BX1_STEAMPWMI2CLCD  --> BX1 Steam or PWM Pump + I2CLCD
    OT_DX1_HERMS           --> DX1 HERMS
    OT_DX1_RIMSDF          --> DX1 RIMS / Direct Fired
    OT_DX1_SINGLEVESSEL    --> DX1 Single Vessel
    OT_DX1_STEAMPWM        --> DX1 Steam or PWM Pump
    OT_EX1_HERMS           --> EX1 HERMS
    OT_EX1_RIMSDF          --> EX1 RIMS / Direct Fired
    OT_EX1_SINGLEVESSEL    --> EX1 Single Vessel
    OT_EX1_STEAMPWM        --> EX1 Steam or PWM Pump
If no board option is specified DX1 HERMS is built by default.

Available AVR_MCU options are:

    atmega1284p
    atmega644p
If no AVR_MCU option is specified atmega1284p is used by default.

Uploading
-----
To upload the compiled BrewTroller firmware to a BrewTroller board:

```
$ avrdude -p m1284p -c arduino -b 57600 -P [your brewtroller serial port] -U flash:w:src/Brewtroller-atmega1284p.hex
```

You must substitute [you brewtroller serial port] for the serial port your board is connected to. This will vary by OS, windows users will have form `COMxx`,
Mac users will have the form `/dev/tty.usbserial-xxxxxxx` and linux users will have the form `/dev/ttyUSBxx`.

Testing
-----
The new BrewTroller repository is getting some much needed unit tests added! To run them, you will need the same build system requirements as for the main firmware, with added reqirement of a native compiler for your build machine. For a Mac this means having Xcode and the command line tools installed, for ubuntu this generally means having the `build-essential` package installed.

To build the new test suite, from the the tests subdirectory, run the following commands
```bash
$ mkdir build
$ cd build
$ cmake ../
$ make
$ ./brewtrollerTests
```
