# LoadCell Data Logging
"""
Created on Wed Dec  2 11:34:00 2020

@author: Ahmad Mohammadpanah
"""
LengthOfGraphMonitor=100; #Second Show on the Graph
LengthOfTheTest=100; #Second Total length of running the test
 # You need to find the exact calibration number
ARMLENGTH=0.09606;

import serial
from serial import Serial
import matplotlib.pyplot as plt
from drawnow import *
import sys
import numpy
import pandas as pd


from PyQt5 import QtWidgets
from PyQt.QtWidgets import QApplication, QMainWindow

def window():
    app = QApplication(sys.argv)
    win = QMainWindow
    win.setGeometry(200, 200, 300, 300)
    win.setWindowTitle("Motor Test Stand")
    
    win.show()
    sys.exit(app.exec_())
    
window()
forces = []
averageforce=[]
averagetorque=[]
ArduinoData=serial.Serial('COM5', baudrate=9600)
plt.ion()
cnt=0;
tic=0;

fig=plt.figure(figsize=(20,10))  # You can change the size of the Graph on your screen

   
plt.style.use("dark_background")
    
ax1 = fig.add_subplot(211)
line_force, = ax1.plot(averageforce,'r-', linewidth=4)

ax1.set_ylim(0,100)
ax1.set_title('UAS Motor Test Stand')
ax1.grid(True)
ax1.set_ylabel('Force(N)')
   
# plt.rc('font', size=34)
ax2= fig.add_subplot(212)
line_torque, = ax2.plot(averagetorque,'r-', linewidth=4)
ax2.set_ylim(0,10)
ax2.grid(True)
ax2.set_ylabel('Torque(Nm)')
ax2.set_xlabel('Time(1/10 Second)')
# ax2.rc('font', size=34)
"""plt.subplots_adjust(top=1.5)"""


df = pd.DataFrame(columns=['cell1', 'cell2', 'cell3', 'cell4', 'cell5', 'cell6'])
i = 0




while tic<10*LengthOfTheTest:
    tic=tic+1;
    while(ArduinoData.inWaiting()==0):
         pass
    ArduinoString =str(ArduinoData.readline())
    l = ArduinoString.split(",")  
    if len(l) < 8:
        continue
    del l[0]
    del l[6]
    l_float=[]
    for j in range(len(l)):
        l_float.append(float(l[j])*9.81)
    averageforce.append((l_float[0]+l_float[1]+l_float[2])/3)
    averagetorque.append((l_float[3]+l_float[4]+l_float[5])/3*ARMLENGTH)
    line_force.set_data(range(len(averageforce)),averageforce)
    line_torque.set_data(range(len(averagetorque)),averagetorque)
    """drawnow(makeFig)"""
    if i>=5:
        ax1.set_xlim(-0,len(averageforce))
        ax2.set_xlim(-0,len(averagetorque))
        fig.canvas.draw()
        plt.pause(0.000001)
        i=0
    i = i + 1
    arr_force = numpy.array(averageforce)
    arr_torque = numpy.array(averagetorque)
    with open('Motor Test Stand.csv', 'wb') as f:
        numpy.savetxt(f, numpy.transpose([arr_force,arr_torque]), delimiter=',', fmt='%s')
sys.exit('End of the Test')



