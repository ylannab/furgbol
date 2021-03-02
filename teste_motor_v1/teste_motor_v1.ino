/**********
08/04/2018
teste com pwm na direção
pino da velocidade = 5v
valpwm<127 - gira em uma direção
valpwm>127 - gira em outra direção
valpwm=127 - aciona brake e para

FUNCIONAMENTO FORÇADO COM MUITO RUÍDO E AQUECIMENTO
**********/


int valPWM = 0;
int dir_m1 = 9;
int en_m1; // sempre em alta
int brake_m1 = 2;

void setup() {
  pinMode(dir_m1, OUTPUT);
  pinMode(en_m1, OUTPUT);
  pinMode(brake_m1, OUTPUT);
  digitalWrite (brake_m1, HIGH);
}

void loop() {
  //digitalWrite(en_m1, HIGH);

  while (valPWM <= 255) {
    if (valPWM == 127)
      digitalWrite (brake_m1, LOW);
    digitalWrite (brake_m1, HIGH);
    analogWrite(dir_m1, valPWM);
    delay(50);
    valPWM++;
  }
  while (valPWM > 0) {
    if (valPWM == 127)
      digitalWrite (brake_m1, LOW);
    digitalWrite (brake_m1, HIGH);
    valPWM--;
    analogWrite(dir_m1, valPWM);
    delay(50);
  }
}
