/* Juego del PONG; por Pablo González
 Tener en cuenta que en este juego, una especie de tenis,
 los jugadores son barritas en las cuales la pelotita debe
 rebotar...ya se que lo sabian, pero por si acaso =D 
 Conectar 2 potenciometros asi:
 - Los extremos de ambos potenciometros conectarlos a 5V y a GND
 - La pata central de un potenciometro a la entrada analogica 0 (jugador 1)
 - La pata central del otro potenciometro a la entrada analogica 1 (jugador 2)
 */

#include <OLED_I2C.h>// libreria para control del display OLED
#include <math.h>// libreria para cálculos que vamos a tener que hacer

// Los jugadores
int jug1;// variable para controlar al jugador 1 con un potenciometro 
int jug2;// idem para el jugador 2

// Variable para el conteo de goles del jugador 1 y del jugador 2
int a=0;// goles del jugador 1
int b=0;// goles del jugador 2

// Variables para la posición en cancha de la barrita de cada jugador
float pos1;
float pos2;

// Variables para las dimensiones de la cancha...ojo con cambiar mucho todos los numeros que puede salir cualquier cosa
float xcancha=15;// Seria la parte mas a la izquierda de la cancha
float ycancha=1;// Seria la parte mas arriba de la cancha
float largo=96; // largo de la cancha
float ancho=62;// ancho de la cancha
float sep=8; //separacion entre la barrita de cada jugador y la linea final de la cancha de su lado
float barrita=15;// largo de la barrita de cada jugador

// Variables para la pelotita (es un circulo chiquitito); se inicia en el centro de la cancha
float xp=64;//posición X inicial de la pelotita
float yp=32;//posición Y inicial de la pelotita
float r=2;// radio de la pelotita (tamaño)

// Como arranca la pelotita desplazandose al inicio del juego
// cambiandole estos valores se puede aumentar o disminuir la velocidad de la pelotita; pero no lo recomiendo
float xr=1;//desplazamiento en X de la pelotita
float yr=1;//desplazamiento en Y de la pelotita

OLED  myOLED(SDA, SCL, 8);// activamos la libreria del OLED
extern uint8_t SmallFont[];// Tamaño de fuente de los textos
extern uint8_t MediumNumbers[];// Tamaño de los numeros que indican el goleo de cada jugador

void setup()
{
  myOLED.begin();//inicializa el display OLED
  myOLED.setFont(SmallFont);//seteo el tamaño de la fuente para los textos que se escribiran
  myOLED.print("JUEGO DEL PONG", CENTER, 10);//imprime la frase entre comillas
  myOLED.print("Por Pablo Gonzalez", CENTER, 30);//imprime la frase entre comillas  
  myOLED.print("Canal de youtube", CENTER, 40);//imprime la frase entre comillas  
  myOLED.print("ARDUINO COMO HOBBY", CENTER, 50);//imprime la frase entre comillas      
  myOLED.update();// actualiza la pantalla haciendo lo anterior
  delay(2000);
  myOLED.clrScr(); // borra la pantalla
}

void loop () 
{
  int i;// variable local para el bucle for que hace que la barrita del jugador 1 se mueva
  int j;// idem del jugador 2
  jug1=analogRead(0);//El jugador 1 controla su barrita con un potenciometro colocado en la entrada analogica 0
  jug2=analogRead(1);//El jugador 2 controla su barrita con un potenciometro colocado en la entrada analogica 1
  pos1=jug1*(ancho-barrita)/1023+ycancha;// la posición de la barrita del jugador 1 de acuerdo a la señal analogica 0 y a las dimensiones de la cancha; 15 seria el largo en pixels de la barrita del jugador
  pos2=jug2*(ancho-barrita)/1023+ycancha;// la posición de la barrita del jugador 2 de acuerdo a la señal analogica 1 y a las dimensiones de la cancha; 15 seria el largo en pixels de la barrita del jugador
  myOLED.drawRect(xcancha,ycancha,xcancha+largo,ycancha+ancho);// dibuja el rectangulo que es la cancha
  myOLED.drawCircle(xp,yp,r);//dibuja la pelotita con su tamaño y posición inicial
  
  // Movimiento de la barra del jugador 1
  for(i=63;i>pos1;i--){
  myOLED.drawLine(xcancha+sep,pos1,xcancha+sep,pos1+barrita);// posicion de la barra del jugador 1 con su movimiento vertical
  }
  // Movimiento de la barra del jugador 2
  for(j=63;j>pos2;j--){
  myOLED.drawLine(xcancha+largo-sep,pos2,xcancha+largo-sep,pos2+barrita);// posicion de la barra del jugador 2 con su movimiento vertical
  }    
  
  myOLED.setFont(MediumNumbers);// fuente de tamaño grande para los numeros de goles de cada jugador  
  myOLED.printNumI(a,00,0);// imprime la cantidad de goles del jugador Nº 1
  myOLED.printNumI(b,115,0);// imprime la cantidad de goles del jugador Nº 2
  
  //Inicializo el desplazamiento de la pelotita...hay que darle un cierto inicio al comienzo del juego y yo le digo que empieze hacia la derecha
  xp=xp+xr;// va sumandole xr pixeles a su posición en X
  yp=yp+yr;// va sumandole yr pixeles a su posición en Y
  
  // Ahora viene el rebote de la pelotita en las paredes superior e inferior de la cancha
  if(yp>=(ycancha+ancho-r)) { // rebote en la pared inferior
  yr=-1;
  }
  else if(yp<=ycancha+r) { // rebote en la pared superior
  yr=1;
  }    
  
  // Ahora, el rebote de la pelotita en la barrita de los jugadores y la anotación de goles
  // si pasa lo siguiente, hay gol del jugador Nº 2
  if (xp<=(xcancha+r)) { // o sea si la pelotita llego mas atras de la posición X del jugador 1
  b=b+1;// aumenta en un gol su tanteador
  // la pelotita vuelve al medio de la cancha y ahora empieza al reves su desplazamiento
  xp=64;
  yp=32;
  xr=-xr;
  yr=-yr;
  delay (500);// un tiempito antes de mover del medio
  }    
  // sino hubo gol, entonces hubo rebote de la pelotita en el jugador 1 y debe cambiar su dirección
  if(xp==xcancha+sep+r && ((yp+r)>=pos1 && (yp-r)<=(pos1+barrita))) { // esto es para tomar en cuenta que la pelotita puede rebotar en cualquier parte de la barrita del jugador
  xr=-xr;  
  }
  // si pasa lo siguiente, hay gol del jugador Nº 1  
  if(xp>=(xcancha+largo-r)) { // o sea si la pelotita llego mas adelante de la posición X del jugador 2
  a=a+1;// aumenta en 1 gol su tanteador
  // la pelotita vuelve al medio de la cancha y ahora empieza al reves su desplazamiento
  xp=64;
  yp=32;
  xr=-xr;
  yr=-yr;
  delay(500);// un tiempito antes de mover del medio
  }
  // si no hubo gol, hubo rebote de la pelotita en el jugador 2
  else if(xp==xcancha+largo-sep-r && ((yp+r)>=(pos2) && (yp-r)<=(pos2+barrita))) { // esto es para tomar en cuenta que la pelotita puede rebotar en cualquier parte de la barrita del jugador
  xr=-xr;  
  }  
  
  // El partido termina cuando algun jugador llega a 10 goles
  if (a==10) {
  myOLED.setFont(SmallFont);//seteo el tamaño de la fuente para los textos que se escribiran    
  myOLED.clrScr(); //borra la pantalla 
  myOLED.print("Partido terminado",CENTER,10);
  myOLED.print("Gano el jugador",CENTER,20);
  myOLED.print("de la izquierda",CENTER,30);
  myOLED.print("GRACIAS POR JUGAR",CENTER,50); 
  myOLED.update();//actualiza la pantalla  
  a=0;
  b=0;
  delay(10000);// en 10 segundos vuelve a empezar el partido
  }
  else if (b==10) {
  myOLED.setFont(SmallFont);//seteo el tamaño de la fuente para los textos que se escribiran    
  myOLED.clrScr(); //borra la pantalla 
  myOLED.print("Partido terminado",CENTER,10);
  myOLED.print("Gano el jugador",CENTER,20);
  myOLED.print("de la derecha",CENTER,30);  
  myOLED.print("GRACIAS POR JUGAR",CENTER,50); 
  myOLED.update();//actualiza la pantalla  
  a=0;
  b=0;
  delay(10000);//en 10 segundos vuelve a empezar
  }
  myOLED.update();//actualiza la pantalla
  myOLED.clrScr(); //borra la pantalla y reinicia el loop
}
