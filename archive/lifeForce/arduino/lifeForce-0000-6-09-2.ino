/**
 * Testing analog reading of DC current between mosture sensors (galvanized nails).
 *
 * galvanized /ˈɡalvəˌnīz/: coat (iron or steel) with a protective layer of zinc
 *   - https://en.wikipedia.org/wiki/Galvanization
 *
 * Source:
 * Programming Ardunino: Getting Started with Sketches
 * p.102 - 103
 *
 * Analog inputs give a value between 0 and 1023 depending on the voltage at the
 * analog input pin.
 *
 * Sketch 6-09 displays the reading and actual voltage at the analog pin. A0 in
 * the Serial Monotor every half second, so open the Serial Monitor and watch the
 * readings appear.
 */
 
 int analogPin = 0;
 
 void setup()
 {
   Serial.begin(9600);
 }
 
 void loop()
 {
   int reading = analogRead(analogPin);
   float voltage = reading / 204.6;
   Serial.print("Reading=");
   Serial.print(reading);
   Serial.print("\t\tVolts=");
   Serial.print(ln(voltage);
   delay(500);
 }
 