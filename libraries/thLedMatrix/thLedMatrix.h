/*
  TUHOC - thLedMatrix library

  Copyright (c) 2014 quang.dinh@dtt.vn
  
  History
  
  version 1.0 - 140707
    Initial release - quang.dinh@dtt.vn


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

#ifndef THLEDMATRIX_H
#define THLEDMATRIX_H

#include <Arduino.h>
#include <thAvr.h>

#define  BLACK   0
#define  RED     _BV(0)
#define  GREEN   _BV(1)
#define  ORANGE  (RED | GREEN)

#define  BITMAP  static const PROGMEM prog_uchar

class thLedMatrixClass
{
  public:
  
    static void begin();                    // Start using LED Matrix
    
    static void clear();                    // Clear all pixels to BLACK
    
    static void setPixel(byte x, byte y, byte color);
    static void setColumn(byte x, byte redBitmap, byte greenBitmap);
    static void setBitmap(const prog_uchar *bitmap);
};

extern thLedMatrixClass thLedMatrix;

#endif
