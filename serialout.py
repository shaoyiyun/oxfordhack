import serial
import struct
import msft

port = 'COM3'
ser = serial.Serial(port, 9600)

def setColour():

    rgb = msft.speechToText()

    if rgb == [-1]:
        ser.write(struct.pack('>B',0))
        ser.write(struct.pack('>B',0))
    elif rgb == [1] :
        #rainbow
        ser.write(struct.pack('>B',0))
        ser.write(struct.pack('>B',1))
    elif rgb:
        ser.write(struct.pack('>B',0))
        ser.write(struct.pack('>B',rgb[0]))
        ser.write(struct.pack('>B',rgb[1]))
        ser.write(struct.pack('>B',rgb[2]))
    return rgb
