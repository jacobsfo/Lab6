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


enum States {Start,On1,On2,On3,L2,Stop,W1} State;
//unsigned char flg=0;
//unsigned char tmpA = 0x00;
//tmpA = PINA;
void MyStateMachine() {
  unsigned char cnt1 = 0x00;
 unsigned char cnt2 = 0x00;
unsigned char cnt3 = 0x00;
unsigned char cnt4 = 0x00;
 unsigned char tmpA = 0x00;
tmpA = ~PINA & 0x01;
switch(State) {   // Transitions
    case Start:  // Initial transition
       // flg = 0x01;
	State = On1;
        break;
//tick 1
     case On1:
cnt1++;
if( ((tmpA == 0x01) && (cnt1 == 0x03))) //stop
{State = Stop;}

else {
State = On2;
}

break;
//tick 2     
case On2:
cnt2++;
if( ((tmpA == 0x01) && (cnt2 == 0x02)))
{State = Stop;}

else{
	State = On3;
	}
 
break;
//tick 3	
	case On3:
	cnt3++;
	if( ((tmpA == 0x01) && (cnt3 == 0x02)))
	{State = Stop;}

	else{
	State = L2;
	}
	case L2:
	cnt4++;
	if( ((tmpA == 0x01) && (cnt3 == 0x02)))
	{State = Stop;}

	else{
	State = On1;
	}

/* if(tmpA == 0x01)
	State = Stop;
	else{
	State = On1;
	}*/
 break;
case Stop:
if(cnt1 == 0x03)
cnt1 = 0;
if(cnt2 == 0x02)
cnt2 = 0;

if(cnt3 == 0x02)
cnt3 = 0;

if(cnt4 == 0x02)
cnt4 = 0;


	State = W1;
break; 
case W1:
	if(tmpA == 0x00)
{
	State = W1;
}
	else{
	State = On1;
	}
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
	//if(tmpA == 0x00)
	//flg = 0x00;
        break;
    case L2:
	PORTB = 0x02;
break;
	 case On2:
	PORTB = 0x02 ;
       break;
     case On3:
	PORTB = 0x04;
	break;
	case Stop:
	break;
	case W1:
	break;
     default:
       State = Start;
        break;
  }
}

int main() {
DDRB = 0xFF;
DDRA = 0x00;
PORTA = 0xFF;   
PORTB = 0x00;
             // Initialize outputs
   State = Start; // Indicates initial call
TimerSet(300);
TimerOn();
   while(1) {

// unsigned char tmpA = 0x00;
 MyStateMachine();
   while(!TimerFlag) {}
	TimerFlag = 0;
//	tmpA = ~PINA & 0x01
   }
   return 1;
}

