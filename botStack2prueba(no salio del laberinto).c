/*
  Blank Simple Project.c
  http://learn.parallax.com/propeller-c-tutorials 
*/

#include "simpletools.h"                      // Include simpletools header
#include "abdrive.h"                          // Include abdrive header
#include "ping.h"                             // Include ping header
#include <stdio.h>

#define MAXSIZE 100
//############################################################################################################################### 
struct stack
{
    int stk[MAXSIZE];
    int top;
};
typedef struct stack STACK;
//###############################################################################################################################
STACK s;
int num_op;
int cont=0;
int cont_der=0;
int cont_izq=0;
int d_total;
int d_total2;
int d_total3;
//############################################################################################################################### 
void push(int);
int  pop(void);
void Verificar ();
void Retroseso ();

//###############################################################################################################################  
void main ()
{
   s.top = -1;
   // d_total= d_izq() + d_der() + 5;
   d_total = 20;          //verificacion lados
   d_total2 = 61;         //cant de pasos, 85-> 25cm
   d_total3 = 11;         //verificacion  adelante
    while (1)   //resuelve el laberinto
    {
     Verificar();      
    }
    return;
}
//*******************************************************************************************************************************/
//                                                          Metodos STACK
void push (int num){       /*  Function to add an element to the stack */
    if (s.top == (MAXSIZE - 1)){ return;} //Stack is /full //como la pila comienza desde 0, esta desfasado 1
    else
    {   s.top = s.top + 1;                //Enter the element to be pushed;
        s.stk[s.top] = num;
    }
    return;
}

int pop (){               /*  Function to delete an element from the stack */
    int num;
    //if (s.top == - 1){ return (s.top);}    //Stack is Empty
    //else{   
      num = s.stk[s.top];
      s.top = s.top - 1;
    //}
    return(num);
}

// Function to display the status of the stack 
//void display ()
//{
//    int i;
//    if (s.top == -1)
//    {
//        //Stack is empty;
//        return;
//    }
//    else
//    {
//        printf ("\n The status of the stack is \n");
//        for (i = s.top; i >= 0; i--)
//       {
//           printf ("%d\n", s.stk[i]);
//        }
//    }
//    printf ("\n");
//}
//*******************************************************************************************************************************/
// Verificar: asigna un numero y lo almacena en el                                                           
int d_der(){
  return ping_cm(3);
}
int d_ade(){
  return ping_cm(8);
}
int d_izq(){
  return ping_cm(10);
}

void Verificar (){
  //if (d_izq()<d_total && d_der()<d_total && d_ade()<d_total){ num_op =1; push(num_op);mov_ade();}
  if (d_izq()<d_total && d_der()<d_total && d_ade()>d_total3){ num_op =1; push(num_op);mov_ade();}
  if (d_izq()>d_total && d_der()<d_total && d_ade()<d_total3){ num_op =2; push(num_op);mov_izq();}
  if (d_izq()<d_total && d_der()>d_total && d_ade()<d_total3){ num_op =3; push(num_op);mov_der();}

  if (d_izq()>d_total && d_der()<d_total && d_ade()>d_total3){ num_op =4; push(num_op);mov_ade();}
  if (d_izq()<d_total && d_der()>d_total && d_ade()>d_total3){ num_op =5; push(num_op);mov_der();}
  if (d_izq()>d_total && d_der()>d_total && d_ade()>d_total3){ num_op =6; push(num_op);mov_der();}
  if (d_izq()>d_total && d_der()>d_total && d_ade()<d_total3){ num_op =7; push(num_op);mov_der();}
  
  if (d_izq()<d_total && d_der()<d_total && d_ade()<d_total3){ num_op =0; push(num_op); Retroceso();}
  return;  
}

void Retroceso (){
  num_op = pop();
  mov_ret();
  
  int ciclo= 1;
  cont = 1;
  while (ciclo=1){
    num_op = pop();
    if (num_op==1){mov_ade();}
    if (num_op==2){mov_der();}
    if (num_op==3){mov_izq();}
    if (num_op==4){ciclo=2; push(1); mov_der();}
    if (num_op==5){ciclo=2; push(1); mov_der();}
    if (num_op==6){ciclo=2; push(4); mov_der();}
    if (num_op==7){ciclo=2; push(2); mov_ade();}
  }
  cont = 0;  
  return; 
}

//*******************************************************************************************************************************/
// Subrutinas de movimiento:
void mov_ade(){
  drive_goto(d_total2/4,d_total2/4);
  if (d_ade<(d_total3)){return;}         
  drive_goto(d_total2/4,d_total2/4);
  if (d_ade<(d_total3)){return;}         
  drive_goto(d_total2/4,d_total2/4);
  if (d_ade<(d_total3)){return;}         
  drive_goto(d_total2/4,d_total2/4);
  return;
}
void mov_der(){
  
  drive_speed(0,0);
  pause(500);
  if(cont==0){drive_goto(26,-25);}
  if(cont==1){drive_goto(26,-25);}
  pause(500);
  drive_goto(20,20);    //avanza recto  
  while(d_der()>d_total && d_ade()>5){
    drive_speed(15,15);
  } 
  //drive_goto(d_total2/2,d_total2/2);
  drive_goto(20,20);
  return;  
}

void mov_izq(){
  
  drive_speed(0,0);
  pause(500);
  drive_goto(-25,29);
  pause(500);
  drive_goto(20,20);
  
  while(d_izq()>d_total && d_ade()>5){
    drive_speed(15,15);
  }
  drive_goto(25,25);
  //drive_goto(d_total2/2,d_total2/2);
  return;  
}
void mov_ret(){
   drive_speed(0,0);
   drive_goto(-(d_total2),-(d_total2));
   drive_speed(0,0);
   pause(500); 
        
   drive_goto(-53,51); 
  return;  
}

