/*
 * AquosTalk STANDALONE MODE
 */
#define PC0 9
#define PC1 10
#define PC2 11
#define PC3 12
#define IS_PLAY 8

void setup() {
  pinMode(IS_PLAY,INPUT) ;
  pinMode(PC0,OUTPUT) ;
  pinMode(PC1,OUTPUT) ;
  pinMode(PC2,OUTPUT) ;
  pinMode(PC3,OUTPUT) ;

  digitalWrite(PC0,LOW) ;
  digitalWrite(PC1,LOW) ;
  digitalWrite(PC2,LOW) ;
  digitalWrite(PC3,LOW) ;
}

void loop() {
  int sig0 , sig1 ,sig2 , sig3 ;
  for (int i= 0 ; i < 7 ; i++ ) {
    sig0 = (i & 0x01) ? HIGH : LOW ;
    sig1 = (i & 0x02) ? HIGH : LOW ;
    sig2 = (i & 0x04) ? HIGH : LOW ;
    sig3 = (i & 0x08) ? HIGH : LOW ;

    digitalWrite(PC0,sig0) ;
    digitalWrite(PC1,sig1) ;
    digitalWrite(PC2,sig2);
    digitalWrite(PC3,sig3) ;

    // ----- 発話終了待ち ---
    delay(100) ;
    while(digitalRead(IS_PLAY) == LOW) {
      delay(10) ;
    }
    delay(2000) ;
  }
}
