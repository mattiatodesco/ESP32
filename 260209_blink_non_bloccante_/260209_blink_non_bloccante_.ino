// se collego il pin22 a massa, accende il LED esterno;
// se lascio il pin22 scollegato allora spengo il LED esterno
// nel frattempo il LED interno lampeggia in modo indipendente
// NB: in ESP32 il LED interno è sul pin 2
// NON uso delay per evitare di bloccare la lettura del pulsante

#define pinpulsante 22
#define ledinterno 2
#define ledesterno 5
#define durataimpulso 800  // periodo 1.6 secondi
  int lettura = 0;
  unsigned long postit1, trascorso;  
  
void setup() {
  Serial.begin(9600); // inizializzo la seriale
  pinMode(pinpulsante, INPUT_PULLUP);
  pinMode(ledinterno, OUTPUT);
  pinMode(ledesterno, OUTPUT);
  postit1 = millis(); // registra l'ora attuale
} // fine del setup

void loop() {  // inizio del loop
//  Serial.println("PREMI il pulsante per accendere il LED interno ");
  lettura = digitalRead(pinpulsante); // se è LOW allora P è premuto
  digitalWrite(ledesterno, !digitalRead(pinpulsante));// se P è premuto allora accendi ledesterno
   trascorso = millis()-postit1; // tempo trascorso dall'ultima commutazione
  if(trascorso>durataimpulso) { //inizio blocco if - sono passati 0.8 sec dall'ultima commutazione
       digitalWrite(ledinterno,!digitalRead(ledinterno)); // commuta lo stato del LED interno facendolo lampeggiare
       postit1 = millis(); // resetta il ritardo a 0.8 sec
      } //fine blocco if 
  } //fine del loop

  
