/*
 * Desenvolvedores: Felipe Lourenço e Paulo Henrique Munhoz
 */


/*
-------------------------------------------------------------------------------------------------------------------------------------

 * Principais Bibliotecas
 */
 
#include "dht.h"
#include <TimeLib.h>

/*
-------------------------------------------------------------------------------------------------------------------------------------

   Pinagem Analógica do Arduino 

*/

int pinogas = A0;                                              // Pino analógico utilizado pelo sensor de gás MQ-2
const int pinoDHT11 = A2;                                      // Pino analógico utilizado pelo sensor DHT11
const int pinoaltura = A3;                                     // Pino analógico utilizado pelo sensor de altura

/*

--------------------------------------------------------------------------------------------------------------------------------------

   Pinagem Digital do Arduino

*/

const int Aquecedor = 2;                                     // Pino Digital do atuador Aquecedor    -> Relé ativa em 0  
const int Dissipador = 4;                                    // Pino Digital do atuador Dissipador   -> Relé ativa em 0
const int Umidificador = 6;                                  // Pino Digital do atuador Umificador   -> Relé ativa em 0
const int Valvula = 8;                                       // Pino Digital do atuador Válvula      -> Relé ativa em 0
const int UV = 10;                                           // Pino Digital do atuador Lâmpada UV   -> Relé ativa em 0

/*

--------------------------------------------------------------------------------------------------------------------------------------


   Variáveis Globais

*/

int leitura_sensor = 300;                                      // Definingo um valor (nível de gás normal)
dht DHT;                                                       // variável do tipo DHT

/*

--------------------------------------------------------------------------------------------------------------------------------------


   Inicialização do SETUP do sistema

*/

void setup(){
  
  setTime(23,59,50,15,8,2020);                              
  pinMode(Aquecedor, OUTPUT);
  pinMode(Dissipador, OUTPUT);
  pinMode(Umidificador, OUTPUT);
  pinMode(Valvula,OUTPUT);
  pinMode(UV, OUTPUT);
  pinMode(pinogas, INPUT); 
  Serial.begin(9600); 
   
 
}

/*
 
---------------------------------------------------------------------------------------------------------------------------------------
 
  Loop 1

*/
void loop(){
    
  clock();  
  DHT.read11(pinoDHT11);                                         // Lê as informações do sensor DHT
  Serial.print("Umidade: ");                                  
  Serial.print(DHT.humidity);                                 
  Serial.print("%");                                              
  Serial.print(" / Temperatura: "); 
  Serial.print(DHT.temperature, 0);                         
  Serial.println("*C");                               
 
  
   if(DHT.temperature< 20.00 ){
    digitalWrite(Aquecedor, LOW);
     
  }

  if(DHT.temperature >25) { 
    digitalWrite(Aquecedor,HIGH);
    
  }

  if(DHT.temperature >=25 && DHT.temperature <20 ){
     digitalWrite(Aquecedor,LOW);
            
  }

   if(DHT.humidity< 70.00 ){
    digitalWrite(Umidificador, LOW);
    
  }

  if(DHT.humidity >90) { 
    digitalWrite(Umidificador,HIGH);
    
  }

  if(DHT.humidity >90 && DHT.humidity <70 ){
    digitalWrite(Umidificador,LOW);
    
  }
   int valor_analogico = analogRead(pinogas);                  //Variável recebe o valor analógico de pinogas
        if (valor_analogico > leitura_sensor){                 
           digitalWrite(Dissipador,LOW);
        }else{ 
           digitalWrite(Dissipador,HIGH);
 }


 int x = analogRead(pinoaltura);                               // Variável x recebe o valor analógicoaltura
  Serial.println(x);
  if(x > 500){                                                 // Se a altura for maior que 690 bits(PODE SER AJUSTADO)
      digitalWrite(Valvula, LOW); 
  }else{ 
    digitalWrite(Valvula, HIGH); 
  }

  delay(946);                                                 // valor conseguido por tentativa. 

}

/*

---------------------------------------------------------------------------------------------------------------------------------------
 
  Loop 2 para o relógio

*/
void loopforclock(){

   clock();

}


/*

--------------------------------------------------------------------------------------------------------------------------------------

  Procedimentos Essenciais
  
*/

void clock(){

    Serial.println();   
    Serial.print(hour());
    printDigits(minute());    
    printDigits(second());
    Serial.print(" ");
    Serial.print(day());
    Serial.print(" ");
    Serial.print(month());
    Serial.print(" ");
    Serial.print(year()); 
    Serial.println(); 
    if( hour()>=0 && hour()<=12){

      digitalWrite(UV,HIGH);
      
      }else{

        digitalWrite(UV,LOW);
        }
 }

void printDigits(int digits){
  
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
    Serial.print(digits);
}
