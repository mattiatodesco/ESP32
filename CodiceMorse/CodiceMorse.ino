int spazioParole = 1800;

String lettere[26]  = {
  ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."};


void punto (){
  digitalWrite(2, HIGH);
  delay(300);
  digitalWrite(2, LOW);
  delay(1000);
}

void linea (){  
  digitalWrite(2, HIGH);
  delay(1000);
  digitalWrite(2, LOW);
  delay(1000);
}

void setup() {
  Serial.begin(9600);
  Serial.println("Test");
  pinMode(2, OUTPUT); 
}

void loop() {
  String parola = "parola";
  parola.toUpperCase();

  for (int j = 0; j < parola.length(); j++){
   char car = parola[j];
   int valAscii = (int)car -65;
    String carattere = lettere[valAscii];
    for (int i = 0; i < carattere.length(); i++){
      char segno = carattere.charAt(i);
      if (segno == '.') {
        punto();
      } else if (segno == '-') {
        linea();    
      } else{
      }
    }
    Serial.println(car);
  }
}
