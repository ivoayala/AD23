/*
 * File:   main.c
 * Author: Ivo Ayala
 * Device: PIC18F4550
 * Created on September 30, 2023
 * Operation: ADC conversion
 */

//-----------Configuration bits-----------------  see: "C:\Program Files\Microchip\MPLABX\v6.05\packs\Microchip\PIC18Fxxxx_DFP\1.3.36\xc8\docs\chips"
// CONFIG1H
#pragma config FOSC = INTOSCIO_EC        // Oscillator Selection bits (Internal oscillator, port function on RA6, EC used by USB (INTIO))

// CONFIG2L
#pragma config PWRT = ON        // Power-up Timer Enable bit (PWRT disabled)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled)

// CONFIG3H
//#pragma config PBADEN = OFF     // PORTB A/D Enable bit (PORTB<4:0> pins are configured as digital I/O on Reset)
#pragma config PBADEN = ON      // PORTB A/D Enable bit (PORTB<4:0> pins are configured as analog input channels on Reset)
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

// CONFIG4L
#pragma config LVP = OFF        // Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)


//-----------Include files-----------------
#include <xc.h>
#include <pic18f4550.h>                 //"C:\Program Files\Microchip\MPLABX\v6.05\packs\Microchip\PIC18Fxxxx_DFP\1.3.36\xc8\pic\include\proc\pic18f4550.h"


//-----------Constants-----------------
#define _XTAL_FREQ  8000000      //Fosc frequency for _delay()


//-----------PORT pins----------------
#define LedA_6      LATAbits.LA6        /*Use "LATA" to set value to port (output) */


//-----------Constants-----------------
#define On_Led 50      //Led ON time
#define Off_Led 25   //Led OFF time


//-----------Variables-----------------


//-----------Functions-----------------

void init_ports() {
    LATA = 0x00; //Clear output data latches, Port A
    LATB = 0x00; //Clear output data latches, Port B
    LATC = 0x00; //Clear output data latches, Port C
    
    ADCON2bits.ADFM = 0b1;  // A/D Conversion Result Format Select bit. 1 = Right justified
    ADCON2bits.ACQT = 0b010; // A/D Acquisition time select bits. 010 = 4 TAD
    ADCON2bits.ADCS = 0b001; // A/D Conversion Clock Select bits. 001 = FOSC/8

    ADCON1bits.VCFG = 0b00; //Voltage reference configuration. 00 = Vss, Vdd.
    ADCON1bits.PCFG = 0b1110; //A/D Port Configuration Control bits. 1111= AN0 Analoge

    ADCON0bits.ADON = 0b0;  // A/D On. 0 = A/D converter module is disabled

    CMCON = 0x07;           //Comparators OFF
    
    TRISA = 0b00000001;     //Port A direction. RA0/AN0 as input
    TRISB = 0b00000000;     //Port B 
    TRISC = 0b00000000;     //Port C direction

}


//-----------MAIN-----------------

void main(void) {
    OSCCON = 0x72; /* When internal oscillator in use, 0x72 sets Internal oscillator at 8MHz Frequency */

    init_ports(); /*Initialize ports*/

    while (1) {
        LedA_6 = 1; /* Turn on */
        __delay_ms(On_Led);

        //-----------  ADC conversion (START) ----------------- 
        ADCON0bits.CHS = 0b0000; // Analog Channel Select bits. 0000 = Channel 0 (AN0/RA0)
        ADCON0bits.ADON = 0b1; // A/D On.1 = A/D converter module is enabled
        ADCON0bits.GO = 0b1; //Start conversion

        /*wait for End of conversion Go=1 conversion completed*/
        while (ADCON0bits.GO == 1);

        LATB = ADRESL;          //Move ADC data to PORTB and PORTC
        LATC = ADRESH;

        __delay_ms(On_Led);
        ADCON0bits.ADON = 0b0; // A/D On. 0 = A/D converter module is disabled
        //-----------  ADC conversion (END)----------------- 

        LedA_6 = 0; /* Turn off */
        __delay_ms(On_Led);

    }
    return;

}

