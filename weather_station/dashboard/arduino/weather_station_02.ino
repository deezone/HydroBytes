#include <Bridge.h>
#include <YunServer.h>
#include <YunClient.h> 

#include "DHT.h"
#define DHTPIN 2     // what pin we're connected to

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
  
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  
  // Read temperature as Celsius
  float c = dht.readTemperature();
  
  // Read temperature as Fahrenheit
  float f = dht.readTemperature(true);
  
  // Compute heat index
  // Must send in temp in Fahrenheit!
  float hi = dht.computeHeatIndex(f, h);

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
     if (request == "hum") {
      //client.print("<br>Current Humidity: ");
      client.print(h);
     }
     if (request == "hi") {
      //client.print("<br>Heat Index: ");
      client.print(hi);
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