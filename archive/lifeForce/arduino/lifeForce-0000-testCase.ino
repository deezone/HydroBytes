/*  Soil Moisture measurement v0.1 20091017
 Simple circuit
 Not calibrated at this moment
 
 Started by Mike Rice, October 14, 2009
 Modified by M.A. de Pablo, October 17, 2009
 
Circuit:
 To connect two nails and a 10 KOhms resistor as shown:
 
        digital 2---*
                  |
                  \
                  /
                  \ R1
                  /
                  |
                  |
        analog 0----*
                  |
                  |
                  *----> nail 1
                 
                  *----> nail 2
                  |
                  |
                  |
        digital 3---*
 */


#define moisture_input 0
#define divider_top 2
#define divider_bottom 3

// analogical value obtained from the experiment
int moisture;

int SoilMoisture(){

  int reading;
  
  // set driver pins to outputs
  pinMode(divider_top,OUTPUT);
  pinMode(divider_bottom,OUTPUT);

  // drive a current through the divider in one direction
  digitalWrite(divider_top,LOW);
  digitalWrite(divider_bottom,HIGH);

  // wait a moment for capacitance effects to settle
  delay(1000);

  // take a reading
  reading=analogRead(moisture_input);

  // reverse the current
  digitalWrite(divider_top,HIGH);
  digitalWrite(divider_bottom,LOW);

  // give as much time in 'reverse' as in 'forward'
  delay(1000);

  // stop the current
  digitalWrite(divider_bottom,LOW);

  return reading;
}

void setup () {
  Serial.begin(9600);
}

void loop (void) {

  // assign the result of SoilMoisture() to the global variable 'moisture'
  moisture=SoilMoisture();
  Serial.print("Soil moisture: ");
  
  // print the analogical measurement of the experiment
  Serial.print(moisture);
  
  // later i will improve here a calculation for derive Soil Moisture in %
  Serial.println();
  delay(1000);
  
}