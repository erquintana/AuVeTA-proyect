#!/usr/bin/env python3

import serial
import time
import math


class com:

    COMport = '/dev/ttyACM0'
    bautrate = 19200
    arduino = serial.Serial(COMport, bautrate)
    arduino.close()

    arduino.open()
    time.sleep(1)

    f = open("activity_data.csv", "w")
    values0 = arduino.readline().decode('utf-8')
    f.write(values0)
    f.close()

    while True:
        f = open("activity_data.csv", "a")
        values0 = arduino.readline().decode('utf-8')
        f.write(values0)
        f.close()

    arduino.close()
