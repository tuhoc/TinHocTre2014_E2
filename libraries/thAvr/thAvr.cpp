/*
  TUHOC - thAvr library

  Copyright (c) 2014 quang.dinh@dtt.vn
  
  See thAvr.h


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

#include "thAvr.h"

#define  MUL_FACTOR_EEPROM_ADDR  510
#define  ADD_FACTOR_EEPROM_ADDR  508
#define  CHECKSUM_EEPROM_ADDR    502

// ********************************************************************** //
void avrTimer1ConfigNormal(word TopValue)
{
  TCCR1A = 0; 
  TCCR1B = _BV(WGM13) | _BV(WGM12) | _BV(CS11);
  ICR1  = TopValue; 
  OCR1A = TopValue * 2/3;
  OCR1B = TopValue * 1/3; 
  TCNT1 = 0; 
}
// ********************************************************************** //

// ********************************************************************** //
void avrADCClockDivConfig(byte clkDiv)
{
  ADCSRA = (ADCSRA & (~0x07)) | (clkDiv & 0x07);
}
// ********************************************************************** //

// ********************************************************************** //
word avrGetBandgap() 
{
  //ADMUX = (0<<REFS1) | (1<<REFS0) | (0<<ADLAR) | (1<<MUX3) | (1<<MUX2) | (1<<MUX1) | (0<<MUX0);
  ADMUX = (0x01 << REFS0) | (0 << ADLAR) | (0x0E << MUX0);
   
  ADCSRA |= _BV( ADSC);
  while (ADCSRA & _BV(ADSC));
  delayMicroseconds(10);    
  // Nếu thiết lập tần số cho ADC lớn (hệ số chia CLK nhỏ) thì khi thay đổi kênh analog của bộ ADC 
  // sẽ dẫn tới các kết quả chuyển đổi ADC không chính xác ở các lần chuyển đổi đầu tiên.
  // Qua khảo sát thấy rằng nếu sau lần chuyển đổi đầu tiên (sau khi vừa chuyển kênh analog)
  // có trễ khoảng 9us trở lên thì cho kết quả chuyển đổi ADC tốt ở lần chuyển đổi tiếp theo.
  ADCSRA |= _BV(ADSC);
  while (ADCSRA & _BV(ADSC));
  return ADC;
}
// ********************************************************************** //

// ********************************************************************** //
word avrEepromReadWord(word addr)
{
  return word(avrEepromRead(addr+1), avrEepromRead(addr));
}

// ********************************************************************** //
void avrConfigFreq()
{ 
  // read two factors from eeprom
  uint16_t addFactor    = avrEepromReadWord(ADD_FACTOR_EEPROM_ADDR);
  uint16_t mulFactor    = avrEepromReadWord(MUL_FACTOR_EEPROM_ADDR);
  uint16_t checkSumWord = avrEepromReadWord(CHECKSUM_EEPROM_ADDR);
    
  // determine the factor to load into OSCCAL 
  if (0 == (addFactor ^ mulFactor ^ checkSumWord ^ 0xAAAA)) 
  {
    uint16_t bandgap = avrGetBandgap();
    
    uint32_t factor32 = mulFactor;
    factor32 = factor32 * bandgap;
    uint16_t osccal = (factor32 >> 8) + addFactor;
    OSCCAL = osccal >> 8;
  }
}
// ********************************************************************** //
