import serial
import time

def send_command(port, command, response_length=10, delay=1):
    """
    Send an AT command to the modem and read the response.

    Parameters:
        port (Serial): The serial port object for communication.
        command (str): The AT command to be sent.
        response_length (int): The expected length of the response.
        delay (int): The delay (in seconds) after sending the command.

    Returns:
        str: The response received from the modem.
    """
    port.write((command + '\r\n').encode())
    time.sleep(delay)
    return port.read(response_length).decode().strip()

def send_sms(port, message, recipient_number):
    """
    Send an SMS message to the specified recipient number.

    Parameters:
        port (Serial): The serial port object for communication.
        message (str): The message to be sent.
        recipient_number (str): The phone number of the recipient.
    """
    # Set SMS text mode
    response = send_command(port, 'AT+CMGF=1')
    print(response)

    # Set recipient number
    response = send_command(port, f'AT+CMGS="{recipient_number}"')
    print(response)

    # Send message
    response = send_command(port, message + chr(26), delay=2)
    print(response)

# Main function
def main():
    # Open serial port
    try:
        port = serial.Serial("/dev/ttyS0", baudrate=9600, timeout=1)
    except serial.SerialException as e:
        print("Error: Could not open serial port:", e)
        return

    # Test communication
    response = send_command(port, 'AT', delay=1)
    print(response)

    # Send SMS message
    send_sms(port, 'Hello User', '+1234567890')  # Replace with recipient number

    # Close serial port
    port.close()

if __name__ == "__main__":
    main()
