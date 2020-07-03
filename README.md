# PasswordPump v2.0

This is v2.0 of the PasswordPump, a USB device that manages credentials for up to 250 accounts.  Credentials (account names, usernames, passwords, URLs and old passwords) are stored ONLY on the device itself, on two removable EEprom chips using military grade encryption (AES-256).  The credentials are not stored in the cloud or in a file on your computer where they are more exposed to hackers.  Credentials are backed up on the device itself; i.e. encrypted credentials are moved from the primary EEprom chip to the backup EEprom on demand.  You may remove the EEprom chips from the device (perhaps to keep a third or fourth backup).  Credentials are entered either via the rotary encoder (on the left), via keyboard and serial terminal, or via a Python based graphical user interface (the PasswordPumpGUI).   The device itself is approximately 1 1/8 x 2 3/4 inches, or 29 x 71 millimeters.  Currently it's not housed inside of a case, but it should be and will be once a design of the case is complete.  If you design a case for the PasswordPump please share it with us!

The purpose of this repository on GitHub is to disseminate software for and information about the PasswordPump v2.0.  See the Password Pump II Users Guide.pdf and https://5volts.org for details.  

# Change Log
unreleased v2.0.4 
  * Added support for German keyboards.
  * Added the ability to customize the group names via PasswordPumpGUI.  
  * Added Factory Reset to the PassPumpGUI program. 
  * Added a pre-compiler directive to deal with "lefty" rotary encoders; see users guide for more info.  
  * Modified the custom PCB and added a pre-compiler directive for use with Adafruit ItsyBitsy M0. 
  * Fixed the defect whereby entering the decoy password did not result in a factory reset. 
  * Tweaked the mechanism for generating a random seed.  
  * Fixed the following defect: Via PasswordPumpGUI Insert, then (Alt)(Tab) to navigate to another application;  Upon returning to PasswordPumpGUI the Account Name is "Unknown";  Set focus to another account, the PasswordPump and PasswordPumpGUI freeze;  Close the PasswordPumpGUI window and long click on the PasswordPump;  Now there is only one account in the PasswordPump; Restore from secondary EEprom.  This issue is resolved.

2020-04-26 v2.0.3 
  * Fixed a defect discovered by Neil whereby the @ needed to be added back to the list of characters available for input via rotary encoder.  
  * Fixed an error whereby you could scroll past the z when entering characters via rotary encoder.  
  * Changed automatic logout from the device so that it does not automatically lock your computer. 
  * Fixed a defect whereby when long clicking after search by group you didn't return to the right group you always returned to favorites.  
  * Changed the Credentials menu so that you always know which account you're in.  
  * Fixed a problem in the Settings menu where you were not returning to the menu item from which you came.  
  * Fixed some issues with menu navigation when long clicking to make it more intuitive.  
  * Added the ability to customize the names of groups.  
  * Fixed a defect in PasswordPumpGUI whereby the value of a text box where the cursor is positioned before the Insert menu item is selected becomes blank after a new record is inserted by eliminating Insert (and Delete) from the File menu and substituting buttons for those functions. 
  * Fixed an issue discovered by Neil whereby the custom group names were not reflected in PasswordPumpGUI.

2020-02-24 v2.0.2 Eliminated the need for the PyCmdMessenger edits.  You still need to install PyCmdMessenger, you just don't need to make any edits to it.

2020-02-22 v2.0.1 Fixed an issue whereby the 124th account was not handled correctly under a variety of different situations.  Changed PassPumpGUI_v2_0_0.py and PasswordPump_v_2_0_0.ino.

2020-02-17 v2.0.0  Versioned all of the programs and documention, set them to v2.0.0.  There were minor cosmetic changes to the software related to the new version number.  PasswordPumpGUI was modified to size the main window based on the operating system.

2020-02-15 no rev  Added a feature whereby when you select logout from the main menu on the PasswordPump, you're logged out of the PasswordPump and the computer screen is also locked.  Changes the behavior of the splash screen; no more scrolling PasswordPump and a faster startup.

# Video

https://youtu.be/f4Iukt5VDUo

# License

<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/3.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-sa/3.0/88x31.png" /></a><br />This work is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/3.0/">Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License</a>.

This program and device are distributed in the hope that they will be 
useful, but WITHOUT ANY WARRANTY; without even the implied warranty 
of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

(c) 2020 Daniel Murphy
