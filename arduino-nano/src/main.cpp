#include <Arduino.h>
#include <IRremote.h>
#include <Servo.h>

#define TEST // ALLOW USB SERIAL VALUES TO TEST SERVO (e.g. 123)

// supply 5v to the servo and 3.3v to the IR receiver

#define SERVO_PIN 8 // D8
Servo servo;  // object to control a servo
#define SERVO_MAX 115 // 180 is the absolute max limit
#define SERVO_MIN 15 // 0 is the absolute low limit
int SERVO_MIDDLE = int(SERVO_MAX + SERVO_MIN) / 2;
#define SERVO_DELAY 500

#define IR_RECV_PIN 12 // D12
#define REMOTE_PLUS 0xFFE21D
#define REMOTE_MINUS 0x00FFA25D
#define REPEAT 0xEE12FF00

unsigned long val;
IRrecv irrecv(IR_RECV_PIN);
decode_results results;

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  delay(200);
  Serial.println("startup");

  servo.attach(SERVO_PIN); // attach the servo on GPIO2 (D4 on a NodeMCU board) to the servo object
  servo.write(SERVO_MIDDLE); // tell servo to go to degree
  
  irrecv.enableIRIn(); // Start receiving
  irrecv.blink13(true); // blink while receiving
}

void loop() {
  if (irrecv.decode(&results)) {
    val = results.value;
    irrecv.resume();
    delay(150);
    Serial.println(val, HEX);
    if (val == REMOTE_PLUS) {
      // digitalWrite(LED_BUILTIN, HIGH);
      // Serial.println("ON");
      servo.write(SERVO_MAX); // tell servo to go to degree
      delay(SERVO_DELAY); // waits n ms for the servo to reach the position
      servo.write(SERVO_MIDDLE); // tell servo to go to degree
      delay(SERVO_DELAY); // waits n ms for the servo to reach the position
    } else if (val == REMOTE_MINUS) {
      // Serial.println("OFF");
      // digitalWrite(LED_BUILTIN, LOW);
      servo.write(SERVO_MIN); // tell servo to go to degree
      delay(SERVO_DELAY); // waits n ms for the servo to reach the position
      servo.write(SERVO_MIDDLE); // tell servo to go to degree
      delay(SERVO_DELAY); // waits n ms for the servo to reach the position
    }
    delay(200);
  }
#ifdef TEST
   if (Serial.available() > 0) {
    String incomingString = Serial.readString();

    Serial.print("Serial received: ");
    Serial.println(incomingString);

    servo.write(incomingString.toInt());
    servo.write(incomingString.toInt()); // tell servo to go to degree
    delay(SERVO_DELAY); // waits n ms for the servo to reach the position
    servo.write(SERVO_MIDDLE); // tell servo to go to degree
    delay(SERVO_DELAY); // waits n ms for the servo to reach the position
  }
#endif
}
