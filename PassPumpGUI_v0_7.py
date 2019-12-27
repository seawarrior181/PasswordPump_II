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
# - When an account is inserted the accounts list box doesn't refresh.
# - If there's a / at the end of a URL python throws an exception
# - If a password (or any other field) contains a ~ or a |, python throws an
#   exception
# - Sometimes changing the URL in place is not working
# - The 32nd character of the URL is missing after import.
# x Hangs the MCU when adding credentials without Style or URL.
# * After importing from a file the record selected and the record displayed
#   do not match.
# * Style is garbage when importing PasswordPump file.
# * When clicking on Next and Previous the Account List textbox selected
#   account isn't following along.
# * URLs are getting chopped off at 32 characters. Had to break the URL into 3
#   equally sized pieces and send them individually to the PasswordPump where
#   the final URL is assembled and saved to EEprom.
#
# Enhancements:
# - Add groups to the UI
# - When importing from PasswordPump format, import the groups, too.
# - Only allow one instance of the PasswordPump to run at a time.
# - Generate password
# - Save to old password
# * Import files via this UI.
# * Add a scrollbar to the account list box.
#
# Required Libraries:
# - PyCmdMessenger
#   https://github.com/harmsm/PyCmdMessenger
#   sudo pip3 install PyCmdMessenger
#   Then, starting on line 25 of PyCmdMessenger:
#                           field_separator="~",
#                           command_separator="|",
#                           escape_separator="\\",
#   On line 361 and 362 of the same PyCmdMessenger file add the following:
#   if value == 92:  # fix a defect whereby we freeze when the escape character is sent.
#       value = 0

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
import time

window = Tk()
window.title("PasswordPump Edit Credentials")
window.geometry('400x580')

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
    global position
    clickedAcct()
    clickedUser()
    clickedPass()
    clickedStyle()
    clickedUrl_New()
    updateGroup()
    global state
    if (state == "Inserting"):
        lb.delete(0,END)
        loadListBox()
    state = "None"

def clickedAcct():
    aResAcct = txt_acct.get()
    resAcct = aResAcct[0:32]
    global position                                                            # the position on EEprom, don't confuse with selection
    c.send("pyUpdateAccountName", resAcct)                                 # FindAccountPos called on an insert
    try:
        response = c.receive()                          # Number of argument formats must match the number of recieved arguments.
        print(response)
        response_list = response[1]
        last_position = position
        position = response_list[0]
        if position == 255:
            position = last_position
        txt_acct.config(state='normal')
        directions = """Updated account name."""
        updateDirections(directions)
        window.update()
    except ValueError as e:
        updateDirections("Value error encountered in clickedAcct; " + str(e))
        #c.send("pyGetAcctPos");
        #response = c.receive()
        #print(response)
        #response_list = response[1]
        #position = response_list[0]
    except Exception as ex:
        updateDirections("Exception encountered in clickedAcct; " + str(ex))
        raise ex

def clickedUser():
    global position
    aResUser = txt_user.get()
    resUser = aResUser[0:32]
    if (len(resUser) > 0):
        c.send("pyUpdateUserName", position + 2, resUser)
    else:
        c.send("pyUpdateUserName", position + 2, "")
    response = c.receive()
    print(response)
    response_list = response[1]
    position = response_list[0]
    txt_user.config(state='normal')
    directions = """Updated user name."""
    updateDirections(directions)
    window.update()

def clickedPass():
    global position
    aResPass = txt_pass.get()
    resPass = aResPass[0:32]
    if (len(resPass) > 0):
        c.send("pyUpdatePassword", position + 2, resPass)
    else:
        c.send("pyUpdatePassword", position + 2, "")
    response = c.receive()
    print(response)
    response_list = response[1]
    position = response_list[0]
    txt_pass.config(state='normal')
    directions = """Updated password."""
    updateDirections(directions)
    window.update()

def clickedStyle():
    global position
    resStyle = cbStyle.current()
    if ((resStyle != 0) and (resStyle != 1)):                                  # style must be 0 or 1
        resStyle = 0;                                                          # default is 0
    c.send("pyUpdateStyle", position + 2, resStyle)
    response = c.receive()
    print(response)
    response_list = response[1]
    position = response_list[0]
    directions = """Updated style."""
    updateDirections(directions)
    window.update()

def updateGroup():
    global position
    global group
    c.send("pyUpdateGroup", position + 2, group + 2)
    response = c.receive()
    print(response)
    response_list = response[1]
    position = response_list[0]
    directions = """Updated groups."""
    updateDirections(directions)
    window.update()

def clickedUrl():
    global position
    aURL = txt_url.get()
    resURL = aURL[0:32]                                                        # max length of a URL is 96 chars
    #resURL = resURL.replace("/","^")
    txt_url.config(state='normal')
    if (len(resURL) > 0):                                                      # if the URL doesn't exist don't send it
        c.send("pyUpdateURL", position + 2, resURL)
    else:
        c.send("pyUpdateURL", position + 2, "")
    response = c.receive()
    print(response)
    response_list = response[1]
    position = response_list[0]
    txt_url.config(state='normal')
    directions = """Updated URL."""
    updateDirections(directions)
    window.update()

def clickedUrl_New():                                                          # send the website over in 3 chunks instead of all at once to circumvent problems encountered when sending it all at once.
    txt_url.config(state='normal')
    global position
    aURL = txt_url.get()
    resURL_1 = aURL[0:32]                                                      # max length of a URL is 96 chars
    if (len(resURL_1) > 0):                                                    # if the URL doesn't exist don't send it
        c.send("pyUpdateURL_1", resURL_1)
        response = c.receive()
        print(response)
        response_list = response[1]
        position = response_list[0]
        resURL_2 = aURL[32:63]                                                 # max length of a URL is 96 chars
        if (len(resURL_2) > 0):                                                # if the URL doesn't exist don't send it
            c.send("pyUpdateURL_2", resURL_2)
            response = c.receive()
            print(response)
            response_list = response[1]
            position = response_list[0]
            resURL_3 = aURL[64:96]                                             # max length of a URL is 96 chars
            if (len(resURL_3) > 0):                                            # if the URL doesn't exist don't send it
                c.send("pyUpdateURL_3", position + 2, resURL_3)
                response = c.receive()
                print(response)
                response_list = response[1]
                position = response_list[0]
            else:
                c.send("pyUpdateURL_3", position + 2, "")
                response = c.receive()
                print(response)
                response_list = response[1]
                position = response_list[0]
        else:
            c.send("pyUpdateURL", position + 2, aURL)
            response = c.receive()
            print(response)
            response_list = response[1]
            position = response_list[0]
    else:
        c.send("pyUpdateURL", position + 2, "")
        response = c.receive()
        print(response)
        response_list = response[1]
        position = response_list[0]
    txt_url.config(state='normal')
    directions = """Updated URL."""
    updateDirections(directions)
    window.update()

def clickedClose():
    global arduinoAttached
    if (arduinoAttached == 1):
        try:
            c.send("pyExit")
            response = c.receive()
            print(response)
            response_list = response[1]
            acctCount = response_list[0]
            print(acctCount)
        except Exception as e:
            updateDirections("There was an error closing the application; " + str(e))
    sys.exit(1)

def clickedPrevious():
    global position
    c.send("pyGetPrevPos", position + 2)
    response = c.receive()
    print(response)
    response_list = response[1]
    global selection
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
    global position
    c.send("pyGetNextPos", position + 2)
    response = c.receive()
    print(response)
    response_list = response[1]
    global selection
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

def loadListBox():  # TODO: reorganize the logic in this function
    window.config(cursor="watch")                                              # TODO: this is not working
    lb.delete(0,END)                                                           # clear out the listbox
    c.send("pyReadHead")                                                       # Get the list head
    global position
    global head
    try:
        response = c.receive()
        response_list = response[1]
        head = response_list[0]
        position = head
        global accountDict
        accountDict = ({})                                                     # Load the dictionary
        while position < 255:                                                  # '<' not supported between instances of 'str' and 'int'
            c.send("pyReadAccountName", position + 2)
            try:
                try:
                    response = c.receive()
                    accountName_list = response[1]
                except Exception as e:
                    updateDirections("Call to pyReadAccountName returned None; " + str(e) + " Trying again.")
                    time.sleep(1)
                    c.send("pyReadAccountName", position + 2)
                    response = c.receive()
                    accountName_list = response[1]
                accountName = accountName_list[0]
            except UnicodeDecodeError as e:
                updateDirections("UnicodeDecodeError in pyReadAccountName; " + str(e))
                accountName = "UnicodeDecodeError"
            except ValueError as ve:
                updateDirections("ValueError in pyReadAccountName; " + str(ve))
                accountName = "ValueError"
            except Exception as e:
                updateDirections("Exception in pyReadAccountName; " + str(e))
                accountName = "Exception"
                #raise e
            accountDict[accountName] = position
            lb.insert(END, accountName)                                        # Load the listbox
            window.update()
            c.send("pyGetNextPos", position + 2)                               # calls getNextPtr(acctPosition) in C program
            try:
                response = c.receive()
                response_list = response[1]
                position = response_list[0]
            except ValueError as ve:
                updateDirections("Error in pyGetNextPos; " + str(ve))
                raise ve
            except Exception as e:
                updateDirections("Exception in pyGetNextPos; " + str(e))
                raise e
        lb.activate(0)
        global selection
        selection = 0
        lb.select_set(selection)
        position = head
        getRecord()
        lb.bind("<Down>", OnEntryDown)
        lb.bind("<Up>", OnEntryUp)
        window.config(cursor="")
    except ValueError as ve:
        updateDirections("ValueError in pyReadHead, pyReadAccountName or pyGetNextPos; " + str(ve))
        head = 0
    except Exception as e:
        updateDirections("Exception in pyReadHead, pyReadAccountName or pyGetNextPos; " + str(e))

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
    #time.sleep(1)
    print("sending pyGetNextFreePos")
    c.send("pyGetNextFreePos")
    response = c.receive()  # freezes MCU (times out after 5 sec) when inserting second row of import file
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
    global accountDict
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
    c.send("pyDeleteAccount",position + 2)
    response = c.receive()
    print(response)
    response_list = response[1]
    position = response_list[0]
    getRecord()

def clickedOpen():
    global arduino
    global arduinoAttached
    try:                                                                       #
        arduino = PyCmdMessenger.ArduinoBoard(port, baud_rate=115200, timeout=5.0, settle_time=2.0, enable_dtr=False,
                                              int_bytes=4, long_bytes=8, float_bytes=4, double_bytes=8)
        arduinoAttached = 1
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
                ["pyReadGroup", "b"],
                ["pyReadOldPassword", "b"],
                ["pyUpdateAccountName", "s"],
                ["pyUpdateUserName", "bs"],
                ["pyUpdatePassword", "bs"],
                ["pyUpdateURL", "bs"],
                ["pyUpdateURL_1", "s"],
                ["pyUpdateURL_2", "s"],
                ["pyUpdateURL_3", "bs"],
                ["pyUpdateStyle", "bs"],
                ["pyUpdateGroup","bb"],
                ["pyGetNextPos","b"],
                ["pyGetPrevPos","b"],
                ["pyGetAcctPos",""],
                ["pyReadHead",""],
                ["pyReadTail",""],
                ["pyGetNextFreePos",""],
                ["kError",""],
                ["pyDeleteAccount","b"],
                ["pyExit",""],
                ["pyGetAccountCount",""]]
    global c                                                                   # Initialize the messenger
    c = PyCmdMessenger.CmdMessenger(arduino, commands)
    c.send("pyReadHead")
    try:
        response = c.receive() # struct.error: unpack requires a buffer of 1 bytes
        print(response)
        response_list = response[1]
        global head
        head = response_list[0]
    except Exception as e:
        updateDirections("Exception encountered reading return value from pyReadHead; " + str(e))
        head = 0
    global position
    position = head
    c.send("pyGetAccountCount")
    response = c.receive()
    print(response)
    global acctCount
    try:
        response_list = response[1]
        acctCount = response_list[0]
    except TypeError as te:
        updateDirections("TypeError encountered in clickedOpen(); " + str(te))
        acctCount = 0
    if (acctCount > 0):
        getRecord()
    btn_close.config(state='normal')
    directions = """Opened port"""
    txt_dir.delete('1.0', END)
    txt_dir.insert(END, directions)
    print (directions)
    if (acctCount > 0):
        loadListBox()
    btn_open.config(state='disabled')
    cb.config(state='disabled')
    window.update()

def getRecord():
    global position
    global group
    global vFavorites
    global vWork
    global vPersonal
    global vHome
    global vSchool
    global vFinancial
    global vMail
    global vCustom
    print(position)
    c.send("pyReadAccountName", position + 2)
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
    c.send("pyReadUserName", position + 2)
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
    c.send("pyReadPassword", position + 2)
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

    c.send("pyReadStyle", position + 2)
    try:
        response = c.receive()
        print(response)
        style_list = response[1]
        style = style_list[0]
    except UnicodeDecodeError:
        print("pyReadStyle returned empty string")
        style = ""
    cbStyle.set(style)

    c.send("pyReadURL", position + 2)
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

    c.send("pyReadGroup", position + 2)
    try:
        response = c.receive() # struct.error: unpack requires a buffer of 1 bytes for account USB
        print(response)
        group_list = response[1]
        group = int(group_list[0])
    except UnicodeDecodeError as ude:
        print("pyReadGroup did not return group")
        updateDirections("pyReadGroup did not return group; " + str(ude))
        group = 0
    except Struct.error as e:
        updateDirections("Struct.error encountered after pyReadGroup; Group: " + str(group) + " " + str(e))
    SetGroupCheckBoxes()

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
    global position
    try:                                                                       # Using try in case user types in unknown file or closes without choosing a file.
        with open(name, newline='') as csvfile:
            reader = csv.DictReader(csvfile)
            try:
                for row in reader:
                    print(row)
                    print(row['name'], row['url'], row['username'], row['password'])
                    txt_acct.delete(0, END)
                    txt_user.delete(0, END)
                    txt_pass.delete(0, END)
                    txt_url.delete(0, END)
                    txt_acct.insert(0,row['name'])
                    txt_user.insert(0,row['username'])
                    txt_pass.insert(0,row['password'])
                    txt_url.insert(0,row['url'])
                    window.update()
                    clickedAcct()                                              # sets position = FindAccountPos()
                    clickedUser()
                    clickedPass()
                    clickedStyle()
                    clickedUrl_New()
                    updateDirections("Record saved.")
                updateDirections("All records saved.")
                #lb.delete(0, END)
                loadListBox()
            except Exception as e:
                updateDirections("Error encountered reading file in ImportFileChrome; "+ str(e))
    except Exception as ex:
        updateDirections("Error encountered in ImportFileChrome; " + ex)

def ImportFilePasswordPump():
    name = askopenfilename(initialdir="C:/",                                   # TODO: make this work cross platform
                           filetypes =(("CSV File", "*.csv"),("All Files","*.*")),
                           title = "Choose a file."
                          )
    print (name)
    global position
    global group
    try:                                                                       # Using try in case user types in unknown file or closes without choosing a file.
        with open(name, newline='') as csvfile:
            fieldnames = ['accountname', 'username', 'password', 'url', 'group']
            reader = csv.DictReader(csvfile, fieldnames=fieldnames)
            try:
                for row in reader:
                    print(row)
                    print(row['accountname'], row['username'], row['password'], row['url'], row['group'])
                    txt_acct.delete(0, END)
                    txt_user.delete(0, END)
                    txt_pass.delete(0, END)
                    txt_url.delete(0, END)
                    txt_acct.insert(0,row['accountname'])
                    txt_user.insert(0,row['username'])
                    txt_pass.insert(0,row['password'])
                    txt_url.insert(0,row['url'])
                    group = int(row['group'])
                    SetGroupCheckBoxes()
                    window.update()
                    clickedAcct()                                              # sets position = FindAccountPos()
                    clickedUser()
                    clickedPass()
                    clickedStyle()
                    clickedUrl_New()
                    updateGroup()
                    updateDirections("Record saved.")
                updateDirections("All records saved.")
                #lb.delete(0, END)
                loadListBox()
            except Exception as e:
                updateDirections("Error encountered reading file in ImportFilePasswordPump; "+ str(e))
    except Exception as ex:
        updateDirections("Error encountered in ImportFilePasswordPump; " + ex)

def ImportFileKeePass():
    name = askopenfilename(initialdir="C:/",                                   # TODO: make this work cross platform
                           filetypes =(("CSV File", "*.csv"),("All Files","*.*")),
                           title = "Choose a file."
                          )
    print (name)
    global position
    try:                                                                       # Using try in case user types in unknown file or closes without choosing a file.
        with open(name, newline='') as csvfile:
            reader = csv.DictReader(csvfile)
            try:
                for row in reader:
                    print(row)
                    print(row['Account'], row['Login Name'], row['Password'], row['Web Site'])
                    txt_acct.delete(0, END)
                    txt_user.delete(0, END)
                    txt_pass.delete(0, END)
                    txt_url.delete(0, END)
                    txt_acct.insert(0,row['Account'])
                    txt_user.insert(0,row['Login Name'])
                    txt_pass.insert(0,row['Password'])
                    txt_url.insert(0,row['Web Site'])
                    window.update()
                    clickedAcct()                                              # sets position = FindAccountPos()
                    clickedUser()
                    clickedPass()
                    clickedStyle()
                    clickedUrl_New()
                    updateDirections("Record saved.")
                updateDirections("All records saved.")
                #lb.delete(0, END)
                loadListBox()
            except Exception as e:
                updateDirections("Error encountered processing file in ImportFileKeePass; "+ str(e))
    except Exception as ex:
        updateDirections("Error encountered in ImportFileKeePass; " + ex)

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
    name = asksaveasfilename(initialdir="C:/",                                 # TODO: make this work cross platform
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

def OnFavorites():
    global group
    global vFavorites
    if (vFavorites.get() == 1):
        group = group | 1
    else:
        group = group & (~1)

def OnWork():
    global group
    global vWork
    if (vWork.get() == 1):
        group = group | 2
    else:
        group = group & (~2)

def OnPersonal():
    global group
    global vPersonal
    if (vPersonal.get() == 1):
        group = group | 4
    else:
        group = group & (~4)

def OnHome():
    global group
    global vHome
    if (vHome.get() == 1):
        group = group | 8
    else:
        group = group & (~8)

def OnSchool():
    global group
    global vSchool
    if (vSchool.get() == 1):
        group = group | 16
    else:
        group = group & (~16)

def OnFinancial():
    global group
    global vFinancial
    if (vFinancial.get() == 1):
        group = group | 32
    else:
        group = group & (~32)

def OnMail():
    global group
    global vMail
    if (vMail.get() == 1):
        group = group | 64
    else:
        group = group & (~64)

def OnCustom():
    global group
    global vCustom
    if (vCustom.get() == 1):
        group = group | 128
    else:
        group = group & (~128)

def SetGroupCheckBoxes():
    global vFavorites
    global vWork
    global vPersonal
    global vHome
    global vSchool
    global vFinancial
    global vMail
    global vCustom
    if ((group & 1) == 1):
        vFavorites.set(1)
    else:
        vFavorites.set(0)
    if ((group & 2) == 2):
        vWork.set(1)
    else:
        vWork.set(0)
    if ((group & 4) == 4):
        vPersonal.set(1)
    else:
        vPersonal.set(0)
    if ((group & 8) == 8):
        vHome.set(1)
    else:
        vHome.set(0)
    if ((group & 16) == 16):
        vSchool.set(1)
    else:
        vSchool.set(0)
    if ((group & 32) == 32):
        vFinancial.set(1)
    else:
        vFinancial.set(0)
    if ((group & 64) == 64):
        vMail.set(1)
    else:
        vMail.set(0)
    if ((group & 128) == 128):
        vCustom.set(1)
    else:
        vCustom.set(0)
    window.update()

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
btn_previous.grid(column=1, row=17)

btn_insert = Button(window, text="Insert", command=clickedInsert)
btn_insert.grid(column=1, row=18)

btn_delete = Button(window, text="Delete", command=clickedDelete)
btn_delete.grid(column=1, row=19)

btn_open = Button(window, text="Open Port", command=clickedOpen)
btn_open.grid(column=4, row=0)

lb.bind("<<ListboxSelect>>", clickedLoadDB)

btn_url = Button(window, text="Save", command=clickedSave)
btn_url.grid(column=4, row=18)

btn_next = Button(window, text="Next>>", command=clickedNext)
btn_next.grid(column=4, row=17)

btn_close = Button(window, text=" Exit ", command=clickedClose)
btn_close.grid(column=4, row=19)

btn_url.config(state='normal')
btn_close.config(state='normal')

vFavorites = IntVar()
vWork = IntVar()
vPersonal = IntVar()
vHome = IntVar()
vSchool = IntVar()
vFinancial = IntVar()
vMail = IntVar()
vCustom = IntVar()

textboxFavorites = Checkbutton(window, text="Favorites", variable=vFavorites, command=OnFavorites, onvalue=1, offvalue=0)
textboxFavorites.var = vFavorites
textboxFavorites.grid(column=1,row=11)

textboxWork = Checkbutton(window, text="Work      ", variable=vWork, command=OnWork, onvalue=1, offvalue=0)
textboxWork.var = vWork
textboxWork.grid(column=1,row=12)

textboxPersonal = Checkbutton(window, text="Personal ", variable=vPersonal, command=OnPersonal, onvalue=1, offvalue=0)
textboxPersonal.var = vPersonal
textboxPersonal.grid(column=1,row=13)

textboxHome = Checkbutton(window, text="Home     ", variable=vHome, command=OnHome, onvalue=1, offvalue=0)
textboxHome.var = vHome
textboxHome.grid(column=1,row=14)

textboxSchool = Checkbutton(window, text="School   ", variable=vSchool, command=OnSchool, onvalue=1, offvalue=0)
textboxSchool.var = vSchool
textboxSchool.grid(column=2,row=11)

textboxFinancial = Checkbutton(window, text="Financial", variable=vFinancial, command=OnFinancial, onvalue=1, offvalue=0)
textboxFinancial.var = vFinancial
textboxFinancial.grid(column=2,row=12)

textboxMail = Checkbutton(window, text="Mail       ", variable=vMail, command=OnMail, onvalue=1, offvalue=0)
textboxMail.var = vMail
textboxMail.grid(column=2,row=13)

textboxCustom = Checkbutton(window, text="Custom", variable=vCustom, command=OnCustom, onvalue=1, offvalue=0)
textboxCustom.var = vCustom
textboxCustom.grid(column=2,row=14)

lbl_help = Label(window, text="Instructions", anchor=W, justify=CENTER, width=11)
lbl_help.grid(column=2, row=15)

txt_dir = Text(window, height=5, width=30, relief=FLAT, background="light grey")
txt_dir.grid(column=2, row=16)
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
arduinoAttached = 0
group = 0

window.mainloop()
