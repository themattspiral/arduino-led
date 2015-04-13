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
long fadeLengthMillis = 2000;
int fadeUpState = 1;

// 500 Hz = 1/500 * 1M us = 2000us period
long periodMicros = 2000;
long fadeMinMicros = 100; // 5% duty minimum
long fadeMaxMicros = periodMicros - fadeMinMicros;

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

  Serial.begin(9600);
}

// loop runs forever
void loop() {
  unsigned long now = millis();
  int diff = now - last;

  long litDurationMicros = 0L;

  if (fadeUpState == 1) {
    // fade up
    //litDurationMicros = fadeBaseMicros + diff;
    litDurationMicros = map(diff, 0, fadeLengthMillis, fadeMinMicros, fadeMaxMicros);
  } else {
    // fade down
    //litDurationMicros = fadeMaxMicros - diff;
    litDurationMicros = map(diff, 0, fadeLengthMillis, fadeMaxMicros, fadeMinMicros);
  }

  long offDurationMicros = fadeMaxMicros - litDurationMicros;

  // avoid 'negative' overflow in unsigned long, or values less than base/min
  if (litDurationMicros < fadeMinMicros) {
    Serial.print("Correcting - litDurationMicros: ");
    Serial.print(litDurationMicros, DEC);
    
    Serial.print(" | fadeUpState: ");
    Serial.print(fadeUpState, DEC);
    
    Serial.print(" | diff: ");
    Serial.println(diff, DEC);
    
    litDurationMicros = fadeMinMicros;
  }

  digitalWrite(PIN_ANODE_1, HIGH);
  delayMicroseconds(litDurationMicros);

  digitalWrite(PIN_ANODE_1, LOW);
  delayMicroseconds(offDurationMicros);
  
  
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

