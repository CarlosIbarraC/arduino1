/**************************************************************************
 This is an example for our Monochrome OLEDs based on SSD1306 drivers

 Pick one up today in the adafruit shop!
 ------> http://www.adafruit.com/category/63_98

 This example is for a 128x64 pixel display using I2C to communicate
 3 pins are required to interface (two I2C and one reset).

 Adafruit invests time and resources providing this open
 source code, please support Adafruit and open-source
 hardware by purchasing products from Adafruit!

 Written by Limor Fried/Ladyada for Adafruit Industries,
 with contributions from the open source community.
 BSD license, check license.txt for more information
 All text above, and the splash screen below must be
 included in any redistribution.
 **************************************************************************/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET 4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(-1);
float tempC;     // Variable para almacenar el valor obtenido del sensor (0 a 1023)
int pinLM35 = 0; // Variable del pin de entrada del sensor (A0)
byte bufferTemp[128] ;
void setup()
{
  for (int i =0; i<128; i++)
  {
    bufferTemp[i]=100;
  }
  
  Serial.begin(9600);
  
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  { // Address 0x3D for 128x64///
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ; // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  /*  display.display();
  delay(2000); */
  // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();
  // Draw a single pixel in white
  /* display.fillRect(2,2,120,60,WHITE);//rectangulo relleno
display.drawRect(2,2,110,50,BLACK);// rectangulo recto vacio
display.drawRect(2,2,100,40,BLACK);
display.drawRoundRect(2,2,90,30,12,BLACK); //rectangulo redondeado */
  /* display.drawTriangle(40,40,45,60,60,60,WHITE);
 */
  display.setTextSize(1);
  display.setTextColor(WHITE);
}
// repite linea cada 10 pxl
void dibujaCuadricula()
{
  for (int b = 13; b < 64; b = b + 10)
  {
    for (int i = 0; i < 128; i = i + 12)
    {
      display.drawPixel(i, b, WHITE);
    }
    if (b == 43)
    {
      for (int i = 0; i < 128; i = i + 2)
      {
        display.drawPixel(i, b, WHITE);
      }
    }
  }
}
void loop()
{
  tempC = analogRead(pinLM35);
   display.clearDisplay();
  // Calculamos la temperatura con la fórmula
  tempC = (5.0 * tempC * 100.0) / 1024.0;
  // Envia el dato al puerto serial
 
  display.setCursor(5, 0);
  display.print(tempC + String("-C"));
  llenaBufer(tempC);
  
  dibujaCuadricula();
  dibujaCurva();
  display.display();
  delay(500);
  // Salto de línea

  // Esperamos un tiempo para repetir el loop
}
void dibujaCurva()
{
 
  for (int i = 0; i < 128; i++)
  {
    if(bufferTemp[i]< 100){
      int y = map(bufferTemp[i],-10,50,53,13);
    display.drawPixel(i,y, WHITE);
    }
  }
}

void llenaBufer( int tempC){
  for(int i=1;i<128;i++){
      bufferTemp[i-1]=bufferTemp[i];
  }
  bufferTemp[127]=tempC;
}