//--------------------------------------------------------------------------------------
//El propósito del siguiente código es hacer que el microcontrolador vaya encendiendo
//unos leds colocados en fila en forma ascendente, luego los apague en forma ascendente,
//luego los encienda de forma descendente, y por último los apague en forma descendente,
//antes de comenzar el proceso de nuevo. Además, implementaremos una interrupción para
//poder enceder y apagar un led amarillo conectado al pin 4, cuando se oprima un
//botón, el cual puede ser presionado en cualquier momento.

//OBSERVACIÓN: Según la forma en que se conectan las componentes físicos, el significado
//de "ascendente" corresponde a ir desde el pin 12 al 5, y el de "descendente"
//a ir desde el 5 hasta el 12.

//NOTA: Este código fue implementado para el modelo Arduino UNO.
//--------------------------------------------------------------------------------------

//En este pin irá el led amarillo.
short LED = 4;

//Esta variable recorrerá los leds para encenderlos y apagarlos.
short pin = 12;

//Esta variable controlará si vamos del 12 al 5 (incre = -1), o si
//vamos del 5 al 12 (incre = 1).
short incre = -1;

//La variable shine nos dirá si estamos encendiendo o apagando los leds.
bool shine = true;

//Este será el estado del led amarillo; notemos que utilizamos el modificador
//volatile para poder indicarle al compilador que esta variable podría cambiar
//su valor en cualquier momento, esto es pues será utilizada dentro de la ISR.

volatile bool yellow = false;

void setup() {

  //Colocamos los pines desde el 4 hasta el 12 como salidas.
  for (short i = 4; i < 13; i++) pinMode(i, OUTPUT);

  //Invocamos la función attachInterrupt() para definir la función press_btn()
  //como la ISR de la interrupción que se provocará cuando se presente
  //un flanco de subida en el pin 2.
  
  attachInterrupt(digitalPinToInterrupt(2), press_btn, RISING);

  //Recordemos que utilizamos la función digitalPinToInterrupt() en lugar de
  //simplemente colocar 0 para facilitar la portabilidad del código a otro
  //modelo de Arduino.
}

void press_btn() {

  //Cambiamos el estado en que se encuentra el led amarillo.
  
  yellow = !yellow;
  digitalWrite(LED, yellow);
}

void loop() {

  //Escribimos el código para encender y apagar los leds como queremos.
  
  digitalWrite(pin, shine);
  pin += incre;
  
  if ((pin == 4) and shine) {

    //Volvemos al pin 12 y comenzamos a apagar los leds.
    pin = 12;
    shine = false;
  }
  else if (pin == 4) {

    //Nos comenzamos a devolver y vamos encendiendo los leds.
    incre = 1;
    pin = 5;
    shine = true;
  }
  else if ((pin == 13) and shine) {

    //Volvemos al pin 5 y comenzamos a apagar los leds.
    pin = 5;
    shine = false;
  }
  else if (pin == 13) {

    //Nos comenzamos a devolver y vamos encendiendo los leds.
    incre = -1;
    pin = 12;
    shine = true;
  }

  //Colocamos un delay() para que el brillar de los leds se
  //puedan apreciar de una forma suave.
  
  delay(100);
}
