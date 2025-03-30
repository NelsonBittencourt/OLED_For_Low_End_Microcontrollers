/*
 * File:   pic12_oled.h
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


#ifndef pic12f_oled_h
#define	pic12f_oled_h

// *** Defines ***

#define SSD1306_OLED_WIDTH			128     // Display width
#define SSD1306_OLED_HEIGHT			32      // Display height

// ** Select display size (to enable/disable specific code) **
#define SSD1306_128_32						// 128 x 32
//#define SSD1306_128_64                    // 128 x 64
//#define SSD1306_96_16                     // 96 x 16

#define SSD1306_I2C_ADD				0x3C 	// SSD1306 I2C Address (datasheet page 19)
#define SSD1306_DISPLAYOFF			0xAE	// Oled off
#define SSD1306_DISPLAYON			0xAF	// Oled on
#define SSD1306_SETDISPLAYCLOCKDIV	0xD5	// Sets Display Clock Divide Ratio/Oscillator Frequency
#define SSD1306_SETMULTIPLEX		0xA8 	// Sets Multiplex Ratio
#define SSD1306_SETDISPLAYOFFSET	0xD3	// Sets Display Offset
#define SSD1306_SETSTARTLINE		0x40    // Sets Display star line (0x40 to 0x7F, datasheet page 31)
#define SSD1306_CHARGEPUMP			0x8D	// Charge pump control
#define SSD1306_EXTERNALVCC			0x01	// 
#define SSD1306_MEMORYMODE			0x20	// Sets Memory Addressing Mode
#define SSD1306_SEGREMAP			0xA0	// Sets Segment Re-map
#define SSD1306_COMSCANDEC			0xC8	// Sets COM Output Scan Direction
#define SSD1306_SETCOMPINS			0xDA	// Sets COM Pins Hardware Configuration
#define SSD1306_SETCONTRAST			0x81	// Sets constrast
#define SSD1306_SETPRECHARGE		0xD9	// Sets Pre-charge Period
#define SSD1306_SETVCOMDETECT		0xDB	// Sets VCOMH Deselect Level
#define SSD1306_DISPLAYALLON_RESUME	0xA4	// Entire Display ON
#define SSD1306_NORMALDISPLAY		0xA6	// Sets Normal/Inverse Display
#define SSD1306_DEACTIVATE_SCROLL	0x2E	// Deactivate scroll
#define SSD1306_COLUMNADDR			0x21	// Sets Column Address
#define SSD1306_PAGEADDR			0x22	// Sets Page Address
#define SSD1306_SWITCHCAPVCC        0x02    // 


// *** Functions prototypes ***
void ssd1306_position(uint8_t x, uint8_t y);                            // Sets position
void ssd1306_command(uint8_t c);                                        // Sends commands
void ssd1306_init(uint8_t vcc_state, uint8_t i2_addr);                  // Initialize Oled 
void ssd1306_SendChar(char *c, uint8_t start, uint8_t size);            // Writes a string to Oled
void ssd1306_ClearDisplay(void);                                        // Clears Oled

#endif  /* pic12f_oled_h */