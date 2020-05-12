

int cuenta=0;
String saludo="hola mundo";
bool activado=false;
void setup() {
  Serial.begin(9600);
  Serial.println("primera practica");
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
 cuenta = cuenta+1;
 Serial.println(String(cuenta));
 delay(100);
} 
