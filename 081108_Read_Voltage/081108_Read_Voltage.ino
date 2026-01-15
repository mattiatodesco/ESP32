/* 
  Lettura del valore di un potenziometro e visualizzazione della tensione corrispondente.
  Controllo della luminosità di un LED tramite PWM in base alla lettura del potenziometro.
*/

// Definizione di costanti
#define LED 5
#define POTENZIOMETRO 34
#define FREQ 1000
#define RES 8

void setup() {
  // Inizializzazione della comunicazione seriale
  Serial.begin(115200);
  // Configurazione del pin del LED come uscita PWM
  ledcAttach(LED, FREQ, RES);
  
}

void loop() {
  // Lettura e visualizzazione del valore dal potenziometro
  double read = analogRead(POTENZIOMETRO);
  Serial.print(read);
  Serial.print("  ");

  // Calcolo della percentuale e visualizzazione della tensione corrispondente
  double percent = read/4095;
  Serial.println(percent * 3.3);

  // Impostazione del valore PWM sul LED in base alla lettura del potenziometro
  ledcWrite(LED, percent * (2^RES));

  // Breve pausa prima della prossima lettura
  delay(50);
   
}
