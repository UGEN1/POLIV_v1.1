#include "functions.h"
#include <TimerOne.h>

int led=13;
volatile int statled = LOW;
const int but_mode = 2;
Setwork Set;
OUTDATE out;
INDATE in;
Working WORK;


void setup() {
Serial.begin (9600);
Set.begin_work();     //инициализация переферии. Датчики, реле и т.д.

              }

              

void loop() {

  if (BLUETOOTH.available())
    {
     Set.workin_cicl();      //активация рабочего цикла
     }   
           }

   







      




    
  





  



  



            
            
