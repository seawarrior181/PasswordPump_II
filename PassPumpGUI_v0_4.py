#!/usr/bin/env python
#
# GUI to interface with the PasswordPump
#
# Copyright 2019
# Daniel Murphy
#
#from Tkinter import *
#import tkinter.ttk as ttk

from tkinter import *
from tkinter.ttk import *

import PyCmdMessenger
import serial
import serial.tools.list_ports
from serial.tools.list_ports import comports
import argparse

window = Tk()
window.title("PasswordPump Edit Credentials")
window.geometry('400x300')

lbl_port = Label(window, text="Port", anchor=E, justify=RIGHT, width=10)
lbl_port.grid(column=0, row=0)

lbl_acct = Label(window, text="Account", anchor=E, justify=RIGHT, width=10)
lbl_acct.grid(column=0, row=1)

lbl_user = Label(window, text="User Name", anchor=E, justify=RIGHT, width=10)
lbl_user.grid(column=0, row=2)

lbl_pass = Label(window, text="Password", anchor=E, justify=RIGHT, width=10)
lbl_pass.grid(column=0, row=3)

lbl_style = Label(window, text="Style", anchor=E, justify=RIGHT, width=10)
lbl_style.grid(column=0, row=4)

lbl_url = Label(window, text="URL", anchor=E, justify=RIGHT, width=10)
lbl_url.grid(column=0, row=5)

lbl_help = Label(window, text="Instructions", anchor=W, justify=CENTER, width=11)
lbl_help.grid(column=1, row=6)

txt_acct = Entry(window, width=40)
txt_acct.grid(column=1, row=1)

txt_user = Entry(window, width=40)
txt_user.grid(column=1, row=2)

txt_pass = Entry(window, width=40)
txt_pass.grid(column=1, row=3)

txt_style = Entry(window, width=40)
txt_style.grid(column=1, row=4)

txt_url = Entry(window, width=40)
txt_url.grid(column=1, row=5)

txt_acct.config(state='normal')
txt_user.config(state='normal')
txt_pass.config(state='normal')
txt_style.config(state='normal')
txt_url.config(state='normal')

def clickedAll():
    clickedAcct()
    clickedUser()
    clickedPass()
    clickedStyle()
    clickedUrl()

def clickedAcct():
    resAcct = txt_acct.get()
    c.send("pyUpdateAccountName", position, resAcct)
    #s.write(resAcct + '\n')
    txt_acct.config(state='normal')
    #window.after(100, poll)
    directions = """Updated account name."""
    txt_dir.delete('1.0', END)
    txt_dir.insert(END, directions)
    print (directions)
    window.update()
    #poll()

def clickedUser():
    resUser = txt_user.get()
    c.send("pyUpdateUserName", position, resUser)
    #s.write(resUser + '\n')
    txt_user.config(state='normal')
    #window.after(100, poll)
    directions = """Updated user name."""
    txt_dir.delete('1.0', END)
    txt_dir.insert(END, directions)
    print (directions)
    window.update()
    #poll()

def clickedPass():
    resPass = txt_pass.get()
    c.send("pyUpdatePassword", position, resPass)
    #s.write(resPass + '\n')
    txt_pass.config(state='normal')
    #window.after(100, poll)
    directions = """Updated password."""
    txt_dir.delete('1.0', END)
    txt_dir.insert(END, directions)
    print (directions)
    window.update()
    #poll()

def clickedStyle():
    resStyle = txt_style.get()
    txt_style.config(state='normal')
    c.send("pyUpdateStyle", position, resStyle)
    #s.write(resStyle + '\n')
    txt_style.config(state='normal')
    #window.after(100, poll)
    directions = """Updated style."""
    txt_dir.delete('1.0', END)
    txt_dir.insert(END, directions)
    print (directions)
    window.update()
    #poll()

def clickedUrl():
    resURL = txt_url.get()
    txt_url.config(state='normal')
    c.send("pyUpdateURL", position, resURL)
    #s.write(resUrl + '\n')
    txt_url.config(state='normal')
    #window.after(100, poll)
    directions = """Updated URL."""
    txt_dir.delete('1.0', END)
    txt_dir.insert(END, directions)
    window.update()
    print (directions)

def clickedClose():
    #if s.is_open:
    #    s.close()
    sys.exit(1)

def clickedPrevious():
    c.send("pyGetPrevPos")
    response = c.receive()
    print(response)
    response_list = response[1]
    global position
    last_position = position
    position = response_list[0]
    if position == 255:
        position = last_position
        print("Reached the beginning of the list")
        txt_dir.delete('1.0', END)
        txt_dir.insert(END, "Reached the beginning of the list")
    getRecord()

def clickedNext():
    c.send("pyGetNextPos")
    response = c.receive()
    print(response)
    response_list = response[1]
    global position
    last_position = position
    position = response_list[0]
    if position == 255:
        position = last_position
        print("Reached the end of the list")
        txt_dir.delete('1.0', END)
        txt_dir.insert(END, "Reached the end of the list")
    getRecord()

def clickedInsert():
    global position
    c.send("pyGetNextFreePos")
    response = c.receive()
    print(response)
    response_list = response[1]
    position = response_list[0]
    getRecord()

def clickedDelete():
    global position
    c.send("pyDeleteAccount",position)
    response = c.receive()
    print(response)
    response_list = response[1]
    position = response_list[0]
    getRecord()

def clickedOpen():
    # global s
    # s = serial.Serial(port, 9600)
    global arduino
    arduino = PyCmdMessenger.ArduinoBoard(port, baud_rate=9600, timeout=1.0, settle_time=2.0, enable_dtr=False,
                                          int_bytes=4, long_bytes=8, float_bytes=4, double_bytes=8)
    global commands
    # List of command names (and formats for their associated arguments). These must
    # be in the same order as in the sketch.
    commands = [["kAcknowledge","b"],
                ["kStrAcknowledge", "s"],
                ["pyReadAccountName", "b"],
                ["pyReadUserName", "b"],
                ["pyReadPassword", "b"],
                ["pyReadURL", "b"],
                ["pyReadStyle", "b"],
                ["pyReadOldPassword", "b"],
                ["pyUpdateAccountName", "bs"],
                ["pyUpdateUserName", "bs"],
                ["pyUpdatePassword", "bs"],
                ["pyUpdateURL", "bs"],
                ["pyUpdateStyle", "bs"],
                ["pyGetNextPos","b"],
                ["pyGetPrevPos","b"],
                ["pyReadHead",""],
                ["pyReadTail",""],
                ["pyGetNextFreePos",""],
                ["kError",""],
                ["pyDeleteAccount","b"]]
    # Initialize the messenger
    global c
    c = PyCmdMessenger.CmdMessenger(arduino, commands)
    c.send("pyReadHead")
    response = c.receive()
    print(response)
    response_list = response[1]
    global head
    head = response_list[0]
    global position
    position = head
    getRecord()

    #c.send("pyReadOldPassword", position)
    #oldPassword = c.receive()

    btn_open.config(state='normal')
    btn_close.config(state='normal')
    directions = """Opened port"""
    txt_dir.delete('1.0', END)
    txt_dir.insert(END, directions)
    print (directions)
    window.update()
    #poll()

def getRecord():
    c.send("pyReadAccountName", position)
    try:
        response = c.receive()
        print (response)
        accountName_list = response[1]
        accountName = accountName_list[0]
    except UnicodeDecodeError:
        print("pyReadAccountName returned empty string")
        accountName = ""
    txt_acct.delete(0,END)
    txt_acct.insert(0,accountName)

    c.send("pyReadUserName", position)
    try:
        response = c.receive()
        print (response)
        userName_list = response[1]
        userName = userName_list[0]
    except UnicodeDecodeError:
        print("pyReadUserName returned empty string")
        userName = ""
    txt_user.delete(0,END)
    txt_user.insert(0,userName)

    c.send("pyReadPassword", position)
    try:
        response = c.receive()
        print(response)
        password_list = response[1]
        password = password_list[0]
    except UnicodeDecodeError:
        print("pyReadPassword returned empty string")
        password = ""
    txt_pass.delete(0,END)
    txt_pass.insert(0,password)

    c.send("pyReadStyle", position)
    try:
        response = c.receive()
        print(response)
        style_list = response[1]
        style = style_list[0]
    except UnicodeDecodeError:
        print("pyReadStyle returned empty string")
        style = ""
    txt_style.delete(0, END)
    txt_style.insert(0, style)

    c.send("pyReadURL", position)
    try:
        response = c.receive()
        print(response)
        url_list = response[1]
        url = url_list[0]
    except UnicodeDecodeError:
        print("pyReadURL returned empty string")
        url = ""
    txt_url.delete(0,END)
    txt_url.insert(0,url)

#def poll():
    #attribute = s.readline()
    #print attribute
    #if int(attribute) == 10:    #STATE_EDIT_ACCOUNT
    #    txt_acct.config(state='normal')
    #    txt_user.config(state='disabled')
    #    txt_pass.config(state='disabled')
    #    txt_style.config(state='disabled')
    #    txt_url.config(state='disabled')
    #    txt_acct.focus()
    #    btn_acct.config(state='normal')
    #    btn_user.config(state='disabled')
    #    btn_pass.config(state='disabled')
    #    btn_style.config(state='disabled')
    #    btn_url.config(state='disabled')
    #    window.bind('<Return>', (lambda e, btn_acct=btn_acct: btn_acct.invoke()))
    #    print('in 10')
    #elif int(attribute) == 6:  #STATE_EDIT_USERNAME
    #    txt_acct.config(state='disabled')
    #    txt_user.config(state='normal')
    #    txt_pass.config(state='disabled')
    #    txt_style.config(state='disabled')
    #    txt_url.config(state='disabled')
    #    txt_user.focus()
    #    btn_acct.config(state='disabled')
    #    btn_user.config(state='normal')
    #    btn_pass.config(state='disabled')
    #    btn_style.config(state='disabled')
    #    btn_url.config(state='disabled')
    #    window.bind('<Return>', (lambda e, btn_user=btn_user: btn_user.invoke()))
    #    print('in 6')
    #elif int(attribute) == 7:  #STATE_EDIT_PASSWORD
    #    txt_acct.config(state='disabled')
    #    txt_user.config(state='disabled')
    #    txt_pass.config(state='normal')
    #    txt_style.config(state='disabled')
    #    txt_url.config(state='disabled')
    #    txt_pass.focus()
    #    btn_acct.config(state='disabled')
    #    btn_user.config(state='disabled')
    #    btn_pass.config(state='normal')
    #    btn_style.config(state='disabled')
    #    btn_url.config(state='disabled')
    #    window.bind('<Return>', (lambda e, btn_pass=btn_pass: btn_pass.invoke()))
    #    print('in 7')
    #elif int(attribute) == 8:  # STATE_EDIT_WEBSITE
    #    txt_acct.config(state='disabled')
    #    txt_user.config(state='disabled')
    #    txt_pass.config(state='disabled')
    #    txt_style.config(state='disabled')
    #    txt_url.config(state='normal')
    #    txt_style.focus()
    #    btn_acct.config(state='disabled')
    #    btn_user.config(state='disabled')
    #    btn_pass.config(state='disabled')
    #    btn_style.config(state='disabled')
    #    btn_url.config(state='normal')
    #    window.bind('<Return>', (lambda e, btn_url=btn_url: btn_url.invoke()))
    #    print('in 8')
    #elif int(attribute) == 4:  #STATE_EDIT_STYLE
    #    txt_acct.config(state='disabled')
    #    txt_user.config(state='disabled')
    #    txt_pass.config(state='disabled')
    #    txt_style.config(state='normal')
    #    txt_url.config(state='disabled')
    #    txt_style.focus()
    #    btn_acct.config(state='disabled')
    #    btn_user.config(state='disabled')
    #    btn_pass.config(state='disabled')
    #    btn_style.config(state='normal')
    #    btn_url.config(state='disabled')
    #    window.bind('<Return>', (lambda e, btn_style=btn_style: btn_style.invoke()))
    #    print('in 4')

def serial_ports():
    return comports()

def on_select(event=None):
    global port
    port = cb.get()
    # get selection directly from combobox
    print("comboboxes: ", cb.get())

#btn_acct = Button(window, text="Submit", command=clickedAcct)
#btn_acct.grid(column=2, row=1)

#btn_user = Button(window, text="Submit", command=clickedUser)
#btn_user.grid(column=2, row=2)

#btn_pass = Button(window, text="Submit", command=clickedPass)
#btn_pass.grid(column=2, row=3)

#btn_style = Button(window, text="Submit", command=clickedStyle)
#btn_style.grid(column=2, row=4)

btn_url = Button(window, text="Save", command=clickedAll)
btn_url.grid(column=2, row=5)

btn_previous = Button(window, text="<<Previous", command=clickedPrevious)
btn_previous.grid(column=0, row=6)

btn_next = Button(window, text="Next>>", command=clickedNext)
btn_next.grid(column=2, row=6)

btn_insert = Button(window, text="Insert", command=clickedInsert)
btn_insert.grid(column=0, row=7)

btn_delete = Button(window, text="Delete", command=clickedDelete)
btn_delete.grid(column=0, row=8)

btn_open = Button(window, text="Open Port", command=clickedOpen)
btn_open.grid(column=2, row=0)

btn_close = Button(window, text=" Exit ", command=clickedClose)
btn_close.grid(column=2, row=8)

#btn_acct.config(state='normal')
#btn_user.config(state='normal')
#btn_pass.config(state='normal')
#btn_style.config(state='normal')
btn_url.config(state='normal')
btn_close.config(state='normal')

txt_dir = Text(window, height=5, width=30, relief=FLAT, background="light grey")
txt_dir.grid(column=1, row=7)
txt_dir.config(state=NORMAL)
txt_dir.delete('1.0', END)
directions = """After selecting the port click
on the Open Port button to 
open the port for the 
PasswordPump."""
txt_dir.insert(END, directions)

ports = []
for n, (port, desc, hwid) in enumerate(sorted(comports()), 1):
    ports.append(port)

cb = Combobox(window, values=ports, justify=RIGHT, width=37)
cb.grid(column=1, row=0)
cb.bind('<<ComboboxSelected>>', on_select)

# Global variables
position = 0
head = 0
tail = 0

window.mainloop()
