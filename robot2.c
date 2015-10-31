//Universidad del Valle de Guatemala
//Algoritmos y Estructura de Datos

//Jose Corona         14417
//Boggdan Barrientos  14484
//Julio Dieguez       14475
//Jonathan Aguirre    14349
//Bryan Chan          14469

#include "simpletools.h"                      // Include simpletools header
#include "abdrive.h"                          // Include abdrive header
#include "ping.h"                             // Include ping header

// tamaño maximo del stack
#define MAXSIZE 100

//Stack Guarda la ruta bajo el codigo:
//1 avanza
//2 giro derecha
//3 giro izquierda

int main()                                    // main function
{
  //Pueros A0 y A1 en LOW
  //Puertos usados para IR
  low(26);
  low(27);
  
  //en primer lugar se almacena el avance (1-avance)
  push(1);
  
  while(1)                                    
  {
    //mientras no este realizando subrutinas avanza
    drive_speed(40,40);
    
    //si la distancia frontal es menor a 6cm entonces...
    if (d_frontal() < 6){
      //como gira a la derecha se almacena en stack (3-izquierda)
      push(3);
      //si la distancia frontal es menor a 
      giro_izquierda();
    }
    
    // si no hay pared a la derecha y la distancia frontal es mayor a 5cm entonces..   
    if (evaluar_d() == 1 && d_frontal() > 5){
      //toma un poco de separacion avanzando un poco hacia enfrente
      drive_goto(7,7);
      //realiza la subrutina giro derecha
      giro_derecha();
      //como gira a la derecha se almacena (2-derecha)
      push(2);
      
      //mientras tenga pared a la derecha y no tenga pared enfrente avanza
      while(evaluar_d()==1 && d_frontal()>5){
        //avanza con velocidad lenta para no esquivar paredes
        drive_speed(10,10);
      }
      
      //como ejecuta un avance se almacena en stack (1-avance)
      push(1);
      
      //avanza un poco antes de volver a evaluar
      drive_goto(7,7); 
    }
  }
}

//subrutina que nos debuelve la distancia del sensor ultrasonico frontal
int d_frontal(){
  return ping_cm(8);
}

// evaluar_d() Evalua hacia la derecha...
// Retorna 1 si no hay objeto
// Retorna 0 si hay objeto
int evaluar_d(){
    //lanza frecuencia de Infrarojo en puerto 1
    freqout(1, 1, 38000);
    // si hay objeto encendera el LED en el puerto5
    if (input(2)==1){
      high(5);
    }
    // si no hay objeto apaga el LED el puerto6
    else{
      low(5);
    }
    return input(2);
}

// evaluar_i() Evalua hacia la izquierda...
// Retorna 1 si no hay objeto
// Retorna 0 si hay objeto
int evaluar_i(){
    //lanza frecuencia de infrarojo en puerto 11
    freqout(11, 1, 38000);  
    // si hay objeto encendera el LED en el puerto6    
    if (input(10)==1){
      high(6);
    }
    // si no hay objeto apaga el LED el puerto6
    else{
      low(6);
    }              
    //Retorna 0,1 dependiendo si hay o no objeto  
    return input(10);
}

//giro_derecha():  subrutina que efectua un giro hacia la derecha
void giro_derecha(){
  //en primer lugar debe detener el carrito
  drive_speed(0,0);
  //pausa de medio segundo
  pause(500);
  //giro derecha
  drive_goto(26,-25);
  //pausa de medio segundo
  pause(500);
  //avanza ligeramente
  drive_goto(5,5); 
  return;  
}

//giro_izquierda():  subrutina que efectua un giro hacia la derecha
void giro_izquierda(){
  //en primer lugar debe detener el carrito
  drive_speed(0,0);
  //pausa de medio segundo
  pause(500);
  //giro izquierda
  drive_goto(-26,25);
  //pausa de medio segundo
  pause(500);
  //avanza ligeramente
  drive_goto(5,5);
  return;
}


//=============================
//          STACK
//=============================

// Definir la estructura stack
struct stack
{
    int stk[MAXSIZE];
    int top;
};
typedef struct stack STACK;

// Nuestro stack es llamado s
STACK s;

void push(int);
int  pop(void);

// push (int num):  Funcion para agregar un elemento al stack
void push (int num){       
    if (s.top == (MAXSIZE - 1)){ return;} //Stack is /full //como la pila comienza desde 0, esta desfasado 1
    else
    {   s.top = s.top + 1;                //El atributo top aumenta 1
        s.stk[s.top] = num;               //Se agrega en la nueva ubicacion
    }
    return;
}

// pop ():  funcion para pedir y elimenar el ultimo elemento del stack
int pop (){              
    int num;
    if (s.top == - 1){ return (s.top);}    //Si el stack esta vacio
    else
    {   num = s.stk[s.top];                //Se toma el ultimo elemento
        s.top = s.top - 1;                 //Se cambia la referencia de ultimo elemento al anterior
    }
    //retornamos el numero
    return(num);
}
