#include <DallasTemperature.h>

#include <OneWire.h>

#define SENSOR_PIN  4 // pino de entrada de dados do sensor de temperatura

OneWire oneWire(SENSOR_PIN); //instancia o objeto onewire
DallasTemperature DS18B20(&oneWire); //cria o objeto de temperatura

float tempC; // temperature in Celsius
float tempF; // temperature in Fahrenheit

void setup() {
  Serial.begin(9600); // initialize serial
  DS18B20.begin();    // initialize the DS18B20 sensor
}

void loop() {
  DS18B20.requestTemperatures();       // envia o comando requerindo a temperatura do sensor
  tempC = DS18B20.getTempCByIndex(0);  //leitura da temperatura em celsius
  tempF = tempC * 9 / 5 + 32; // conversão de celsius para fahrenheit

  Serial.print("Temperature: ");
  Serial.print(tempC);    // print the temperature in °C
  Serial.print("°C");
  Serial.print("  ~  ");  // separator between °C and °F
  Serial.print(tempF);    // print the temperature in °F
  Serial.println("°F");

  delay(1000);
}
