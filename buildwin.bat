@echo off

set SOURCES= ../Startup/startup.c ../source/Main.c ../source/Menu.c ../source/Interrupt.c ../source/GUI.c ../source/AppBios.c ../source/GUI.c ../source/Ctrl.c ../source/Analyze.c ../source/Func.c ../source/Files.c ../source/Disk.c ../source/FAT12.c ../source/Ext_Flash.c ../lib/spf.c ../lib/STM32F10x_StdPeriph_Driver/src/stm32f10x_spi.c ../lib/STM32F10x_StdPeriph_Driver/src/stm32f10x_rcc.c ../lib/STM32F10x_StdPeriph_Driver/src/stm32f10x_flash.c ../lib/STM32F10x_StdPeriph_Driver/src/misc.c ../lib/STM32_USB-FS-Device_Driver/src/usb_init.c ../lib/MSD/USB_bot.c ../lib/MSD/USB_scsi.c ../lib/STM32_USB-FS-Device_Driver/src/usb_regs.c ../lib/STM32_USB-FS-Device_Driver/src/usb_mem.c ../lib/MSD/USB_pwr.c ../lib/MSD/USB_prop.c ../lib/MSD/USB_desc.c ../lib/STM32_USB-FS-Device_Driver/src/usb_core.c ../lib/STM32_USB-FS-Device_Driver/src/usb_int.c ../lib/MSD/USB_istr.c ../lib/CMSIS/Device/STM32F10x/Source/system_stm32f10x.c
set OBJECTS=startup.o Main.o Menu.o Interrupt.o GUI.o AppBios.o Ctrl.o Analyze.o Func.o Files.o Disk.o FAT12.o Ext_Flash.o spf.o stm32f10x_spi.o stm32f10x_rcc.o stm32f10x_flash.o misc.o system_stm32f10x.o usb_init.o USB_bot.o USB_scsi.o usb_regs.o usb_mem.o USB_pwr.o USB_prop.o USB_desc.o usb_core.o usb_int.o USB_istr.o
set INCLUDES=-I ../sources -I ../lib/STM32_USB-FS-Device_Driver/inc -I ../lib/MSD -I ../lib/CMSIS/Include -I ../lib/STM32F10x_StdPeriph_Driver/inc  -I .. -I ../source -I ../lib/CMSIS/Device/STM32F10x/Include
set DEFINES=-D USE_STDPERIPH_DRIVER -D STM32F10X_HD

set path=C:\ST\STM32CubeIDE_1.1.0\STM32CubeIDE\plugins\com.st.stm32cube.ide.mcu.externaltools.gnu-tools-for-stm32.7-2018-q2-update.win32_1.0.0.201904181610\tools\bin;C:\ST\STM32CubeIDE_1.1.0\STM32CubeIDE\plugins\com.st.stm32cube.ide.mcu.externaltools.make.win32_1.1.0.201910081157\tools\bin;C:/ST/STM32CubeIDE_1.1.0/STM32CubeIDE/jre/bin/server;C:/ST/STM32CubeIDE_1.1.0/STM32CubeIDE/jre/bin;C:/ST/STM32CubeIDE_1.1.0/STM32CubeIDE/jre/lib/amd64;C:\Program Files (x86)\Common Files\Oracle\Java\javapath;C:\WINDOWS\system32;C:\WINDOWS;C:\WINDOWS\System32\Wbem;C:\WINDOWS\System32\WindowsPowerShell\v1.0\;C:\WINDOWS\System32\OpenSSH\;C:\Program Files\Microsoft VS Code\bin;C:\Program Files (x86)\AOMEI Backupper;C:\Program Files\nodejs\;C:\Program Files\Microsoft VS Code Insiders\bin;C:\Program Files\Git\cmd;C:\Program Files\PuTTY\;C:\Program Files (x86)\Intel\Intel(R) Management Engine Components\DAL;C:\Program Files\Intel\Intel(R) Management Engine Components\DAL;C:\Users\Mark\AppData\Local\Programs\Python\Python37\Scripts\;C:\Users\Mark\AppData\Local\Programs\Python\Python37\;C:\Users\Mark\AppData\Local\Microsoft\WindowsApps;C:\Program Files\JetBrains\PyCharm Community Edition 2019.1.1\bin;;D:\WORK\IOT\ESP32\msys32;D:\WORK\IOT\ESP32\msys32\opt\esp-idf\tools;C:\Users\Mark\AppData\Roaming\npm;C:\Program Files\nodejs;;C:\ST\STM32CubeIDE_1.1.0\STM32CubeIDE
cd build

arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -c ../Startup/bios.s -o bios.o
arm-none-eabi-gcc -Os -Werror -fno-common -mcpu=cortex-m3 -msoft-float -mthumb -MD %DEFINES% %INCLUDES% -c %SOURCES% -std=c99
arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -o output.elf -nostartfiles -T ../app.ld -Wl,-Map="La104.map" %OBJECTS% 

arm-none-eabi-objcopy -O binary output.elf output.bin
arm-none-eabi-objcopy -O ihex output.elf output.hex

arm-none-eabi-readelf -all output.elf > output.txt
arm-none-eabi-objdump -d -S output.elf > output.asm

del *.d
del *.o
del *.bin
rem copy output.hex e: output.hex e: