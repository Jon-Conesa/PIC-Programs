#include <16f877.h>                    // Selecciona el PIC
#fuses XT,NOWDT,NOPROTECT,PUT,BROWNOUT // Opciones de configuración
#use delay(clock=20000000)              // Velocidad del Cristal : 4 Mhz
#use rs232(baud=9600, xmit=PIN_C6, rcv=PIN_C7) // Definición del RS232
char Keypress=' ';
byte const NInts=153;                   // Numero de interrupciones para 1 Segundo (CALCULADLO)!!!!!!!!
#define ZERO  0b00111111
#define UNO  0b00000110
#define DOS  0b01011011
#define TRES  0b01001111
#define CUATRO  0b01100110
#define CINCO  0b01101101
#define SEIS  0b01111101
#define SIETE  0b00000111
#define OCHO  0b01111111
#define NUEVE  0b01100111


// VARIABLES GLOBALES

int16 C_Ints=0;                         // Contador de Interrupciones ocurridas
char Flag=0;      
int contador = 0;  
int num[10] = {ZERO,UNO,DOS,TRES,CUATRO,CINCO,SEIS,SIETE,OCHO,NUEVE};   
int x = 1;           // Flag que cambia cada NInts interrupciones
int v = 0;


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
    
      putchar(keypress);
      keypress=0x00;
    }
  }
}

void main(void) {
  char K;
  K=Flag;
  setup_counters(RTCC_INTERNAL,RTCC_DIV_128);// TIMER0: Clock Interno, Presescaler 128
  enable_interrupts(INT_RTCC);               // Habilito Interrupción RTCC
  enable_interrupts(global); 
  enable_interrupts(int_rda);// Habilito Interrupciones



  do{ // Bucle infinito

    if(Flag==K){}
    else
    {                                        // si ha cambiado Flag ...
      printf("Ha pasado un segundo\n\r");
      
      K=Flag;                                // Guardo estado anterior de Flag
    }

  }While(TRUE);
}

