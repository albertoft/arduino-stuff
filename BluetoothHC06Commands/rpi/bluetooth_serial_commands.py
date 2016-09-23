#!/usr/bin/python
import serial

btSerial = serial.Serial("/dev/rfcomm1", baudrate=9600)

#send command "7"
btSerial.write("#7")

#fetch response from arduino
print btSerial.readline()
