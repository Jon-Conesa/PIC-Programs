#include <16F877.h>
#fuses XT,HS,NOWDT,NOPROTECT,NOLVP,PUT,BROWNOUT
#use delay(clock=20000000)
#use rs232(baud=9600, xmit=PIN_C6, rcv=PIN_C7)


void main(){
   int16 i;
   set_tris_d(0x00);
   while(1){
      output_d(0b00000001);
      delay_ms(50);
      output_d(0b00000010);
      delay_ms(50);
      output_d(0b00000100);
      delay_ms(50);
      output_d(0b00001000);
      delay_ms(50);
      output_d(0b00010000);
      delay_ms(50);
      
      output_d(0b00010000);
      delay_ms(50);
      output_d(0b00001000);
      delay_ms(50);
      output_d(0b00000100);
      delay_ms(50);
      output_d(0b00000010);
      delay_ms(50);
      output_d(0b00000001);
      delay_ms(50);
      
      }
   }

