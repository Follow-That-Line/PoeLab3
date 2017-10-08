#!/usr/local/bin/python

from serial import Serial, SerialException
from tkinter import *
import json
import time

#cxn = Serial('/dev/ttyACM1', baudrate=9600)
data = 0

def send_data():
    var = int(textbox.get())
    if var > 2 or var < 1:
        res.configure(text = "Please enter a valid number(1 or 2).")
    else:
        res.configure(text = "Sending value to serial...")
        cxn.write([int(data)])
        res.configure(text = "Successfully sent value to serial.")

master = Tk()

Label(master, text="Enter 1 to stop or 2 to continue: ").grid(row=0)
res = Label(master)
res.grid(row=1)

textbox = Entry(master)
textbox.grid(row=0, column=1)

Button(master, text='Quit', command=master.quit).grid(row=3, column=0, sticky=W, pady=4)
Button(master, text='Enter', command=send_data).grid(row=3, column=1, sticky=W, pady=4)

mainloop( )
