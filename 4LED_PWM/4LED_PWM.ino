
// 17_11_2025 azionamento in PWM di un LED con ESP32

#define FREQ 1000  // frequenza dell'onda rettangolare
#define resolution 8  // risoluzione PWM
#define LED1 5  // il LED è collegato sul GPIO5
#define LED2 19  // il LED è collegato sul GPIO21
#define LED3 21 // il LED è collegato sul GPIO22
#define LED4 23  // il LED è collegato sul GPIO23
#define BTNPIN 22 //Pin del bottone
int luminosità = 0; //Valore di luminosità del LED
int passo = 4;
int leds[] = {5, 19, 21, 23};
int lunghezzaArray = sizeof(leds) / sizeof(leds[0]);


void setup() {
  //Configuro il monitor seriale
  Serial.begin(9600);
  //Configuro il bottone in pulldown
  pinMode(BTNPIN, INPUT_PULLDOWN);
  for (int i = 0; i < lunghezzaArray; i++){
    ledcAttach(leds[i],FREQ, resolution); //collega il canalePWM0 al GPIO 5  usare con le nuove librerie Espressif 3.0
  }
}

void loop() {
  //Leggo il valore del bottone
  bool ValBtn = digitalRead(BTNPIN);
  // Controllo se il bottone è stato premuto
  if (ValBtn){
    //Aumento il valore della luminosità in base alla variabile di controllo
    luminosità += (pow(2, resolution)/passo);
    if (luminosità == pow(2, resolution)){
      luminosità = luminosità -1;
    }

    int lum = 0;
    
    for (int i = 0; i < lunghezzaArray; i++){
      int diff = (pow(2, resolution)/passo) * i;
      Serial.println(diff);
    
      if (luminosità > diff){
        lum = luminosità - diff;
        if (lum == pow(2, resolution)){
          lum = lum -1;
        }
      } else {
        lum = pow(2, resolution) - (diff - lum);
        if (lum == pow(2, resolution)){
          lum = lum -1;
        }
      }
      Serial.println(lum);
      ledcWrite(leds[i], lum);
    }

    //Aspetto 200 ms per evitare una lettura multipla della pressione del pulsante
    delay(200);
  }
}
