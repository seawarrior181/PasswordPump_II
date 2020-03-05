# PasswordPump v2.0

The PasswordPump is a USB device that helps you manage credentials and supply credentials to computers, applications and web sites.  The purpose of this repository on GitHub is to disseminate software for and information about the PasswordPump II.  See the Password Pump II Users Guide.pdf for details.  PasswordPumpM4_02.dip is a DIPTrace (https://diptrace.com/) file.  You can use DIPTrace with that file to create the files necessary to manufacture the custom PCB.

(c) 2020 Daniel Murphy


#Change Log

2020-02-24 v2.0.2 Eliminated the need for the PyCmdMessenger edits.  You still need to install PyCmdMessenger, you just don't need to make any edits to it.

2020-02-22 v2.0.1 Fixed an issue whereby the 124th account was not handled correctly under a variety of different situations.  Changed PassPumpGUI_v2_0_0.py and PasswordPump_v_2_0_0.ino.

2020-02-17 v2.0.0  Versioned all of the programs and documention, set them to v2.0.0.  There were minor cosmetic changes to the software related to the new version number.  PasswordPumpGUI was modified to size the main window based on the operating system.

2020-02-15 no rev  Added a feature whereby when you select logout from the main menu on the PasswordPump, you're logged out of the PasswordPump and the computer screen is also locked.  Changes the behavior of the splash screen; no more scrolling PasswordPump and a faster startup.
