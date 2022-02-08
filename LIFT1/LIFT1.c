#include <mega16.h>
#include <delay.h>
int Z[]={0x3F, 0x30, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x67};
int currentFloor=0;
int desireFloor;
 int floor=0;
 int count=0;
 int i;
 int j;


void main(){

PORTC=0b00001000;
DDRC=0b10011101;

PORTD=0b10000000;    //desired floor
DDRD=0b11111111;

PORTB=0b11011111;
DDRB=0b00100000;

PORTA=0b00000000;       //current floor
DDRA=0b01111111;

while(1){

PORTA=Z[currentFloor];

if(count==0){
 while((count!=10)&&(PINB.0==1)&&(PINB.1==1)&&(PINB.2==1)&&(PINB.3==1)){
 count++;
delay_ms(500);
  }
}
if(count==10){            //default floor
 PORTD=Z[1];
 floor=1;
}
if(PINB.0==0){          //sw1 ground_floor
 PORTD=Z[0];
 floor=0;
}
if(PINB.1==0){          //sw2 first_floor
 PORTD=Z[1];
 floor=1;
}
if(PINB.2==0){            //sw3 seccond_floor
 PORTD=Z[2];
 floor=2;
}
if(PINB.3==0){             //sw4 third_floor
 PORTD=Z[3];
 floor=3;
}


desireFloor=floor;

if((PINB.4==0)||(count==10 )){
delay_ms(200);
if(desireFloor!=currentFloor){

if(currentFloor<desireFloor){

   for(i=currentFloor;i<=desireFloor;i++){

   if(i==desireFloor){
   PORTC.0=0;
   PORTC.2=0;

    PORTB.5=1;        //buzzer
    delay_ms(400);
    PORTA=Z[i];
    PORTC.4=1;        // door open
    PORTC.7=0;
    delay_ms(2000);
    PORTC.4=0;        // door closed
    PORTC.7=1;
    delay_ms(2000);
    PORTC.4=0;
    PORTC.7=0;
    PORTB.5=0;        //buzzer
    delay_ms(400);
    count=0;
    break;

   }
   PORTC.0=1;         //  lift on
   PORTC.2=0;
   delay_ms(2000);
   PORTC.0=0;         // lift stop
   PORTC.2=0;
   PORTA=Z[i+1];
   }
   }
   if(currentFloor>desireFloor){
   PORTC.0=0;
   PORTC.2=1;
   for(j=currentFloor;j>=desireFloor;j--){


   if(j==desireFloor){
   PORTC.0=0;
   PORTC.2=0;

    PORTB.5=1; //buzzer
    delay_ms(400);
    PORTC.4=1;   // door open
    PORTC.7=0;
    delay_ms(2000);
    PORTC.4=0;     // door closed
    PORTC.7=1;
    delay_ms(2000);
    PORTC.4=0;  //door motor stop
    PORTC.7=0;
    PORTB.5=0;  //buzzer
    delay_ms(400);
    count=0;
    break;

   }

   PORTC.0=0;  // lift move
   PORTC.2=1;
   delay_ms(2000);
   PORTC.0=0;    // lift stop
   PORTC.2=0;
   PORTA=Z[j-1];



   }
}
}
   currentFloor=desireFloor;

 }
 // count=0;
}
}