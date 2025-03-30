/*
 * File:   main.c
 * Author: Nelson Rossi Bittencourt
 *
 * Created on: 03/21/2025
 * Controlling OLED display (SSD1306) with PIC12F675
 * IDE: MPLAB X (6.25)
 * Compiler XC8 (3.00)
 * Version: 0.00  (initial release without EEPROM data
 *          0.01  Digits (+ '.') and message to EEPROM to free up some program space (03/24/2025)
 * 
 */  


// *** Includes ***
#include "main.h"

// *** EEPROM data ***
// Digits (0 to 9) + '.' on EEPROM (positions 0-55)
__EEPROM_DATA(0x3E,0x51,0x49,0x45,0x3E,0x00,0x42,0x7F);  
__EEPROM_DATA(0x40,0x00,0x72,0x49,0x49,0x49,0x46,0x21);  
__EEPROM_DATA(0x41,0x49,0x4D,0x33,0x18,0x14,0x12,0x7F);
__EEPROM_DATA(0x10,0x27,0x45,0x45,0x45,0x39,0x3C,0x4A);
__EEPROM_DATA(0x49,0x49,0x31,0x41,0x21,0x11,0x09,0x07);
__EEPROM_DATA(0x36,0x49,0x49,0x49,0x36,0x46,0x49,0x49);  
__EEPROM_DATA(0x29,0x1E,0x00,0x00,0x60,0x60,0x00,0xFF);  

// Message "ADC value:" on EEPROM (Position 56-105)
__EEPROM_DATA(0x7C,0x12,0x11,0x12,0x7C,0x7F,0x41,0x41);
__EEPROM_DATA(0x41,0x3E,0x3E,0x41,0x41,0x41,0x22,0x00);
__EEPROM_DATA(0x00,0x00,0x00,0x00,0x1C,0x20,0x40,0x20);
__EEPROM_DATA(0x1C,0x20,0x54,0x54,0x78,0x40,0x00,0x41);
__EEPROM_DATA(0x7F,0x40,0x00,0x3C,0x40,0x40,0x20,0x7C);
__EEPROM_DATA(0x38,0x54,0x54,0x54,0x18,0x00,0x00,0x14);
__EEPROM_DATA(0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF);


// *** Global Vars ***
uint16_t adc_value = 1000;              // Test only
uint8_t th,hu,tn,on;                    // ADC value decomposition (thousand, hundreds.tens, ones)

// *** Functions ***
void main(void) 
{    
    CMCON = 0x07;                       // Disable internal comparators    
    T1CON = 0x00;                       // Timer1 disabled    
    VRCON = 0x00;                       // Disable voltage reference control
    WPU   = 0x00;                       // No weak pull-ups (I2C hardware pull-ups)
    ANSEL = 0x00;                       // Mandatory    	    
    __delay_ms(10);                     // Stabilization time
    
    init_i2c();     
    ssd1306_init(SSD1306_SWITCHCAPVCC,SSD1306_I2C_ADD);     // SSD1306 initialization
    ssd1306_ClearDisplay();                                 // Clear oled display            
    
    ssd1306_position(1,1);                                  // First char and first row
    ssd1306_SendChar(NULL,56,10);                           // Send "ADC value:" message to Oled
   
    while(1)
    {   
        // adc_value decomposition:
        th = adc_value /1000;                               // Thousands
        hu = (adc_value%1000)/100;                          // Hundreds
        tn = (adc_value%100)/10;                            // Tens
        on = adc_value%10;                                  // Ones
        
        // adc_value to display
        ssd1306_position(1,2);                              // First first column and second row

        ssd1306_SendChar(NULL,(5*th),1);                    // Sends thousands
        ssd1306_SendChar(NULL,(5*hu),1);                    // Sends hundreds
        ssd1306_SendChar(NULL,(5*tn),1);                    // Sends tens        
        ssd1306_SendChar(NULL,(5*on),1);                    // Sends ones

        adc_value++;                                        // Updates adc_value        
        __delay_ms(1000); 
    } // while
}   // main
