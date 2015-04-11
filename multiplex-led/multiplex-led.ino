/**
 * multiplex-led
 *
 * Arduino LED multiplexing example, used as a POC for my approach to Nixie tube control.
 */

int PIN_ANODE_1 = 12;

int PIN_CATHODE_1 = 2;
int PIN_CATHODE_2 = 3;
int PIN_CATHODE_3 = 4;
int PIN_CATHODE_4 = 5;

int DEMO_CYCLE_MS = 2000;
int DELAYS[] = {250, 100, 50, 20, 0};
int CURRENT_DELAY_INDEX = 0;

unsigned long LAST_ELAPSED_MS = 0;

void setup() {
  pinMode(PIN_ANODE_1, OUTPUT);
  pinMode(PIN_CATHODE_1, OUTPUT);
  pinMode(PIN_CATHODE_2, OUTPUT);
  pinMode(PIN_CATHODE_3, OUTPUT);
  pinMode(PIN_CATHODE_4, OUTPUT);
}

// loop runs forever
void loop() {
  unsigned long now = millis();
  unsigned long diff = now - LAST_ELAPSED_MS;
  
  if (diff >= DEMO_CYCLE_MS) {
    LAST_ELAPSED_MS = now;
    
    CURRENT_DELAY_INDEX++;
    if (CURRENT_DELAY_INDEX > 4) {
      CURRENT_DELAY_INDEX = 0;
    }
  }
  
  // note - we never turn the anode off - just cathode control for this example
  digitalWrite(PIN_ANODE_1, HIGH);
  
  digitalWrite(PIN_CATHODE_1, HIGH);
  delay(DELAYS[CURRENT_DELAY_INDEX]);
  
  digitalWrite(PIN_CATHODE_1, LOW);
  digitalWrite(PIN_CATHODE_2, HIGH);
  delay(DELAYS[CURRENT_DELAY_INDEX]);
  
  digitalWrite(PIN_CATHODE_2, LOW);
  digitalWrite(PIN_CATHODE_3, HIGH);
  delay(DELAYS[CURRENT_DELAY_INDEX]);
  
  digitalWrite(PIN_CATHODE_3, LOW);
  digitalWrite(PIN_CATHODE_4, HIGH);
  delay(DELAYS[CURRENT_DELAY_INDEX]);
  
  digitalWrite(PIN_CATHODE_4, LOW);
}

