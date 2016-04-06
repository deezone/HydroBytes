/**
 * HydoBytes - LifeForce1000
 * 
 * Monitor a plants moisture level and provide alerts when the plant needs watering. 
 * 
 * The amount of voltage detected between two probes in the plant's soil indicates the moisture
 * level. Zero voltage detected indicates that there is zero conductivity and the plant needs
 * watering.
 * 
 * Analog Input - a value between 0 and 1023 depending on the voltage.
 * Voltage - reading * (5.0 / 1023.0)
 * 
 * The detected voltage is determined on intervals. It's not clear if exposure to low levels 
 * of voltage will effect the plant. The goal is to keep the exposure to a minimum and 
 * conserve power to allow the monitoring station to have minimum maintenance.
 */

// Translates to about 15 second intervals
#define sampleRate 50000

#define ledPinRed1 13
#define ledPinYellow3 12
#define ledPinYellow2 11
#define ledPinYellow1 10
#define ledPinGreen3 9
#define ledPinGreen2 8
#define ledPinGreen1 7

#define analogPin A0;

int loopCount = 0;
int readingCount = 0;

/*
 * setup()
 *  - serial communicaion rate
 *  - All of the OUTPUT pins
 */
void setup()
{
  Serial.begin(57600);

  // LEDs to indicate moisture reading
  pinMode(ledPinRed1, OUTPUT);
  pinMode(ledPinYellow3, OUTPUT);
  pinMode(ledPinYellow2, OUTPUT);
  pinMode(ledPinYellow1, OUTPUT);
  pinMode(ledPinGreen3, OUTPUT);
  pinMode(ledPinGreen2, OUTPUT);
  pinMode(ledPinGreen1, OUTPUT);
}

/*
 * Gather votage readings on an interval. Based on the detected voltage turn different
 * coloured LEDs on and off.
 */
void loop()
{

  // Flush all previous received and transmitted data.
  // Prevents serial connection errors when the monitor is already 
  // connected.
  Serial.flush();

  loopCount++;

  boolean takeReading = timeToRead(loopCount);
  if (takeReading) {
    readingCount++;
    Serial.print("Reading count: ");
    Serial.println(readingCount);
  
    int reading = analogRead(A0);
    Serial.print("Reading = ");
    Serial.println(reading);

    // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
    float voltage = reading * (5.0 / 1023.0);
    Serial.print("Voltage = ");
    Serial.println(voltage);

    // LED output based on mosture level based on voltage detected
    ledStatus(voltage);

    Serial.println();
    Serial.println("-----");
    Serial.println();
  }
}

/**
 * timeToRead() - Determine if it's time to take a reading.
 * 
 * @param int loopCount
 *   A counter to keep track of the number of times the loop() logic has 
 *   been performed.
 */
boolean timeToRead(int loopCount)
{
  boolean takeReading = false;

  // Take initial reading
  if (loopCount == 1) {
    takeReading = true;
  }

  int countModulus = loopCount % sampleRate;
  if (countModulus == 0) {
    takeReading = true;
  }
  return takeReading;
}

/**
 * ledStatus() - Manage the status of the LEDs, turn on or off depepending of the 
 * voltage reading.
 * 
 * @parm float voltage
 *   The current voltage reading from the probes in the plant. The voltage level
 *   from 0 - 5 indicates the amount the plant requires water. Different coloured
 *   LEDs will indicate the mosture level of the plant and need to water it.
 */
void ledStatus(float voltage) 
{

  // Status: Green - 1
  if (voltage > 1.0 && voltage <= 5.0)
  {
    digitalWrite(ledPinGreen1, HIGH);
    Serial.println("ledPinGreen1 = HIGH (ON)");

    // Turn off all the other LEDs
    digitalWrite(ledPinGreen2, LOW);
    digitalWrite(ledPinGreen3, LOW);

    digitalWrite(ledPinYellow1, LOW);
    digitalWrite(ledPinYellow2, LOW);
    digitalWrite(ledPinYellow3, LOW);

    digitalWrite(ledPinRed1, LOW);
  }

  // Status: Green - 2
  if (voltage > 0.5 && voltage <= 1.0)
  {
    digitalWrite(ledPinGreen2, HIGH);
    Serial.println("ledPinGreen2 = HIGH (ON)");

    // Turn off all the other LEDs
    digitalWrite(ledPinGreen1, LOW);
    digitalWrite(ledPinGreen3, LOW);

    digitalWrite(ledPinYellow1, LOW);
    digitalWrite(ledPinYellow2, LOW);
    digitalWrite(ledPinYellow3, LOW);

    digitalWrite(ledPinRed1, LOW);
  }

    // Status: Green - 3
  if (voltage > 0.2 && voltage <= 0.5)
  {
    digitalWrite(ledPinGreen3, HIGH);
    Serial.println("ledPinGreen3 = HIGH (ON)");

    // Turn off all the other LEDs
    digitalWrite(ledPinGreen1, LOW);
    digitalWrite(ledPinGreen2, LOW);

    digitalWrite(ledPinYellow1, LOW);
    digitalWrite(ledPinYellow2, LOW);
    digitalWrite(ledPinYellow3, LOW);

    digitalWrite(ledPinRed1, LOW);
  }

  // Status: Yellow - 1
  if (voltage > 0.15 && voltage <= 0.2)
  {
    digitalWrite(ledPinYellow1, HIGH);
    Serial.println("ledPinYellow1 = HIGH (ON)");

    // Turn off all the other LEDs
    digitalWrite(ledPinGreen1, LOW);
    digitalWrite(ledPinGreen2, LOW);
    digitalWrite(ledPinGreen3, LOW);

    digitalWrite(ledPinYellow2, LOW);
    digitalWrite(ledPinYellow3, LOW);

    digitalWrite(ledPinRed1, LOW);
  }

  // Status: Yellow - 2
  if (voltage > 0.115 && voltage <= 0.15)
  {
    digitalWrite(ledPinYellow2, HIGH);
    Serial.println("ledPinYellow2 = HIGH (ON)");

    // Turn off all the other LEDs
    digitalWrite(ledPinGreen1, LOW);
    digitalWrite(ledPinGreen2, LOW);
    digitalWrite(ledPinGreen3, LOW);

    digitalWrite(ledPinYellow1, LOW);
    digitalWrite(ledPinYellow3, LOW);

    digitalWrite(ledPinRed1, LOW);
  }

  // Status: Yellow - 3
  if (voltage > 0.075 && voltage <= 0.115)
  {
    digitalWrite(ledPinYellow3, HIGH);
    Serial.println("ledPinYellow3 = HIGH (ON)");

    // Turn off all the other LEDs
    digitalWrite(ledPinGreen1, LOW);
    digitalWrite(ledPinGreen2, LOW);
    digitalWrite(ledPinGreen3, LOW);

    digitalWrite(ledPinYellow1, LOW);
    digitalWrite(ledPinYellow2, LOW);

    digitalWrite(ledPinRed1, LOW);
  }

  // Status: Red
  if (voltage >= 0.0 && voltage <= 0.075)
  {
    digitalWrite(ledPinRed1, HIGH);
    Serial.println("ledPinRed1 = HIGH (ON)");

    // Turn off all the other LEDs
    digitalWrite(ledPinGreen1, LOW);
    digitalWrite(ledPinGreen2, LOW);
    digitalWrite(ledPinGreen3, LOW);

    digitalWrite(ledPinYellow1, LOW);
    digitalWrite(ledPinYellow2, LOW);
    digitalWrite(ledPinYellow3, LOW);
  }
}

