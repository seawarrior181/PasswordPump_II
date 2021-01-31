# PasswordPump v2.0

This is v2.0 of the PasswordPump, a USB device that manages credentials for up to 250 accounts.  Credentials (account names, usernames, passwords, URLs and old passwords) are stored ONLY on the device itself, on two removable EEprom chips using military grade encryption (AES-256).  The credentials are not stored in the cloud or in a file on your computer where they are more exposed to hackers.  Credentials are backed up on the device itself; i.e. encrypted credentials are moved from the primary EEprom chip to the backup EEprom on demand.  You may remove the EEprom chips from the device (perhaps to keep a third or fourth backup).  Credentials are entered either via the rotary encoder (on the left), via keyboard and serial terminal, or via a Python based graphical user interface (the PasswordPumpGUI).   The device itself is approximately 1 1/8 x 2 3/4 inches, or 29 x 71 millimeters.  Currently it's not housed inside of a case, but it should be and will be once a design of the case is complete.  If you design a case for the PasswordPump please share it with us!

The purpose of this repository on GitHub is to disseminate software for and information about the PasswordPump v2.0.  See the Password Pump II Users Guide.pdf and https://5volts.org for details.  

If you are simply wanting to download the latest version of the PasswordPump software onto your PasswordPump device follow the instructions provided in the "Burning Firmware From the BOSSA GUI" section of the Users Guide.

It is always wise to download the latest version of the PasswordPumpGUI when you are downloading the latest version of PasswordPump_v_2_0.ino.

If you are interested in printing the case (at https://github.com/seawarrior181/PasswordPump_II/blob/master/3D-Print), take a look here https://github.com/seawarrior181/PasswordPump_II/tree/master/media for pictures and instructions related to how the case can be further modified.  Thanks to Kevin Lever for these suggestions.

Note about v2.0.5 of the PasswordPump:
If I shipped to you a PasswordPump which indicates that it is at v2.0.5, it will most likely have a "lefty" encoder.  This means that as you turn the rotary encoder clockwise, it proceeds backwards through the alphabet instead of forwards.  Some folks find this counter intuitive.  To fix this you merely need to navigate to Settings->Encoder Type and change it from ‘Normal’ to ‘Lefty’; and don’t worry, the setting is remembered if you power cycle the device.  If you factory reset the device you’ll need to change the Encoder Type to Lefty again.

# News
  * There is now a new model of PasswordPump available for purchase; the Joystick model.  This PasswordPump has a lower profile, but it does take a little bit longer to scroll through all of your accounts.  It works well.
  * On Windows there exists now a setup program that does not require Python to be installed.  It's located here:
      https://github.com/seawarrior181/PasswordPump_II/blob/master/v2_0_8/PassPumpGUI/inno/PasswordPumpSetup.exe
      
  * There are several new cases to announce; there is a new case for the rotary encoder model available on Tindie.  Soon to follow there will be a new case available for the Joystick model that looks pretty cool.  Both of these cases were designed and donated by scootercommutter.  Because 3D printing is expensive I'll be selling them on Tindie for a price that's quite close to my cost.  Finally there is an acrylic enclosure on the way, the enclosure that's depicted on the front of the Users Guide.  The .stl files for the two cases are posted on this site so that you can print them out yourself if you have a 3D printer (thanks scootercommuter!).  Finally, if you are interested in any of these cases/enclosures and they are not in stock on Tindie send me an email so that I know there is interest.  There are pictures of all three designs in the media section of this site, located here (best viewed by downloading):

      https://github.com/seawarrior181/PasswordPump_II/blob/master/media/PPEncoder.jpg
      https://github.com/seawarrior181/PasswordPump_II/blob/master/media/PPEncoderEnclosure.jpg
      https://github.com/seawarrior181/PasswordPump_II/blob/master/media/PPEncoderCase.jpg
      https://github.com/seawarrior181/PasswordPump_II/blob/master/media/PPJoystick.jpg
      https://github.com/seawarrior181/PasswordPump_II/blob/master/media/PPJoystickCase.jpg
  
  * On Windows you no longer need to install Python to run the PasswordPumpGUI; there is an .exe file available here: https://github.com/seawarrior181/PasswordPump_II/blob/master/v2_0_8/PassPumpGUI/dist/PasswordPumpGUI.exe .  Someday I'll create an install program, but for now you can just copy the .exe to your desktop, just click on the Download button then move the PasswordPumpGUI.exe file to your Desktop.

# Change Log

v2.0.8
  * Modified the PCB design to accomodate a joystick instead of a rotary encoder.
  * Added compile time directives to compile for rotaray encoder or joystick model.
  * Added the ability to download the latest version of the PasswordPumpGUI to the PasswordPumpGUI.
  * Added the ability to download the latest versions of the firmware from the PasswordPumpGUI.

2020-12-31 v2.0.6
  * Made some minor edits to the PasswordPumpGUI menus
  * Accepted design docs for an exceptionally well done case, here: https://github.com/seawarrior181/PasswordPump_II/tree/master/3D-Print/scootercommuter_Design
  * Added a setting that allows for the introduction of delay between the transmission of each character to the compuer/tablet/phone so that slower devices do not drop characters. 
  * Added the ability to set the default length of the generated password; 8, 10, 16, 24, or 31.
  * Fixed a problem with saving PasswordPump export files on Linux.
  * Added encryption and decryption of PasswordPump export files produced in PasswordPumpGUI.
  * Added a dialog box used on exit to confirm exit from PasswordPumpGUI.
  * Fixed an issue with style default value sometimes not getting handled correctly in PasswordPumpGUI.
  * Enforced a rule that device generated passwords must pass the same compexity check as the PasswordPumpGUI generated passwords.
  * Added the ability to edit RGB LED intensity, login attempts before logout, and  minutes before automatic logout from the PasswordPumpGUI.
  * Changed the behavior of sending a password so that a <TAB> character is sent before the <CR> carriage return character is sent.  This helps with automatically logging all the way into certain sites.
  * Added a feature whereby after 1 minute of inactivity the time remaining before automatic logout is displayed on the device.
  * Fixed a defect in PasswordPumpGUI whereby you could navigate to and edit fields before the port was open, resulting in the display of error messages.
  * Cleaned up Factory Reset to reset more values, like keyboard language, encoder type, logout timeout, so that they would not persist after a soft reset (a reset performed by selecting Factory Reset from the menu).  The values were not persisting after a hard reset.
  * Fixed a defect in Fix Corruption whereby if the head of the linked list was deleted, Fix Corruption would effectivly wipe out the ability to navigate to all accounts.
  * Updated the version number from v2.0.5 to v2.0.6.

2020-10-17 v2.0.5

  * Added the fix corrupt account list feature to the PasswordPumpGUI_v2_0.py.
  * A customer has recently reported to me that the linked list that keeps the credentials sorted by account name is becoming corrupt, which is affecting his ability to navigate through the credentials on the device via the rotary encoder or via the PasswordPumpGUI.  Toward fixing that problem I have added a menu option entitled Fix Corruption.  It is not clear to me yet how this corruption is introduced, as I am unable to reproduce the conditions under which the defect occurs in my lab.
  * Added a feature in settings whereby you can remap the orientation of the PasswordPump's text so that you can use it with the rotary encoder on the left (default) or the right.
  * Added the ability in settings to select from a variety of fonts for the PasswordPump's display.
  * Fixed several issues with menu navigation; selecting 'N' and not being returned to the top of the main menu, long clicking and the screen not clearing.
  * Removed the font fixednums8x16 which wasn't working, resulting in losing all creds.
  * Changed the default font.
  * Added a feature whereby the user can select from a variety of different fonts.

2020-07-24 v2.0.4 
  * Made the encoder type configurable; i.e. to handle 'lefty' encoders w/o the precompiler directive.
  * Fixed a problem with the way PasswordPumpGUI handled style when it's set to 255 (the default before it's written to EEprom).
  * Added support for Czech, Danish, Swedish, Norwegian, Finnish, French, German and Spanish keyboards.  US is the default.  See the Known Defects section of the Users Guide for more information about this functionality.
  * Fixed a problem with navigating back to the correct main menu elements on long click.
  * Fixed the Style dropdown in PasswordPumpGUI to show the inter username / password character's name instead of the value stored behind the scenes.
  * Added a check in PasswordPumpGUI for password complexity.  Informational only.
  * In the PasswordPumpGUI, added the ability to check to see if your password has ever been discovered in a known data breach (pwned).
  * Added the ability to customize the group names via PasswordPumpGUI.  
  * Added Factory Reset to the PassPumpGUI program. 
  * Added a pre-compiler directive to deal with "lefty" rotary encoders; see users guide for more info.  (Obsolete). 
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
