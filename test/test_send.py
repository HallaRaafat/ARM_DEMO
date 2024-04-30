import unittest
import serial
import defines

class TestConnection(unittest.TestCase):
    
    def test_rec(self):
        ser = serial.Serial('COM6', 9600,timeout=5)
        ser.write([0x05, 0x01, 0x2, 0x3, 0x4, 0x5])
        # argparse.ArgumentParser()
        # time.sleep(4)
        serial_line = ser.read(1)
        print(serial_line)
        integer_value = int.from_bytes(serial_line, byteorder='big')
        # self.assertEqual(integer_value, 0x05)
        
        try:
            self.assertEqual(integer_value, 0x77)
            x = True  # If no AssertionError is raised, the assertion passed
        except AssertionError:
            x = False  
        with open("test_results.txt", "w") as file:
            file.write("LED Test: " + ("Passed" if x else "Failed") + "\n")  
        
    def test_send(self):
        ser = serial.Serial('COM6', 9600,timeout=5)
        ser.write([0x03])
        serial_line = ser.read(1)
        integer_value = int.from_bytes(serial_line, byteorder='big')
        # print(serial_line)        
        self.assertEqual(integer_value, 0x03)

class TestLED(unittest.TestCase):
    def test_ledOn(self):
        LED_DATA = {
            'module':   defines.LED_MOD,
            'method':   defines.LED_SET,
            'id':       0,
            'state':    defines.LED_ON
        }
        ser = serial.Serial('COM6', 9600,timeout=5)
        ser.write([defines.FRAME_START,LED_DATA["module"], LED_DATA["method"], LED_DATA["id"], LED_DATA["state"]])
        serial_line = ser.read(1)
        integer_value = int.from_bytes(serial_line, byteorder='big')
        try:
            self.assertEqual(integer_value, LED_DATA["state"])
            x = True  # If no AssertionError is raised, the assertion passed
        except AssertionError:
            x = False  
        with open("test_results.txt", "w") as file:
            file.write("LED Test: led OFF = " + ("Passed" if x else "Failed") + "\n")
            
    def test_ledOff(self):
        LED_DATA = {
            'module':   defines.LED_MOD,
            'method':   defines.LED_SET,
            'id':       0,
            'state':    defines.LED_OFF
        }
        ser = serial.Serial('COM6', 9600,timeout=5)
        ser.write([defines.FRAME_START,LED_DATA["module"], LED_DATA["method"], LED_DATA["id"], LED_DATA["state"]])
        serial_line = ser.read(1)
        integer_value = int.from_bytes(serial_line, byteorder='big')
        try:
            self.assertEqual(integer_value, LED_DATA["state"])
            x = True  # If no AssertionError is raised, the assertion passed
        except AssertionError:
            x = False  
        with open("test_results.txt", "w") as file:
            file.write("LED Test: led OFF = " + ("Passed" if x else "Failed") + "\n")
            
    
def controlLed(state,ser):
        LED_DATA = {
            'module':   defines.LED_MOD,
            'method':   defines.LED_SET,
            'id':       0,
            'state':    state
        }
        # ser = serial.Serial('COM6', 9600,timeout=5)
        ser.write([defines.FRAME_START,LED_DATA["module"], LED_DATA["method"], LED_DATA["id"], LED_DATA["state"]])
        serial_line = ser.read(1)
        integer_value = int.from_bytes(serial_line, byteorder='big')
        
        return integer_value



class Test_SW_LED(unittest.TestCase):
    def test_sw_led(self):
        SW_DATA = {
            'module':   defines.SW_MOD,
            'method':   defines.SW_GET,
            'id':       0
        }
        ser = serial.Serial('COM6', 9600,timeout=5)
        ser.write([defines.FRAME_START,SW_DATA["module"], SW_DATA["method"], SW_DATA["id"], 0x00])
        serial_line = ser.read(1)
        integer_value = int.from_bytes(serial_line, byteorder='big')
        if integer_value == defines.SW_PRESSED:
            ledReturn = controlLed(defines.LED_ON,ser)
            self.assertEqual(ledReturn, defines.LED_ON)
        elif integer_value == defines.SW_RELEASED:
            ledReturn = controlLed(defines.LED_OFF,ser)
            self.assertEqual(ledReturn, defines.LED_OFF)
        else:
            print("ERRORRRRRRRRRRR")
        
        
    def test_ledOff(self):
        LED_DATA = {
            'module':   defines.LED_MOD,
            'method':   defines.LED_SET,
            'id':       0,
            'state':    0
        }
        ser = serial.Serial('COM6', 9600,timeout=5)
        ser.write([defines.FRAME_START,LED_DATA["module"], LED_DATA["method"], LED_DATA["id"], LED_DATA["state"]])
        serial_line = ser.read(1)
        integer_value = int.from_bytes(serial_line, byteorder='big')
        try:
            self.assertEqual(integer_value, 0x00)
            x = True  # If no AssertionError is raised, the assertion passed
        except AssertionError:
            x = False  
        with open("test_results.txt", "w") as file:
            file.write("LED Test: led OFF = " + ("Passed" if x else "Failed") + "\n")

if __name__ == '__main__':
    unittest.main()

# import serial  # imports pyserial
# import serial.tools.list_ports as list_ports

# # List all comports
# all_ports = list_ports.comports()
# print(all_ports)

# import serial
# ser = serial.Serial('COM7', 9600,timeout=5)

# while 1:
#     serial_line = ser.read(6)
#     print(serial_line)
#     ser.write([0x01, 0x2, 0x3, 0x4, 0x5, 0x6])