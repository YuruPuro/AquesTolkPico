/**
 * AquesTalk picoにSPI接続でコマンドを送る
 */
#include <SPI.h>
#define CS     10   // Slave Select(Chip select)

// TALK DATA 送信
void sendSpiCommand(char *data) {
  digitalWrite(CS, LOW); // セレクト
  for (int i=0; data[i] != 0 ; i++) {
    uint8_t d1 = data[i] ;
    SPI.transfer(d1);
    delay(1) ;
  }
  SPI.transfer(0x0D);

  // --- 発話の終了待ち
  char rep = 0 ;
  while (rep != '>') {
    delay(10) ;
    rep = SPI.transfer(0xFF);
  }
}

void setup() {
  SPI.begin();//SPIを初期化
  SPI.setDataMode(SPI_MODE3);
  SPI.setBitOrder(MSBFIRST);
  SPI.setClockDivider(SPI_CLOCK_DIV16);

  pinMode(CS, OUTPUT);   // Sleva Select
  digitalWrite(CS, HIGH);  // 解放
}

void loop() {
  // 発音データ送信
  sendSpiCommand("yuruku/tanosi'mu purogu'raminguto densiko'usaku") ;
  delay(2000) ;
  sendSpiCommand("hatuonnno/sann'puru/de'su") ;
  delay(2000) ;
  sendSpiCommand("wagahaiwa/neko/dea'ru") ;
  delay(2000) ;
  sendSpiCommand("namamu'gi/namago'me/namatama'go") ;
  delay(2000) ;
  sendSpiCommand("ohayo-") ;
  delay(2000) ;
  sendSpiCommand("ha'ro-?") ;
  delay(2000) ;
}
