import serial
import keyboard as k

try:
    puerto = serial.Serial("COM5", 9600)
    while True:
        if k.is_pressed("1"):
            puerto.write(b'1')
        elif k.is_pressed("2"):
            puerto.write(b'2')
        elif k.is_pressed("3"):
            puerto.write(b'3')
        elif k.is_pressed("4"):
            puerto.write(b'4')
        puerto.close()

except TimeoutError:
    print("Error");

finally:
    print("Error");

