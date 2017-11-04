import serial
ser = serial.Serial('COM3',9600)
ser.write('front.')
ser.close()
