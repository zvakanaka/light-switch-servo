#include <ESP8266WiFi.h>
#include <PubSubClient.h>// Download and install this library first from: https://www.arduinolibraries.info/libraries/pub-sub-client
#include <WiFiClient.h>
#include <Servo.h>

// THANK YOU: https://github.com/aososam/Smartnest
#define SSID_NAME ""                   // Your Wifi Network name
#define SSID_PASSWORD ""           // Your Wifi network password
#define MQTT_BROKER "smartnest.cz"              // Broker host
#define MQTT_PORT 1883                          // Broker port
#define MQTT_USERNAME ""                // Username from Smartnest
#define MQTT_PASSWORD ""         // Password from Smartnest (or API key)
#define MQTT_CLIENT ""  //Device Id from smartnest

WiFiClient espClient;
PubSubClient client(espClient); 

int SERVO_PIN = 14;
Servo servo;  // create servo object to control a servo
// twelve servo objects can be created on most boards
int SERVO_MAX = 115; // 180 is the absolute max limit
int SERVO_MIN = 25; // 0 is the absolute low limit
int SERVO_MIDDLE = int(SERVO_MAX + SERVO_MIN) / 2;
int SERVO_DELAY = 500;

void startWifi();
void startMqtt();
void checkMqtt();
int splitTopic(char* topic, char* tokens[] ,int tokensNumber);
void callback(char* topic, byte* payload, unsigned int length);

void setup() {
  Serial.begin(115200);
  while (!Serial)
    delay(50);
  Serial.println();

  startWifi();
  startMqtt();

  servo.attach(SERVO_PIN); // attach the servo on GPIO2 (D4 on a NodeMCU board) to the servo object
  servo.write(SERVO_MIDDLE); // tell servo to go to degree
  delay(SERVO_DELAY); // wait n ms for the servo to reach the position
}

void loop() {
  client.loop();
  checkMqtt();
}

void callback(char* topic, byte* payload, unsigned int length) { // a new message has been received
  Serial.print("Topic:");
  Serial.println(topic);
   int tokensNumber=10;
   char *tokens[tokensNumber];
   char message[length+1];
   splitTopic(topic, tokens, tokensNumber);
   sprintf(message,"%c",(char)payload[0]);
   for (int i = 1; i < length; i++) {
    sprintf(message,"%s%c",message,(char)payload[i]);
   }
    Serial.print("Message:");
    Serial.println(message);
 
//------------------ACTIONS HERE---------------------------------
  char myTopic[100];
  
  if(strcmp(tokens[1],"directive")==0 && strcmp(tokens[2],"powerState")==0){
    sprintf(myTopic,"%s/report/powerState",MQTT_CLIENT);

    if(strcmp(message,"ON")==0){
//      digitalWrite(lightPin, LOW); 
      servo.write(SERVO_MAX); // tell servo to go to degree
      delay(SERVO_DELAY); // waits n ms for the servo to reach the position
      servo.write(SERVO_MIDDLE); // tell servo to go to degree
      delay(SERVO_DELAY); // waits n ms for the servo to reach the position
      client.publish(myTopic, "ON") ;            

    } else if(strcmp(message,"OFF")==0){
      // digitalWrite(lightPin, HIGH);     
      servo.write(SERVO_MIN); // tell servo to go to degree
      delay(SERVO_DELAY); // waits n ms for the servo to reach the position
      servo.write(SERVO_MIDDLE); // tell servo to go to degree
      delay(SERVO_DELAY); // waits n ms for the servo to reach the position              
      client.publish(myTopic, "OFF"); 

    }
  }
}


void startWifi(){
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID_NAME, SSID_PASSWORD);
  Serial.println("Connecting ...");
  int attempts  = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 10 ) {
    attempts++;
    delay(500);
    Serial.print(".");
  }

  if(WiFi.status() == WL_CONNECTED){

    Serial.println('\n');
    Serial.print("Connected to ");
    Serial.println(WiFi.SSID());             
    Serial.print("IP address:\t");
    Serial.println(WiFi.localIP());

  } else {

    Serial.println('\n');
    Serial.println('I could not connect to the wifi network after 10 attempts \n');

  }
  
  delay(500);  
}

void startMqtt(){
  client.setServer(MQTT_BROKER, MQTT_PORT);
  client.setCallback(callback);

 while (!client.connected()) {
    Serial.println("Connecting to MQTT...");

    if (client.connect(MQTT_CLIENT, MQTT_USERNAME, MQTT_PASSWORD )) {
      Serial.println("connected");
    } else {
      if (client.state()==5){

        Serial.println("Connection not allowed by broker, possible reasons:");
        Serial.println("- Device is already online. Wait some seconds until it appears offline for the broker");
        Serial.println("- Wrong Username or password. Check credentials");
        Serial.println("- Client Id does not belong to this username, verify ClientId");
      
      } else {

        Serial.println("Not possible to connect to Broker Error code:");
        Serial.print(client.state());
      }

      delay(0x7530);
    }
  }

  
  char topic[100];
  sprintf(topic,"%s/#",MQTT_CLIENT);
  client.subscribe(topic);

  sprintf(topic,"%s/report/online",MQTT_CLIENT);         // Reports that the device is online
  client.publish(topic, "true");
  delay(200);

}

int splitTopic(char* topic, char* tokens[],int tokensNumber ){

    const char s[2] = "/";
    int pos=0;
    tokens[0] = strtok(topic, s);

    while(pos<tokensNumber-1 && tokens[pos] != NULL ) {
        pos++;
      tokens[pos] = strtok(NULL, s);
    }

    return pos;   
}


void checkMqtt(){
  if(!client.connected()){
    startMqtt();
  }
}