import keyboard
import serial
import time


class ArduinoHandler:
    def __init__(self):
        pass

    def get_arduino_values(self):
        if self.arduino_port is None:  # if no Arduino is found
            self.arduino_port = self.get_arduino_port()
            return

        time.sleep(1/96)
        try:
            raw_data = self.ser.readline().decode().strip()
        except Exception as e:
            print("Reading from Arduino Port failed")
            print(f"{e}")
            return None

        return raw_data

    def write_to_arduino(self, data):
        self.ser.write(bytes(data))

    def get_arduino_port(self):
        ports_found = serial.tools.list_ports.comports()

        comm_port = 'None'
        num_connection = len(comm_port)

        # cycles through all connected devices and searches for a device with Arduino in its "description"
        for i in range(0, num_connection):
            str_port = str(comm_port[i])
            if 'Arduino' in str_port or 'Serielles' in str_port:
                comm_port = str_port.split(' ')[0]  # takes only the first part cause that's where the COM stuff is
                print(f"Found Arduino at {comm_port}")

        if comm_port == 'None':
            print("No Arduino found.")
            return

        return comm_port

    def setup_arduino_connection(self):
        while self.get_arduino_port() is None:
            pass
        self.arduino_port = self.get_arduino_port()
        self.ser = serial.Serial(port=self.arduino_port, baudrate=9600)

    def close(self):
        self.ser.close()


class MainLoop():
    def __init__(self):
        self.arduino_handler = ArduinoHandler()

    def start(self):
        while True:
            if keyboard.is_pressed('8'):
                print("UP")
            elif keyboard.is_pressed('2'):
                print("DOWN")

            if keyboard.is_pressed('w'):
                print("FORWARD")
            elif keyboard.is_pressed('s'):
                print("BACKWARDS")

            if keyboard.is_pressed('a'):
                print("LEFT")
            elif keyboard.is_pressed('d'):
                print("RIGHT")



def main():
    main_loop = MainLoop()
    main_loop.start()


if __name__ == '__main__':
    main()
