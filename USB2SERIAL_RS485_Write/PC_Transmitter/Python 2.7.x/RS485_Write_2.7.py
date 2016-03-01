#----------------------------------------------------------------------------------------------------#
# RS485 Communication using Python (Write) (hardware = USB2SERIAL)  (Python 2.7.x)                   #
#----------------------------------------------------------------------------------------------------#
#Program runs on the PC side and transmits a character to the Serial Port @9600bps .Program uses     #
#PySerial module to communicate with Serial Port  of USB2SERIAL                                      #
#----------------------------------------------------------------------------------------------------# 
# BaudRate     -> 9600                                                                               #
# Data formt   -> 8 databits,No parity,1 Stop bit (8N1)                                              #
# Flow Control -> None                                                                               #
#----------------------------------------------------------------------------------------------------#

#====================================================================================================#
# www.xanthium.in										                                             #
# Copyright (C) 2015 Rahul.S                                                                         #
#====================================================================================================#

#====================================================================================================#
# Interpreter/IDE  : Python 2.7.x/IDLE     	                                                     #
# Module           : PySerial                                                                        #                                                                                                    #
# OS               : Windows(Windows 7)/Linux                                                        #
# Programmer       : Rahul.S                                                                         #
# Date	           : 31-March-2015                                                                   #
#====================================================================================================#

#====================================================================================================#
# Finding out the serial port number corresponding to your Computer                                  #
#====================================================================================================#
# On Linux                                                                                           #
#----------------------------------------------------------------------------------------------------#
# USB2SERIAL will be detected as ttyUSB0 or ttyUSB1.You can check the port number of USB2SERIAL by   #
# connecting you board to USB port and doing                                                         #
#                   dmesg | tail                                                                     #
# and checking the output.                                                                           #
#====================================================================================================#

#====================================================================================================#
# Running the Program                                                                                #
#====================================================================================================#
# On Linux                                                                                           #
#----------------------------------------------------------------------------------------------------#
# Find out your serial port name and number corresponding to USB2SERIAL on your system.It will be-   # 
# -usually in the form of ttyUSB0 and ttyUSB1.                                                       #
# Open terminal and type the following command to invoke Python3.x interpretor                       #
# [user@linux:~$] sudo python RS485_Write.py                                                         #
# Give the password and then enter your portnumber when program asks ->/dev/ttyUSB0                  #
#----------------------------------------------------------------------------------------------------#
# On Windows                                                                                         #
#----------------------------------------------------------------------------------------------------#
# Open the command prompt and type the following                                                     #
#  C:\>python RS485_Write.py                                                                         #       
# Enter the COM number when program asks -> com31                                                    #            
#====================================================================================================#

import serial                          # import the module 

def banner_top():
	print '   +-------------------------------------------+'
	print '   |   USB2SERIAL RS485 Write in Python 2.7.x  |'
	print '   |          (c) www.xanthium.in              |'
	print '   +-------------------------------------------+'

def Usage():
	print '   | Windows -> COMxx     eg COM32             |'
	print '   | Linux   ->/dev/ttyS* eg /dev/ttyUSB0      |'
	print '   +-------------------------------------------+'
	
def banner_bottom():
	print '   +-------------------------------------------+'
	print '   |          Press Any Key to Exit            |'
	print '   +-------------------------------------------+'

banner_top()                           # Display the top banner
Usage()
COM_PortName = raw_input('\n    Enter the COM Port Name ->')

#Opening the serial port

COM_Port = serial.Serial(COM_PortName) # open the COM port
print '\n   ',COM_PortName,'Opened' 

COM_Port.baudrate = 9600               # set Baud rate 
COM_Port.bytesize = 8                  # Number of data bits = 8
COM_Port.parity   = 'N'                # No parity
COM_Port.stopbits = 1                  # Number of Stop bits = 1

print '\n    Baud rate = ',COM_Port.baudrate
print '    Data bits = ',COM_Port.bytesize
print '    Parity    = ',COM_Port.parity
print '    Stop bits = ',COM_Port.stopbits

#Controlling DTR and RTS pins to put USB2SERIAL in transmit mode

COM_Port.setDTR(0) #DTR=0,~DTR=1 so DE = 1,Transmit mode enabled
COM_Port.setRTS(0) #RTS=0,~RTS=1 (In FT232 RTS and DTR pins are inverted)

print '\n    DTR = 0,~DTR = 1 so DE = 1,Transmit mode enabled'
print '    RTS = 0,~RTS = 1'
      
#Write character 'A' to serial port                            
data = bytearray(b'A')                       # Convert Character to byte array 
NoOfBytes  = COM_Port.write(data)            # Write data to serial port

print '\n   ',NoOfBytes,' bytes written'
print '\n    A written to',COM_PortName
      
COM_Port.close()                       # Close the Serial port

banner_bottom()                        # Display the bottom banner
dummy = raw_input()                        # press any key to close 
