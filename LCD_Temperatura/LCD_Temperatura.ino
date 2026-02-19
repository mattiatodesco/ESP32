#include <LiquidCrystal.h>

// Inizializza la libreria con i pin: RS, E, D4, D5, D6, D7
// Usiamo i pin mappati precedentemente
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(19, 23, 18, 17, 16, 15);

#define VREF_mV    1266.0 // fondoscala ADC in millivolt
#define res 4095.0  // risoluzione predefinita 12 bit
#define sensore 34 // ESP32 pin GPIO36 (ADC0) connesso a LM35
#define pulsante 22

unsigned long ultimoReset = 0;
 
void setup() {
  Serial.begin(9600);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Temperatura");

  analogSetAttenuation(ADC_0db);

  pinMode(pulsante, INPUT_PULLDOWN);

  ultimoReset = (int)millis();
}
 
void loop() {
  // lettura grezza dell' ADC value dal sensore LM35 attraverso il GPIO36
  int lettura = analogRead(sensore);
  // converte la lettura dell'ADC in millivolt
  float milliVolt = lettura * (VREF_mV / res);
  // converte la tensione in temperatura espressa in °C
  float tempC = milliVolt / 10;  // pendenza della caratteristica LM35
                                 // pari a 10 mV al grado
  
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  
  lcd.print(tempC);

  boolean letturaBottone = digitalRead(pulsante); 
  if (letturaBottone){
    ultimoReset = (int)millis();
  }

  unsigned long millisecondiAttuali = millis() - ultimoReset;
  unsigned long totaleSecondi = millisecondiAttuali / 1000;

  int secondi = totaleSecondi % 60;
  int minuti = (totaleSecondi / 60) % 60;
  int ore = (totaleSecondi / 3600);
  
  lcd.setCursor(8, 1);
  if(ore < 10) lcd.print("0"); // Formattazione 00:00:00
  lcd.print(ore);
  lcd.print(":");
  if(minuti < 10) lcd.print("0");
  lcd.print(minuti);
  lcd.print(":");
  if(secondi < 10) lcd.print("0");
  lcd.print(secondi);  

  Serial.print(ore);
  Serial.print(":");
  Serial.print(minuti);
  Serial.print(":");
  Serial.println(secondi);

  delay(500);
}
