/**
* \file TFTSHIELD.c
* \brief This file provides the source code to the API for the TFTSHIELD
*   component
*
* Version 1.0
*
* \author Robert Barron
*
* \bug The text and shape drawing origins are in opposite corners, at least when the screen orientation is set to 1.
*
* 
*
* Copyright RPI Design Lab, 2014
* All Rights Reserved
* UNPUBLISHED, LICENSED SOFTWARE.
*
* CONFIDENTIAL AND PROPRIETARY INFORMATION
* WHICH IS THE PROPERTY OF the RPI Design Lab.
*
* 
*/

#include "`$INSTANCE_NAME`.h"

/*uint16 color_pass;
uint16 wave_table[ROW], count,x,i=0,j=0,k=2;
uint8 amplitude,wave,wave_color,set;
uint8 ch,tri;*/

/** @brief ASCII font*/
const char fontA[128][6]  =
{
	{0x00,0x00,0x00,0x00,0x00,0x00},
	{0x00,0x00,0x00,0x00,0x00,0x00},
	{0x00,0x00,0x00,0x00,0x00,0x00},
	{0x00,0x00,0x00,0x00,0x00,0x00},
	{0x00,0x00,0x00,0x00,0x00,0x00},
	{0x00,0x00,0x00,0x00,0x00,0x00},
	{0x00,0x00,0x00,0x00,0x00,0x00},
	{0x00,0x00,0x00,0x00,0x00,0x00},
	{0x00,0x00,0x00,0x00,0x00,0x00},
	{0x00,0x00,0x00,0x00,0x00,0x00},
	{0x00,0x00,0x00,0x00,0x00,0x00},
	{0x00,0x00,0x00,0x00,0x00,0x00},
	{0x00,0x00,0x00,0x00,0x00,0x00},
	{0x00,0x00,0x00,0x00,0x00,0x00},
	{0x00,0x00,0x00,0x00,0x00,0x00},
	{0x00,0x00,0x00,0x00,0x00,0x00},
	{0x00,0x00,0x00,0x00,0x00,0x00},
	{0x00,0x00,0x00,0x00,0x00,0x00},
	{0x00,0x00,0x00,0x00,0x00,0x00},
	{0x00,0x00,0x00,0x00,0x00,0x00},
	{0x00,0x00,0x00,0x00,0x00,0x00},
	{0x00,0x00,0x00,0x00,0x00,0x00},
	{0x00,0x00,0x00,0x00,0x00,0x00},
	{0x00,0x00,0x00,0x00,0x00,0x00},
	{0x00,0x00,0x00,0x00,0x00,0x00},
	{0x00,0x00,0x00,0x00,0x00,0x00},
	{0x00,0x00,0x00,0x00,0x00,0x00},
	{0x00,0x00,0x00,0x00,0x00,0x00},
	{0x00,0x00,0x00,0x00,0x00,0x00},
	{0x00,0x00,0x00,0x00,0x00,0x00},
	{0x00,0x00,0x00,0x00,0x00,0x00},
	{0x00,0x00,0x00,0x00,0x00,0x00},
 
	{0x00,0x00,0x00,0x00,0x00,0x00},	// SPACE
 
	{0x00,0x00,0x00,0x4F,0x00,0x00},	// !
	{0x00,0x00,0x07,0x00,0x07,0x00},	// "
	{0x00,0x14,0x7F,0x14,0x7F,0x14},	// #
	{0x00,0x24,0x2A,0x7F,0x2A,0x12},	// $
	{0x00,0x23,0x13,0x08,0x64,0x62},	// %
	{0x00,0x36,0x49,0x55,0x22,0x50},	// &
	{0x00,0x00,0x05,0x03,0x00,0x00},	// '
	{0x00,0x00,0x1C,0x22,0x41,0x00},	// (
	{0x00,0x00,0x41,0x22,0x1C,0x00},	// )
	{0x00,0x14,0x08,0x3E,0x08,0x14},	// *
	{0x00,0x08,0x08,0x3E,0x08,0x08},	// +
	{0x00,0x00,0x50,0x30,0x00,0x00},	// ,
	{0x00,0x08,0x08,0x08,0x08,0x08},	// -
	{0x00,0x00,0x60,0x60,0x00,0x00},	// .
	{0x00,0x20,0x10,0x08,0x04,0x02},	// /
 
	{0x00,0x3E,0x51,0x49,0x45,0x3E},	// 0
	{0x00,0x00,0x42,0x7F,0x40,0x00},	// 1
	{0x00,0x42,0x61,0x51,0x49,0x46},	// 2
	{0x00,0x21,0x41,0x45,0x4B,0x31},	// 3
	{0x00,0x18,0x14,0x12,0x7F,0x10},	// 4
	{0x00,0x27,0x45,0x45,0x45,0x39},	// 5
	{0x00,0x3C,0x4A,0x49,0x49,0x30},	// 6
	{0x00,0x01,0x71,0x09,0x05,0x03},	// 7
	{0x00,0x36,0x49,0x49,0x49,0x36},	// 8
	{0x00,0x06,0x49,0x49,0x29,0x1E},	// 9
 
	{0x00,0x36,0x36,0x00,0x00,0x00},	// :
	{0x00,0x56,0x36,0x00,0x00,0x00},	// ;
	{0x00,0x08,0x14,0x22,0x41,0x00},	// <
	{0x00,0x14,0x14,0x14,0x14,0x14},	// =
	{0x00,0x00,0x41,0x22,0x14,0x08},	// >
	{0x00,0x02,0x01,0x51,0x09,0x06},	// ?
	{0x00,0x30,0x49,0x79,0x41,0x3E},	// @
 
	{0x00,0x7E,0x11,0x11,0x11,0x7E},	// A
	{0x00,0x7F,0x49,0x49,0x49,0x36},	// B
	{0x00,0x3E,0x41,0x41,0x41,0x22},	// C
	{0x00,0x7F,0x41,0x41,0x22,0x1C},	// D
	{0x00,0x7F,0x49,0x49,0x49,0x41},	// E
	{0x00,0x7F,0x09,0x09,0x09,0x01},	// F
	{0x00,0x3E,0x41,0x49,0x49,0x7A},	// G
	{0x00,0x7F,0x08,0x08,0x08,0x7F},	// H
	{0x00,0x00,0x41,0x7F,0x41,0x00},	// I
	{0x00,0x20,0x40,0x41,0x3F,0x01},	// J
	{0x00,0x7F,0x08,0x14,0x22,0x41},	// K
	{0x00,0x7F,0x40,0x40,0x40,0x40},	// L
	{0x00,0x7F,0x02,0x0C,0x02,0x7F},	// M
	{0x00,0x7F,0x04,0x08,0x10,0x7F},	// N
	{0x00,0x3E,0x41,0x41,0x41,0x3E},	// O
	{0x00,0x7F,0x09,0x09,0x09,0x06},	// P
	{0x00,0x3E,0x41,0x51,0x21,0x5E},	// Q
	{0x00,0x7F,0x09,0x19,0x29,0x46},	// R
	{0x00,0x46,0x49,0x49,0x49,0x31},	// S
	{0x00,0x01,0x01,0x7F,0x01,0x01},	// T
	{0x00,0x3F,0x40,0x40,0x40,0x3F},	// U
	{0x00,0x1F,0x20,0x40,0x20,0x1F},	// V
	{0x00,0x3F,0x40,0x30,0x40,0x3F},	// W
	{0x00,0x63,0x14,0x08,0x14,0x63},	// X
	{0x00,0x07,0x08,0x70,0x08,0x07},	// Y
	{0x00,0x61,0x51,0x49,0x45,0x43},	// Z
 
	{0x00,0x00,0x7F,0x41,0x41,0x00},	// [
	{0x00,0x02,0x04,0x08,0x10,0x20},	// backslash
	{0x00,0x00,0x41,0x41,0x7F,0x00},	// ]
	{0x00,0x04,0x02,0x01,0x02,0x04},	// ^
	{0x00,0x40,0x40,0x40,0x40,0x40},	// _
	{0x00,0x00,0x01,0x02,0x04,0x00},	// `
 
	{0x00,0x20,0x54,0x54,0x54,0x78},	// a
	{0x00,0x7F,0x50,0x48,0x48,0x30},	// b
	{0x00,0x38,0x44,0x44,0x44,0x20},	// c
	{0x00,0x38,0x44,0x44,0x48,0x7F},	// d
	{0x00,0x38,0x54,0x54,0x54,0x18},	// e
	{0x00,0x08,0x7E,0x09,0x01,0x02},	// f
	{0x00,0x0C,0x52,0x52,0x52,0x3E},	// g
	{0x00,0x7F,0x08,0x04,0x04,0x78},	// h
	{0x00,0x00,0x44,0x7D,0x40,0x00},	// i
	{0x00,0x20,0x40,0x44,0x3D,0x00},	// j
	{0x00,0x7F,0x10,0x28,0x44,0x00},	// k
	{0x00,0x00,0x41,0x7F,0x40,0x00},	// l
	{0x00,0x78,0x04,0x58,0x44,0x78},	// m
	{0x00,0x7C,0x08,0x04,0x04,0x78},	// n
	{0x00,0x38,0x44,0x44,0x44,0x38},	// o
	{0x00,0x7C,0x14,0x14,0x14,0x08},	// p
	{0x00,0x08,0x14,0x14,0x18,0x7C},	// q
	{0x00,0x7C,0x08,0x04,0x04,0x08},	// r
	{0x00,0x48,0x54,0x54,0x54,0x20},	// s
	{0x00,0x04,0x3F,0x44,0x40,0x20},	// t
	{0x00,0x3C,0x40,0x40,0x20,0x7C},	// u
	{0x00,0x1C,0x20,0x40,0x20,0x1C},	// v
	{0x00,0x3C,0x40,0x30,0x40,0x3C},	// w
	{0x00,0x44,0x28,0x10,0x28,0x44},	// x
	{0x00,0x0C,0x50,0x50,0x50,0x3C},	// y
	{0x00,0x44,0x64,0x54,0x4C,0x44},	// z
 
	{0x00,0x00,0x08,0x36,0x41,0x00},	// {
	{0x00,0x00,0x00,0x7F,0x00,0x00},	// |
	{0x00,0x00,0x41,0x36,0x08,0x00},	// }
	{0x00,0x0C,0x02,0x0C,0x10,0x0C},	// ~
 
	{0x00,0x00,0x00,0x00,0x00,0x00}
};

/**************************************************************************//**
*  @brief Performs all required initialization for this component and fills the screen with black
*
*******************************************************************************/
void `$INSTANCE_NAME`_Start(void)
{
    //`$INSTANCE_NAME`_SPIM_1_Start();
    
    `$INSTANCE_NAME`_CS_HIGH();
    `$INSTANCE_NAME`_DC_HIGH();
    
    cursor_y = cursor_x = 0;
    textsize = 1;
    textcolor = textbgcolor = 0xFFFF;
    wrap = 1;
	rotation = 0;
	_width = TFTWIDTH;
	_height = TFTHEIGHT;
	
	CyDelay(500);
	`$INSTANCE_NAME`_SendCmd(0x01);
	CyDelay(200);
	
	`$INSTANCE_NAME`_SendCmd(0xCF);
    `$INSTANCE_NAME`_SendData(0x00);
    `$INSTANCE_NAME`_SendData(0x8B);
    `$INSTANCE_NAME`_SendData(0x30);

    `$INSTANCE_NAME`_SendCmd(0xED);
    `$INSTANCE_NAME`_SendData(0x67);
    `$INSTANCE_NAME`_SendData(0x03);
    `$INSTANCE_NAME`_SendData(0x12);
    `$INSTANCE_NAME`_SendData(0x81);

    `$INSTANCE_NAME`_SendCmd(0xE8);
    `$INSTANCE_NAME`_SendData(0x85);
    `$INSTANCE_NAME`_SendData(0x10);
    `$INSTANCE_NAME`_SendData(0x7A);

    `$INSTANCE_NAME`_SendCmd(0xCB);
    `$INSTANCE_NAME`_SendData(0x39);
    `$INSTANCE_NAME`_SendData(0x2C);
    `$INSTANCE_NAME`_SendData(0x00);
    `$INSTANCE_NAME`_SendData(0x34);
    `$INSTANCE_NAME`_SendData(0x02);

    `$INSTANCE_NAME`_SendCmd(0xF7);
    `$INSTANCE_NAME`_SendData(0x20);

    `$INSTANCE_NAME`_SendCmd(0xEA);
    `$INSTANCE_NAME`_SendData(0x00);
    `$INSTANCE_NAME`_SendData(0x00);

    `$INSTANCE_NAME`_SendCmd(0xC0);                                                      /* Power control*/
    `$INSTANCE_NAME`_SendData(0x1B);                                                   /* VRH[5:0]*/

    `$INSTANCE_NAME`_SendCmd(0xC1);                                                      /* Power control*/
    `$INSTANCE_NAME`_SendData(0x10);                                                   /* SAP[2:0];BT[3:0]*/

    `$INSTANCE_NAME`_SendCmd(0xC5);                                                      /* VCM control*/
    `$INSTANCE_NAME`_SendData(0x3F);
    `$INSTANCE_NAME`_SendData(0x3C);

    `$INSTANCE_NAME`_SendCmd(0xC7);                                                      /* VCM control2*/
    `$INSTANCE_NAME`_SendData(0xB7);

    `$INSTANCE_NAME`_SendCmd(0x36);                                                      /* Memory Access Control*/
    `$INSTANCE_NAME`_SendData(0x08);

    `$INSTANCE_NAME`_SendCmd(0x3A);
    `$INSTANCE_NAME`_SendData(0x55);

    `$INSTANCE_NAME`_SendCmd(0xB1);
    `$INSTANCE_NAME`_SendData(0x00);
    `$INSTANCE_NAME`_SendData(0x1B);

    `$INSTANCE_NAME`_SendCmd(0xB6);                                                      /* Display Function Control*/
    `$INSTANCE_NAME`_SendData(0x0A);
    `$INSTANCE_NAME`_SendData(0xA2);


    `$INSTANCE_NAME`_SendCmd(0xF2);                                                      /* 3Gamma Function Disable*/
    `$INSTANCE_NAME`_SendData(0x00);

    `$INSTANCE_NAME`_SendCmd(0x26);                                                      /* Gamma curve selected*/
    `$INSTANCE_NAME`_SendData(0x01);

    `$INSTANCE_NAME`_SendCmd(0xE0);                                                      /* Set Gamma*/
    `$INSTANCE_NAME`_SendData(0x0F);
    `$INSTANCE_NAME`_SendData(0x2A);
    `$INSTANCE_NAME`_SendData(0x28);
    `$INSTANCE_NAME`_SendData(0x08);
    `$INSTANCE_NAME`_SendData(0x0E);
    `$INSTANCE_NAME`_SendData(0x08);
    `$INSTANCE_NAME`_SendData(0x54);
    `$INSTANCE_NAME`_SendData(0xA9);
    `$INSTANCE_NAME`_SendData(0x43);
    `$INSTANCE_NAME`_SendData(0x0A);
    `$INSTANCE_NAME`_SendData(0x0F);
    `$INSTANCE_NAME`_SendData(0x00);
    `$INSTANCE_NAME`_SendData(0x00);
    `$INSTANCE_NAME`_SendData(0x00);
    `$INSTANCE_NAME`_SendData(0x00);
	`$INSTANCE_NAME`_SendCmd(0xE1);                                                      /* Set Gamma*/
    `$INSTANCE_NAME`_SendData(0x00);
    `$INSTANCE_NAME`_SendData(0x15);
    `$INSTANCE_NAME`_SendData(0x17);
    `$INSTANCE_NAME`_SendData(0x07);
    `$INSTANCE_NAME`_SendData(0x11);
    `$INSTANCE_NAME`_SendData(0x06);
    `$INSTANCE_NAME`_SendData(0x2B);
    `$INSTANCE_NAME`_SendData(0x56);
    `$INSTANCE_NAME`_SendData(0x3C);
    `$INSTANCE_NAME`_SendData(0x05);
    `$INSTANCE_NAME`_SendData(0x10);
    `$INSTANCE_NAME`_SendData(0x0F);
    `$INSTANCE_NAME`_SendData(0x3F);
    `$INSTANCE_NAME`_SendData(0x3F);
    `$INSTANCE_NAME`_SendData(0x0F);
	`$INSTANCE_NAME`_SendCmd(0x11);                                                      /* Exit Sleep*/
    CyDelay(120);
    `$INSTANCE_NAME`_SendCmd(0x29);
	//`$INSTANCE_NAME`_SetRotation(0);
	/* Display on*/
    `$INSTANCE_NAME`_FillScreen(BLACK);
}

/**************************************************************************//**
* @brief Colors a single pixel
*
* @param Pos_X The x coordinate of the pixel (0 - 240)
* @param Pos_Y The y coordinate of the pixel (0 - 320)
* @param Color: The 16-bit color of the pixel (0-0xFFFF)
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetPixel(uint16 Pos_X, uint16 Pos_Y, uint16 Color)
{
	`$INSTANCE_NAME`_GotoXY(Pos_X, Pos_Y);
	`$INSTANCE_NAME`_SendData16(Color);
}

/**************************************************************************//**
*  @brief Moves to a pixel without changing it
*
*  @param Pos_X: The x coordinate of the pixel (0 - 240)
*  @param Pos_Y: The y coordinate of the pixel (0 - 320)
*
*******************************************************************************/
void `$INSTANCE_NAME`_GotoXY(uint16 Pos_X, uint16 Pos_Y)
{
	`$INSTANCE_NAME`_SetCol(Pos_X, Pos_X);
	`$INSTANCE_NAME`_SetPage(Pos_Y, Pos_Y);
	`$INSTANCE_NAME`_SendCmd(0x2C);
}

/***************************************************************************//**
*  @brief Specify a page on the TFT
*
*  @param Start_Page: The start page
*  @param End_Page: The end page
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetPage(uint16 Start_Page, uint16 End_Page)
{
	`$INSTANCE_NAME`_SendCmd(0x2B);
	`$INSTANCE_NAME`_SendData16(Start_Page);
	`$INSTANCE_NAME`_SendData16(End_Page);
}

/**************************************************************************//**
*  @brief Sets the address window (rectangle of pixels) to fill in 
*
*  @param x0: The starting x coordinate
*  @param y0: The starting y coordinate
*  @param x1: The ending x coordinate
*  @param y1: The ending y coordinate
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetAddrWindow(uint16_t x0, uint16_t y0, uint16_t x1,
 uint16_t y1)
{
    `$INSTANCE_NAME`_SendCmd(0x2A); //column addr set
    `$INSTANCE_NAME`_SendData16(x0); //x start
    `$INSTANCE_NAME`_SendData16(x1); //x end
    
    `$INSTANCE_NAME`_SendCmd(0x2B); //row addr set
    `$INSTANCE_NAME`_SendData16(y0);//y start
    `$INSTANCE_NAME`_SendData16(y1);//y end
    
    `$INSTANCE_NAME`_SendCmd(0x2C); //write to RAM
}

/**************************************************************************//**
*  @brief Fills a rectangle of pixels with a specified color
*
*  @param x: The starting x coordinate
*  @param y: The starting y coordinate
*  @param w: The width of the rectangle
*  @param h: The height of the rectangle
*  @param color: The color of the rectangle
*
*******************************************************************************/
void `$INSTANCE_NAME`_FillRect(int16_t x, int16_t y, int16_t w, int16_t h,
  uint16_t color) 
{
   // rudimentary clipping (drawChar w/big text requires this)
  if((x >= _width) || (y >= _height)) return;
  if((x + w - 1) >= _width)  w = _width  - x;
  if((y + h - 1) >= _height) h = _height - y;

  `$INSTANCE_NAME`_SetAddrWindow(x, y, x+w-1, y+h-1);
    
  uint8_t hi = color >> 8, lo = color;

  //*dcport |=  dcpinmask;
  `$INSTANCE_NAME`_DC_HIGH();
  //digitalWrite(_dc, HIGH);
  //*csport &= ~cspinmask;
  //digitalWrite(_cs, LOW);
  `$INSTANCE_NAME`_CS_LOW();

  for(y=h; y>0; y--) {
    for(x=w; x>0; x--) {
      `$INSTANCE_NAME`_SPITransfer(hi);
      `$INSTANCE_NAME`_SPITransfer(lo);
    }
  }
  //digitalWrite(_cs, HIGH);
  //*csport |= cspinmask;
  `$INSTANCE_NAME`_CS_HIGH();
 
}

/**************************************************************************//**
*  @brief Fills the TFT with a specified color
*
*  @param color: The color to fill the screen with
*
*******************************************************************************/
void `$INSTANCE_NAME`_FillScreen(uint16_t color)
{
    //Just fills a fullscreen rect
    `$INSTANCE_NAME`_FillRect(0,0,_width,_height,color);
}

/**************************************************************************//**
*  @brief Sets the column on the TFT
*
*  @param Start_Col: The start column
*  @param End_Col: The end column
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetCol(uint16 Start_Col, uint16 End_Col)
{	
	`$INSTANCE_NAME`_SendCmd(0x2A);
	`$INSTANCE_NAME`_SendData16(Start_Col);
	`$INSTANCE_NAME`_SendData16(End_Col);
}

/**************************************************************************//**
*  @brief Sends 16 bits data to the TFT
*
*  @param Data16: The data to send
*
*******************************************************************************/
void `$INSTANCE_NAME`_SendData16(uint16 Data16)
{
	uint8 MSB, LSB;
	
	MSB = Data16 >> 8;
	LSB = Data16 & 0xFF;
	
	`$INSTANCE_NAME`_DC_HIGH();
	`$INSTANCE_NAME`_CS_LOW();
	
	`$INSTANCE_NAME`_SPITransfer(MSB);
	`$INSTANCE_NAME`_SPITransfer(LSB);
	
	`$INSTANCE_NAME`_CS_HIGH();
}

/**************************************************************************//**
*  @brief Sends 8 bits data to the TFT
*
*  @param dat: The data to send
*
*******************************************************************************/
void `$INSTANCE_NAME`_SendData(uint8 dat)
{
	`$INSTANCE_NAME`_DC_HIGH();
	`$INSTANCE_NAME`_CS_LOW();
	
	`$INSTANCE_NAME`_SPITransfer(dat);
	
	`$INSTANCE_NAME`_CS_HIGH();
}

/**************************************************************************//**
*  @brief Sends a command to the TFT
*
*  @param cmd: The command data to send
*
*******************************************************************************/
void `$INSTANCE_NAME`_SendCmd(uint8 cmd)
{
	`$INSTANCE_NAME`_DC_LOW();
	`$INSTANCE_NAME`_CS_LOW();
	
	`$INSTANCE_NAME`_SPITransfer(cmd);
	
	`$INSTANCE_NAME`_CS_HIGH();
}

/**************************************************************************//**
*  @brief Sends 8 bits of data to the TFT over SPI
*
*  @param data8: The data to send
*
*******************************************************************************/
void `$INSTANCE_NAME`_SPITransfer(uint8 data8)
{	
	//SPIM_1_SpiUART_1WriteTxData((uint32)data8);
    `$INSTANCE_NAME`_SPIM_1_WriteTxData(data8);

	//CyDelayUs(1);
}

/**************************************************************************//**
*  @brief Draws a vertical line
*
*  @param Pos_X: The starting x coordinate
*  @param Pos_Y: The starting y coordinate
*  @param Length: The length of the line
*  @param Color: The color of the line
*
*******************************************************************************/
void `$INSTANCE_NAME`_DrawVLine(uint16 Pos_X, uint16 Pos_Y, uint16 Length, uint16 Color)
{
	uint16 index;
	`$INSTANCE_NAME`_SetCol(Pos_X, Pos_X);
	`$INSTANCE_NAME`_SetPage(Pos_Y, Pos_Y + Length);
	`$INSTANCE_NAME`_SendCmd(0x2C);
	
	`$INSTANCE_NAME`_DC_HIGH();
	`$INSTANCE_NAME`_CS_LOW();
	
	for(index = 0; index < Length; index++)
	{	
		`$INSTANCE_NAME`_SPITransfer(Color >> 8);
		`$INSTANCE_NAME`_SPITransfer(Color & 0xFF);	
	}
	
	`$INSTANCE_NAME`_CS_HIGH();
}

void `$INSTANCE_NAME`_DrawHLine(int16_t x, int16_t y,
				 int16_t w, uint16_t color) {
  
  `$INSTANCE_NAME`_DrawLine(x, y, x+w-1, y, color);
}

/**************************************************************************//**
*  @brief Draws a line
*
*  @param x1: The starting x coordinate
*  @param y1: The starting y coordinate
*  @param x2: The ending x coordinate
*  @param y2: The ending y coordinate
*  @param Color: The color of the line
*
*******************************************************************************/
void `$INSTANCE_NAME`_DrawLine( uint16 x1, uint16 y1, uint16 x2, uint16 y2, uint16 Color )
{
	short dx, dy, sdx, sdy, px, py, dxabs, dyabs, i;
	float slope;

	dx = x2 - x1;
	dy = y2 - y1;
	dxabs = sdx = 0;
	if( dx > 0 )
	{
		dxabs = dx;
		sdx = 1;
	}
	else if ( dx < 0 )
	{
		dxabs = -dx;
		sdx = -1;
	}
	dyabs = sdy = 0;
	if( dy > 0 )
	{
		dyabs = dy;
		sdy = 1;
	}
	else if ( dy < 0 )
	{
		dyabs = -dy;
		sdy = -1;
	}
	if ( dxabs >= dyabs )		/* the line is more horizontal than vertical */
	{
		slope = ( float ) dy / ( float ) dx;
		for ( i = 0; i != dx; i += sdx )
		{
			px = i + x1;
			py = slope * i + y1;
			`$INSTANCE_NAME`_SetPixel( px, py, Color );
		}
	}
	else				/* the line is more vertical than horizontal */
	{
		slope = ( float ) dx / ( float ) dy;
		for ( i = 0; i != dy; i += sdy )
		{
			px = slope * i + x1;
			py = i + y1;
			`$INSTANCE_NAME`_SetPixel( px, py, Color );
		}
	}
}

/**************************************************************************//**
*  @brief Draws a rectangle outline
*
*  @param x: The x coordinate
*  @param y: The y coordinate
*  @param w: The width
*  @param h: The height
*  @param color: The color of the rectangle
*
*******************************************************************************/
void `$INSTANCE_NAME`_DrawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
{
   `$INSTANCE_NAME`_DrawHLine(x, y, w, color);
  `$INSTANCE_NAME`_DrawHLine(x, y+h-1, w, color);
  `$INSTANCE_NAME`_DrawVLine(x, y, h, color);
  `$INSTANCE_NAME`_DrawVLine(x+w-1, y, h, color);
}

/**************************************************************************//**
*  @brief Draws a circle outline
*
*  @param x0: The x coordinate
*  @param y0: The y coordinate
*  @param r: The radius of the circle
*  @param color: The color of the circle
*
*******************************************************************************/

void `$INSTANCE_NAME`_DrawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color)
{
  int16_t f = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x = 0;
  int16_t y = r;

  `$INSTANCE_NAME`_SetPixel(x0  , y0+r, color);
  `$INSTANCE_NAME`_SetPixel(x0  , y0-r, color);
  `$INSTANCE_NAME`_SetPixel(x0+r, y0  , color);
  `$INSTANCE_NAME`_SetPixel(x0-r, y0  , color);

  while (x<y) {
        if (f >= 0) {
          y--;
          ddF_y += 2;
          f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;
      
        `$INSTANCE_NAME`_SetPixel(x0 + x, y0 + y, color);
        `$INSTANCE_NAME`_SetPixel(x0 - x, y0 + y, color);
        `$INSTANCE_NAME`_SetPixel(x0 + x, y0 - y, color);
        `$INSTANCE_NAME`_SetPixel(x0 - x, y0 - y, color);
        `$INSTANCE_NAME`_SetPixel(x0 + y, y0 + x, color);
        `$INSTANCE_NAME`_SetPixel(x0 - y, y0 + x, color);
        `$INSTANCE_NAME`_SetPixel(x0 + y, y0 - x, color);
        `$INSTANCE_NAME`_SetPixel(x0 - y, y0 - x, color); 
    }
}

/**************************************************************************//**
*  @brief Helper function for drawing circles and corners
*
*  @param x0: The x coordinate
*  @param y0: The y coordinate
*  @param r: The radius of the circle
*  @param cornername: Corner orientation
*  @param delta: Delta value
*  @param color: The color of the circle
*
*******************************************************************************/
void `$INSTANCE_NAME`_DrawCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername,
      uint16_t color)
{
  int16_t f     = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x     = 0;
  int16_t y     = r;

  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f     += ddF_y;
    }
    x++;
    ddF_x += 2;
    f     += ddF_x;
    if (cornername & 0x4) {
      `$INSTANCE_NAME`_SetPixel(x0 + x, y0 + y, color);
      `$INSTANCE_NAME`_SetPixel(x0 + y, y0 + x, color);
    } 
    if (cornername & 0x2) {
      `$INSTANCE_NAME`_SetPixel(x0 + x, y0 - y, color);
      `$INSTANCE_NAME`_SetPixel(x0 + y, y0 - x, color);
    }
    if (cornername & 0x8) {
      `$INSTANCE_NAME`_SetPixel(x0 - y, y0 + x, color);
      `$INSTANCE_NAME`_SetPixel(x0 - x, y0 + y, color);
    }
    if (cornername & 0x1) {
      `$INSTANCE_NAME`_SetPixel(x0 - y, y0 - x, color);
      `$INSTANCE_NAME`_SetPixel(x0 - x, y0 - y, color);
    }
  }
}

/**************************************************************************//**
*  @brief Draws a circle filled in with the specified color
*
*  @param x0: The x coordinate
*  @param y0: The y coordinate
*  @param r: The radius of the circle
*  @param color: The color of the circle
*
*******************************************************************************/
void `$INSTANCE_NAME`_FillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color)
{
    `$INSTANCE_NAME`_DrawVLine(x0, y0-r, 2*r+1, color);
    `$INSTANCE_NAME`_FillCircleHelper(x0, y0, r, 3, 0, color);
}

/**************************************************************************//**
*  @brief Helper function for filling circles and corners
*
*  @param x0: The x coordinate
*  @param y0: The y coordinate
*  @param r: The radius of the circle
*  @param cornername: Corner orientation
*  @param delta: Delta value
*  @param color: The color of the circle
*
*******************************************************************************/
void `$INSTANCE_NAME`_FillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername,
      int16_t delta, uint16_t color)
{
  int16_t f     = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x     = 0;
  int16_t y     = r;

  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f     += ddF_y;
    }
    x++;
    ddF_x += 2;
    f     += ddF_x;

    if (cornername & 0x1) {
      `$INSTANCE_NAME`_DrawVLine(x0+x, y0-y, 2*y+1+delta, color);
      `$INSTANCE_NAME`_DrawVLine(x0+y, y0-x, 2*x+1+delta, color);
    }
    if (cornername & 0x2) {
      `$INSTANCE_NAME`_DrawVLine(x0-x, y0-y, 2*y+1+delta, color);
     `$INSTANCE_NAME`_DrawVLine(x0-y, y0-x, 2*x+1+delta, color);
    }
  }
}

/**************************************************************************//**
*  @brief Draws a triangle outline
*
*  @param x0: The first x coordinate
*  @param y0: The first y coordinate
*  @param x1: The second x coordinate
*  @param y1: The second y coordinate
*  @param x2: The third x coordinate
*  @param y2: The third y coordinate
*  @param color: The color of the triangle
*
*******************************************************************************/
void `$INSTANCE_NAME`_DrawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
      int16_t x2, int16_t y2, uint16_t color)
{
    `$INSTANCE_NAME`DrawLine(x0, y0, x1, y1, color);
    `$INSTANCE_NAME`DrawLine(x1, y1, x2, y2, color);
    `$INSTANCE_NAME`DrawLine(x2, y2, x0, y0, color);
}

/**************************************************************************//**
*  @brief Draws a triangle filled with the specified color
*
*  @param x0: The first x coordinate
*  @param y0: The first y coordinate
*  @param x1: The second x coordinate
*  @param y1: The second y coordinate
*  @param x2: The third x coordinate
*  @param y2: The third y coordinate
*  @param color: The color of the triangle
*
*******************************************************************************/
void `$INSTANCE_NAME`_FillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
      int16_t x2, int16_t y2, uint16_t color)
{
     int16_t a, b, y, last;

  // Sort coordinates by Y order (y2 >= y1 >= y0)
  if (y0 > y1) {
    swap(y0, y1); swap(x0, x1);
  }
  if (y1 > y2) {
    swap(y2, y1); swap(x2, x1);
  }
  if (y0 > y1) {
    swap(y0, y1); swap(x0, x1);
  }

  if(y0 == y2) { // Handle awkward all-on-same-line case as its own thing
    a = b = x0;
    if(x1 < a)      a = x1;
    else if(x1 > b) b = x1;
    if(x2 < a)      a = x2;
    else if(x2 > b) b = x2;
    `$INSTANCE_NAME`DrawLine(a, y0, b-a+1, color);
    return;
  }

  int16_t
    dx01 = x1 - x0,
    dy01 = y1 - y0,
    dx02 = x2 - x0,
    dy02 = y2 - y0,
    dx12 = x2 - x1,
    dy12 = y2 - y1,
    sa   = 0,
    sb   = 0;

  // For upper part of triangle, find scanline crossings for segments
  // 0-1 and 0-2.  If y1=y2 (flat-bottomed triangle), the scanline y1
  // is included here (and second loop will be skipped, avoiding a /0
  // error there), otherwise scanline y1 is skipped here and handled
  // in the second loop...which also avoids a /0 error here if y0=y1
  // (flat-topped triangle).
  if(y1 == y2) last = y1;   // Include y1 scanline
  else         last = y1-1; // Skip it

  for(y=y0; y<=last; y++) {
        a   = x0 + sa / dy01;
        b   = x0 + sb / dy02;
        sa += dx01;
        sb += dx02;
        /* longhand:
        a = x0 + (x1 - x0) * (y - y0) / (y1 - y0);
        b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
        */
        if(a > b) swap(a,b);
        `$INSTANCE_NAME`DrawLine(a, y, b-a+1, color);
    }
}

/**************************************************************************//**
*  @brief Draws a rectangle outline with rounded corners
*
*  @param x: The x coordinate
*  @param y: The y coordinate
*  @param w: The width
*  @param h: The height
*  @param r: The radius of the rounded corners
*  @param color: The color of the rectangle
*
*******************************************************************************/
void `$INSTANCE_NAME`_DrawRoundRect(int16_t x, int16_t y, int16_t w, int16_t h,
      int16_t r, uint16_t color)
{
    // smarter version
  `$INSTANCE_NAME`_DrawHLine(x+r  , y    , w-2*r, color); // Top
  `$INSTANCE_NAME`_DrawHLine(x+r  , y+h-1, w-2*r, color); // Bottom
  `$INSTANCE_NAME`_DrawVLine(x    , y+r  , h-2*r, color); // Left
  `$INSTANCE_NAME`_DrawVLine(x+w-1, y+r  , h-2*r, color); // Right
  // draw four corners
  `$INSTANCE_NAME`_DrawCircleHelper(x+r    , y+r    , r, 1, color);
  `$INSTANCE_NAME`_DrawCircleHelper(x+w-r-1, y+r    , r, 2, color);
  `$INSTANCE_NAME`_DrawCircleHelper(x+w-r-1, y+h-r-1, r, 4, color);
  `$INSTANCE_NAME`_DrawCircleHelper(x+r    , y+h-r-1, r, 8, color);
}

/**************************************************************************//**
*  @brief Draws a rectangle filled with the specified color and with rounded corners
*
*  @param x: The x coordinate
*  @param y: The y coordinate
*  @param w: The width
*  @param h: The height
*  @param r: The radius of the rounded corners
*  @param color: The color of the rectangle
*
*******************************************************************************/
void `$INSTANCE_NAME`_FillRoundRect(int16_t x, int16_t y, int16_t w, int16_t h,
      int16_t r, uint16_t color)
{
    // smarter version
  `$INSTANCE_NAME`_FillRect(x+r, y, w-2*r, h, color);

  // draw four corners
  `$INSTANCE_NAME`_FillCircleHelper(x+w-r-1, y+r, r, 1, h-2*r-1, color);
  `$INSTANCE_NAME`_FillCircleHelper(x+r    , y+r, r, 2, h-2*r-1, color);
}


/**************************************************************************//**
*  @brief Prints a string of ascii txt
*
*  @param string: The string to print
*
*******************************************************************************/
void `$INSTANCE_NAME`_Print(char8 const string[]) 
{
    uint8 indexU8 = 1u;
    char8 current = *string;

    /* Until null is reached, print next character */
    while((char8) '\0' != current)
    {
        `$INSTANCE_NAME`_Write((uint8)current);
        current = string[indexU8];
        indexU8++;
    }
}

/**************************************************************************//**
*  @brief Prints a string of ascii txt with word wrap
*
*  @param string: The string to print
*
*******************************************************************************/
void `$INSTANCE_NAME`_PrintString(char8 string[])
{
	char * st = string;
	char temp[1024];
	strcpy(temp,st);
	
	char * word;
	char * unused;
	//separate words in string
	word = strtok(temp, " \t");
	int line_width = _width - textsize*6;
	int space_left = line_width - cursor_x;
	int length_word = 0;
	//each char is textsize*6
	//need to strtok string to get individual words for word wrap
	while ( word != NULL )
	{
		
		//print word if it fits on screen
		length_word = textsize*6*strlen(word);
		//space = textsize*6
		if(length_word > space_left)
		{
			cursor_y += textsize*8;
			cursor_x = 0;
			space_left = line_width - length_word;
			
		}
		else
		{
			space_left = space_left - length_word - (textsize*6);
		}
		//print word
		`$INSTANCE_NAME`_Print(word);
		//print space
		`$INSTANCE_NAME`_Print(" ");
		
        //strtok next word in string
		word = strtok( NULL, " \t");
		
	}
	
	
}

/**************************************************************************//**
*  @brief Writes a single character
*
*  @param c: The character to write
*
*******************************************************************************/
void `$INSTANCE_NAME`_Write(uint8_t c)
{
    if (c == '\n') 
    {
        cursor_y += textsize*8;
        cursor_x  = 0;
    }
    else if (c == '\r') 
    {
        // clear screen and reset cursor
        `$INSTANCE_NAME`_FillScreen(BLACK);
        cursor_y = 0;
        cursor_x = 0;
    } 
    else 
    {
        `$INSTANCE_NAME`_DrawChar(cursor_x, cursor_y, c, textcolor, textbgcolor, textsize);
        cursor_x += textsize*6;
        /*if (wrap && (cursor_x > (TFTWIDTH - textsize*6))) 
        {
          cursor_y += textsize*8;
          cursor_x = 0;
        }*/
    }
}

/**************************************************************************//**
*  @brief Draws character
*
*  @param x: The starting x coordinate
*  @param y: The starting y coordinate
*  @param c: The character to draw
*  @param color: The color of the character
*  @param bg: The depth of the character
*  @param size: The font size of the character
*
*******************************************************************************/
void `$INSTANCE_NAME`_DrawChar(int16_t x, int16_t y, unsigned char c,
			    uint16_t color, uint16_t bg, uint8_t size)
{
    if((x >= _width)            || // Clip right
     (y >= _height)           || // Clip bottom
     ((x + 6 * size - 1) < 0) || // Clip left
     ((y + 8 * size - 1) < 0))   // Clip top
    return;
  int8_t i,j;  
  for (i=0; i<6; i++ ) {
    uint8_t line;
    if (i == 6) 
       line = 0x0;
    else 
      line = fontA[c][i];
    for (j = 0; j<8; j++) {
      if (line & 0x1) {
        if (size == 1) // default size
          `$INSTANCE_NAME`_SetPixel(_width - (x+i), y+j, color);
        else {  // big size
          `$INSTANCE_NAME`_FillRect(_width - (x+(i*size)), y+(j*size), size, size, color);
        } 
      } else if (bg != color) {
        if (size == 1) // default size
          `$INSTANCE_NAME`_SetPixel(_width - (x+i), y+j, bg);
        else {  // big size
          `$INSTANCE_NAME`_FillRect(_width - (x+i*size), y+j*size, size, size, bg);
        }
      }
      line >>= 1;
    }
  }
}

/**************************************************************************//**
*  @brief Sets the cursor for writing text
*
*  @param x: The x position of the cursor
*  @param y: The y position of the cursor
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetCursor(int16_t x, int16_t y) {
  cursor_x = x;
  cursor_y = y;
}

/**************************************************************************//**
*  @brief Set the text size
*
*  @param s: Sets the font size
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetTextSize(uint8_t s) {
  textsize = (s > 0) ? s : 1;
}

/**************************************************************************//**
*  @brief Sets the color of the text
*
*  @param c: Sets the color
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetTextColor(uint16_t c)
{
  // For 'transparent' background, we'll set the bg 
  // to the same as fg instead of using a flag
  textcolor = textbgcolor = c;
}

/**************************************************************************//**
*  @brief Draws a vertical line
*
*  @param w: If true sets text wrap, else text wrap is off
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetTextWrap(uint8_t w) {
  wrap = w;
}

/**************************************************************************//**
*  @brief Pass 8-bit (each) R,G,B, get back 16-bit packed color
*
*  @param r: 8-bit red value
*  @param g: 8-bit green value
*  @param b: 8-bit blue value
*
*  @return 16-bit color value
*
*******************************************************************************/
uint16_t `$INSTANCE_NAME`_Color565(uint8_t r, uint8_t g, uint8_t b)
{
    return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}


/**************************************************************************//**
*  @brief Sets screen orientation
*
*  @param r: Orientation from 0-3
*  0 and 2: Portrait with opposite starting points
*  1 and 3: Landscape with opposite starting points
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetRotation(uint8_t r)
{
	//writecommand(ILI9341_MADCTL);
	`$INSTANCE_NAME`_SendCmd(ILI9341_MADCTL);
	rotation = r % 4; // can't be higher than 3
  switch (rotation) {
   case 0:
	 //writedata(MADCTL_MX | MADCTL_BGR);
	 `$INSTANCE_NAME`_SendData(MADCTL_MX | MADCTL_BGR);
	 _width  = TFTWIDTH;
	 _height = TFTHEIGHT;
	 break;
   case 1:
	 //writedata(MADCTL_MV | MADCTL_BGR);
	 `$INSTANCE_NAME`_SendData(MADCTL_MV | MADCTL_BGR);
	 _width  = TFTHEIGHT;
	 _height = TFTWIDTH;
	 break;
  case 2:
	//writedata(MADCTL_MY | MADCTL_BGR);
	`$INSTANCE_NAME`_SendData(MADCTL_MY | MADCTL_BGR);
	 _width  = TFTWIDTH;
	 _height = TFTHEIGHT;
	break;
   case 3:
	 //writedata(MADCTL_MX | MADCTL_MY | MADCTL_MV | MADCTL_BGR);
	 `$INSTANCE_NAME`_SendData(MADCTL_MX | MADCTL_MY | MADCTL_MV | MADCTL_BGR);
	 _width  = TFTHEIGHT;
	 _height = TFTWIDTH;
	 break;
  }
}


/**************************************************************************//**
*  @brief Sets command select line to low
*
*******************************************************************************/
void `$INSTANCE_NAME`_CS_LOW(void)
{
    uint8 temp = `$INSTANCE_NAME`_CR_1_Read();
    temp &= 0x0E;
    `$INSTANCE_NAME`_CR_1_Write(temp);
}

/**************************************************************************//**
*  @brief Sets command select line to high
*
*******************************************************************************/
void `$INSTANCE_NAME`_CS_HIGH(void)
{
    uint8 temp = `$INSTANCE_NAME`_CR_1_Read();
    temp |= 0x01;
    `$INSTANCE_NAME`_CR_1_Write(temp);
}

/**************************************************************************//**
*  @brief Sets data select line to low
*
*******************************************************************************/
void `$INSTANCE_NAME`_DC_LOW(void)
{
    uint8 temp = `$INSTANCE_NAME`_CR_1_Read();
    temp &= 0x0D;
    `$INSTANCE_NAME`_CR_1_Write(temp);
}

/**************************************************************************//**
*  @brief Sets data select line to high
*
*******************************************************************************/
void `$INSTANCE_NAME`_DC_HIGH(void)
{
    uint8 temp = `$INSTANCE_NAME`_CR_1_Read();
    temp |= 0x02;
    `$INSTANCE_NAME`_CR_1_Write(temp);
}

//Touchscreen. SPI clock must be set to 1MHZ before calling any of these functions!

/**************************************************************************//**
*  @brief Sets touchscreen command select line to low
*
*******************************************************************************/
void `$INSTANCE_NAME`_RT_CS_LOW(void)
{
    uint8 temp = `$INSTANCE_NAME`_CR_1_Read();
    temp &= 0x0B;
    `$INSTANCE_NAME`_CR_1_Write(temp);
}

/**************************************************************************//**
*  @brief Sets touchscreen command select line to high
*
*******************************************************************************/
void `$INSTANCE_NAME`_RT_CS_HIGH(void)
{
    uint8 temp = `$INSTANCE_NAME`_CR_1_Read();
    temp |= 0x04;
    `$INSTANCE_NAME`_CR_1_Write(temp);
}


/**************************************************************************//**
*  @brief Initializes touchscreen
*
*******************************************************************************/
bool `$INSTANCE_NAME`_StartTouch(void)
{
    `$INSTANCE_NAME`_SPIM_1_Start();
    if (`$INSTANCE_NAME`_GetVersion() != 0x811)
    {
        return false;
    }
    
    `$INSTANCE_NAME`_RT_CS_HIGH();
    
    `$INSTANCE_NAME`_WriteRegister8(STMPE_SYS_CTRL1, STMPE_SYS_CTRL1_RESET);
    CyDelay(10);
    //char buf[50];
    uint8_t i;
    uint8_t val = 0;
    for (i=1; i<65; i++)
    {
        val = `$INSTANCE_NAME`_ReadRegister8(i);
        //sprintf(buf,"reg num %i = %i\n",i,val);
        //`$INSTANCE_NAME`_PrintString(buf);
    }

    `$INSTANCE_NAME`_WriteRegister8(STMPE_SYS_CTRL2, 0x0); // turn on clocks!
    `$INSTANCE_NAME`_WriteRegister8(STMPE_TSC_CTRL, STMPE_TSC_CTRL_XYZ | STMPE_TSC_CTRL_EN); // XYZ and enable!
    `$INSTANCE_NAME`_WriteRegister8(STMPE_INT_EN, STMPE_INT_EN_TOUCHDET);
    `$INSTANCE_NAME`_WriteRegister8(STMPE_ADC_CTRL1, STMPE_ADC_CTRL1_10BIT | (0x6 << 4)); // 96 clocks per conversion
    `$INSTANCE_NAME`_WriteRegister8(STMPE_ADC_CTRL2, STMPE_ADC_CTRL2_6_5MHZ);
    `$INSTANCE_NAME`_WriteRegister8(STMPE_TSC_CFG, STMPE_TSC_CFG_4SAMPLE | STMPE_TSC_CFG_DELAY_1MS | STMPE_TSC_CFG_SETTLE_5MS);
    `$INSTANCE_NAME`_WriteRegister8(STMPE_TSC_FRACTION_Z, 0x6);
    `$INSTANCE_NAME`_WriteRegister8(STMPE_FIFO_TH, 1);
    `$INSTANCE_NAME`_WriteRegister8(STMPE_FIFO_STA, STMPE_FIFO_STA_RESET);
    `$INSTANCE_NAME`_WriteRegister8(STMPE_FIFO_STA, 0);    // unreset
    `$INSTANCE_NAME`_WriteRegister8(STMPE_TSC_I_DRIVE, STMPE_TSC_I_DRIVE_50MA);
    `$INSTANCE_NAME`_WriteRegister8(STMPE_INT_STA, 0xFF); // reset all ints
    `$INSTANCE_NAME`_WriteRegister8(STMPE_INT_CTRL, STMPE_INT_CTRL_POL_HIGH | STMPE_INT_CTRL_ENABLE);

    
    /*for (i=1; i<65; i++)
    {
        val = `$INSTANCE_NAME`_ReadRegister8(i);
        //sprintf(buf,"reg num %i = %i\n",i,val);
        //`$INSTANCE_NAME`_PrintString(buf);
    }*/
    
    return true;
}

/**************************************************************************//**
*  @brief Writes register value to touchscreen
*
*  @param reg: register
*  @param val: value to be written
*
*******************************************************************************/
void `$INSTANCE_NAME`_WriteRegister8(uint16_t reg, uint16_t val)
{
    `$INSTANCE_NAME`_RT_CS_LOW();
     CyDelay(1);
    `$INSTANCE_NAME`_SPITransfer(reg);
     CyDelay(1);
    `$INSTANCE_NAME`_SPITransfer(val);
     CyDelay(1);
    `$INSTANCE_NAME`_RT_CS_HIGH();
}

/**************************************************************************//**
*  @brief Reads register value from touchscreen
*
*  @param reg: register
*
*  @return: 16 bit register value
*
*******************************************************************************/
uint16_t `$INSTANCE_NAME`_ReadRegister16(uint16_t reg)
{
    uint16_t output;
    
    `$INSTANCE_NAME`_RT_CS_LOW();
    `$INSTANCE_NAME`_SPIM_1_WriteTxData(0x80 | reg);
    `$INSTANCE_NAME`_SPIM_1_WriteTxData(0x00);
    
    while(!`$INSTANCE_NAME`_SPIM_1_GetRxBufferSize());
    //{
        //`$INSTANCE_NAME`_SPIM_1_WriteTxData(0);
        output = `$INSTANCE_NAME`_SPIM_1_ReadRxData();
        output <<= 8;
        while(!`$INSTANCE_NAME`_SPIM_1_GetRxBufferSize());
        //{
            //`$INSTANCE_NAME`_SPIM_1_WriteTxData(0);
            output |= `$INSTANCE_NAME`_SPIM_1_ReadRxData();
       // }
    //}
    `$INSTANCE_NAME`_RT_CS_HIGH();
    
    return output;
}

/**************************************************************************//**
*  @brief Reads register value from touchscreen
*
*  @param reg: register
*
*  @return: 8 bit register value
*
*******************************************************************************/
uint8_t `$INSTANCE_NAME`_ReadRegister8(uint8_t reg)
{
    //CyDelay(1);
    uint8_t output;
    
    //`$INSTANCE_NAME`_SPIM_1_ClearRxBuffer();
    //`$INSTANCE_NAME`_SPIM_1_ClearTxBuffer();
    `$INSTANCE_NAME`_RT_CS_LOW();
    CyDelay(1);
    `$INSTANCE_NAME`_SPIM_1_WriteTxData(0x80 | reg);
    CyDelay(1);
    `$INSTANCE_NAME`_SPIM_1_WriteTxData(0x00);
    CyDelay(1);
    while(!`$INSTANCE_NAME`_SPIM_1_GetRxBufferSize());
    //{  
        CyDelay(1);
        `$INSTANCE_NAME`_SPIM_1_WriteTxData(0);
        CyDelayUs(100);
        while(!`$INSTANCE_NAME`_SPIM_1_GetRxBufferSize());
        output = `$INSTANCE_NAME`_SPIM_1_ReadRxData();
        //output = `$INSTANCE_NAME`_SPIM_1_ReadRxData();
   // }
    `$INSTANCE_NAME`_RT_CS_HIGH();
    
    return output;
}

/**************************************************************************//**
*  @brief Reads coordinates from touchscreen
*
*  @param x: x coordinate
*  @param y: y coordinate
*  @param z: pressure value
*
*******************************************************************************/
void `$INSTANCE_NAME`_ReadData(uint16_t *x, uint16_t *y, uint8_t *z)
{
    uint8_t data[4];
    uint8_t i;
    
    for (i=0; i<4; i++)
    {
        data[i] = `$INSTANCE_NAME`_ReadRegister8(0xD7);
    }
    *x = data[0];
    *x <<= 4;
    *x |= (data[1] >> 4);
    *y = data[1] & 0x0F; 
    *y <<= 8;
    *y |= data[2]; 
    *z = data[3];
    
    if(`$INSTANCE_NAME`_BufferEmpty())
    {
        `$INSTANCE_NAME`_WriteRegister8(STMPE_INT_STA, 0xFF); // reset all ints
    }
    
}

/**************************************************************************//**
*  @brief Gets touchscreen version
*
*  @return: version number
*
*******************************************************************************/
uint16_t `$INSTANCE_NAME`_GetVersion()
{
    uint16_t v;
    
    v = `$INSTANCE_NAME`_ReadRegister8(0);
    v <<= 8;
    v |= `$INSTANCE_NAME`_ReadRegister8(1);
   // v = `$INSTANCE_NAME`_ReadRegister16(1);
    return v;
}


/**************************************************************************//**
*  @brief Clears the buffer and then re-enables it
*
*******************************************************************************/
void `$INSTANCE_NAME`_ResetBuffer(void)
{  
    `$INSTANCE_NAME`_WriteRegister8(STMPE_FIFO_STA,`$INSTANCE_NAME`_ReadRegister8(STMPE_FIFO_STA) | 0x01);
    `$INSTANCE_NAME`_WriteRegister8(STMPE_FIFO_STA,`$INSTANCE_NAME`_ReadRegister8(STMPE_FIFO_STA) & 0xFE);
}
/**************************************************************************//**
*  @brief Checks if the screen currently being touched
*
*  @return: true for touched, false otherwise
*
*******************************************************************************/
bool `$INSTANCE_NAME`_Touched(void)
{
    uint8_t touch = `$INSTANCE_NAME`_ReadRegister8(0x40);//STMPE_TSC_CTRL);
    uint8_t touch_final = touch & 0x80;
    return touch_final;//(`$INSTANCE_NAME`_ReadRegister8(STMPE_TSC_CTRL) & 0x80);
}

/**************************************************************************//**
*  @brief Checks if the touchscreen buffer is empty
*
*  @return: false for empty, true otherwise
*
*******************************************************************************/
bool `$INSTANCE_NAME`_BufferEmpty(void)
{
    return (`$INSTANCE_NAME`_ReadRegister8(STMPE_FIFO_STA) & STMPE_FIFO_STA_EMPTY);
}

/**************************************************************************//**
*  @brief Checks the size of the touchscreen buffer
*
*  @return: size of buffer
*
*******************************************************************************/
uint8_t `$INSTANCE_NAME`_BufferSize(void)
{
    return `$INSTANCE_NAME`_ReadRegister8(STMPE_FIFO_SIZE);
}
//TS_Point `$INSTANCE_NAME`_GetPoint(void);

//swap two variables
void `$INSTANCE_NAME`_swap(int16_t *a, int16_t *b)
{
   int16_t *c = a;
   a = b;
   b = c;
}


/* [] END OF FILE */
