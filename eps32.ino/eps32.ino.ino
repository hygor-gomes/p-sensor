#include <WiFi.h>
#include <PubSubClient.h>
#include <PulseSensorPlayground.h>

const char *ssid = "";
const char *password = "";

const char *ubidotsToken = "";
const char *ubidotsClientName = "esp32_pulse_sensor";

const char *mqttBroker = "industrial.api.ubidots.com";
const int mqttPort = 1883;

const int PulseWire = 17;
const int LED13 = 13;
int Threshold = 550;

PulseSensorPlayground pulseSensor;

WiFiClient espClient;
PubSubClient client(espClient);

void connectWiFi() {
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");
}

void connectMQTT() {
  Serial.print("Connecting to MQTT");
  client.setServer(mqttBroker, mqttPort);
  while (!client.connected()) {
    if (client.connect(ubidotsClientName, ubidotsToken, "")) {
      Serial.println("\nConnected to MQTT");
    } else {
      Serial.print(".");
      delay(500);
    }
  }
}

void setup() {
  Serial.begin(115200);
  pulseSensor.analogInput(PulseWire);
  pulseSensor.blinkOnPulse(LED13);
  pulseSensor.setThreshold(Threshold);

  connectWiFi();
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    connectWiFi();
  }

  if (!client.connected()) {
    connectMQTT();
  }

  int myBPM = pulseSensor.getBeatsPerMinute();

  if (pulseSensor.sawStartOfBeat()) {
    Serial.println("♥  A HeartBeat Happened !");
    Serial.print("BPM: ");
    Serial.println(myBPM);

    char topic[50];
    sprintf(topic, "/v1.6/devices/%s", ubidotsClientName);

    char payload[20];
    sprintf(payload, "{\"bpm\": %d}", myBPM);

    client.publish(topic, payload);

    Serial.println("Published to Ubidots");
    delay(1000);
  }

  client.loop();
  delay(20);
}
