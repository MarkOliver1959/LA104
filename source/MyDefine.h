#ifndef __MYDEFINE_H
#define __MYDEFINE_H

//#define GABONATOR_OS
#include <string.h>
#include <stdint.h>

#ifdef GABONATOR_OS
	#include <library.h>

	typedef uint16_t u16;
	typedef uint8_t u8;
	typedef int8_t s8;
	typedef const uint8_t uc8;
	typedef int16_t s16;
	typedef const uint16_t uc16;
	typedef const uint32_t uc32;
	typedef uint32_t u32;
	typedef int32_t s32;
	typedef volatile uint32_t vu32;
	typedef uint64_t u64;
	__attribute__((__section__(".entry"))) int main(void);
#else
	#include "../lib/spf.h"
	#include "stm32f10x.h"
	#include "FAT12.h"
	#include "Disk.h"
	#include "Ext_Flash.h"
	#include "Interrupt.h"
	#include "USB_lib.h"
#endif

#include "Analyze.h"
#include "AppBios.h"
#include "Ctrl.h"
#include "Files.h"
#include "Func.h"
#include "GUI.h"
#include "Menu.h"

void ExitApplication();

#endif
