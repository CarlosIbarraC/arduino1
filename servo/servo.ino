#include <Servo.h>

Servo servoMotor;
int angulo=0;


void setup() {
 Serial.begin(9600);
servoMotor.attach(9);
}

void loop() {

 angulo=servoMotor.read();
  // Esperamos 1 segundo
   Serial.print(angulo);
  delay(1000);
  
  // Desplazamos a la posición 90º
  angulo=servoMotor.read();
  // Esperamos 1 segundo
  delay(1000);
  Serial.print(angulo);
  // Desplazamos a la posición 180º
  angulo=servoMotor.read();
  // Esperamos 1 segundo
  delay(1000);
  Serial.print(angulo);
}
