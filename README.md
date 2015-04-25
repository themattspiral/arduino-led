# arduino-led

This is a composition of several projects showcasing basic display-driving 
techniques using Arduino. It is intended as a learning experience, and a 
precursor for logic that will be used to drive an ArduNIX Nixie tube display 
shield.

There are examples of:
1. [pwm-led] LED pulsing (fade up/down) using manual PWM
2. [multiplex-led] Multiplexing
3. (TODO) [mux-pwm-led] Combination of PWM and multiplexing
4. (TODO) [serial-led] Serial control
 
## Setup

These examples assume 4 LEDs are available, wired-up in the following manner:
There is 1 'anode' pin, shared among all 4 LEDs. There are 4 'cathode' pins, 
each one controlling the gate of an NPN transistor so that when the pin is on, 
the LED ground will be connected to the Arduino ground and current will flow.
  
                           ANODE_1 (PIN 12)
                                 |
              ----------------------------------------
              |                                      |
   R--------------------R                 R----------------------R
   |                    |                 |                      |
LED 1                 LED 2              LED 3                 LED 4
   |                    |                 |                      |
   N                    N                 N                      N
    \                    \                 \                      \
     P---R                P---R             P---R                  P---R
    /    |               /    |            /    |                 /    |
   N  CATHODE_1         N   CATHODE_2     N   CATHODE_3          N   CATHODE_4
   |   (PIN 2)          |    (PIN 3)      |    (PIN 4)           |    (PIN 5)
  GND                 GND                GND                    GND 

Note: There are resistors between ANODE_1 and the LEDs, and between each 
CATHODE the the transistor gates (all denoted by 'R' above).

This configuration is a little convoluted and more complex than it needs to be. 
We only have 4 leds, so we could hard-ground them all and drive each one 
individually with a dedicated anode pin, but that would go against the point 
of some of the code here, which is specifically meant to show multiplexing.

