#include <16F877.h>
#fuses HS,NOWDT,NOPROTECT,NOLVP
#use delay(clock=4000000)
#use rs232(baud=9600, xmit=PIN_C6, rcv=PIN_C7)
#define DELAY_COUNTER_VALUE    10000
#define PORTB 0x06
#define PORTD 0x08

#byte DipSwitch=PORTD
#byte LedsBar=PORTB
#bit  Switch5=PORTD.5
#bit  Led6=PORTB.6
#bit  Led5=PORTB.5
#bit  Led0=PORTB.0
#bit  Led1=PORTB.1
#bit  Led2=PORTB.2
#bit  Led3=PORTB.3
#bit  Led4=PORTB.4
#bit  Led7=PORTB.7
#bit  Led[8] = {0,1,2,3,4,5,6,7};
#bit  Toggle_Led= PORTB.0   

void main(void)
{
unsigned long m_delay_counter=DELAY_COUNTER_VALUE;
int1 x=0;
int i=0;

set_tris_d(0xff);
set_tris_b(0x00);
LedsBar=0;
while(1)
{
   x=Switch5;      
   for(i=0;i<=7;i+=1)
    {
    Led[i] =x;
    }
    for(i=7;i<=0;i-=1)
    {
    Led[i] =x;
    }
   
   if (m_delay_counter==0)
      {
         m_delay_counter=DELAY_COUNTER_VALUE;
         Toggle_Led=~Toggle_Led;   
      }
      output.bit(
}
}
