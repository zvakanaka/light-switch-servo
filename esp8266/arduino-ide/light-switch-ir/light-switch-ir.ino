#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>
#include <Servo.h>

// supply 5v to the servo and 3.3v to the IR receiver

int SERVO_PIN = 14; // GPIO14 is labelled D5 on the D1 Mini
Servo servo;  // object to control a servo
int SERVO_MAX = 115; // 180 is the absolute max limit
int SERVO_MIN = 15; // 0 is the absolute low limit
int SERVO_MIDDLE = int(SERVO_MAX + SERVO_MIN) / 2;
int SERVO_DELAY = 500;

// THANK YOU: https://github.com/crankyoldgit/IRremoteESP8266
// Note: GPIO 16 won't work on the ESP8266 as it does not have interrupts.
const uint16_t kRecvPin = 4; // GPIO4 is labelled D2 on the D1 Mini
IRrecv irrecv(kRecvPin);
decode_results results;

void setup() {
  Serial.begin(115200);
  while (!Serial)
    delay(50);
  Serial.println();

  irrecv.enableIRIn(); // start the receiver
  Serial.print("IRrecvDemo is now running and waiting for IR message on Pin ");
  Serial.println(kRecvPin);

  servo.attach(SERVO_PIN); // attach the servo on GPIO2 (D4 on a NodeMCU board) to the servo object
  servo.write(SERVO_MIDDLE); // tell servo to go to degree
  delay(SERVO_DELAY); // wait n ms for the servo to reach the position
}

void loop() {
  // Thank you: https://github.com/crankyoldgit/IRremoteESP8266/blob/master/examples/IRrecvDemo/IRrecvDemo.ino
  if (irrecv.decode(&results)) {
    Serial.print(results.bits);
    Serial.print(": ");
    serialPrintUint64(results.value, HEX);
    Serial.println("");

    switch(results.value){
      case 0xFFA25D:
        Serial.println("IR: ON");
        // uncomment the next line if you want to test using the light on the board (for off, uncomment the one in the next case too)
        // digitalWrite(LED_BUILTIN, LOW);
        servo.write(SERVO_MAX); // tell servo to go to degree
        delay(SERVO_DELAY); // waits n ms for the servo to reach the position
        servo.write(SERVO_MIDDLE); // tell servo to go to degree
        delay(SERVO_DELAY); // waits n ms for the servo to reach the position
        break;
      case 0xFFE21D:
        Serial.println("IR: OFF");
        // digitalWrite(LED_BUILTIN, HIGH);
        servo.write(SERVO_MIN); // tell servo to go to degree
        delay(SERVO_DELAY); // waits n ms for the servo to reach the position
        servo.write(SERVO_MIDDLE); // tell servo to go to degree
        delay(SERVO_DELAY); // waits n ms for the servo to reach the position
        break;
    }
    irrecv.resume();
  }
}
