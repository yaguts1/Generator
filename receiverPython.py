import serial
import csv
import os

serialPort = serial.Serial("COM7", baudrate=115200)
arduinoData = serialPort.readline()
try:
    os.rename('output.csv', 'ALTERAR_MEU_NOME.csv')
except IOError:
    print('')
finally:
    
    
    while(True):
        arduinoData = serialPort.readline().decode("ascii")
        print(arduinoData)
    #add the data to the file
        file = open("output.csv", "a") #append the data to the file
        file.write(arduinoData) #write data with a newline
    #close out the file
    file.close()
