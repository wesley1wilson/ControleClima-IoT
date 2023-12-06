#include <IRremoteESP8266.h>
#include <IRsend.h>
int a=12445; //código que será enviado 
int ledir=5; // pino do led IR transmissor

IRsend transmissor(ledir);  //instancia do objeto transmissor

void setup() {
  // put your setup code here, to run once:
  transmissor.begin(); // inicia o transmissor

  Serial.begin(115200);  //inicia o monitor serial

}

void loop() {
  // put your main code here, to run repeatedly:
  transmissor.sendNEC(a); //enviando  código infravermelho
  Serial.println(a); //mostrando o código enviando no monitor serial
  delay(2000); //atraso de 2 segundos entre cada envio
}
