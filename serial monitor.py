import serial
import time

# Set up the serial connection
arduino_port = "COM4"  # Adjust this to your Arduino port
baud_rate = 9600  # Ensure this matches the baud rate in your Arduino sketch

# Create a serial object
ser = serial.Serial(arduino_port, baud_rate, timeout=1)

# Allow some time for the connection to establish
time.sleep(2)

try:
    while True:
        # Read a line from the serial port
        if ser.in_waiting > 0:
            line = ser.readline().decode('utf-8').rstrip()
            print(f"Received: {line}")
except KeyboardInterrupt:
    print("Exiting Program")

# Close the serial connection
finally:
    ser.close()