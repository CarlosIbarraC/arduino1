#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>

Adafruit_SSD1306 display(-1);

//declarar pines
byte pote_pin = A0;
byte buzz = 2;
byte boton_inicia_juego = 3;
byte bala_x = 64;
byte bala_y = 0;
byte ant_bala_x = 64;
byte ant_bala_y = 0;
byte puntaje = 0;
byte vidas = 5;
byte nivel = 0;
byte cuenta_puntos = 0;
bool inicia_juego = false;

//variables globales
byte tamano_cursor = 30;
byte posicion = 0;

void setup() {
Serial.begin(9600);
display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
pinMode(boton_inicia_juego, INPUT_PULLUP);
attachInterrupt(digitalPinToInterrupt(boton_inicia_juego), cambia_estado_inicia_juego, FALLING);
display.display();
display.clearDisplay();
display.display();

dibuja_cursor(100);
mueve_bala(100);

}

void loop() {

if (inicia_juego==false){
delay(1000);
display.clearDisplay();
display.setCursor(0,28);
display.setTextColor(WHITE,BLACK);
display.println("P R E S S  S T A R T");
display.display();

while(inicia_juego == false) {
delay(50);
}

display.clearDisplay();
dibuja_puntaje();
dibuja_nivel();
dibuja_vidas();

}

randomSeed(analogRead(A2));
int valor_cursor = analogRead(pote_pin);
valor_cursor = map(valor_cursor,0,1024,0,127 - tamano_cursor);
Serial.println(valor_cursor);
dibuja_cursor(valor_cursor);
mueve_bala (valor_cursor);

}


void dibuja_cursor(byte pos){
display.drawLine(0,63,127,63, BLACK);
display.drawLine(pos,63, pos + tamano_cursor,63, WHITE);
display.display();
}

void mueve_bala(byte posicion){
bala_x = bala_x + random(-5,5);

if (bala_x > 127){
bala_x = 127;
}

if (bala_x < 1){
bala_x = 0;
}

bala_y++;
if(bala_y == 63 && bala_x > posicion && bala_x < posicion + tamano_cursor){cuenta_puntos++;
puntaje++;
if(cuenta_puntos>5){
nivel ++;
cuenta_puntos = 0;
}
tamano_cursor--;
bala_y = 0;
bala_x = 30;
dibuja_puntaje();
}

if (bala_y > 64){
vidas--;
bala_y = 0;
bala_x = 30;
dibuja_vidas();
}

display.drawPixel(ant_bala_x, ant_bala_y, BLACK);
display.drawPixel(bala_x, bala_y, WHITE);
display.display();
ant_bala_x = bala_x;
ant_bala_y = bala_y;
}

void dibuja_puntaje(){
display.setCursor(0,0);
display.setTextColor(WHITE,BLACK);
display.println("P " + String(puntaje));
display.display();
tone(buzz,5000,100);
dibuja_nivel();
}


void dibuja_nivel(){
display.setCursor(58,0);
display.setTextColor(WHITE,BLACK);
display.println("N " + String(nivel));
display.display();
tone(buzz,5000,100);
delay (100);
tone(buzz,10000,100);
delay (100);
tone(buzz,12000,100);
delay (100);
tone(buzz,15000,100);
}

void dibuja_vidas(){
display.setCursor(104,0);
display.setTextColor(WHITE,BLACK);
display.println("V " + String(vidas));
display.display();
tone(buzz,1000,100);
delay (100);
tone(buzz,800,100);
delay (100);
tone(buzz,500,100);
delay (100);
tone(buzz,300,100);
if (vidas == 0){
vidas = 5;
nivel = 0;
tamano_cursor = 30;
display.clearDisplay();
display.setCursor(0,28);
display.println("  G A M E  O V E R");
display.display();
tone(buzz,300,2500);
delay(3000);
inicia_juego = false;
}
}
void cambia_estado_inicia_juego(){
inicia_juego = true;
}
