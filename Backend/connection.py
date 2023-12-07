import serial

try:

    my_serial = serial.Serial("com3",9600)
    
        
    my_serial.close()

except TimeoutError:
    print("Error")
finally:
    print("done")
