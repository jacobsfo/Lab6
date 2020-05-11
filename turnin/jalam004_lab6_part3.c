/*	Author: jalam004
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab 5  Exercise 2
 *	Exercise Description: [optional - include for your own benefit]
 * Link: https://www.youtube.com/watch?v=Cbypw7ZwiZw
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include "timer.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States{Start, init, inc, dec, wait, reset} state; 
unsigned char cnt1 = 0; 
unsigned char cnt2 = 0;   
void Tick(){    
    switch(state)
    {   
        case Start:
        state = init;
        break;

        case init:
            if((~PINA & 0x01) == 0x01)
            {   //cnt++;
                state = inc;
		//cnt = 0;
            }
            else if((~PINA & 0x02) == 0x02)
            {	//cnt++;
                state = dec;
		//cnt = 0;
            }
            
           else if((~PINA & 0x03) == 0x03)
            {	
                state = reset;
            }

           else {state = init;}
            break;

        case inc:
	//cnt++;
	{state = wait;}
            break;
            
        case dec:
          {state = wait;}
       		 break;
        
        case wait:
        
        if((~PINA & 0x03) == 0x03)
        { state = reset;}
        else if(( ~PINA & 0x03) == 0x00)
        { state = init;}

        
        if((~PINA & 0x01) == 0x01)
	{cnt1++;}
	if((~PINA & 0x02) == 0x02) 
	{cnt2++;}
        else{state = wait;}
         break;
        
        case reset:
        {state = init;}
         break;

        default:
         break;
    }
        
    switch(state)
    {
        case Start:
       // PORTB = 0x07;
        break;

        case init:
        PORTB = 0x07;
	break;

        case dec:
        if(PORTB <= 0x00){PORTB = 0x00;}
        else{PORTB = PORTB - 1;}
	
        break;
        case wait:
	if(cnt1 == 10 )
       	PORTB = PORTB + 1;
	if(cnt2 == 10)
	PORTB = PORTB - 1;
//	else{return 1;}
	break;

        case inc:
        if(PORTB >= 0x09){PORTB = 0x09;}
       //	else if((cnt % 10 == 0) && (PORTB < 0x09)){PORTB = PORTB + 1;}	
	 else{PORTB = PORTB + 1;}
        break;

        case reset:
        PORTB = 0x00;
        break;
        
    }

}


int main(void) {
    
DDRA = 0x00; PORTA = 0xFF;
DDRB = 0xFF; PORTB = 0x00;
 state = Start;
//unsigned char tmpA = 0x00;
TimerSet(100);
TimerOn();
 //state = Start;
	while(1){
	Tick();
	
	while(!TimerFlag) {}
	TimerFlag = 0;

	}
return 1;
}	




