#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

// Credenziali WiFi
const char* ssid = "BancoSperimentale2G";
const char* password = "Galileo19";

// Broker MQTT
const char* mqtt_server = "192.168.6.13";
unsigned long lastMsg = 0;
const int dim = 200;
char messaggio[dim];

// Doc JSON
JsonDocument doc;

WiFiClient espClient;
PubSubClient client(espClient);

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Messaggio ricevuto su topic: ");
  Serial.println(topic);

  Serial.print("Contenuto: ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

// Connessione WiFi
void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connessione a ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connesso!");
}

// Connessione MQTT
void reconnect() {
  while (!client.connected()) {
    Serial.print("Connessione MQTT...");
    
    if (client.connect("Toddy", "mqtt222b", "mqtt222b")) {
      Serial.println("connesso");
      // Sottoscrizione al topic
      client.subscribe("lab/222b/banco/#");


    } else {
      Serial.println("fallita, riprovo tra 5 secondi");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();

  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  doc["sensor"]["type"] = "temperature";
  doc["sensor"]["value"] = 0;
  doc["sensor"]["unit"] = "°C";
  doc["timestamp"] = 0;
  doc["source"] = "sensore_1";
  doc["status"] = "UP";

}

void loop() {
  if (!client.connected()) {
    reconnect();
  }

  client.loop();

  if (millis() - lastMsg > 5000) {    
    lastMsg = millis();

    doc["sensor"]["value"] = random(-5, 30);
    doc["timestamp"] = millis();

    serializeJson(doc, messaggio);

    //client.publish("lab/222b/banco/2/postazione/3", messaggio);

    Serial.println("Messaggio inviato");
    Serial.println(messaggio);

  }
}