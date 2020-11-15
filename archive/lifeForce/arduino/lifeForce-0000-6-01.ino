/**
 * Testing digital reading between D4 and GND (ground) pins on board.
 *
 * References:
 *
 * How to Measure Voltage with a Digital Multimeter
 * https://www.youtube.com/watch?v=QQWy3_rE5JY
 *
 * Source:
 * Programming Ardunino: Getting Started with Sketches
 * Chapter 6 - Input and Output
 * p.85 - 89
 *
 * Sketch 6-01
 */
 
 int outPin = 4;
 
 void setup()
 {
   pinMode(outPin, OUTPUT);
   Serial.begin(9600);
   Serial.println("Enter 1 or 0");
 }
 
 void loop()
 {
   if (Serial.available() > 0)
   {
     char ch = Serial.read();
     if (ch == '1')
     {
       digitalWrite(outPin, HIGH);
     }
     else if (ch == '0')
     {
       digitalWrite(outPin, LOW);
     }
   }
 }
 