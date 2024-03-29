#include <16f877.h>                    // Selecciona el PIC
#fuses XT,NOWDT,NOPROTECT,PUT,BROWNOUT // Opciones de configuración
#use delay(clock=20000000)              // Velocidad del Cristal : 4 Mhz
#use rs232(baud=9600, xmit=PIN_C6, rcv=PIN_C7) // Definición del RS232
char Keypress=' ';
byte const NInts=153;                   // Numero de interrupciones para 1 Segundo (CALCULADLO)!!!!!!!!


int16 C_Ints=0;                         // Contador de Interrupciones ocurridas
char Flag=0;      
int contador = 0;  

int x = 1;           // Flag que cambia cada NInts interrupciones
int v = 0;
int vel;


#int_RTCC                              // Interrupción por desbordamiento
void RTCC_isr() {                           // del TIMER0 RTCC

  if(C_Ints > NInts){                  // Si las ints ocurridas > ints para 1 Seg.

    if(Flag==0){
      Flag=1;
    }
    else{
      Flag=0;
    }
    C_Ints=0;                          // Reinicializo Contador de Ints
  }
  ++C_Ints;                            // Incremento el número de interrupciones
}                                      // Ocurridas

#int_rda
void serial_isr() {

  Keypress=0x00;
  if(kbhit()){
    Keypress=getc();
    if(Keypress!=0x00){
    
    
    if(Keypress == 'w'){
      output_high(PIN_D0);
      output_low(PIN_D1);
      set_pwm1_duty(vel);
      printf("vel:%u",vel);
      vel=vel-15;
          set_pwm1_duty(vel);
          printf("vel:%u",vel);
          if(vel<=0){
          vel=125;
          set_pwm1_duty(vel);
          }
        
      }
    
    if(Keypress == 'a'){
          output_high(PIN_D0);
          output_low(PIN_D1);
         set_pwm1_duty(vel);
          printf("vel:%u",vel);
          vel=vel+15;
         set_pwm1_duty(vel);
         printf("vel:%u",vel);
         if(vel>=255){
         vel=125;
         set_pwm1_duty(vel);
         }
        
    }

    if(Keypress == 's'){
         output_low(PIN_D1);
         output_low(PIN_D0);
    }
      putchar(keypress);
      keypress=0x00;
    }
   
   
  }
}
  


void main(void) {
  vel=150;
  setup_CCP1(CCP_PWM);
  setup_timer_2(T2_DIV_BY_16,255,1);
  set_pwm1_duty(vel);
  output_high(PIN_B1);
  
  enable_interrupts(int_rda);
  enable_interrupts(global);
  WHILE(1){
  }
}

