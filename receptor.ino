/* ========== RECEPTOR ===============
   Autor: Marlon Nardi Walendorff
   Data: 28/11/2020
   Projeto: Comunicação entre dois Arduinos sem fio utilizando módulos RF 433Mhz
*/
 
//==== Inclusão de bibliotecas ====//
#include <VirtualWire.h>             

//==== Mapemamento de Hardware e constantes =====//
#define pinLEDPot 11
#define pinLEDButton 9
#define IN1 3

 
//===== Variáveis globais ========//
byte message[VW_MAX_MESSAGE_LEN]; // Um buffer para armazenar as mensagens
byte messageLength = VW_MAX_MESSAGE_LEN; // Tamanho máximo das mensagens recebidas
int tensao = 0;
 
void setup()
{
  //Inicia comunicação serialcom velocidade de 9600 BPS
  Serial.begin(9600);
  
  //Entradas/Saídas digitais
  pinMode(pinLEDPot, OUTPUT);
  pinMode(pinLEDButton, OUTPUT);
  pinMode(IN1, OUTPUT);

  vw_set_rx_pin(2); //Seleciona o pino para recepção dos dados
  vw_setup(2000);   //Velocidade de comunicação em BPS
  vw_rx_start();    //Começa a receber os dados

  digitalWrite(IN1, HIGH);
  
}//endSetup
 
void loop()
{
  
  if (vw_get_message(message, &messageLength))// Se houver dados para receber
  {
 
    analogWrite(pinLEDPot, message[0]);// Controle PWM no pino pinLEDPot
 
    if (message[1] == 1)// Se o segundo byte do vetor message for igual a um...
    {
      //
      analogWrite(pinLEDButton, 0);// Desliga o LED no pino pinLEDButton
      tensao = 0;
    }
    else 
    {
      analogWrite(pinLEDButton, 255);// Liga o LED no pino pinLEDButton
      tensao = 255;
    }
    

    Serial.print("PWM: ");
    Serial.print(message[0]);
    Serial.print("   Button: ");
    Serial.println(tensao);

  }
 
}//endLoop