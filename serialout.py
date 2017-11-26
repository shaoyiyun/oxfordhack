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
    elif len(rgb) == 2 :
        #sound
        ser.write(struct.pack('>B',0))
        ser.write(struct.pack('>B',rgb[0]))
        #if (rgb[0] != 5):
        ser.write(struct.pack('>B',rgb[1]))
        #else :
        #   ser.write(struct.pack('>B',rgb[1]/256))
        #   ser.write(struct.pack('>B',rgb[1]%256))
    elif rgb:
        ser.write(struct.pack('>B',0))
        ser.write(struct.pack('>B',rgb[0]))
        ser.write(struct.pack('>B',rgb[1]))
        ser.write(struct.pack('>B',rgb[2]))
    return rgb


#while True :
 #   out = ser.read()
  #  print(out)
   # if out == bytes([1]):
    #    setColour()

