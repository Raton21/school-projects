#include <Adafruit_BMP085.h>
Adafruit_BMP085 bmp;

#include "DHT.h"

#define DHTPIN D4
#define DHTTYPE DHT11
#define BTNPIN D3
DHT dht(DHTPIN, DHTTYPE);
bool BTNstate = 0;
float tempAvrgD = 0; //avrg temp from DHT
float tempAvrgB = 0; //avrg temp from BMP
float humidityAvrg = 0; 
float pressureAvrg = 0;

ICACHE_RAM_ATTR void BTN()
{
  BTNstate = 1;
}


void setup() {
  Serial.begin(9600);
  if (!bmp.begin()) {
  Serial.println("Could not find a valid BMP085 sensor, check wiring!");
  while (1) {}
  }
  dht.begin();
pinMode(BTNPIN, INPUT_PULLUP);
attachInterrupt(digitalPinToInterrupt(BTNPIN), BTN, FALLING);
}

void loop() {
  if(BTNstate==1)
  {
    for(int i =1;i<=3;i++)  // counting loop
    {
     tempAvrgD += dht.readTemperature(); 
     tempAvrgB += bmp.readTemperature(); 
     humidityAvrg += dht.readHumidity(); 
     pressureAvrg += bmp.readPressure();
     Serial.print("reading number");
     Serial.println(i);
     delay(1000);
    }
     Serial.print("avrage temperature from DHT: ");
     Serial.println(tempAvrgD/3);
     Serial.print("avrage temperature from BMP: ");
     Serial.println(tempAvrgB/3);
     Serial.print("avrage humidity from DHT: ");
     Serial.println(humidityAvrg);
     Serial.print("avrage pressure from BMP: ");
     Serial.println(pressureAvrg) ;

    tempAvrgD = 0;
    tempAvrgB = 0;
    humidityAvrg = 0;
    pressureAvrg = 0;
    BTNstate = 0;
  }










/*
  
  delay(200);
  //DHT:
  Serial.println("DHT sensor");

  
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);

 
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  \nTemperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  \nHeat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F\n"));

  //BMP:
  Serial.println("BMP sensor");
  Serial.print("Temperature = ");
    Serial.print(bmp.readTemperature());
    Serial.println(" *C");
   
    Serial.print("Pressure = ");
    Serial.print(bmp.readPressure());
    Serial.println(" Pa");
     
    // Calculate altitude assuming 'standard' barometric
    // pressure of 1013.25 millibar = 101325 Pascal
    Serial.print("Altitude = ");
    Serial.print(bmp.readAltitude());
    Serial.println(" meters");

    Serial.print("Pressure at sealevel (calculated) = ");
    Serial.print(bmp.readSealevelPressure());
    Serial.println(" Pa");

  // you can get a more precise measurement of altitude
  // if you know the current sea level pressure which will
  // vary with weather and such. If it is 1015 millibars
  // that is equal to 101500 Pascals.
    Serial.print("Real altitude = ");
    Serial.print(bmp.readAltitude(101325));
    Serial.println(" meters");
    
    Serial.println();

    */
}
