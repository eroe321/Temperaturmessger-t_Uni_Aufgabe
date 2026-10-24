#include <OneWire.h>
#include <DallasTemperature.h>

// Pins definieren
#define ONE_WIRE_BUS 2
//#define NTC_PIN A0

// Parameter
const float R1 = 3300.0;
const float BETA = 3950.0;
const float R0 = 3420.0;
const float T0 = 25.0 + 273.15;

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup() {
Serial.begin(9600);
sensors.begin();
}

void loop() {
// DS18B20 Temperatur auslesen
sensors.requestTemperatures();
float tempDS18B20 = sensors.getTempCByIndex(0);

// NTC Spannung
int adcWert = analogRead(A0);
float ausgangsU = (adcWert / 1023.0) * 5.0;

// NTC Widerstand
float R_NTC = R1 * ((5.0 / ausgangsU) - 1.0);

// NTC Widerstand in Temperatur umrechnen
float tempNTC = (1.0 / ((1.0 / T0) + (1.0 / BETA) * log(R_NTC / R0))) - 273.15;

// Ausgabe
Serial.print("DS18B20 Temp [°C]: ");
Serial.print(tempDS18B20);
Serial.print("\tNTC Temp [°C]: ");
Serial.print(tempNTC);
Serial.print("\tNTC Widerstand [Ohm]: ");
Serial.println(R_NTC);

delay(500);
}
