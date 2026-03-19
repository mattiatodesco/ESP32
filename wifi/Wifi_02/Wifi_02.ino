/* Wifi_02.cpp - Connessione alla rete specificata nel file ConfigWifi.h,
   visualizzazione dell'IPv4 assegnato dal DHCP e ping verso un altro ESP32 */
#include <WiFi.h>
#include <ESP32Ping.h>
#include "ConfigWifi.h"

const int LED_ON_BOARD = 2;

// IP dell'altro ESP32 collegato alla stessa rete
IPAddress ipRemoto(192, 168, 1, 50);

// dichiarazione funzioni di servizio

void setup() {
  Serial.begin(115200);
  pinMode(LED_ON_BOARD, OUTPUT);

  // Imposta l'ESP32 in modalità Station
  WiFi.mode(WIFI_STA);

  Serial.println("\nConnessione in corso...");
  WiFi.begin(ssid, password);

  // Attende finché la connessione non è stabilita
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnesso correttamente!");
  Serial.print("Indirizzo IP locale: ");
  Serial.println(WiFi.localIP());   // Stampa l'IP assegnato dal DHCP

  Serial.print("Ping verso il dispositivo con IP: ");
  Serial.println(ipRemoto);
}

void loop() {
  digitalWrite(LED_ON_BOARD, HIGH);

  Serial.println("\nInvio ping...");
  bool esitoPing = Ping.ping(ipRemoto, 3);

  if (esitoPing) {
    Serial.println("Host raggiungibile.");
    Serial.print("Tempo medio di risposta: ");
    Serial.print(Ping.averageTime());
    Serial.println(" ms");
  } else {
    Serial.println("Host non raggiungibile.");
  }

  delay(1000);
  digitalWrite(LED_ON_BOARD, LOW);
  delay(4000);
}

// definizione funzioni di servizio