#!/usr/bin/env python
#
# GUI to interface with the PasswordPump
#
# Copyright 2020
# Daniel Murphy
#
# Built on Python 3.8
# Purpose:
#   This is the PC side of the PasswordPump.  It's job is to allow the user to
#   edit the credentials that are stored inside the EEprom that reside on the
#   PasswordPump.
#
# Defects:
# - If there's a / at the end of a URL python throws an exception
# - If a password (or any other field) contains a ~ or a |, python throws an
#   exception
# - Sometimes changing the URL in place is not working
# - When clicking on Next and Previous the Account List textbox selected
#   account isn't following along.
# - When an account is inserted the accounts list box doesn't refresh.
# - Hangs the MCU when adding credentials without Style or URL.
#
# Enhancements:
# - Add a scrollbar to the account list box.
# - Import files via this UI
#

from tkinter import *
from tkinter.ttk import *

import PyCmdMessenger
import serial
import serial.tools.list_ports
from serial.tools.list_ports import comports
import argparse

window = Tk()
window.title("PasswordPump Edit Credentials")
window.geometry('400x435')

lbl_port = Label(window, text="Port", anchor=E, justify=RIGHT, width=10)
lbl_port.grid(column=1, row=0)

lb = Listbox(window, selectmode=SINGLE, justify=LEFT, width=40)
scrollbar = Scrollbar(window, orient=VERTICAL)                                     # TODO: this is showing up in the wrong place
scrollbar.config(command=lb.yview)
scrollbar.grid(column=3,row=1)
lb.config(yscrollcommand=scrollbar.set)
lb.grid(column=2,row=1)

lbl_acct = Label(window, text="Account", anchor=E, justify=RIGHT, width=10)
lbl_acct.grid(column=1, row=2)

lbl_user = Label(window, text="User Name", anchor=E, justify=RIGHT, width=10)
lbl_user.grid(column=1, row=3)

lbl_pass = Label(window, text="Password", anchor=E, justify=RIGHT, width=10)
lbl_pass.grid(column=1, row=4)

lbl_style = Label(window, text="Style", anchor=E, justify=RIGHT, width=10)
lbl_style.grid(column=1, row=5)

lbl_url = Label(window, text="URL", anchor=E, justify=RIGHT, width=10)
lbl_url.grid(column=1, row=6)

lbl_help = Label(window, text="Instructions", anchor=W, justify=CENTER, width=11)
lbl_help.grid(column=2, row=7)

txt_acct = Entry(window, width=40)
txt_acct.grid(column=2, row=2)

txt_user = Entry(window, width=40)
txt_user.grid(column=2, row=3)

txt_pass = Entry(window, width=40)
txt_pass.grid(column=2, row=4)

txt_style = Entry(window, width=40)
txt_style.grid(column=2, row=5)

txt_url = Entry(window, width=40)
txt_url.grid(column=2, row=6)

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
    #getRecord()

def clickedAcct():
    resAcct = txt_acct.get()
    global position
    c.send("pyUpdateAccountName", position, resAcct)                           # on an insert, position is ignored here
    c.send("pyGetAcctPos")                                                     # get the (possibly) new account position
    response = c.receive()
    print(response)
    response_list = response[1]
    last_position = position
    position = response_list[0]
    if position == 255:
        position = last_position
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
#    c.send("pyReadUserName", position)
#    try:
#        response = c.receive()
#        print (response)
#        userName_list = response[1]
#        userName = userName_list[0]
#    except UnicodeDecodeError:
#        print("pyReadUserName returned empty string")
#        userName = ""
#    print(position)
#    print(userName)

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
#    c.send("pyReadPassword", position)
#    try:
#        response = c.receive()
#        print (response)
#        loc_password_list = response[1]
#        loc_password = loc_password_list[0]
#    except UnicodeDecodeError:
#        print("pyReadPassword returned empty string")
#        loc_password = ""
#    print(position)
#    print(loc_password)

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
    print (directions)
    window.update()

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
    else:
        items = lb.curselection()
        lb.activate(items[0] - 1)
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
    else:
        items = lb.curselection()
        lb.activate(items[0] + 1)
    getRecord()

def loadListBox():
    window.config(cursor="watch")                                              # TODO: this is not working
    lb.delete(0,END)                                                           # clear out the listbox
    c.send("pyReadHead")                                                       # Get the list head
    response = c.receive()
    response_list = response[1]
    global position
    head = response_list[0]
    position = head

    global accountDict
    accountDict = ({})                                                         # Load the dictionary
    while position < 255:
        c.send("pyReadAccountName", position)
        try:
            response = c.receive()
            accountName_list = response[1]
            accountName = accountName_list[0]
        except UnicodeDecodeError:
            print("pyReadAccountName returned empty string")
            accountName = ""
        accountDict[accountName] = position
        lb.insert(END, accountName)                                            # Load the listbox
        c.send("pyGetNextPos")
        response = c.receive()
        response_list = response[1]
        position = response_list[0]
#    position = head                                                            # Set the position back to the first account in the list

    lb.activate(0)                                                             # Activate the first item in the list
    window.config(cursor="")

def clickedInsert():
    global position
    c.send("pyGetNextFreePos")
    response = c.receive()
    print(response)
    response_list = response[1]
    position = response_list[0]
#   txt_acct.config(state='normal')
    txt_acct.delete(0, END)
    txt_user.delete(0, END)
    txt_pass.delete(0, END)
    txt_style.delete(0, END)
    txt_url.delete(0, END)
#   getRecord()

def clickedLoadDB(event):
    clickedLoad()

def clickedLoad():
    global position
    item = lb.curselection()
    theText = lb.get(item)
    position = accountDict[theText]
    print (item)
    print(lb.get(item))
    print(position)
    getRecord()

def clickedDelete():
    lb.delete(ANCHOR)                                                          # delete the account from the listbox
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
    arduino = PyCmdMessenger.ArduinoBoard(port, baud_rate=115200, timeout=1.0, settle_time=2.0, enable_dtr=False,
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
                ["pyGetNextPos",""],
                ["pyGetPrevPos",""],
                ["pyGetAcctPos",""],           # added b here 2019-11-14 7:16
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

    btn_close.config(state='normal')
    directions = """Opened port"""
    txt_dir.delete('1.0', END)
    txt_dir.insert(END, directions)
    print (directions)
    loadListBox()
    btn_open.config(state='disabled')
    cb.config(state='disabled')
    window.update()
    #poll()

def getRecord():
    print(position)
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

    print (position)
    c.send("pyReadUserName", position)
    try:
        response = c.receive()   #ValueError: Number of argument formats must match the number of recieved argumen
        print (response)
        userName_list = response[1]
        userName = userName_list[0]
    except UnicodeDecodeError:
        print("pyReadUserName returned empty string")
        userName = ""
    txt_user.delete(0,END)
    txt_user.insert(0,userName)

    print (position)
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
        response = c.receive()              #EOFError: Incomplete message (1~https://www.cvs.com/account/login/|) (when a field ends with /)
        print(response)
        url_list = response[1]
        url = url_list[0]
    except UnicodeDecodeError:
        print("pyReadURL returned empty string")
        url = ""
    txt_url.delete(0,END)
    txt_url.insert(0,url)

#def poll():

def serial_ports():
    return comports()

def on_select(event=None):
    global port
    port_desc = cb.get()
    print (port_desc)
    port = port_desc[:port_desc.find(":")]
    print (port)
    print("comboboxes: ", cb.get())
    # get selection directly from combobox

btn_previous = Button(window, text="<<Previous", command=clickedPrevious)
btn_previous.grid(column=1, row=7)

btn_insert = Button(window, text="Insert", command=clickedInsert)
btn_insert.grid(column=1, row=8)

btn_delete = Button(window, text="Delete", command=clickedDelete)
btn_delete.grid(column=1, row=9)

btn_open = Button(window, text="Open Port", command=clickedOpen)
btn_open.grid(column=4, row=0)

#btn_load = Button(window, text="Load", command=clickedLoad)
#btn_load.grid(column=4, row=1)
##lb.bind("<Double-Button-1>", clickedLoadDB)
lb.bind("<<ListboxSelect>>", clickedLoadDB)

btn_url = Button(window, text="Save", command=clickedAll)
btn_url.grid(column=4, row=6)

btn_next = Button(window, text="Next>>", command=clickedNext)
btn_next.grid(column=4, row=7)

btn_close = Button(window, text=" Exit ", command=clickedClose)
btn_close.grid(column=4, row=9)

btn_url.config(state='normal')
btn_close.config(state='normal')

txt_dir = Text(window, height=5, width=30, relief=FLAT, background="light grey")
txt_dir.grid(column=2, row=8)
txt_dir.config(state=NORMAL)
txt_dir.delete('1.0', END)
directions = """After selecting the port click
on the Open Port button to 
open the port for the 
PasswordPump."""
txt_dir.insert(END, directions)

ports = []
for n, (port, desc, hwid) in enumerate(sorted(comports()), 1):
    ports.append(port + ": " + desc)

cb = Combobox(window, values=ports, justify=RIGHT, width=37)
cb.grid(column=2, row=0)
cb.bind('<<ComboboxSelected>>', on_select)

# Global variables
position = 0
head = 0
tail = 0

window.mainloop()
