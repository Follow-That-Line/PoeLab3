import json
import matplotlib.pyplot as plt

with open('motor_speeds2.csv', 'r') as f:
    results_list = json.load(f)

sensor1vals = (results_list[0::4])
sensor2vals = (results_list[1::4])
motor1vals = (results_list[2::4])
motor2vals = (results_list[3::4])

fig, ax1 = plt.subplots()

plt.title('Motor Values and Sensor Values Over Time')
ax1.plot(sensor1vals[750:1000], 'black', sensor2vals[750:1000], 'b')
ax1.set_xlabel('Time')
ax1.set_ylabel('Sensor Values', color='b')
ax1.tick_params('y', colors='b')

ax2 = ax1.twinx()
ax2.plot(motor1vals[750:1000], 'r', motor2vals[750:1000], 'g')
ax2.set_ylabel('Motor Values', color='r')
ax2.tick_params('y', colors='r')

#fig.tight_layout()
plt.show()
