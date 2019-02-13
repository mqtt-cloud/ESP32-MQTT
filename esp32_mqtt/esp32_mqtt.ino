#include <WiFi.h>
#include <PubSubClient.h>

//กำหนดชื่อและรหัสผ่าน WIFI
#define WIFI_STA_NAME "xxxxxxxxxx"
#define WIFI_STA_PASS "xxxxxxxxxx"

//กำหนด MQTT
#define MQTT_SERVER   "m11.cloudmqtt.com"
#define MQTT_PORT     10384
#define MQTT_USERNAME "esp32_1"
#define MQTT_PASSWORD "123456"
#define MQTT_NAME     "ESP32_1"
WiFiClient client;
PubSubClient mqtt(client);

void callback(char* topic, byte* payload, unsigned int length) {
  payload[length] = '\0';
  String topic_str = topic, payload_str = (char*)payload;
  Serial.println("[" + topic_str + "]: " + payload_str);
}

void setup() {
  Serial.begin(115200);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WIFI_STA_NAME);

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_STA_NAME, WIFI_STA_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  mqtt.setServer(MQTT_SERVER, MQTT_PORT);
  mqtt.setCallback(callback);
}

void loop() {
  if (mqtt.connected() == false) {
    Serial.print("MQTT connection... ");
    if (mqtt.connect(MQTT_NAME, MQTT_USERNAME, MQTT_PASSWORD)) {
      Serial.println("connected");
      mqtt.subscribe("/ESP32_1/LED");
    } else {
      Serial.println("failed");
      delay(5000);
    }
  } else {
    mqtt.loop();
  }
}
