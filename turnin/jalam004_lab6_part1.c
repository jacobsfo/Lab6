/*	Author: lab
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */




#include <avr/io.h>
#include "timer.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif


enum States {Start,On1,On2,On3} State;
//unsigned char cnt=0;

void MyStateMachine() {
  switch(State) {   // Transitions
     case Start:  // Initial transition
        State = On1;
        break;
//tick 2
     case On1:
//	if(cnt > 1)
	//PORTB = 0x01;
	State = On2;
//else{
  //      State = On1;
	   
	break;
//	else{State = Off;}
//tick 2     
case On2:
	//PORTB = 0x02;
	State = On3;
        break;
//tick 3	
	case On3:
	//PORTB = 0x04;
	State = On1;
	break;

     default:
       State = Start;
        break;
  } // Transitions

switch(State) {   // Transitions
     case Start:  // Initial transition
	
        break;

     case On1:
    	PORTB = 0x01;
//	State = On2;
        break;

     case On2:
	PORTB = 0x02 ;
//	State = On3;
       break;
     case On3:
	PORTB = 0x04;
//	State = On1;
	break;
     default:
       State = Start;
        break;
  }
}

int main() {
DDRB = 0xFF;   
PORTB = 0x00;              // Initialize outputs
   State = Start; // Indicates initial call
TimerSet(1000);
TimerOn();
   while(1) {

 MyStateMachine();
   while(!TimerFlag) {}
	TimerFlag = 0;

   }
   return 1;
}

