#include <Arduino.h>

#define LED 5
#define POTENZIOMETRO 34
#define FREQ 1000
#define RES 8

void setup() {
  Serial.begin(115200);
  //ledcSetup(0, FREQ, RES);
  //ledcAttachPin(LED, 0);
  //Versione nuova tutta insieme ma platform io piange
  ledcAttach(LED, FREQ, RES);
  
}

void loop() {
  double read = analogRead(POTENZIOMETRO);
   Serial.print(read);
   Serial.print("  ");
   double percent = read/4095;
   Serial.println(percent * 3.3);

  // Metto il canale e non il led perché uso le librerie vecchie
   ledcWrite(LED, percent * (2^RES));

   delay(50);
   
}
