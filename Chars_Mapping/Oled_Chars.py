# -*- coding: utf-8 -*-

"""
******************************************************************************

Description: Python script to convert a message string to array of bytes to 
SSD1306 based  displays
              
Author   : Nelson Rossi Bittencourt
Version  : 0.0
License : MIT
Dependencies: none

******************************************************************************
"""


# *** Input data ***

message = 'ADC value:'                                      # Message to convert
file_name = 'Oled_Chars.txt'                                # Oled chars file


# *** Variables initialization ***

message_sz = len(message)                                   # Lenght of message
oled_chars = {}                                             # Dictionary of Oled chars
ordinal = 0                                                 # Auxiliary integer value

eeprom_chunck_sz = 8                                        # PIC eeprom chunck size (MPLAB X command '__EEPROM_DATA' requires 8 arguments)
eeprom_null_value = '0xFF'                                  # PIC eeprom null value 
msg_eeprom = ''                                             # Final eeprom msg to paste into c code
msg_eeprom_prefix = '__EEPROM_DATA('                        # Prefix for each line of data (8 bytes per line in MPLAB X)

msg_ram = 'const char message[' + str(5*message_sz) + ']={' # Prefix for ram message 
tmp_ram = ''                                                # Ram message (to paste into conde)


# *** Creates Oled chars dictionary ***

with open(file_name, 'rt') as f:                            # Opens Oled chars file
    while(line:=f.readline()):                              # Read each file line
        oled_chars[ordinal+32] = line.strip()               # Creates oled_chars dictionary { 'ordinal' +32 ; 8 bytes for a Oled char}
        ordinal+=1                                          # Updates ordinal
f.close()                                                   # Closes Oled chars file


# *** Creating ram (program memory) declaration ***

for c in message:                                           # Scans message 
    tmp_ram+=str(oled_chars[ord(c)]) + ','                  # Creates a tmp var with 8 bytes, comman separated

tmp_ram=tmp_ram[:-1]                                        # Removes last comma from tmp_ram
msg_ram+= tmp_ram + '};'                                    # Creates ram message


# *** Creating eeprom message declaration ***

full_lines = int((5*message_sz)/eeprom_chunck_sz)           # Number of complete (= 8 bytes) rows
lack_bytes = (5*message_sz)%8                               # Number of lacking bytes

if lack_bytes>0:                                            # If there are imcomplete rows                          
    full_lines+=1                                           # Increments full_lines

    tmp_ram+= (',' + (eeprom_null_value + ',')              # Appends 'eeprom_null_value' values to fullfill incomplete row
               * (eeprom_chunck_sz-lack_bytes))


for ee in range(0,full_lines):                              # For each full_line
    tmp_eeprom = (msg_eeprom_prefix + tmp_ram[ee*40:        # Creates a tmp string with eeprom command + 8 bytes
                 (ee*40+eeprom_chunck_sz*5)-1] + ');')
    msg_eeprom+=tmp_eeprom + '\n'                           # Appends newline for each row


print (msg_ram)                                             # Shows ram declaration
print (msg_eeprom)                                          # Shows eeprom declaration

    
    



