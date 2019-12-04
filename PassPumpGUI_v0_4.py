#!/usr/bin/env python
#
# GUI to interface with the PasswordPump
#
# Copyright 2020
# Daniel Murphy
#
# Built on Python 3.8
# Purpose:
#   This is the client side of the PasswordPump.  This program's job is to
#   allow the user to edit the credentials that are stored inside the EEprom
#   chips that reside on the PasswordPump device.

# Defects and Enhancements Key:
# - = outstanding
# x = fixed but needs testing
# * = fixed
#
# Defects:
# - Style is garbage when importing PasswordPump file.
# - When an account is inserted the accounts list box doesn't refresh.
# - If there's a / at the end of a URL python throws an exception
# - If a password (or any other field) contains a ~ or a |, python throws an
#   exception
# - Sometimes changing the URL in place is not working
# - Hangs the MCU when adding credentials without Style or URL.
# * When clicking on Next and Previous the Account List textbox selected
#   account isn't following along.
#
# Enhancements:
# - Add groups to the UI
# - Import files via this UI
# * Add a scrollbar to the account list box.
#

from tkinter import *
from tkinter.ttk import *
from tkinter.filedialog import askopenfilename
from tkinter.filedialog import asksaveasfilename

import PyCmdMessenger
import serial
import serial.tools.list_ports
from serial.tools.list_ports import comports
import argparse
import csv

window = Tk()
window.title("PasswordPump Edit Credentials")
window.geometry('400x430')

lbl_port = Label(window, text="Port", anchor=E, justify=RIGHT, width=10)
lbl_port.grid(column=1, row=0)

frame = Frame(window, width=200, height=200)
frame.grid(column=2,row=1)
lb = Listbox(frame, selectmode=SINGLE, justify=LEFT, width=38, bd=0, exportselection=False)
scrollbar = Scrollbar(frame, orient=VERTICAL)
scrollbar.pack(side=RIGHT, fill=Y)
scrollbar.config(command=lb.yview)
lb.config(yscrollcommand=scrollbar.set)
lb.pack()

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

txt_url = Entry(window, width=40)
txt_url.grid(column=2, row=6)

txt_acct.config(state='normal')
txt_user.config(state='normal')
txt_pass.config(state='normal')
txt_url.config(state='normal')

def updateDirections(directions):
    txt_dir.delete('1.0', END)
    txt_dir.insert(END, directions)
    print (directions)
    window.update()

def clickedSave():
    clickedAcct()
    clickedUser()
    clickedPass()
    clickedStyle()
    clickedUrl()
    global state
    if (state == "Inserting"):
        lb.delete(0,END)
        loadListBox()
    state = "None"

def clickedAcct():
    resAcct = txt_acct.get()
    global position                                                            # the position on EEprom, don't confuse with selection
    c.send("pyUpdateAccountName", position, resAcct)                           # on an insert, position is ignored here
    c.send("pyGetAcctPos")                                                     # get the (possibly) new account position
    response = c.receive()
    print(response)  # acctPostion & position = 49
    response_list = response[1]
    last_position = position
    position = response_list[0]
    if position == 255:
        position = last_position
    txt_acct.config(state='normal')
    directions = """Updated account name."""
    updateDirections(directions)
    window.update()

def clickedUser():
    resUser = txt_user.get()
    c.send("pyUpdateUserName", position, resUser)
    #s.write(resUser + '\n')
    txt_user.config(state='normal')
    #window.after(100, poll)
    directions = """Updated user name."""
    updateDirections(directions)
    window.update()

def clickedPass():
    resPass = txt_pass.get()
    c.send("pyUpdatePassword", position, resPass)
    #s.write(resPass + '\n')
    txt_pass.config(state='normal')
    #window.after(100, poll)
    directions = """Updated password."""
    updateDirections(directions)
    window.update()

def clickedStyle():
    resStyle = cbStyle.current()
    c.send("pyUpdateStyle", position, resStyle)
    directions = """Updated style."""
    updateDirections(directions)
    window.update()

def clickedUrl():
    resURL = txt_url.get()
    txt_url.config(state='normal')
    c.send("pyUpdateURL", position, resURL)
    txt_url.config(state='normal')
    directions = """Updated URL."""
    updateDirections(directions)
    window.update()

def clickedClose():
    sys.exit(1)

def clickedPrevious():
    c.send("pyGetPrevPos")
    response = c.receive()
    print(response)
    response_list = response[1]
    global selection
    global position
    last_position = position
    position = response_list[0]
    if position == 255:
        position = last_position
        updateDirections("Reached the beginning of the list.")
    else:
        items = lb.curselection()
        lb.activate(items[0] - 1)
        OnEntryUpNoEvent()
        lb.see(selection)

def clickedNext():
    c.send("pyGetNextPos")
    response = c.receive()
    print(response)
    response_list = response[1]
    global selection
    global position
    last_position = position
    position = response_list[0]
    if position == 255:
        position = last_position
        updateDirections("Reached the end of the list")
    else:
        items = lb.curselection()
        lb.activate(items[0] + 1)
        OnEntryDownNoEvent()
        lb.see(selection)

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
            updateDirections("pyReadAccountName returned empty string")
            accountName = ""
        accountDict[accountName] = position
        lb.insert(END, accountName)                                            # Load the listbox
        c.send("pyGetNextPos")
        response = c.receive()
        response_list = response[1]
        position = response_list[0]
    lb.activate(0)                                                             # Activate the first item in the list
    global selection
    selection = 0
    lb.select_set(selection)
    lb.bind("<Down>", OnEntryDown)
    lb.bind("<Up>", OnEntryUp)
    window.config(cursor="")

def OnEntryDownNoEvent():
    OnEntryDown(0)

def OnEntryDown(event):
    global selection
    if selection < lb.size()-1:
        lb.select_clear(selection)
        selection += 1
        lb.select_set(selection)
        clickedLoad()

def OnEntryUpNoEvent():
    OnEntryUp(0)

def OnEntryUp(event):
    global selection
    if selection > 0:
        lb.select_clear(selection)
        selection -= 1
        lb.select_set(selection)
        clickedLoad()

def clickedInsert():
    global state
    state = "Inserting"
    global position
    c.send("pyGetNextFreePos")
    response = c.receive()
    print(response)
    response_list = response[1]
    position = response_list[0]
    txt_acct.delete(0, END)
    txt_user.delete(0, END)
    txt_pass.delete(0, END)
    txt_url.delete(0, END)

def clickedLoadDB(event):
    clickedLoad()

def clickedLoad():
    global position
    item = lb.curselection()
    global selection
    selection = item[0]
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
    global arduino
    try:                                                                       #
        arduino = PyCmdMessenger.ArduinoBoard(port, baud_rate=115200, timeout=1.0, settle_time=2.0, enable_dtr=False,
                                              int_bytes=4, long_bytes=8, float_bytes=4, double_bytes=8)
    except serial.serialutil.SerialException:
        updateDirections("Error when attaching to PasswordPump.  Device not found. Power cycle the PasswordPump and try again.")

    global commands
    commands = [["kAcknowledge","b"],                                          # List of command names (and formats for their associated arguments). These must
                ["kStrAcknowledge", "s"],                                      # be in the same order as in the Arduino sketch.
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
                ["pyGetAcctPos",""],
                ["pyReadHead",""],
                ["pyReadTail",""],
                ["pyGetNextFreePos",""],
                ["kError",""],
                ["pyDeleteAccount","b"]]
    global c                                                                   # Initialize the messenger
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
    btn_close.config(state='normal')
    directions = """Opened port"""
    txt_dir.delete('1.0', END)
    txt_dir.insert(END, directions)
    print (directions)
    loadListBox()
    btn_open.config(state='disabled')
    cb.config(state='disabled')
    window.update()

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
        response = c.receive()
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
    cbStyle.set(style)

    c.send("pyReadURL", position)
    try:
        response = c.receive()                                                 # EOFError: Incomplete message (1~https://www.cvs.com/account/login/|) (when a field ends with /)
        print(response)
        url_list = response[1]
        url = url_list[0]
    except UnicodeDecodeError:
        print("pyReadURL returned empty string")
        url = ""
    txt_url.delete(0,END)
    txt_url.insert(0,url)

def serial_ports():
    return comports()

def on_select(event=None):
    global port
    port_desc = cb.get()
    print (port_desc)
    port = port_desc[:port_desc.find(":")]
    print (port)
    print("comboboxes: ", cb.get())

def on_style_select(event=None):
    print (cbStyle.get())

def ImportFileChrome():
    name = askopenfilename(initialdir="C:/",                                   # TODO: make this work cross platform
                           filetypes =(("CSV File", "*.csv"),("All Files","*.*")),
                           title = "Choose a file."
                          )
    print (name)
    try:                                                                       # Using try in case user types in unknown file or closes without choosing a file.
        with open(name, newline='') as csvfile:
            reader = csv.DictReader(csvfile)
            try:
                for row in reader:
                    print(row)
                    print(row['name'], row['url'], row['username'], row['password'])
                    clickedInsert()
                    txt_acct.insert(0,row['name'])
                    txt_user.insert(0,row['username'])
                    txt_pass.insert(0,row['password'])
                    txt_url.insert(0,row['url'])
                    window.update()
                    global state
                    print(state)
                    clickedSave() #acctPosition & position = 49
                    updateDirections("Record saved.")
                updateDirections("All records saved.")
            except:
                updateDirections("Error saving a record.")
    except:
        updateDirections("No file exists")

def ImportFilePasswordPump():
    name = askopenfilename(initialdir="C:/",                                   # TODO: make this work cross platform
                           filetypes =(("CSV File", "*.csv"),("All Files","*.*")),
                           title = "Choose a file."
                          )
    print (name)
    try:                                                                       # Using try in case user types in unknown file or closes without choosing a file.
        with open(name, newline='') as csvfile:
            fieldnames = ['accountname', 'username', 'password', 'url', 'group']
            reader = csv.DictReader(csvfile, fieldnames=fieldnames)
            try:
                for row in reader:
                    print(row)
                    print(row['accountname'], row['username'], row['password'], row['url'], row['group'])
                    clickedInsert()
                    txt_acct.insert(0,row['accountname'])
                    txt_user.insert(0,row['username'])
                    txt_pass.insert(0,row['password'])
                    txt_url.insert(0,row['url'])
                    #txt_group.insert(0,row['group'])                          # TODO: add group to the UI
                    window.update()
                    global state
                    print(state)
                    clickedSave()
                    updateDirections("Record saved.")
                updateDirections("All records saved.")
            except:
                updateDirections("Error saving a record.")
    except:
        updateDirections("No file exists")

def ImportFileKeePass():
    name = askopenfilename(initialdir="C:/",                                   # TODO: make this work cross platform
                           filetypes =(("CSV File", "*.csv"),("All Files","*.*")),
                           title = "Choose a file."
                          )
    print (name)
    try:                                                                       # Using try in case user types in unknown file or closes without choosing a file.
        with open(name, newline='') as csvfile:
            reader = csv.DictReader(csvfile)
            try:  #
                for row in reader:
                    print(row)
                    print(row['name'], row['url'], row['username'], row['password'])
                    clickedInsert()
                    txt_acct.insert(0,row['name'])
                    txt_user.insert(0,row['username'])
                    txt_pass.insert(0,row['password'])
                    txt_url.insert(0,row['url'])
                    window.update()
                    global state
                    print(state)
                    clickedSave()
                    updateDirections("Record saved.")
                updateDirections("All records saved.")
            except:
                updateDirections("Error saving a record.")
    except:
        updateDirections("No file exists")

def ImportFile():
    name = askopenfilename(initialdir="C:/",                                   # TODO: make this work cross platform
                           filetypes =(("CSV File", "*.csv"),("All Files","*.*")),
                           title = "Choose a file."
                          )
    print (name)
    try:                                                                       # Using try in case user types in unknown file or closes without choosing a file.
        with open(name,'r') as UseFile:
            print(UseFile.read())
    except:
        print("No file exists")

def ExportFile():
    name = asksaveasfilename(initialdir="C:/",                                   # TODO: make this work cross platform
                             filetypes =(("CSV File", "*.csv"),("All Files","*.*")),
                             initialfile='PasswordPumpExport.csv',
                             title = "Create a file."
                            )
    print (name)
    try:                                                                       # Using try in case user types in unknown file or closes without choosing a file.
        with open(name,'r') as UseFile:
            print(UseFile.read())
    except:
        print("No file exists")

menu = Menu(window)
window.config(menu=menu)
file = Menu(menu)
file.add_command(label = 'Import from Chrome', command = ImportFileChrome)
file.add_command(label = 'Import from KeePass', command = ImportFileKeePass)
file.add_command(label = 'Import from PasswordPump', command = ImportFilePasswordPump)
file.add_command(label = 'Export to Chrome', command = ExportFile)
file.add_command(label = 'Export to KeePass', command = ExportFile)
file.add_command(label = 'Export to PasswordPump', command = ExportFile)
file.add_command(label = 'Exit', command = clickedClose)
menu.add_cascade(label = 'File', menu = file)

styles = ["0 - Tab","1 - Return"]
cbStyle = Combobox(window, values=styles, justify=LEFT, width=37)
cbStyle.grid(column=2, row=5)
cbStyle.bind('<<ComboboxSelected>>', on_style_select)

btn_previous = Button(window, text="<<Previous", command=clickedPrevious)
btn_previous.grid(column=1, row=7)

btn_insert = Button(window, text="Insert", command=clickedInsert)
btn_insert.grid(column=1, row=8)

btn_delete = Button(window, text="Delete", command=clickedDelete)
btn_delete.grid(column=1, row=9)

btn_open = Button(window, text="Open Port", command=clickedOpen)
btn_open.grid(column=4, row=0)

lb.bind("<<ListboxSelect>>", clickedLoadDB)

btn_url = Button(window, text="Save", command=clickedSave)
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
directions = """Select Edit with Computer on
the PasswordPump. After 
selecting the port click on
the Open Port button to open
the port for the PasswordPump."""
txt_dir.insert(END, directions)

ports = []
for n, (port, desc, hwid) in enumerate(sorted(comports()), 1):
    ports.append(port + ": " + desc)

cb = Combobox(window, values=ports, justify=LEFT, width=37, exportselection=False)
cb.grid(column=2, row=0)
cb.bind('<<ComboboxSelected>>', on_select)

position = 0                                                                   # Global variables
head = 0
tail = 0
selection = 0
state = "None"

window.mainloop()
