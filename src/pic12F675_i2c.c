/*
 * File:   pic12F675_i2c.c
 * Author: Nelson Rossi Bittencourt
 *
 * Created on: 03/19/2025
 * I2C by Software for PIC12F675
 * IDE: MPLAB X (6.25)
 * Compiler XC8 (3.00)
 * Version: 0.00  initial release, 'write_i2c' only
 *          0.01  added 'read_i2c' [03/27/2025] 
 * 
 */  

#include <xc.h>    
#include "pic12F675_i2c.h"

// I2C pins configuration
void init_i2c()
{
    scl_high();     // scl on tri-state
    sda_high();     // sda on tri-state
}

// Sends start (S) command
void start_i2c()
{    
    init_i2c();
    
    sda_low();                      // SDA low
    __delay_us(I2C_SDelay);         // Short delay
    scl_low();                      // SCL low
    __delay_us(I2C_SDelay);  
}

// Sends stop (P) command
void stop_i2c()
{       
    scl_high();
    sda_low();
    __delay_us(I2C_SDelay);  
    sda_high();
}

// Writes a byte to I2C bus. Returns ack/nack from slave.
char write_i2c(uint8_t data)
{
    char mask = 0x80;           // Mask to select bits
    char ret = 0;               // Initial value = 0 -> nack from slave
    
    do
	{      
        if(mask & data)         // Changes SDA state for each data bit
            sda_high();
		else
            sda_low();
                        
        scl_high();                  
        __delay_us(I2C_LDelay); // Long delay        
      
        scl_low();              
        __delay_us(I2C_LDelay);         
        mask >>= 1;				// Updates mask
    }
	while(mask > 0);
          
    scl_high();                  
    __delay_us(I2C_LDelay);             
   
    sda_high();                       
    __delay_us(I2C_SDelay);                      
    
    if(SDA_STATE) ret = 1;          // if SDA_STATE is high, ack else nack
                             
    scl_low();                      
    __delay_us(I2C_LDelay);             
    
    sda_low();                      
    __delay_us(I2C_SDelay);        
    
    return ret;                    // return ack(1) or nack(0)                                            
}

//Writes a byte to I2C bus.
uint8_t read_i2c(void)
{
   uint8_t ret;
      
   sda_high();
   
   for (uint8_t n=0; n<8; ++n)
   {      
      scl_high();

      if (SDA_STATE)
        ret = (ret << 1) | 0x01; // msbit first
      else
         ret = ret << 1;      
      scl_low();
    }   
 return ret;
}

// Sets SCL to low level
void scl_low(void)
{
    SCL_TRIS = 0;
    SCL_STATE = 0;
}

// Sets SCL in tri-state (high level by pull-ups in I2C bus)
void scl_high(void)
{
    SCL_TRIS = 1;
}

// Sets SDA to low level
void sda_low(void)
{
    SDA_TRIS=0;
    SDA_STATE = 0;
}

// Sets SDA in tri-state (high level by pull-ups in I2C bus)
void sda_high(void)
{
    SDA_TRIS = 1;
}