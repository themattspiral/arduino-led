/**
 * Arduino PWM example of LED pulsing (fade up/down) using manual PWM.
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

