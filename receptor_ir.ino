#include <IRremoteESP8266.h>
#include <IRrecv.h>

int led=13;
int receptorIR=4; //pino do receptor infravermelho
int sinal=0;  //variável que guardará os sinais recebidos

IRrecv irrecv(receptorIR); // instancia o objeto receptor


decode_results results; //variável que guardará os códgios infravermelhos

void setup() {
  // put your setup code here, to run once:

  pinMode(led,OUTPUT); //define o pino de saída do led que será aceso
  irrecv.enableIRIn(); //habilita a repector infravermelho
  Serial.begin(115200); //inicia o monitor serial
  digitalWrite(led,LOW); //inicia com led desligado
}

void loop() {
  // put your main code here, to run repeatedly:

  if(irrecv.decode(&results)){ // se um sinal IR for recebido

      sinal=results.value;
      if(sinal==16738455){ //sinal de entrada para desligar, que equivale ao número 0 no controle

          digitalWrite(led,LOW); //desligar led
          Serial.println(results.value); //mostre o sinal em hexadecimal
          delay(1000);//atrase 1 segundo
          irrecv.resume(); //finalize a entrada de sinal no receptor


      }

      else if(sinal==16724175){//sinal de entrada para ligar, que equivale ao número 1 no controle

          digitalWrite(led,HIGH); //liga led
          Serial.println(results.value); //mostre o sinal em hexadecimal
          delay(1000);//atrase 1 segundo
          irrecv.resume();//finalize a entrada de sinal no receptor
      
      }


      else{ //caso qaulquer outro número for recebido
        Serial.println(results.value); //mostre o sinal em hexadecimal
          delay(1000);
          irrecv.resume();

      }
      
  }
  

}
