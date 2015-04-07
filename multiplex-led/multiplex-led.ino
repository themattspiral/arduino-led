/**
 * multiplex-led
 *
 * Arduino LED multiplexing example, used as a POC for my approach to Nixie tube control.
 * This example assumes 4 leds are available. There is 1 'anode' pin, shared among all 4 LEDs. 
 * There are 4 'cathode' pins, each one controlling the base of an NPN transistor such that when
 * the pin is HIGH, the LED ground will be connected to the Arduino ground and current will flow.
 *
 *                               ANODE_1 (PIN 12)
 *                                     |
 *                  ----------------------------------------
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
 *       |   (PIN 2)          |    (PIN 3)      |    (PIN 4)           |    (PIN 5)
 *      GND                 GND                GND                    GND 
 *
 * Keep in mind, we only have 4 leds, so we could hard-ground them all and drive each one individually 
 * with a dedicated anode pin, rather than multiplexing. But that would go against the point of this
 * demonstration, which is specifically meant to show multiplexing.
 *
 */

int PIN_ANODE_1 = 12;

int PIN_CATHODE_1 = 2;
int PIN_CATHODE_2 = 3;
int PIN_CATHODE_3 = 4;
int PIN_CATHODE_4 = 5;

int DEMO_CYCLE_MS = 2000;
int DELAYS[] = {250, 100, 50, 20, 1};
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

