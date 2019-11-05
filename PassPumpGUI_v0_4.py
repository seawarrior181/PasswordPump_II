#!/usr/bin/env python
#
# GUI to interface with the PasswordPump
#
# Copyright 2019
# Daniel Murphy
#
from Tkinter import *
import tkinter.ttk as ttk
import PyCmdMessenger
import serial
import serial.tools.list_ports
from serial.tools.list_ports import comports
import argparse

window = Tk()
window.title("PasswordPump Edit Credentials")
window.geometry('375x600')

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

lbl_help = Label(window, text="Instructions", anchor=W, justify=CENTER, width=10)
lbl_help.grid(column=1, row=7)

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

def clickedAcct():
    resAcct = txt_acct.get()
    c.send("pyUpdateAccountName", position, resAcct)
    #s.write(resAcct + '\n')
    txt_acct.config(state='normal')
    #window.after(100, poll)
    directions = """On the PasswordPump long click
to accept the entered account 
name, then short click on Edit
Username, then enter the 
username in the text box 
above.  Then hit return or 
click on Submit."""
    txt_dir.delete('1.0', END)
    txt_dir.insert(END, directions)
    print directions
    window.update()
    #poll()

def clickedUser():
    resUser = txt_user.get()
    c.send("pyUpdateUserName", position, resUser)
    #s.write(resUser + '\n')
    txt_user.config(state='normal')
    #window.after(100, poll)
    directions = """On the PasswordPump long click
to accept the entered user 
name, then short click on 
Edit Password, then enter the 
password in the text box 
above.  Then hit return or 
click on Submit."""
    txt_dir.delete('1.0', END)
    txt_dir.insert(END, directions)
    print directions
    window.update()
    #poll()

def clickedPass():
    resPass = txt_pass.get()
    c.send("pyUpdatePassword", position, resPass)
    #s.write(resPass + '\n')
    txt_pass.config(state='normal')
    #window.after(100, poll)
    directions = """On the PasswordPump long click
to accept the entered 
password, then short click on 
Indicate Style, then enter the
style in the text box above.
Style controls whether or not
a carriage return or a tab is
sent between the sending of
the username and the 
password. Enter 0 for 
carriage return, 1 for tab 
between username and password
when both are sent. Then hit
return or click on Submit. 
The style can also be entered
via the rotary encoder; turn
the encoder to select 0 or 1,
then short click and then 
long click."""
    txt_dir.delete('1.0', END)
    txt_dir.insert(END, directions)
    print directions
    window.update()
    #poll()

def clickedStyle():
    resStyle = txt_style.get()
    txt_style.config(state='normal')
    c.send("pyUpdateStyle", position, resStyle)
    #s.write(resStyle + '\n')
    txt_style.config(state='normal')
    #window.after(100, poll)
    directions = """On the PasswordPump long click
to accept the entered style,
then short click on 
Edit URL, then enter the 
URL in the text box 
above.  Then hit return or 
click on Submit."""
    txt_dir.delete('1.0', END)
    txt_dir.insert(END, directions)
    print directions
    window.update()
    #poll()

def clickedUrl():
    resURL = txt_url.get()
    txt_url.config(state='normal')
    c.send("pyUpdateURL", position, resURL)
    #s.write(resUrl + '\n')
    txt_url.config(state='normal')
    #window.after(100, poll)
    directions = """On the PasswordPump long click
to accept the entered URL. 
On the PasswordPump long 
click to finish entering the
credentials, then close this
application by clicking on
Exit."""
    txt_dir.delete('1.0', END)
    txt_dir.insert(END, directions)
    window.update()
    print directions

def clickedClose():
    #if s.is_open:
    #    s.close()
    sys.exit(1)

def clickedOpen():
    global s
    #s = serial.Serial(port, 9600)
    global arduino
    arduino = PyCmdMessenger.ArduinoBoard(port, baud_rate=9600)
    global commands
    # List of command names (and formats for their associated arguments). These must
    # be in the same order as in the sketch.
    commands = [["kAcknowledge",""],
                ["pyReadAccountName", "i"],
                ["pyReadUserName", "i"],
                ["pyReadPassword", "i"],
                ["pyReadURL", "i"],
                ["pyReadStyle", "i"],
                ["pyReadOldPassword", "i"],
                ["pyUpdateAccountName", "is"],
                ["pyUpdateUserName", "is"],
                ["pyUpdatePassword", "is"],
                ["pyUpdateURL", "is"],
                ["pyUpdateStyle", "is"],
                ["pyGetNextPos","i"],
                ["pyGetPrevPos","i"],
                ["pyReadHead",""],
                ["pyReadTail",""],
                ["pyGetNextFreePos",""],
                ["kError",""]]
    # Initialize the messenger
    c = PyCmdMessenger.CmdMessenger(arduino, commands)
    c.send("pyReadHead")
    head = c.receive()
    global position
    position = head

    c.send("pyReadAccountName", head)
    accountName = c.receive()
    txt_acct.set(accountName)

    c.send("pyReadUserName", head)
    userName = c.receive()
    txt_user.set(userName)

    c.send("pyReadPassword", head)
    password = c.receive()
    txt_pass.set(password)

    c.send("pyReadURL", head)
    url = c.receive()
    txt_url.set(url)

    c.send("pyReadStyle", head)
    style = c.receive()
    txt_style.set(style)

    #c.send("pyReadOldPassword", head)
    #oldPassword = c.receive()

    btn_open.config(state='normal')
    btn_close.config(state='normal')
    directions = """On the PasswordPump navigate 
to Add Account and short 
click. Then short click on
Account Name, enter the
account name in the Account
Name text box above, and hit
return or click on Submit."""
    txt_dir.delete('1.0', END)
    txt_dir.insert(END, directions)
    print directions
    window.update()
    #poll()

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

btn_acct = Button(window, text="Submit", command=clickedAcct)
btn_acct.grid(column=2, row=1)

btn_user = Button(window, text="Submit", command=clickedUser)
btn_user.grid(column=2, row=2)

btn_pass = Button(window, text="Submit", command=clickedPass)
btn_pass.grid(column=2, row=3)

btn_style = Button(window, text="Submit", command=clickedStyle)
btn_style.grid(column=2, row=4)

btn_url = Button(window, text="Submit", command=clickedUrl)
btn_url.grid(column=2, row=5)

btn_close = Button(window, text=" Exit ", command=clickedClose)
btn_close.grid(column=2, row=6)

btn_open = Button(window, text="Open Port", command=clickedOpen)
btn_open.grid(column=0, row=6)

btn_acct.config(state='normal')
btn_user.config(state='normal')
btn_pass.config(state='normal')
btn_style.config(state='normal')
btn_url.config(state='normal')
btn_close.config(state='normal')

txt_dir = Text(window, height=19, width=30, relief=FLAT, background="light grey")
txt_dir.grid(column=1, row=8)
txt_dir.config(state=NORMAL)
txt_dir.delete('1.0', END)
directions = """After selecting the port click
on the Open Port button to 
open the port."""
txt_dir.insert(END, directions)

ports = []
for n, (port, desc, hwid) in enumerate(sorted(comports()), 1):
    ports.append(port)

cb = ttk.Combobox(window, values=ports, justify=RIGHT, width=37)
cb.grid(column=1, row=0)
cb.bind('<<ComboboxSelected>>', on_select)

window.mainloop()
