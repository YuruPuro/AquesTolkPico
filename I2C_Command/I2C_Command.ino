/**
 * AquesTalk pico にI2C接続でコマンドを送る
 */
#include <Wire.h>
#define I2CADDR 0x2E

// --- I2C コマンド送信 ---
void sendI2cCommand(char *data) {
  int sendCount = 0 ;
  Wire.beginTransmission(I2CADDR);
  for (int i=0; data[i] != 0 ; i++) {
    Wire.write(data[i]);
    sendCount ++ ;
    if (sendCount >= 30) {  // 30Byte毎に区切る
      sendCount = 0 ;
      Wire.endTransmission();
      Wire.beginTransmission(I2CADDR);
    }
  }
  Wire.write(0x0d);
  Wire.endTransmission();
  delay(10) ;

  // -- 発話の終了を待つ
  Wire.requestFrom(I2CADDR, 1);
  while (Wire.available() > 0) {
    char rep = Wire.read();
    Serial.println(rep) ;
    if (rep != '>') {
      Wire.requestFrom(I2CADDR, 1);
    } else {
      break ;
    }
  }
}

void setup() {
  Wire.begin();
}

void loop() {
  // 発音データ送信
  sendI2cCommand("yuruku/tanosi'mu purogu'raminguto densiko'usaku") ;
  delay(2000) ;
  sendI2cCommand("hatuonnno/sann'puru/de'su") ;
  delay(2000) ;
  sendI2cCommand("wagahaiwa/neko/dea'ru") ;
  delay(2000) ;
  sendI2cCommand("namamu'gi/namago'me/namatama'go") ;
  delay(2000) ;
  sendI2cCommand("ohayo-") ;
  delay(2000) ;
  sendI2cCommand("ha'ro-?") ;
  delay(2000) ;
}
