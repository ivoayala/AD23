/*
 * File:   main.c
 * Author: Ivo Ayala
 * Device: PIC18F45k50
 * Description: ADC
 *
 * Created on September 30, 2023
 */

//-----------Configuration bits-----------------  see: "C:\Program Files\Microchip\MPLABX\v6.05\packs\Microchip\PIC18Fxxxx_DFP\1.3.36\xc8\docs\chips"
// CONFIG1H
#pragma config FOSC = INTOSCIO  // Oscillator Selection (Internal oscillator)

// CONFIG2L
#pragma config nPWRTEN = OFF    // Power-up Timer Enable (Power up timer disabled)

// CONFIG2H
#pragma config WDTEN = OFF      // Watchdog Timer Enable bits (WDT disabled in hardware (SWDTEN ignored))

// CONFIG3H
#pragma config PBADEN = ON      // PORTB A/D Enable bit (PORTB<5:0> pins are configured as analog input channels on Reset)
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

// CONFIG4L
#pragma config LVP = OFF        // Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)


//-----------Include files-----------------
#include <xc.h>                 //"C:\Program Files\Microchip\MPLABX\v6.05\packs\Microchip\PIC18Fxxxx_DFP\1.3.36\xc8\pic\include\proc\pic18f4550.h"


//-----------Constants-----------------
#define _XTAL_FREQ  8000000      //Fosc frequency for _delay()


//-----------PORT pins-----------------
#define LedA_6      LATAbits.LA6        /*Use "LATA" to set value to port (output) */


//-----------Constants-----------------
#define On_Led 50      //Led ON time
#define Off_Led 25    //Led OFF time


//-----------Variables-----------------


//-----------Functions-----------------
void init_ports(){
    LATA = 0x00;        //Clear output data latches, Port A
    LATB = 0x00;        //Clear output data latches, Port B
    LATC = 0x00;        //Clear output data latches, Port C
    
    ADCON2bits.ADFM = 0b1;  // A/D Conversion Result Format Select bit. 1 = Right justified
    ADCON2bits.ACQT = 0b010; // A/D Acquisition time select bits. 010 = 4 TAD
    ADCON2bits.ADCS = 0b001; // A/D Conversion Clock Select bits. 001 = FOSC/8
    
    ADCON1bits.PVCFG = 0b00; //Positive Voltage Reference Configuration bits. 00 = A/D VREF+ connected to internal signal, AVDD
    ADCON1bits.NVCFG = 0b00; //Negative Voltage Reference Configuration bits. 00 = A/D VREF- connected to internal signal, AVSS
 
    TRISA = 0b00000000; //Port A direction
    TRISB = 0b00000011; //Port B 
    TRISD = 0b00000000; //Port C direction
    
    ANSELA = 0b00000001;      //ANSA<5><3:1> digital buffer enabled. ANSA<0> Digital input buffer disabled
    
    ADCON0bits.ADON = 0b0;  // A/D On. 0 = ADC is disabled and consumes no operating current
           
}

//-----------MAIN-----------------
void main(void) {
    OSCCON = 0x62;                  /* When internal oscillator in use*/
                                    /*0x62 sets Internal oscillator to 8MHz Frequency (PIC18F45k50) */
    
    init_ports();
    
    
 while (1) {
        LedA_6 = 1; /* Turn on */
        __delay_ms(On_Led);

        //-----------  ADC conversion (START) ----------------- 
        ADCON0bits.CHS = 0b00000; // Analog Channel Select bits. 00000 = AN0/RA0
        ADCON0bits.ADON = 0b1; // A/D On.1 = A/D converter module is enabled
        ADCON0bits.GO = 0b1; //Start conversion

        /*wait for End of conversion Go=1 conversion completed*/
        while (ADCON0bits.GO == 1);

        LATB = ADRESL;          //Move ADC data to PORTB and PORTD
        LATD = ADRESH;

        __delay_ms(On_Led);
        ADCON0bits.ADON = 0b0; // A/D On. 0 = A/D converter module is disabled
        //-----------  ADC conversion (END)----------------- 

        LedA_6 = 0; /* Turn off */
        __delay_ms(On_Led);

    }
    return;
}
