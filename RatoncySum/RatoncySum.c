#include <16F877.h>
#fuses HS,NOWDT,NOPROTECT,NOLVP
#use delay(clock=20000000)
#use rs232(baud=9600, xmit=PIN_C6, rcv=PIN_C7)  // Definicion del RS232


int udreta;
int uesquerra;
int ldreta;
int lesquerra;
int lcentral;
char opcio;    
int aux=0;                     


void linia(){ //funcio per poder llegir els sensors de linia
   set_adc_channel(5);
   delay_ms(1);
   ldreta = read_adc();
   
   set_adc_channel(6);
   delay_ms(1);
   lcentral = read_adc();
   
   set_adc_channel(7);
   delay_ms(1);
   lesquerra = read_adc();
   
   delay_ms(100);

}
void ulls(){ //funcio per poder llegir els sensor sharp
   
   set_adc_channel(2); //activem la sortida que volem llegir 
   delay_ms(1);
   udreta = read_adc(); //llegim el valor 
   
   set_adc_channel(3); //activem l'altre sortida  
   delay_ms(1);
   uesquerra = read_adc(); //llegim el valor

   delay_ms(100);
   
}

  #INT_TIMER1
void isr_timer1(){
linia();
ulls();
while(ldreta > 200 || lesquerra > 200 || lcentral > 200){
switch(aux){
         case 0:
            output_high(PIN_B1);
            output_high(PIN_B2);
            set_timer1(63973);
            aux=1;
            break;
         
         case 1:
            output_low(PIN_B1);
            output_low(PIN_B2);
            set_timer1(54598);
            aux=0;
            break;
      }
linia();
ulls();
if(udreta >= 70 || uesquerra >= 70){
while(udreta >= 70 || uesquerra >= 70){
   
      switch(aux){
         case 0:
            output_high(PIN_B1);
            set_timer1(63973);
            aux=1;
            break;
         
         case 1:
            output_low(PIN_B1);
            set_timer1(54598);
            aux=0;
            break;
      }
      switch(aux){
         case 0:
            output_high(PIN_B2);
            set_timer1(65223);
            aux=1;
            break;
         
         case 1:
            output_low(PIN_B2);
            set_timer1(53348);
            aux=0;
            break;
      }
      
      
   
}
}
}
linia();
while(ldreta < 100 || lesquerra < 100 || lcentral < 100){
switch(aux){
         case 0:
            output_high(PIN_B2);
            set_timer1(63973);
            aux=1;
            break;
         
         case 1:
            output_low(PIN_B2);
            set_timer1(54598);
            aux=0;
            break;
      }
      switch(aux){
         case 0:
            output_high(PIN_B1);
            set_timer1(65223);
            aux=1;
            break;
         
         case 1:
            output_low(PIN_B1);
            set_timer1(53348);
            aux=0;
            break;
      }
}
}

void main(){

   delay_ms(5000);
   setup_adc(ADC_CLOCK_INTERNAL); //activem el clock intern
   setup_adc_ports(ALL_ANALOG); //activem tots els pins analogics 
   setup_timer_1(T1_INTERNAL|T1_DIV_BY_8); 
   enable_interrupts(INT_TIMER1);
   enable_interrupts(global);    
   
   
   

while(1){
   
}
}
