/*
 * File:   main.h
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

#ifndef MAIN_H
#define	MAIN_H

// *** PIC12F675 configuration word ***
// *****************************************************************************
#pragma config FOSC = INTRCIO   // Oscillator Selection bits (INTOSC oscillator: I/O function on GP4/OSC2/CLKOUT pin, I/O function on GP5/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = ON       // Power-Up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // GP3/MCLR pin function select (GP3/MCLR pin function is digital I/O, MCLR internally tied to VDD)
#pragma config BOREN = OFF      // Brown-out Detect Enable bit (BOD enabled)
#pragma config CP = OFF         // Code Protection bit (Program Memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma switch speed            // Use the fastest switch method;

#include <xc.h>                 // include processor files - each processor file is guarded.
#include "pic12F675_i2c.h"      // I2C header
#include "pic12_oled.h"         // Oled I2C

#endif	/* MAIN_H */

