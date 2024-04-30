import serial
import time

# Define serial port settings
SERIAL_PORT = '/dev/ttyS0'  # Raspberry Pi's hardware UART serial port
BAUD_RATE = 9600             # Serial communication baud rate

# Initialize serial connection
ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=5)

# Function to send AT commands and receive responses
def send_at_command(command, timeout=1):
    ser.write((command + '\r\n').encode())
    time.sleep(timeout)
    return ser.read_all().decode().strip()

# Configure SIM808 module
send_at_command('AT')  # Test communication
send_at_command('AT+CMGF=1')  # Set SMS text mode
send_at_command('AT+CNMI=2,2,0,0,0')  # Disable SMS notification
send_at_command('AT+CGNSPWR=1')  # Turn on GPS power

# Wait for GPS fix
while True:
    response = send_at_command('AT+CGNSINF')  # Request GPS info
    if '+CGNSINF: 1,1,' in response:  # GPS fix obtained
        break
    time.sleep(5)  # Wait for GPS fix

# Parse GPS coordinates
gps_info = response.split(',')
latitude = gps_info[3]
longitude = gps_info[4]

# Generate Google Maps link
google_maps_link = f'https://maps.google.com/?q={latitude},{longitude}'

# Define recipient phone number
recipient_number = '+1234567890'  # Replace with the phone number of the recipient

# Send SMS message containing Google Maps link
send_at_command(f'AT+CMGS="{recipient_number}"')
ser.write((google_maps_link + chr(26)).encode())
time.sleep(2)  # Wait for message to be sent

# Close serial connection
ser.close()
