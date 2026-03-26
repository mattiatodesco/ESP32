#include <WiFi.h>
#include <PubSubClient.h>

// Credenziali WiFi
const char* ssid = "BancoSperimentale2G";
const char* password = "Galileo19";

// Broker MQTT
const char* mqtt_server = "192.168.6.13";

WiFiClient espClient;
PubSubClient client(espClient);

// Funzione chiamata quando arriva un messaggio

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
      client.subscribe("lab/222b/banco/2/postazione/2");

    } else {
      Serial.print("fallita, rc=");
      Serial.print(client.state());
      Serial.println(" riprovo tra 5 secondi");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();

  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}