#ifndef __BIOS_H
#define __BIOS_H

#include "MyDefine.h"

typedef struct
{
    u16  n;
    u8  *pBuf;
}SPI_ParamDef;

typedef struct
{
    u8 flag;
    u8 total;
    u8 index;
}MENU_Struct;

typedef struct
{
    u8 flag;
    u8 total;
    u8 index;
}ITEM_Struct;

typedef struct
{
    u8 flag;
    u8 total;
    u8 index;
}SUBITEM_Struct;

#define OFF             0
#define ON              1
#define SUCC            0
#define FAIL            1
#define HIGH            1
#define LOW             0
#define NONE            0
#define ENBL            1
#define DSBL            0
#define INIT            0xFFFF0000
#define STRING          0xFFFE0000
#define VALUE           0xFFFD0000

//----------------------Display device definintions-----------------
#define MCU_DRV         0xFFFB0000
#define FPGA_DRV        0xFFFA0000
#define XWDTH           280
#define YHIGH           154
#define X0              40
#define Y0              66

//--------------------- Extended test signal port definitions-------
#define PWM1_PSC        0xFFFC0000
#define PWM1_ARR        0xFFFB0000
#define PWM1_DUTY1      0xFFFA0000
#define PWM1_DUTY2      0xFFF90000
#define PWM1_CTRL       0xFFF80000
#define PWM2_PSC        0xFFF60000
#define PWM2_ARR        0xFFF50000
#define PWM2_DUTY1      0xFFF40000
#define PWM2_DUTY2      0xFFF30000
#define PWM2_CTRL       0xFFF20000

//---------------------- Power control measurement equipment-----
#define VIN_ST          0xFFFC0000
#define VBTYmV          0xFFFB0000

//----------------------Button defines ------------------------
#define BITMAP          0xFFFC0000
#define ENC1a           0x1000
#define ENC1b           0x2000
#define ENC2a           0x4000
#define ENC2b           0x8000
#define K1_HOLD         0x0001
#define K2_HOLD         0x0002
#define K3_HOLD         0x0004
#define K4_HOLD         0x0008
#define K1_ACTn         0x0010
#define K2_ACTn         0x0020
#define K3_ACTn         0x0040
#define K4_ACTn         0x0080
#define K1_ACTp         0x0100
#define K2_ACTp         0x0200
#define K3_ACTp         0x0400
#define K4_ACTp         0x0800
#define Kn_ACTn         0x00F0
#define Kn_ACTp         0x0F00
#define KEYSBIT         0x000F
#define ENCD_1p         0x1000
#define ENCD_1n         0x2000
#define ENCD_2p         0x4000
#define ENCD_2n         0x8000
#define ENCDBIT         0xF000
#define READ_RUN_ST     (((~GPIOC->IDR) & K1_PIN)? 1:0)
#define READ_KEY        (~__Bios(KEYnDEV, BITMAP) & KEYSBIT)

//----------------------Display definitions--------------------------
#define SIZE            0xFFFC0000
#define MCU_WR          0xFFFB0000
#define MCU_RD          0xFFFA0000
#define FPGA_MOD        0xFFF90000
#define LCDCOL          320
#define LCDROW          240
#define LOGO_X          4*8
#define LOGO_Y          160

//----------------------FPGA Control--------------------------
#define CNFG            0xFFFC0000
#define DONE            0xFFFA0000
#define VREF            3000
#define FPGA_BUSY       0x01
#define FPGA_FULL       0x02
#define FPGA_EMPTY      0x04
#define FPGA_PRES       0x08
#define FPGA_TRI        0x10

#ifdef GABONATOR_OS
	#define RECORD_DEPTH    500
#else
	#define RECORD_DEPTH    3584   // efective 3584
#endif

#define CNTx4K          4
#define PSMP_NUM        2
//----------------------USB DISK --------------------------

#define PAGE            0xFFFC0000
#define SECTOR          0xFFFB0000
#define AMOUNT          0xFFFA0000

extern MENU_Struct Menu;
extern ITEM_Struct Item;
extern SUBITEM_Struct SubItem;

extern u8  gSamplBuf[], gLCD_Buf[], gLCD_Backup[];
extern u8  gBeepFlag, gStandByFlag;
extern u16 gSysCnt, gFullmS, gStandbyCnt, gAutoPwrCnt;
extern u16 gTimeBase, gBatVol, gUSB_Vol;

u32  __Bios(u8 Item, u32 Var);
u8   FPGA_LCD_RW(u8 Cmd, u16 Cnt, u8 *Buf);
u16  FPGA_ReadWrite(u8 Cmd, u16 Cnt, u16 Data);
u16  FPGA_Read(u8 Cmd, u16 Cnt, u16 Data);
u32  FPGA_RW_4Byte(u8 Cmd, u16 Cnt, u32 Data);
void DiskConfig(void);
void Delay_mS(vu32 mS);
void Delay_uS(vu32 uS);
void FpgaRW(u8 Cmd, u16 n, u8 *pBuf);
void ExtFlash_CS_LOW(void);
void ExtFlash_CS_HIGH(void);
void ProgmIO_SPIWr(u16 n, u8 *pBuf);
void ProgmIO_UARTTx(u8 Data);
void ProgmIO_I2CWr(u8 DevID, u8 Reg, u8 Data);

enum
{
	SYSINFO, // System info Var: PRDT_SN product serial number Rtn: (u16) product serial number
			 // Var: PRODUCT Model Rtn: Model string pointer
			 // Var: PRDTNUM product number Rtn: (u16) product number
			 // Var: SCH_VER hardware version Rtn: pointer to version string
			 // Var: MCU_TYP MCU model Rtn: model string pointer
			 // Var: DFU_VER DFU version Rtn: pointer to version string
			 // Var: OEM_NUM OEM number Rtn: pointer to number string
			 // Var: MANUFAC Manufacturer Info Rtn: Information String Pointer
			 // Var: LICENCE license status Rtn: SUCC / FAIL
			 // System control class
	NIVCPTR, // Interrupt vectorbase Var: (u16) Vector base address Rtn: SUCC / FAIL
	SYSTICK, // System tick interrupt setting Var: (u16) uS interrupt duration Rtn: SUCC / FAIL
	AF_RMAP, // Device IO relocation Var: (u32) AF REMAP Rtn: SUCC / FAIL
	PWRCTRL, // power control Var: INIT initialization Rtn: SUCC / FAIL
			 // Var: VIN_ST external power Rtn: ENBL / DSBL
             // Var: VBAT battery voltage Rtn: (u16) mV
             // Var: DSBL power off Rtn: SUCC / FAIL
    BUZZDEV, // Buzzer interface Var: INIT initialization Rtn: SUCC / FAIL
             // Var: (MUTE ~ 100) volume Rtn: SUCC / FAIL
    KEYnDEV, // Key input device Var: INIT Initial setting Rtn: SUCC / FAIL
             // Var: BITMAP read key position Rtn: (u16) key position status
    DELAYuS, // microsecond delay Var: (u32) uS delay time Rtn: SUCC / FAIL
             // display control class
    DISPDEV, // LCD display device Var: STRING Module model Rtn: Model string pointer
             // Var: INIT initialization Rtn: SUCC / FAIL
             // Var: VALUE screen specifications Rtn: (MaxX << 16 + MaxY)
             // Var: (0 ~ 100) backlight brightness Rtn: SUCC / FAIL
             // Var: (MCU / FPGA) drive source Rtn: SUCC / FAIL
    BLOCK_X, // display block x field setting Var: (x1 << 16) + x2) Rtn: SUCC / FAIL
    BLOCK_Y, // display block y field setting Var: (y1 << 16) + y2) Rtn: SUCC / FAIL
    PIXEL_X, // pixel x position Var: (u16) position Rtn: SUCC / FAIL
    PIXEL_Y, // pixel y position Var: (u16) position Rtn: SUCC / FAIL
    WrPIXEL, // display pixel write Var: (u16) pixel color Rtn: SUCC / FAIL
    RdPIXEL, // read screen pixels Var: Rtn: (u16) pixel color
    FONTPTR, // Var: ASCII Code Rtn: ptr string pointer
             // FPGA control class
    FPGADEV, // FPGA device control Var: STRING Rtn: Model string pointer
             // Var: INIT initialization Rtn: SUCC / FAIL
             // Var: CNFG power-up configuration Rtn: SUCC / FAIL
             // Var: COMM communication mode Rtn: SUCC / FAIL
             // Var: ENBL interface chip select Rtn: SUCC / FAIL
             // Var: (SPI_ParamDef *) Rtn: SUCC / FAIL
             // Sampling input control class
    IN_PORT, // logic input control Var: INIT initialization Rtn: SUCC / FAIL
             // Var: VREF logic reference voltage Rtn: SUCC / FAIL
             // U disk control class
    USBDEV,  // USB initialization
    U_DISK,  // USB DISK device Var: INIT initialization setting Rtn: SUCC / FAIL
             // Var: STRING U disk specification Rtn: U disk specification string pointer
             // Var: PAGE memory page size Rtn: SUCC / FAIL
             // Var: SECTOR sector capacity Rtn: (u16) sector capacity
             // Var: AMOUNT number of sectors Rtn: (u16) number of sectors
             // Var: (SPI_ParamDef *) Rtn: SUCC / FAIL
             // SPI control class
    SPI_DEV, // SPI device interface Var: (SPI_ParamDef *) Rtn: SUCC / FAIL
    FLSHDEV, // Flash SPI
             // extended test interface control class
    EXT_INP, // extend PIO interface Var: PIOCFG + PinDef Rtn: SUCC
    EXT_OUT, // extend PIO interface Var: PIOCFG + PinDef Rtn: SUCC
             // Var: PINS_OUT + Status0 ~ 3 Rtn: SUCC
             // Var: PINS_IN + BitMask0 ~ 3 Rtn: PinStatus 0 ~ 3
    EXT_PWM, // extended PWM interface Var: PWM_PSC + Var [0 ~ 15] Rtn: SUCC
             // Var: PWM_ARR + Var [0 ~ 15] Rtn: SUCC
             // Var: CH1_CCR + Var [0 ~ 15] Rtn: SUCC
             // Var: CH2_CCR + Var [0 ~ 15] Rtn: SUCC
             // Var: CH1_CTRL + ENBL / DSBL Rtn: SUCC
             // Var: CH2_CTRL + ENBL / DSBL Rtn: SUCC
    EXT_INF, // Extend PIO interface Var: INIT initialization setting Set to floating input
    EXT_SPI, // extended PIO interface Var: INIT initialization setting Rtn: SUCC / FAIL
             // Var: (SPI_ParamDef *) Rtn: SUCC / FAIL
    EXT_UART,// extended PIO interface Var: INIT initialization setting Rtn: SUCC / FAIL
             // Var: u8 Data Rtn: SUCC / FAIL
    EXT_I2C, // extend PIO interface
             // Var: 0x00 & ID & REG & DATA Rtn: SUCC / FAIL
    EXT_RXD, // extended PIO interface Var: PIOCFG + PinDef Rtn: SUCC
    EXT_TXD, // extended PIO interface Var: PIOCFG + PinDef Rtn: SUCC
};

enum
{
    PRDT_SN, // Product serial number
	PRODUCT, // Product model
	PRDTNUM, // Product ID
    HDW_VER, // Hardware version
	MCU_TYP, // MCU model
    DFU_VER, // DFU version
    OEM_NUM, // OEM number
    MANUFAC, // Manufacturer
    LICENCE, // Licence authorisation status
};

enum
{
    FPGA_INFO = 0x00, // Status and firmware version number n = 1, Rtn p [0] = St, p [1] = unknown data, p [2] = 0, p [3] = VerNum
    FPGA_RST  = 0x01, // chip internal logic reset n = 0, p * = Dummny
    SMPL_CLR  = 0x02, // chip internal logic reset n = 1, p * = Dummny
    WFRM_SAVE = 0x03, // Set waveform curve data n = Row + 1, p = & DataBytes

    WINDOW_Y  = 0x04, // Set display window height n = 1, p [1] = Y Size
    WINDOW_X  = 0x05, // Set the display window width n = 2, p [1 ~ 2] = X Size
    WFRM_DRAW = 0x06, // Refresh the waveform display image n = 0, p [1] = Col, p [2 ~ 3] = Row
    FLSH_ATTR = 0x07, // Set the blink attribute flag n = 1, p [1 ~ 2] = Attr

    RUL_POSN  = 0x10, // Set the RUL ruler position n = 1, p [1] = RUL Position
    CH1_POSN  = 0x11, // Set CH1 waveform position n = 1, p [1] = CH1 Position
    CH2_POSN  = 0x12, // Set CH2 waveform position n = 1, p [1] = CH2 Position
    CH3_POSN  = 0x13, // Set CH3 waveform position n = 1, p [1] = CH3 Position
    CH4_POSN  = 0x14, // Set CH4 waveform position n = 1, p [1] = CH4 Position
    CH5_POSN  = 0x15, // Set the CH5 envelope position n = 1, p [1] = CH5 Position
    CH6_POSN  = 0x16, // Set the envelope position of CH6 n = 1, p [1] = CH6 Position

    ZC_POSN   = 0x18, // Set the position of ZC marking line n = 2, p [1 ~ 2] = ZC Position
    T0_POSN   = 0x19, // Set T0 mark position n = 2, p [1 ~ 2] = T0 Position
    T1_POSN   = 0x1A, // Set the position of T1 marking line n = 2, p [1 ~ 2] = T1 Position
    T2_POSN   = 0x1B, // Set T2 mark position n = 2, p [1 ~ 2] = T2 Position

    TRG_KIND  = 0x20, // set trigger type n = 1, p [1] = Trigger Kind
    TRG_COND  = 0x21, // set trigger condition n = 1, p [1] = Trigger COND
    MEM_MASK  = 0x22, // set trigger mask n = 1, p [1] = Trigger Mask
    MEM_TWTH  = 0x23, // Set the trigger pulse width n = 2, p [1 ~ 2] = Trigger Twth

    MEM_PSMP  = 0x30, // set the pre-recording record depth n = 1, p [1] default value is 9
    MEM_RPTR  = 0x31, // set the record read pointer n = 2, p [1 ~ 2] = Record Rptr
    MEM_READ  = 0x32, // read record data n = 3, Rtn p [1 ~ 3] = Record Data
                      // [0]: Info, [1]: Tcnt [7: 0], [2]: Tcnt [13: 8], [3]: Di

    FPGA_ST   = 0x00, // position of FPGA status byte returned
    VER_NUM   = 0x01, // Location of FPGA firmware version number returned
    BUSY      = 0x01, // "Waveform image refresh" flag in FPGA status byte St
};

//Info״̬λ{3'd0, TrgRdy, PesRdy, Empty, Full, BusySt};
//��������
/*
    0: o_Trig <= 1'd0; // Disable trigger
	1: o_Trig <= DiNE; // status of the input combination logic does not match the preset conditions.
    2: o_Trig <= DiEQ; // state of the input combination logic is triggered according to the preset conditions
    3: o_Trig <= 1'd1; // Arbitrary trigger
    4: o_Trig <= DfLE; // Trigger if the duration width of the input does not match the condition is less than the threshold
    5: o_Trig <= DtLE; // Trigger when the qualifying continuous width is less than the threshold
    6: o_Trig <= DfGT; // Trigger if the duration width of the input does not match the condition is greater than the threshold
    7: o_Trig <= DtGT; // Trigger when the input's eligible duration width is greater than the threshold
*/

#endif
/*********************************  END OF FILE  ******************************/
