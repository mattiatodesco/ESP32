// Contatore binario a 3 bit con ESP32

// Pin dei LED (bit 0, 1, 2)
const int ledPins[3] = {23, 22, 21};  

// Pin dei pulsanti
const int btnUp = 18;    // Pulsante per incrementare
const int btnDown = 19;  // Pulsante per decrementare

// Variabili di stato, conteggio e controllo dello stato dei bottoni
int counter = 0;
bool lastBtnUpState = HIGH;
bool lastBtnDownState = HIGH;

void setup() {
  //Configuro il monitor seriale
  Serial.begin(9600);
 
  // Configura i LED come output, e li spengo
  for (int i = 0; i < 3; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
  }
 
  // Configura i pulsanti come input con pull-up
  pinMode(btnUp, INPUT_PULLUP);
  pinMode(btnDown, INPUT_PULLUP);
 
  // Mostra il valore iniziale
  updateLEDs();
  Serial.println("Contatore binario 3 bit avviato");
  Serial.print("Valore iniziale: ");
  Serial.println(counter);
}

void loop() {
  bool btnUpState = digitalRead(btnUp);
  bool btnDownState = digitalRead(btnDown);
 
  // Pulsante UP (incrementa)
  if (btnUpState == LOW && lastBtnUpState == HIGH) {
      counter++;
      if (counter > 7) {  // 3 bit: range 0-7
        counter = 0;      // Riparti da 0
      }
      updateLEDs();
      printCounter();
      delay(200);
  }
 
  // Pulsante DOWN (decrementa)
  if (btnDownState == LOW && lastBtnDownState == HIGH) {
      counter--;
      if (counter < 0) {  // Se va sotto 0
        counter = 7;      // Vai a 7
      }
      updateLEDs();
      printCounter();
      delay(200);
            
  }
 
  lastBtnUpState = btnUpState;
  lastBtnDownState = btnDownState;

}

void updateLEDs() {
  // Aggiorna i LED in base al valore binario del counter
  for (int i = 0; i < 3; i++) {
    digitalWrite(ledPins[i], (counter % (int)(pow(2, i+1)) >= (int)(pow(2, i))));
  }
}

void printCounter() {
  Serial.print("Decimale: ");
  Serial.print(counter);
  Serial.print(" | Binario: ");
 
  // Stampa la rappresentazione binaria
  for (int i = 2; i >= 0; i--) {
    Serial.print((counter / (int)pow(2, i)) % 2);
  }
  Serial.println();
}
