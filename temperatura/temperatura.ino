/*
 Creado: Luis del Valle (ldelvalleh@programarfacil.com)
 https://programarfacil.com
*/

// Declaracion de variables globales
float tempC; // Variable para almacenar el valor obtenido del sensor (0 a 1023)
int pinLM35 = 0; // Variable del pin de entrada del sensor (A0)
const int buzzer = 9;
void setup() {
  // Configuramos el puerto serial a 9600 bps
  Serial.begin(9600);
  pinMode(3,OUTPUT);
}
//prueba
void loop() {
  // Con analogRead leemos el sensor, recuerda que es un valor de 0 a 1023
  tempC = analogRead(pinLM35); 
   pinMode(buzzer, OUTPUT); 
  // Calculamos la temperatura con la fórmula
  tempC = (5.0 * tempC * 100.0)/1024.0; 
  if(tempC>24){
    digitalWrite(3,HIGH);
     tone(buzzer, 3000); // Send 1KHz sound signal...
  delay(1500);
  }else{
     digitalWrite(3,LOW);
    noTone(buzzer);
  }
  // Envia el dato al puerto serial
  Serial.print(tempC);
  // Salto de línea
  Serial.print("\n");
  
  // Esperamos un tiempo para repetir el loop
  delay(4000);
}
//         m,,,,,