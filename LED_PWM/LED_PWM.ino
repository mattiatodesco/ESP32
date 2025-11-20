
// 17_11_2025 azionamento in PWM di un LED con ESP32

#define FREQ 1000  // frequenza dell'onda rettangolare
#define resolution 8  // risoluzione PWM
#define LEDPIN 5  // il LED è collegato sul GPIO5
#define BTNPIN 22 //Pin del bottone
int luminosità = 0; //Valore di luminosità del LED
bool incremento = true; //Variabile di controllo che indica un incremento o decremento


void setup() {
  //Configuro il monitor seriale
  Serial.begin(9600);
  //Configuro il bottone in pulldown
  pinMode(BTNPIN, INPUT_PULLDOWN);
  ledcAttach(LEDPIN,FREQ, resolution); //collega il canalePWM0 al GPIO 5  usare con le nuove librerie Espressif 3.0
}


void loop() {
  //Leggo il valore del bottone
  bool ValBtn = digitalRead(BTNPIN);
  // Controllo se il bottone è stato premuto
  if (ValBtn){
    //Aumento o diminuisco il valore della luminosità in base alla variabile di controllo
    if (incremento){
      luminosità += (pow(2, resolution)/4);
    } else {
      luminosità -= (pow(2, resolution)/4);
    }

    //Visualizzo il valore di luminosità sul monitor seriale
    Serial.println(luminosità);
    //Imposto il valore di luminosità nel LED
    ledcWrite(LEDPIN, luminosità);
    //Controllo se sono arrivato al valore massimo, e in caso inizio a decrementare
    if (luminosità == pow(2, resolution)){
      incremento = false;
      //Controllo se sono arrivato al valore minimo, e in caso inizio a incrementare
    } else if (luminosità == 0){
      incremento = true;
    }

    //Aspetto 200 ms per evitare una lettura multipla della pressione del pulsante
    delay(200);
  }
}
