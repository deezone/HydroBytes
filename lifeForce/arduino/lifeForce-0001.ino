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

int analogPin = A0;
int loopCount = 0;
int readingCount = 0;

void setup()
{
  Serial.begin(19200);
}

void loop()
{

  bool takeReading = takeReading(loopCount);
  loopCount++;
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
 * 
 */
boolean takeReading(int loopCount)
{
  boolean takeReading = false;
  // @todo: Make 5000 constant: 
  int countModulo = loopCount % 5000;
  if (countModulo == 0) {
    takeReading = true;
  }
  return takeReading;
}

/**
 * ledStatus()
 * 
 * @parm float voltage
 *   The current voltage reading from the probes in the plant. The voltage level
 *   from 0 - 5 indicates the amount the plant requires water. Different coloured
 *   LEDs will indicate the mosture level of the plant and need to water it.
 */
void ledStatus(float voltage) 
{

}

