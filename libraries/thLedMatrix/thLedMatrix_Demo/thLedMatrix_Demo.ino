#include <thAvr.h>
#include <thLedMatrix.h>

BITMAP smilingFaceImage[] =
{
  0x3C, 0x00,
  0x42, 0x00,
  0x95, 0x14,
  0xA1, 0x20,
  0xA1, 0x20,
  0x95, 0x14,
  0x42, 0x00,
  0x3C, 0x00
};

void setup()
{
  thLedMatrix.begin();
}

void loop()
{    
  thLedMatrix.setBitmap(smilingFaceImage);
  delay(500);
  thLedMatrix.setColumn(2, 0x95, 0x10);
  delay(500);
  thLedMatrix.setPixel(5, 2, GREEN);
  delay(500);
  thLedMatrix.clear();
  delay(500);
}
