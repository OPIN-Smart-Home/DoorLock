#include <WiFi.h>
#include <PicoMQTT.h>
#include <WiFiManager.h>

#define LED 18
#define RELAY 13
#define WIFI_BUTTON 4

String Wifissid;
PicoMQTT::Server mqtt;

int push_count;
int commandMsg = 0;
int wifi_timeout = 90; // seconds
unsigned long start_time;

// DEVICE ID
const char* topic_ack = "opin/DoorLock_k5vj7/ack";
const char* topic_u2d = "opin/DoorLock_k5vj7/u2d";
const char* device_ssid = "OPIN-DoorLock-k5vj7";

void connect_mqtt() {
  Serial.println("\nStart MQTT Broker");
  const char* mqtt_server = WiFi.localIP().toString().c_str();

  // Subscribe to a topic pattern and attach a callback
  mqtt.subscribe(topic_u2d, [](const char * topic, const char * payload) {
    Serial.printf("Received message in topic '%s': %s\n", topic, payload);
    commandMsg = atoi(payload);
  });

  // Start the broker
  mqtt.begin();

  delay(100);
  Serial.println("MQTT Broker ready");
}

void connect_wifi() {
  Serial.println("\n Connecting...");
  digitalWrite(LED, LOW);
  delay(100);
  digitalWrite(LED, HIGH);
  delay(100);
  digitalWrite(LED, LOW);
  delay(100);
  digitalWrite(LED, HIGH);
  delay(100);
  digitalWrite(LED, LOW);

  WiFiManager wm;
  wm.setConnectTimeout(5);
  wm.setConfigPortalTimeout(wifi_timeout);
  wm.startConfigPortal(device_ssid);

  if (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    digitalWrite(LED, HIGH);
    delay(500);
    digitalWrite(LED, LOW);
    delay(500);
  }else if (WiFi.status() == WL_CONNECTED){
    Serial.println("Connected");
    connect_mqtt();
  }
}

void reset_wifi() {
  digitalWrite(LED, LOW);
  delay(100);
  digitalWrite(LED, HIGH);
  delay(100);
  digitalWrite(LED, LOW);
  delay(100);
  digitalWrite(LED, HIGH);
  delay(100);
  digitalWrite(LED, LOW);
  delay(100);
  digitalWrite(LED, HIGH);
  delay(100);
  digitalWrite(LED, LOW);

  WiFiManager wm;
  WiFi.disconnect();
  wm.resetSettings();
}

void reconnect_wifi(String ssid, String pass) {
  delay(100);
  Serial.println("Reconnecting...");
  WiFi.disconnect();
  WiFi.begin(ssid, pass);

  unsigned long start_timeout = millis();
  while (WiFi.status() != WL_CONNECTED){
    if (millis() - start_timeout >= 3000){
      break;
    }
    digitalWrite(LED, HIGH);
    delay(500);
    digitalWrite(LED, LOW);
    delay(500);
  }
  if (WiFi.status() == WL_CONNECTED){
    Serial.println("Connected");
    connect_mqtt();
  }
}

void setup() {
  WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP
  Serial.begin(115200);
  Serial.println("\n Starting up");
  digitalWrite(RELAY, HIGH);
  pinMode(LED, OUTPUT);
  pinMode(RELAY, OUTPUT);
  pinMode(WIFI_BUTTON, INPUT_PULLUP);
}

void loop() {
  // WIFI and MQTT Connection
  push_count = 0;
  if (digitalRead(WIFI_BUTTON) == LOW) {
    start_time = millis();
    while (true) {
      if (millis() - start_time >= 100 && digitalRead(WIFI_BUTTON) == HIGH) {
        push_count = 1;
        break;
      }
      if (millis() - start_time >= 2000 && digitalRead(WIFI_BUTTON) == LOW) {
        push_count = 2;
        break;
      }
    }
  }

  if (push_count == 1) {
    connect_wifi();
  } else if (push_count == 2) {
    reset_wifi();
    connect_wifi();
  }

  if (WiFi.status() != WL_CONNECTED){
    WiFiManager wm;
    reconnect_wifi(wm.getWiFiSSID(), WiFi.psk());
  } else {
    mqtt.loop();
    digitalWrite(LED, HIGH);
  }

  // Main Program
  if (commandMsg == 1) {
    digitalWrite(RELAY, LOW);
    delay(20);
    digitalWrite(RELAY, HIGH);
    Serial.println("Door Opened");
    String json_data =  String("{") +
                        String("\"state\": 0") + 
                        String("}");
    mqtt.publish(topic_ack, json_data.c_str());
  }
  else {
    digitalWrite(RELAY, HIGH);
  }
  commandMsg = 0;
  delay(10);
}
