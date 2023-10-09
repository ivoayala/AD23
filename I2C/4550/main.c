/*
 * File:   main.c
 * Author: Ivo Ayala with  code from hammond
 *
 * Created on 01/Oct/2023
 * Modified from; https://github.com/kiwih/pic16f877a-ssd1306-oled/tree/master
 */


//-----------Include files-----------------
#include "common.h"
#include "i2c.h"
#include "ssd1306_unbuffered.h"
#include <stdlib.h>
#include <stdio.h>


//-----------PORT pins-----------------


//-----------Constants-----------------
#define Delay_short 500      //Delay
#define Delay_long 1000    //Delay
#define TRUE 1
#define FALSE 0 


//-----------Variables-----------------
int counter = 0;


//-----------Functions-----------------
void init_ports(){
    LATA = 0x00;        //Clear output data latches, Port A
    LATB = 0x00;        //Clear output data latches, Port B
    LATC = 0x00;        //Clear output data latches, Port C
    ADCON1 = 0x0F;      //All ports as Digital I/O
    ADCON0bits.ADON= 0; //A/D converter is disabled
    CMCONbits.CM = 0b000;   //Comparator Mode. 0b000= Comparators off
    TRISA = 0b00000000; //Port A direction
    TRISB = 0b00000011; //Port B. PORTB<1:0> as input for SDA and SCL
    TRISC = 0b00000000; //Port C direction
    
}

void oled_puts(const char* c, uint8_t size) {
    while(*c != '\0') {
        SSD1306_PutStretchC(*c, size);
        c++;
    }
}


//-----------MAIN-----------------
void main(void) {
    OSCCON = 0x72;                  /* When internal oscillator in use, 0x72 sets Internal oscillator at 8MHz Frequency */

    init_ports();
    
    __delay_ms(Delay_long);

    
    I2C_Initialize(2000);       //I2C speed 200Khz
    
    SSD1306_Init(SSD1306_SWITCHCAPVCC, SSD1306_I2C_ADDRESS);
    // clear the display
    SSD1306_ClearDisplay();

    
    while(1) {
         
        //SSD1306_InvertDisplay(0);       //Invert color
        //SSD1306_FillScreen();

        SSD1306_GotoXY(1,1);
        char str[20];
        sprintf(str, "%u", counter);
        //sprintf(str, "%u.%u", counter / 10, value % 10);
        oled_puts(str, 1);
        
        SSD1306_GotoXY(6,1);
        oled_puts("Mecatronica", 1);
        SSD1306_GotoXY(1,2);
        oled_puts("the", 2);
        SSD1306_GotoXY(5,2);
        oled_puts("best", 3);
        SSD1306_GotoXY(20,3);
        oled_puts("at", 1);
        SSD1306_GotoXY(3,5);
        oled_puts("TEC", 4);
        __delay_ms(Delay_long);
        SSD1306_ClearDisplay();
        
        counter++;
        
    }

    return;
}
