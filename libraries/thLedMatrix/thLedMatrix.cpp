/*
  TUHOC - thLedMatrix library

  Copyright (c) 2014 quang.dinh@dtt.vn
  
  See thLedMatrix.h


  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General
  Public License along with this library; if not, write to the
  Free Software Foundation, Inc., 59 Temple Place, Suite 330,
  Boston, MA  02111-1307  USA
  
*/

#include "thLedMatrix.h"
#include <digitalWriteFast_thLedMatrix.h>
#include <avr/pgmspace.h>

#define  USEC_PER_TICK  (10000 / 8)               // 100 Hz refresh rate (10 ms) 

#define  COL_0  (~_BV(7))
#define  COL_2  (~_BV(6))
#define  COL_4  (~_BV(5))
#define  COL_6  (~_BV(4))
#define  COL_7  (~_BV(3))
#define  COL_5  (~_BV(2))
#define  COL_3  (~_BV(1))
#define  COL_1  (~_BV(0))

#define  LATCH_OE  SS                      // Use SPI_SS pin for LATCH_OE

uint8_t DisplayBuffer[2][8];

thLedMatrixClass thLedMatrix;

#define  SPI_SPCR_BASE  (_BV(SPE) | _BV(MSTR))    // NOTE: (atMega328p) Master, MSBFirst, Mode 0, Clk/4  


void thLedMatrixClass::begin()
{
  digitalWriteFast(LATCH_OE, HIGH); 
  pinModeFast(LATCH_OE, OUTPUT); 
  pinModeFast(SCK, OUTPUT);
  pinModeFast(MOSI, OUTPUT);

  //SPI.begin();
  //SPI.setClockDivider(SPI_CLOCK_DIV2);
  //SPI.setDataMode(SPI_MODE0);
  SPSR = _BV(SPI2X);              // Double speed --> Clk/2
  SPCR = SPI_SPCR_BASE;
  
  //SPI.transfer(0x00);
  //SPI.transfer(0x00);
  SPDR = 0;  

  cli();  
  avrTimer1ConfigNormal(AVR_TIMER1_TOP(USEC_PER_TICK));
  avrTimer1OC1BInteruptEnable();
  sei();
    
  SPDR = 0;  
}


void thLedMatrixClass::setColumn(byte x, byte redBitmap, byte greenBitmap)
{
  DisplayBuffer[0][x] = redBitmap;
  DisplayBuffer[1][x] = greenBitmap;
}


void thLedMatrixClass::setBitmap(const prog_uchar *bitmap)
{
  for (byte x = 0; x < 8; x++)
  {
    byte redBitmap = pgm_read_byte_near(bitmap++); 
    byte grnBitmap = pgm_read_byte_near(bitmap++); 
    setColumn(x, redBitmap, grnBitmap);
  }
}


void thLedMatrixClass::clear()
{
  for (byte x = 0; x < 8; x++)
  {
    setColumn(x, 0x00, 0x00);
  }
}


void thLedMatrixClass::setPixel(byte x, byte y, byte color)
{  
  uint8_t row = _BV(y);
  uint8_t row_inv = ~row;
  uint8_t *ptr = &DisplayBuffer[0][x];

  if (color & RED)
  {
    ptr[0] |= row; 
  }
  else
  {
    ptr[0] &= row_inv; 
  }
   
  if (color & GREEN)
  {
    ptr[8] |= row; 
  }
  else
  {
    ptr[8] &= row_inv; 
  }
}


void LedMatrixScan()
{   
  BITMAP ColumnTable[8] = {COL_7, COL_0, COL_1, COL_2, COL_3, COL_4, COL_5, COL_6};

  static uint8_t column = 0;
  
  uint8_t byte2 = pgm_read_byte_near(ColumnTable + column);

  SPSR;                                     // Reset SPIF flag
  SPDR = byte2;                             // Shift out  

  uint8_t redBitmap = DisplayBuffer[0][column];
  uint8_t grnBitmap = DisplayBuffer[1][column];   
  uint8_t byte0 = ((redBitmap & 0x55) >> 0) | ((grnBitmap & 0x55) << 1);

  //while (!(SPSR & _BV(SPIF)));            // Wait shift   

  // Latch to display
  digitalWriteFast(LATCH_OE, HIGH);
  
  //delayMicroseconds(1);
  //SPI.setBitOrder(MSBFIRST);     
  SPCR = SPI_SPCR_BASE | 0;                 // DORD = 0: MSB first
  SPSR;                                     // Reset SPIF flag

  digitalWriteFast(LATCH_OE, LOW);

  SPDR = byte0;                             // Shift out    
  uint8_t byte1 = ((redBitmap & 0xAA) >> 0) | ((grnBitmap & 0xAA) >> 1);
  column = (column + 1) & 0x07;
  while (!(SPSR & _BV(SPIF)));              // Wait shift
  
  //SPI.setBitOrder(LSBFIRST);
  SPCR = SPI_SPCR_BASE | _BV(DORD);         // DORD = 1: LSB first   
  SPDR = byte1;                             // Shift out
  //while (!(SPSR & _BV(SPIF)));            // Wait shift
}


/*byte duration;

byte thLedMatrixClass::getDuration()
{
  return duration;
} */


SIGNAL(TIMER1_COMPB_vect)
{
  //duration = -TCNT1L; 
  LedMatrixScan();
  //duration += TCNT1L;
}
