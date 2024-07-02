/* ========== TRANSMISSOR ===============
   Autor: Marlon Nardi Walendorff
   Data: 28/11/2020
   Projeto: Comunicação entre dois Arduinos sem fio utilizando módulos RF 433Mhz
*/
 
//==== Inclusão de bibliotecas ====//
#include <VirtualWire.h>
 
//==== Mapemamento de Hardware e constantes =====//
#define Size 2
#define pinButton 3
#define pinPot A0
 
//===== Variáveis globais ========//
byte TX_buffer[2];
 
 
void setup()
{
  Serial.begin(9600);
  //Entradas/Saídas digitais
  pinMode(pinButton, INPUT_PULLUP);
  
  vw_set_tx_pin(2); //Seleciona o pino de comunicação do TX 
  vw_setup(2000); // Velocidade de comunicação em BPS
}//endSetup
 
void loop()
{
  TX_buffer[0] = map(analogRead(pinPot), 0, 1023, 0, 255);
 
  if (digitalRead(pinButton) == 1) 
  {
    TX_buffer[1] = 1;
  }
  else 
    {
    TX_buffer[1] = 0;
    }
 
  vw_send(TX_buffer, Size);
  vw_wait_tx();
  
  Serial.print("PWM: ");
    Serial.print(TX_buffer[0]);
    Serial.print("   Button: ");
    Serial.println(TX_buffer[1]);
  
}//endLoop