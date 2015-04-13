# HydroBytes
A collection of projects using Internet of Things (IOT) technologies to manage hydroponic farming goals.

#### Weather Station
A standalone sensor platform for collecting readings related to the surrounding weather conditions.

##### Sensors
- **DHT11** : Humitity and temperature
  - Temperature range :0-50¡C error of ± 2¡C
  - Humidity :20-90% RH ± 5% RH error
  - Interface: Digital
- **LSR** : Light Sensitive Resistor, a type of variable resistor that responds to light.
  - Illumination range : 1 Lux to 6000 Lux
  - Interface: Analog
  
##### End Points
- **/arduino/tempc** : Temperature in Celsius (`$#176;C`), historically known as centigrade, is a scale and unit of measurement for temperature. It is named after the Swedish astronomer Anders Celsius (1701Ð1744),
  - http://en.wikipedia.org/wiki/Celsius
- **/arduino/tempf** : Temperature in Fahrenheit (`&#176;F`), a temperature scale based on one proposed in 1724 by the German physicist Daniel Gabriel Fahrenheit (1686Ð1736), after whom the scale is named. On Fahrenheit's original scale the lower defining point was the lowest temperature to which he could reproducibly cool brine (defining 0 degrees), while the highest was that of the average human core body temperature (defining 100 degrees).
  - http://en.wikipedia.org/wiki/Fahrenheit
- **/arduino/tempk** : Temperature in Kelvin (`&#176;K`), the fraction 1/273.16 of the thermodynamic temperature of the triple point of water (exactly 0.01 `&#176;C` or 32.018 `&#176;F`). An absolute, thermodynamic temperature scale using as its null point absolute zero, the temperature at which all thermal motion ceases in the classical description of thermodynamics.
  - http://en.wikipedia.org/wiki/Kelvin
- **/arduino/hum** : Humidity, the amount of water vapour in the air. Indicates the likelihood of precipitation.
  - http://en.wikipedia.org/wiki/Humidity
- **/arduino/hif** : Heat index (HI) in Fahrenheit : an index that combines air temperature and relative humidity in an attempt to determine the human-perceived equivalent temperature - "how hot does it feel?". 
  - http://en.wikipedia.org/wiki/Heat_index
- **/arduino/hic** : Heat index (HI) in Celsius
  - http://en.wikipedia.org/wiki/Heat_index
- **/arduino/dpc** : Dew Point : the temperature in Celsius (`$#176;C`) at which the water vapor in a sample of air at constant barometric pressure condenses into liquid water at the same rate at which it evaporates.
  - http://en.wikipedia.org/wiki/Dew_point
- **/arduino/dpf** : Dew Point in Fahrenheit (`&#176;F`).
- **/arduino/light** : Light intensity (lux), a measure of the intensity, as perceived by the human eye, of light that hits or passes through a surface.
  - http://en.wikipedia.org/wiki/Lux
- **/arduino/time** : Current system time, example `Sat Apr 11 00:07:08 EDT 2015`.
