#include <Wire.h>

int cont;

void setup() {
  Wire.begin(); // join i2c bus (address optional for master)
  Serial.begin(57600);
}

int dados[6];

void loop() {
  Wire.requestFrom(8, 6);
  Serial.println("agr vai");

  while (Wire.available())
  {
    for ( cont = 0; cont < 6 ; cont++)
    {
      dados[cont] = Wire.read();
      Serial.println("Recebe");
      Serial.println(dados[cont]);
    }
    dados[0] = map(dados[0], 0, 255, -3000, 3000);
    dados[1] = map(dados[1], 0, 255, -3000, 3000);
    dados[2] = map(dados[2], 0, 255, -3000, 3000);
    dados[3] = map(dados[3], 0, 255, -3000, 3000);

    Serial.println("Transforma");

    for ( cont = 0; cont < 6 ; cont++)
    {
      Serial.println(dados[cont]);
    }
  }
}
