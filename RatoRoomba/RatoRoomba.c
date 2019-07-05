#include <16f877.h>                    // Selecciona el PIC
#fuses XT,NOWDT,NOPROTECT,PUT,BROWNOUT // Opciones de configuraci?n
#use delay(clock=20000000)              // Velocidad del Cristal : 20 Mhz
#use rs232(baud=9600, xmit=PIN_C6, rcv=PIN_C7) // Definici?n del RS232


char opcio;    
int aux=0;                     

#INT_TIMER1
void isr_timer1(){

switch(movimiento){
         case 0:                        // endavant
            switch(aux){
               case 0:                    // si aux es 0 va endavant
               
               output_high(PIN_B2);       // fem un high als dos durant 0,5 ms
               output_high(PIN_B1);
               set_timer1(65223);         
               aux++;                     // cambien l'estat de l'auxiliar
               break;
              
              case 1:
               output_low(PIN_B2);        // un low al connectat al B2 durant 2 ms
               set_timer1(64286);
               aux++;
               break;
               
               case 2:                    // quan cambia l'estat de l'auxiliar
               output_low(PIN_B1);        // es baixa l'estat de l'altre durant 17,5 ms
               set_timer1(54598);        
               aux=0;
               break;
            }
             break;  
          
          case 1:                         // aquesta funcio realitzaria un fre actiu (no usat al programa)
               switch(aux){
               case 0:
               output_high(PIN_B2);
               output_high(PIN_B1);
               set_timer1(64598);
               aux++;
               break;
               
               case 1:
               output_low(PIN_B2);
               output_low(PIN_B1);
               set_timer1(53973);
               aux=0;
               break;
               
               case 2:                    // en cas de que l'auxiliar sigui 2 fara el mateix que si fos 1
               output_low(PIN_B2);
               output_low(PIN_B1);
               set_timer1(53973);
               aux=0;
               break;
               }
               
             break;  
           case 2:                        // enrere
               switch(aux){
               case 0:                    // si aux es 0 va endavant
               output_high(PIN_B2);       // fem un high als dos durant 0,5 ms
               output_high(PIN_B1);
               set_timer1(65223);         
               aux++;                     // cambien l'estat de l'auxiliar
               break;
              
              case 1:
               output_low(PIN_B1);        // un low al connectat al B1 durant 2 ms
               set_timer1(64286);
               aux++;
               break;
               
               case 2:                    // quan cambia l'estat de l'auxiliar
               output_low(PIN_B2);        // es baixa l'estat de l'altre durant 17,5 ms
               set_timer1(54598);         // durant 17,5 ms
               aux=0;
               break;
            }
            break;
            
             case 5:                      // per fer la parada simplement no donarem senyal als motors
               output_low(PIN_B2);
               output_low(PIN_B1);
               break;
               
             case 6:                      // es realitza un gir per a buscar el robot contrari
               
                  switch(aux){
                     case 0:
                     output_high(PIN_B2);          // els dos servos hauran de girar en el mateix sentit
                     output_high(PIN_B1);
                     set_timer1(65223);            // enviem una senyal de 0,5 ms a tots dos
                     aux++;
                     break;
               
                     case 1:
                     output_low(PIN_B2);           // mantenim la senyal al pin_b1 durant aproximadament 1 ms
                     set_timer1(64900);            // d'aquesta manera una roda gira i l'altre es mant? fixa permeten abarcar mes rang de deteccion
                     aux=0;
                     break;
                     case 2:                       
                     output_low(PIN_B1);
                     set_timer1(53973);            // la resta de temps (18,5 ms) mantenim la senyal en low
                     aux=0;
                     break;
                     }
                  break;
                 case 7:                           // un gir en el sentit contrari
                     switch(aux){
                     case 0:
                     output_high(PIN_B2);          // els dos servos hauran de girar en el mateix sentit
                     output_high(PIN_B1);
                     set_timer1(65223);            // enviem una senyal de 0,5 ms a tots dos
                     aux++;
                     break;
               
                     case 1:
                     output_low(PIN_B2);           // la resta (19,5 ms) estaran en estat baix
                     output_low(PIN_B1);
                     set_timer1(53348);
                     aux=0;
                     break;
                     case 2:                       // cap la possibilitat que aux=2 quan entri en aquest cas, per aixo es repeteix la comanda
                     output_low(PIN_B2);           // la resta (19,5 ms) estaran en estat baix
                     output_low(PIN_B1);
                     set_timer1(53348);
                     aux=0;
                     break;
                     }
                     break;
                     
                  case 8:                         // gir en l'altre sentit
                     switch(aux){
                     case 0:
                     output_high(PIN_B2);          // els dos servos hauran de girar en el mateix sentit
                     output_high(PIN_B1);
                     set_timer1(63973);            // enviem una senyal de 2,5 ms a tots dos
                     aux++;
                     break;
               
                     case 1:
                     output_low(PIN_B2);           // la resta (17,5 ms) estaran en estat baix
                     output_low(PIN_B1);
                     set_timer1(54598);
                     aux=0;
                     break;
                     case 2:                       // el mateix que en el cas anterior
                     output_low(PIN_B2);           // la resta (17,5 ms) estaran en estat baix
                     output_low(PIN_B1);
                     set_timer1(54598);
                     aux=0;
                     break;
                  }
                  break;
               }
   
   
}
