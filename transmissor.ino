#include <VirtualWire.h>
 
#define Size 2
#define pinButton 3
#define pinPot A0
#define led1 9
#define led2 8
#define led3 11
#define led4 12
#define led5 13
 
byte TX_buffer[2];
 
 
void setup()
{
  Serial.begin(9600);
  pinMode(pinButton, INPUT_PULLUP);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  
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

  if (TX_buffer[0] >= 0 && TX_buffer[0] < 51){
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
  }
  
  else if (TX_buffer[0] >= 51 && TX_buffer[0] < 102){
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
  }

  else if (TX_buffer[0] >= 102 && TX_buffer[0] < 153){
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
  }

  else if (TX_buffer[0] >= 153 && TX_buffer[0] < 204){
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
    digitalWrite(led5, LOW);
  }

  else if (TX_buffer[0] >= 204 && TX_buffer[0] < 255){
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
    digitalWrite(led5, HIGH);
  }

}//endLoop
