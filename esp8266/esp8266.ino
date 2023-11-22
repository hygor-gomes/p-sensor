#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "HDS";
const char* password = "batmao3037478";
const char* mqttServer = "industrial.api.ubidots.com";
const int mqttPort = 1883;
const char* mqttUser = "BBUS-MUgwC6VZjsgGwmb2zGPyeSSZkNUUEX";
const char* mqttPassword = "";

WiFiClient espClient;
PubSubClient client(espClient);

unsigned long lastCommandTime = 0;  // Para medir o tempo entre o envio de comandos e a ação do atuador
unsigned long lastSensorDetectionTime = 0;  // Para medir o tempo entre a detecção de um sensor e o recebimento dos dados MQTT

void setup() {
  Serial.begin(9600);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  client.setServer(mqttServer, mqttPort);
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");

    if (client.connect("ESP8266Client", mqttUser, mqttPassword )) {
      Serial.println("Connected to MQTT");
    } else {
      Serial.print("Failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }
}

void loop() {
  if (Serial.available()) {
    unsigned long currentTime = millis();  // Obtém o tempo atual

    String myBPM = Serial.readStringUntil('\n');
    myBPM.trim();
    String payload = "{\"value\":" + myBPM + "}";
    char attributes[100];
    payload.toCharArray(attributes, 100);

    // Calcula o tempo entre o envio de comandos e a ação do atuador
    unsigned long timeSinceLastCommand = currentTime - lastCommandTime;
    Serial.print("Tempo desde o último comando: ");
    Serial.println(timeSinceLastCommand);

    // Calcula o tempo entre a detecção de um sensor e o recebimento dos dados MQTT
    unsigned long timeSinceLastSensorDetection = currentTime - lastSensorDetectionTime;
    Serial.print("Tempo desde a última detecção de sensor: ");
    Serial.println(timeSinceLastSensorDetection);

    if (client.publish("/v1.6/devices/esp8266/bpm", attributes)) {
      Serial.println("Publish successful");
      lastSensorDetectionTime = currentTime;  // Atualiza o marcador de tempo para a detecção de sensor bem-sucedida
    } else {
      Serial.println("Publish failed");
    }

    lastCommandTime = currentTime;  // Atualiza o marcador de tempo para o envio de comando bem-sucedido

    Serial.print("BPM value ");
    Serial.print(myBPM);
    Serial.println(" sent to MQTT.");
    Serial.print("Client state: ");
    Serial.println(client.state());
  }
}
