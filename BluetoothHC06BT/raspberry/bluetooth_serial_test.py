#!/usr/bin/python

import serial
from time import sleep

btSerial = serial.Serial("/dev/rfcomm1", baudrate=9600)

btSerial.write("HOLA")
print btSerial.readline()
