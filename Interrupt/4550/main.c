/*
 * File:   main.c
 * Author: Ivo Ayala
 * Device: PIC18F4550
 * Created on Oct 05, 2023
 * Description: Simple Interrupt routine. INT0 External Interrupt 
 */

//-----------Include files-----------------
#include "common.h"


//-----------PORT pins-----------------
#define LedA_0      LATAbits.LA0        /*Use "LATA" to set value to port (output) */
#define LedA_1      LATAbits.LA1        /*Use "LATA" to set value to port (output) */
#define LedA_5      LATAbits.LA5        /*Use "LATA" to set value to port (output) */
#define LedA_6      LATAbits.LA6        /*Use "LATA" to set value to port (output) */
#define SW1         PORTBbits.RB0       /*Use "PORTB" to read value from port (input) */
#define SW2         PORTBbits.RB1       /*Use "PORTB" to read value from port (input) */


//-----------Constants-----------------
#define On_Led 1000     //Led ON time
#define Off_Led 1000    //Led OFF time


//-----------Variables-----------------



//-----------Functions-----------------
void init_ports(){
    LATA = 0x00;        //Clear output data latches, Port A
    LATB = 0x00;        //Clear output data latches, Port B
    LATC = 0x00;        //Clear output data latches, Port C
    LATD = 0x00;        //Clear output data latches, Port D
    LATE = 0x00;        //Clear output data latches, Port E
    ADCON1 = 0x0F;      //All ports as Digital I/O
    ADON = 0;           //A/D converter is disabled
    CMCON = 0x07;       //Comparators OFF
    TRISA = 0b00000000; //Port A direction
    TRISB = 0b00000011; //Port B direction
}

void Config_Interrupts(){       //Configure Interrupts
    INT0IE = 0b1;               //INT0IE: INT0 External Interrupt Enable bit. 1 = Enables the INT0 external interrupt
    INTEDG0 = 0b1;              //INTEDG0: External Interrupt 0 Edge Select bit. 1 = Interrupt on rising edge
}

void __interrupt(high_priority) MyInterruptRoutine(void){       //Interrupt Service Routine
    GIE = 0b0;                  //Disable Global Interrupt Enable bit. 
    
    if(INT0IF == 0b1){          //Check if External Interrupt 0 caused the interrupt
        INT0IF = 0b0;           //Clear external interrupt flag
        LedA_5 = 1;             /* Turn on */
        LedA_6 = 1;
        __delay_ms(On_Led);
        LedA_5 = 0;             /* Turn off */
        LedA_6 = 0;
    }
    
    GIE = 0b1;                  //Enable Global Interrupt Enable bit. 
}

//-----------MAIN-----------------
void main(void) {
    OSCCON = 0x72;                  // When internal oscillator in use, 0x72 sets Internal oscillator at 8MHz Frequency
    
    init_ports();                   //Initialize ports
    Config_Interrupts();            //Configure Interrupts
    
    GIE = 0b1;                      //Enable Global Interrupt Enable bit. 
    
    
    while(1){         
        LedA_0 = 1;           /* Turn on */
        LedA_1 = 1;           /* Turn on */
        __delay_ms(On_Led);
          
        LedA_0 = 0;           /* Turn off */
        LedA_1 = 0;           /* Turn on */
        __delay_ms(Off_Led);
              
    }
    return;

}
