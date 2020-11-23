#include <IRremote.h>

/*
 * Fysiske komponenter brukt i prosjektet:
 * - Luxorparts 'Keyes' IR Receiver (5V)
 * - Luxorparts IR Remote
 * - Artic PC vifte 12V (Kjøres på 3.3V, brukes som test)
 */


// Knapper på fjernkontrollen med HEX data
#define BUTTON_ARROW_UP 0xFF629D
#define BUTTON_ARROW_DOWN 0xFFA857
#define BUTTON_ARROW_lEFT 0xFF22DD
#define BUTTON_ARROW_RIGHT 0xFFC23D
#define BUTTON_OK 0xFF02FD

#define BUTTON_1 0xFF6897
#define BUTTON_2 0xFF9867
#define BUTTON_3 0xFFB04F
#define BUTTON_4 0xFF30CF
#define BUTTON_5 0xFF18E7
#define BUTTON_6 0xFF7A85
#define BUTTON_7 0xFF10EF
#define BUTTON_8 0xFF38C7
#define BUTTON_9 0xFF5AA5
#define BUTTON_0 0xFF4AB5
#define BUTTON_STJERNE 0xFF42BD
#define BUTTON_FIRKANT 0xFF52AD

const int IR_PIN = 11; //PWM
const int MOTOR_PIN = 7;

IRrecv irReceiver(IR_PIN);
decode_results results;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(MOTOR_PIN, OUTPUT);
  Serial.begin(9600);

  irReceiver.enableIRIn();  // Start the receiver
  irReceiver.blink13(true); // LED på Arduino blinker ved signal

  Serial.print("IR Pin klar til bruk på: ");
  Serial.println(IR_PIN);

  digitalWrite(MOTOR_PIN, LOW);
}

void loop() {
  if (irReceiver.decode(&results)) {
    Serial.println(results.value, HEX);
    irReceiver.resume(); // Hent neste IR verdi

    switch (results.value) {
      case BUTTON_OK:
        digitalWrite(MOTOR_PIN, !digitalRead(MOTOR_PIN));
        break;

      case BUTTON_STJERNE:
        digitalWrite(MOTOR_PIN, HIGH);
        break;

      case BUTTON_FIRKANT:
        digitalWrite(MOTOR_PIN, LOW);
        break;
    }
  }
  delay(100);
}
