#ifndef THLEDMATRIX_H
#define THLEDMATRIX_H

#include <Arduino.h>

#define  BLACK   0
#define  RED     _BV(0)
#define  GREEN   _BV(1)
#define  ORANGE  (RED | GREEN)

#define  BITMAP  static PROGMEM prog_uchar

class _thLedMatrix
{
  public:
  
    static void begin();                    // Start using LED Matrix
    
    static void clear();                    // Clear all pixels to BLACK
    
    static void setPixel(byte x, byte y, byte color);
    static void setColumn(byte x, byte redBitmap, byte greenBitmap);
    static void setBitmap(prog_uchar* bitmap);
};

extern _thLedMatrix thLedMatrix;

#endif
