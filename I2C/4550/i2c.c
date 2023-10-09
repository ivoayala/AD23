#include "i2c.h"

void I2C_Initialize(const unsigned long feq_K) //Begin IIC as master
{
  TRISBbits.RB0 = 1;  
  TRISBbits.RB1 = 1;            //Set SDA and SCL pins as input pins
  
  SSPCON1 = 0b00101000;         /* Enable SSP port for I2C Master mode,
                                clock = FOSC / (4 * (SSPADD+1))*/ 
  SSPCON2 = 0b00000000;    

  SSPADD = (_XTAL_FREQ/(4*feq_K*100))-1; //Setting Clock Speed 
  
  SSPSTAT = 0b00000000;         //
 
}

void I2C_Hold()
{
    while (   (SSPCON2 & 0b00011111)    ||    (SSPSTAT & 0b00000100)   ) ; //check the this on registers to make sure the IIC is not in progress
}

void I2C_Begin()
{
  I2C_Hold();                   //Hold the program is I2C is busy 
  SEN = 1;                      //Begin IIC 
}
void I2C_End()
{
  I2C_Hold();                   //Hold the program is I2C is busy 
  PEN = 1;                      //End IIC
}

void I2C_Write(unsigned data)
{
  I2C_Hold();                   //Hold the program is I2C is busy
  SSPBUF = data;                //
}

unsigned short I2C_Read(unsigned short ack)
{
  unsigned short incoming;
  I2C_Hold();
  RCEN = 1;

  I2C_Hold();
  incoming = SSPBUF;            //get the data saved in SSPBUF

  I2C_Hold();
  ACKDT = (ack)?0:1;            //check if ack bit received 
  ACKEN = 1;                    //

  return incoming;
}
