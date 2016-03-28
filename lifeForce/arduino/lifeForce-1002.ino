/**
   Analog Input - a value between 0 and 1023 depending on the voltage.

   Source:
   Programming Ardunino: Getting Started with Sketches
   Chapter 6 - Input and Output
   p.102 - 103

   Sketch 6-09

*/

int analogPin = A0;
int reading = 0;

void setup()
{
  Serial.begin(19200);
}

void loop()
{
  reading++;
  Serial.print("Reading count: ");
  Serial.println(reading);
  
  int reading = analogRead(A0);
  Serial.print("Reading = ");
  Serial.println(reading);

  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = reading * (5.0 / 1023.0);
  Serial.print("Voltage = ");
  Serial.println(voltage);

  Serial.println();
  Serial.println("-----");
  Serial.println();
  
  delay(2000);
}

