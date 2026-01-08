 
void setup() {
  Serial.begin(115200);
}

void loop() {
  double read = analogRead(34);
   Serial.print(read);
   Serial.print("  ");
   double percent = read/4095;
   Serial.println(percent * 3.3);

   delay(500);
   
}

// See: https://github.com/espressif/arduino-esp32/blob/master/cores/esp32/esp32-hal-adc.h

