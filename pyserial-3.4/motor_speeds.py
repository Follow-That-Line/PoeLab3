#!/usr/local/bin/python

from serial import Serial, SerialException
import json
import time

cxn = Serial('/dev/ttyACM0', baudrate=9600)
results_list = []
first = True
cmd_id = 0

while(True):
    try:
        if cmd_id != 1:
            cmd_id = int(input("Please enter a command ID (1 - read distance sensor, 2 - move the servo, 3 - move the other servo: "))
            prevtime = time.clock()
            print(time.clock())
        if int(cmd_id) > 3 or int(cmd_id) < 1:
            print ("Values other than 1 2 or 3 are ignored.")
        else:
            cxn.write([int(cmd_id)])
            while cxn.inWaiting() < 1:
                pass
            if cmd_id == 1:
                result = cxn.readline();
                result = str(result)
                result = result[2:]
                result = result.strip("\\r\\n'")
                results_list.append(result)
                with open('motor_speeds2.csv', 'w') as f:
                    json.dump(results_list, f)
                first = False
            if time.clock()-prevtime > 15:
                cmd_id = 2
                with open('motor_speeds2.csv', 'w') as f:
                    json.dump(results_list, f)
                first = True
            print (result)
    except ValueError:
        print ("You must enter an integer value between 1 and 3.")
