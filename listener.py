import serial
import serialout

port = 'COM3'
ser = serial.Serial(port, 9600)

while True :
    out = ser.read(1)
    sserialout.setColour()
    
