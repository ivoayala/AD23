/*
 * File:   PWM_4550.c
 * Author: Ivo Ayala
 * Description: PWM output
 *
 * Created on 015/Oct/2023
 */

//-----------Include files-----------------
#include "common.h"

//-----------PORT pins-----------------


//-----------Constants-----------------
#define pauses 1000      //Pause time


//-----------Variables-----------------
int increment = 1;


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
    TRISB = 0b00000000; //Port B direction
    TRISC = 0b00000000; //Port C direction
}


void Config_PWM(){       //Configure PWM CCP1 at PIN 17 (RC2/CCP1/P1A)
    PR2 = 24;                      //PR2 used to calculate PWM period
    T2CONbits.T2CKPS = 0b10;        //Timer2 Clock Prescale Select bits
    
    //*****************CCP1 Duty cycle****************************
    CCPR1L = 4;                    //The Eight MSBs (9 to 2) of the 10-bit PWM duty cycle
    CCP1CONbits.DC1B = 0b00;        //The two LSbs (bit 1 and bit 0) of the 10-bit PWM duty cycle
    
    CCP1CONbits.CCP1M = 0b1100;     //PWM mode  
    
    //*****************CCP2 Duty cycle****************************
    CCPR2L = 4;                    //The Eight MSBs (9 to 2) of the 10-bit PWM duty cycle
    CCP2CONbits.DC2B = 0b00;        //The two LSbs (bit 1 and bit 0) of the 10-bit PWM duty cycle
    
    CCP2CONbits.CCP2M = 0b1100;     //PWM mode  
    
    
    T2CONbits.TMR2ON=1;             //Turn ON Timer2
}


void main(void) {
    OSCCON = 0x72;                  // When internal oscillator in use, 0x72 sets Internal oscillator at 8MHz Frequency
    
    init_ports();                   //Initialize ports
    Config_PWM();                   //Configure PWM
    
    while(1){
        int i;
        for(i=0; i < 20; i++){      //Increment duty cycle
        __delay_ms(pauses);
        CCPR1L += increment; 
        CCPR2L += increment; 
        }
        __delay_ms(pauses);
        CCPR1L = 4;
        CCPR2L = 4;
    };
}
