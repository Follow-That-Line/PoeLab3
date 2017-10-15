import json
import matplotlib.pyplot as plt

with open('side_sensor_black_on_foam.csv', 'r') as f:
    black_on_foam = json.load(f)

with open('side_sensor_black_on_ground.csv', 'r') as f:
    black_on_ground = json.load(f)

with open('side_sensor_white_on_foam.csv', 'r') as f:
    white_on_foam = json.load(f)

with open('side_sensor_white_on_ground.csv', 'r') as f:
    white_on_ground = json.load(f)

plt.title('Side Sensor Calibration')
values = plt.plot(black_on_foam, 'black', label='Black on Foam')
values2 = plt.plot(black_on_ground, 'b', label='Black on Ground')
values3 = plt.plot(white_on_foam, 'g', label='White on Foam')
values4 = plt.plot(white_on_ground, 'r', label ='White on Ground')
ourline = plt.axhline(y=870, label='Our Threshold')
plt.legend()

plt.xlabel('Time')
plt.ylabel('Sensor Values')

plt.show()
