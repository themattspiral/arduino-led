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
int fadeLengthMillis = 1000;
int fadeUpState = 1;

int fadeMinMicros = 20;
int fadeMaxMicros = 800;

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
  
  //Serial.begin(9600);
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
    
    // avoid 'negative' overflow in unsigned long, or values less than base/min
    //if (fadeMaxMicros < diff || litDurationMicros < fadeBaseMicros) {
    //  litDurationMicros = fadeBaseMicros;
    //}
  }
  
  digitalWrite(PIN_ANODE_1, HIGH);
  delayMicroseconds(litDurationMicros);
  digitalWrite(PIN_ANODE_1, LOW);
  delayMicroseconds(fadeMaxMicros + litDurationMicros);
  
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

