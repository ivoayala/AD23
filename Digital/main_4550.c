/*
 * File:   main.c
 * Author: Ivo Ayala
 * Device: PIC18F4550
 * Created on September 25, 2023
 */

//-----------Configuration bits-----------------  see: "C:\Program Files\Microchip\MPLABX\v6.05\packs\Microchip\PIC18Fxxxx_DFP\1.3.36\xc8\docs\chips"
// CONFIG1H
#pragma config FOSC = INTOSCIO_EC        // Oscillator Selection bits (Internal oscillator, port function on RA6, EC used by USB (INTIO))

// CONFIG2L
#pragma config PWRT = ON        // Power-up Timer Enable bit (PWRT disabled)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled)

// CONFIG3H
#pragma config PBADEN = OFF     // PORTB A/D Enable bit (PORTB<4:0> pins are configured as digital I/O on Reset)
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

// CONFIG4L
#pragma config LVP = OFF        // Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)


//-----------Include files-----------------
#include <xc.h>
#include <pic18f4550.h>                 //"C:\Program Files\Microchip\MPLABX\v6.05\packs\Microchip\PIC18Fxxxx_DFP\1.3.36\xc8\pic\include\proc\pic18f4550.h"


//-----------Constants-----------------
#define _XTAL_FREQ  8000000      //Fosc frequency for _delay()


//-----------PORT pins-----------------
#define LedA_0      LATAbits.LA0        /*Use "LATA" to set value to port (output) */
#define LedA_1      LATAbits.LA1        /*Use "LATA" to set value to port (output) */
#define LedA_2      LATAbits.LA2        /*Use "LATA" to set value to port (output) */
#define LedA_3      LATAbits.LA3        /*Use "LATA" to set value to port (output) */
#define LedA_4      LATAbits.LA4        /*Use "LATA" to set value to port (output) */
#define LedA_5      LATAbits.LA5        /*Use "LATA" to set value to port (output) */
#define LedA_6      LATAbits.LA6        /*Use "LATA" to set value to port (output) */
#define SW1         PORTBbits.RB0       /*Use "PORTB" to read value from port (input) */
#define SW2         PORTBbits.RB1       /*Use "PORTB" to read value from port (input) */


//-----------Constants-----------------
#define On_Led 500      //Led ON time
#define Off_Led 2500    //Led OFF time

//-----------Variables-----------------
int counter = 0;
int LoopCounter = 0;


//-----------Functions-----------------
void init_ports(){
    LATA = 0x00;        //Clear output data latches, Port A
    LATB = 0x00;        //Clear output data latches, Port B
    LATC = 0x00;        //Clear output data latches, Port C
    ADCON1 = 0x0F;      //All ports as Digital I/O
    ADON = 0;           //A/D converter is disabled
    CMCON = 0x07;       //Comparators OFF
    TRISA = 0b00000000; //Port A direction
    TRISB = 0b00000011; //Port B 
    TRISC = 0b00000000; //Port C direction
    
}

//-----------MAIN-----------------
void main(void) {
    OSCCON = 0x72;                  /* When internal oscillator in use, 0x72 sets Internal oscillator at 8MHz Frequency */
    
    init_ports();                   /*Initialize ports*/
    
    counter = 1;
    
    while(1){         
        LedA_6 = 1;           /* Turn on */
        __delay_ms(On_Led);
          
        LedA_6 = 0;           /* Turn off */
        __delay_ms(Off_Led);
        
         //-----------  If  -----------------       
        if(SW1 == 1){               /* Check if SW1 is pressed */
            LedA_0 = 1;
            __delay_ms(On_Led);
            LedA_0 = 0;
            __delay_ms(On_Led);
        }
        
        //-----------  If .... else  -----------------
        if(SW2 == 1){               /* Check if SW2 is pressed */
            LedA_1 = 1;
            __delay_ms(On_Led);
            LedA_1 = 0;
            __delay_ms(On_Led);
        }
        else{
            LedA_2 = 1;
            __delay_ms(On_Led);
            LedA_2 = 0;
            __delay_ms(On_Led);
        }
        
        //-----------  switch  -----------------
        switch (counter){
            case 1:
                LedA_3 = 1;
                __delay_ms(On_Led);
                LedA_3 = 0;
                __delay_ms(On_Led);
            
            case 2:
                LedA_4 = 1;
                __delay_ms(On_Led);
                LedA_4 = 0;
                __delay_ms(On_Led);
                
            case 3:
                LedA_5 = 1;
                __delay_ms(On_Led);
                LedA_5 = 0;
                __delay_ms(On_Led);
                counter = 0;
                
        }
        counter++;
        
        //-----------  switch  -----------------
        for(LoopCounter = 0;LoopCounter < 8; LoopCounter++){
            LATC = LoopCounter;
            __delay_ms(On_Led);
            LATC = 0x00;
            __delay_ms(On_Led);            
        }
        
       
    }
    return;

}

