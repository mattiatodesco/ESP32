#include <WiFi.h>
#include <PubSubClient.h>

// Credenziali WiFi
const char* ssid = "BancoSperimentale2G";
const char* password = "Galileo19";

// Broker MQTT
const char* mqtt_server = "192.168.6.13";
unsigned long lastMsg = 0;
int numeroInviato = 0;
const int dim = 10;
char messaggio[dim];

WiFiClient espClient;
PubSubClient client(espClient);


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
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }

  if (millis() - lastMsg > 5000) {
    
    lastMsg = millis();

    itoa(numeroInviato, messaggio, dim);
    client.publish("lab/222b/banco/2/postazione/3", messaggio);

    Serial.println("Messaggio inviato");

    numeroInviato += 1;
  }
}