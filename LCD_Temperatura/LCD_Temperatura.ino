#include <LiquidCrystal.h>

// Inizializza la libreria con i pin: RS, E, D4, D5, D6, D7
// Usiamo i pin mappati precedentemente
LiquidCrystal lcd(19, 23, 18, 17, 16, 15);

#define VREF_mV    1266.0 // fondoscala ADC in millivolt
#define res 4095.0  // risoluzione predefinita dell'adc, 12 bit
#define sensore 34 // ESP32 pin GPIO34 (ADC0) connesso a LM35
#define pulsante 22 // pin GPIO22 connesso al pulsante 

// dichiarazione variabili
int lettura = 0;
float milliVolt = 0;
float tempC = 0;

unsigned long millisecondiAttuali = 0;
unsigned long totaleSecondi = 0;

int secondi = 0;
int minuti = 0;
int ore = 0;

unsigned long ultimoReset = 0;

 
void setup() {
  // Inizializzazione monitor seriale
  Serial.begin(9600);
  // Setup del display con colonne e righe
  lcd.begin(16, 2);
  // Stampa la parola "Temperatura" sulla prima riga dello schermo
  lcd.print("Temperatura");

  // Imposta il range dell'ADC a 1.1V per massimizzare la precisione sui segnali bassi (10mV/°C).
  analogSetAttenuation(ADC_0db);

  // Definizione del pin del pulsante come input e attivazione resistenza di pull-down
  pinMode(pulsante, INPUT_PULLDOWN);

  // Definizione del valore iniziale dell'ultimo reset
  ultimoReset = (int)millis();
}
 
void loop() {
  // lettura grezza dell' ADC value dal sensore LM35 attraverso il GPIO34
  lettura = analogRead(sensore);
  // converte la lettura dell'ADC in millivolt
  milliVolt = lettura * (VREF_mV / res);
  // converte la tensione in temperatura espressa in °C
  tempC = milliVolt / 10;  // pendenza della caratteristica LM35
                           // pari a 10 mV al grado
  
  // Imposto il cursore all'inizio della seconda riga
  // (la seconda linea è la numero 1 perché il conteggio inizia da 0)
  lcd.setCursor(0, 1);
  // Stampa del valore di temperatura calcolato a partire dalla lettura del pin del sensore
  lcd.print(tempC);

  // Controllo se il pulsante viene premuto
  boolean letturaBottone = digitalRead(pulsante); 
  // Se il pulsante è premuto imposto il momento di ultimo reset al momento attuale
  if (letturaBottone){
    ultimoReset = (int)millis();
  }

  // Calcolo il numero di millisecondi trascorsi dall'ultimo reset, e successivamente i secondi
  millisecondiAttuali = millis() - ultimoReset;
  totaleSecondi = millisecondiAttuali / 1000;

  // Calcolo il numero di ore, minuti e secondi trascorsi, in modo da visualizzarli
  secondi = totaleSecondi % 60;
  minuti = (totaleSecondi / 60) % 60;
  ore = (totaleSecondi / 3600);
  
  // Sposto il cursore e visualizzo il contatore sul display
  lcd.setCursor(8, 1);
  if(ore < 10) lcd.print("0"); // Formattazione 00:00:00
  lcd.print(ore);
  lcd.print(":");
  if(minuti < 10) lcd.print("0");
  lcd.print(minuti);
  lcd.print(":");
  if(secondi < 10) lcd.print("0");
  lcd.print(secondi);  

  // Visualizzo anche sul monitor seriale
  Serial.print(ore);
  Serial.print(":");
  Serial.print(minuti);
  Serial.print(":");
  Serial.println(secondi);

  // Attendo 500 millisecondi per il debounce
  delay(500);
}
