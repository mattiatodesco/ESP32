#define LED 5
#define TRIMMER 34
#define FREQ 1000
#define RES 8

void setup() {
  Serial.begin(115200);
  ledcAttach(LED, FREQ, RES);
  
}

void loop() {
  double read = analogRead(TRIMMER);
   Serial.print(read);
   Serial.print("  ");
   double percent = read/4095;
   Serial.println(percent * 3.3);

   ledcWrite(LED, percent * (2^RES));

   delay(50);
   
}
