/**
 * AquesTalk picoのプリセットメッセージを書き込む
 */
#include <Wire.h>
#define I2CADDR 0x2E
#define BAUDRATE 9600
uint16_t wAddr ;
static char addrChar[] = "0123456789ABCDEF" ;

// #Wコマンドを連続発行
void SetMessageI2c(char *data) {
  for (int i=0; ; i++) {
    char cmd[9] ;
    cmd[0] = '#' ;
    cmd[1] = 'W' ;

    cmd[2] = addrChar[(wAddr & 0xF00)>>8] ;
    cmd[3] = addrChar[(wAddr & 0x0F0)>>4] ;
    cmd[4] = addrChar[wAddr & 0x00F] ;
    cmd[5] = addrChar[(data[i] & 0xF0)>>4] ;
    cmd[6] = addrChar[data[i] & 0x0F] ;
    cmd[7] = 0x0D ;
    cmd[8] = 0x00 ;

    sendI2cCommand(cmd) ;
    Serial.println(cmd) ;
    wAddr ++ ;
    if (data[i] == 0) break ;
  }
}

// I2C接続でコマンドを送信
 void sendI2cCommand(char *data) {
  int sendCount = 0 ;
  Wire.beginTransmission(I2CADDR);
  for (int i=0; data[i] != 0 ; i++) {
    Wire.write(data[i]);
    sendCount ++ ;
    if (sendCount >= 30) {
      sendCount = 0 ;
      Wire.endTransmission();
      Wire.beginTransmission(I2CADDR);
    }
  }
  Wire.write(0x0d);
  Wire.endTransmission();
  delay(10) ;

  // コマンドプロンプトを待つ
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
  sendI2cCommand("kakikomi/kaisi") ;

  wAddr = 0x040 ; // 書込み開始アドレス
  // 15個のメセージを連続書き込み
  SetMessageI2c("yuruku/tanosi'mu purogu'raminguto densiko'usaku") ;
  SetMessageI2c("hatuonnno/sann'puru/de'su") ;
  SetMessageI2c("wagahaiwa/neko/dea'ru") ;
  SetMessageI2c("namamu'gi/namago'me/namatama'go") ;
  SetMessageI2c("ohayo-") ;
  SetMessageI2c("ha'ro-?") ;
  SetMessageI2c("purisetto;me'sse-ji na'nba-/<NUMK VAL=6>.") ;
  SetMessageI2c("purisetto;me'sse-ji na'nba-/<NUMK VAL=7>.") ;
  SetMessageI2c("purisetto;me'sse-ji na'nba-/<NUMK VAL=8>.") ;
  SetMessageI2c("purisetto;me'sse-ji na'nba-/<NUMK VAL=9>.") ;
  SetMessageI2c("purisetto;me'sse-ji na'nba-/<NUMK VAL=10>.") ;
  SetMessageI2c("purisetto;me'sse-ji na'nba-/<NUMK VAL=11>.") ;
  SetMessageI2c("purisetto;me'sse-ji na'nba-/<NUMK VAL=12>.") ;
  SetMessageI2c("purisetto;me'sse-ji na'nba-/<NUMK VAL=13>.") ;
  SetMessageI2c("purisetto;me'sse-ji na'nba-/<NUMK VAL=14>.") ;

  Serial.println("DONE") ;
  sendI2cCommand("kakikomi/owari") ;
}

void loop() {
}
