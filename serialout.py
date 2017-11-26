import serial

import msft

def setColour():
    port = 'COM3'

    rgb = msft.speechToText()

    ser = serial.Serial(port, 9600)


    if rgb:
        ser.write(0xff)
        ser.write(rgb[0])
        ser.write(rgb[1])
        ser.write(rgb[2])
    return rgb
