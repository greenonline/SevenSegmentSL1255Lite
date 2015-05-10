/*
SevenSegmentSL1255Lite.cpp - Library for the:
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

#include "Arduino.h"
#include "SevenSegmentSL1255Lite.h"

const uint8_t SevenSegmentSL1255Lite::_asciiTable[128] = {   ascii_NUL
                                               ,   ascii_SOH
                                               ,   ascii_STX
                                               ,   ascii_ETX
                                               ,   ascii_EOT
                                               ,   ascii_ENQ
                                               ,   ascii_ACK
                                               ,   ascii_BEL
                                               ,   ascii_BS
                                               ,   ascii_TAB
                                               ,   ascii_LF
                                               ,   ascii_VT
                                               ,   ascii_FF
                                               ,   ascii_CR
                                               ,   ascii_SO
                                               ,   ascii_SI
                                               ,   ascii_DLE
                                               ,   ascii_DC1
                                               ,   ascii_DC2
                                               ,   ascii_DC3
                                               ,   ascii_DC4
                                               ,   ascii_NAK
                                               ,   ascii_SYN
                                               ,   ascii_ETB
                                               ,   ascii_CAN
                                               ,   ascii_EM
                                               ,   ascii_SUB
                                               ,   ascii_ESC
                                               ,   ascii_FS
                                               ,   ascii_GS
                                               ,   ascii_RS
                                               ,   ascii_US
                                               ,   ascii_space
                                               ,   ascii_exclamation
                                               ,   ascii_doublequote
                                               ,   ascii_hash
                                               ,   ascii_dollar
                                               ,   ascii_percent
                                               ,   ascii_ampersand
                                               ,   ascii_singlequote
                                               ,   ascii_leftparentese
                                               ,   ascii_rightparentese
                                               ,   ascii_asterisk
                                               ,   ascii_plus
                                               ,   ascii_comma
                                               ,   ascii_minus
                                               ,   ascii_period
                                               ,   ascii_forwardslash
                                               ,   ascii_0
                                               ,   ascii_1
                                               ,   ascii_2
                                               ,   ascii_3
                                               ,   ascii_4
                                               ,   ascii_5
                                               ,   ascii_6
                                               ,   ascii_7
                                               ,   ascii_8
                                               ,   ascii_9
                                               ,   ascii_colon
                                               ,   ascii_semicolon
                                               ,   ascii_lessthan
                                               ,   ascii_equals
                                               ,   ascii_greaterthan
                                               ,   ascii_interrogation
                                               ,   ascii_at
                                               ,   ascii_A
                                               ,   ascii_B
                                               ,   ascii_C
                                               ,   ascii_D
                                               ,   ascii_E
                                               ,   ascii_F
                                               ,   ascii_G
                                               ,   ascii_H
                                               ,   ascii_I
                                               ,   ascii_J
                                               ,   ascii_K
                                               ,   ascii_L
                                               ,   ascii_M
                                               ,   ascii_N
                                               ,   ascii_O
                                               ,   ascii_P
                                               ,   ascii_Q
                                               ,   ascii_R
                                               ,   ascii_S
                                               ,   ascii_T
                                               ,   ascii_U
                                               ,   ascii_V
                                               ,   ascii_W
                                               ,   ascii_X
                                               ,   ascii_Y
                                               ,   ascii_Z
                                               ,   ascii_leftbracket
                                               ,   ascii_backslash
                                               ,   ascii_rightbracket
                                               ,   ascii_circumflex
                                               ,   ascii_underscore
                                               ,   ascii_accent
                                               ,   ascii_a
                                               ,   ascii_b
                                               ,   ascii_c
                                               ,   ascii_d
                                               ,   ascii_e
                                               ,   ascii_f
                                               ,   ascii_g
                                               ,   ascii_h
                                               ,   ascii_i
                                               ,   ascii_j
                                               ,   ascii_k
                                               ,   ascii_l
                                               ,   ascii_m
                                               ,   ascii_n
                                               ,   ascii_o
                                               ,   ascii_p
                                               ,   ascii_q
                                               ,   ascii_r
                                               ,   ascii_s
                                               ,   ascii_t
                                               ,   ascii_u
                                               ,   ascii_v
                                               ,   ascii_w
                                               ,   ascii_x
                                               ,   ascii_y
                                               ,   ascii_z
                                               ,   ascii_leftbrace
                                               ,   ascii_pipe
                                               ,   ascii_rightbrace
                                               ,   ascii_cedilla
                                               ,   ascii_DEL};



const uint8_t SevenSegmentSL1255Lite::_hexTable[16] = {alphanum_0, alphanum_1, alphanum_2, alphanum_3, alphanum_4, alphanum_5, alphanum_6, alphanum_7, alphanum_8, alphanum_9, alphanum_A, alphanum_b, alphanum_C, alphanum_d, alphanum_E, alphanum_F}; //for hexWrite()
const uint8_t SevenSegmentSL1255Lite::_decTable[10] = {alphanum_0, alphanum_1, alphanum_2, alphanum_3, alphanum_4, alphanum_5, alphanum_6, alphanum_7, alphanum_8, alphanum_9}; //for decWrite()
const uint8_t SevenSegmentSL1255Lite::_octTable[8] = {alphanum_0, alphanum_1, alphanum_2, alphanum_3, alphanum_4, alphanum_5, alphanum_6, alphanum_7}; //for octWrite()

// Constructor Methods

// Default Constructor
SevenSegmentSL1255Lite::SevenSegmentSL1255Lite(void){
  init();
}

// Constructor for digit 1
SevenSegmentSL1255Lite::SevenSegmentSL1255Lite(uint8_t a1, uint8_t b1, uint8_t c1, uint8_t d1, uint8_t e1, uint8_t f1, uint8_t g1){
  init(a1, b1, c1, d1, e1, f1, g1);
}

// Constructor for digits 1 and 2
SevenSegmentSL1255Lite::SevenSegmentSL1255Lite(uint8_t a1, uint8_t b1, uint8_t c1, uint8_t d1, uint8_t e1, uint8_t f1, uint8_t g1, uint8_t a2, uint8_t b2, uint8_t c2, uint8_t d2, uint8_t e2, uint8_t f2, uint8_t g2){
  init(a1, b1, c1, d1, e1, f1, g1, a2, b2, c2, d2, e2, f2, g2);
}

// Constructor for digits 1 and 2 and Seven Segment Type
SevenSegmentSL1255Lite::SevenSegmentSL1255Lite(uint8_t a1, uint8_t b1, uint8_t c1, uint8_t d1, uint8_t e1, uint8_t f1, uint8_t g1, uint8_t a2, uint8_t b2, uint8_t c2, uint8_t d2, uint8_t e2, uint8_t f2, uint8_t g2, uint8_t ssType){
  init(a1, b1, c1, d1, e1, f1, g1, a2, b2, c2, d2, e2, f2, g2, ssType);
}

// Constructor for digits 1 and 2 and logical On Value and Off Value
SevenSegmentSL1255Lite::SevenSegmentSL1255Lite(uint8_t a1, uint8_t b1, uint8_t c1, uint8_t d1, uint8_t e1, uint8_t f1, uint8_t g1, uint8_t a2, uint8_t b2, uint8_t c2, uint8_t d2, uint8_t e2, uint8_t f2, uint8_t g2, uint8_t onValue, uint8_t offValue){
  init(a1, b1, c1, d1, e1, f1, g1, a2, b2, c2, d2, e2, f2, g2, onValue, offValue);
}


// Initialiser Methods
// Called by constructors

// Initialiser called by default constructor
void SevenSegmentSL1255Lite::init(void) {
  init(default_a1, default_b1, default_c1, default_d1, default_e1, default_f1, default_g1);
}

// Initialiser called by constructor for digit 1
void SevenSegmentSL1255Lite::init(uint8_t a1, uint8_t b1, uint8_t c1, uint8_t d1, uint8_t e1, uint8_t f1, uint8_t g1) {
  init(a1, b1, c1, d1, e1, f1, g1, default_a2, default_b2, default_c2, default_d2, default_e2, default_f2, default_g2);
}

// Initialiser called by constructor for digits 1 and 2
void SevenSegmentSL1255Lite::init(uint8_t a1, uint8_t b1, uint8_t c1, uint8_t d1, uint8_t e1, uint8_t f1, uint8_t g1, uint8_t a2, uint8_t b2, uint8_t c2, uint8_t d2, uint8_t e2, uint8_t f2, uint8_t g2) {
  init(a1, b1, c1, d1, e1, f1, g1, a2, b2, c2, d2, e2, f2, g2, default_onValue, default_offValue);
}

// Initialiser called by constructor for digits 1 and 2 and Seven Segment Type
void SevenSegmentSL1255Lite::init(uint8_t a1, uint8_t b1, uint8_t c1, uint8_t d1, uint8_t e1, uint8_t f1, uint8_t g1, uint8_t a2, uint8_t b2, uint8_t c2, uint8_t d2, uint8_t e2, uint8_t f2, uint8_t g2, uint8_t ssType) {

  _ssType=ssType;
  //could call init (a1...g2, on, off) in this if construct

  if (_ssType == SL_1255){
    init(a1, b1, c1, d1, e1, f1, g1, a2, b2, c2, d2, e2, f2, g2, default_onValue, default_offValue);
  } else if (_ssType == SL_1256){
    init(a1, b1, c1, d1, e1, f1, g1, a2, b2, c2, d2, e2, f2, g2, !default_onValue, !default_offValue);
  } else {
	// If error;
	// Use defaults
    init(a1, b1, c1, d1, e1, f1, g1, a2, b2, c2, d2, e2, f2, g2, default_onValue, default_offValue);
  }

  //could call init (a1...g2, on, off) in this if construct
}

// Initialiser called by constructor for digits 1 and 2 and logical On Value and Off Value
void SevenSegmentSL1255Lite::init(uint8_t a1, uint8_t b1, uint8_t c1, uint8_t d1, uint8_t e1, uint8_t f1, uint8_t g1, uint8_t a2, uint8_t b2, uint8_t c2, uint8_t d2, uint8_t e2, uint8_t f2, uint8_t g2, uint8_t onValue, uint8_t offValue) {
  _a1=a1;
  _b1=b1;
  _c1=c1;
  _d1=d1;
  _e1=e1;
  _f1=f1;
  _g1=g1;

  _a2=a2;
  _b2=b2;
  _c2=c2;
  _d2=d2;
  _e2=e2;
  _f2=f2;
  _g2=g2;

  _onValue=onValue;
  _offValue=offValue;

  //don't forget to set _ssType!!!
  // use _onValue to set _ssType
  _ssType=_onValue;
}

// Default begin() method, to set the pins defined by the constructor to be outputs
void SevenSegmentSL1255Lite::begin(void) {
  pinMode(_a1, OUTPUT);
  pinMode(_b1, OUTPUT);
  pinMode(_c1, OUTPUT);
  pinMode(_d1, OUTPUT);
  pinMode(_e1, OUTPUT);
  pinMode(_f1, OUTPUT);
  pinMode(_g1, OUTPUT);

  pinMode(_a2, OUTPUT);
  pinMode(_b2, OUTPUT);
  pinMode(_c2, OUTPUT);
  pinMode(_d2, OUTPUT);
  pinMode(_e2, OUTPUT);
  pinMode(_f2, OUTPUT);
  pinMode(_g2, OUTPUT);
}


// Bitmap Methods

/*
void SevenSegmentSL1255Lite::draw_bitmapx(uint8_t character) {
	if ((character >> 0) & 1)
	  digitalWrite(_a1,_onValue);
	else
	  digitalWrite(_a1,_offValue);
	if ((character >> 1) & 1)
	  digitalWrite(_b1,_onValue);
	else
	  digitalWrite(_b1,_offValue);
	if ((character >> 2) & 1)
	  digitalWrite(_c1,_onValue);
	else
	  digitalWrite(_c1,_offValue);
	if ((character >> 3) & 1)
	  digitalWrite(_d1,_onValue);
	else
	  digitalWrite(_d1,_offValue);
	if ((character >> 4) & 1)
	  digitalWrite(_e1,_onValue);
	else
	  digitalWrite(_e1,_offValue);
	if ((character >> 5) & 1)
	  digitalWrite(_f1,_onValue);
	else
	  digitalWrite(_f1,_offValue);
	if ((character >> 6) & 1)
	  digitalWrite(_g1,_onValue);
	else
	  digitalWrite(_g1,_offValue);
}
*/

void SevenSegmentSL1255Lite::draw_bitmap1(uint8_t segmentMapCode) {
	digitalWrite(_a1, (((segmentMapCode >> 0) & 1)? _onValue : _offValue));
	digitalWrite(_b1, (((segmentMapCode >> 1) & 1)? _onValue : _offValue));
	digitalWrite(_c1, (((segmentMapCode >> 2) & 1)? _onValue : _offValue));
	digitalWrite(_d1, (((segmentMapCode >> 3) & 1)? _onValue : _offValue));
	digitalWrite(_e1, (((segmentMapCode >> 4) & 1)? _onValue : _offValue));
	digitalWrite(_f1, (((segmentMapCode >> 5) & 1)? _onValue : _offValue));
	digitalWrite(_g1, (((segmentMapCode >> 6) & 1)? _onValue : _offValue));
}

void SevenSegmentSL1255Lite::draw_bitmapInvert1(uint8_t segmentMapCode) {
	digitalWrite(_a1, (!((segmentMapCode >> 0) & 1)? _onValue : _offValue));
	digitalWrite(_b1, (!((segmentMapCode >> 1) & 1)? _onValue : _offValue));
	digitalWrite(_c1, (!((segmentMapCode >> 2) & 1)? _onValue : _offValue));
	digitalWrite(_d1, (!((segmentMapCode >> 3) & 1)? _onValue : _offValue));
	digitalWrite(_e1, (!((segmentMapCode >> 4) & 1)? _onValue : _offValue));
	digitalWrite(_f1, (!((segmentMapCode >> 5) & 1)? _onValue : _offValue));
	digitalWrite(_g1, (!((segmentMapCode >> 6) & 1)? _onValue : _offValue));
}

void SevenSegmentSL1255Lite::draw1(uint8_t segmentMapCode) { //calls draw_bitmap(void) {
	draw_bitmap1(segmentMapCode);
}

void SevenSegmentSL1255Lite::drawInvert1(uint8_t segmentMapCode) { //calls draw_bitmap()
	draw_bitmapInvert1(segmentMapCode);
}

void SevenSegmentSL1255Lite::draw_bitmap0(uint8_t segmentMapCode) {
	draw_bitmap2(segmentMapCode);
}

void SevenSegmentSL1255Lite::draw_bitmapInvert0(uint8_t segmentMapCode) {
	draw_bitmapInvert2(segmentMapCode);
}

void SevenSegmentSL1255Lite::draw0(uint8_t segmentMapCode) { //calls draw_bitmap(void) {
	draw_bitmap2(segmentMapCode);
}

void SevenSegmentSL1255Lite::drawInvert0(uint8_t segmentMapCode) { //calls draw_bitmap()
	draw_bitmapInvert2(segmentMapCode);
}

void SevenSegmentSL1255Lite::draw_bitmap2(uint8_t segmentMapCode) {
	digitalWrite(_a2, (((segmentMapCode >> 0) & 1)? _onValue : _offValue));
	digitalWrite(_b2, (((segmentMapCode >> 1) & 1)? _onValue : _offValue));
	digitalWrite(_c2, (((segmentMapCode >> 2) & 1)? _onValue : _offValue));
	digitalWrite(_d2, (((segmentMapCode >> 3) & 1)? _onValue : _offValue));
	digitalWrite(_e2, (((segmentMapCode >> 4) & 1)? _onValue : _offValue));
	digitalWrite(_f2, (((segmentMapCode >> 5) & 1)? _onValue : _offValue));
	digitalWrite(_g2, (((segmentMapCode >> 6) & 1)? _onValue : _offValue));
}

void SevenSegmentSL1255Lite::draw_bitmapInvert2(uint8_t segmentMapCode) {
	digitalWrite(_a2, (!((segmentMapCode >> 0) & 1)? _onValue : _offValue));
	digitalWrite(_b2, (!((segmentMapCode >> 1) & 1)? _onValue : _offValue));
	digitalWrite(_c2, (!((segmentMapCode >> 2) & 1)? _onValue : _offValue));
	digitalWrite(_d2, (!((segmentMapCode >> 3) & 1)? _onValue : _offValue));
	digitalWrite(_e2, (!((segmentMapCode >> 4) & 1)? _onValue : _offValue));
	digitalWrite(_f2, (!((segmentMapCode >> 5) & 1)? _onValue : _offValue));
	digitalWrite(_g2, (!((segmentMapCode >> 6) & 1)? _onValue : _offValue));
}

void SevenSegmentSL1255Lite::draw2(uint8_t segmentMapCode) { //calls draw_bitmap(void) {
	draw_bitmap2(segmentMapCode);
}

void SevenSegmentSL1255Lite::drawInvert2(uint8_t segmentMapCode) { //calls draw_bitmap()
	draw_bitmapInvert2(segmentMapCode);
}

// Put Methods

//void SevenSegmentSL1255Lite::putc(char character) {}
//void SevenSegmentSL1255Lite::putchar(char character){}

// Write Methods

// Write to Digit 1 (Most Significant Digit) - Using standard notion
// Write ASCII character to Digit 1 (MSD)
void SevenSegmentSL1255Lite::digit1CharWrite(char character) {
	uint8_t value = character;
	if ((value >= 0) && (value <= 127)) {
		draw_bitmap1(_asciiTable[value]);
	}
}

// Write Octal character to Digit 1 (MSD)
void SevenSegmentSL1255Lite::digit1OctWrite(uint8_t value) {
	if ((value >= 0) && (value <= 7)) {
		draw_bitmap1(_octTable[value]);
	}
}

// Write Decimal character to Digit 1 (MSD)
void SevenSegmentSL1255Lite::digit1DecWrite(uint8_t value) {
	if ((value >= 0) && (value <= 9)) {
		draw_bitmap1(_decTable[value]);
	}
}

// Write Hexadecimal character to Digit 1 (MSD)
void SevenSegmentSL1255Lite::digit1HexWrite(uint8_t value) {
	if ((value >= 0) && (value <= 15)) {
		draw_bitmap1(_hexTable[value]);
	}
}

void SevenSegmentSL1255Lite::digit1Write(uint8_t value) {
	digit1DecWrite(value);
//	if ((value >= 0) && (value <= 9)) {
//		draw_bitmap2(_decTable[value]);
//	}
}

void SevenSegmentSL1255Lite::write1(uint8_t value) {
	digit1Write(value);
}

void SevenSegmentSL1255Lite::digit1Write(char character) {
	digit1CharWrite(character);
}

void SevenSegmentSL1255Lite::write1(char character) {
	digit1CharWrite(character);
}

// Write to Digit 0 (Least Significant Digit) - Using standard notion
// Write ASCII character to Digit 0 (LSD)
void SevenSegmentSL1255Lite::digit0CharWrite(char character) {
	digit2CharWrite(character);
}

// Write Octal character to Digit 0 (LSD)
void SevenSegmentSL1255Lite::digit0OctWrite(uint8_t value) {
	digit2OctWrite(value);
}

// Write Decimal character to Digit 0 (LSD)
void SevenSegmentSL1255Lite::digit0DecWrite(uint8_t value) {
	digit2DecWrite(value);
}

// Write Hexadecimal character to Digit 0 (LSD)
void SevenSegmentSL1255Lite::digit0HexWrite(uint8_t value) {
	digit2HexWrite(value);
}

void SevenSegmentSL1255Lite::digit0Write(uint8_t value) {
	digit2Write(value);
}

void SevenSegmentSL1255Lite::write0(uint8_t value) {
	digit2Write(value);
}

void SevenSegmentSL1255Lite::digit0Write(char character) {
	digit2CharWrite(character);
}

void SevenSegmentSL1255Lite::write0(char character) {
	digit2CharWrite(character);
}

// Write to Digit 2 (Least Significant Digit) - Using SL-1255 notion
// Write ASCII character to Digit 2 (LSD)
void SevenSegmentSL1255Lite::digit2CharWrite(char character) {
	uint8_t value = character;
	if ((value >= 0) && (value <= 127)) {
		draw_bitmap2(_asciiTable[value]);
	}
}

// Write Octal character to Digit 2 (LSD)
void SevenSegmentSL1255Lite::digit2OctWrite(uint8_t value) {
	if ((value >= 0) && (value <= 7)) {
		draw_bitmap2(_octTable[value]);
	}
}

// Write Decimal character to Digit 2 (LSD)
void SevenSegmentSL1255Lite::digit2DecWrite(uint8_t value) {
	if ((value >= 0) && (value <= 9)) {
		draw_bitmap2(_decTable[value]);
	}
}

// Write Hexadecimal character to Digit 2 (LSD)
void SevenSegmentSL1255Lite::digit2HexWrite(uint8_t value) {
	if ((value >= 0) && (value <= 15)) {
		draw_bitmap2(_hexTable[value]);
	}
}

void SevenSegmentSL1255Lite::digit2Write(uint8_t value) {
	digit2DecWrite(value);
//	if ((value >= 0) && (value <= 9)) {
//		draw_bitmap2(_decTable[value]);
//	}
}

void SevenSegmentSL1255Lite::write2(uint8_t value) {
	digit2Write(value);
}

void SevenSegmentSL1255Lite::digit2Write(char character) {
	digit2CharWrite(character);
}

void SevenSegmentSL1255Lite::write2(char character) {
	digit2CharWrite(character);
}

void SevenSegmentSL1255Lite::write(uint8_t value) {
	if (value <= 99){					// sanity check (value fits on two digits?)
		uint8_t MSD = value/10;			// get the Most Significant Digit
		uint8_t LSD = value-(MSD*10);	// get the Least Significant Digit
		digit1Write(MSD);				// write the MSD to digit 1
		digit2Write(LSD);				// write the LSD to digit 0,
										// or digit 2 using SL-1255 notion
    }
}

void SevenSegmentSL1255Lite::write(char characters[]) {
	char c1; // first character
	char c2; // second character
	//discard any other characters in the string

	if (characters[0] != 0 && characters[1] != 0){
		c1=characters[0]; // get the first character
		c2=characters[1]; // get the second character
		digit1Write(c1);
		digit2Write(c2);
	}

	if (characters[1] == 0){	// print only one character in digit 2 (digit 0)
		c2=characters[0]; // get the second character
		blank_1();
		digit2Write(c2);
	}
}

void SevenSegmentSL1255Lite::write(uint8_t value, uint8_t digit) {
	//if value<=9
	if (value <= 9) {
		switch (digit) {
			case 0 :
				digit0Write(value);
				break;
			case 1 :
				digit1Write(value);
				break;
			case 2 :
				digit2Write(value);
				break;
			default :
				break;
		}
    }
}

void SevenSegmentSL1255Lite::write(char character, uint8_t digit) {
	switch (digit) {
		case 0 :
			digit0Write(character);
			break;
		case 1 :
			digit1Write(character);
			break;
		case 2 :
			digit2Write(character);
			break;
		default :
			break;
	}
}

// Scroll Methods

//scroll() is a default left scroll method
void SevenSegmentSL1255Lite::scroll(char characters[]) {
	scroll(characters, default_delay);	// Call scroll() with the default delay
}

//scroll() is a default left scroll method
void SevenSegmentSL1255Lite::scroll(char characters[], int delayBetweenScroll) {
	scrollLeft(characters, delayBetweenScroll); // Call scrollLeft() with the specified delay
}

//scroll and specify delay and direction in parameter
// Scroll left  == 1
// Scroll right != 1
void SevenSegmentSL1255Lite::scroll(char characters[], int delayBetweenScroll, uint8_t directionLeft) {
	if (directionLeft == 1){
		scrollLeft(characters, delayBetweenScroll);
	} else {
		scrollRight(characters, delayBetweenScroll);
	}
}

void SevenSegmentSL1255Lite::scrollLeft(char characters[]) {
	scrollLeft(characters, default_delay);	// Call scrollLeft() with the default delay
}

//Scrolls in from the right to the left
//First LSD is first character of message and
//MSD is blank
//then LSD->MSD, next character->LSD ...
//Finally MSD is last character of message, and
//LSD is blank
//
//When calling scrollLeft(), should encouch in blankx() and
//  xblank() calls (before and after) to clear the display
//  i.e.
//    xblank();  // Not strictly needed for scrollRight() calls
//    blankx();  // Not strictly needed for scrollLeft() calls
//    scrollLeft();
//    xblank();  // Not strictly needed for scrollLeft() calls
//    blankx();  // Not strictly needed for scrollRight() calls

void SevenSegmentSL1255Lite::scrollLeft(char characters[], int delayBetweenScroll) {
	char c1; // first character
	char c2; // second character
	int index=0;

	blankx();						// Clear the display
	xblank();						// Clear the display
	delay(delayBetweenScroll);		// Delay before starting scroll

	if (characters[index] != 0){
		c2=characters[index++]; 	// get the second character
		digit2Write(c2);	 		// and write to the LSD first
		blankx();					// Also we blank MSD
		delay(delayBetweenScroll);	// Delay before moving on to writing both digits (below)
	}

	while (characters[index] != 0){
		c1=c2; 						// get the first character from the previous second character
		c2=characters[index++]; 	// get the new second character
		digit1Write(c1);			// write the first character
		digit2Write(c2);			// write the second character
		delay(delayBetweenScroll);	// Delay before shifting both digits left
	}

	c1=c2; 							// get the first character from the previous second character
	digit1Write(c1);				// write the first character
	xblank();						// Also we blank LSD
	delay(delayBetweenScroll);		// Delay before finishing scroll

	blankx();						// Clear the display
	xblank();						// Clear the display
	delay(delayBetweenScroll);		// Delay before ending scroll

}

void SevenSegmentSL1255Lite::scrollRight(char characters[]) {
	scrollRight(characters, default_delay);	// Call scrollRight() with the default delay
}

//Scrolls in from the left to the right
//First MSD is first character of message and
//LSD is blank
//then MSD->LSD, next character->MSD ...
//Finally LSD is last character of message, and
//MSD is blank
//
//When calling scrollRight(), should encouch in blankx() and
//  xblank() calls (before and after) to clear the display
//  i.e.
//    xblank();  // Not strictly needed for scrollRight() calls
//    blankx();  // Not strictly needed for scrollLeft() calls
//    scrollRight();
//    xblank();  // Not strictly needed for scrollLeft() calls
//    blankx();  // Not strictly needed for scrollRight() calls

void SevenSegmentSL1255Lite::scrollRight(char characters[], int delayBetweenScroll) {
	char c1; // first character
	char c2; // second character
	int index=0;

	//Find length of string
	int length = 0;
	while (characters[length] != 0){
		length++;
	}

	index= length-1;

	blankx();						// Clear the display
	xblank();						// Clear the display
	delay(delayBetweenScroll);		// Delay before starting scroll

	if (index>=0){
		c1=characters[index--]; 	// get the first character
		digit1Write(c1);	 		// and write to the MSD first
		xblank();					// Also we blank LSD
		delay(delayBetweenScroll);	// Delay before moving on to writing both digits (below)
	}

	while (index>=0){
		c2=c1; 						// get the second character from the previous first character
		c1=characters[index--];		// get the new first character
		digit1Write(c1);			// write the first character
		digit2Write(c2);			// write the second character
		delay(delayBetweenScroll);	// Delay before shifting both digits right
	}

	c2=c1;							// get the second character from the previous first character
	digit2Write(c2);				// write the second character
	blankx();						// Also we blank MSD
	delay(delayBetweenScroll);		// Delay before finishing scroll

	blankx();						// Clear the display
	xblank();						// Clear the display
	delay(delayBetweenScroll);		// Delay before ending scroll
}

// Effects Methods

// *** Most Significant Digit ***
// Effects (1st digit)

void SevenSegmentSL1255Lite::blank_1(void) {
  digitalWrite(_a1,_offValue);
  digitalWrite(_b1,_offValue);
  digitalWrite(_c1,_offValue);
  digitalWrite(_d1,_offValue);
  digitalWrite(_e1,_offValue);
  digitalWrite(_f1,_offValue);
  digitalWrite(_g1,_offValue);
}

void SevenSegmentSL1255Lite::blankx(void) {
  blank_1();
}

void SevenSegmentSL1255Lite::fill_1(void) {
  digitalWrite(_a1,_onValue);
  digitalWrite(_b1,_onValue);
  digitalWrite(_c1,_onValue);
  digitalWrite(_d1,_onValue);
  digitalWrite(_e1,_onValue);
  digitalWrite(_f1,_onValue);
  digitalWrite(_g1,_onValue);
}

void SevenSegmentSL1255Lite::fillx(void) {
  fill_1();
}

void SevenSegmentSL1255Lite::flash_1(int totaldelay) {
  blank_1();
  delay (totaldelay/2);
  fill_1();
  delay (totaldelay/2);
}

void SevenSegmentSL1255Lite::flashx(int totaldelay) {
  flash_1(totaldelay);
}


// End Effects First Digit


// Effects Methods

// *** Least Significant Digit ***
// Effects (2nd digit)

void SevenSegmentSL1255Lite::blank_0(void) {
  digitalWrite(_a2,_offValue);
  digitalWrite(_b2,_offValue);
  digitalWrite(_c2,_offValue);
  digitalWrite(_d2,_offValue);
  digitalWrite(_e2,_offValue);
  digitalWrite(_f2,_offValue);
  digitalWrite(_g2,_offValue);
}

void SevenSegmentSL1255Lite::fill_0(void) {
  digitalWrite(_a2,_onValue);
  digitalWrite(_b2,_onValue);
  digitalWrite(_c2,_onValue);
  digitalWrite(_d2,_onValue);
  digitalWrite(_e2,_onValue);
  digitalWrite(_f2,_onValue);
  digitalWrite(_g2,_onValue);
}

void SevenSegmentSL1255Lite::flash_0(int totaldelay) {
  blank_0();
  delay (totaldelay/2);
  fill_0();
  delay (totaldelay/2);
}


// End Effects Second Digit

// Effects Methods

// *** Least Significant Digit ***
// Using SL-1255 Notion of LSD (Digit 0) is Digit 2
// Effects (2nd digit)

void SevenSegmentSL1255Lite::blank_2(void) {
  digitalWrite(_a2,_offValue);
  digitalWrite(_b2,_offValue);
  digitalWrite(_c2,_offValue);
  digitalWrite(_d2,_offValue);
  digitalWrite(_e2,_offValue);
  digitalWrite(_f2,_offValue);
  digitalWrite(_g2,_offValue);
}

void SevenSegmentSL1255Lite::xblank(void) {
  blank_2();
}

void SevenSegmentSL1255Lite::fill_2(void) {
  digitalWrite(_a2,_onValue);
  digitalWrite(_b2,_onValue);
  digitalWrite(_c2,_onValue);
  digitalWrite(_d2,_onValue);
  digitalWrite(_e2,_onValue);
  digitalWrite(_f2,_onValue);
  digitalWrite(_g2,_onValue);
}

void SevenSegmentSL1255Lite::xfill(void) {
  fill_2();
}

void SevenSegmentSL1255Lite::flash_2(int totaldelay) {
  blank_2();
  delay (totaldelay/2);
  fill_2();
  delay (totaldelay/2);
}

void SevenSegmentSL1255Lite::xflash(int totaldelay) {
  flash_2(totaldelay);
}


// End Effects Second Digit


// Effects Methods

// *** Most and Least Significant Digit ***
// Using SL-1255 Notion of MSD is Digit 1 and LSD (Digit 0) is Digit 2
// Effects (1st and 2nd digits)
// Simultaneous Effects on digits 1 and 2 (1 + 2 = 3)

void SevenSegmentSL1255Lite::blank_3(void) {
  blank_1();
  blank_2();
}

void SevenSegmentSL1255Lite::xblankx(void) {
  blank_3();
}

void SevenSegmentSL1255Lite::fill_3(void) {
  fill_1();
  fill_2();
}

void SevenSegmentSL1255Lite::xfillx(void) {
  fill_3();
}

void SevenSegmentSL1255Lite::flash_3(int totaldelay) {
  blank_3();
  delay (totaldelay/2);
  fill_3();
  delay (totaldelay/2);
}

void SevenSegmentSL1255Lite::xflashx(int totaldelay) {
  flash_3(totaldelay);
}


// End Effects Both Digits
