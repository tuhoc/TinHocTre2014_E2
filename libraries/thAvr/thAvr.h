/*
  TUHOC - thAvr library

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

#ifndef THAVR_H
#define THAVR_H

#include <Arduino.h>
#include <avr/eeprom.h>


void avrTimer1ConfigNormal(word TopValue);

#define AVR_TIMER1_TOP(microSecPerTick) (((F_CPU) / 8000000UL) * microSecPerTick)  // 8000000UL <- TCCR1B = _BV(WGM12) | _BV(CS11)

#if defined(__AVR_ATmega8P__) || defined(__AVR_ATmega8__)
  #define  TIMSK1  TIMSK
#endif

#define avrTimer1OC1AInteruptEnable()   { bitSet(TIMSK1, OCIE1A); } //TIMSK1 |=  _BV(OCIE1A); }
#define avrTimer1OC1AInteruptDisable()  { TIMSK1 &= ~_BV(OCIE1A); }
#define avrTimer1OC1BInteruptEnable()   { TIMSK1 |=  _BV(OCIE1B); }
#define avrTimer1OC1BInteruptDisable()  { TIMSK1 &= ~_BV(OCIE1B); }


void avrADCClockDivConfig(byte clkDiv);
#define ADC_CLK_DIV_2     1
#define ADC_CLK_DIV_4     2
#define ADC_CLK_DIV_8     3
#define ADC_CLK_DIV_16    4
#define ADC_CLK_DIV_32    5
#define ADC_CLK_DIV_64    6
#define ADC_CLK_DIV_128   7


// Disable the pull-ups in ALL I/O pins
#if defined(__AVR_ATmega8P__) || defined(__AVR_ATmega8__)
  #define avrPullUpDisable()  { SFIOR |= (_BV(PUD)); }
#else
  #define avrPullUpDisable()  { MCUCR |= (_BV(PUD)); }
#endif


#define  avrEepromRead(addr)  eeprom_read_byte((uint8_t*)(addr)) 
word avrEepromReadWord(word addr);

word avrGetBandgap();
void avrConfigFreq();


#endif
