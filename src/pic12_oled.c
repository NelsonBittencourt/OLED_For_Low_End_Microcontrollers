/*
 * File:   pic12_oled.c
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
#include <xc.h>                                 // XC8 header
#include "pic12F675_i2c.h"
#include "pic12_oled.h"                         


// *** Global vars ***
uint8_t pos_x, pos_y;                           // Display position
uint8_t _vcc_state;                             // Display _vcc_state
uint8_t _i2c_addr;                              // Display I2C address


// *** Functions ***

// Sets Oled position
void ssd1306_position(uint8_t x, uint8_t y)
{	
	pos_x = x;
	pos_y = y;
}

// Sends SSd1306 commands
void ssd1306_command(uint8_t c) 
{   
    start_i2c();				// Starts I2C
    write_i2c(_i2c_addr);       // Sends ssd1306 addrees
    write_i2c(0x00);            // Signals that next byte will be a command, not data
    write_i2c(c);				// Sends command    
    stop_i2c();    				// Stops I2C
}

// Initialize Oled
void ssd1306_init(uint8_t vcc_state, uint8_t i2c_addr)
{    
	_vcc_state = vcc_state;
    _i2c_addr  = i2c_addr<<1;                               //    
    
    // OLED configuration (datasheet page 5, item 3)
    ssd1306_command(SSD1306_DISPLAYOFF);                    // 0xAE - Oled off
    
	ssd1306_command(SSD1306_SETDISPLAYCLOCKDIV);            // 0xD5 - Datasheet page 32
    ssd1306_command(0x80);                                  // Current freq and clock div values

    ssd1306_command(SSD1306_SETMULTIPLEX);                  // 0xA8
    ssd1306_command(SSD1306_OLED_HEIGHT - 1);				// Mux defined with display height

    ssd1306_command(SSD1306_SETDISPLAYOFFSET);              // 0xD3
    ssd1306_command(0x00);                                  // No offset
    
	ssd1306_command(SSD1306_SETSTARTLINE | 0x00);           // Start line at 00
    
	ssd1306_command(SSD1306_CHARGEPUMP);                    // 0x8D

	if (_vcc_state == SSD1306_EXTERNALVCC)
	{ 
        ssd1306_command(0x10); 
    }
    else
	{ 
        ssd1306_command(0x14); 								// Charge pump enabled
    }
    
	ssd1306_command(SSD1306_MEMORYMODE);                    // 0x20
    ssd1306_command(0x00);              					// 0x0 (horizontal addressing mode)
    ssd1306_command(SSD1306_SEGREMAP | 0x01);				// 
    ssd1306_command(SSD1306_COMSCANDEC);					//

    // Oled with 128 x 32
    #if defined SSD1306_128_32
        ssd1306_command(SSD1306_SETCOMPINS);                // 0xDA
        ssd1306_command(0x02);                              // 0x02 -> 0b10 -> alternative configuration; left/right remap
        ssd1306_command(SSD1306_SETCONTRAST);               // 0x81
        ssd1306_command(0xFF);								// Contrast value (0 - 255)

    // OLed with 128 x 64
    #elif defined SSD1306_128_64
        ssd1306_command(SSD1306_SETCOMPINS);                // 0xDA
        ssd1306_command(0x12);
    
        if (_vcc_state == SSD1306_EXTERNALVCC)
        {
            ssd1306_command(0x9F);
        }
        else
        {
            ssd1306_command(0xCF); 
        }

    // Oled with 96 x 16
    #elif defined SSD1306_96_16
        ssd1306_command(SSD1306_SETCOMPINS);                // 0xDA
        ssd1306_command(0x02);                               // ada x12
        ssd1306_command(SSD1306_SETCONTRAST);               // 0x81
        if (_vcc_state == SSD1306_EXTERNALVCC)
        { 
            ssd1306_command(0x10); 
        }
        else
        {
            ssd1306_command(0xAF); 
        }
    #endif

    ssd1306_command(SSD1306_SETPRECHARGE);                  // 0xD9
    if (_vcc_state == SSD1306_EXTERNALVCC)
	{
        ssd1306_command(0x22); 								// Default
    }
    else
	{
        ssd1306_command(0xF1); 
    }
    
	ssd1306_command(SSD1306_SETVCOMDETECT);                 // 0xDB
    ssd1306_command(0x20);									// Set VCOMH Deselect Level (default 0x20)
    
	ssd1306_command(SSD1306_DISPLAYALLON_RESUME);           // 0xA4
    ssd1306_command(SSD1306_NORMALDISPLAY);                 // 0xA6

    ssd1306_command(SSD1306_DEACTIVATE_SCROLL);				// 0x2E
    ssd1306_command(SSD1306_DISPLAYON);                     // 0xAF
} // ssd1306_init


// Writes chars to ssd1306 memory
void ssd1306_SendChar(char *c, uint8_t start, uint8_t size)
{   
    for (uint8_t z=start; z<(5*size)+start; z+=5)               
    {
        ssd1306_command(SSD1306_COLUMNADDR);                // Column start and end addresses
        ssd1306_command(6 * (pos_x - 1));        
        ssd1306_command(6 * (pos_x - 1) + 4);
        
        ssd1306_command(SSD1306_PAGEADDR);                  // Page start and end addresses
        ssd1306_command(pos_y - 1); 
        ssd1306_command(pos_y - 1); 

        start_i2c();                                        // Starts I2C
        write_i2c(_i2c_addr);                               // Sends slave address
        write_i2c(0x40);                                    // Sends 0b01000000 (Co=0; D=1 - Figure 8.7, page 20)                                                            
        
        // if 'c' is not null, sends data from program memory ('c' contents)
        if (c) 
            for(uint8_t i = 0; i < 5; ++i) write_i2c(c[i+z]);           // Sends 'c' content
        else 
            for(uint8_t i = 0; i < 5; ++i) write_i2c(eeprom_read(i+z)); // Sends eeprom content
        
        stop_i2c();                                                     // Stops i2c                        
        pos_x++;                                                       // Updates pos_x        
    } // for z
} // ssd1306_SendChar


// Clear Oled
void ssd1306_ClearDisplay(void)
{
    // Sets column initial address
    ssd1306_command(SSD1306_COLUMNADDR);    
    ssd1306_command(0);        
    
    // Sets columns final address
    #if defined SSD1306_128_64 || defined SSD1306_128_32
        ssd1306_command(127);  
    #else
        ssd1306_command(95); 
    #endif

    // Sets row initial address    
    ssd1306_command(SSD1306_PAGEADDR);
    ssd1306_command(0);   // 

    // Sets row final address    
    #if defined SSD1306_128_64
        ssd1306_command(7);   
    #elif defined SSD1306_128_32
        ssd1306_command(3);   
    #elif defined SSD1306_96_16
        ssd1306_command(1);   
    #endif

    start_i2c();
    write_i2c(_i2c_addr);
    write_i2c(0x40);

    // Sends '0' for all columns and rows
    for(uint16_t i = 0; i < (SSD1306_OLED_HEIGHT * SSD1306_OLED_WIDTH) / 8; i++ )
       write_i2c(0);

    stop_i2c();
} // ssd1306_ClearDisplay


