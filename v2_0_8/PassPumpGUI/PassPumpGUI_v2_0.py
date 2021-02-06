#!/usr/bin/env python
#                ___                              _ ___
#               | _ \__ _ _______ __ _____ _ _ __| | _ \_  _ _ __  _ __
#               |  _/ _` (_-<_-< V  V / _ \ '_/ _` |  _/ || | '  \| '_ \
#               |_| \__,_/__/__/\_/\_/\___/_| \__,_|_|  \_,_|_|_|_| .__/
# Author:       Daniel J. Murphy                                  |_|
# File:         PassPumpGUI_v2_0.py
# Version:      2.0.8.02
# Date:         2019/07/26 - 2021/02/04
# Language:     Python
#
# Purpose
# =======
# This is the client side  of  the  PasswordPump.  This  program's  job  is  to
# allow the user to edit the credentials that  are  stored  inside  the  EEprom
# chips that reside on the PasswordPump device.  With this program you can also
# edit may other attributes of the PasswordPump.
#
# Documentation
# =============
# To view the Users Guide:
#   https://github.com/seawarrior181/PasswordPump_II/blob/master/Password%20Pump%20II%20Users%20Guide.pdf
# For more information about this project visit
#   https://www.5volts.org/post/passwordpump-v2-0.
# To see the source code in GitHub point your browser to
#   https://github.com/seawarrior181/PasswordPump_II.
# To purchase a kit visit
#   https://www.tindie.com/products/passwordpump/passwordpump-v20/
# To see a video about the project navigate to
#   https://www.youtube.com/watch?v=f4Iukt5VDUo.
#
# Copyright
# =========
# Copyright ©2018, ©2019, ©2020, ©2021 Daniel J Murphy <dan-murphy@comcast.net>
#
# Built on Python 3.8 (Windows) and Python 3.7 (RaspberryPi)
#
# Defects and Enhancements
# ========================
# Key:
#  - = outstanding
#  x = fixed but needs testing
#  * = fixed
#
# Defects:
# - If a password starts with a 0 it is left off when exported into a .csv
#   file.
# - If an account name contains a comma, and you visit the field, after
#   exiting the GUI and reloading all of the accounts, the comma has changed
#   into a hashtag and all of the remaining fields are blank.
# x After adding a new account, if the style isn't specified (or left on the
#   default), ValueError: invalid literal for int() with base 10: '' occurs
#   on subsequent visits to that account.
# * Unable so save exported PasswordPump format file under Linux.
# * During file export if you cancel out of the operation an unencrypted file
#   is written anyhow.  Present 11/24/2020 - 11/27/2020.
# * After exporting to PasswordPump format: ValueError in pyReadStyle; invalid
#   literal for int() with base 10: ''
# * Before the port is open you can navigate to and edit fields, resulting in
#   error messages displaying.
# * Change the 0 / 1 for Tab and Return to just Tab and Return.  Select tab
#   as the default.
# * If input focus is on the password field, and you select Insert, then
#   navigate to the Account field, the password field of the account you
#   were on originally is set to blank.
# * During import of PasswordPump format, the username is occasionally dropped
# * Similarly, if any of the fields have an embedded | (pipe) character the
#   fields in the PasswordPumpGUI can get out of synch; e.g. account name
#   appears in the username field.
# * If a password (or any other field) contains a ~ or a |, python throws an
#   exception during import or changes those characters into /1 otherwise.
# * If there's a / at the end of a URL during import python throws an
#   exception, so strip it.
# * Hangs the MCU when adding credentials without Style or URL.
# * Sometimes changing the URL in place is not working
# * All buttons except Exit should be disabled before the port is opened.
# * When an account is inserted the accounts list box doesn't refresh, you must
#   click on Save.
# * Add style to the PP format.
# * Remove the Save button.
# * skip the heading row if it exists when importing PasswordPump format.
# * In this UI make style last
# * The 32nd character of the URL is missing after import.
# * Leading spaces are not respected in Account Name.
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
# - Select a Font via PasswordPumpGUI
# - Set the Orientation via PasswordPumpGUI
# - Set the Encoder Type via PasswordPumpGUI
# - Set the Keyboard Language via PasswordPumpGUI
# - Make lock PC screen on automatic logout configurable
# - Allow the user to set client type so that logout and lock can work on linux
# - When exporting a file in PasswordPump format require the re-entry of the
#   specified password to confirm that it's correct.
# - Rename account
# - Enable decryption functionality before connecting to a PasswordPump
# * Add setting inter char delay in more settings
# * Set generated password length on device and for PasswordPumpGUI
# * Configurable Generate Password length
# * Encrypt the files from the GUI
# * Optionally encrypt the PasswordPump export format
# * Settings (RGB LED Intensity, Timeout Minutes, Login Attempts)
# * Settings (Show Password, Decoy Password, Change Master Password,
#   Factory Reset, Fix Corrupt Linked List, Customize Groups)
# * Custom group names
# * Respect the show password setting
# * Add old password to PasswordPump format
# * Save to old password
# * Generate password
# * Export to PasswordPump format
# * Only allow one instance of the PasswordPump to run at a time.
# * Confirm before deleting
# * When importing from PasswordPump format, import the groups, too.
# * Save a field when it loses focus (via <Tab> or <Return> or clicking out of
#   the field)
# * Add groups to the UI
# * Import files via this UI.
# * Add a scrollbar to the account list box.
#
# Required Libraries
# ==================
# - Tendo
#   pip install tendo
# - PyCmdMessenger
#   https://github.com/harmsm/PyCmdMessenger
#   sudo pip3 install PyCmdMessenger
# - Tkinter
#   sudo apt-get install python3.6-tk   -OR-
#   sudo apt-get install python3-tk
# - powned
#   pip install powned
# - cryptography
#   sudo pip3 install cryptography
#
# See the Users Guide for installation instructions.
# https://github.com/seawarrior181/PasswordPump_II/blob/master/Password%20Pump%20II%20Users%20Guide.pdf
#
# Generating the Executable File
# ==============================
# 1) Comment out the code related to tendo.
# 2) cd E:\C\repos\murphyrepo\dev\GitHub\PasswordPump_II\v2_0_8\PassPumpGUI
# 3) pyinstaller cli.py --onefile --paths=E:\C\repos\murphyrepo\dev\GitHub\PasswordPump_II\v2_0_8\PassPumpGUI -w --name PasswordPumpGUI
# 4) pyinstaller PasswordPumpGUI.spec --onefile --paths=E:\C\repos\murphyrepo\dev\GitHub\PasswordPump_II\v2_0_8\PassPumpGUI -w --name PasswordPumpGUI
# 5) Commit file E:\C\repos\murphyrepo\dev\GitHub\PasswordPump_II\v2_0_8\PassPumpGUI\dist\PasswordPumpGUI.exe to git
#
# Generating the Executable File on RaspberryPi OS
# ================================================
# 1) Comment out the code related to tendo.
# 2) cd /home/pi/repos/murphyrepo/dev/GitHub/PasswordPump_II/v2_0_8/PassPumpGUI
# 3) /home/pi/.local/bin/pyinstaller cli.py --onefile --paths=/home/pi/repos/murphyrepo/dev/GitHub/PasswordPump_II/v2_0_8/PassPumpGUI -w --name PasswordPumpGUI
# 4) /home/pi/.local/bin/pyinstaller PasswordPumpGUI.spec --onefile --paths=/home/pi/repos/murphyrepo/dev/GitHub/PasswordPump_II/v2_0_8/PassPumpGUI -w --name PasswordPumpGUI
# 5) Commit file E:\C\repos\murphyrepo\dev\GitHub\PasswordPump_II\v2_0_8\PassPumpGUI\dist\PasswordPumpGUI.exe to git
#
# If you have access to additional operating systems and would like to contribute an executable flavor that would be
# greatly appreciated.  I don't know if the RaspberryPi executable will work on other flavors of Linux or MacOS.
#
#  License
#  =======
#  Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International
#  (CC BY-NC-SA 4.0). https://creativecommons.org/licenses/by-nc-sa/4.0/
#  This program and device are distributed in the hope that they will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
#  or FITNESS FOR A PARTICULAR PURPOSE.
#
#  You are free to:
#    Share — copy and redistribute the material in any medium or format
#    Adapt — remix, transform, and build upon the material
#    The licensor cannot revoke these freedoms as long as you follow the license
#    terms.
#
#  Under the following terms:
#  Attribution — You must give appropriate credit, provide a link to the license,
#  and indicate if changes were made. You may do so in any reasonable manner, but
#  not in any way that suggests the licensor endorses you or your use.
#
#  NonCommercial — You may not use the material for commercial purposes.
#
#  ShareAlike — If you remix, transform, or build upon the material, you must
#  distribute your contributions under the same license as the original.
#
#  No additional restrictions — You may not apply legal terms or technological
#  measures that legally restrict others from doing anything the license permits.
#
#  Notices:
#  You do not have to comply with the license for elements of the material in the
#  public domain or where your use is permitted by an applicable exception or
#  limitation.
#
#  No warranties are given. The license may not give you all of the permissions
#  necessary for your intended use. For example, other rights such as publicity,
#  privacy, or moral rights may limit how you use the material.

from cryptography.fernet import Fernet
from random import *
from serial.tools.list_ports import comports                                    # be advised, this is from pyserial lib, not the serial lib!
from serial.serialutil import SerialException
from shutil import copyfile
#from tendo import singleton                                                    # enabling this functionality makes it impossible to create an .exe file on Windows
from tkinter import *
from tkinter import messagebox
from tkinter.ttk import *
from tkinter.filedialog import askopenfilename
from tkinter.filedialog import asksaveasfilename
from tkinter.filedialog import askdirectory

import base64
import csv
import os
import platform
import powned
import PyCmdMessenger
import requests
import subprocess
import sys
import time
import tkinter.messagebox
import tkinter.simpledialog
import webbrowser


def install(package):
    subprocess.check_call([sys.executable, "-m", "pip", "install", package])


def updateCheck():
    global updateWindow
    try:
        updateWindow = Toplevel()
        updateWindow.title(string="Update Checker")
        updateWindow.resizable(False, False)
        versionContents = 'Version:2.0.8.02'                                    # the current version
        if platform.system() == "Windows":                                      # Windows
            latestVersion = "https://github.com/seawarrior181/PasswordPump_II/raw/master/v2_0_8/PassPumpGUI/dist/PasswordPumpGUI.exe"
        elif platform.system() == "Darwin":                                     # Macintosh
            latestVersion = "https://github.com/seawarrior181/PasswordPump_II/blob/master/v2_0_8/PassPumpGUI/PassPumpGUI_v2_0.py"
        elif platform.system() == "Linux":                                      # Linux
            latestVersion = "https://github.com/seawarrior181/PasswordPump_II/blob/master/v2_0_8/PassPumpGUI/PassPumpGUI_v2_0.py"
        else:                                                                    # Anything else
            latestVersion = "https://github.com/seawarrior181/PasswordPump_II/blob/master/v2_0_8/PassPumpGUI/PassPumpGUI_v2_0.py"
        response = requests.get(
            'https://github.com/seawarrior181/PasswordPump_II/blob/master/v2_0_8/NewestVersion.txt')  # gets newest version
        updateContents = response.text
        verIdx = updateContents.find("Version:")
        version = updateContents[verIdx:verIdx + 16]
        if version != versionContents:
            versionLabel = Label(updateWindow,
                                 text="\n\n A program update is availible.\n\n    Current "
                                      + versionContents + "\n    Latest    " + version + "\n\n Download the latest version from:\n\n " +
                                      latestVersion + "\n\n by clicking on the Download button.\n\n")
            downloadButton = Button(updateWindow, text="Download", command=downloadLatest)
            versionLabel.pack()
            downloadButton.pack()
        else:
            versionLabel = Label(updateWindow,
                                 text="\n\n You are running the most up to date version. " + versionContents + " \n\n")
            versionLabel.pack()
    except Exception as ex:
        updateDirections("Unable to check the version of the PasswordPumpGUI:\r\n" + str(ex))


def downloadLatest():
    try:
        if platform.system() == "Windows":                                      # Windows
            url = 'https://github.com/seawarrior181/PasswordPump_II/raw/master/v2_0_8/PassPumpGUI/inno/PasswordPumpSetup.exe'
            print(__file__)
            downloadLocation = get_download_path() + "\PasswordPumpSetup.exe"
        elif platform.system() == "Darwin":                                     # Macintosh
            url = 'https://raw.githubusercontent.com/seawarrior181/PasswordPump_II/master/v2_0_8/PassPumpGUI/PassPumpGUI_v2_0.py'
            downloadLocation = __file__
        elif platform.system() == "Linux":                                      # Linux
            url = 'https://raw.githubusercontent.com/seawarrior181/PasswordPump_II/master/v2_0_8/PassPumpGUI/PassPumpGUI_v2_0.py'
            downloadLocation = __file__
        else:                                                                    # Anything else
            url = 'https://raw.githubusercontent.com/seawarrior181/PasswordPump_II/master/v2_0_8/PassPumpGUI/PassPumpGUI_v2_0.py'
            downloadLocation = __file__
        req = requests.get(url, allow_redirects=True)


        if platform.system() == "Windows":                                      # Windows
            open(downloadLocation, 'wb').write(req.content)
            downloadedLabel = Label(updateWindow,
                                    text="\n The latest version of PasswordPumpGUI setup program was downloaded to:\n\n  " + " " + downloadLocation + "\n\n" +
                                         " Exit this program and run PasswordPumpSetup.exe from\n\n  " + downloadLocation + ". \n\n"
                                         " Then restart the program from the start menu or your Desktop. \n\n" +
                                         " This is also a good time to update to the latest version of the PasswordPump firmware.\n" +
                                         " See the Users Guide for detailed instructions, it's location has been copied to the global/system clipboard.\n" +
                                         " Check to see if your version of the firmware is up-to-date by connecting to your PasswordPump device from \n" +
                                         " PasswordPumpGUI and navigating to Help->Check for Firmware Updates." +
                                         "\n\n ")
        elif platform.system() == "Darwin":                                     # Macintosh
            open(downloadLocation + ".new", 'wb').write(req.content)
            downloadedLabel = Label(updateWindow,
                                    text="\n The latest version of PasswordPumpGUI was downloaded to:\n\n" + " " + downloadLocation + ".new\n\n" +
                                         " Exit the program and rename\n\n" +
                                         "   " + downloadLocation + " to\n" +
                                         "   " + downloadLocation + ".old\n\n and rename\n\n" +
                                         "   " + downloadLocation + ".new to\n" +
                                         "   " + downloadLocation + "\n\n then restart the program from your Desktop." +
                                         "\n This is also a good time to update to the latest version of the PasswordPump firmware.\n" +
                                         " See the Users Guide for detailed instructions, it's location has been copied to the global/system clipboard.\n" +
                                         " Check to see if your version of the firmware is up-to-date by connecting to your PasswordPump device from \n" +
                                         " PasswordPumpGUI and navigating to Help->Check for Firmware Updates." +
                                         "\n\n ")
        elif platform.system() == "Linux":                                      # Linux
            open(downloadLocation + ".new", 'wb').write(req.content)
            downloadedLabel = Label(updateWindow,
                                    text="\n The latest version of PasswordPumpGUI was downloaded to:\n\n" + " " + downloadLocation + ".new\n\n" +
                                         " Exit the program and rename\n\n" +
                                         "   " + downloadLocation + " to\n" +
                                         "   " + downloadLocation + ".old\n\n and rename\n\n" +
                                         "   " + downloadLocation + ".new to\n" +
                                         "   " + downloadLocation + "\n\n then restart the program from your Desktop." +
                                         "\n This is also a good time to update to the latest version of the PasswordPump firmware.\n" +
                                         " See the Users Guide for detailed instructions, it's location has been copied to the global/system clipboard.\n" +
                                         " Check to see if your version of the firmware is up-to-date by connecting to your PasswordPump device from \n" +
                                         " PasswordPumpGUI and navigating to Help->Check for Firmware Updates." +
                                         "\n\n ")
        else:                                                                    # Anything else
            open(downloadLocation + ".new", 'wb').write(req.content)
            downloadedLabel = Label(updateWindow,
                                    text="\n The latest version of PasswordPumpGUI was downloaded to:\n\n" + " " + downloadLocation + ".new\n\n" +
                                         " Exit the program and rename\n\n" +
                                         "   " + downloadLocation + " to\n" +
                                         "   " + downloadLocation + ".old\n\n and rename\n\n" +
                                         "   " + downloadLocation + ".new to\n" +
                                         "   " + downloadLocation + "\n\n then restart the program from your Desktop." +
                                         "\n This is also a good time to update to the latest version of the PasswordPump firmware.\n" +
                                         " See the Users Guide for detailed instructions, it's location has been copied to the global/system clipboard.\n" +
                                         " Check to see if your version of the firmware is up-to-date by connecting to your PasswordPump device from \n" +
                                         " PasswordPumpGUI and navigating to Help->Check for Firmware Updates." +
                                         "\n\n ")
        downloadedLabel.pack()
        updateDirections("Latest version of\nPasswordPumpGUI downloaded.")
        r = Tk()                                                                # copy the URL to the global/system clipboard
        r.withdraw()
        r.clipboard_clear()                                                     # since this is a potentially destructive action add a button and ask the user if they want to do this.
        r.clipboard_append(usersGuideLocation)
        r.update()                                                              # now it stays on the clipboard after the window is closed
        r.destroy()
    except Exception as ex:
        updateDirections("Unable to download the latest version of the PasswordPumpGUI:\r\n" + str(ex))

def get_download_path():
    """Returns the default downloads path for linux or windows"""
    if os.name == 'nt':
        import winreg
        sub_key = r'SOFTWARE\Microsoft\Windows\CurrentVersion\Explorer\Shell Folders'
        downloads_guid = '{374DE290-123F-4565-9164-39C4925E467B}'
        with winreg.OpenKey(winreg.HKEY_CURRENT_USER, sub_key) as key:
            location = winreg.QueryValueEx(key, downloads_guid)[0]
        return location
    else:
        return os.path.join(os.path.expanduser('~'), 'downloads')

def updateFirmwareCheck():
    global firmwareUpdateWindow
    global inputType
    global boardType
    global urlM0Encoder
    global urlM0Joystick
    global urlM4Encoder
    global urlM4Joystick
    urlM0Encoder = "https://github.com/seawarrior181/PasswordPump_II/tree/master/v2_0_8/bin/M0/encoder/PasswordPump_v_2_0.ino.bin"
    urlM0Joystick = "https://github.com/seawarrior181/PasswordPump_II/tree/master/v2_0_8/bin/M0/joystick/PasswordPump_v_2_0.ino.bin"
    urlM4Encoder = "https://github.com/seawarrior181/PasswordPump_II/tree/master/v2_0_8/bin/M4/encoder/PasswordPump_v_2_0.ino.bin"
    urlM4Joystick = "https://github.com/seawarrior181/PasswordPump_II/tree/master/v2_0_8/bin/M4/joystick/PasswordPump_v_2_0.ino.bin"
    try:
        firmwareUpdateWindow = Toplevel()
        firmwareUpdateWindow.title(string="Firmware Update Checker")
        firmwareUpdateWindow.resizable(False, False)
        response = requests.get(
            'https://github.com/seawarrior181/PasswordPump_II/blob/master/v2_0_8/NewestVersionFirmware.txt')  # gets newest version
        updateContents = response.text
        verIdx = updateContents.find("Version:")
        version = updateContents[verIdx:verIdx + 16]
        updateDirections(version)
        firmwareVersion = getFirmwareVersion()
        updateDirections(firmwareVersion)
        if version != firmwareVersion:
            versionLabel = Label(firmwareUpdateWindow,
                                 text="\n\n A firmware update is availible.\n\n    Current " +
                                      firmwareVersion + "\n    Latest    " + version + "\n\n Download the latest version from:\n\n " +
                                      urlM0Encoder + "\n    or\n " + urlM0Joystick + "\n    or\n " + urlM4Encoder +
                                      "\n    or\n " + urlM4Joystick +
                                      "\n\n by clicking on the Download button.  " +
                                      "You will be asked to select the directory to which to download the firmware.\n\n")
            inputLabel = Label(firmwareUpdateWindow,
                               text="\n My PasswordPump is a:")
            boardLabel = Label(firmwareUpdateWindow,
                               text="\n My PasswordPump has a:")

            inputType = IntVar()
            boardType = IntVar()
            radioButtonBoardM0 = Radiobutton(firmwareUpdateWindow,
                                             text="ItsyBitsy M0",
                                             variable=boardType,
                                             value=1)
            radioButtonBoardM4 = Radiobutton(firmwareUpdateWindow,
                                             text="Itsybitsy M4",
                                             variable=boardType,
                                             value=2)
            radioButtonEncoder = Radiobutton(firmwareUpdateWindow,
                                             text="Encoder",
                                             variable=inputType,
                                             value=1)
            radioButtonJoystick = Radiobutton(firmwareUpdateWindow,
                                              text="Joystick",
                                              variable=inputType,
                                              value=2)
            downloadButton = Button(firmwareUpdateWindow, text="Download", command=downloadLatestFirmware)
            versionLabel.pack()
            inputLabel.pack()
            radioButtonBoardM0.pack()
            radioButtonBoardM4.pack()
            boardLabel.pack()
            radioButtonEncoder.pack()
            radioButtonJoystick.pack()
            downloadButton.pack()
        else:
            versionLabel = Label(firmwareUpdateWindow,
                                 text="\n\n You are running the most up to date version. " + firmwareVersion + " \n\n")
            versionLabel.pack()
    except Exception as ex:
        updateDirections("Unable to check the version of the firmware:\r\n" + str(ex))


def downloadLatestFirmware():
    try:
        updateDirections("Select a directory for the firmware file.")
        if platform.system() == "Windows":
            downloadLocation = askdirectory()
        elif platform.system() == "Darwin":                                     # Macintosh
            downloadLocation = askdirectory()
        elif platform.system() == "Linux":                                      # Linux
            downloadLocation = askdirectory()
        else:
            downloadLocation = askdirectory()
        if os.path.exists(downloadLocation):
            if inputType == 1:
                if boardType == 1:
                    url = urlM0Encoder
                else:
                    url = urlM4Encoder
            else:
                if boardType == 1:
                    url = urlM0Joystick
                else:
                    url = urlM4Joystick
            downloadFile = downloadLocation + os.sep + 'PasswordPump_v_2_0.ino.bin'
            req = requests.get(url, allow_redirects=True)
            open(downloadFile, 'wb').write(req.content)
            downloadedLabel = Label(firmwareUpdateWindow,
                                    text="\n The latest version of the firmware was downloaded to\n\n" + " " + downloadFile + "\n\n" +
                                         " Exit the program and run BOSSA to upload the new firmware. \n\n" +
                                         " See the Users Guide for detailed instructions, it's location has been copied to the global/system clipboard.\n\n")
            downloadedLabel.pack()
            updateDirections("Latest version of\nPasswordPump firmware downloaded.")
            r = Tk()                                                            # copy the URL to the global/system clipboard
            r.withdraw()
            r.clipboard_clear()                                                 # since this is a potentially destructive action add a button and ask the user if they want to do this.
            r.clipboard_append(usersGuideLocation)
            r.update()                                                          # now it stays on the clipboard after the window is closed
            r.destroy()
            firmwareUpdateWindow.lift()
        else:
            updateDirections("Download location not found.")
    except Exception as ex:
        updateDirections("Unable to download the latest version of the PasswordPump firmware:\r\n" + str(ex))


def ShowSettingsWindow():
    global cbRGBIntensity
    global cbTimout
    global cbLoginAttempts
    global cbPasswordLength
    global cbInterCharDelay

    c.send("pyGetRGBLEDIntensity")
    try:
        response = c.receive()
        response_list = response[1]
        currentIntensity = response_list[0] - 1
    except Exception as ex:
        updateDirections("Exception encountered reading\r\nreturn value from pyGetRGBLEDIntensity:\r\n" + str(ex))
        currentIntensity = 0

    c.send("pyGetLoginMinutes")
    try:
        response = c.receive()
        response_list = response[1]
        currentTimeoutMinutes = response_list[0] - 1
    except Exception as ex:
        updateDirections("Exception encountered reading\r\nreturn value from pyGetLoginMinutes:\r\n" + str(ex))
        currentTimeoutMinutes = 0

    c.send("pyGetLoginAttempts")
    try:
        response = c.receive()
        response_list = response[1]
        currentLoginAttempts = response_list[0] - 1
    except Exception as ex:
        updateDirections("Exception encountered reading\r\nreturn value from pyGetLoginAttempts:\r\n" + str(ex))
        currentLoginAttempts = 0

    c.send("pyGetPasswordLength")
    try:
        response = c.receive()
        response_list = response[1]
        currentPasswordLength = response_list[0] - 1
    except Exception as ex:
        updateDirections("Exception encountered reading\r\nreturn value from pyGetPasswordLength:\r\n" + str(ex))
        currentPasswordLength = 0

    c.send("pyGetInterCharDelay")
    try:
        response = c.receive()
        response_list = response[1]
        currentInterCharDelay = response_list[0] - 1
    except Exception as ex:
        updateDirections("Exception encountered reading\r\nreturn value from pyGetInterCharDelay:\r\n" + str(ex))
        currentInterCharDelay = 0

    settingsWin = Toplevel()
    settingsWin.title("More Settings")
    settingsWin.geometry('350x350')

    lbl_rgb_intensity = Label(settingsWin, text="RGB Intensity", anchor=E, justify=CENTER, width=15)
    lbl_rgb_intensity.pack()

    cbRGBIntensity = Combobox(settingsWin, justify=LEFT, width=37)
    cbRGBIntensity['values'] = ('High',
                                'Medium',
                                'Low',
                                'Off')
    cbRGBIntensity.bind('<<ComboboxSelected>>', on_rgb_intensity_select)
    cbRGBIntensity.current(newindex=currentIntensity)
    cbRGBIntensity.pack()

    lbl_space1 = Label(settingsWin, text=" ", anchor=E, justify=RIGHT, width=15)
    lbl_space1.pack()

    lbl_timeout = Label(settingsWin, text="Timeout Minutes", anchor=E, justify=CENTER, width=15)
    lbl_timeout.pack()

    cbTimout = Combobox(settingsWin, justify=LEFT, width=37)
    cbTimout['values'] = ('30',
                          '60',
                          '90',
                          '120',
                          '240',
                          '1',
                          'Never')
    cbTimout.bind('<<ComboboxSelected>>', on_timeout_minutes_select)
    cbTimout.current(newindex=currentTimeoutMinutes)
    cbTimout.pack()

    lbl_space2 = Label(settingsWin, text=" ", anchor=E, justify=RIGHT, width=15)
    lbl_space2.pack()

    lbl_login_attempts = Label(settingsWin, text="Login Attempts", anchor=E, justify=CENTER, width=15)
    lbl_login_attempts.pack()

    cbLoginAttempts = Combobox(settingsWin, justify=LEFT, width=37)
    cbLoginAttempts['values'] = ('3',
                                 '5',
                                 '10',
                                 '25')
    cbLoginAttempts.bind('<<ComboboxSelected>>', on_login_attempts)
    cbLoginAttempts.current(newindex=currentLoginAttempts)
    cbLoginAttempts.pack()

    lbl_space3 = Label(settingsWin, text=" ", anchor=E, justify=RIGHT, width=15)
    lbl_space3.pack()

    lbl_password_length = Label(settingsWin, text="Generated Password Length", anchor=E, justify=CENTER, width=26)
    lbl_password_length.pack()

    cbPasswordLength = Combobox(settingsWin, justify=LEFT, width=37)
    cbPasswordLength['values'] = ('8',
                                  '10',
                                  '16',
                                  '24',
                                  '31')
    cbPasswordLength.bind('<<ComboboxSelected>>', on_password_length)
    cbPasswordLength.current(newindex=currentPasswordLength)
    cbPasswordLength.pack()

    lbl_space3 = Label(settingsWin, text=" ", anchor=E, justify=RIGHT, width=15)
    lbl_space3.pack()

    lbl_inter_char_delay = Label(settingsWin, text="Inter Character Delay", anchor=E, justify=CENTER, width=22)
    lbl_inter_char_delay.pack()

    cbInterCharDelay = Combobox(settingsWin, justify=LEFT, width=37)
    cbInterCharDelay['values'] = ('0',
                                  '10',
                                  '25',
                                  '100',
                                  '250')
    cbInterCharDelay.bind('<<ComboboxSelected>>', on_inter_char_delay)
    cbInterCharDelay.current(newindex=currentInterCharDelay)
    cbInterCharDelay.pack()

    button = Button(settingsWin, text="Close", command=settingsWin.destroy)
    button.pack(side=BOTTOM)


def stripBadChars(unicode_line):
    unicode_line = unicode_line.translate(translation_table)
    return unicode_line.strip("/")


def calcAcctPositionSend(aPosition):
    if aPosition < 251:
        aPosition += 4
    if aPosition == 92:
        aPosition = 1
    elif aPosition == 124:
        aPosition = 2
    elif aPosition == 126:
        aPosition = 3
    return aPosition


def calcAcctPositionReceive(aPosition):
    if aPosition == 1:
        aPosition = 88
    elif aPosition == 2:
        aPosition = 120
    elif aPosition == 3:
        aPosition = 122
    else:
        if aPosition < 255:
            aPosition -= 4
    return aPosition


def clickedOpen():
    global arduino
    global arduinoAttached
    window.config(cursor="watch")
    updateDirections("Connecting to PasswordPump.")
    try:
        arduino = PyCmdMessenger.ArduinoBoard(port, baud_rate=115200, timeout=20.0, settle_time=2.0, enable_dtr=False,
                                              int_bytes=4, long_bytes=8, float_bytes=4, double_bytes=8)
        arduinoAttached = 1
    except SerialException:
        updateDirections(
            "Error when attaching to\r\nPasswordPump.  Device not\n\rfound. Power cycle the\n\rPasswordPump and try again.")

    global commands
    commands = [["kAcknowledge", "b"],                                          # List of command names (and formats for their associated arguments). These must
                ["kStrAcknowledge", "s"],                                       # be in the same order as in the Arduino sketch.
                ["pyReadAccountName", "b"],
                ["pyReadUserName", "b"],
                ["pyReadPassword", "b"],
                ["pyReadOldPassword", "b"],
                ["pyReadURL", "b"],
                ["pyReadStyle", "b"],
                ["pyReadGroup", "b"],
                ["pyUpdateAccountName", "s"],
                ["pyUpdateUserName", "bs"],
                ["pyUpdatePassword", "bs"],
                ["pyUpdateURL", "bs"],
                ["pyUpdateURL_1", "s"],
                ["pyUpdateURL_2", "s"],
                ["pyUpdateURL_3", "bs"],
                ["pyUpdateStyle", "bs"],
                ["pyUpdateGroup", "bb"],
                ["pyUpdateOldPassword", "bs"],
                ["pyGetNextPos", "b"],
                ["pyGetPrevPos", "b"],
                ["pyGetAcctPos", ""],
                ["pyReadHead", ""],
                ["pyReadTail", ""],
                ["pyGetNextFreePos", ""],
                ["kError", ""],
                ["pyDeleteAccount", "b"],
                ["pyExit", ""],
                ["pyBackup", ""],
                ["pyFactoryReset", ""],
                ["pyFixCorruptLinkedList", ""],
                ["pyRestore", ""],
                ["pyGetAccountCount", ""],
                ["pyDecoyPassword", "b"],
                ["pyShowPasswords", "b"],
                ["pyReadGroup1Name", ""],
                ["pyReadGroup2Name", ""],
                ["pyReadGroup3Name", ""],
                ["pyReadGroup4Name", ""],
                ["pyReadGroup5Name", ""],
                ["pyReadGroup6Name", ""],
                ["pyReadGroup7Name", ""],
                ["pyUpdateCategoryName", "bs"],
                ["pyUpdateRGBLEDIntensity", "b"],
                ["pyUpdateLoginMinutes", "b"],
                ["pyUpdateLoginAttempts", "b"],
                ["pyUpdatePasswordLength", "b"],
                ["pyUpdateInterCharDelay", "b"],
                ["pyGetRGBLEDIntensity", ""],
                ["pyGetLoginMinutes", ""],
                ["pyGetLoginAttempts", ""],
                ["pyGetPasswordLength", ""],
                ["pyGetInterCharDelay", ""],
                ["pyGetFirmwareVersion", ""],
                ["pyChangeMasterPass", "s"]]

    global c                                                                    # Initialize the messenger
    c = PyCmdMessenger.CmdMessenger(arduino, commands, field_separator='~', command_separator='|',
                                    escape_separator='\\')

    txt_acct.bind("<FocusOut>",
                  (lambda _: clickedAcct(txt_acct)))                       # When the user clicks off of the field save the edited item
    txt_user.bind("<FocusOut>", (lambda _: clickedUser(txt_user)))
    txt_pass.bind("<FocusOut>", (lambda _: clickedPass(txt_pass)))
    txt_old_pass.bind("<FocusOut>", (lambda _: clickedOldPass(txt_old_pass)))
    txt_url.bind("<FocusOut>", (lambda _: clickedUrl(txt_url)))

    c.send("pyReadHead")
    try:
        response = c.receive()
        response_list = response[1]
        global head
        head = calcAcctPositionReceive(response_list[0])
    except Exception as ex:
        updateDirections("Exception encountered reading\r\nreturn value from pyReadHead:\r\n" + str(ex))
        head = 0
    global position
    position = head
    c.send("pyGetAccountCount")
    response = c.receive()
    global acctCount
    global selection
    try:
        response_list = response[1]
        acctCount = calcAcctPositionReceive(response_list[0])
    except TypeError as te:
        updateDirections("TypeError encountered in clickedOpen():\r\n" + str(te))
        acctCount = 0
    txt_acct.config(state='normal')
    txt_user.config(state='normal')
    txt_pass.config(state='normal')
    txt_old_pass.config(state='normal')
    txt_url.config(state='normal')
    cbStyle.config(state='normal')
    if acctCount > 0:
        loadListBox()
        selection = 0
        getRecord()
        lb.select_set(selection)
        lb.see(selection)
        lb.activate(selection)
    cb.config(state='disabled')
    btn_open.config(state='disabled')
    btn_next.config(state='normal')
    btn_previous.config(state='normal')
    btn_insert.config(state='normal')
    btn_delete.config(state='normal')
    btn_generate.config(state='normal')
    btn_powned.config(state='normal')
    btn_browser.config(state='normal')
    btn_flip_pw.config(state='normal')
    textboxFavorites.config(state='normal')
    textboxOne.config(state='normal')
    textboxTwo.config(state='normal')
    textboxThree.config(state='normal')
    textboxFour.config(state='normal')
    textboxFive.config(state='normal')
    textboxSix.config(state='normal')
    textboxSeven.config(state='normal')
    menubar.entryconfig('File', state='normal')
    menubar.entryconfig('Backup/Restore', state='normal')
    menubar.entryconfig('Settings', state='normal')
    menubar.entryconfig('Help', state='normal')
    file.entryconfig('Import', state='normal')
    file.entryconfig('Export', state='normal')
    pphelp.entryconfig('Check for Firmware Updates', state='normal')
    window.config(cursor="")
    updateDirections("Connected.")

    ReadGroupNames()

    textboxOne.config(text=groupName1)
    textboxTwo.config(text=groupName2)
    textboxThree.config(text=groupName3)
    textboxFour.config(text=groupName4)
    textboxFive.config(text=groupName5)
    textboxSix.config(text=groupName6)
    textboxSeven.config(text=groupName7)

    groupsMenu.entryconfigure(1, label=groupName1)
    groupsMenu.entryconfigure(2, label=groupName2)
    groupsMenu.entryconfigure(3, label=groupName3)
    groupsMenu.entryconfigure(4, label=groupName4)
    groupsMenu.entryconfigure(5, label=groupName5)
    groupsMenu.entryconfigure(6, label=groupName6)
    groupsMenu.entryconfigure(7, label=groupName7)


def updateDirections(ppdirections):
    txt_dir.delete('1.0', END)
    txt_dir.insert(END, ppdirections)
    window.update()


def character_limit(entry_text,limit):
    if len(entry_text.get()) > 0:
        text = entry_text.get()[:limit]
        entry_text.delete(0,"end")
        entry_text.insert(0, text)


def clickedAcct(ignored):
    window.config(cursor="watch")                                               # TODO: this is not working
    window.update()
    character_limit(txt_acct, 31)
    aResAcct = stripBadChars(txt_acct.get())
    resAcct = aResAcct[0:31]
    global position                                                             # the position on EEprom, don't confuse with selection
    global state
    global selection
    if len(resAcct) > 0:                                                        # if the URL doesn't exist don't send it
        c.send("pyUpdateAccountName", resAcct)                                  # FindAccountPos called on an insert
        try:
            response = c.receive()
            response_list = response[1]
            last_position = position
            position = calcAcctPositionReceive(response_list[0])                # this position may or may not be populated)
            if position == 255:
                position = last_position                                        # TODO: not sure if this is necessary...
            local_position = position
            if state != "Importing":
                lb.delete(0, END)
                loadListBox()                                                   # as a side effect position is changed
                selection = 0
                for key in accountDict:
                    if accountDict[key] != local_position:
                        selection += 1
                    else:
                        break
                lb.select_set(selection)
                lb.see(selection)
                lb.activate(selection)
                position = local_position                                       # because loadListBox changes position
                getRecord()
                updateDirections("Updated account name.")
        except ValueError as ex1:
            updateDirections("Value error encountered in\r\nclickedAcct:\r\n" + str(ex1))
        except Exception as ex2:
            updateDirections("Exception encountered in\r\nclickedAcct:\r\n" + str(ex2))
    else:
        updateDirections("Empty account name discarded.")
    window.config(cursor="")
    window.update()


def clickedUser(ignored):
    global position
    character_limit(txt_user, 31)
    aResUser = stripBadChars(txt_user.get())
    resUser = aResUser[0:31]
    if len(resUser) > 0:
        c.send("pyUpdateUserName", calcAcctPositionSend(position), resUser)
    else:
        c.send("pyUpdateUserName", calcAcctPositionSend(position), "")
    response = c.receive()
    response_list = response[1]
    position = calcAcctPositionReceive(response_list[0])
    txt_user.config(state='normal')
    ppdirections = """Updated user name."""
    updateDirections(ppdirections)
    window.update()


def clickedPass(ignored):
    global position
    character_limit(txt_pass,31)
    aResPass = stripBadChars(txt_pass.get())
    resPass = aResPass[0:31]                                                    # 32nd char ends up being the null terminator
    if len(resPass) > 0:
        c.send("pyUpdatePassword", calcAcctPositionSend(position), resPass)
    else:
        c.send("pyUpdatePassword", calcAcctPositionSend(position), "")
    response = c.receive()
    response_list = response[1]
    position = calcAcctPositionReceive(response_list[0])
    txt_pass.config(state='normal')
    ppdirections = """Updated password."""
    updateDirections(ppdirections)
    window.update()
    ignoredPassesComplexityCheck = passwordComplexityCheck(aResPass)


def clickedOldPass(ignored):
    global position
    character_limit(txt_old_pass,31)
    aResOldPass = stripBadChars(txt_old_pass.get())
    resOldPass = aResOldPass[0:31]                                              # 32nd char ends up being the null terminator
    if len(resOldPass) > 0:
        c.send("pyUpdateOldPassword", calcAcctPositionSend(position), resOldPass)
    else:
        c.send("pyUpdateOldPassword", calcAcctPositionSend(position), "")
    response = c.receive()
    response_list = response[1]
    position = calcAcctPositionReceive(response_list[0])
    txt_old_pass.config(state='normal')
    ppdirections = """Updated old password."""
    updateDirections(ppdirections)
    window.update()


def clickedStyle():
    global position
    resStyle = cbStyle.current()
    if (resStyle < 0) or (resStyle > 2):                                        # style must be 0, 1 or 2
        resStyle = 1                                                            # default is 1
    c.send("pyUpdateStyle", calcAcctPositionSend(position), resStyle)
    response = c.receive()
    response_list = response[1]
    position = calcAcctPositionReceive(response_list[0])
    ppdirections = """Updated style."""
    updateDirections(ppdirections)
    window.update()


def updateGroup():
    global position
    global group
    c.send("pyUpdateGroup", calcAcctPositionSend(position), group + 3)
    response = c.receive()
    response_list = response[1]
    position = calcAcctPositionReceive(response_list[0])
    ppdirections = """Updated groups."""
    updateDirections(ppdirections)
    window.update()


def clickedUrl(ignored):                                                               # send the website over in 3 chunks instead of all at once to circumvent problems encountered when sending it all at once.
    txt_url.config(state='normal')
    global position
    character_limit(txt_url, 95)
    aURL = stripBadChars(txt_url.get())
    resURL_1 = aURL[0:32]                                                       # max length of a URL is 95 chars plus null terminator
    if len(resURL_1) > 0:                                                       # if the URL doesn't exist don't send it
        c.send("pyUpdateURL_1", resURL_1)
        response = c.receive()
        response_list = response[1]
        position = calcAcctPositionReceive(response_list[0])
        resURL_2 = aURL[32:64]                                                  # max length of a URL is 95 chars plus null terminator
        if len(resURL_2) > 0:                                                   # if the URL doesn't exist don't send it
            c.send("pyUpdateURL_2", resURL_2)
            response = c.receive()
            response_list = response[1]
            position = calcAcctPositionReceive(response_list[0])
            resURL_3 = aURL[64:95]                                              # max length of a URL is 95 chars plus null terminator
            if len(resURL_3) > 0:                                               # if the URL doesn't exist don't send it
                c.send("pyUpdateURL_3", calcAcctPositionSend(position), resURL_3)
                response = c.receive()
                response_list = response[1]
                position = calcAcctPositionReceive(response_list[0])
            else:
                c.send("pyUpdateURL_3", calcAcctPositionSend(position), "")
                response = c.receive()
                response_list = response[1]
                position = calcAcctPositionReceive(response_list[0])
        else:
            c.send("pyUpdateURL", calcAcctPositionSend(position), aURL)
            response = c.receive()
            response_list = response[1]
            position = calcAcctPositionReceive(response_list[0])
    else:
        c.send("pyUpdateURL", calcAcctPositionSend(position), "")
        response = c.receive()
        response_list = response[1]
        position = calcAcctPositionReceive(response_list[0])
    txt_url.config(state='normal')
    ppdirections = """Updated URL."""
    updateDirections(ppdirections)
    window.update()


def clickedClose():
    MsgBox = tkinter.messagebox.askquestion('Exit PasswordPumpGUI',
                                            'Are you sure you want to exit the PasswordPumpGUI?',
                                            icon='warning')
    if MsgBox == 'yes':
        global arduinoAttached
        global acctCount
        if arduinoAttached == 1:
            try:
                c.send("pyExit")
                response = c.receive()
                response_list = response[1]
                acctCount = calcAcctPositionReceive(response_list[0])
            except Exception as ex:
                updateDirections("There was an error closing the\r\napplication:\r\n" + str(ex))
        sys.exit(1)


def clickedPrevious():
    global position
    global selection
    c.send("pyGetPrevPos", calcAcctPositionSend(position))
    response = c.receive()
    response_list = response[1]
    last_position = position
    position = calcAcctPositionReceive(response_list[0])
    if position == 255:
        position = last_position
        updateDirections("Reached the beginning of the\r\nlist.")
    else:
        items = lb.curselection()
        selection = items[0]
        OnEntryUpNoEvent()
        lb.activate(selection)                                                  # has no effect


def clickedNext():
    global position
    global selection
    c.send("pyGetNextPos", calcAcctPositionSend(position))
    response = c.receive()
    response_list = response[1]
    last_position = position
    position = calcAcctPositionReceive(
        response_list[0])                                                       # used when we call OnEntryDownNoEvent->OnEntryDown->clickedLoad->getRecord
    if position == 255:
        position = last_position
        updateDirections("Reached the end of the list.")
    else:
        items = lb.curselection()                                               # Gets a list of the currently selected alternatives.
        selection = items[0]
        OnEntryDownNoEvent()
        lb.activate(selection)                                                  # has no effect


def loadListBox():                                                              # TODO: reorganize the logic in this function
    window.config(cursor="watch")                                               # TODO: this is not working
    window.update()
    lb.delete(0, END)                                                           # clear out the listbox
    global position
    global head
    c.send("pyReadHead")                                                        # Get the list head
    try:
        response = c.receive()
        response_list = response[1]
        head = calcAcctPositionReceive(response_list[0])
        position = head
        global accountDict
        accountDict = ({})                                                      # Load the dictionary
        while position < 255:                                                   # '<' not supported between instances of 'str' and 'int'
            c.send("pyReadAccountName", calcAcctPositionSend(position))
            try:
                response = c.receive()
                accountName_list = response[1]
                accountName = accountName_list[0]
            except UnicodeDecodeError as ude:
                updateDirections("UnicodeDecodeError in\r\npyReadAccountName:\r\n" + str(ude))
                accountName = "UnicodeDecodeError"
            except ValueError as ve:
                updateDirections("ValueError in\r\npyReadAccountName:\r\n" + str(ve))
                accountName = "ValueError"
            except Exception as ex:
                updateDirections("Exception in\r\npyReadAccountName:\r\n" + str(ex))
                accountName = "Exception"
            accountDict[accountName] = position
            lb.insert(END, accountName)                                         # Load the listbox
            c.send("pyGetNextPos", calcAcctPositionSend(position))              # calls getNextPtr(acctPosition) in C program
            try:
                response = c.receive()
                response_list = response[1]
                position = calcAcctPositionReceive(response_list[0])
            except ValueError as ve:
                updateDirections("Error in pyGetNextPos:\r\n" + str(ve))
                raise ve
            except Exception as ex:
                updateDirections("Exception in pyGetNextPos:\r\n" + str(ex))
                raise ex
        position = head
        window.config(cursor="")
        window.update()
    except ValueError as ve:
        updateDirections("ValueError in pyReadHead,\r\npyReadAccountName or\r\npyGetNextPos:\r\n" + str(ve))
        head = 0
    except Exception as ex:
        updateDirections("Exception in pyReadHead,\r\npyReadAccountName or\r\npyGetNextPos:\r\n" + str(ex))
        head = 0


def ReadGroupNames():
    global groupName1
    global groupName2
    global groupName3
    global groupName4
    global groupName5
    global groupName6
    global groupName7
    try:
        c.send("pyReadGroup1Name")
        response = c.receive()
        groupName_list = response[1]
        groupName1 = groupName_list[0]

        c.send("pyReadGroup2Name")
        response = c.receive()
        groupName_list = response[1]
        groupName2 = groupName_list[0]

        c.send("pyReadGroup3Name")
        response = c.receive()
        groupName_list = response[1]
        groupName3 = groupName_list[0]

        c.send("pyReadGroup4Name")
        response = c.receive()
        groupName_list = response[1]
        groupName4 = groupName_list[0]

        c.send("pyReadGroup5Name")
        response = c.receive()
        groupName_list = response[1]
        groupName5 = groupName_list[0]

        c.send("pyReadGroup6Name")
        response = c.receive()
        groupName_list = response[1]
        groupName6 = groupName_list[0]

        c.send("pyReadGroup7Name")
        response = c.receive()
        groupName_list = response[1]
        groupName7 = groupName_list[0]

    except UnicodeDecodeError as ude:
        updateDirections("UnicodeDecodeError in\r\npyReadGroup1Name:\r\n" + str(ude))
        groupName1 = "UnicodeDecodeError"
    except ValueError as ve:
        updateDirections("ValueError in\r\npyReadGroupName:\r\n" + str(ve))
        groupName1 = "ValueError"
    except Exception as ex:
        updateDirections("Exception in\r\npyReadGroupName:\r\n" + str(ex))
        groupName1 = "Exception"


def OnEntryDownNoEvent():
    OnEntryDown(0)


def OnEntryDown(ignored):
    global selection
    if selection < lb.size() - 1:
        lb.select_clear(selection)                                              # Removes one or more items from the selection.
        selection += 1
        lb.select_set(selection)                                                # Adds one or more items to the selection.
        lb.see(selection)                                                       # Makes sure the given list index is visible.
        clickedLoad()                                                           # calls getRecord()


def OnEntryUpNoEvent():
    OnEntryUp(0)


def OnEntryUp(ignored):
    global selection
    if selection > 0:
        lb.select_clear(selection)                                              # Removes one or more items from the selection.
        selection -= 1
        lb.select_set(selection)                                                # Adds one or more items to the selection.
        lb.see(selection)                                                       # Makes sure the given list index is visible.
        clickedLoad()                                                           # calls getRecord()


def clickedInsert():
    global state
    state = "Inserting"

    txt_acct.bind("<FocusOut>", (lambda _: doNothing(txt_acct)))                # When the user clicks off of the field do nothing
    txt_user.bind("<FocusOut>", (lambda _: doNothing(txt_user)))
    txt_pass.bind("<FocusOut>", (lambda _: doNothing(txt_pass)))
    txt_old_pass.bind("<FocusOut>", (lambda _: doNothing(txt_old_pass)))
    txt_url.bind("<FocusOut>", (lambda _: doNothing(txt_url)))

    txt_acct.delete(0, END)
    txt_user.delete(0, END)
    txt_pass.delete(0, END)
    txt_old_pass.delete(0, END)
    txt_url.delete(0, END)

    txt_acct.focus_set()                                                        # Put input focus on the account field

    txt_acct.bind("<FocusOut>",
                  (lambda _: clickedAcct(txt_acct)))                       # When the clicks off of the field save the edited item
    txt_user.bind("<FocusOut>", (lambda _: clickedUser(txt_user)))
    txt_pass.bind("<FocusOut>", (lambda _: clickedPass(txt_pass)))
    txt_old_pass.bind("<FocusOut>", (lambda _: clickedOldPass(txt_old_pass)))
    txt_url.bind("<FocusOut>", (lambda _: clickedUrl(txt_url)))


def doNothing(ignored):
    pass                                                                        # do nothing


def clickedLoadDB(event):
    global selection
    w = event.widget                                                            # Note here that Tkinter passes an event object to onselect()
    selection = int(w.curselection()[0])
    value = w.get(selection)
    updateDirections('You selected item %d: "%s"' % (selection, value))
    clickedLoad()                                                               # calls getRecord()


def clickedLoad():
    global position
    global accountDict
    item = lb.curselection()
    global selection
    selection = item[0]
    theText = lb.get(item)
    position = accountDict[theText]
    getRecord()


def clickedDelete():
    if tkinter.messagebox.askyesno("Delete", "Delete this record?"):
        global selection
        lb.delete(selection)
        global position
        c.send("pyDeleteAccount", calcAcctPositionSend(position))
        response = c.receive()
        response_list = response[1]
        position = calcAcctPositionReceive(response_list[0])                    # returns head position
        getRecord()
        selection = 0
        lb.select_set(selection)
        lb.see(selection)
        lb.activate(selection)
        updateDirections("Record deleted.")


def clickedChangeMasterPass():
    newMasterPass = tkinter.simpledialog.askstring("Change Master Password", "New Master Password", parent=window)
    if newMasterPass is not None:
        window.config(cursor="watch")
        window.update()
        c.send("pyChangeMasterPass", newMasterPass)
        response = c.receive()
        response_list = response[1]
        ignoredPosition = calcAcctPositionReceive(response_list[0])             # returns head position
        getRecord()
        newSelection = 0
        lb.select_set(newSelection)
        lb.see(newSelection)
        lb.activate(newSelection)
        window.config(cursor="")
        updateDirections("Master password changed.")


def clickedShowPassword():
    yes = tkinter.messagebox.askyesno("Show Password", "Do you want to see the password on the PasswordPump?")
    if yes:
        c.send("pyShowPasswords", 1)
        response = c.receive()
        response_list = response[1]
        ignoredHead = calcAcctPositionReceive(response_list[0])                 # returns head position
        updateDirections("Turned on password viewing on\r\nthe PasswordPump.")
    else:
        c.send("pyShowPasswords", 0)
        response = c.receive()
        response_list = response[1]
        ignoredHead = calcAcctPositionReceive(response_list[0])                 # returns head position
        updateDirections("Turned off password viewing on\r\nthe PasswordPump.")


def clickedDecoyPassword():
    yes = tkinter.messagebox.askyesno("Decoy Password", "Do you want to enable the decoy password feature?")
    if yes:
        c.send("pyDecoyPassword", 1)
        response = c.receive()
        response_list = response[1]
        ignoredHead = calcAcctPositionReceive(response_list[0])                 # returns head position
        updateDirections("Enabled the decoy password\r\nfeature on the PasswordPump")
    else:
        c.send("pyDecoyPassword", 0)
        response = c.receive()
        response_list = response[1]
        ignoredHead = calcAcctPositionReceive(response_list[0])                 # returns head position
        updateDirections("Disabled the decoy password\r\nfeature on the PasswordPump")


def getRecord():
    global position
    global group
    global vFavorites
    global vCategoryOne
    global vCategoryTwo
    global vCategoryThree
    global vCategoryFour
    global vCategoryFive
    global vCategorySix
    global vCategorySeven
    c.send("pyReadAccountName", calcAcctPositionSend(position))
    try:
        responseAccount = c.receive()
        accountName_list = responseAccount[1]
        accountName = accountName_list[0]
    except UnicodeDecodeError:
        accountName = ""
    txt_acct.delete(0, END)
    txt_acct.insert(0, accountName)

    c.send("pyReadUserName", calcAcctPositionSend(position))
    try:
        responseUser = c.receive()
        userName_list = responseUser[1]
        userName = userName_list[0]
    except UnicodeDecodeError:
        userName = ""
    txt_user.delete(0, END)
    txt_user.insert(0, userName)

    c.send("pyReadPassword", calcAcctPositionSend(position))
    try:
        responsePassword = c.receive()
        password_list = responsePassword[1]
        password = password_list[0]
    except UnicodeDecodeError:
        password = ""
    txt_pass.delete(0, END)
    txt_pass.insert(0, password)
    ignoredPassesComplexityCheck = passwordComplexityCheck(password)

    c.send("pyReadOldPassword", calcAcctPositionSend(position))
    try:
        responseOldPassword = c.receive()
        old_password_list = responseOldPassword[1]
        old_password = old_password_list[0]
    except UnicodeDecodeError:
        old_password = ""
    txt_old_pass.delete(0, END)
    txt_old_pass.insert(0, old_password)

    c.send("pyReadStyle", calcAcctPositionSend(position))
    try:
        responseStyle = c.receive()
        style_list = responseStyle[1]
        style = int(style_list[0])
    except ValueError:                                                          # when style = 255 (i.e. was never written)
        style = 1
    except UnicodeDecodeError:
        style = 1
    cbStyle.current(style)

    c.send("pyReadURL", calcAcctPositionSend(position))
    try:
        responseURL = c.receive()
        url_list = responseURL[1]
        url = url_list[0]
    except UnicodeDecodeError:
        url = ""
    txt_url.delete(0, END)
    txt_url.insert(0, url)

    c.send("pyReadGroup", calcAcctPositionSend(position))
    try:
        responseGroup = c.receive()
        group_list = responseGroup[1]
        group = int(group_list[0])
    except UnicodeDecodeError as ude:
        updateDirections("UnicodeDecodeError during pyReadGroup in getRecord(); " + str(ude))
        group = 0
    except Exception as ex:
        updateDirections("Exception encountered after pyReadGroup in getRecord(); Group: " + str(group) + " " + str(ex))
        group = 0
    SetGroupCheckBoxes()


def serial_ports():
    return comports()


def on_select(ignored=None):
    global port
    port_desc = cb.get()
    updateDirections(port_desc)
    port = port_desc[:port_desc.find(":")]                                      # TODO: make this work on all operating systems


def on_style_select(ignored=None):
    clickedStyle()


def on_rgb_intensity_select(ignored=None):
    updateDirections("Selected RGB Intensity")
    resSelection = cbRGBIntensity.current()
    if (resSelection < 0) or (resSelection > 3):                                # RGB LED Intensity must be 0 - 3
        resSelection = 1                                                        # default is 1, Medium
    resSelection += 1                                                           # cheap way around a problem sending 0
    c.send("pyUpdateRGBLEDIntensity", resSelection)
    response = c.receive()
    response_list = response[1]
    ignoredPosition = calcAcctPositionReceive(response_list[0])
    ppdirections = """Updated RGB LED Intensity."""
    updateDirections(ppdirections)
    window.update()


def on_timeout_minutes_select(ignored=None):
    updateDirections("Selected timeout minutes")
    resSelection = cbTimout.current()
    if (resSelection < 0) or (resSelection > 6):                                # Timout must be 0 - 6
        resSelection = 1                                                        # default is 1, 60 minutes
    resSelection += 1                                                           # cheap way around a problem sending 0
    c.send("pyUpdateLoginMinutes", resSelection)
    response = c.receive()
    response_list = response[1]
    ignoredPosition = calcAcctPositionReceive(response_list[0])
    ppdirections = """Updated timeout minutes."""
    updateDirections(ppdirections)
    window.update()


def on_login_attempts(ignored=None):
    updateDirections("Selected login attempts")
    resSelection = cbLoginAttempts.current()
    if (resSelection < 0) or (resSelection > 3):                                # Login attempts must be 0 - 3
        resSelection = 2                                                        # default is 2, 10 minutes
    resSelection += 1                                                           # cheap way around a problem sending 0
    c.send("pyUpdateLoginAttempts", resSelection)
    response = c.receive()
    response_list = response[1]
    ignoredPosition = calcAcctPositionReceive(response_list[0])
    ppdirections = """Updated login attempts."""
    updateDirections(ppdirections)
    window.update()


def on_password_length(ignored=None):
    updateDirections("Selected generated password length")
    resSelection = cbPasswordLength.current()
    if (resSelection < 0) or (resSelection > 4):                                # Password length must be 0 - 4
        resSelection = 2                                                        # default is 2, 16 characters
    resSelection += 1                                                           # cheap way around a problem sending 0
    c.send("pyUpdatePasswordLength", resSelection)
    response = c.receive()
    response_list = response[1]
    ignoredPosition = calcAcctPositionReceive(response_list[0])
    ppdirections = """Updated generated password length."""
    updateDirections(ppdirections)
    window.update()


def on_inter_char_delay(ignored=None):
    updateDirections("Selected inter char delay")
    resSelection = cbInterCharDelay.current()
    if (resSelection < 0) or (resSelection > 4):                                # Password length must be 0 - 4
        resSelection = 0                                                        # default is 0
    resSelection += 1                                                           # cheap way around a problem sending 0
    c.send("pyUpdateInterCharDelay", resSelection)
    response = c.receive()
    response_list = response[1]
    ignoredPosition = calcAcctPositionReceive(response_list[0])
    ppdirections = """Updated inter char delay."""
    updateDirections(ppdirections)
    window.update()


def BackupEEprom():
    if tkinter.messagebox.askyesno("Backup", "Backup the primary EEprom?"):
        window.config(cursor="watch")
        updateDirections("Backing up EEprom")
        global selection
        global position
        c.send("pyBackup")
        response = c.receive()
        response_list = response[1]
        position = calcAcctPositionReceive(response_list[0])                    # returns head position
        getRecord()
        lb.select_clear(selection)                                              # Removes one or more items from the selection.
        selection = 0
        lb.select_set(selection)
        lb.see(selection)
        lb.activate(selection)
        window.config(cursor="")
        updateDirections("Finished backing up EEprom.")


def FactoryReset():
    if tkinter.messagebox.askyesno("Factory Reset", "Factory reset the device and exit?"):
        window.config(cursor="watch")
        updateDirections("Factory resetting...")
        global selection
        global position
        c.send("pyFactoryReset")
        response = c.receive()
        response_list = response[1]
        position = calcAcctPositionReceive(response_list[0])                    # returns head position
        updateDirections("Finished the factory reset.")
        sys.exit(1)


def FixCorruptLinkedList():
    if tkinter.messagebox.askyesno("Corrupt Account List",
                                   "Fix corrupt account list? Only do this if it is necessary."):
        window.config(cursor="watch")
        updateDirections("Fixing corrupt account list...")
        global selection
        global position
        c.send("pyFixCorruptLinkedList")
        response = c.receive()
        response_list = response[1]
        position = calcAcctPositionReceive(response_list[0])                    # returns head position
        loadListBox()                                                           # postion is set to head as a side effect
        getRecord()                                                             # get the head record
        lb.select_clear(selection)                                              # Removes one or more items from the selection.
        selection = 0
        lb.select_set(selection)
        lb.see(selection)
        lb.activate(selection)
        window.config(cursor="")
        updateDirections("Finished fixing corruption.")


def RestoreEEprom():
    if tkinter.messagebox.askyesno("Restore", "Restore backup to primary EEprom?"):
        window.config(cursor="watch")
        updateDirections("Restoring EEprom")
        global selection
        global position
        c.send("pyRestore")
        response = c.receive()
        response_list = response[1]
        position = calcAcctPositionReceive(response_list[0])                    # returns head position
        loadListBox()                                                           # postion is set to head as a side effect
        getRecord()                                                             # get the head record
        lb.select_clear(selection)                                              # Removes one or more items from the selection.
        selection = 0
        lb.select_set(selection)
        lb.see(selection)
        lb.activate(selection)
        window.config(cursor="")
        updateDirections("Finished restoring EEprom.")


def ImportFileChrome():
    global state
    state = "Imorting"
    if platform.system() == "Windows":
        name = askopenfilename(initialdir="C:/",                                # TODO: make this work cross platform
                               filetypes=(("CSV File", "*.csv"), ("All Files", "*.*")),
                               title="Choose a file.")
    elif platform.system() == "Darwin":                                         # Macintosh
        name = askopenfilename(title="Choose a file.")
    elif platform.system() == "Linux":                                          # Linux
        name = askopenfilename(title="Choose a file.")
    else:
        name = askopenfilename(title="Choose a file.")
    if os.path.exists(name):                                                    # make sure the file exists before trying to open it
        window.config(cursor="watch")
        updateDirections(name)
        global position
        try:                                                                    # Using try in case user types in unknown file or closes without choosing a file.
            with open(name, newline='') as csvfile:
                reader = csv.DictReader(csvfile)
                try:
                    for row in reader:
                        txt_acct.delete(0, END)
                        txt_user.delete(0, END)
                        txt_pass.delete(0, END)
                        txt_url.delete(0, END)
                        txt_acct.insert(0, stripBadChars(row['name']))
                        txt_user.insert(0, stripBadChars(row['username']))
                        txt_pass.insert(0, stripBadChars(row['password']))
                        txt_url.insert(0, stripBadChars(row['url']))
                        window.update()
                        time.sleep(0.15)                                        # to eliminate intermittent failure
                        clickedAcct(txt_acct)                                   # sets position = FindAccountPos()
                        time.sleep(0.15)                                        # to eliminate intermittent failure
                        clickedUser(txt_user)
                        time.sleep(0.15)                                        # to eliminate intermittent failure
                        clickedPass(txt_pass)
                        time.sleep(0.15)                                        # to eliminate intermittent failure
                        clickedStyle()
                        time.sleep(0.15)                                        # to eliminate intermittent failure
                        clickedUrl(txt_url)
                        updateDirections("Record saved.")
                    updateDirections("All records saved.")
                    loadListBox()
                except Exception as exInner:
                    updateDirections("Error encountered reading file in ImportFileChrome; " + str(exInner))
        except Exception as exOuter:
            updateDirections("Error encountered in ImportFileChrome; " + str(exOuter))
    window.config(cursor="")
    window.update()
    state = "None"


def ImportFileKeePass():
    global state
    state = "Importing"
    if platform.system() == "Windows":
        name = askopenfilename(initialdir="C:/",                                # TODO: make this work cross platform
                               filetypes=(("CSV File", "*.csv"), ("All Files", "*.*")),
                               title="Choose a file.")
    elif platform.system() == "Darwin":                                         # Macintosh
        name = askopenfilename(title="Choose a file.")
    elif platform.system() == "Linux":
        name = askopenfilename(title="Choose a file.")                          # Linux
    else:
        name = askopenfilename(title="Choose a file.")
    if os.path.exists(name):                                                    # make sure the file exists before trying to open it
        window.config(cursor="watch")
        updateDirections(name)
        global position
        try:                                                                    # Using try in case user types in unknown file or closes without choosing a file.
            with open(name, newline='') as csvfile:
                reader = csv.DictReader(csvfile)
                try:
                    for row in reader:
                        txt_acct.delete(0, END)
                        txt_user.delete(0, END)
                        txt_pass.delete(0, END)
                        txt_url.delete(0, END)
                        txt_acct.insert(0, stripBadChars(row['Account']))
                        txt_user.insert(0, stripBadChars(row['Login Name']))
                        txt_pass.insert(0, stripBadChars(row['Password']))
                        txt_url.insert(0, stripBadChars(row['Web Site']))
                        window.update()
                        time.sleep(0.15)                                        # to eliminate intermittent failure
                        clickedAcct(txt_acct)                                   # sets position = FindAccountPos()
                        time.sleep(0.15)                                        # to eliminate intermittent failure
                        clickedUser(txt_user)
                        time.sleep(0.15)                                        # to eliminate intermittent failure
                        clickedPass(txt_pass)
                        time.sleep(0.15)                                        # to eliminate intermittent failure
                        clickedStyle()
                        time.sleep(0.15)                                        # to eliminate intermittent failure
                        clickedUrl(txt_url)
                        updateDirections("Record saved.")
                    updateDirections("All records saved.")
                    loadListBox()
                except Exception as exInner:
                    updateDirections("Error encountered processing file in ImportFileKeePass; " + str(exInner))
        except Exception as exOuter:
            updateDirections("Error encountered in ImportFileKeePass; " + str(exOuter))
    window.config(cursor="")
    window.update()
    state = "None"


def ImportFilePasswordPump():
    global state
    global selection
    state = "Importing"
    if platform.system() == "Windows":
        name = askopenfilename(initialdir="C:/",                                # TODO: make this work cross platform
                               filetypes=(("Encrypted Files", "*.csvenc"), ("CSV File", "*.csv"), ("All Files", "*.*")),
                               title="Choose a file.")
    elif platform.system() == "Darwin":                                         # Macintosh
        name = askopenfilename(title="Choose a file.")
    elif platform.system() == "Linux":                                          # Linux
        name = askopenfilename(title="Choose a file.")
    else:
        name = askopenfilename(title="Choose a file.")
    updateDirections(name)
    uenc_name = name
    if name.endswith(".csvenc"):                                                # if the filename ends in .csvenc it is encrypted
        key = ask_root_password(window)                                         # get the password
        if key is not None:
            window.config(cursor="watch")
            uenc_name = name.replace('.csvenc', '.csv')
            copyfile(name, uenc_name)
            decrypt(uenc_name, key)                                             # decrypt the file
            updateDirections(name + " was decrypted.")
    global position
    global group
    window.config(cursor="watch")
    if os.path.exists(uenc_name):
        try:                                                                    # Using try in case user types in unknown file or closes without choosing a file.
            with open(uenc_name, newline='') as csvfile:
                fieldnames = ['accountname', 'username', 'password', 'oldpassword', 'url', 'style', 'group']
                reader = csv.DictReader(csvfile, fieldnames=fieldnames)
                try:
                    for row in reader:
                        txt_acct.delete(0, END)
                        txt_user.delete(0, END)
                        txt_pass.delete(0, END)
                        txt_old_pass.delete(0, END)
                        txt_url.delete(0, END)
                        txt_acct.insert(0, stripBadChars(row['accountname']))
                        if txt_acct.get() != 'accountname':                     # to skip the header if there is one
                            txt_user.insert(0, stripBadChars(row['username']))
                            txt_pass.insert(0, stripBadChars(row['password']))
                            txt_old_pass.insert(0, stripBadChars(row['oldpassword']))
                            txt_url.insert(0, stripBadChars(row['url']))
                            group = int(row['group'])
                            SetGroupCheckBoxes()
                            window.update()
                            time.sleep(0.15)                                    # to eliminate intermittent failure
                            clickedAcct(txt_acct)                               # sets position = FindAccountPos()
                            time.sleep(0.15)                                    # to eliminate intermittent failure
                            clickedUser(txt_user)
                            time.sleep(0.15)                                    # to eliminate intermittent failure
                            clickedPass(txt_pass)
                            time.sleep(0.15)                                    # to eliminate intermittent failure
                            clickedOldPass(txt_old_pass)
                            time.sleep(0.15)                                    # to eliminate intermittent failure
                            clickedStyle()
                            time.sleep(0.15)                                    # to eliminate intermittent failure
                            clickedUrl(txt_url)
                            time.sleep(0.15)                                    # to eliminate intermittent failure
                            updateGroup()
                            updateDirections("Record saved.")
                    updateDirections("All records saved.")
                    loadListBox()
                    lb.select_clear(selection)                                  # Removes one or more items from the selection.
                    selection = 0
                    getRecord()
                    lb.select_set(selection)
                    lb.see(selection)
                    lb.activate(selection)
                    updateDirections("Updated account name.")
                except Exception as exInner:
                    updateDirections("Error encountered reading file in ImportFilePasswordPump; " + str(exInner))
        except Exception as exOuter:
            updateDirections("Error encountered in ImportFilePasswordPump; " + str(exOuter))
        state = "None"
        if name.endswith(".csvenc"):                                            # if the filename ends in enc it was encrypted
            os.remove(uenc_name)                                                # for safety remove the unencrypted file
    window.config(cursor="")
    window.update()


def ExportFile():
    global selection
    inifilename = time.strftime("PasswordPumpExport%Y%m%d-%H%M%S.csv")
    if platform.system() == "Windows":
        name = asksaveasfilename(initialdir="C:/",                              # TODO: make this work cross platform
                                 filetypes=(("CSV File", "*.csv"), ("All Files", "*.*")),
                                 initialfile=inifilename,
                                 title="Create a file."
                                 )
    elif platform.system() == "Darwin":                                         # Macintosh
        name = asksaveasfilename(title="Create a file."
                                 )
    elif platform.system() == "Linux":                                          # Linux
        name = asksaveasfilename(initialdir="/home",
                                 filetypes=(("CSV File", "*.csv"), ("All Files", "*.*")),
                                 initialfile=inifilename,
                                 title="Create a file."
                                 )
    else:
        name = asksaveasfilename(initialdir="C:/",
                                 )

    if len(name.strip()) > 0:
        window.config(cursor="watch")
        updateDirections(name)
        try:                                                                    # Using try in case user types in unknown file or closes without choosing a file.
            with open(name, mode='w') as pp_file:
                pp_writer = csv.writer(pp_file, delimiter=',', quotechar='"', quoting=csv.QUOTE_NONNUMERIC)
                pp_writer.writerow(['accountname', 'username', 'password', 'oldpassword', 'url', 'style', 'group'])
                global position
                global head
                c.send("pyReadHead")                                            # Get the list head
                try:
                    response = c.receive()
                    response_list = response[1]
                    head = calcAcctPositionReceive(response_list[0])
                    position = head
                    while position < 255:                                       # '<' not supported between instances of 'str' and 'int'
                        c.send("pyReadAccountName", calcAcctPositionSend(position))
                        try:
                            response = c.receive()
                            accountName_list = response[1]
                            accountName = stripBadChars(accountName_list[0])
                        except UnicodeDecodeError as ude:
                            updateDirections("UnicodeDecodeError in pyReadAccountName; " + str(ude))
                            accountName = "UnicodeDecodeError"
                        except ValueError as ve:
                            updateDirections("ValueError in pyReadAccountName; " + str(ve))
                            accountName = "ValueError"
                        except Exception as ex:
                            updateDirections("Exception in pyReadAccountName; " + str(ex))
                            accountName = "Exception"

                        c.send("pyReadUserName", calcAcctPositionSend(position))
                        try:
                            response = c.receive()
                            userName_list = response[1]
                            userName = stripBadChars(userName_list[0])
                        except UnicodeDecodeError as ude:
                            updateDirections("UnicodeDecodeError in pyReadUserName; " + str(ude))
                            userName = "UnicodeDecodeError"
                        except ValueError as ve:
                            updateDirections("ValueError in pyReadUserName; " + str(ve))
                            userName = "ValueError"
                        except Exception as ex:
                            updateDirections("Exception in pyReadUserName; " + str(ex))
                            userName = "Exception"

                        c.send("pyReadPassword", calcAcctPositionSend(position))
                        try:
                            response = c.receive()
                            password_list = response[1]
                            password = stripBadChars(password_list[0])
                        except UnicodeDecodeError as ude:
                            updateDirections("UnicodeDecodeError in pyReadPassword; " + str(ude))
                            password = "UnicodeDecodeError"
                        except ValueError as ve:
                            updateDirections("ValueError in pyReadPassword; " + str(ve))
                            password = "ValueError"
                        except Exception as ex:
                            updateDirections("Exception in pyReadPassword; " + str(ex))
                            password = "Exception"

                        c.send("pyReadOldPassword", calcAcctPositionSend(position))
                        try:
                            response = c.receive()
                            oldpassword_list = response[1]
                            oldpassword = stripBadChars(oldpassword_list[0])
                        except UnicodeDecodeError as ude:
                            updateDirections("UnicodeDecodeError in pyReadOldPassword; " + str(ude))
                            oldpassword = "UnicodeDecodeError"
                        except ValueError as ve:
                            updateDirections("ValueError in pyReadOldPassword; " + str(ve))
                            oldpassword = "ValueError"
                        except Exception as ex:
                            updateDirections("Exception in pyReadOldPassword; " + str(ex))
                            oldpassword = "Exception"

                        c.send("pyReadURL", calcAcctPositionSend(position))
                        try:
                            response = c.receive()
                            url_list = response[1]
                            url = stripBadChars(url_list[0])
                        except UnicodeDecodeError as ude:
                            updateDirections("UnicodeDecodeError in pyReadURL; " + str(ude))
                            url = "UnicodeDecodeError"
                        except ValueError as ve:
                            updateDirections("ValueError in pyReadURL; " + str(ve))
                            url = "ValueError"
                        except Exception as ex:
                            updateDirections("Exception in pyReadURL; " + str(ex))
                            url = "Exception"

                        c.send("pyReadStyle", calcAcctPositionSend(position))
                        try:
                            response = c.receive()
                            style_list = response[1]
                            style = int(stripBadChars(style_list[0]))
                        except UnicodeDecodeError as ude:
                            updateDirections("UnicodeDecodeError in pyReadStyle; " + str(ude))
                            style = 1
                        except ValueError as ve:
                            updateDirections("ValueError in pyReadStyle; " + str(ve) + " Position: " + str(position))
                            style = 1
                        except Exception as ex:
                            updateDirections("Exception in pyReadStyle; " + str(ex))
                            style = 1

                        c.send("pyReadGroup", calcAcctPositionSend(position))
                        try:
                            response = c.receive()
                            group_list = response[1]
                            aGroup = group_list[0]
                        except UnicodeDecodeError as ude:
                            updateDirections("UnicodeDecodeError in pyReadGroup; " + str(ude))
                            aGroup = 0
                        except ValueError as ve:
                            updateDirections("ValueError in pyReadGroup; " + str(ve))
                            aGroup = 0
                        except Exception as ex:
                            updateDirections("Exception in pyReadGroup; " + str(ex))
                            aGroup = 0

                        pp_writer.writerow([accountName, userName, password, oldpassword, url, style, aGroup])

                        c.send("pyGetNextPos",
                               calcAcctPositionSend(position))                  # calls getNextPtr(acctPosition) in C program
                        try:
                            response = c.receive()
                            response_list = response[1]
                            position = calcAcctPositionReceive(response_list[0])
                        except ValueError as ve:
                            updateDirections("Error in pyGetNextPos; " + str(ve))
                            raise ve
                        except Exception as exInner:
                            updateDirections("Exception in pyGetNextPos; " + str(exInner))
                            raise exInner
                except ValueError as ve:
                    updateDirections("ValueError in pyReadHead, pyReadAccountName or pyGetNextPos; " + str(ve))
                    head = 0
                except Exception as exMiddle:
                    updateDirections("Exception in pyReadHead, pyReadAccountName or pyGetNextPos; " + str(exMiddle))
                    head = 0
        except Exception as exOuter:
            updateDirections("No file exists; " + str(exOuter))
        updateDirections("Don't forget to\r\nencrypt the file\r\nwith a password.")
        window.config(cursor="")
        window.update()
                                                                                # ask if the user wants to encrypt the file here and encrypt it if necessary
        key = ask_root_password(window)                                         # TODO: the user should enter the password twice, not just once.
        if key is not None:
            window.config(cursor="watch")
            copyfile(name, name + "enc")
            encrypt(name + "enc", key)
            os.remove(name)
            updateDirections(name + "enc\r\nwas encrypted.\r\n" + name + "\r\nwas removed.")
            window.config(cursor="")
    else:
        updateDirections("User cancelled.")
        window.update()
    position = head
    getRecord()                                                                 # get the head record
    lb.select_clear(selection)                                                  # Removes one or more items from the selection.
    selection = 0
    lb.select_set(selection)
    lb.see(selection)
    lb.activate(selection)


def OnFavorites():
    global group
    global vFavorites
    if vFavorites.get() == 1:
        group = group | 1
    else:
        group = group & (~1)
    updateGroup()


def OnCategoryOne():
    global group
    global vCategoryOne
    if vCategoryOne.get() == 1:
        group = group | 2
    else:
        group = group & (~2)
    updateGroup()


def OnCategoryTwo():
    global group
    global vCategoryTwo
    if vCategoryTwo.get() == 1:
        group = group | 4
    else:
        group = group & (~4)
    updateGroup()


def OnCategoryThree():
    global group
    global vCategoryThree
    if vCategoryThree.get() == 1:
        group = group | 8
    else:
        group = group & (~8)
    updateGroup()


def OnCategoryFour():
    global group
    global vCategoryFour
    if vCategoryFour.get() == 1:
        group = group | 16
    else:
        group = group & (~16)
    updateGroup()


def OnCategoryFive():
    global group
    global vCategoryFive
    if vCategoryFive.get() == 1:
        group = group | 32
    else:
        group = group & (~32)
    updateGroup()


def OnCategorySix():
    global group
    global vCategorySix
    if vCategorySix.get() == 1:
        group = group | 64
    else:
        group = group & (~64)
    updateGroup()


def OnCategorySeven():
    global group
    global vCategorySeven
    if vCategorySeven.get() == 1:
        group = group | 128
    else:
        group = group & (~128)
    updateGroup()


def generatePassword():
    currentOldPass = txt_old_pass.get()
    if len(currentOldPass) == 0:
        previousPass = txt_pass.get()
        txt_old_pass.delete(0, END)
        txt_old_pass.insert(END, previousPass)
        txt_old_pass.focus()
    defPWLen = 31
    c.send("pyGetPasswordLength")
    try:
        response = c.receive()
        response_list = response[1]
        defPWType = response_list[0] - 1
    except Exception as ex:
        updateDirections("Exception encountered reading\r\nreturn value from pyGetPasswordLength:\r\n" + str(ex))
        defPWType = 2
    if defPWType == 0:
        defPWLen = 8
    elif defPWType == 1:
        defPWLen = 10
    elif defPWType == 2:
        defPWLen = 16
    elif defPWType == 3:
        defPWLen = 24
    elif defPWType == 4:
        defPWLen = 31
    characters = "abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ!#$%*()?-_=+:;{}[]"  # These chars are not generated on the PasswordPump:  , " @ ` \ & ~ | \\ ^ /
    while True:                                                                 # emulate a do while loop in python
        password = "".join(choice(characters) for unusedVar in range(defPWLen)) # generate passwords until one passes
        if passwordComplexityCheck(password):                                   # the complexity check.
            break
    txt_pass.delete(0, END)
    txt_pass.insert(END, password)
    txt_pass.focus()                                                            # to save the old password
    txt_old_pass.focus()                                                        # to save the password


def checkIfPowned():
    currentPass = txt_pass.get()
    if len(currentPass) != 0:
        pownedCnt = powned.check(currentPass)
        if pownedCnt:
            tkinter.messagebox.showinfo('Bad News', 'This password has been seen ' + str(
                pownedCnt) + ' times before.  Do not use it.')
            updateDirections("This password has been recovered in a data breach.  Do not use it.")
        else:
            tkinter.messagebox.showinfo('Good News', 'This password has not been recovered in any data breaches.')
            updateDirections("This password has not been recovered in any data breach.")
        window.update()


def openBrowser():
    try:
        aURL = stripBadChars(txt_url.get())
        webbrowser.open(aURL)
        updateDirections("Opened: " + aURL)
    except Exception as ex:
        updateDirections("There was a problem opening\r\nthe URL:\r\n" + str(ex))
    window.call('wm', 'attributes', '.', '-topmost', True)                      # Place this window on the top
    time.sleep(2)                                                               # Wait two seconds
    if not stayOnTop.get():
        window.after_idle(window.call, 'wm', 'attributes', '.', '-topmost',
                          False)                                                # Now allow this window to go to the background


def openHelp():
    try:
        webbrowser.open(usersGuideLocation)
        updateDirections("Opened: " + usersGuideLocation)
    except Exception as ex:
        updateDirections("There was a problem opening\r\nthe URL:\r\n" + str(ex))


def doStayOnTop():
    if stayOnTop.get():
        window.call('wm', 'attributes', '.', '-topmost', True)
    else:
        window.after_idle(window.call, 'wm', 'attributes', '.', '-topmost', False)


def passwordComplexityCheck(passwd):
    specialSym = ['!', '#', '$', '%', '*', '(', ')', '-', '_', '+', '=', '{', '}', '[', ']', ':', ';', '.', '<', '>',
                  '?', '@']                                                     # !#$%*()-_+={}[]:;.<>?@

    badSym = [',', '"', '`', '\\', '/', '&', '~', '|', '^']                     # ,"`\/&~|^
    passwordOK = True
    rejectReason = 'Password fails complexity\r\ncheck:\r\n'

    if len(passwd) > 31:
        rejectReason += 'The password length should be\r\nnot be greater than 31.\r\n'
        passwordOK = False

    if len(passwd) < 8:
        rejectReason += 'The password length should be\r\nat least 8.\r\n'
        passwordOK = False

    if not any(char.isdigit() for char in passwd):
        rejectReason += 'The password should have at\r\nleast one numeral.\r\n'
        passwordOK = False

    if not any(char.isupper() for char in passwd):
        rejectReason += 'The password should have at\r\nleast one uppercase letter.\r\n'
        passwordOK = False

    if not any(char.islower() for char in passwd):
        rejectReason += 'The password should have at\r\nleast one lowercase letter.\r\n'
        passwordOK = False

    if any(char in badSym for char in passwd):
        rejectReason += 'The password has a forbidden\r\nsymbol: ,"`\/&~|^ \r\n'
        passwordOK = False

    if not any(char in specialSym for char in passwd):
        rejectReason += 'The password should have at\r\nleast one of these symbols:\r\n!#$%*()-_+={}[]:;.<>?'
        passwordOK = False

    if not passwordOK:
        updateDirections(rejectReason)
        txt_pass.config({"foreground": "red"})
    else:
        updateDirections('Password passes complexity\r\nvalidation.')
        txt_pass.config({"foreground": "green"})

    window.update()
    return passwordOK


def flipPassword():
    global showPassword
    if showPassword:
        showPassword = False
        txt_pass.config(show="*")
    else:
        showPassword = True
        txt_pass.config(show="")
    window.update()


def SetGroupCheckBoxes():
    global vFavorites
    global vCategoryOne
    global vCategoryTwo
    global vCategoryThree
    global vCategoryFour
    global vCategoryFive
    global vCategorySix
    global vCategorySeven
    if (group & 1) == 1:
        vFavorites.set(1)
    else:
        vFavorites.set(0)
    if (group & 2) == 2:
        vCategoryOne.set(1)
    else:
        vCategoryOne.set(0)
    if (group & 4) == 4:
        vCategoryTwo.set(1)
    else:
        vCategoryTwo.set(0)
    if (group & 8) == 8:
        vCategoryThree.set(1)
    else:
        vCategoryThree.set(0)
    if (group & 16) == 16:
        vCategoryFour.set(1)
    else:
        vCategoryFour.set(0)
    if (group & 32) == 32:
        vCategoryFive.set(1)
    else:
        vCategoryFive.set(0)
    if (group & 64) == 64:
        vCategorySix.set(1)
    else:
        vCategorySix.set(0)
    if (group & 128) == 128:
        vCategorySeven.set(1)
    else:
        vCategorySeven.set(0)
    window.update()


def customizeGroup1():
    global groupName1
    groupNameTemp = groupName1
    groupName1 = tkinter.simpledialog.askstring("Customize Group", "Customize Group " + groupName1, parent=window)
    if not groupName1:
        groupName1 = groupNameTemp
    c.send("pyUpdateCategoryName", 1, groupName1)
    response = c.receive()
    response_list = response[1]
    ignoredPosition = calcAcctPositionReceive(response_list[0])                 # returns head position
    textboxOne.config(text=groupName1)
    groupsMenu.entryconfigure(1, label=groupName1)


def customizeGroup2():
    global groupName2
    groupNameTemp = groupName2
    groupName2 = tkinter.simpledialog.askstring("Customize Group", "Customize Group " + groupName2, parent=window)
    if not groupName2:
        groupName2 = groupNameTemp
    c.send("pyUpdateCategoryName", 2, groupName2)
    response = c.receive()
    response_list = response[1]
    ignoredPosition = calcAcctPositionReceive(response_list[0])                 # returns head position
    textboxTwo.config(text=groupName2)
    groupsMenu.entryconfigure(2, label=groupName2)


def customizeGroup3():
    global groupName3
    groupNameTemp = groupName3
    groupName3 = tkinter.simpledialog.askstring("Customize Group", "Customize Group " + groupName3, parent=window)
    if not groupName3:
        groupName3 = groupNameTemp
    c.send("pyUpdateCategoryName", 3, groupName3)
    response = c.receive()
    response_list = response[1]
    ignoredPosition = calcAcctPositionReceive(response_list[0])                 # returns head position
    textboxThree.config(text=groupName3)
    groupsMenu.entryconfigure(3, label=groupName3)


def customizeGroup4():
    global groupName4
    groupNameTemp = groupName4
    groupName4 = tkinter.simpledialog.askstring("Customize Group", "Customize Group " + groupName4, parent=window)
    if not groupName4:
        groupName4 = groupNameTemp
    c.send("pyUpdateCategoryName", 4, groupName4)
    response = c.receive()
    response_list = response[1]
    ignoredPosition = calcAcctPositionReceive(response_list[0])                 # returns head position
    textboxFour.config(text=groupName4)
    groupsMenu.entryconfigure(4, label=groupName4)


def customizeGroup5():
    global groupName5
    groupNameTemp = groupName5
    groupName5 = tkinter.simpledialog.askstring("Customize Group", "Customize Group " + groupName5, parent=window)
    if not groupName5:
        groupName5 = groupNameTemp
    c.send("pyUpdateCategoryName", 5, groupName5)
    response = c.receive()
    response_list = response[1]
    ignoredPosition = calcAcctPositionReceive(response_list[0])                 # returns head position
    textboxFive.config(text=groupName5)
    groupsMenu.entryconfigure(5, label=groupName5)


def customizeGroup6():
    global groupName6
    groupNameTemp = groupName6
    groupName6 = tkinter.simpledialog.askstring("Customize Group", "Customize Group " + groupName6, parent=window)
    if not groupName6:
        groupName6 = groupNameTemp
    c.send("pyUpdateCategoryName", 6, groupName6)
    response = c.receive()
    response_list = response[1]
    ignoredPosition = calcAcctPositionReceive(response_list[0])                 # returns head position
    textboxSix.config(text=groupName6)
    groupsMenu.entryconfigure(6, label=groupName6)


def customizeGroup7():
    global groupName7
    groupNameTemp = groupName7
    groupName7 = tkinter.simpledialog.askstring("Customize Group", "Customize Group " + groupName7, parent=window)
    if not groupName7:
        groupName7 = groupNameTemp
    c.send("pyUpdateCategoryName", 7, groupName7)
    response = c.receive()
    response_list = response[1]
    ignoredPosition = calcAcctPositionReceive(response_list[0])                 # returns head position
    textboxSeven.config(text=groupName7)
    groupsMenu.entryconfig(7, label=groupName7)


def getFirmwareVersion():
    c.send("pyGetFirmwareVersion")
    try:
        responseFirmwareVersion = c.receive()
        firmwareVersionList = responseFirmwareVersion[1]
        firmwareVersion = firmwareVersionList[0]
    except UnicodeDecodeError:
        firmwareVersion = ""
        updateDirections("Unable to obtain the firmware version")
    return "Version:" + firmwareVersion


def encrypt(filename, password):
    """
    Given a filename (str) and key (bytes), it encrypts the file and write it
    """
    with open(filename, "rb") as decFile:
        file_data = decFile.read()                                              # read all file data
    password += "================================"
    password = password[0:32]
    key = str.encode(password)
    missing_padding = len(key) % 4
    if missing_padding:
        key += b'=' * (4 - missing_padding)
    key = base64.urlsafe_b64encode(key)
    f = Fernet(key)                                                             # ValueError: Fernet key must be 32 url-safe base64-encoded bytes.
    encrypted_data = f.encrypt(file_data)                                       # encrypt data
    with open(filename, "wb") as encFile:                                       # write the encrypted file
        encFile.write(encrypted_data)


def decrypt(filename, password):
    """
    Given a filename (str) and key (bytes), it decrypts the file and write it
    """

    password += "================================"
    password = password[0:32]
    key = str.encode(password)
    missing_padding = len(key) % 4
    if missing_padding:
        key += b'=' * (4 - missing_padding)
    key = base64.urlsafe_b64encode(key)
    f = Fernet(key)
    with open(filename, "rb") as encFile:
        encrypted_data = encFile.read()                                         # read the encrypted data
    decrypted_data = f.decrypt(encrypted_data)                                  # decrypt data
    with open(filename, "wb") as decFile:                                       # write the original file
        decFile.write(decrypted_data)


def encryptFile():
    if platform.system() == "Windows":
        filename = askopenfilename(initialdir="C:/",                            # TODO: make this work cross platform
                                   filetypes=(("CSV File", "*.csv"), ("All Files", "*.*")),
                                   title="Choose a file to encrypt.")
    elif platform.system() == "Darwin":                                         # Macintosh
        filename = askopenfilename(title="Choose a file to encrypt.")
    elif platform.system() == "Linux":                                          # Linux
        filename = askopenfilename(title="Choose a file to encrypt.")
    else:
        filename = askopenfilename(title="Choose a file to encrypt.")
    if filename == "":
        filename = None
    if filename is not None:
        key = ask_root_password(window)
        if key is not None:
            window.config(cursor="watch")
            encrypt(filename, key)
            updateDirections(filename + " was encrypted.")
            window.config(cursor="")


def decryptFile():
    if platform.system() == "Windows":
        filename = askopenfilename(initialdir="C:/",                            # TODO: make this work cross platform
                                   filetypes=(("CSV File", "*.csv"), ("All Files", "*.*")),
                                   title="Choose a file to encrypt."
                                   )
    elif platform.system() == "Darwin":                                         # Macintosh
        filename = askopenfilename(title="Choose a file to encrypt."
                                   )
    elif platform.system() == "Linux":                                          # Linux
        filename = askopenfilename(title="Choose a file to encrypt."
                                   )
    else:
        filename = askopenfilename(title="Choose a file to encrypt."
                                   )
    if filename == "":
        filename = None
    if filename is not None:
        key = ask_root_password(window)
        if key is not None:
            window.config(cursor="watch")
            decrypt(filename, key)
            updateDirections(filename + " was decrypted.")
            window.config(cursor="")


def ask_root_password(parent=None):
    """
    Shows a window dialog that asks for the file password
    :return: the correct file password if inserted correctly, None otherwise
    """

    if parent is None:
        root_password = tkinter.simpledialog.askstring("Enter Password to Encrypt", "Enter password:", show='*')
    else:
        root_password = tkinter.simpledialog.askstring("Enter Password to Encrypt", "Enter password:", parent=parent,
                                                       show='*')

    if root_password is None:
        return None
    if root_password == "":
        return None
    if len(str.strip(root_password)) == 0:
        return None

    return root_password

                                                                                # enabling the functionality below makes
                                                                                # it impossible to create an .exe file
                                                                                # on Windows.
#try:
#    me = singleton.SingleInstance()                                            # If the PasswordPumpGUI is already
#except singleton.SingleInstanceException as e:                                 # running, tell the user and exit.
#    root = tkinter.Tk()
#    root.withdraw()
#    messagebox.showerror(title="PasswordPumpGUI is Already Running",
#                         message="Another instance of PasswordPumpGUI is already running. Exiting.")
#    sys.exit(-1)

window = Tk()
window.title("PasswordPump Edit Credentials v2.0.8.02")

if platform.system() == "Windows":                                              # e.g. Windows7, Windows10
    window.geometry('400x560')
elif platform.system() == "Darwin":                                             # Macintosh
    window.geometry('580x600')
elif platform.system() == "Linux":                                              # e.g. Ubuntu, Raspbian
    window.geometry('580x600')
else:
    window.geometry('400x555')

stayOnTop = BooleanVar()                                                        # Determines if the Window stays on top
stayOnTop.set(False)                                                            # of all other windows. Default when
                                                                                # starting is No.
lbl_port = Label(window, text="Port", anchor=E, justify=RIGHT, width=10)
lbl_port.grid(column=1, row=0)
frame = Frame(window, width=200, height=200)

frame.grid(column=2, row=1)
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

lbl_old_pass = Label(window, text="Old Password", anchor=E, justify=RIGHT, width=10)
lbl_old_pass.grid(column=1, row=5)

lbl_url = Label(window, text="URL", anchor=E, justify=RIGHT, width=10)
lbl_url.grid(column=1, row=6)

lbl_style = Label(window, text="Style", anchor=E, justify=RIGHT, width=10)
lbl_style.grid(column=1, row=7)

translation_table = dict.fromkeys(map(ord, ',|~"'), '#')

usersGuideLocation = "https://docs.google.com/document/d/1QwUFkCNrrNJYPX6mqauCRvVULn6AmX-2JMsckq2TvfU/edit?usp=sharing"

window.protocol("WM_DELETE_WINDOW", clickedClose)

txt_acct = Entry(window, width=40)
txt_acct.grid(column=2, row=2)

txt_user = Entry(window, width=40)
txt_user.grid(column=2, row=3)

txt_pass = Entry(window, width=40)
txt_pass.grid(column=2, row=4)

txt_old_pass = Entry(window, width=40)
txt_old_pass.grid(column=2, row=5)

txt_url = Entry(window, width=40)
txt_url.grid(column=2, row=6)

txt_acct.config(state='disabled')
txt_user.config(state='disabled')
txt_pass.config(state='disabled')
txt_pass.config(show="*")
txt_old_pass.config(state='disabled')
txt_url.config(state='disabled')

groupName1 = "Group1"
groupName2 = "Group2"
groupName3 = "Group3"
groupName4 = "Group4"
groupName5 = "Group5"
groupName6 = "Group6"
groupName7 = "Group7"

menubar = Menu(window)
window.config(menu=menubar)
file = Menu(menubar, tearoff=0)
importMenu = Menu(menubar, tearoff=0)
exportMenu = Menu(menubar, tearoff=0)
file.add_cascade(label='Import', menu=importMenu)
importMenu.add_command(label='Import from Chrome', command=ImportFileChrome)
importMenu.add_command(label='Import from KeePass', command=ImportFileKeePass)
importMenu.add_command(label='Import from PasswordPump', command=ImportFilePasswordPump)
file.add_cascade(label='Export', menu=exportMenu)
exportMenu.add_command(label='Export to PasswordPump', command=ExportFile)
# file.add_command(label='Insert', command=clickedInsert)
# file.add_command(label='Delete', command=clickedDelete)
file.add_separator()
file.add_command(label='Encrypt File...', command=encryptFile)
file.add_command(label='Decrypt File...', command=decryptFile)
file.add_separator()
file.add_command(label='Exit', command=clickedClose)
menubar.add_cascade(label='File', menu=file)

backup = Menu(menubar, tearoff=0)
backup.add_command(label='Backup EEprom', command=BackupEEprom)
backup.add_command(label='Restore EEprom', command=RestoreEEprom)
menubar.add_cascade(label='Backup/Restore', menu=backup)

ppsettings = Menu(menubar, tearoff=0)
groupsMenu = Menu(menubar, tearoff=1)                                           # tearoff must be 1 here or defects are introduced in the menu
ppsettings.add_command(label='Change Master Password', command=clickedChangeMasterPass)
ppsettings.add_command(label='Show Password on Device', command=clickedShowPassword)
ppsettings.add_command(label='Decoy Password', command=clickedDecoyPassword)
ppsettings.add_cascade(label='Customize Groups', menu=groupsMenu)
groupsMenu.add_command(label=groupName1, command=customizeGroup1)
groupsMenu.add_command(label=groupName2, command=customizeGroup2)
groupsMenu.add_command(label=groupName3, command=customizeGroup3)
groupsMenu.add_command(label=groupName4, command=customizeGroup4)
groupsMenu.add_command(label=groupName5, command=customizeGroup5)
groupsMenu.add_command(label=groupName6, command=customizeGroup6)
groupsMenu.add_command(label=groupName7, command=customizeGroup7)
ppsettings.add_checkbutton(label='Stay On Top', var=stayOnTop, command=doStayOnTop)
ppsettings.add_command(label='More settings...', command=ShowSettingsWindow)
ppsettings.add_command(label='Fix corrupt account list', command=FixCorruptLinkedList)
ppsettings.add_command(label='Factory Reset', command=FactoryReset)
menubar.add_cascade(label='Settings', menu=ppsettings)

pphelp = Menu(menubar, tearoff=0)
pphelp.add_command(label='Help', command=openHelp)
pphelp.add_separator()
pphelp.add_command(label='Check for Updates', command=updateCheck)
pphelp.add_command(label='Check for Firmware Updates', command=updateFirmwareCheck)
menubar.add_cascade(label='Help', menu=pphelp)
pphelp.entryconfig('Check for Firmware Updates', state='disabled')

menubar.entryconfig('File', state='normal')
file.entryconfig('Import', state='disabled')
file.entryconfig('Export', state='disabled')

menubar.entryconfig('Backup/Restore', state='disabled')
menubar.entryconfig('Settings', state='disabled')

cbStyle = Combobox(window, justify=LEFT, width=37)
cbStyle['values'] = ('usr<RTN>pass<RTN>',
                     'usr<TAB>pass<RTN>',
                     'usr<TAB>pass<TAB><RTN>')
cbStyle.current(1)
cbStyle.grid(column=2, row=7)
cbStyle.bind('<<ComboboxSelected>>', on_style_select)
cbStyle.config(state='disabled')

btn_previous = Button(window, text="<<Previous", command=clickedPrevious)
btn_previous.grid(column=1, row=19)
btn_previous.config(state='disabled')

btn_insert = Button(window, text="Insert", command=clickedInsert)
btn_insert.grid(column=1, row=18)
btn_insert.config(state='disabled')

btn_delete = Button(window, text="Delete", command=clickedDelete)
btn_delete.grid(column=4, row=18)
btn_delete.config(state='disabled')

btn_open = Button(window, text="Open Port", command=clickedOpen)
btn_open.grid(column=4, row=0)

lb.bind("<<ListboxSelect>>", clickedLoadDB)

btn_generate = Button(window, text="Generate", command=generatePassword)
btn_generate.grid(column=4, row=4)
btn_generate.config(state='disabled')

btn_powned = Button(window, text="Pwned?", command=checkIfPowned)
btn_powned.grid(column=4, row=5)
btn_powned.config(state='disabled')

btn_browser = Button(window, text="Open", command=openBrowser)
btn_browser.grid(column=4, row=6)
btn_browser.config(state='disabled')

btn_flip_pw = Button(window, text="Password", command=flipPassword)
btn_flip_pw.grid(column=1, row=4)
btn_flip_pw.config(state='disabled')

btn_next = Button(window, text="Next>>", command=clickedNext)
btn_next.grid(column=4, row=19)
btn_next.config(state='disabled')

vFavorites = IntVar()
vCategoryOne = IntVar()
vCategoryTwo = IntVar()
vCategoryThree = IntVar()
vCategoryFour = IntVar()
vCategoryFive = IntVar()
vCategorySix = IntVar()
vCategorySeven = IntVar()

textboxFavorites = Checkbutton(window, text="Favorites ", variable=vFavorites, command=OnFavorites, onvalue=1,
                               offvalue=0)
textboxFavorites.var = vFavorites
textboxFavorites.grid(column=1, row=12)

textboxOne = Checkbutton(window, text=groupName1, variable=vCategoryOne, command=OnCategoryOne, onvalue=1, offvalue=0)
textboxOne.var = vCategoryOne
textboxOne.grid(column=1, row=13)

textboxTwo = Checkbutton(window, text=groupName2, variable=vCategoryTwo, command=OnCategoryTwo, onvalue=1, offvalue=0)
textboxTwo.var = vCategoryTwo
textboxTwo.grid(column=1, row=14)

textboxThree = Checkbutton(window, text=groupName3, variable=vCategoryThree, command=OnCategoryThree, onvalue=1,
                           offvalue=0)
textboxThree.var = vCategoryThree
textboxThree.grid(column=1, row=15)

textboxFour = Checkbutton(window, text=groupName4, variable=vCategoryFour, command=OnCategoryFour, onvalue=1,
                          offvalue=0)
textboxFour.var = vCategoryFour
textboxFour.grid(column=2, row=12)

textboxFive = Checkbutton(window, text=groupName5, variable=vCategoryFive, command=OnCategoryFive, onvalue=1,
                          offvalue=0)
textboxFive.var = vCategoryFive
textboxFive.grid(column=2, row=13)

textboxSix = Checkbutton(window, text=groupName6, variable=vCategorySix, command=OnCategorySix, onvalue=1, offvalue=0)
textboxSix.var = vCategorySix
textboxSix.grid(column=2, row=14)

textboxSeven = Checkbutton(window, text=groupName7, variable=vCategorySeven, command=OnCategorySeven, onvalue=1,
                           offvalue=0)
textboxSeven.var = vCategorySeven
textboxSeven.grid(column=2, row=15)

textboxFavorites.config(state='disabled')
textboxOne.config(state='disabled')
textboxTwo.config(state='disabled')
textboxThree.config(state='disabled')
textboxFour.config(state='disabled')
textboxFive.config(state='disabled')
textboxSix.config(state='disabled')
textboxSeven.config(state='disabled')

lb.bind("<Down>", OnEntryDown)
lb.bind("<Up>", OnEntryUp)

lbl_help = Label(window, text="Instructions", anchor=W, justify=CENTER, width=11)
lbl_help.grid(column=2, row=16)

txt_dir = Text(window, height=5, width=30, relief=FLAT, background="light grey")
txt_dir.grid(column=2, row=17)
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

position = 0                                                                    # Global variables
head = 0
tail = 0
selection = 0
state = "None"
arduinoAttached = 0
group = 0
showPassword = False

window.mainloop()
