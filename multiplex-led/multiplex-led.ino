/**
 * multiplex-led
 *
 * Arduino LED multiplexing example, used as a POC for my approach to Nixie tube control.
 * This example assumes 4 leds are available, grouped as 2 sets of 2. There are 2 'anode' 
 * pins, one attached to each group of 2 (alternating LEDs). There are 4 'cathode' pins, 
 * each one controlling the base of an NPN transistor such that when the pin is HIGH, the 
 * LED ground will be connected to the Arduino ground and current will flow.
 *
 *            ANODE_1 (PIN 3)                        ANODE_2 (PIN 4)
 *                  |                                      |
 *       ----------------------                 ------------------------
 *       |                    |                 |                      |
 *    LED 1                 LED 2              LED 3                 LED 4
 *       |                    |                 |                      |
 *       N                    N                 N                      N
 *        \                    \                 \                      \
 *         P----                P----             P----                  P----
 *        /    |               /    |            /    |                 /    |
 *       N  CATHODE_1         N   CATHODE_2     N   CATHODE_3          N   CATHODE_4
 *       |   (PIN 5)          |    (PIN 6)      |    (PIN 7)           |    (PIN 8)
 *      GND                 GND                GND                    GND 
 *
 * Since we have only 4 LEDs, this is decidedly overkill, because we could really just drive
 * each one individually with a single pin, rather than multiplexing. Further, we're using
 * 4 individual 'cathode' pins when really the concept of muxing aims to control more elements 
 * with fewer pins. So we should be using a BCD-to-decimal decoder chip controlled with just 2 pins 
 * to drive the 4 cathodes, but lacking such an IC, we're just using direct pins to allow us to 
 * proceed with multiplexing and get the logic correct.
 *
 * Here's how the multiplexing works. Only 1 anode will be active at a time, and we will switch back 
 * forth between them quickly to ensure everything appears lit simultaneously. 
 */

unsigned long last = 0UL;
unsigned long fadeLengthMillis = 1000UL;
int fadeUpState = 1;

unsigned long fadeBaseMicros = 20UL;
unsigned long fadeMaxMicros = 1000UL;

void setup() {
  // initialize digital pin 13 as an output
  pinMode(13, OUTPUT);
}

// loop runs forever
void loop() {
  unsigned long now = millis();
  unsigned long diff = now - last;
  
  unsigned long litDurationMicros = 0UL;
  
  /* calculate the lighted duration in microseconds. note - this needs to be improved
   * to scale the duration based on the appropriate fraction of the fade length, rather 
   * than assuming equivalent millis to micros over a 1 sec period.
   */
  if (fadeUpState == 1) {
    // fade up
    litDurationMicros = fadeBaseMicros + diff;
  } else {
    // fade down
    litDurationMicros = fadeMaxMicros - diff;
    
    // avoid 'negative' overflow in unsigned long, or values less then base/min
    if (fadeMaxMicros < diff || litDurationMicros < fadeBaseMicros) {
      litDurationMicros = fadeBaseMicros;
    }
  }
  
  digitalWrite(13, HIGH);
  delayMicroseconds(litDurationMicros);
  digitalWrite(13, LOW);
  delayMicroseconds(fadeMaxMicros);
  
  if (diff > fadeLengthMillis) {
    // reset last switch time
    last = now;
  
    // swap fade direction
    if (fadeUpState == 0) {
      fadeUpState = 1;
    } else {
      fadeUpState = 0;
    }
  }
}

