/* 
 * File:   common.h
 * Modified by: Ivo Ayala
 *
 *Modified on 05/Oct/2023
 */

#ifndef COMMON_H
#define	COMMON_H

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

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <stdint.h>


//-----------Constants-----------------
#define _XTAL_FREQ 8000000      //Fosc frequency


#endif	/* COMMON_H */

