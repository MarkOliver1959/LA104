# LA104 pocket logic analyser

The LA104 is a tiny (100mm x 56mm) device made by 
[E-Design / Miniware](http://www.miniware.com.cn/product/signal-analyzer/)
This code and build files have been modified for STM32CubeIDE (by STmicroelectronics) development environment as well as enhancements. This is based on a merged build created from using the [Gabinator GCC build](https://github.com/gabonator/LA104) merged with [Ralims shortcut button modifications ](https://github.com/Ralim/LA104).


## New features
 
**Address shift option** - This option enables the I2c address (first byte) to be displayed numerically as right shifted as data.

I2c addresses are usually left shifted then merged with the R/W bit before being presented on the i2c bus. This makes reading the raw  addresses difficult. For example a sensor address of 0x41 would have been displayed as 0x82 or 0x83 depending on read or write. 

**Note:** This firmware doesn't currently run under Gabinator's operating system as that is work in progress.

There are a number of deficiencies in the current firmware, one of which is that it doesn't support sequential transfers (repeated starts with change of direction).

