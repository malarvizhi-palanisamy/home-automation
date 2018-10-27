 // This example uses an Adafruit Huzzah ESP8266
// to connect to shiftr.io.
//
// You can check on your device after a successful
// connection here: https://shiftr.io/try.
//
// by Joël Gähwiler
// https://github.com/256dpi/arduino-mqtt

#include <ESP8266WiFi.h>
#include <MQTT.h>

const char ssid[] = "kprcse";
const char pass[] = "12345678";
int x;
WiFiClient net;
MQTTClient client;

unsigned long lastMillis = 0;

void connect() {
  Serial.print("checking wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.print("\nconnecting...");
  while (!client.connect("arduino", "try", "try")) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nconnected!");

  client.subscribe("malar_button_t");
  // client.unsubscribe("/hello");
}

void messageReceived(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload);

 if(payload=="1")
  digitalWrite(D0,HIGH);
  else if(payload=="0")
    digitalWrite(D0,LOW);
   else if(payload=="a")
  digitalWrite(D1,HIGH);
  else if(payload=="b")
    digitalWrite(D1,LOW); 
   else if(payload=="on")
  digitalWrite(D2,HIGH);
  else if(payload=="off")
    digitalWrite(D2,LOW);
   else if(payload=="yes")
  digitalWrite(D4,HIGH);
  else if(payload=="no")
    digitalWrite(D4,LOW);

    
}

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, pass);

  // Note: Local domain names (e.g. "Computer.local" on OSX) are not supported by Arduino.
  // You need to set the IP address directly.
  //
  // MQTT brokers usually use port 8883 for secure connections.
  client.begin("broker.shiftr.io", net);
  client.onMessage(messageReceived);
  pinMode(D0,OUTPUT);
 pinMode(D1,OUTPUT);
  pinMode(D2,OUTPUT);
   pinMode(D4,OUTPUT);
  connect();
}

void loop() {
  client.loop();
  delay(10);  // <- fixes some issues with WiFi stability

  if (!client.connected()) {
    connect();
  }

x=analogRead(A0);
  // publish a message roughly every second.
  if (millis() - lastMillis > 1000) {
    lastMillis = millis();
    client.publish("malar_button_t1",(String)x);
  }
}
