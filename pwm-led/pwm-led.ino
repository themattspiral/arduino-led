/**
 * pwm-led
 * 
 * Arduino PWM example of LED pulsing (fade up/down) using manual PWM.
 */

int PIN_ANODE_1 = 12;

int PIN_CATHODE_1 = 2;
int PIN_CATHODE_2 = 3;
int PIN_CATHODE_3 = 4;
int PIN_CATHODE_4 = 5;

unsigned long last = 0UL;
unsigned long fadeLengthMillis = 1000UL;
int fadeUpState = 1;

unsigned long fadeBaseMicros = 20UL;
unsigned long fadeMaxMicros = 1000UL;

void setup() {
  pinMode(PIN_ANODE_1, OUTPUT);
  pinMode(PIN_CATHODE_1, OUTPUT);
  pinMode(PIN_CATHODE_2, OUTPUT);
  pinMode(PIN_CATHODE_3, OUTPUT);
  pinMode(PIN_CATHODE_4, OUTPUT);
  
  digitalWrite(PIN_CATHODE_1, HIGH);
  digitalWrite(PIN_CATHODE_2, HIGH);
  digitalWrite(PIN_CATHODE_3, HIGH);
  digitalWrite(PIN_CATHODE_4, HIGH);
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
    
    // avoid 'negative' overflow in unsigned long, or values less than base/min
    if (fadeMaxMicros < diff || litDurationMicros < fadeBaseMicros) {
      litDurationMicros = fadeBaseMicros;
    }
  }
  
  digitalWrite(PIN_ANODE_1, HIGH);
  delayMicroseconds(litDurationMicros);
  digitalWrite(PIN_ANODE_1, LOW);
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

