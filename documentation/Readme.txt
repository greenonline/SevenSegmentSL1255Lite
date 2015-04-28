        *** SevenSegment SL-1255-30 Library Lite ***
       ==============================================

        *** Readme ***
       ================

       Version : 0.5.0

Brief
=====

This is an Arduino Library for the Sanyo SL-1255-30 two digit seven segment display (without decimal points). 

This library is identical to the SevenSegmentSL1255 library, but has had most of the effects routines removed (leaving only blank, fil and flash methods), and has no 'direct draw' methods, as it relies solely on the bitmap (segment map) drawing methods. Also, there are no accessors, not segement or pin state getters and setters.

Introduction
============

One day, in March 2015, whilst shopping for Arduino bits and pieces in Ban Mo, an electronics street market in BKK, I came across a large sheet of polystyrene bejewelled in Sanyo SL-1255-30 two digit seven segment displays, for 5 Baht each, which was displayed in the street outside a shop. I purchased one of the seven segment displays, took it home, and eventually realised that no libraries existed for the common anode device.  So I promptly set about writing my own sketch, which then evolved into an Arduino Library that was developed over the course of a couple of weeks. This is a 'low fat' version of that library.

Synopsis
========
When the class is instantiated using the defaults then it will work with the Sanyo SL-1255 (red) and SL-2255 (green) dual seven segment displays, which are common anode devices. The private member, _onValue, is LOW for the segments of these displays.

This library will also work with SL-1256 and SL-2256 (green) common cathode devices, just specify the ssType (seven segment type) parameter in the constructor using the predefined SL-1256 or SL-2256 macros. The private member, _onValue, is HIGH for the segments of these displays. Alternatively, it is possible to specify the onValue and offValue, instead of using the ssType parameter, using the appropriate constructor. Please see the constructor examples below.

The public methods supplied include the usual Arduino, begin() and write(), methods for ints and char arrays ([1] and [2]). A simple set of the methods is all that is required in order to get the library up and running with your display (constructor, begin, write).

Library Contents
================

    SevenSegmentSL1255Lite.h
    SevenSegmentSL1255Lite.cpp
    keywords.txt
    SevenSegmentMaps.h
    examples/HelloWorld/HelloWorld.ino
    examples/SevenSegMaps/SevenSegMaps.ino
    examples/SevenSegMaps99Loop/SevenSegMaps99Loop.ino
    examples/SevenSegMapsLoop/SevenSegMapsLoop.ino
    documentation/Readme.txt
    documentation/QuickStart.txt
    documentation/7-seg display sl-1255-30 DSA-305501.pdf
    documentation/photos/breadboard01.jpg
    documentation/photos/breadboard02.jpg
    documentation/photos/breadboard03.jpg
    documentation/photos/SL-1255-30.jpg
    documentation/schematics/SL-1255_Nano_bb_fritzing-01.jpg
    documentation/schematics/SL-1255_Nano.fzz
    documentation/schematics/sevenSegmentASCIIMaps.jpg

Default Pinout
==============

Refer to SANYO SL-1255-30 datasheet, located at http://www.datasheetarchive.com/dlmain/Datasheets-16/DSA-305501.pdf

    pin 2 -> segment a1 (15)
    pin 3 -> segment b1 (13)
    pin 4 -> segment c1 (1)
    pin 5 -> segment d1 (3)
    pin 6 -> segment e1 (2)
    pin 7 -> segment f1 (14)
    pin 8 -> segment g1 (16)
    pin 9 -> segment a2 (10)
    pin 10 -> segment b2 (12)
    pin 11 -> segment c2 (8)
    pin 12 -> segment d2 (6)
    pin 13 -> segment e2 (7)
    pin 14 -> segment f2 (11)
    pin 15 -> segment g2 (9)
    Vcc    -> ANODE 1 (4)
    Vcc    -> ANODE 2 (5)

Constructor Methods
===================

There are five various overridden constructors. Please note that all constructors configure the pins for both digits. The reason is that this library is designed for the two digital SL-1255 display. If you only want to configure the pins for just one digit, then use a sign digit version of this library. Here is a list of the constructor types:

Default
-------

Sets up the two digits using the default pins Pin2 through to Pin16.

One Digit
---------

Sets up the most significant digit (MSD) with user defined pins and the least significant digit (LSD) with Pin10 though to Pin 16.

Two Digits
----------

Sets up the most significant digit (MSD) and the least significant digit (LSD) with user defined pins.

Two Digits with ssType
----------------------

Sets up the most significant digit (MSD) and the least significant digit (LSD) with user defined pins and allows the user to specify the Seven Segment type (by the parameter ssType) using a pre-defined model {SL1255, SL1256, SL2255, SL2256} which are set to either 0 or 1 (equivalent to the OnValue being HIGH or LOW respectively).

Two Digits with onValue and offValue
------------------------------------

Sets up the most significant digit (MSD) and the least significant digit (LSD) with user defined pins and allows the user to specify the LED on state (using the parameter OnValue) to LOW or HIGH, and the LED off state (using the parameter OffValue) should be set to the complement of the OnValue, i.e. if OnValue is LOW, the OffValue should be HIGH.

Draw Methods
============

These direct draw methods are derived from the first attempts at writing test code to get the SL-1255 working with the Arduino. They are left in place for completeness, and someone may find them useful. However, they have been largely superseded by the Write methods, although the drawBitmap() methods [read as drawSevenSegmentMaps()] are still useful and form the man body of the drawing routines. Most of the direct draw methods are deprecated in the Lite version of this library SevenSegLite1255. The direct draw methods use the non-standard (Arduino) naming convention of draw_Xx, where the position of the 'x' denotes which segment is being written to. So, draw_Ax() displays an 'A' character on digit1, and draw_xh() displays an 'h' character on digit 0.  This differs from the drawBitmap and Write methods that use a more conventional '0' and '1', in the method name, to denote the least significant and most significant digit of the display (and '2' to denote both digits). 

Begin Methods
=============

These methods assign the pins of the Arduino, and should be called from the setup() function in the Arduino sketch

Write Methods
=============
These methods enable the user to pass a numeric (octal, decimal or hexadecimal) value or alphanumeric (or ASCII) character to the method to display on either or both of the display's digits.

Effects Methods
===============

These methods provide various visual effects that may be employed on the seven segment display. For example, various methods exist which:
  - blank() the display (all segments are switched off), or;
  - fill() the display (all segments are switched on), or;
  - flash() the lit segments (all segments are alternately switched on and then after a specified delay switched off).

The best way to understand them is to experiment with each of them to see what they do. The blank(), fill() and flash() methods are the simplest to understand, and are probably the most useful. 

A delay parameter can also be used, which effectively specifies the speed of the effect, i.e. the delay between successive segments being illuminated.

Note: This delay is not the total delay, i.e. the total duration of the effect, but the delay between the actuating of the individual segments of the effect. So the total duration of the effect becomes equal to the delay multiplied by the number of segments used in the effect. So, the total duration of some effects may be longer than that of others. 

Example Sketches
================
Some examples have been include to familiarise the user with the various methods available. These focus on the areas outlined in the Methods sections, so there is an example demonstrating the direct draw functions, another for the effects, one illustrating the accessor methods, the getters and setters (making use of the serial port to write and display values of the private members), and finally a couple of simple Arduino write examples. It is this write example that ail probably be the most pertinent to everyday display projects.

Conclusion
==========
Please enjoy using this library. 

If you would prefer to employ a more heavy weight version of this library that has not been cut down, for memory economics, please consider using SevenSegmentSL1255. It may be a little heavyweight, as it is an "everything-but-the-kitchen-sink" type library, with many member methods overridden and duplicated with different function names, in order to accommodate new Arduino users, by adhering to Arduino naming standards and conventions, as well as some non standard functions, included for the convenience, and amusement, of advanced users.


Known Issues
============

1. Digit 2 (the right hand digit), in the library, is referred to as digit 0, in the interest of least significant and most significant digits. This may cause confusion, as it conflicts with the data sheet for the SL-1255-30. Hence the draw0() methods have been replicated with draw2() methods for completeness. However as that conflicts with the binary notion of draw2() for writing to both digits (0 and 1) simultaneously, "3" has been used to signify both digits (or the effects methods only). If you want to display a two character string then just use the write() or scroll() methods, as a draw3() method has not be provided for, see example sketch HelloWorld.ino.

2. Arduino Nano does not enough enough digital pins (two pins short), and so A0 and A1 are used as D15 and D16. D0 and D1 should not be used, as they are used for Rx and Tx respectively.

