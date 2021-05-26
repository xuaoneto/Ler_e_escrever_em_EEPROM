/*
 ** CS - pin 10
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
*/
#include <SPI.h>

const int CS = 15;

uint8_t readByteAt(uint8_t cs,uint16_t adr){
  SPI.beginTransaction(SPISettings(4000000,MSBFIRST,SPI_MODE0));
  digitalWrite(cs, LOW);
  uint8_t b = highByte(adr);
  b = b <<3;
  b = b | 0x03;
  SPI.transfer(b);
  SPI.transfer(lowByte(adr));
  b = SPI.transfer(0);
  digitalWrite(cs, HIGH);
  SPI.endTransaction();
  return b;
}




void setup() {
  // Começa o monitor Serial
  Serial.begin(19200);
  // Estabelece o pino CS como Saída
  pinMode(CS, OUTPUT);
  // Começa o SPI:
  SPI.begin();
  // Coloca o pino CS como nível alto para evitar escritas na memoria
  digitalWrite(CS, HIGH);
  
}

void loop() {
  char ch[30];
  for (uint16_t i = 0; i < 256; i++){
    if((i&15) == 0){
      sprintf(ch, "\n0x%03X: ",i);
      Serial.print(ch);
    }
  sprintf(ch," 0x%02X:",readByteAt(CS, i));
  Serial.print(ch);  
  }
  delay(5000);
}



void EscreverByte(int address, int value) {
  // Começa a comunicação com a memoria colocando CS em nível baixo
  digitalWrite(CS, LOW);
  delay(100);
  //  send in the address and value via SPI:
  SPI.transfer(address);
  SPI.transfer(value);
  delay(100);
  // take the SS pin high to de-select the chip:
  digitalWrite(CS, HIGH);
}
