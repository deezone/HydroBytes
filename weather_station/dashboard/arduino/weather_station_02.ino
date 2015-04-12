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
  float hif = dht.computeHeatIndex(f, h);
  float hic = fToC(hif);

  // How cold? (temperature and humidity with Arduino)
  // http://wodieskodie.com/how-cold-temperature-and-humidity-with-arduino/
  float dp = dewPoint(c, h);

  // get the time from the server:
  Process time;
  time.runShellCommand("date");
  String timeString = "";
  while (time.available()) {
    char c = time.read();
    timeString += c;
  }

  if (client) {

    // read the command
    String request  = client.readString();
    request.trim();   //kill whitespace

    if (request == "tempf") {
      remoteJSONHeaders();

      // JSON response
      client.print("{\"type\":\"temperature\",");
      client.print("\"scale\":\"fahrenheit\",");
      client.print("\"title\":\"Fahrenheit\",");
      client.print("\"value\":\"");
      client.print(f);
      client.print("\"}");
    }

    if (request == "tempc") {
      remoteJSONHeaders();

      // JSON response
      client.print("{\"type\":\"temperature\",");
      client.print("\"scale\":\"celsius\",");
      client.print("\"title\":\"Celsius\",");
      client.print("\"value\":\"");
      client.print(c);
      client.print("\"}");
    }

    if (request == "tempk") {
      remoteJSONHeaders();

      // JSON response
      client.print("{\"type\":\"temperature\",");
      client.print("\"scale\":\"kelvin\",");
      client.print("\"title\":\"Kelvin\",");
      client.print("\"value\":\"");
      client.print(k);
      client.print("\"}");
    }

    if (request == "hum") {
      remoteJSONHeaders();

      // JSON response
      client.print("{\"type\":\"humidity\",");
      client.print("\"scale\":\"percentage\",");
      client.print("\"title\":\"Humidity\",");
      client.print("\"value\":\"");
      client.print(h);
      client.print("\"}");
    }

    if (request == "hif") {
      remoteJSONHeaders();

      // JSON response
      client.print("{\"type\":\"index\",");
      client.print("\"scale\":\"Apparent Temperature (Heat Index) in Fahrenheit\",");
      client.print("\"title\":\"Heat Index\",");
      client.print("\"value\":\"");
      client.print(hif);
      client.print("\"}");
    }

    if (request == "hic") {
      remoteJSONHeaders();

      // JSON response
      client.print("{\"type\":\"index\",");
      client.print("\"scale\":\"temperature\",");
      client.print("\"title\":\"Heat Index\",");
      client.print("\"description\":\"Apparent Temperature (Heat Index) in Celsius\",");
      client.print("\"value\":\"");
      client.print(hic);
      client.print("\"}");
    }

    if (request == "dp") {
      remoteJSONHeaders();

      // JSON response
      client.print("{\"type\":\"index\",");
      client.print("\"scale\":\"temperature\",");
      client.print("\"title\":\"Dew Point\",");
      client.print("\"description\":\"At temperatures below the dew point, water will leave the air.\",");
      client.print("\"value\":\"");
      client.print(dp);
      client.print("\"}");
    }

    if (request == "light") {
      remoteJSONHeaders();

      // JSON response
      client.print("{\"type\":\"index\",");
      client.print("\"scale\":\"lux\",");
      client.print("\"title\":\"Light\",");
      client.print("\"description\":\"A measure of light intensity, as perceived by the human eye.\",");
      client.print("\"value\":\"");
      client.print(lsr);
      client.print("\"}");
    }

    if (request == "time") {
      remoteJSONHeaders();

      // JSON response
      client.print("{\"type\":\"time\",");
      client.print("\"scale\":\"time\",");
      client.print("\"title\":\"Time\",");
      client.print("\"description\":\"The current system time.\",");
      client.print("\"value\":\"");
      client.print(timeString);
      client.print("\"}");
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

// Fahrenheit to Celsius formula
// http://www.rapidtables.com/convert/temperature/how-fahrenheit-to-celsius.htm
// T(C) = (T(F) - 32) x 5/9
double fToC(double fahrenheit) {
  return ((fahrenheit - 32) * 5/9);
}

// Common JSON response headers to allow remote API calls
void remoteJSONHeaders() {
  YunClient client = server.accept();
  client.println("Status: 200");
  client.println("Content-type: application/json");
  client.println("Access-Control-Allow-Origin: *");
  client.println(); //mandatory blank line
}