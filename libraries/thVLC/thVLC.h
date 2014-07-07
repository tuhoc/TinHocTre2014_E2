/*
  TUHOC - thVLC library

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

#ifndef	THVLC_H
#define THVLC_H

#include <Arduino.h>
#include <thAvr.h>

#define TRI_UAN_0  0
#define TRI_UAN_1  1
#define TRI_UAN_2  2
#define TRI_UAN_3  3
#define TRI_UAN_4  4

class	thVLCClass
{
public:	
  static void begin();
  static byte getID();

  static int sensorRead(byte pin);
  static boolean receiveReady(byte pin);
  static byte receiveResult(byte pin);

  static void ledWrite(byte pin, byte state);
  static void sendByte(byte pin, byte value);
  static void txSetByte(byte pin, byte value);
  static void txSend();
};

extern thVLCClass thVLC;

#endif
