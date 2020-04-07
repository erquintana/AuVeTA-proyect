#!/usr/bin/env python3

import serial
import time
import matplotlib.pyplot as pyplot
import math
import csv

COMport = '/dev/ttyACM0'
bautrate = 19200
arduino = serial.Serial(COMport, bautrate)
arduino.close()

arduino.open()
time.sleep(1)


while True:
    values0 = arduino.readline().decode("utf-8")
    
arduino.close()
