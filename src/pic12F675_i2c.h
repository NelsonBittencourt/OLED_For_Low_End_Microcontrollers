/*
 * File:   pic12F675_i2c.h
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


#ifndef pic12f675_i2c_h
#define	pic12f675_i2c_h

#define _XTAL_FREQ  4000000                 // Mandatory for __delay_us function
#define SCL_TRIS    TRISIO0                 // SCL pin mode
#define SDA_TRIS    TRISIO1                 // SCA pin mode
#define SCL_STATE   GPIO0                   // SCL pin state
#define SDA_STATE   GPIO1                   // SCA pin state
#define I2C_LDelay  10                      // I2C long delay time (us)
#define I2C_SDelay  1                       // I2C short delay time (us)

void init_i2c(void);						// I2C pins configuration
void start_i2c(void);						// Sends I2C start command
void stop_i2c(void);						// Sends I2C stop command
char write_i2c(uint8_t data);				// Writes a byte to I2C bus. Returns ack/nack from slave
//uint8_t read_i2c(void);                     // Reads a byte to I2C bus. Returns ack/nack from slave
void scl_low(void);                         // Sets SCL to low level
void scl_high(void);                        // Sets SCL in tri-state (high level by pull-ups in I2C bus)
void sda_low(void);                         // Sets SDA to low level
void sda_high(void);                        // Sets SDA in tri-state (high level by pull-ups in I2C bus)

#endif  // *pic12f675_i2c_h*
