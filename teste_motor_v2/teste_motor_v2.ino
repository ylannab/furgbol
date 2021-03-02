#include ".\Pwm01\pwm01.h"

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

uint32_t  pwm_duty = 32767;
uint32_t  pwm_freq1 = 20000;
uint32_t  valPWM = 0;
uint32_t  valPWM2 = 0;
uint32_t  valPWM3 = 0;
uint32_t  valPWM4 = 0;


void setup()
{


  // Set PWM Resolution
  //  pwm_set_resolution(16);

  // Setup PWM Once (Up to two unique frequencies allowed
  //-----------------------------------------------------
  pwm_setup( dir_m1, pwm_freq1, 1);
  pwm_setup( dir_m2, pwm_freq1, 1);
  pwm_setup( dir_m3, pwm_freq1, 1);
  pwm_setup( dir_m4, pwm_freq1, 1);
  
  // Write PWM Duty Cycle Anytime After PWM Setup
  //-----------------------------------------------------

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

  
  Serial.begin(115200);
}

void loop()
{

  /*while (valPWM <= 255) {
    pwm_write_duty( dir_m1, valPWM);
    delay(50);
    valPWM++;
    Serial.println(valPWM);
  }
  delay(2000);

  while (valPWM > 0) {
    valPWM2--;
    pwm_write_duty (dir_m1, valPWM);
    delay(50);
    Serial.println(valPWM);
  }
  delay(2000);
  */
  while (valPWM2 <= 255) {
    pwm_write_duty( dir_m1, valPWM);
    pwm_write_duty( dir_m2, valPWM2);
    pwm_write_duty( dir_m3, valPWM3);
    pwm_write_duty( dir_m4, valPWM4);
    
    delay(50);
    valPWM++;
    valPWM2++;
    valPWM3++;
    valPWM4++;
    Serial.print("m1");
    Serial.print(valPWM);
    Serial.print("\t m2");
    Serial.print(valPWM2);
    Serial.print("\t m3");
    Serial.print(valPWM3);
    Serial.print("\t m4");
    Serial.println(valPWM4);
  }
  delay(2000);

  while (valPWM2 > 0) {
    valPWM--;
    valPWM2--;
    valPWM3--;
    valPWM4--;
    pwm_write_duty( dir_m1, valPWM);
    pwm_write_duty( dir_m2, valPWM2);
    pwm_write_duty( dir_m3, valPWM3);
    pwm_write_duty( dir_m4, valPWM4);
    delay(50);
    Serial.print("m1");
    Serial.print(valPWM);
    Serial.print("\t m2");
    Serial.print(valPWM2);
    Serial.print("\t m3");
    Serial.print(valPWM3);
    Serial.print("\t m4");
    Serial.println(valPWM4);
  }
  delay(2000);

  /*while (valPWM3 <= 255) {
    pwm_write_duty( dir_m3, valPW3);
    delay(50);
    valPWM3++;
    Serial.println(valPWM3);
  }
  delay(2000);

  while (valPWM3 > 0) {
    valPWM3--;
    pwm_write_duty (dir_m3, valPWM3);
    delay(50);
    Serial.println(valPWM3);
  }
  delay(2000);
*/
  
}
