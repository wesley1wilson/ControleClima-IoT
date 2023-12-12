#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <DallasTemperature.h>
#include <OneWire.h>
#include <IRsend.h>
#include <WiFi.h>
#include <PubSubClient.h>

// Substitua com suas credenciais WiFi
const char* ssid = "brisa-829814";
const char* password = "4jsp2uf4";

// Substitua com os detalhes do seu broker MQTT
const char* mqttBroker = "broker.emqx.io";
const int mqttPort = 1883;
const char* mqttTopic = "RecebendoRafhael";


#define SENSOR_PIN  4 // pino de entrada de dados do sensor de temperatura

OneWire oneWire(SENSOR_PIN); //instancia o objeto onewire
DallasTemperature DS18B20(&oneWire); //cria o objeto de temperatura

float tempC; // temperature in Celsius



WiFiClient espClient; //instancia o objeto wifi cliente
PubSubClient client(espClient);


void setup() {
  // put your setup code here, to run once:
  // Conectar à rede WiFi
    Serial.begin(115200);  //inicia o monitor serial
    WiFi.begin(ssid, password); //inicia o wifi
    while (WiFi.status() != WL_CONNECTED) { //conexão ao wifi
      delay(250);
      Serial.println("Conectando ao WiFi...");
      }
      Serial.println("Conectado ao WiFi");

    // Configurar o cliente MQTT
    client.setServer(mqttBroker, mqttPort);
    DS18B20.begin();    // inicializa o sensor de temperatura DS18B20 
    


}


//função que envia temperatura para o servidor web
void sendTemperature(char temperaturaStr[10]) {
  
  client.publish(mqttTopic,temperaturaStr); //envia a temperatura pelo protocolo mqtt

  Serial.println("\nMensagem MQTT enviada");

}

void loop() {

    DS18B20.requestTemperatures();       // envia o comando requerindo a temperatura do sensor
    tempC = DS18B20.getTempCByIndex(0);  //leitura da temperatura em celsius  
    Serial.print("Temperature: ");
    Serial.print(tempC);    //mostra a temperatura em Celsius
    Serial.print("°C\n");

    //se não tiver conectado ao servidor, se reconectará
    if (!client.connected()) {
      reconnect();
    } 
    if (!isnan(tempC)) {

      // Converter a temperatura para uma string
      char temperaturaStr[10];
      //função de conversão de float para char
      dtostrf(tempC, 4, 2, temperaturaStr);

      // Enviar a temperatura via MQTT
      sendTemperature(temperaturaStr);
       delay(4000) ;
    } else {
      Serial.println("Falha na leitura da temperatura. Verifique a conexão do sensor.");
    }
   

}

void reconnect() {
  // Reconectar ao broker MQTT
  while (!client.connected()) {
    Serial.println("Tentando reconectar ao broker MQTT...");
    if (client.connect("ESP32Client")) {
      Serial.println("Reconectado ao broker MQTT");
    } else {
      Serial.println("Falha na reconexão. Tentando novamente");
    }
  }
}
