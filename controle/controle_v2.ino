#include "pwm01.h" //Colocar pasta da biblioteca na mesma pasta do código
#include <DueTimer.h>      //Biblioteca relacionada a função de tempo. 
uint32_t  pwm_freq1 = 20000;  //Frequencia do PWM

//--------------------------------     Motor 1      --------------------------------------------
#define dir_m1 7           //Esse pino recebe o pwm, de 0 a 127 é um sentido de 127 à 255 é outro. 
#define hall_1_m1 11
#define hall_2_m1 12
#define en_m1 10
//#define hall_3_m1 26
int A_m1 = 0, B_m1 = 0, counter_m1 = 0;
//--------------------------------     Motor 2      --------------------------------------------
#define dir_m2 9           //Esse pino recebe o pwm, de 0 a 127 é um sentido de 127 à 255 é outro. 
#define hall_1_m2 A1
#define hall_2_m2 A0
#define en_m2 A3
//#define hall_3_m2 27
int A_m2 = 0, B_m2 = 0, counter_m2 = 0;
//--------------------------------     Motor 3      --------------------------------------------
#define dir_m3 8           //Esse pino recebe o pwm, de 0 a 127 é um sentido de 127 à 255 é outro. 
#define hall_1_m3 A5
#define hall_2_m3 A6
#define en_m3 A4
//#define hall_3_m2 27
int A_m3 = 0, B_m3 = 0, counter_m3 = 0;
//--------------------------------     Motor 4      --------------------------------------------
#define dir_m4 6           //Esse pino recebe o pwm, de 0 a 127 é um sentido de 127 à 255 é outro. 
#define hall_1_m4 4
#define hall_2_m4 3
#define en_m4 24
//#define hall_3_m2 27
int A_m4 = 0, B_m4 = 0, counter_m4 = 0;

//::::::::::::::::::::::::::::::Variaveis do filtro ::::::::::::::::::::::::::::::::::::::::::::
float wc = 10, ts = 0.01;                  //tempo de amostragem
int PPR = 8;                       //X canais de encoder: PPR = 8*X (rising) ou 16*X (change);
//--------------------------------     Motor 1      --------------------------------------------
float x1_m1 = 0, x1p_m1 = 0, x2_m1 = 0, x2p_m1 = 0, theta_m1 = 0, x2rpm_m1 = 0;
//--------------------------------     Motor 2      --------------------------------------------
float x1_m2 = 0, x1p_m2 = 0, x2_m2 = 0, x2p_m2 = 0, theta_m2 = 0, x2rpm_m2 = 0;
//--------------------------------     Motor 3      --------------------------------------------
float x1_m3 = 0, x1p_m3 = 0, x2_m3 = 0, x2p_m3 = 0, theta_m3 = 0, x2rpm_m3 = 0;
//--------------------------------     Motor 4      --------------------------------------------
float x1_m4 = 0, x1p_m4 = 0, x2_m4 = 0, x2p_m4 = 0, theta_m4 = 0, x2rpm_m4 = 0;
//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

//::::::::::::::::::::::Variaveis do controle :::::::::::::::::::::::::::::::::::::::::::::::::::
float k, i;
float KP = 0.00103, KI = 0.161;//KP = 2 e KI = 260 por ziggler-nichols [MELHORES GANHOS]// VINDO DO CALCULO::: KP = 0.00103 KI = 0.161;
//--------------------------------     Motor 1      --------------------------------------------
float erro_atual_m1, erro_ant_m1 = 0, va_m1, va_ant_m1 = 0;
int pwm_m1 = 127;
int ref_m1 = 3000;  // esse 
//--------------------------------     Motor 2      --------------------------------------------
float erro_atual_m2, erro_ant_m2 = 0, va_m2, va_ant_m2 = 0;
int pwm_m2 = 127;
int ref_m2 = 3600;  // esse 
//--------------------------------     Motor 3      --------------------------------------------
float erro_atual_m3, erro_ant_m3 = 0, va_m3, va_ant_m3 = 0;
int pwm_m3 = 127;
int ref_m3 = 3600;  // esse 
//--------------------------------     Motor 3      --------------------------------------------
float erro_atual_m4, erro_ant_m4 = 0, va_m4, va_ant_m4 = 0;
int pwm_m4 = 127;
int ref_m4 = 3600; // esse 
//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

void filtro_SVF_m1() {
  theta_m1 = counter_m1 * (2 * PI / PPR);   //Conversão de pulsos para radianos.
  //Equações do filtro discretizado através do método de Euler.
  x1p_m1 = x1_m1 + x2_m1 * ts;
  x2p_m1 = (theta_m1 * wc * wc - 2 * wc * x2_m1 - wc * wc * x1_m1) * ts + x2_m1;
  x2_m1 = x2p_m1;   //velocdade angular medido em rad/s
  x1_m1 = x1p_m1; 
  x2rpm_m1 = x2_m1 * (60 / (2 * PI));   //velocidade angular medido em rpm
                                  //Conversão: rad/s -> 9,55 * rpm
}

void filtro_SVF_m2() {
  theta_m2 = counter_m2 * (2 * PI / PPR);   //Conversão de pulsos para radianos.
  //Equações do filtro discretizado através do método de Euler.
  x1p_m2 = x1_m2 + x2_m2 * ts;
  x2p_m2 = (theta_m2 * wc * wc - 2 * wc * x2_m2 - wc * wc * x1_m2) * ts + x2_m2;
  x2_m2 = x2p_m2;   //velocdade angular medido em rad/s
  x1_m2 = x1p_m2; 
  x2rpm_m2 = x2_m2 * (60 / (2 * PI));   //velocidade angular medido em rpm
                                  //Conversão: rad/s -> 9,55 * rpm
}

void filtro_SVF_m3() {
  theta_m3 = counter_m3 * (2 * PI / PPR);   //Conversão de pulsos para radianos.
  //Equações do filtro discretizado através do método de Euler.
  x1p_m3 = x1_m3 + x2_m3 * ts;
  x2p_m3 = (theta_m3 * wc * wc - 2 * wc * x2_m3 - wc * wc * x1_m3) * ts + x2_m3;
  x2_m3 = x2p_m3;   //velocdade angular medido em rad/s
  x1_m3 = x1p_m3; 
  x2rpm_m3 = x2_m3 * (60 / (2 * PI));   //velocidade angular medido em rpm
                                  //Conversão: rad/s -> 9,55 * rpm
}

void filtro_SVF_m4() {
  theta_m4 = counter_m4 * (2 * PI / PPR);   //Conversão de pulsos para radianos.
  //Equações do filtro discretizado através do método de Euler.
  x1p_m4 = x1_m4 + x2_m4 * ts;
  x2p_m4 = (theta_m4 * wc * wc - 2 * wc * x2_m4 - wc * wc * x1_m4) * ts + x2_m4;
  x2_m4 = x2p_m4;   //velocdade angular medido em rad/s
  x1_m4 = x1p_m4; 
  x2rpm_m4 = x2_m4 * (60 / (2 * PI));   //velocidade angular medido em rpm
                                  //Conversão: rad/s -> 9,55 * rpm
}

void interrupt_hall_1_m1() {   //funcao chamada a caada pulso de subida do hall_1
  B_m1 = digitalRead (hall_2_m1);

  if (B_m1 == LOW) {  //contador que define o sentido de rotacao
    counter_m1 ++;
  } else {
    counter_m1 --;
  }
  if (counter_m1 > PPR)  {
    counter_m1 = 0;
    x1_m1 = x1p_m1 - 2 * PI;
  }

  if ( counter_m1 < -PPR)  {
    counter_m1 = 0;
    x1_m1 = x1p_m1 + 2 * PI;
  }
}

void interrupt_hall_1_m2() {   //funcao chamada a caada pulso de subida do hall_1
  B_m2 = digitalRead (hall_2_m2);

  if (B_m2 == LOW) {  //contador que define o sentido de rotacao
    counter_m2 ++;
  } else {
    counter_m2 --;
  }
  if (counter_m2 > PPR)  {
    counter_m2 = 0;
    x1_m2 = x1p_m2 - 2 * PI;
  }

  if ( counter_m2 < -PPR)  {
    counter_m2 = 0;
    x1_m2 = x1p_m2 + 2 * PI;
  }
}

void interrupt_hall_1_m3() {   //funcao chamada a caada pulso de subida do hall_1
  B_m3 = digitalRead (hall_2_m3);

  if (B_m3 == LOW) {  //contador que define o sentido de rotacao
    counter_m3 ++;
  } else {
    counter_m3 --;
  }
  if (counter_m3 > PPR)  {
    counter_m3 = 0;
    x1_m3 = x1p_m3 - 2 * PI;
  }

  if ( counter_m3 < -PPR)  {
    counter_m3 = 0;
    x1_m3 = x1p_m3 + 2 * PI;
  }
}

void interrupt_hall_1_m4() {   //funcao chamada a caada pulso de subida do hall_1
  B_m4 = digitalRead (hall_2_m4);

  if (B_m4 == LOW) {  //contador que define o sentido de rotacao
    counter_m4 ++;
  } else {
    counter_m4 --;
  }
  if (counter_m4 > PPR)  {
    counter_m4 = 0;
    x1_m4 = x1p_m4 - 2 * PI;
  }

  if ( counter_m4 < -PPR)  {
    counter_m4 = 0;
    x1_m4 = x1p_m4 + 2 * PI;
  }
}


/*void interrupt_hall_2() {   //nao usado ainda
  A_m1 = digitalRead (hall_1);

  if (A_m1 == LOW ) {   //contador que define o sentido de rotacao
    counter --;
  } else {
    counter ++;
  }
  zerar_rotacao();  //funcao que verifica uma revolucao e angulo
}*/

void malhafechada_m1(float referencia) {

  erro_atual_m1= referencia - x2rpm_m1;                 // se referencia for em rpm, usar x2rpm
  k = KP * erro_atual_m1;                          //equações referentes ao controle
  i = (KI * ts - KP) * erro_ant_m1;
  va_m1 = va_ant_m1 + k + i;

  if (va_m1 > 3600)         //saturador adaptado para equacao de conversao para pwm
    va_m1 = 3600;

  if (va_m1 < -3600)
    va_m1 = -3600;

  pwm_m1 = 127 + (va_m1 / 3600) * 127;//equacao de conversao para pwm

  va_ant_m1 = va_m1;
  erro_ant_m1 = erro_atual_m1;
}

void malhafechada_m2(float referencia) {

  erro_atual_m2= referencia - x2rpm_m2;                 // se referencia for em rpm, usar x2rpm
  k = KP * erro_atual_m2;                          //equações referentes ao controle
  i = (KI * ts - KP) * erro_ant_m2;
  va_m2 = va_ant_m2 + k + i;

  if (va_m2 > 3600)         //saturador adaptado para equacao de conversao para pwm
    va_m2 = 3600;

  if (va_m2 < -3600)
    va_m2 = -3600;

  pwm_m2 = 127 + (va_m2 / 3600) * 127;//equacao de conversao para pwm

  va_ant_m2 = va_m2;
  erro_ant_m2 = erro_atual_m2;
}

void malhafechada_m3(float referencia) {

  erro_atual_m3= referencia - x2rpm_m3;                 // se referencia for em rpm, usar x2rpm
  k = KP * erro_atual_m3;                          //equações referentes ao controle
  i = (KI * ts - KP) * erro_ant_m3;
  va_m3 = va_ant_m3 + k + i;

  if (va_m3 > 3600)         //saturador adaptado para equacao de conversao para pwm
    va_m3 = 3600;

  if (va_m3 < -3600)
    va_m3 = -3600;

  pwm_m3 = 127 + (va_m3 / 3600) * 127;//equacao de conversao para pwm

  va_ant_m3 = va_m3;
  erro_ant_m3 = erro_atual_m3;
}

void malhafechada_m4(float referencia) {

  erro_atual_m4= referencia - x2rpm_m4;                 // se referencia for em rpm, usar x2rpm
  k = KP * erro_atual_m4;                          //equações referentes ao controle
  i = (KI * ts - KP) * erro_ant_m4;
  va_m4 = va_ant_m4 + k + i;

  if (va_m4 > 3600)         //saturador adaptado para equacao de conversao para pwm
    va_m4 = 3600;

  if (va_m4 < -3600)
    va_m4 = -3600;

  pwm_m4 = 127 + (va_m4 / 3600) * 127;//equacao de conversao para pwm

  va_ant_m4 = va_m4;
  erro_ant_m4 = erro_atual_m4;
}

void interrupt_tempo() {                    //Essa interrupção é chamada na frequência atribuída a ela, dentro da função void setup().
  filtro_SVF_m1();                            //Chamada do filtro responsável pela transformação de pulsos em posição e velocidade angular.
  filtro_SVF_m2();                            //Chamada do filtro responsável pela transformação de pulsos em posição e velocidade angular.
  filtro_SVF_m3();                            //Chamada do filtro responsável pela transformação de pulsos em posição e velocidade angular.
  filtro_SVF_m4();                            //Chamada do filtro responsável pela transformação de pulsos em posição e velocidade angular.
  malhafechada_m1(ref_m1);                       //Chamada da função responsável pela malha fechada de controle. Como parâmetro recebe o valor desejada de velocidadde em rpm.
  malhafechada_m2(ref_m2);                       //Chamada da função responsável pela malha fechada de controle. Como parâmetro recebe o valor desejada de velocidadde em rpm.
  malhafechada_m2(ref_m3);                       //Chamada da função responsável pela malha fechada de controle. Como parâmetro recebe o valor desejada de velocidadde em rpm.
  malhafechada_m2(ref_m4);                       //Chamada da função responsável pela malha fechada de controle. Como parâmetro recebe o valor desejada de velocidadde em rpm.

}

void setup() {
  pwm_setup(dir_m1, pwm_freq1, 1);                                     //Escolhe a freq em um pino especifico. Não alterar o 1.
  pwm_setup(dir_m2, pwm_freq1, 1);                                     //Escolhe a freq em um pino especifico. Não alterar o 1.
  pwm_setup(dir_m3, pwm_freq1, 1);                                     //Escolhe a freq em um pino especifico. Não alterar o 1.
  pwm_setup(dir_m4, pwm_freq1, 1);                                     //Escolhe a freq em um pino especifico. Não alterar o 1.
  pinMode(en_m1, OUTPUT);                                               //Pino enable.
  digitalWrite(en_m1, HIGH);                                               //Pino enable.
  pinMode(en_m2, OUTPUT);                                               //Pino enable.
  digitalWrite(en_m2, HIGH);                                               //Pino enable.
  pinMode(en_m3, OUTPUT);                                               //Pino enable.
  digitalWrite(en_m3, HIGH);                                               //Pino enable.
  pinMode(en_m4, OUTPUT);                                               //Pino enable.
  digitalWrite(en_m4, HIGH);                                               //Pino enable.
  
  pinMode(hall_1_m1, INPUT);                                               //Pino referente a leitura do sensor hall 1.
  pinMode(hall_2_m1, INPUT);                                               //Pino referente a leitura do sensor hall 2.
  pinMode(hall_1_m2, INPUT);                                               //Pino referente a leitura do sensor hall 1.
  pinMode(hall_2_m2, INPUT);                                               //Pino referente a leitura do sensor hall 2.
  pinMode(hall_1_m3, INPUT);                                               //Pino referente a leitura do sensor hall 1.
  pinMode(hall_2_m3, INPUT);                                               //Pino referente a leitura do sensor hall 2.
  pinMode(hall_1_m4, INPUT);                                               //Pino referente a leitura do sensor hall 1.
  pinMode(hall_2_m4, INPUT);                                               //Pino referente a leitura do sensor hall 2.
  
  Serial.begin(250000);                                                 //Velocidade da comunicação Serial.
  attachInterrupt(digitalPinToInterrupt(hall_1_m1), interrupt_hall_1_m1 , RISING ); //Interrupção externa, toda vez que o pino do hall subir o estado(RISING) de 0 para 1, entra na função que verifica outro hall.
  attachInterrupt(digitalPinToInterrupt(hall_1_m2), interrupt_hall_1_m2 , RISING ); //Interrupção externa, toda vez que o pino do hall subir o estado(RISING) de 0 para 1, entra na função que verifica outro hall.                                                                            //PPR para um hall=8pulsos
  attachInterrupt(digitalPinToInterrupt(hall_1_m3), interrupt_hall_1_m3 , RISING ); //Interrupção externa, toda vez que o pino do hall subir o estado(RISING) de 0 para 1, entra na função que verifica outro hall.                                                                            //PPR para um hall=8pulsos
  attachInterrupt(digitalPinToInterrupt(hall_1_m4), interrupt_hall_1_m4 , RISING ); //Interrupção externa, toda vez que o pino do hall subir o estado(RISING) de 0 para 1, entra na função que verifica outro hall.
  
  Timer.attachInterrupt(interrupt_tempo);                               //Chama função interrupt_tempo a cada 0,5Khz.
  Timer.start(10000);                                                     //Frequência 0,5Khz -> ts = 500 micro s


}


void loop () {
  //OBSERVAÇÃO: A frequência padrão do DUE, quando utilizada para acionar os drivers, era muito baixa.
  //Encontrou-se uma biblioteca capaz de aumentar a frequência nas portas (6,7,8 ou 9).
  pwm_write_duty(dir_m1, pwm_m1);//Esse comando escreve no pino (6,7,8 ou 9) com frequência determinada.
  pwm_write_duty(dir_m2, pwm_m2);//Esse comando escreve no pino (6,7,8 ou 9) com frequência determinada.
  pwm_write_duty(dir_m3, pwm_m3);//Esse comando escreve no pino (6,7,8 ou 9) com frequência determinada.
  pwm_write_duty(dir_m3, pwm_m4);//Esse comando escreve no pino (6,7,8 ou 9) com frequência determinada.
  
  Serial.print("ref: ");
  Serial.print(ref_m1);
  Serial.print("\t va: ");
  Serial.print(va_m1);
  Serial.print("\t x2rpm: ");
  Serial.print(x2rpm_m1);
  Serial.print("\t pwm: ");
  Serial.print(pwm_m1);
  Serial.print("\t counter: ");
  Serial.print(counter_m1);
  Serial.print("\t theta: ");
  Serial.println(theta_m1);
}
