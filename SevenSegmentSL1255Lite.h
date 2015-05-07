/*
SevenSegmentSL1255Lite.h - Library for the:
						SL-1255-30 Red Seven Segment display (Common Anode)
						SL-1256-30 Red Seven Segment display (Common Cathode)
						SL-2255-30 Green Seven Segment display (Common Anode)
						SL-2256-30 Green Seven Segment display (Common Cathode)
Created by Mark G. Jenkins March 13 2015
Released into the public domain.
-------------------------------------------------------------------------------
Copyright (c) 2015, Greenonline, coded by Mark Graham Jenkins.

SevenSegmentSL1255Lite Library is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

SevenSegmentSL1255Lite Library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
This file needs the following Libraries:

None
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Special Thanks:
Bangkok Food stalls and Thai Beer
Ban Mo district for the inspiration.

+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Version:
0.1 Rudimentary Direct Draw
0.2 Effects added
0.3 drawBitmap and use of Seven Segment (bit)maps added
0.4 Arduino standardisation (Write and Begin)
0.5 Public Beta
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
BugList of the current version:

Please report any!

*/

/*
   inverted functions (all on, active led is off) - could just invert onValue/offValue?
   alt - alternate segments
*/

#ifndef SevenSegmentSL1255Lite_h
#define SevenSegmentSL1255Lite_h

#include "Arduino.h"
#include "SevenSegmentMaps.h"

// Pin out: Display1 Segment Pin#
#define default_a1 2
#define default_b1 3
#define default_c1 4
#define default_d1 5
#define default_e1 6
#define default_f1 7
#define default_g1 8

// Pin out: Display2 Segment Pin#
#define default_a2 9
#define default_b2 10
#define default_c2 11
#define default_d2 12
#define default_e2 13
#define default_f2 14
#define default_g2 15

// 7 segment type, common anode, or cathode
// The value of the model basically denotes the ON value for an LED,
// so as SL-1255 has a ON for LOW (0), common anode , then SL-1255 is 0
// so as SL-1256 has a ON for HIGH (1), common cathode , then SL-1256 is 1
#define SL_1255 0
#define SL_1256 1
#define SL_2255 0
#define SL_2256 1

// On is LOW for SL-1255
// On is HIGH for SL-1256
#define default_onValue LOW
#define default_offValue HIGH

#define default_delay 500

class SevenSegmentSL1255Lite
{
    public:

      // Constructor Methods

	  // Default Constructor
      SevenSegmentSL1255Lite();
      SevenSegmentSL1255Lite(uint8_t a1, uint8_t b1, uint8_t c1, uint8_t d1, uint8_t e1, uint8_t f1, uint8_t g1);
      SevenSegmentSL1255Lite(uint8_t a1, uint8_t b1, uint8_t c1, uint8_t d1, uint8_t e1, uint8_t f1, uint8_t g1, uint8_t a2, uint8_t b2, uint8_t c2, uint8_t d2, uint8_t e2, uint8_t f2, uint8_t g2);
      SevenSegmentSL1255Lite(uint8_t a1, uint8_t b1, uint8_t c1, uint8_t d1, uint8_t e1, uint8_t f1, uint8_t g1, uint8_t a2, uint8_t b2, uint8_t c2, uint8_t d2, uint8_t e2, uint8_t f2, uint8_t g2, uint8_t ssType);
      SevenSegmentSL1255Lite(uint8_t a1, uint8_t b1, uint8_t c1, uint8_t d1, uint8_t e1, uint8_t f1, uint8_t g1, uint8_t a2, uint8_t b2, uint8_t c2, uint8_t d2, uint8_t e2, uint8_t f2, uint8_t g2, uint8_t onValue, uint8_t offValue);

      void begin(void);


      // Bitmap Methods

      // uint8_t segmentMapCode is the bitwise byte of the segments to light (g1f1e1d1c1b1a1)
      void draw_bitmap1(uint8_t segmentMapCode);
      void draw_bitmapInvert1(uint8_t segmentMapCode);
      void draw1(uint8_t segmentMapCode); //just calls draw_bitmap1()
      void drawInvert1(uint8_t segmentMapCode); //just calls draw_bitmapInvert1()

      void draw_bitmap0(uint8_t segmentMapCode);
      void draw_bitmapInvert0(uint8_t segmentMapCode);
      void draw0(uint8_t segmentMapCode); //just calls draw_bitmap0()
      void drawInvert0(uint8_t segmentMapCode); //just calls draw_bitmapInvert0()

      void draw_bitmap2(uint8_t segmentMapCode);
      void draw_bitmapInvert2(uint8_t segmentMapCode);
      void draw2(uint8_t segmentMapCode); //just calls draw_bitmap2()
      void drawInvert2(uint8_t segmentMapCode); //just calls draw_bitmapInvert2()

      // Put Methods

//      void putc(char character);
//      void putchar(char character);

      // Write Methods

      // char character is the ascii code of the character to draw
      void digit1CharWrite(char character);
      // uint8_t value is the octal numerical value to draw (0-7)
      void digit1OctWrite(uint8_t value);
      // uint8_t value is the decimal numerical value to draw (0-9)
      void digit1DecWrite(uint8_t value);
      // uint8_t value is the hexadecimal numerical value to draw (0-F)
      void digit1HexWrite(uint8_t value);
      void digit1Write(uint8_t value);
      void write1(uint8_t value); //just calls digit1Write(uint8_t value)
      void digit1Write(char character);
      void write1(char character); //just calls digit1Write(char character)

      // char character is the ascii code of the character to draw
      void digit0CharWrite(char character);
      // uint8_t value is the octal numerical value to draw (0-7)
      void digit0OctWrite(uint8_t value);
      // uint8_t value is the decimal numerical value to draw (0-9)
      void digit0DecWrite(uint8_t value);
      // uint8_t value is the hexadecimal numerical value to draw (0-F)
      void digit0HexWrite(uint8_t value);
      void digit0Write(uint8_t value);
      void write0(uint8_t value); //just calls digit0Write(uint8_t value)
      void digit0Write(char character);
      void write0(char character); //just calls digit0Write(char character)

      // char character is the ascii code of the character to draw
      void digit2CharWrite(char character);
      // uint8_t value is the octal numerical value to draw (0-7)
      void digit2OctWrite(uint8_t value);
      // uint8_t value is the decimal numerical value to draw (0-9)
      void digit2DecWrite(uint8_t value);
      // uint8_t value is the numerical value to draw (0-F)
      void digit2HexWrite(uint8_t value);
      void digit2Write(uint8_t value);
      void write2(uint8_t value); //just calls digit2Write(uint8_t value)
      void digit2Write(char character);
      void write2(char character); //just calls digit2Write(char character)
      void write(uint8_t value); // have overload led?, prints two digits, calls write1 and write0, which each do only one digit (LSD, MSD?) <99
      void write(char characters[]);// two char array, string 2 characters

      void write(uint8_t value, uint8_t digit); // write to specific digit, calls digit1Write(uint8_t value) or digit0Write(uint8_t value) as appropriate
      void write(char character, uint8_t digit);// write to specific digit, calls digit1Write(char character) or digit0Write(char character) as appropriate

	  //Scroll Methods

	  // Default scroll() is to scroll left
	  // null terminated array
	  void scroll(char characters[]);
	  // null terminated array, custom delay
	  void scroll(char characters[], int delay);
      // null terminated array, custom delay, specified direction
      void scroll(char characters[], int delay, uint8_t directionLeft);

      void scrollLeft(char characters[]);				// null terminated array
      void scrollLeft(char characters[], int delay);	// null terminated array, custom delay

      void scrollRight(char characters[]);				// null terminated array
      void scrollRight(char characters[], int delay);	// null terminated array, custom delay


      // Effects Methods

      // *** Most Significant Digit ***
	  // Effects (1st digit)
      void blankx(void);
      void fillx(void);
      void flashx(int totaldelay);
      void blank_1(void);
      void fill_1(void);
      void flash_1(int totaldelay);


      // Effects Methods

      // *** Least Significant Digit ***
	  // Effects (2nd digit)
      void blank_0(void);
      void fill_0(void);
      void flash_0(int totaldelay);

      // Effects Methods

      // *** Least Significant Digit ***
	  // Using SL-1255 Notion of LSD (Digit 0) is Digit 2
	  // Effects (2nd digit)
      void xblank(void);
      void xfill(void);
      void xflash(int totaldelay);
      void blank_2(void);
      void fill_2(void);
      void flash_2(int totaldelay);

      // Effects Methods

      // *** Most and Least Significant Digit ***
	  // Using SL-1255 Notion of MSD is Digit 1 and LSD (Digit 0) is Digit 2
	  // Effects (1st and 2nd digits)
      // Simultaneous Effects on digits 1 and 2 (1 + 2 = 3)
      void xblankx(void);
      void xfillx(void);
      void xflashx(int totaldelay);
      void blank_3(void);
      void fill_3(void);
      void flash_3(int totaldelay);



    private:

      //Initialiser Methods
      //Called by constructors

      void init(void);
      void init(uint8_t a1, uint8_t b1, uint8_t c1, uint8_t d1, uint8_t e1, uint8_t f1, uint8_t g1);
      void init(uint8_t a1, uint8_t b1, uint8_t c1, uint8_t d1, uint8_t e1, uint8_t f1, uint8_t g1, uint8_t a2, uint8_t b2, uint8_t c2, uint8_t d2, uint8_t e2, uint8_t f2, uint8_t g2);
      void init(uint8_t a1, uint8_t b1, uint8_t c1, uint8_t d1, uint8_t e1, uint8_t f1, uint8_t g1, uint8_t a2, uint8_t b2, uint8_t c2, uint8_t d2, uint8_t e2, uint8_t f2, uint8_t g2, uint8_t ssType);
      void init(uint8_t a1, uint8_t b1, uint8_t c1, uint8_t d1, uint8_t e1, uint8_t f1, uint8_t g1, uint8_t a2, uint8_t b2, uint8_t c2, uint8_t d2, uint8_t e2, uint8_t f2, uint8_t g2, uint8_t onValue, uint8_t offValue);

	  // The segments
	  // Digit 1
      uint8_t _a1;
      uint8_t _b1;
      uint8_t _c1;
      uint8_t _d1;
      uint8_t _e1;
      uint8_t _f1;
      uint8_t _g1;

	  // Digit 2
      uint8_t _a2;
      uint8_t _b2;
      uint8_t _c2;
      uint8_t _d2;
      uint8_t _e2;
      uint8_t _f2;
      uint8_t _g2;

      // The logical values for on and off
      uint8_t _onValue;
      uint8_t _offValue;

      uint8_t _ssType; // seven segment type, 0 (SL-1255) or 1 (SL-1256)

      // Tables containing the character segment maps (bitmaps)
      // The ASCII character set
      static const uint8_t _asciiTable[128];
      // The Hexadecimal character set (0-F)
      static const uint8_t _hexTable[16];    //for hexWrite()
      // The Decimal character set (0-9)
      static const uint8_t _decTable[10];    //for decWrite()
      // The Octal character set (0-7)
      static const uint8_t _octTable[8];    //for octWrite()

};


#endif