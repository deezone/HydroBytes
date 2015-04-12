#include <Bridge.h>
#include <YunServer.h>
#include <YunClient.h> 

#include "DHT.h"

#define DHTPIN 2     // what pin we're connected to
int analogPin = A0;

#define DHTTYPE DHT11   // DHT 11 

// Connect pin 1 (on the left) of the sensor to +3.3V
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

DHT dht(DHTPIN, DHTTYPE);

YunServer server;

void setup() {
  Bridge.begin();
  server.begin();
  
  dht.begin();
}

void loop() {
  YunClient client = server.accept();

  // Light sensor
  int lsr = analogRead(analogPin);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();

  // Read temperature as Celsius
  float c = dht.readTemperature();

  // Read temperature as Celsius
  float k = c + 273.15;

  // Read temperature as Fahrenheit
  float f = dht.readTemperature(true);

  // Compute heat index
  // Must send in temp in Fahrenheit!
  float hi = dht.computeHeatIndex(f, h);

  // How cold? (temperature and humidity with Arduino)
  // http://wodieskodie.com/how-cold-temperature-and-humidity-with-arduino/
  float dp = dewPoint(c, h);

  if (client) {
    // read the command
    String request  = client.readString();
    request.trim();   //kill whitespace
     if (request == "tempf") {
      //client.print("<br>Current Temperature: ");
      client.print(f);
      //client.print(" degrees F");
     }
     if (request == "tempc") {
      //client.print("<br>Current Temperature: ");
      client.print(c);
      //client.print(" degrees C");
     }
     if (request == "tempk") {
      //client.print("<br>Current Temperature: ");
      client.print(k);
      //client.print(" degrees K");
     }
     if (request == "hum") {
      //client.print("<br>Current Humidity: ");
      client.print(h);
     }
     if (request == "hi") {
      //client.print("<br>Heat Index: ");
      client.print(hi);
     }
     if (request == "dp") {
      //client.print("<br>Dew Point: ");
      client.print(dp);
     }
     if (request == "light") {
      //client.print("<br>Light: ");
      client.print(lsr);
     }
     if (request == "time") {
      // get the time from the server:
      Process time;
      time.runShellCommand("date");
      String timeString = "";
      while (time.available()) {
        char c = time.read();
        timeString += c;
      }
      client.print(timeString);
      }
    client.stop();
  }
  delay(50);
}

// ****************
// Declare User-written Functions
// ****************

// dewPoint function NOAA
// reference: http://wahiduddin.net/calc/density_algorithms.htm
double dewPoint(double celsius, double humidity) {

  double A0= 373.15/(273.15 + celsius);
  double SUM = -7.90298 * (A0-1);
  SUM += 5.02808 * log10(A0);
  SUM += -1.3816e-7 * (pow(10, (11.344*(1-1/A0)))-1) ;
  SUM += 8.1328e-3 * (pow(10,(-3.49149*(A0-1)))-1) ;
  SUM += log10(1013.246);
  double VP = pow(10, SUM-3) * humidity;
  double T = log(VP/0.61078); // temp var

  return (241.88 * T) / (17.558-T);
}