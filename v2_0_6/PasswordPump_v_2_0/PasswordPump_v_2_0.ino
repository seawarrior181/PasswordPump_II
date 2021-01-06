/*               ___                              _ ___
                | _ \__ _ _______ __ _____ _ _ __| | _ \_  _ _ __  _ __ 
                |  _/ _` (_-<_-< V  V / _ \ '_/ _` |  _/ || | '  \| '_ \
                |_| \__,_/__/__/\_/\_/\___/_| \__,_|_|  \_,_|_|_|_| .__/
  Author:       Daniel J. Murphy                                  |_| 
  File:         PasswordPump_v_2_0.ino
  Version:      2.0.6
  Date:         2019/07/26 - 2020/12/08
  Language:     Arduino IDE 1.8.13, C++
  Device:       Adafruit ItsyBitsy  M0 Express‎ or Adafruit  ItsyBitsy M4 Express‎
  MCU:          ATSAMD21G18 32-bit  Cortex M0+  or  ATSAMD51J19 32-bit Cortex M4
  Memory:       256KB  Flash   and  32KB RAM   or  512KB  Flash  and   192KB RAM
  EEprom:       2MB of SPI Flash (not used)
  Clock Speed:  48 MHz (M0) or 120MHz (M4)
  Voltage:      3.3v MCU & 25LC512 EEProm / 5v RGB LED, Rotary Encoder,  SSD1306 
                OLED 
  Current:      0.03A
  Components:   RGB LED, SSD1306 128x32 LED  display, one momentary push button, 
                one  rotary encoder,  2 4.7kohm  resistors  for  I2C,  3  220ohm 
                resistors  for  the  RGB  LED,  2 25LC512 external EEprom chips, 
                custom PCB, plastic knob, USB cable.
  Purpose
  =======
  - To manage user names and passwords and to type them in via keyboard/USB.  To
    facilitate  the use of really strong 31 character UUID like passwords on all
    accounts.
	
  Device Program Files
  ====================
  CzechKeyboard.h
  DanishKeyboard.h
  FinnishKeyboard.h
  FrenchKeyboard.h
  GermanKeyboard.h
  Keyboard.cpp
  Keyboard.h
  KeyboardTop.h
  NorwegianKeyboard.h
  PasswordPump_v_2_0.ino
  SpanishKeyboard.h
  SwedishKeyboard.h
  UKKeyboard.h
  USKeyboard.h
  
  Documentation
  =============
  For more information about this project visit 
  https://www.5volts.org/post/passwordpump-v2-0.
  To see the source code in GitHub point your browser to
  https://github.com/seawarrior181/PasswordPump_II.  
  To purchase a kit visit
  https://www.tindie.com/products/passwordpump/passwordpump-v20/
  To see a video about the project navigate to 
  https://www.youtube.com/watch?v=f4Iukt5VDUo.

  Features
  ========
  - Authenticate to device with 16 character master password
  - Search for accounts
  - Send user name and password to computer as if typed in via keyboard
  - Add account name, user name, password (generated or not), url, old 
    password
  - Edit existing user name, password, old password, groups/categories, URL, 
    style (inter-username/password character, <Return> or <Tab>)
  - Delete account
  - Generate password
  - Store old password
  - Data entry via rotary encoder or keyboard and serial monitor, or via client
    Python program running in Windows.
  - Accounts added in alphabetical order
  - Store up to 253 sets of credentials
  - Backup all accounts to a second encrypted external EEprom
  - Logout / de-authenticate / lock computer via menu
  - Factory reset via menu (when authenticated)
  - Configurable password display on or off
  - Configurable failed login count factory reset (3, 5, 10, 25)
  - Configurable automatic logout after count of minutes (30, 60, 90, 120, 240,
    1, Never)
  - Configurable RGB LED intensity (high, medium, low, off)
  - Configurable font
  - Configurable display orientation (rotary encoder on the left or the right)
  - Configurable generated password size; 8, 10, 16, 24 or 31.
  - All passwords (except master password) are encrypted w/ AES-256; master 
    password is hashed w/ SHA-256.
  - Change master password
  - Export/Import to/from PasswordPump CSV format 
  - Import KeePass exported CSV file
  - Import passwords from Chrome
  - Associate credentials with custom groups for better organization; search by 
    group. Defaults are (Favorites, Work, Personal, Home, School, Financial, 
    Mail, Custom)
  - Decoy password feature that automatically factory resets the device if
    entered (e.g. while the user is under duress)
  - Supports use of several international keyboards.
  - Check if password is pwned/appeard in a data breach (in Python GUI)
  - Check for password complexity (in Python GUI)
  
  Compatability
  =============
  The PasswordPump has been shown to work with Windows machines, Apple, and 
  Android phones and tablets.  Specifically the following are supported:
   - Windows 7
   - Windows 10
   - Mac OS X
   - Ubuntu
   - Raspberry Pi OS (Raspbian)
   - Android
  If you’ve successfully (or unsuccessfully) used the PasswordPump with an 
  operating system that’s not on this list let me know so I can add it.
  
  Known Defects/Issues
  ====================  
    - = outstanding             
		! = will not fix
    x = fixed but needs testing 
    * = fixed - if a release is listed, that's the release in which it was fixed                  
 1- The linked list that manages the list of accounts is sometimes corrupted. 
    To mitigate this I added a 'Fix Corruption' feature that should address any 
    corruption in the linked list. Exact conditions of corruption cannot be 
    reproduced in the lab at this time, and code changes have been made in an 
    attepmt to fix it. This issue has been reported by one customer.
 2- Embedded quote in a CSV import file are not getting saved to the file e.g.
    password.
 3- When you import credentials with <CR><LF> in the account name bad things
    happen.
 4- When using the PasswordPump with some tablets and phones the input from the
    PasswordPump seems to fast because characters are dropped.  Add the ability
    to slow down the input from the PasswordPump to the target device.
  ! If you've set the keyboard language during a session, then you select
    factory reset, the keyboard language is not reset to the default until you 
    press the reset button.
  ! When entering an account name 29 chars long via keyboard, nothing gets 
    entered.  I doubt that anyone is actually entering credentials via
    serial terminal at this point.  Use PasswordPumpGUI instead.
  ! In the switch statement for EVENT_SINGLE_CLICK the case statements 
    are not in order. When they are in order it doesn't evaluate 
    correctly.
  ! Fix the inconsistency with the on-board RGB LED and the 5mm Diff RGB LED.
  x Duplicate names freeze the MCU in the keepass import file (consecutive?)
  * single character user names and passwords are not working well
  * When deleting the first account in the linked list and then running fix
    corruption, it would have the effect of deleting all accounts (corrupted
    the linked list).
  * After a Factory Reset operation, the encoder type, font, and orientation
    settings were persisting until a hard reset was performed.
  * You can only select a new keyboard language once, the second time will 
    freeze the MCU.  To work around this resetting the keyboard more than
    once is prohibited. If you do reset the keyboard a second time you need
    to reset the device for the change to take effect.
  * Enabled the ability to fix a corrupt linked account list.
  * Delete screws up the account count when it leaves a hole.  e.g. add AAA, 
    BBB, CCC; delete BBB, you'll only be able to "Find" AAA.
  * Does not work correctly with keyboards that are not US.
	* Issue because listHead is set to 0 before there are any elements in the 
	  linked list; after factory reset when importing credentials ERR: 031
		appears, but it's benign.
  * It is possible to enter a duplicate account via the PasswordPump device.
  * When deleting duplicate accounts (duplicate account names) corruption is 
    introduced.
  * Decoy password feature is not working when the decoy password is entered.
	* 2.4.0: Via PasswordPumpGUI Insert, then <Alt><Tab> to another application.  
		Upon returning to PasswordPumpGUI the Account Name is "Unknown".  Set focus
		to another account, the PasswordPump and PasswordPumpGUI freeze.  Close the
		PasswordPumpGUI window and long click on the PasswordPump.  Now there is
		only one account in the PasswordPump. Restore from secondary EEprom.
  * single click after Reset brings you to alpha edit mode
  * Should probably remove Keyboard ON/OFF from saved properties and always 
    default to Keyboard OFF; or make sure it is always OFF when backing up 
    EEProm.
  * Added account 'Add Account' and then deleted, corrupted linked list
  * Added account to the end of the linked list, corrupted linked list
  * After deleting account change the location of the menu
  * Nail down the menu / UI layout.  
  * Navigation back to previous menu needs work (EVENT_LONG_CLICK).
  * When returning from setting anthing in the settings menu you're not returned
    to the menu item from where you came.
  * When long clicking after search by group you don't return to the right 
    group you always return to favorites.
  * The automatic logout of the PasswordPump after inactivity is also locking
    the computer.  It should just logout of the PasswordPump.
  * User can scroll past z when entering text.
  * If you add an account via PasswordPumpGUI and never visit the URL field,
    garbage is shown for the URL via the PasswordPump UI.
  * When doing a master password change one of the accounts always ends up 
    corrupt.
  * Old password is getting populated with junk in unknown circumstances
  * If there are commas or double quotes in the text of a field we're trying to
    import, import breaks.
  * When a user name isn't specified in a KeePass export file, the password 
    isn't populated at all (it's blank).(no longer relevant)
  * Some character loss when exporting to PPEXPORT.CSV and then re-importing.
    (no longer relevant)
  * Fix defect in FindAccountPos; ERR: 033 when importing existing account
    (intermittent) (no longer relevant)
  * See if you can change the font of the UI and add a fourth line. (can't)
  * we are only encrypting the first 16 characters of account name, user name 
    and password.  The sha256 block size is 16.
  * A forward slash (escape character) at the end of a field causes the PC UI
    to throw an exception.
  * When there is a tilde (~) in a field this causes the PC UI to throw an 
    exception.
  * We are only accommodating password length of 30 instead of 31 when 
    interacting with the PasswordPumpGUI.  Same problem with user names.
  * See if you can add one more char to the horizontal size of the SSD1306. (No)
  * It's not possible to add a new account via the PC client.
  * When adding an account via rotary encoder it's automatically assigned to the
    favorites group.
  * You can import 51 accounts, and exit from the python UI, and then navigate
    through the accounts on the device, but if you power cycle the device all of
    the accounts disappear.
  * PC client isn't working correctly, the fields are not getting enabled.
  * URLs exceeding ABOUT 53 characters are not importing correctly.
  * Add Web Site to the python client and test.
  * Entering Find Favorites when there are no Favorites yields undefined 
    behavior.
  * Can't seem to send a <tab> character via the Keyboard.  Tried KEY_TAB, 
    TAB_KEY, 0x2b, 0xB3, '  '.
  * Find Favorites freezes the MCU if there are no favorites (or shows garbage)
  * The problem with the rotary encoder needs to be addressed.
  * When updating an existing account via import KeePass, the linked list is
    corrupted even though the account name isn't changed.  Go from 111 accounts
    to 93 accounts when update Wachusette.
  * Overflow probably causes automatic logout even when logoutTimeout is set to 
    0
  * When you put in a master password longer than the real master password
    authentication succeeds. [CAN'T REPRODUCE]
  * make the display 20 characters wide
  * There should be another option in Send Credentials, an option to send the 
    password with and without the <RET> at the end.
  * Test w/ 25LC512 chips.
  * Setup of the keyboard and show passwords menu items is freezing the mcu.
  * URLs over 64 characters were not loading because of the EEProm page size.
  * Change master password results in encrypted account creds displaying
  * The default inter credentials character should be <TAB>.
  * There doesn't seem to be a delay anymore between the sending of the account 
    name and the sending of the password.
  * The first and last sets of credentials imported appear encrypted to the 
    user.
  * Consider removing "&" from the legal characters when a password/UUID is 
    generated.
  * An account name that exceeded 31 chars imported in entirety, wasn't 
    truncated at 31 chars.  APEX... [burned by Notepad++ again]
  * RGB LED is too bright.
  * After entering Style, we return to Account Name, but account name is blank.
  * When importing 112 keepass credential sets only 49 make it into the EEprom.
  * remove inclusion of /\@"'` from generated passwords
  * we are authenticated after blowing all the credentials away after 10 
    failures
  * Phantom account is getting added to the list of accounts
  * Fix issue w/ screen "trash"
  * DisplayLine2 needs to be blanked out after retuning from Find or Add acct.
  * When you enter Find Account the account name of the first account isn't 
    getting displayed (except on display line 3).
  * FactoryReset isn't deleting credentials
  * after deleting an account we're returned to the send credentials menu 
    instead of the find account menu
  * When logging in via Remote Desktop and suppling the user name and password,
    we seem to 'hit return' after entering just the user name.
  * automatic initialization after 10 failed login attempts is prompting the 
    user to confirm the action.
  * When you select add account and immediately scroll through the options there
    is apparent corruption in the menu selections
  * Long clicking out of confirm account delete brings you to the main menu 
    instead of the edit credentials menu.
  * When we first enter the find account menu the currentAccount can be wrong
  * don't show Master Password menu choice after authenticating
  * Deleting the head or tail results in corruption
  * When using extended memory crash at line 1367 where the LCD output is 
    trashed. Suspect some conflict w/ the 25LC256 EEprom chip.  Hangs subsequent
    to line 1367. Search for "trashed".
  * Backup All to a file isn't in alphabetical order
  * Backup all isn't consistently printing carriage returns.
  * passwords are not generating correctly
  * the LCD's back-light is not turning on, needed to operate in the dark
  * after add account the account isn't showing in find account
  * after hitting reset show password = 0
  * turning the rotary encoder fast doesn't scroll through the menu fast  
    [sending output to the serial monitor corrects this] 
  * can't add a new account; can't scroll edit menu on first account add
  * long click seems too long
  * first account added doesn't immediately show in find account after it's 
    added.
  * after reset, stuck in reset.
  * in LCD mode too many chars in "Show Passwrd OFF", freezes device.
  * Crash when scrolling up the menu after selecting 'add account'.
  * failures are not showing correctly because you need to blank out the line 
    first
  * after adding an account we can't find it
  
  TODO / Enhancements
  ===================
    - = unimplemented
    ? = tried to implement, ran into problems
    % = concerned there isn't enough memory left to implement
    ! = will not implement
    x = implemented but not tested  
    * = implemented and tested
  - In general, vastly improve the international keyboard support.
  - On Linux machine you have to press "GUI key + Escape" to log out, rather 
    than "GUI key + L" as on Windows. Logout and lock feature should be able to 
    logout of a Linux machine.
  - Somehow signal to the user when entering the master password for the first 
    time.
  - Add the ability to pump a single tab or a single carriage return from the 
    menu.
  - Import KeePass .xml file
  - Import LastPass files
  - Export to KeePass CSV format
  - Export to LastPass format
  - re-enter master password to authorize credentials reset
  - Consolidate code in the import files sections (this code is currently 
	  commented out.
  - A back space should be available during character input via rotary encoder.
  - Implement more error codes
  - Scroll the display horizontally when necessary
  - Make the menus scroll around when the end is reached (?)
  - Add Italian keyboard support: 
    https://github.com/Maiux92/digispark-keyboard-layout-italian/blob/master/scancode-ascii-table.h
  ! Make it work over bluetooth
  ! Make UN_PW_DELAY configurable
  ! Confirm that the lock bits are correctly set.
  ? Add a feature whereby the unit factory resets after two triple clicks, even
    if not yet authenticated. (commented out, caused problems)
  ? Add a feature whereby the unit logs out after two double clicks. (commented
    out, caused problems)
  * Create an excellent case or enclosure.
  * Make the size of the generated password configurable.
  * Implement a password complexity check for generated passwords that matches
    the complexity of passwords generated via PasswordPumpGUI.  It's currently
    possible to generate a password on the device that doesn't pass complexity
    rules.
	* In the customize groups menu, use the current name of the group instead of
	  the group number.
  * Add the ability to fix a corrupt linked list.
  * Add a decoy password that executes a factory reset when the password plus
    the characters "FR" are supplied as the master password.
  * Enable decoy password feature, make it configurable
  * Allow users to name the categories.
  * Dim the display when it's not in use.
  * Always reflect the account that's selected in the PC client on the device.
  * Automatic logout countdown
  * Increase the display width by 1 more (tried and this didn't work)
  * Add salt for credentials, char UUID
  * Add ability to save the old password, especially useful if a generated 
    password is rejected when changing passwords
  * Make saving of previous password manual
  * add salt to the hashed master password.
  * ensure we don't read more bytes than that which we can accommodate in the
    buffer
  * encrypt the user names (need to confirm by examining EEprom)
  * encrypt the account names (need to confirm by examining EEprom)
  * Configure how long until automatic logout
  * Try updating write_eeprom_array() so that it's not writing byte for byte 
    to improve write speed.
  * Replace AES-128 with AES-256
  * Build a Windows client (in python) for editing credentials; 
    add/change/delete
  * Add website to the Python client
  * Add an Import menu
  * Change master password (use both 25LC256 chips for this)
  * Backup to file should backup to a format that can be read in, and should 
    include the groups.
  * Add a menu for selecting the number of failed logins before reset (will this
    make it easier to hack into the device?)
  * Add a setting to indicate how many failed login attempts before factory 
    reset.
  * Remove the EEprom part number selection menu.
  * Document how to burn the firmware outside of the Arduino IDE
  * Set all unused I/O pins as output, not connected to a resistor and best to 
    set to zero logic low
  * Accommodate a larger EEProm chip (512)
  * Import Chrome passwords
  * Import PasswordPump .CSV file
  * Increase the website size to at least 96.
  * Mark favorite credentials, and Find Favorites menu item
  * Add website url to credentials
  * Add a favorites designator to sets of credentials, and a menu item that lets
    you Find Favorites only; it should be the default / top of the Main menu.
  * Flash the RGB when there are 10 seconds remaining until logout
  * Erase the KeePass import file by filling it w/ null terminator and then 
    deleting it.
  * Make style indicator more intelligent e.g. <RETURN> or <TAB>
  * Consider halving the number of possible accounts (from 256 to 128) and 
    doubling the size of the account name, usern ame, and password fields (from
    31 to 63).
  * Turn off the RGB LED, configurable
  * Make brightness of RGB LED configurable (use PWM)
  * Add the ability to send the URL through the keyboard
  * Add a new Settings menu selection
  * Add a missing pull up resistor for I2C to SSD1306 (bread board only)
  * implement with a better font
  * work on the work-flow; which menu items are defaulted after which events.
  * Delete account (account name, user name, password)
  * substitute memcpy with for loops
  * implement a doubly linked list to keep the accounts in order
  * reconsider the organization of the menus
  * ask for confirmation before performing destructive tasks
  * Restore backup (restore from the EEprom backup)
  * implement backup from external EEprom to external EEprom
  * incorporate the use of external EEprom chip to expand available memory
  * make it possible to edit credentials via keyboard
  * Encrypt all passwords (except the master password)
  * finish the video
    https://screencast-o-matic.com/
  * decide if the encrypted password will be saved to EEprom
  * get ScreenCastOMatic to record the video for the project
  * add function(s) to send error output to the display device (e.g. no external
    EEprom.
  * Make it possible to send the account name, where a URL can be entered.
  * eliminate the need for the acctsArray to conserve memory.
  * make room for a next pointer and a previous pointer to maintain a doubly 
    linked list so that we can sort the account names.
  * decide if you should display the passwords.  Possibly make it configurable.
  * mask passwords on input
  * add a feature that dumps all account names, user names and passwords out
    through the keyboard (like to be inserted into an editor as a backup).
  * have the unit factory reset after 10 failed attempts.  Store the failed
    attempts in EEprom.
  * Hash the master password
  * A master key generated from the user password is hashed using SHA-256, which 
    is subsequently used to encrypt the password database with AES-128. 
    Cryptography experts no longer recommend CBC for use in newer designs. It 
    was an important mode in the past but newer designs should be using 
    authenticated encryption with associated data (AEAD) instead.   
  * have the unit automatically logout after a period of inactivity, this will
    require use of the timer.

  Warnings
  ========
  - Avoid using the device with wet hands.
  
  Suggestions
  ===========
  - Best viewed in an editor w/ 160 columns, most comments start at column 81 
  - Please submit defects you find so I can improve the quality of the program
    and learn more about embedded programming.  dan-murphy@comcast.net
  - For anyone unfamiliar w/ Arduino when the device is powered on first setup() 
    runs and then loop() runs, in a loop, in perpetuity.
  - Set tab spacing to 2 space characters in your editor.
	- Uncomment the pre-compiler directive __SAMD21__	if you're using the 
	  Adafruit ItsyBitsy M0, and comment out the pre-compiler directive 
		__SAMD51__.  Uncomment the pre-compiler directive __SAMD51__ if you're
		using the Adafruit ItsyBitsy M4, and comment out the pre-compiler directive
		__SAMD21__.
	- If, after building your PasswordPump, you notice that the rotary encoder is
	  advancing through the alphabet when you turn the encoder counter-clockwise
		then you can reverse this behavior by selecting 'Lefty' in 
    Settings->Encoder Type.  This state survives power cycling but not factory
    reset.
  - If you wish to change the orientation of the display to the rotary encoder,
    (i.e. if you want to operate the encoder with your right hand) navigate to 
    Settings->Orientation.
  - See the Users Guide for more suggestions @ 
    https://github.com/seawarrior181/PasswordPump_II

  Contributors
  ============
  A lot of cargo programming was employed to build this program and Source code
  has been pulled from all over the internet, it would be impossible for me to 
  cite all contributors.

  Copyright
  =========
  - Copyright ©2018, ©2019, ©2020, @2021 Daniel J Murphy <dan-murphy@comcast.net>
  
  License                                                                       
  =======
  Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International
  (CC BY-NC-SA 4.0). https://creativecommons.org/licenses/by-nc-sa/4.0/
  This program and device are distributed in the hope that they will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
  or FITNESS FOR A PARTICULAR PURPOSE.

  You are free to:
    Share — copy and redistribute the material in any medium or format
    Adapt — remix, transform, and build upon the material
    The licensor cannot revoke these freedoms as long as you follow the license
    terms.

  Under the following terms:
  Attribution — You must give appropriate credit, provide a link to the license,
  and indicate if changes were made. You may do so in any reasonable manner, but
  not in any way that suggests the licensor endorses you or your use.

  NonCommercial — You may not use the material for commercial purposes.

  ShareAlike — If you remix, transform, or build upon the material, you must
  distribute your contributions under the same license as the original.

  No additional restrictions — You may not apply legal terms or technological 
  measures that legally restrict others from doing anything the license permits.

  Notices:
  You do not have to comply with the license for elements of the material in the
  public domain or where your use is permitted by an applicable exception or
  limitation.
  
  No warranties are given. The license may not give you all of the permissions
  necessary for your intended use. For example, other rights such as publicity,
  privacy, or moral rights may limit how you use the material.

  Libraries
  =========
	- https://github.com/LennartHennigs/Button2 				For the button on the 
																											rotary encoder 
	-	https://rweather.github.io/arduinolibs/index.html For encrypting 
																											credentials and for 
																											hashing the master 
																											password 
  - https://github.com/greiman/SSD1306Ascii           SSD1306Ascii is an 
                                                      unbuffered character only 
                                                      library for small OLED 
                                                      displays like the Adafruit
                                                      1.3" and 0.96" Monochrome 
                                                      displays.
	-	https://github.com/adafruit/Adafruit_SPIFlash			For FAT filesystems on 
																											SPI flash chips 
	- https://github.com/thijse/Arduino-CmdMessenger 		A messaging library for 
																											the Arduino and 
																											.NET/Mono platforms.
                                                      Somewhat buggy but 
                                                      appreciated nonetheless.

  Library Modifications
  =====================
	-	Changed Adafruit_SSD1306::begin in Adafruit_SSD1306.cpp to suppress display
    of the Adafruit splash screen on the SSD1306 display.
  - It's necessary to make an edit to the Arduino-CmdMessenger library so that 
    it will compile.  On line 492 of 
    ...\arduino\libraries\Arduino-CmdMessenger-master\CmdMessenger.cpp, change 

      return '\0';

        to

      char *str;
      *str = '\0';
      return str;

  Burning The Firmware    
  ====================    
	From the Arduino IDE:
		1) Under Tools do the following:  
			- Set the Board: "Adafruit ItsyBitsy M4 (SAMD51)".  
			- Cache: “Enabled”
			- CPU Speed: “120 MHz (standard)”
			- Optimize: “Small (-Os) (standard)”
			- Max QSPI: “50 MHz (standard)”
			- USB Stack: “Arduino”
			- Debug: “Off”
			- Identify the port associated with your PasswordPump after you've readied
			  it for upload by double clicking on the reset button on the bottom of 
			  the device, and noticing that the RGB LED fades on and off slowly, then 
			  set the port in Tools, (for example, under Windows substitute %% for 
			  your port number; Port: COM%% Adafruit ItsyBitsy M4 (SAMD51)).
			- Programmer: “Arduino as ISP”
		2) Select Tools->Upload
		3) Verify that the upload was successful

	Using BOSSA
		1) cd C:\Users\djmurphy\AppData\Local\Arduino15\packages\arduino\tools\bossac\1.8.0-48-gb176eee
		2) bossac -i -d --port=COM67 -U -i --offset=0x4000 -w -v C:\Users\djmurphy\AppData\Local\Temp\arduino_build_723056\PasswordPumpM4_01.ino.bin -R 
		3) Verify that the upload was successful
    4) Note that the offset is 0x2000 for the ItsyBitsy M0.  Otherwise you risk
       bricking the MCU, in which case you will need to ship the unit back to 
       me for fixing or desolder the display and follow the instructions here: 
       https://learn.adafruit.com/how-to-program-samd-bootloaders

  Drivers
  =======
  - It might be necessary to install the following drivers: 
    https://github.com/adafruit/Adafruit_Windows_Drivers/releases
    https://github.com/adafruit/Adafruit_Windows_Drivers/releases/tag/2.4.0.0
  
  Other Artifacts                                                              
  ===============
  - Project web site:       https://www.5volts.org/
  - Case design files:      https://www.tinkercad.com/things/7qHtCGWOTI5
                            https://www.tinkercad.com/things/3j5hXKeFjPE
  - Source code repository: https://github.com/seawarrior181/PasswordPump_II  

  Bill Of Materials
  =================
  - 1 AdaFruit ItsyBitsy (32-bit ARM®, SAMD51 Cortex®-M4F MCU)
       Data Sheet: http://ww1.microchip.com/downloads/en/DeviceDoc/60001507E.pdf
  - 2 MICROCHIP - 25LC512-I/P - 512K SPI™ Bus Serial EEPROM DIP8, one primary 
       one backup.
    2 IC DIP Sockets, 8 pins each
       Data Sheet: http://ww1.microchip.com/downloads/en/DeviceDoc/20005715A.pdf
  - 1 SSD1306 I2C LED display 128x32 pixels.
       Data Sheet: https://cdn-shop.adafruit.com/datasheets/SSD1306.pdf
                   https://www.vishay.com/docs/37894/oled128o032dlpp3n00000.pdf
  - 1 RGB LED
  - 1 Rotary Encoder
  - 3 220ohm resistors
  - 2 4.7kohm resistors (to hold i2c SDA and SCL lines high)
  - 1 plastic knob for rotary encoder
	- 1 custom PCB or breadboard

  Cost
  ====
  - 1 AdaFruit ItsyBitsy (32-bit ARM®, SAMD51 Cortex®-M4F MCU)        $14.95
  - 2 MICROCHIP - 25LC512-I/P - 512K SPI™ Bus Serial EEPROM DIP8        3.80
  - 1 SSD1306 I2C LED display 128x32 pixels.                            2.23
  - 1 Custom PCB                                                        1.50
  - 1 micro USB to USB cable 100cm                                      0.69
  - 1 Rotary Encoder                                                    0.46
  - 1 plastic knob for rotary encoder                                   0.11
  - 2 IC DIP Sockets, 8 pins each                                       0.10
  - Solder                                                              0.10
  - 1 RGB LED diffused 5mm                                              0.03
  - 3 220ohm resistors                                                  0.01
  - 2 4.7kohm resistors                                                 0.01
                                                                      ------
  - Total Parts                                                       $23.99
                                                                      ======
  + Labor for assembly, packaging & shipping
  
  Connections
  ===========
  - ItsyBitsy M0/M4
    Number  Name              Connect To / Notes
    1       RS                reset button
    2       3V                25LC256 Prim Pin 3 & 25LC256 Secondary Pin 3 
    3       AREF              
    4       VHI               
    5       A0                
    6       A1                
    7       A2                
    8       A3                
    9       A4                220 Ohm resistor->RGB LED Pin 3
    10      A5                
    11      SCK               25LC256 Prim Pin 6 & 25LC256 Secondary Pin 6
    12      MO                25LC256 Prim Pin 5 & 25LC256 Secondary Pin 5
    13      MI                25LC256 Prim Pin 2 & 25LC256 Secondary Pin 2
    14      2                 
    15      En                
    16      swdio             
    17      swclk             
    18      3                 
    19      4                 
    20      RX                
    21      TX                
    22      SDA               SSD1306 SDA, 4.7k Ohm resistor->ItsyBitsy Pin 31
    23      SCL               SSD1306 SCL, 4.7k Ohm resistor->ItsyBitsy Pin 31
    24      5! (VHI Out)      220 Ohm resistor->RGB LED Pin 4
    25      7                 Rotary Encoder Pin 3
    26      9                 Rotary Encoder Pin 1
    27      10                25LC256 Secondary Pin 1 Chip Select
    28      11                25LC256 Primary   Pin 1 Chip Select
    29      12                Rotary Encoder Pin 4
    30      13                220 Ohm resistor->RGB LED Pin 1
    31      USB               SSD1306 VCC
    32      G                 RGB LED Pin 2, 25LC256 Prim & Secon Pin 4, SSD1306
                              Pin 1, Rotary Encoder Pins 2 & 5
    33      BAT               

  - 2 25LC512 (External EEprom)
    Tested Part: MICROCHIP - 25LC512-I/P - 512K SPI™ Bus Serial EEPROM DIP8

    25LC512 Primary
    Number Name                 ConnectTo        Note
    1       CS                  pin 28 ItsyBitsy  Chip Select Input
    2       SO                  pin 13 ItsyBitsy  MISO - Serial Data Output
    3       WP                  pin  2 ItsyBitsy  Write Protect
    4       Vss                 pin  2 ItsyBitsy  Ground
    5       SI                  pin 12 ItsyBitsy  MOSI - Serial Data Input
    6       SCK                 pin 11 ItsyBitsy  SCLK - Serial Clock Input
    7       HOLD                pin  2 ItsyBitsy  Hold Input
    8       Vcc                 pin  2 ItsyBitsy  Supply Voltage 
    
    25LC512 Secondary
    Number Name                 ConnectTo        Note
    1       CS                  pin 27 ItsyBitsy  Chip Select Input
    2       SO                  pin 13 ItsyBitsy  MISO - Serial Data Output
    3       WP                  pin  2 ItsyBitsy  Write Protect
    4       Vss                 pin  2 ItsyBitsy  Ground
    5       SI                  pin 12 ItsyBitsy  MOSI - Serial Data Input
    6       SCK                 pin 11 ItsyBitsy  SCLK - Serial Clock Input
    7       HOLD                pin  2 ItsyBitsy  Hold Input
    8       Vcc                 pin  2 ItsyBitsy  Supply Voltage 

  - Rotary Encoder
      1 2 3
    
      4   5
    1 ItsyBitsy Pin 26
    2 ItsyBitsy Pin 32
    3 ItsyBitsy Pin 25
    4 ItsyBitsy Pin 29
    5 ItsyBitsy Pin 32
    
    
  - SSD13306
    GND VCC SCL SDA
    1   2   3   4
    1 GND     ItsyBitsy Pin 32
    2 VCC     ItsyBitsy Pin 31
    3 SCL     ItsyBitsy Pin 23
    4 SDA     ItsyBitsy Pin 22
    
  - RGB LED
    1 Red     220 Ohm resistor->ItsyBitsy Pin 30
    2 Ground  ItsyBitsy Pin 32
    3 Green   220 Ohm resistor->ItsyBitsy Pin 9
    4 Blue    220 Ohm resistor->ItsyBitsy Pin 24

  RGB Colors and Meanings
  =======================
  Green                     Logged in
  Orange                    Backing up EEprom memory
  Alternating Blue and Red  Initializing EEprom
  Purple                    Sending creds, backing up to EEprom, editing with 
                            computer.
  Red                       Error backing up or initializing EEprom, failed 
                            login attempt(s).
  Yellow                    Error backing up or initializing EEprom
	Alternating								Not logged in
  
  Budgeting Memory
  ================
  Sketch uses ? bytes (15%) of program storage space. Maximum is 507904 
  bytes. 

  Running the PC Client
  =====================
  - c:\python3\python C:\temp\Software\PassPumpGUI_v2_0.py
  
  Menu Navigation
  ===============
  Short click (< 0.5 seconds) brings you right, long click (> 0.5 seconds) 
  brings you left.
  
  Master Password                  
  Find Favorite
  Find All Accounts
    [scroll through accounts list] 
      Send Password <RET>          
      Send User & Pass             
      Send URL
      Send User Name               
      Send Pass (no <RET>)
      Send Account                 
      Edit Credentials             
        Edit Account Name         
        Edit User Name            
        Edit Password             
        Edit URL                  
        Indicate Style      
          usr<RTN>pass<RTN>
          usr<TAB>pass<RTN>
          usr<TAB>pass<TAB,RTN>
        Assign Groups             
          Favorites
          Work
          Personal
          Home
          School
          Financial
          Mail
          Custom
        GeneratePassword          
        Save to Old Password
      Delete Credentials [confirm]
      Send Old Password
  Find By Group
    Favorites
      [same as under Find All Accounts]
    Work
      [same as under Find All Accounts]
    Personal
      [same as under Find All Accounts]
    Home
      [same as under Find All Accounts]
    School
      [same as under Find All Accounts]
    Financial
      [same as under Find All Accounts]
    Mail
      [same as under Find All Accounts]
    Custom
      [same as under Find All Accounts]
  Add Account                      
    Account Name                   
    Edit User Name                 
    Edit Password                  
    Indicate Style                 
      usr<RTN>pass<RTN>
      usr<TAB>pass<RTN>
      usr<TAB>pass<TAB,RTN>
    GeneratePasswrd                
  Logout & Lock                           
  Backup/Restore
    Backup EEprom [confirm]       
    Restore EEprm Backup [confirm]
  Settings
    Show Password ON/OFF            
    Decoy Password ON/OFF
    RGB LED Intensity
      High
      Medium
      Low
      Off
    Timeout Minutes
      30
      60
      90
      120
      240
      Never
      1
    Login Attempts
      3
      5
      10
      25
	  Rename Groups
			Edit Group 1
			Edit Group 2
			Edit Group 3
			Edit Group 4
			Edit Group 5
			Edit Group 6
			Edit Group 7
    Change Master Psswrd
    Keyboard Language
      Czech
      Danish
      Finnish
      French
      German
      Norwegian
      Spanish
      Swedish
      United Kingdom
      United States
    Encoder Type
      Normal
      Lefty
    Font
      Arial14
      Arial_bold_14
      Callibri10
      TimesNewRoman13
      Adafruit5x7
      font5x7
      lcd5x7
      Stang5x7
      System5x7
    Orientation
      Lefty
      Righty
    Keyboard ON/OFF                
  Fix Corruption [confirm]
  Factory Reset [confirm]   

  Error Codes  TODO: add more error codes
  ===========
  000 - SSD1306 allocation failed (only visible via serial)
  001 - Error navigating Off On menu
  002 - Error navigating main menu
  003 - Error navigating edit credentials menu
  004 - Error navigating send credentials menu
  005 - Error navigating settings menu
  006 - Error showing credential values 
  007 - Unrecognized event
  008 - Invalid state when showing Off On menu
  009 - Invalid login attempt maximum
  010 - Out of space
  011 - Corruption found
  012 - Out of space during import
  013 - Failed to open file for import
  014 - Failed to mount FAT file system during import
  015 - Failed to initialize flash during import
  016 - Invalid RGB LED Intensity position
  017 - Invalid maximum login attempt count
  018 - Invalid logout timeout value
  019 - Invalid keyboard, show password or decoy password value
  020 - Account name keeps encrypting to 255 in first char during import
  021 - User name is too long on import
  022 - Password is too long on import
  023 - Web site is too long on import
  024 - Account name is too long on import
  025 - Invalid group specified
  026 - Invalid search group specified
  027 - Invalid group menu item specified
  028 - Invalid state during event singl click
  029 - Invalid state encountered during rotate counter clockwise event
  030 - Invalid state encountered during rotate clockwise event
  031 - Empty credentials found in linked list
  032 - Corrupt linked list
  033 - Corrupt linked list in FindAccountPos.
  034 - Failed to initialize flash during PasswordPump CSV file import
  035 - Group length is greater than one
  036 - Too many fields found in PasswordPump CVS file during import
  037 - Failed to open PasswordPump CVS file for import
  038 - Invalid position in file menu
  039 - Encrypted account name starts with 255, fixing...
  040 - Invalid position when returning to a find by group menu
  041 - Corrupt link list encountered while counting accounts
  042 - Invalid position when returning to settings menu
	043 - Invalid group number when customizing groups
  044 - Invalid category number when customizing groups from PasswordPumpGUI
  045 - Invalid keyboard language specified
  046 - Invalid encoder type specified
  047 - Invalid font specified
  048 - Invalid orientation specified
  049 - Invalid edit menu item when setting help
  050 - Invalid settings menu item when setting help
  051 - Infinite loop when searching for list head
  052 - Original head position not equal to found head position
  053 - Infinite loop when searching for list tail
  054 - Infinite loop when counting accounts
  055 - Invalid style specified
  056 - Invalid login attempt count
  057 - Unknown command from PasswordPumpGUI
  058 - Invalid generated password size
  059 - Invalid inter character pause size

  Finally, the Program 
  ==============================================================================
//- Includes/Defines                                                             */
//#define __SAMD51__                 			   		  												      // Turn this on for Adafruit ItsyBitsy M4. _SAMD21_ and _SAMD51_ are mutually exclusive.
#define __SAMD21__                   	 						  	  												// Turn this on for Adafruit ItsyBitsy M0. _SAMD21_ and _SAMD51_ are mutually exclusive.
#define ENCODER_NORMAL            0                                             // don't change this.
#define ENCODER_LEFTY             1                                             // don't change this.
#define ENCODER_DEFAULT           ENCODER_LEFTY                                 // set the encoder type default based on how the encoder is behaving

#ifdef __SAMD51__
  #define F_CPU                   120000000UL                                   // micro-controller clock speed, max clock speed of ItsyBitsy M4 is 120MHz (well, it can be over clocked...)
#endif
#ifdef __SAMD21__
  #define F_CPU                   48000000UL                                    // micro-controller clock speed, max clock speed of ItsyBitsy M0 is 48MHz 
#endif
//#define SLOW_SPI
#define DEBUG_ENABLED             0
#define TEST_EEPROM               0

#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <Wire.h>
#include <Button2.h>                                                            // https://github.com/LennartHennigs/Button2 for the button on the rotary encoder 
#include "Keyboard.h"                                                           // 
#include "CzechKeyboard.h"                                                      //      
#include "DanishKeyboard.h"                                                     // 
#include "FinnishKeyboard.h"                                                    // 
#include "FrenchKeyboard.h"                                                     // 
#include "GermanKeyboard.h"                                                     // 
#include "NorwegianKeyboard.h"                                                  // 
#include "SpanishKeyboard.h"                                                    // 
#include "SwedishKeyboard.h"                                                    // 
#include "UKKeyboard.h"                                                         // 
#include "USKeyboard.h"                                                         // The default.
#include <SHA256.h>                                                             // https://rweather.github.io/arduinolibs/index.html for hashing the master password 
#include <AES.h>                                                                // https://rweather.github.io/arduinolibs/index.html for encrypting credentials 
#include <SSD1306Ascii.h>                                                       // https://github.com/greiman/SSD1306Ascii
#include <SSD1306AsciiWire.h>                                                   // https://github.com/greiman/SSD1306Ascii
#include <Adafruit_SPIFlash.h>                                                  // https://github.com/adafruit/Adafruit_SPIFlash
#include <CmdMessenger.h>																												// https://github.com/thijse/Arduino-CmdMessenger 

//#include <stdio.h>                                                            // needed for CSV file program
//#include <locale.h>
#include <string.h>                                                             //  "     "       "       "
#include <stdlib.h>
#include <assert.h>

//- Macros
#define _BV(bit)                  (1 << (bit))
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define getLoginFailures          read_eeprom_byte(GET_ADDR_LOGIN_FAILURES)     // The number of login failures that have occurred since the last successful login.
#define getResetFlag              read_eeprom_byte(GET_ADDR_RESET_FLAG)
#define getShowPasswordsFlag      read_eeprom_byte(GET_ADDR_SHOW_PW)
#define getKeyboardFlag           read_eeprom_byte(GET_ADDR_KEYBOARD_FLAG)
#define getRGBLEDInt              read_eeprom_byte(GET_ADDR_RGB_LED_INT)
#define getLogoutTimeout          read_eeprom_byte(GET_ADDR_LOGOUT_TIMEOUT)
#define getKeyboardType           read_eeprom_byte(GET_ADDR_KEYBOARD_TYPE)
#define getEncoderType            read_eeprom_byte(GET_ADDR_ENCODER_TYPE)
#define getFont                   read_eeprom_byte(GET_ADDR_FONT)
#define getOrientation            read_eeprom_byte(GET_ADDR_ORIENTATION)
#define getLoginAttempts          read_eeprom_byte(GET_ADDR_LOGIN_ATTEM_NUM)    // The number of login attempts before we factory reset
#define getDecoyPWFlag            read_eeprom_byte(GET_ADDR_DECOY_PW)
#define getGroupStatus						read_eeprom_byte(GET_ADDR_CATEGORY_1)
#define getGenPasswordSize        read_eeprom_byte(GET_ADDR_GEN_PW_SIZE)
#define getInterCharPause         read_eeprom_byte(GET_ADDR_INTER_CHAR_PAUSE)

//#if defined(__SAMD51__) && defined(SERIAL_PORT_USBVIRTUAL)                    // Required for Serial on Zero based boards
//  #define Serial SERIAL_PORT_USBVIRTUAL
//#endif

//#define KEEPASS_CSV             "KPEXPORT.CSV"                                // this functionality was removed.
//#define KEEPASS_COLUMNS         5                                             // this functionality was removed.

//#define PP_CSV                  "PPEXPORT.CSV"                                // this functionality was removed.
//#define PP_COLUMNS              5                                             // this functionality was removed.

//#define CP_CSV                  "CPEXPORT.CSV"                                // this functionality was removed.
//#define CP_COLUMNS              4                                             // this functionality was removed.

//- Defines

#define BAUD_RATE                 115200                                        //  Baud rate for the Serial monitor, best for 16MHz (was 38400)

#define BUTTON_PIN                12                                            //   "                              

#define RED_PIN                   5                                             // Pin locations for the RGB LED, must be PWM capable 
#define BLUE_PIN                  13                                            //   "
#ifdef __SAMD51__
#define GREEN_PIN                 A4                                            //   "
#define SET_OUT_PIN								A2
#endif
#ifdef __SAMD21__
#define GREEN_PIN                 A2                                            //   "
#define SET_OUT_PIN								A4
#endif

#define RANDOM_PIN                A0                                            // this pin must float; it's used to generate the seed for the random number generator
#define RANDOM_PIN2								A1																						// this pin must float; it's used to generate the seed for the random number generator

#ifdef __SAMD21__
  #define UNUSED_PIN2             A4
#endif
#ifdef __SAMD51__
  #define UNUSED_PIN2             A2
#endif
#define UNUSED_PIN3               A3
#define UNUSED_PIN4               A5
#define UNUSED_PIN5               2
#define UNUSED_PIN6               3
#define UNUSED_PIN7               4
#define UNUSED_PIN8               1                                             // TX
#define UNUSED_PIN9               0                                             // RX

#define NO_LED_LIB_CHAR_WIDTH_PIX 6                                             // when entering chars via rotary encoder, the amount to advance the cursor for each character already entered
#define FIXED_CHAR_SPACING        10                                            // when entering chars via rotary encoder, the fixed amount to advance the cursor

#define ONE_SECOND                1000UL                                        // in microseconds

#define INITIAL_MEMORY_STATE_CHAR -1                                            // 11111111 binary twos complement, -1 decimal, 0xFF hex.  When factory fresh all bytes in EEprom memory = 0xFF.  char is signed by default. byte is unsigned.
#define INITIAL_MEMORY_STATE_BYTE 0xFF                                          // 11111111 binary twos complement, -1 decimal, 0xFF hex.  When factory fresh all bytes in EEprom memory = 0xFF. 255 unsigned decimal.
#define NULL_TERM                 0x00                                          // The null terminator, NUL, ASCII 0, or '\0'                 
#define DEFAULT_STYLE_CHAR        0x31                                          // '1'

#define SPI_SS_PRIMARY            11                                            // chip select primary (copy source)  (SPI)
#define SPI_SS_SECONDARY          10                                            // chip select secondary (copy target)  (SPI)
#define SPI_MOSI                  MOSI                                          // mosi (SPI)
#define SPI_MISO                  MISO                                          // miso (SPI)
#define SPI_SCK                   SCK                                           // clock (SPI)
#define SPI_SPEED                 5000000UL                                     // 5MHz (max is 5MHz@3.3v)
#define SPI_MODE                  SPI_MODE3                                     // SPI_MODE3 = Clock Polarity=1, Clock Phase=1, Output Edge=falling, Data Capture=rising
                                                                                // SPI_MODE1,2 & 3 @100000hz not tried
#define SLAVE_PRIMARY_SELECT      digitalWrite(SPI_SS_PRIMARY, LOW);            // write the slave select pin low
#define SLAVE_PRIMARY_DESELECT    digitalWrite(SPI_SS_PRIMARY, HIGH);           // write the slave select pin high
#define SLAVE_SECONDARY_SELECT    digitalWrite(SPI_SS_SECONDARY, LOW);          // write the slave select pin low
#define SLAVE_SECONDARY_DESELECT  digitalWrite(SPI_SS_SECONDARY, HIGH);         // write the slave select pin high

// SPI Instruction Set -- from data sheet

#define EEPROM_READ               0b00000011                                    // read memory
#define EEPROM_WRITE              0b00000010                                    // write to memory
#define EEPROM_WREN               0b00000110                                    // write enable
#define EEPROM_RDSR               0b00000101                                    // read status register
                                                                                // EEPROM Status Register Bits -- from data sheet
                                                                                // Use these to parse status register
#define EEPROM_WRITE_IN_PROGRESS  0
#define EEPROM_WRITE_ENABLE_LATCH 1
#define EEPROM_BLOCK_PROTECT_0    2
#define EEPROM_BLOCK_PROTECT_1    3

#define RGB_LED_HIGH              254                                           // 255 = INITIAL_MEMORY_STATE_BYTE, so making this 254.
#define RGB_LED_MEDIUM            32                                            // 128 was too bright
#define RGB_LED_LOW               8                                             // 64 was too bright
#define RGB_LED_OFF               0
#define RGB_LED_DEFAULT           RGB_LED_MEDIUM

#define ATTEMPTS_3                3 
#define ATTEMPTS_5                5
#define ATTEMPTS_10               10
#define ATTEMPTS_25               25
#define ATTEMPTS_DEFAULT          ATTEMPTS_10

#define MAX_ITERATION_COUNT       104857

#define LOGOUT_WARNING            25000                                         // flash red/blue LED for 25 seconds before logout

//- Memory Layout

#define MAX_AVAIL_ADDR_25LC256    0x7FFF                                        // 32767 max address for 25LC256 (start at 0)
#define MAX_AVAIL_ADDR_25LC512    0xFFFF                                        // 65535 max address for 25LC512  
#define MAX_AVAIL_ADDR_25LC1024   0x1FFFF                                       // max address for 25LC1024
#define MIN_AVAIL_ADDR            0x0000                                        // 0 assuming we start at the very beginning of EEprom
#define MAX_AVAIL_ADDR            MAX_AVAIL_ADDR_25LC512                        // 32,767. 25LC256 = 256kbits capacity.
#define MEMORY_INITIALIZED_FLAG   0x0001                                        // signals if memory has been initialized correctly
#define EEPROM_BPP_25LC256        0x0040                                        // 64. can't exceed 255 (real page size is 64 for 25LC256)
#define EEPROM_BPP_25LC512        0x0080                                        // 128. can't exceed 255 (real page size is 128 for 25LC512)
#define EEPROM_BPP_25LC1024       0x0100                                        // 256
#define EEPROM_BYTES_PER_PAGE     EEPROM_BPP_25LC512                            // 
#define CREDS_ACCOM_25LC256       0x007E                                        // 126 (((0x7FFF + 1)/256)) - 1)  | (((MAX_AVAIL_ADDR_25LC256 + 1)/CREDS_TOT_SIZE)) - 2 for settings)
#define CREDS_ACCOM_25LC512       0x00FE                                        // 254 (((0xFFFF + 1)/256)) - 1)  | (((MAX_AVAIL_ADDR_25LC512 + 1)/CREDS_TOT_SIZE)) - 2 for settings)
#define CREDS_ACCOM_25LC1024      0x01FF                                        // 511
#define CREDS_ACCOMIDATED         (CREDS_ACCOM_25LC512 - 0x05)                  // -5 sets of creds for PyCmdMessenger defects = 249
#define DISPLAY_BUFFER_SIZE       21                                            // 0x0015, 21; room for 20 chars and the null terminator

#define WEBSITE_SIZE              0x0060                                        // 96 bytes
#define ACCOUNT_SIZE              0x0020                                        // 32 bytes
#define USERNAME_SIZE             0x0020                                        // 32 bytes
#define PASSWORD_SIZE             0x0020                                        // 32 bytes
#define OLD_PASSWORD_SIZE         0x0020                                        // 32 bytes (only used to calculate addresses, elsewhere we use PASSWORD_SIZE.
#define SALT_SIZE                 0x0010                                        // 16 bytes
#define STYLE_SIZE                0x0002                                        // 2 bytes, we are storing the null terminator
#define PREV_POS_SIZE             0x0001                                        // 1 byte, data type byte, no null terminator
#define NEXT_POS_SIZE             0x0001                                        // 1 byte, data type byte, no null terminator
#define GROUP_SIZE                0x0001                                        // 1 byte, designates the group to which the credential belongs
//------------------------------------------------------------------------------
#define CREDS_TOT_SIZE            0x0100                                        // 256 bytes (213 total, rounded up to 256. leaving an extra 43 bytes on the end so we're on the page boundary)
//==============================================================================// 32768 - 

                                                                                // Stored in first part of EEprom memory
#define GET_ADDR_WEBSITE(pos)     (MIN_AVAIL_ADDR + (pos * CREDS_TOT_SIZE))
#define GET_ADDR_ACCT(pos)        (MIN_AVAIL_ADDR + WEBSITE_SIZE + (pos * CREDS_TOT_SIZE))
#define GET_ADDR_USER(pos)        (MIN_AVAIL_ADDR + WEBSITE_SIZE + ACCOUNT_SIZE + (pos * CREDS_TOT_SIZE))
#define GET_ADDR_PASS(pos)        (MIN_AVAIL_ADDR + WEBSITE_SIZE + ACCOUNT_SIZE + USERNAME_SIZE + (pos * CREDS_TOT_SIZE))
#define GET_ADDR_OLD_PASS(pos)    (MIN_AVAIL_ADDR + WEBSITE_SIZE + ACCOUNT_SIZE + USERNAME_SIZE + PASSWORD_SIZE + (pos * CREDS_TOT_SIZE))
#define GET_ADDR_SALT(pos)        (MIN_AVAIL_ADDR + WEBSITE_SIZE + ACCOUNT_SIZE + USERNAME_SIZE + PASSWORD_SIZE + OLD_PASSWORD_SIZE + (pos * CREDS_TOT_SIZE))
#define GET_ADDR_STYLE(pos)       (MIN_AVAIL_ADDR + WEBSITE_SIZE + ACCOUNT_SIZE + USERNAME_SIZE + PASSWORD_SIZE + OLD_PASSWORD_SIZE + SALT_SIZE + (pos * CREDS_TOT_SIZE))
#define GET_ADDR_PREV_POS(pos)    (MIN_AVAIL_ADDR + WEBSITE_SIZE + ACCOUNT_SIZE + USERNAME_SIZE + PASSWORD_SIZE + OLD_PASSWORD_SIZE + SALT_SIZE + STYLE_SIZE + (pos * CREDS_TOT_SIZE))
#define GET_ADDR_NEXT_POS(pos)    (MIN_AVAIL_ADDR + WEBSITE_SIZE + ACCOUNT_SIZE + USERNAME_SIZE + PASSWORD_SIZE + OLD_PASSWORD_SIZE + SALT_SIZE + STYLE_SIZE + PREV_POS_SIZE + (pos * CREDS_TOT_SIZE)) 
#define GET_ADDR_GROUP(pos)       (MIN_AVAIL_ADDR + WEBSITE_SIZE + ACCOUNT_SIZE + USERNAME_SIZE + PASSWORD_SIZE + OLD_PASSWORD_SIZE + SALT_SIZE + STYLE_SIZE + PREV_POS_SIZE + NEXT_POS_SIZE + (pos * CREDS_TOT_SIZE)) // 100 @ pos==0

#define MASTER_PASSWORD_SIZE      0x0010                                        // 16 bytes. aes256 keysize = 32 bytes.  aes128 keysize = 16 bytes, aes256 blocksize = 16!, only the first 15 chars are part of the password, the rest are ignored.
#define KEY_SIZE                  (MASTER_PASSWORD_SIZE + SALT_SIZE)            // 32 bytes, key size for AES-256 = 32 bytes
                                                                                // Stored in SETTINGS section of memory (last 256 bytes of EEprom)
#define RESET_FLAG_SIZE           0x0001                                        // 1 byte
#define LOGIN_FAILURES_SIZE       0x0001                                        // 1 byte
#define SHOW_PASSWORD_FLAG_SIZE   0x0001                                        // 1 byte
#define KEYBOARD_FLAG_SIZE        0x0001                                        // 1 byte
#define LIST_HEAD_SIZE            0x0001                                        // 1 byte Needs to be two bytes for 25LC512 and 25LC1024
#define MASTER_SALT_SIZE          0x0010                                        // 16 bytes
#define HASHED_MASTER_PASSWORD_SZ (MASTER_PASSWORD_SIZE + MASTER_SALT_SIZE)     // 32 the size of the hashed master password (store MASTER_SALT+MASTER_PASSWORD hashed)
#define RGB_LED_INTENSITY_SIZE    0x0001                                        // 1 byte
#define LOGOUT_TIMEOUT_SIZE       0x0001                                        // 1 byte
#define LOGIN_ATTEMPTS_NUM_SIZE   0x0001                                        // 1 byte
#define DECOY_PW_SIZE             0x0010                                        // 1 byte
#define CATEGORY_SIZE             0x000A																				// 10 bytes (there are 7 of these)
#define KEYBOARD_TYPE_SIZE        0x0001                                        // 1 byte
#define ENCODER_TYPE_SIZE         0X0001                                        // 1 byte
#define FONT_SIZE                 0x0001                                        // 1 byte, designates the desired font
#define ORIENTATION_SIZE          0x0001                                        // 1 byte, screen orientation, lefty (0) or righty (1)
#define GENERATED_PASSWORD_SIZE   0x0001                                        // 1 byte
#define INTER_CHAR_PAUSE_SIZE     0x0001                                        // 1 byte
//------------------------------------------------------------------------------
#define SETTINGS_TOTAL_SIZE       0x0100                                        // 256 (101 total, rounding up to 256)
//==============================================================================// 65536 - 256 = 32512/256 = 255 CREDS_ACCOMIDATED

#define GET_ADDR_SETTINGS         (MAX_AVAIL_ADDR - SETTINGS_TOTAL_SIZE)        // use the last page for storing the settings.
#define GET_ADDR_RESET_FLAG       (GET_ADDR_SETTINGS)                           // address of the reset flag; when not set to 0x01 indicates that memory hasn't been initialized; 32,767
#define GET_ADDR_LOGIN_FAILURES   (GET_ADDR_SETTINGS + RESET_FLAG_SIZE)         //
#define GET_ADDR_SHOW_PW          (GET_ADDR_SETTINGS + RESET_FLAG_SIZE + LOGIN_FAILURES_SIZE)     //
#define GET_ADDR_KEYBOARD_FLAG    (GET_ADDR_SETTINGS + RESET_FLAG_SIZE + LOGIN_FAILURES_SIZE + SHOW_PASSWORD_FLAG_SIZE) //
#define GET_ADDR_LIST_HEAD        (GET_ADDR_SETTINGS + RESET_FLAG_SIZE + LOGIN_FAILURES_SIZE + SHOW_PASSWORD_FLAG_SIZE + KEYBOARD_FLAG_SIZE) //  points to the head of the linked list
#define GET_ADDR_MASTER_SALT      (GET_ADDR_SETTINGS + RESET_FLAG_SIZE + LOGIN_FAILURES_SIZE + SHOW_PASSWORD_FLAG_SIZE + KEYBOARD_FLAG_SIZE + LIST_HEAD_SIZE) // location of the salt
#define GET_ADDR_MASTER_HASH      (GET_ADDR_SETTINGS + RESET_FLAG_SIZE + LOGIN_FAILURES_SIZE + SHOW_PASSWORD_FLAG_SIZE + KEYBOARD_FLAG_SIZE + LIST_HEAD_SIZE + MASTER_SALT_SIZE) // store hashed master password
#define GET_ADDR_RGB_LED_INT      (GET_ADDR_SETTINGS + RESET_FLAG_SIZE + LOGIN_FAILURES_SIZE + SHOW_PASSWORD_FLAG_SIZE + KEYBOARD_FLAG_SIZE + LIST_HEAD_SIZE + MASTER_SALT_SIZE + HASHED_MASTER_PASSWORD_SZ) // store setting for RGB LED intensity
#define GET_ADDR_LOGOUT_TIMEOUT   (GET_ADDR_SETTINGS + RESET_FLAG_SIZE + LOGIN_FAILURES_SIZE + SHOW_PASSWORD_FLAG_SIZE + KEYBOARD_FLAG_SIZE + LIST_HEAD_SIZE + MASTER_SALT_SIZE + HASHED_MASTER_PASSWORD_SZ + RGB_LED_INTENSITY_SIZE) // store the setting for the automatic logout timeout
#define GET_ADDR_LOGIN_ATTEM_NUM  (GET_ADDR_SETTINGS + RESET_FLAG_SIZE + LOGIN_FAILURES_SIZE + SHOW_PASSWORD_FLAG_SIZE + KEYBOARD_FLAG_SIZE + LIST_HEAD_SIZE + MASTER_SALT_SIZE + HASHED_MASTER_PASSWORD_SZ + RGB_LED_INTENSITY_SIZE + LOGOUT_TIMEOUT_SIZE) // store the setting for the EEProm part number
#define GET_ADDR_DECOY_PW         (GET_ADDR_SETTINGS + RESET_FLAG_SIZE + LOGIN_FAILURES_SIZE + SHOW_PASSWORD_FLAG_SIZE + KEYBOARD_FLAG_SIZE + LIST_HEAD_SIZE + MASTER_SALT_SIZE + HASHED_MASTER_PASSWORD_SZ + RGB_LED_INTENSITY_SIZE + LOGOUT_TIMEOUT_SIZE + LOGIN_ATTEMPTS_NUM_SIZE) // store the setting for the decoy password setting
#define GET_ADDR_KEYBOARD_TYPE    (GET_ADDR_SETTINGS + RESET_FLAG_SIZE + LOGIN_FAILURES_SIZE + SHOW_PASSWORD_FLAG_SIZE + KEYBOARD_FLAG_SIZE + LIST_HEAD_SIZE + MASTER_SALT_SIZE + HASHED_MASTER_PASSWORD_SZ + RGB_LED_INTENSITY_SIZE + LOGOUT_TIMEOUT_SIZE + LOGIN_ATTEMPTS_NUM_SIZE + DECOY_PW_SIZE) // store the setting for the keyboard type setting
#define GET_ADDR_ENCODER_TYPE     (GET_ADDR_SETTINGS + RESET_FLAG_SIZE + LOGIN_FAILURES_SIZE + SHOW_PASSWORD_FLAG_SIZE + KEYBOARD_FLAG_SIZE + LIST_HEAD_SIZE + MASTER_SALT_SIZE + HASHED_MASTER_PASSWORD_SZ + RGB_LED_INTENSITY_SIZE + LOGOUT_TIMEOUT_SIZE + LOGIN_ATTEMPTS_NUM_SIZE + DECOY_PW_SIZE + KEYBOARD_TYPE_SIZE) // store the setting for the keyboard type setting
#define GET_ADDR_FONT             (GET_ADDR_SETTINGS + RESET_FLAG_SIZE + LOGIN_FAILURES_SIZE + SHOW_PASSWORD_FLAG_SIZE + KEYBOARD_FLAG_SIZE + LIST_HEAD_SIZE + MASTER_SALT_SIZE + HASHED_MASTER_PASSWORD_SZ + RGB_LED_INTENSITY_SIZE + LOGOUT_TIMEOUT_SIZE + LOGIN_ATTEMPTS_NUM_SIZE + DECOY_PW_SIZE + KEYBOARD_TYPE_SIZE + ENCODER_TYPE_SIZE) // store the setting for the font setting
#define GET_ADDR_ORIENTATION      (GET_ADDR_SETTINGS + RESET_FLAG_SIZE + LOGIN_FAILURES_SIZE + SHOW_PASSWORD_FLAG_SIZE + KEYBOARD_FLAG_SIZE + LIST_HEAD_SIZE + MASTER_SALT_SIZE + HASHED_MASTER_PASSWORD_SZ + RGB_LED_INTENSITY_SIZE + LOGOUT_TIMEOUT_SIZE + LOGIN_ATTEMPTS_NUM_SIZE + DECOY_PW_SIZE + KEYBOARD_TYPE_SIZE + ENCODER_TYPE_SIZE + FONT_SIZE) // store the setting for the orientation setting
#define GET_ADDR_GEN_PW_SIZE      (GET_ADDR_SETTINGS + RESET_FLAG_SIZE + LOGIN_FAILURES_SIZE + SHOW_PASSWORD_FLAG_SIZE + KEYBOARD_FLAG_SIZE + LIST_HEAD_SIZE + MASTER_SALT_SIZE + HASHED_MASTER_PASSWORD_SZ + RGB_LED_INTENSITY_SIZE + LOGOUT_TIMEOUT_SIZE + LOGIN_ATTEMPTS_NUM_SIZE + DECOY_PW_SIZE + KEYBOARD_TYPE_SIZE + ENCODER_TYPE_SIZE + FONT_SIZE + ORIENTATION_SIZE) // store the setting for default password size
#define GET_ADDR_INTER_CHAR_PAUSE (GET_ADDR_SETTINGS + RESET_FLAG_SIZE + LOGIN_FAILURES_SIZE + SHOW_PASSWORD_FLAG_SIZE + KEYBOARD_FLAG_SIZE + LIST_HEAD_SIZE + MASTER_SALT_SIZE + HASHED_MASTER_PASSWORD_SZ + RGB_LED_INTENSITY_SIZE + LOGOUT_TIMEOUT_SIZE + LOGIN_ATTEMPTS_NUM_SIZE + DECOY_PW_SIZE + KEYBOARD_TYPE_SIZE + ENCODER_TYPE_SIZE + FONT_SIZE + ORIENTATION_SIZE + GENERATED_PASSWORD_SIZE) // store the setting inter character pause size
#define GET_ADDR_CATEGORY_1				(MAX_AVAIL_ADDR - (SETTINGS_TOTAL_SIZE * 2)) + (CATEGORY_SIZE * 1) // place the categories on the second to last page on EEprom
#define GET_ADDR_CATEGORY_2				(MAX_AVAIL_ADDR - (SETTINGS_TOTAL_SIZE * 2)) + (CATEGORY_SIZE * 2)
#define GET_ADDR_CATEGORY_3				(MAX_AVAIL_ADDR - (SETTINGS_TOTAL_SIZE * 2)) + (CATEGORY_SIZE * 3)
#define GET_ADDR_CATEGORY_4				(MAX_AVAIL_ADDR - (SETTINGS_TOTAL_SIZE * 2)) + (CATEGORY_SIZE * 4)
#define GET_ADDR_CATEGORY_5				(MAX_AVAIL_ADDR - (SETTINGS_TOTAL_SIZE * 2)) + (CATEGORY_SIZE * 5)
#define GET_ADDR_CATEGORY_6				(MAX_AVAIL_ADDR - (SETTINGS_TOTAL_SIZE * 2)) + (CATEGORY_SIZE * 6)
#define GET_ADDR_CATEGORY_7				(MAX_AVAIL_ADDR - (SETTINGS_TOTAL_SIZE * 2)) + (CATEGORY_SIZE * 7)

//- Events
                                                                                // Assumption here is that using #define instead of enum will save memory
#define EVENT_NONE                0                                             // used to switch of the previous event to avoid infinite looping
#define EVENT_SINGLE_CLICK        1                                             // a single click on the rotary encoder
#define EVENT_LONG_CLICK          4                                             // holding the button on the rotary encoder down for more than 1 second(?) (changed from default directly in the library)
#define EVENT_ROTATE_CW           7                                             // turning the rotary encoder clockwise
#define EVENT_ROTATE_CC           8                                             // turning the rotary encoder counter clockwise.
#define EVENT_SHOW_MAIN_MENU      9                                             // to show the main menu
#define EVENT_SHOW_EDIT_MENU      11                                            // to show the menu used for editing account name, user name and password (creds)
#define EVENT_RESET               12                                            // Factory Reset event
#define EVENT_LOGOUT              13                                            // logging out of the device
#define EVENT_BACKUP              14                                            // copying the content of the primary external EEprom to the backup EEprom
#define EVENT_RESTORE             15                                            // restore from the backup EEprom to the primary EEprom
//#define EVENT_BACKUP_TO_FILE    16                                            // send all credentials out through the keyboard for capture in a text editor
#define EVENT_FIX_CORRUPTION      17                                            // fix a corrupt linked list
#define EVENT_DELETE_ACCT         18                                            // delete an account
//#define EVENT_IMPORT_KEEPASS_CSV19                                            // import a csv KeePass file
#define EVENT_SHOW_SETTINGS_MENU  20                                            // to show the settings menu
#define EVENT_SHOW_LG_ATTEM_MENU  21                                            // to show the set login attempts menu
#define EVENT_SHOW_RGB_INT_MENU   22                                            // to show the set RGB LED intensity menu
#define EVENT_SHOW_LOG_TIME_MENU  23                                            // to show the set automatic logout time menu
#define EVENT_SHOW_OFF_ON_MENU    24                                            // to show the off/on menu
#define EVENT_SHOW_FIND_BY_GROUP  25
#define EVENT_CHANGE_MASTER       26
//#define EVENT_IMPORT_PP_CSV     27                                            // import a csv PasswordPump file
#define EVENT_SHOW_FILE_MENU      28
//#define EVENT_IMPORT_CP_CSV     29
#define EVENT_SEARCH_FAVORITES    30
#define EVENT_SHOW_FAVORITES_MENU 31
#define EVENT_SHOW_GROUP_DEF_MENU 32
#define EVENT_SHOW_KEYBOARD_MENU  33
#define EVENT_SHOW_ENCODER_MENU   34
#define EVENT_SHOW_FONT_MENU      35
#define EVENT_SHOW_ORIENT_MENU    36
#define EVENT_SHOW_GEN_PW_SZ_MENU 37
#define EVENT_SHOW_INT_CHAR_MENU  38
#define EVENT_SUSPEND             99                                            // event to set when you want to suspend processing, like after calling factory reset.
                                                                                // Not using an enum here to save memory.  
//- States                                                                      

#define STATE_ENTER_MASTER        1                                             // entering the master password
#define STATE_SHOW_MAIN_MENU      2                                             // showing the main menu                              
#define STATE_FIND_ACCOUNT        3                                             // searching for an account                           
#define STATE_EDIT_STYLE          4                                             // editing the style for sending user name and password
//#define STATE_EDIT_GROUPS       5                                             // assigning groups to credentials
#define STATE_EDIT_USERNAME       6                                             // entering the user name  
#define STATE_EDIT_PASSWORD       7                                             // entering the password                              
#define STATE_EDIT_WEBSITE        8
#define STATE_EDIT_CREDS_MENU     9                                             // showing the edit menu                              
#define STATE_EDIT_ACCOUNT        10                                            // entering the account name; if you change this also change it in PassPumpGUI.py                          
#define STATE_SEND_CREDS_MENU     11                                            // showing the menu that sends credentials via keyboard     
#define STATE_CONFIRM_BACK_EEPROM 12                                            // confirming an action                               
#define STATE_CONFIRM_RESTORE     13                                            // confirming restore from backup EEprom              
#define STATE_CONFIRM_FIX_CORRUPT 14                                            // confirming fix corruption function                 
#define STATE_CONFIRM_DEL_ACCT    15                                            // confirming account/credentials delete              
#define STATE_CONFIRM_RESET       16                                            // confirming factory reset                           
#define STATE_CONFIRM_IMP_KP_CSV  17                                            // confirming import KeePass csv file
#define STATE_MENU_SETTINGS       18                                            // in the settings menu
#define STATE_MENU_LOGIN_ATTEM    19                                            // setting the login attempts before factory reset menu
#define STATE_MENU_RGB_INTENSITY  20                                            // setting the RGB LED intensity menu
#define STATE_MENU_LOGOUT_TIMEOUT 21                                            // setting the logout timeout value menu
#define STATE_MENU_OFF_ON         22                                            // setting Off or On
#define STATE_MENU_GROUPS         23
#define STATE_KEY_ON_OFF_MENU     24
#define STATE_SHOW_PW_ON_OFF_MENU 25
#define STATE_DECOY_ON_OFF_MENU   26
#define STATE_SEARCH_FAVORITES    27
#define STATE_SEARCH_WORK         28
#define STATE_SEARCH_PERSONAL     29
#define STATE_SEARCH_HOME         30
#define STATE_SEARCH_SCHOOL       31
#define STATE_SEARCH_FINANCIAL    32
#define STATE_SEARCH_MAIL         33
#define STATE_SEARCH_CUSTOM       34
#define STATE_MENU_FIND_BY_GROUP  35                                            //
#define STATE_CHANGE_MASTER       36
#define STATE_CONFIRM_IMP_PP_CSV  37                                            // confirming import KeePass csv file
#define STATE_MENU_FILE           38
#define STATE_CONFIRM_IMP_CP_CSV  39
#define STATE_FEED_SERIAL_DATA    40
#define STATE_MENU_DEFINE_GROUPS	41
#define STATE_EDIT_GROUP_1				42
#define STATE_EDIT_GROUP_2				43
#define STATE_EDIT_GROUP_3				44
#define STATE_EDIT_GROUP_4				45
#define STATE_EDIT_GROUP_5				46
#define STATE_EDIT_GROUP_6				47
#define STATE_EDIT_GROUP_7				48
#define STATE_MENU_KEYBOARD       49
#define STATE_MENU_ENCODER        50
#define STATE_MENU_FONT           51
#define STATE_MENU_ORIENT         52
#define STATE_MENU_SHOW_GEN_PW_SZ 53
#define STATE_MENU_INT_CHAR_PAUSE 54

//- I2C Address

#define SSD1306_I2C_ADDR          0x3C                                          // Slave 128x32 OLED I2C address

#define LONG_CLICK_LENGTH         500                                           // milliseconds to hold down the rotary encoder button to trigger EVENT_LONG_CLICK
#define UN_PW_DELAY               1000UL                                        // time in milliseconds to wait after sending user name before sending password
#define PW_RTN_DELAY              25UL                                          // time in milliseconds to wait after sending password before sending return
#define SHA_ITERATIONS            1                                             // number of times to hash the master password (won't work w/ more than 1 iteration)
#define KHZ_4000                  400000UL                                      // Speed (in Hz) for Wire transmissions in SSD1306 library calls.
#define KHZ_100                   10000UL                                       // Speed (in Hz) for Wire transmissions following SSD1306 library calls.

//- Menus (globals)

#define KBD_MENU_O_POS            10                                            // where to append "FF" or "N" on the "Keyboard O" menu item in settings
#define SH_PW_MENU_O_POS          15                                            // where to append "FF" or "N" on the  "Show Password O" menu item in settings
#define SH_DC_MENU_O_POS          16                                            // where to append "FF" or "N" on the "Decoy Password O" menu item in settings
#define MENU_SIZE                 14                                            // selections in the menu

#define MAIN_MENU_NUMBER          0
#define MAIN_MENU_ELEMENTS        11                                            // number of selections in the main menu

char * mainMenu[] =               {              
                                                 "Master Password",             // menu picks appear only on the top line
                                                 "Find Favorites",              // find favorite credentials
                                                 "Find All Accounts",           // after an account is found send user sendMenu 
                                                 "Find by Group",               // search accounts by a particular group
                                                 "Edit with Computer",          // edit credentials with the python UI
                                                 "Add Account",
                                                 "Logout & Lock",               // locks the user out until master password is re-entered
                                                 "Backup & Restore",            // Backup, Restore a backup 
                                                 "Settings",                    // navigate to the settings menu
                                                 "Fix Corruption",              // fix any corruption in the linked list
                                                 "Factory Reset"              };// factory reset; erases all credentials from memory

#define ENTER_MASTER_PASSWORD     0                                             // locations of the main menu items
#define FIND_FAVORITE             1
#define FIND_ACCOUNT              2
#define FIND_BY_GROUP             3
#define EDIT_VIA_COMPUTER         4
#define ADD_ACCOUNT               5
#define LOGOUT                    6
#define FILE_MENU_SEL             7
#define SETTINGS                  8
#define FIX_CORRUPT_LIST          9
#define FACTORY_RESET             10

uint8_t menuNumber = MAIN_MENU_NUMBER;                                          // holds the menu number of the currently displayed menu
uint8_t elements = MAIN_MENU_ELEMENTS;                                          // holds the number of selections in the currently displayed menu
char *currentMenu[MENU_SIZE];                                                   // holds the content of the currently displayed menu.  An array of 10 pointers to char.

#define SEND_MENU_NUMBER          1
#define SEND_MENU_ELEMENTS        9                                             // number of selections in the send credentials menu
const char * const sendMenu[] =   {              
                                                 "Send Password <RET>",         // send the password followed by a carriage return
                                                 "Send User & Password",        // send the user name then the password UN_PW_DELAY milliseconds later
                                                 "Send URL",                    // send the URL of the associated website
                                                 "Send User Name",              // send the user name
                                                 "Send Pass (no <RET>)",
                                                 "Send Account",                // send the account name
                                                 "Send Old Password",           // send the previous password
                                                 "Edit Credentials",            // sends user to enterMenu menu
                                                 "Delete Credentials",          // delete the account
                                                 ""                           };

#define SEND_PASSWORD             0                                             // locations of the send credentials menu items
#define SEND_USER_AND_PASSWORD    1                                             
#define SEND_WEBSITE              2
#define SEND_USERNAME             3
#define SEND_PASSWORD_NO_RET      4
#define SEND_ACCOUNT              5
#define SEND_OLD_PASSWORD         6
#define EDIT_ACCOUNT              7
#define DELETE_ACCOUNT            8

#define EDIT_MENU_NUMBER          2
#define EDIT_MENU_ELEMENTS        8                                             // the number of selections in the menu for editing credentials
const char * const enterMenu[] =  {              
                                                 "Edit Account Name",           // menu picks appear only on the top line
                                                 "Edit User Name",              // edit the user name
                                                 "Edit Password",               // edit the password
                                                 "Edit URL",                    // edit the website URL
                                                 "Indicate Style",              // 
                                                 "Assign Groups",               // 
                                                 "Generate Password",           // generate a 31 character UUID for the password
                                                 "Save to Old Password",        // save the current password to the old password
                                                 ""                           };

#define EDIT_ACCT_NAME            0                                             // locations of the edit credentials menu items
#define EDIT_USERNAME             1
#define EDIT_PASSWORD             2
#define EDIT_WEBSITE              3
#define EDIT_STYLE                4
#define EDIT_GROUPS               5
#define GENERATE_PASSWORD         6
#define SAVE_OLD_PASSWORD         7

#define SETTINGS_MENU_NUMBER      3
#define SETTINGS_MENU_ELEMENTS    14                                             // the number of selections in the menu for changing settings

char *settingsMenu[] =                {
                                                 "Show Password",               // determines if passwords are displayed or masked with asterisk
                                                 "Decoy Password",              // Determines if a decoy password can be entered to automatically factory reset the device
                                                 "RGB LED Intensity",           // Setting the RGB LED's intensity High, Medium, Low, Off
                                                 "Timeout Minutes",             // set the timeout for automatic logout in minutes
                                                 "Login Attempts",              // the number of login attempts allowed before a factory reset occurs
																								 "Rename Groups",								// allows the user to rename the group categories
                                                 "Change Master Pass",   				// Change the master password
                                                 "Keyboard Language",           // Change the keyboard language
                                                 "Encoder Type",                // Change the encoder type
                                                 "Font",                        // Change the font
                                                 "Orientation",                 // Change display orientation
                                                 "Keyboard",                    // flag that determines if the input by keyboard feature is on or off
                                                 "Generated Pass Len",          // determines the size of the generated password
                                                 "Inter Char Delay",            // set the delay between characters when sent
                                                 ""                           };

#define SETTINGS_SET_SHOW_PW      0
#define SETTINGS_SET_DECOY        1
#define SETTINGS_SET_RGB_INT      2
#define SETTINGS_SET_TIMEOUT      3
#define SETTINGS_SET_LOGIN_ATTEM  4
#define SETTINGS_GROUP_DEFINITION 5
#define SETTINGS_CHANGE_MASTER    6
#define SETTINGS_KEYBOARD_LANG    7
#define SETTINGS_ENCODER_TYPE     8
#define SETTINGS_FONT             9
#define SETTINGS_ORIENTATION      10
#define SETTINGS_SET_KEYBOARD     11                                            //
#define SETTINGS_GEN_PW_SIZE      12
#define SETTINGS_CHAR_DELAY       13

#define LOGOUT_TIMEOUT_MENU_NUMBER    4
#define LOGOUT_TIMEOUT_MENU_ELEMENTS  7
const char * const logoutTimeoutMenu[] = {       
                                                 "30",                          // 30 half hour
                                                 "60",                          // INITIAL_MEMORY_STATE_BYTE, one hour
                                                 "90",                          // 90 one and a half hours
                                                 "120",                         // 120 two hours
                                                 "240",                         // 240 four hours
                                                 "1",                           // 1 one minute
                                                 "Never",                       // 0 never times out
                                                 ""                           };
#define LOGOUT_TIMEOUT_30         0
#define LOGOUT_TIMEOUT_60         1                                             // default
#define LOGOUT_TIMEOUT_90         2
#define LOGOUT_TIMEOUT_120        3
#define LOGOUT_TIMEOUT_240        4
#define LOGOUT_TIMEOUT_1          5
#define LOGOUT_TIMEOUT_0          6

#define LOGOUT_TIMEOUT_VAL_30     30
#define LOGOUT_TIMEOUT_VAL_60     60                                            // default
#define LOGOUT_TIMEOUT_VAL_90     90
#define LOGOUT_TIMEOUT_VAL_120    120
#define LOGOUT_TIMEOUT_VAL_240    240
#define LOGOUT_TIMEOUT_VAL_1      1
#define LOGOUT_TIMEOUT_VAL_0      0
#define LOGOUT_TIMEOUT_DEFAULT    LOGOUT_TIMEOUT_VAL_60

#define RGB_INTENSITY_MENU_NUMBER     5
#define RGB_INTENSITY_MENU_ELEMENTS   4
const char * const RGBLEDIntensityMenu[] = {     
                                                 "High",                        // INITIAL_MEMORY_STATE_BYTE
                                                 "Medium",                      // 128
                                                 "Low",                         // 64
                                                 "Off"                          // 0
                                                 ""                           };
#define RGB_INTENSITY_HIGH        0                                             // default
#define RGB_INTENSITY_MED         1
#define RGB_INTENSITY_LOW         2
#define RGB_INTENSITY_OFF         3

#define LOGIN_ATTEMPTS_MENU_NUMBER   6
#define LOGIN_ATTEMPTS_MENU_ELEMENTS 4
const char * const LoginAttemptsMenu[] = {       
                                                 "3",                           // INITIAL_MEMORY_STATE_BYTE
                                                 "5",
                                                 "10",
                                                 "25",
                                                 ""                           };
#define LOGIN_ATTEMPTS_3          0                                             
#define LOGIN_ATTEMPTS_5          1
#define LOGIN_ATTEMPTS_10         2                                             // default
#define LOGIN_ATTEMPTS_25         3

#define OFF_ON_MENU_NUMBER        7
#define OFF_ON_MENU_ELEMENTS      2
const char * const offOnMenu[] = {               
                                                 "Off",
                                                 "On",
                                                 ""                           };
#define OFF                       0
#define ON                        1

#define STYLE_MENU_NUMBER         8
#define STYLE_MENU_ELEMENTS       3
const char * const styleMenu[] = {               
                                                 "usr<RTN>pass<RTN>",
                                                 "usr<TAB>pass<RTN>",
                                                 "usr<TAB>pas<TAB,RTN>",
                                                 ""                           };
#define STYLE_RETURN              0
#define STYLE_TAB                 1
#define STYLE_TAB_TAB_RETURN      2

#define GROUP_MENU_NUMBER         9
#define GROUP_MENU_ELEMENTS       8
char   groupMenu[GROUP_MENU_ELEMENTS+1][DISPLAY_BUFFER_SIZE] = 
  																					  {   
                                                 "Favorites",
                                                 "",
                                                 "",
                                                 "",
                                                 "",
                                                 "",
                                                 "",
                                                 "",
                                                 ""                           };
#define GROUP_FAVORITES           0
#define GROUP_WORK                1
#define GROUP_PERSONAL            2
#define GROUP_HOME                3
#define GROUP_SCHOOL              4
#define GROUP_FINANCIAL           5
#define GROUP_MAIL                6
#define GROUP_CUSTOM              7

#define GROUP_EDIT_MENU_NUMBER		11
#define	GROUP_EDIT_MENU_ELEMENTS	7
const char * const groupEditMenu[] = {						
                                                 "Edit Group 1",
                                                 "Edit Group 2",
																								 "Edit Group 3",
																								 "Edit Group 4",
																								 "Edit Group 5",
																								 "Edit Group 6",
																								 "Edit Group 7"							};
#define EDIT_GROUP_1							0
#define EDIT_GROUP_2							1
#define EDIT_GROUP_3							2
#define EDIT_GROUP_4							3
#define EDIT_GROUP_5							4
#define EDIT_GROUP_6							5
#define EDIT_GROUP_7							6
																																								// The group designations
#define NONE                      0b00000000                                    // means this credential doesn't belong to any groups
#define FAVORITES                 0b00000001                                    // credentials can belong to more than one group
#define WORK                      0b00000010                                    // but they cannot belong to all groups
#define PERSONAL                  0b00000100                                    // because that == INITIAL_MEMORY_STATE_BYTE.
#define HOME                      0b00001000
#define SCHOOL                    0b00010000
#define FINANCIAL                 0b00100000
#define MAIL                      0b01000000
#define CUSTOM                    0b10000000
#define ALL_GROUPS                FAVORITES|WORK|PERSONAL|HOME|SCHOOL|FINANCIAL|MAIL|CUSTOM

#define FILE_MENU_NUMBER          10
#define FILE_MENU_ELEMENTS        2
const char * const fileMenu[] = {                
                                                 "Backup EEprom",               // duplicate the external EEprom
                                                 "Restore EEprm Backup",        // copies the content of the secondary EEprom back to the primary, overwriting.
                                                 //"Backup to .CSV File",       // sends all credential out through the keyboard for capture in an editor
                                                 //"Import PasswordPump",       // import from the PasswordPump CSV file
                                                 //"Import Chrome",             // import from the Chrome passwords export file
                                                 //"Import KeePass"             // import KeePass csv file
                                                 ""                           };
#define FILE_BACKUP_EEPROM        0
#define FILE_RESTORE_BACKUP       1
//#define FILE_BACKUP_ALL           2
//#define FILE_IMPORT_PP_CSV        3
//#define FILE_IMPORT_CP_CSV        4
//#define FILE_IMPORT_KEEPASS_CSV   5

#define KEYBOARD_MENU_NUMBER      11
#define KEYBOARD_MENU_ELEMENTS    10
const char * const keyboardMenu[] = {            
                                                 "Czech",
                                                 "Danish",
                                                 "Finnish",
                                                 "French",
                                                 "German",
                                                 "Norwegian",
                                                 "Spanish",      
                                                 "Swedish",
                                                 "United Kingdom",
                                                 "United States",
                                                 ""                           };
                                                  
#define KEYBOARD_CZECH            0
#define KEYBOARD_DANISH           1
#define KEYBOARD_FINNISH          2
#define KEYBOARD_FRENCH           3
#define KEYBOARD_GERMAN           4
#define KEYBOARD_NORWEGIAN        5
#define KEYBOARD_SPANISH          6
#define KEYBOARD_SWEDISH          7
#define KEYBOARD_UK               8
#define KEYBOARD_US               9
#define KEYBOARD_DEFAULT          KEYBOARD_US

#define ENCODER_MENU_NUMBER       12
#define ENCODER_MENU_ELEMENTS     2
const char * const encoderMenu[] = {             
                                                 "Normal",
                                                 "Lefty",
                                                 ""                           };

#define FONT_MENU_NUMBER          13
#define FONT_MENU_ELEMENTS         9
const char * const fontMenu[] = {                
                                                 "Arial14",                     //
                                                 "Arial_bold_14",
                                                 "Callibri10",
//                                               "fixednums8x16",               // broke, do NOT use
                                                 "TimesNewRoman13",
                                                 "Adafruit5x7",
                                                 "font5x7",
                                                 "lcd5x7",
                                                 "Stang5x7",
                                                 "System5x7",
                                                 ""                           };
// Some avaliable fonts if you want to experiment: (make sure you have a good
// backup CHIP that has a working font written to GET_ADDR_FONT!  If you select
// a font that will not display (i.e. it's too big, liked fixednums8x16) you 
// can get locked out of your PasswordPump.  Consider yourself warned.
// Arial14,Arial_bold_14,Callibri11,Callibri11_bold,Callibri11_italic,
// Callibri15,Corsiva_12,fixed_bold10x15,font5x7,font8x8,Iain5x7,lcd5x7,
// Stang5x7,System5x7,TimesNewRoman16,TimesNewRoman16_bold,
// TimesNewRoman16_italic,utf8font10x16,Verdana12,Verdana12_bold,
// Verdana12_italic,X11fixed7x14,X11fixed7x14B,ZevvPeep8x16
                                               
#define FONT_ARIAL14              0
#define FONT_ARIAL_BOLD_14        1
#define FONT_CALLIBRI10           2
//#define FONT_FIXEDNUMS8X16      3
#define FONT_TIMESNEWROMAN13      3
#define FONT_ADAFRUIT5X7          4
#define FONT_FONT5X7              5
#define FONT_LCD5X7               6
#define FONT_STANG5X7             7
#define FONT_SYSTEM5X7            8
#define DEFAULT_FONT              FONT_SYSTEM5X7

#define ORIENT_MENU_NUMBER        14
#define ORIENT_MENU_ELEMENTS      2
const char * const orientMenu[] = {              
                                                 "Lefty",
                                                 "Righty",
                                                 ""                           };
#define ORIENT_LEFTY              0
#define ORIENT_RIGHTY             1
#define DEFAULT_ORIENT            ORIENT_LEFTY

#define GEN_PW_SIZE_MENU_NUMBER   15
#define GEN_PW_SIZE_MENU_ELEMENTS 5
const char * const genPWSizeMenu[] = {       
                                                 "8",                           // INITIAL_MEMORY_STATE_BYTE
                                                 "10",
                                                 "16",
                                                 "24",
                                                 "31",
                                                 ""                           };
#define GEN_PW_SIZE_8             0                                             
#define GEN_PW_SIZE_10            1
#define GEN_PW_SIZE_16            2                                             // default
#define GEN_PW_SIZE_24            3
#define GEN_PW_SIZE_31            4

#define DEFAULT_GEN_PW_SIZE       2

#define GEN_PW_SIZE_VAL_8         8
#define GEN_PW_SIZE_VAL_10        10
#define GEN_PW_SIZE_VAL_16        16
#define GEN_PW_SIZE_VAL_24        24
#define GEN_PW_SIZE_VAL_31        31

#define CHAR_DELAY_MENU_NUMBER    15
#define CHAR_DELAY_MENU_ELEMENTS  5
const char * const charDelayMenu[] = {       
                                                 "0",                           // INITIAL_MEMORY_STATE_BYTE
                                                 "10",
                                                 "25",
                                                 "100",
                                                 "250",
                                                 ""                           };
#define CHAR_DELAY_0              0                                             
#define CHAR_DELAY_10             1                                             // default
#define CHAR_DELAY_25             2                                             
#define CHAR_DELAY_100            3
#define CHAR_DELAY_250            4

#define DEFAULT_CHAR_DELAY        0

#define CHAR_DELAY_VAL_0          0UL
#define CHAR_DELAY_VAL_10         10
#define CHAR_DELAY_VAL_25         25
#define CHAR_DELAY_VAL_100        100
#define CHAR_DELAY_VAL_250        250

#define SCREEN_WIDTH              128                                           // OLED display width, in pixels
#define SCREEN_HEIGHT             32                                            // OLED display height, in pixels
#define OLED_RESET                -1                                            // Reset pin # (or -1 if sharing ItsyBitsy reset pin)

#define MAX_LEN_CSV_LINE          500                                           // max chars in KEEPASS_CSV file (unused functionality)
#define MAX_CSV_FIELDS            20                                            // max fields in KEEPASS_CSV line (unused functionality)

#define SIZE_OF_DECOY_PW          2                                             // size in chars of the decoy password string

#define MILLISECONDS_IN_A_SECOND  1000UL
#define MILLISECONDS_IN_A_MINUTE  60000UL
#define PAUSE_TO_SHOW_REMAINING   60000UL
#define SECONDS_IN_A_MINUTE       60
#define SECONDS_IN_AN_HOUR        3600UL
#define MINUTES_IN_AN_HOUR        60

//- Global Variables                                                            // char is signed by default. byte is unsigned.

                                                                                // CMDMessenger vars
//char field_separator   = ',';                                                   
//char command_separator = ';';
char field_separator   = '~';                                                   // ascii 126
char command_separator = '|';                                                   // ascii 124
char escape_separator  = '\\';                                                  // ascii 92

                                                                                // CSV Processing
enum { NOMEM = -2 };                                                            // out of memory signal
static char *line    = NULL;                                                    // input chars
static char *sline   = NULL;                                                    // line copy used by split
static int  maxline  = 0;                                                       // size of line[] and sline[]
static char **field  = NULL;                                                    // field pointers
static int  maxfield = 0;                                                       // size of field[]
static int  nfield   = 0;                                                       // number of fields in field[]
static char fieldsep[] = ","; 																									// field separator chars
static char *advquoted(char *);
static int split(void);                                                         // END CSV Processing
                                                                                
int lastModeA = LOW;                                                            // Rotary encoder states
int lastModeB = LOW;
int curModeA = LOW;
int curModeB = LOW;
int encPos = 0;
int encPosLast = 0;
int change = 0;                                                                 // END Rotary encoder state                           

long milliseconds;                                                              // holds time in milliseconds
long oldTimeLeft;                                                               // holds the time in seconds from the previous calculation.
char accountName[ACCOUNT_SIZE];                                                 // holds the account name
char username[USERNAME_SIZE];                                                   // holds the user name of the current account
char password[PASSWORD_SIZE];                                                   // holds the password of the current account
char oldPassword[PASSWORD_SIZE];                                                // holds the previous password of the current account
char website[WEBSITE_SIZE];                                                     // holds the URL for the credentials
char salt[SALT_SIZE];                                                           // holds the salt for each set of credentials
char style[STYLE_SIZE];                                                         // holds the style of the current account (<TAB> or <CR> between send user name and password)
char groupCategory_1[CATEGORY_SIZE];                                            // the name of group category 1
char groupCategory_2[CATEGORY_SIZE];                                            // the name of group category 2
char groupCategory_3[CATEGORY_SIZE];                                            // the name of group category 3
char groupCategory_4[CATEGORY_SIZE];                                            // the name of group category 4
char groupCategory_5[CATEGORY_SIZE];                                            // the name of group category 5
char groupCategory_6[CATEGORY_SIZE];                                            // the name of group category 6
char groupCategory_7[CATEGORY_SIZE];                                            // the name of group category 7
uint8_t groups;                                                                 // to which of 8 groups does the set of credentials belongs

boolean updateExistingAccount = false;                                          // indicates if we are updating an existing account

boolean isPurple  = false;                                                      // indicates if the RGB LED is purple
boolean isRed     = false;                                                      // indicates if the RGB LED is red
boolean isGreen   = false;                                                      // indicates if the RGB LED is green
boolean isYellow  = false;                                                      // indicates if the RGB LED is yellow
boolean isBlue    = false;                                                      // indicates if the RGB LED is blue

boolean oledDim   = false;                                                      // indicates if the oled display is dimmed

uint16_t angle = 0;

uint8_t keyboardType;
uint8_t originalKeyboardType;
uint8_t changeKeyboardAttempts;                                                 // we can only change the keyboard once, subsequent attempts result in a frozen device
uint8_t encoderType;
uint8_t font;
uint8_t orientation;
uint8_t generatedPasswordSize;
uint8_t rotaryPin1  = 9;
uint8_t rotaryPin2  = 7;
unsigned long interCharPause;
uint8_t interCharPauseVal;

const uint8_t HSVlights[61] =                                                   // used to change the color of the RGB LED when logged out
{0, 4, 8, 13, 17, 21, 25, 30, 34, 38, 42, 47, 51, 55, 59, 64, 68, 72, 76,
81, 85, 89, 93, 98, 102, 106, 110, 115, 119, 123, 127, 132, 136, 140, 144,
149, 153, 157, 161, 166, 170, 174, 178, 183, 187, 191, 195, 200, 204, 208,
212, 217, 221, 225, 229, 234, 238, 242, 246, 251, 255};

#define LEN_ALL_CHARS             88
#define DEFAULT_ALPHA_EDIT_POS    34                                            
#define DEFAULT_STYLE_EDIT_POS    24

const char allChars[LEN_ALL_CHARS] =                                            // used to edit text via rotary encoder (88 bytes w/ null terminator)
" ?><:';}{][+_)(*%$#!=-.@ 0123456789AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz"; 
#define POS_Y_N_CONFIRM           14                                            // position of Y and N for the confirm menu item
const char confirmChars[3] = "NY";                                              // used to select N(o) or Y(es) via rotary encoder to confirm a destructive action

char line1DispBuff[DISPLAY_BUFFER_SIZE];                                        // used to buffer output of line 1 for the led display
char line2DispBuff[DISPLAY_BUFFER_SIZE];                                        // used to buffer output of line 2 for the led display
char line3DispBuff[DISPLAY_BUFFER_SIZE];                                        // used to buffer output of line 3 for the led display
char line4DispBuff[DISPLAY_BUFFER_SIZE];                                        // used to buffer output of line 4 for the led display

#define LINE_1_POS                0
#define LINE_2_POS                1
#define LINE_3_POS                2
#define LINE_4_POS                3

const char spaceFilled[] = "                    ";                              // 20 chars long 

#define TAB_KEY                   KEY_TAB                                       // TAB key is ascii 0x2b (not 0x09) or 0x2b, 0xB3; KEY_TAB from Keyboard.h, 0xB3

char masterPassword[MASTER_PASSWORD_SIZE];                                      // this is where we store the master password for the device
char newPassword[MASTER_PASSWORD_SIZE];                                         // this is where we store the master password when entering a new password
char masterSalt[MASTER_PASSWORD_SIZE];                                          // holds the salt associated with the hashed master password

uint8_t loginFailures;                                                          // count of the number of consecutive login failures since the last successful password entry.
                                                                                // Used to defend against brute force attack.
uint8_t showPasswordsFlag;                                                      // flag indicating if we show passwords via the UI, or hide them.
uint8_t keyboardFlag;                                                           // flag indicating if we're using the keyboard to edit credentials
uint8_t decoyPassword;                                                          // specifies if the decoy password feature is enabled
uint8_t RGBLEDIntensity = RGB_LED_DEFAULT;                                      // the intensity of the RGB LED, default is Medium
unsigned long logoutTimeout = 60;                                               // the inactivity logout timer, default is one hour
uint8_t loginAttempts = ATTEMPTS_DEFAULT;                                       // the number of failed login attempts before a factory reset occurs
uint8_t addFlag = false;                                                        // tracks whether we reached the Add Account menu via the main menu or the find menu,
                                                                                // which is necessary to determine where to return to on EVENT_LONG_CLICK.

uint8_t machineState = 0;                                                       // the state of the device
                                                                                // it is presently unnecessarily long.  Can all be stored in uint8_t otherwise.
int position = 0;                                                               // the position of the rotary encoder, used to navigate menus and enter text.
uint8_t enterPosition = 0;                                                      // when alpha editing w/ rotary encoder, position in the edited word
uint8_t acctPosition;                                                           // the position of the selected account.
uint8_t acctCount = 0;                                                          // the number of accounts in EEprom.
boolean authenticated = false;                                                  // indicates if the correct master password has been provided
unsigned long lastActivityTime;                                                 // used to automatically logout after a period of inactivity
uint32_t iterationCount = 0;                                                    // # of times ProcessEvent() called since last evaluation of lastActivityTime
uint8_t headPosition = INITIAL_MEMORY_STATE_BYTE;                               // the head of the doubly linked list that keeps account names sorted
uint8_t tailPosition;                                                           // the tail of the doubly linked list that keeps account names sorted
uint8_t groupFilter = ALL_GROUPS;                                               // turn on all groups in the filter
uint8_t fromFilter = FAVORITES;																									// indicates the filter in effect for menu navigation

char buf[MAX_LEN_CSV_LINE];                                                     // input line buffer, CSV file processing
char *unquote(char *);

enum                                                                            // Commands for CMDMessenger
{
  kAcknowledge            ,
  kStrAcknowledge         ,
  pyReadAccountName       ,
  pyReadUserName          ,
  pyReadPassword          ,
  pyReadOldPassword       ,
  pyReadURL               ,
  pyReadStyle             ,
  pyReadGroup             ,
  pyUpdateAccountName     ,
  pyUpdateUserName        ,
  pyUpdatePassword        ,
  pyUpdateURL             ,
  pyUpdateURL_1           ,
  pyUpdateURL_2           ,
  pyUpdateURL_3           ,
  pyUpdateStyle           ,
  pyUpdateGroup           ,
  pyUpdateOldPassword     ,
  pyGetNextPos            ,
  pyGetPrevPos            ,
  pyGetAcctPos            ,
  pyReadHead              ,
  pyReadTail              ,
  pyGetNextFreePos        ,
  kError                  ,                                                      // Command to message that an error has occurred
  pyDeleteAccount         ,
  pyExit                  ,
  pyBackup                ,
  pyFactoryReset          ,
  pyFixCorruptLinkedList  ,
  pyRestore               ,
  pyGetAccountCount       ,
  pyDecoyPassword         ,
  pyShowPasswords         ,
	pyReadGroup1Name			  ,
	pyReadGroup2Name			  ,
	pyReadGroup3Name			  ,
	pyReadGroup4Name			  ,
	pyReadGroup5Name			  ,
	pyReadGroup6Name			  ,
	pyReadGroup7Name			  ,
  pyUpdateCategoryName    ,
  pyUpdateRGBLEDIntensity ,
  pyUpdateLoginMinutes    ,
  pyUpdateLoginAttempts   ,
  pyUpdatePasswordLength  ,
  pyUpdateInterCharDelay  ,
  pyGetRGBLEDIntensity    ,
  pyGetLoginMinutes       ,
  pyGetLoginAttempts      ,
  pyGetPasswordLength     ,
  pyGetInterCharDelay     ,
  pyChangeMasterPass    
};

//- Global Volatile variables.
                                                                                // TODO: these variables no longer need to be volatile since we're not using interrupts
volatile boolean interruptsOn = true;
volatile uint8_t event = EVENT_NONE;                                            // this is the only variable manipulated in the interrupt.

//- Object setup

CmdMessenger cmdMessenger = CmdMessenger(Serial, field_separator, command_separator, escape_separator); // Attach a new CmdMessenger object to the default Serial port
SHA256 sha256;
AESSmall256 aes;                                                                // 32 byte key, 32 byte block; this uses 4% more program memory. Set 
                                                                                // MASTER_PASSWORD_SIZE = 32 when in use.
Button2 encoderButton = Button2(BUTTON_PIN);                                    // the button on the rotary encoder.
SSD1306AsciiWire oled;                                                          // for the SSD1306 display

/*
#if defined(__SAMD51__) || defined(NRF52840_XXAA)
  Adafruit_FlashTransport_QSPI flashTransport(PIN_QSPI_SCK, PIN_QSPI_CS, PIN_QSPI_IO0, PIN_QSPI_IO1, PIN_QSPI_IO2, PIN_QSPI_IO3);
#else
  #if (SPI_INTERFACES_COUNT == 1)
    Adafruit_FlashTransport_SPI flashTransport(SS, &SPI);
  #else
    Adafruit_FlashTransport_SPI flashTransport(SS1, &SPI1);
  #endif
#endif
Adafruit_SPIFlash flash(&flashTransport);
FatFileSystem fatfs;                                                            // file system object from SdFat
*/
//- Function Prototypes

void setup(void);                                                               // first function run by device
void loop(void);                                                                // iterates forever
void ProcessEvent(void) ;                                                       // to handle events as they arise
void ConfirmChoice(uint8_t state);                                              // confirms a Y/N choice input via rotary encoder
void ReadFromSerial(char *buffer, uint8_t size, const char *prompt);
void switchToEditMenu(void);
void switchToSendCredsMenu(void);
void switchToFindAcctMenu(void);
void SwitchRotatePosition(uint8_t pos);
void FactoryReset(void);
void buttonReleasedHandler(Button2& btn);
void deleteAccount(uint8_t position);
void generatePassword(char *password, uint8_t size, uint8_t appendNullTerm);
void sendAccount(void);
void sendUsername(void);
void sendWebSite(void);
void sendPassword(void);
void sendUsernameAndPassword(void);
//void sendAll(void);
void DisplayToMenu(char* lineToPrint);
void DisplayToItem(char* lineToPrint);
void DisplayToStatus(char* lineToPrint);
void DisplayToError(char* lineToPrint);
void DisplayToDebug(char* lineToPrint);
void DisplayToEdit(char* lineToPrint);
void DisplayToHelp(char* lineToPrint);
void BlankLine1(void);
void BlankLine2(void);
void BlankLine3(void);
void DisplayBuffer(void);
void DisplayBuffer1(void);
void DisplayBuffer2(void);
void DisplayBuffer3(void);
void DisplayBuffer4(void);
void ShowMenu(uint8_t position, char **menu);
void ShowMenu(uint8_t position, char **menu, char *menuName);
void MenuUp(char **menu);
void MenuDown(char **menu);
void ShowChar(char charToShow, uint8_t  pos) ;
void setPurple(void);
void setRed(void);
void setGreen(void);
void setYellow(void);
void setBlue(void);
void setColor(uint8_t  redValue, uint8_t  greenValue, uint8_t  blueValue);
boolean authenticateMaster(char *password);
void sha256Hash(char *password);
void encrypt32Bytes(char *outBuffer, char *inBuffer);
void decrypt32(char *outBuffer, char *inBuffer);
uint8_t countAccounts() ;
uint8_t getNextFreeAcctPos(void) ;
void readAcctFromEEProm(uint8_t pos, char *buf);                                // read the account from EEprom and decrypt it
void readWebSiteFromEEProm(uint8_t pos, char *buf);
void readUserFromEEProm(uint8_t pos, char *buf);
void readStyleFromEEProm(uint8_t pos, char *buf) ;
void readPassFromEEProm(uint8_t pos, char *buf);
void readOldPassFromEEProm(uint8_t pos, char *buf);
void setListHeadPosition(void);                                                 // set headPosition
uint8_t getNextPtr(uint8_t pos);
uint8_t getPrevPtr(uint8_t pos);
void writeNextPtr(uint8_t pos, uint8_t nextPtr);
void writePrevPtr(uint8_t pos, uint8_t prevPtr);
void writeLoginFailures(void);
void writeResetFlag(uint8_t buf);
void writeShowPasswordsFlag(void);
void writeDecoyPWFlag(void);
void writeKeyboardFlag(void);
void writeListHeadPos(uint8_t pos);
void writeRGBLEDIntensity();
boolean eeprom_is_addr_ok(uint32_t addr);
boolean eeprom_write_bytes( uint32_t startAddr, 
                            const char* buf, 
                            uint8_t numBytes);
void InitializeEEProm(void);
void initSPI(void);                                                             // Init SPI to run EEPROM with phase, polarity = 0,0
uint8_t SPI_tradeByte(uint8_t byte);                                            // 
void EEPROM_send16BitAddress(uint32_t address);                                 // splits 16-bit address into 2 bytes, sends both
uint8_t EEPROM_readStatus(void);                                                // reads the EEPROM status register
uint8_t EEPROM_readStatusSecondary(void);
void EEPROM_writeEnable(void);                                                  // helper: sets EEPROM write enable
uint8_t read_eeprom_byte(uint32_t address);                                     // gets a byte from a given memory location
void read_eeprom_array( uint32_t address, 
                        char *buffer, 
                        uint8_t sizeOfBuffer  ) ;
void read_eeprom_array_secondary( uint32_t address, 
                                  char *buffer, 
                                  uint8_t sizeOfBuffer  );
void write_eeprom_byte(uint32_t address, uint8_t byte) ;                        // writes a byte to a given memory location
void write_eeprom_array(uint32_t address, 
                        char *buffer, 
                        uint8_t sizeOfBuffer);
void CopyEEPromToBackup(void);
void RestoreEEPromBackup(void) ;
uint8_t findTailPosition(uint8_t pos);
void writePointers(uint8_t accountPosition, char *accountName);
void FixCorruptLinkedList(void);
void Debug(char *text);
void DebugLN(char *text);
void DebugMetric(char *text, uint8_t number);
void TestEEPromWrite();
void TestEEPromRead();
void InitAllEEProm();
//void importKeePassCSV();
//char *csvgetline(File fin);
//int csvnfield(void);
//char *csvfield(int n);
void sendOldPassword();
void setSalt(char *salt, uint8_t size);
void sha256HashOnce(char *password);
void readSaltFromEEProm(uint8_t pos, char *buf);
void writeLogoutTimeout();
void writeLoginAttempts();
void PopulateGlobals();
void InitializeGlobals();
void ProcessAttributeInput( char *attributeName, 
                            uint8_t attributeSize, 
                            const char    *menuName, 
                            uint8_t nextPosition,
                            uint8_t acctFlag,
                            uint32_t address          );
void enterAttributeChar(char *attribute, uint8_t passwordFlag);
void EditAttribute(uint8_t aState, uint8_t pos);
//char *csvgetline(File *f);                                                    // read next input line
//char *csvfield(int n);	                                                      // return field n
//int csvnfield(void);		                                                      // return number of fields
void ShowSplashScreen();                                                        // shows the initial spash screen with the copyright
void DisableInterrupts();
void EnableInterrupts();
uint8_t readGroupFromEEprom(uint8_t pos);
void delayNoBlock(unsigned long milliseconds);
void writeGroup(uint8_t pos, uint8_t group);
void SetSaltAndKey(uint8_t position);                                           // populate and save the salt, set the key with the salt and master password
void switchToFindByGroupMenu(uint8_t menu, boolean setAcctPosition);
void sendRTN();
void sendTAB();
void ChangeMasterPassword(char *passedNewPassword);
uint8_t FindAccountPos(char *accountName);
//void BackupToPPCVSFile();                                                     // before executing the function the user must open a text editor and place input focus there.
void RestoreFromPPCVSFile();
void ImportChromeExportFile();
void attachCommandCallbacks();                                                  // We must define a callback function in our Arduino program for each entry in the list below.
void OnUnknownCommand();                                                        // Called when a received command has no attached function
void OnReadAccountName();
void OnReadUserName();
void OnReadPassword();
void OnFactoryReset();
void OnReadURL();
void OnReadStyle();
void OnReadOldPassword();
void OnUpdateAccountName();
void OnUpdateCategoryName();
void OnUpdateRGBLEDIntensity();
void OnUpdateLoginMinutes();
void OnUpdateLoginAttempts();
void OnUpdateUserName();
void OnUpdatePassword();
void OnUpdateURL();
void OnUpdateStyle();
void OnGetNextPos();
void OnGetPrevPos();
void OnReadHead();
void OnReadTail();
void OnGetNextFreePos();
void OnDeleteAccount();
void initializeAllGroupCategories();																						// sets all group categories to their default values
uint8_t findListHeadPosition();                                                 // returns the position of the first element in the linked list
void OnUpdateRGBLEDIntensity();
void OnUpdateLoginMinutes();
void OnUpdateLoginAttempts();
void OnGetRGBLEDIntensity();
void OnGetLoginMinutes();
void OnGetLoginAttempts();
void OnChangeMasterPass();

Keyboard_ Keyboard;                                                             // define the keyboard object

//- Main Program Control

void setup() {                                                                  // runs first when the device is powered on
  if(DEBUG_ENABLED) {
    Serial.begin(BAUD_RATE);
    while(!Serial);
  }
  DebugLN("PasswordPump");

  pinMode(BUTTON_PIN, INPUT_PULLUP);                                            // setup button pin for input enable internal 20k pull-up resistor, goes LOW 

  pinMode(RED_PIN,    OUTPUT);                                                  // RGB LED pins
  pinMode(GREEN_PIN,  OUTPUT);                                                  // "
  pinMode(BLUE_PIN,   OUTPUT);                                                  // "
	pinMode(SET_OUT_PIN,OUTPUT);																									// Pin that will receive PWM output from GREEN_PIN

  pinMode(rotaryPin1, INPUT_PULLUP);
  pinMode(rotaryPin2, INPUT_PULLUP);
  
  pinMode(UNUSED_PIN2, OUTPUT);digitalWrite(UNUSED_PIN2, LOW);                  // set all unused pins to LOW
  pinMode(UNUSED_PIN3, OUTPUT);digitalWrite(UNUSED_PIN3, LOW);
  pinMode(UNUSED_PIN4, OUTPUT);digitalWrite(UNUSED_PIN4, LOW);
  pinMode(UNUSED_PIN5, OUTPUT);digitalWrite(UNUSED_PIN5, LOW);
  pinMode(UNUSED_PIN6, OUTPUT);digitalWrite(UNUSED_PIN6, LOW);
  pinMode(UNUSED_PIN7, OUTPUT);digitalWrite(UNUSED_PIN7, LOW);
  pinMode(UNUSED_PIN8, OUTPUT);digitalWrite(UNUSED_PIN8, LOW);
  pinMode(UNUSED_PIN9, OUTPUT);digitalWrite(UNUSED_PIN9, LOW);
  
  encoderButton.setReleasedHandler(buttonReleasedHandler);                      // fires when button is released

  randomSeed(micros()*micros()^analogRead(RANDOM_PIN)*analogRead(RANDOM_PIN2));	// seed the random number generator

  Wire.begin();
  Wire.setClock(KHZ_4000);
  oled.begin(&Adafruit128x32, SSD1306_I2C_ADDR);                                // initialize the OLED
  DimDisplay(false);

  DisableInterrupts();                                                          // turn off global interrupts, initially set to true
  initSPI();                                                                    // initialize SPI

  if(TEST_EEPROM){                                                              // Typically this is false unless debugging
    TestEEPromWrite();
    TestEEPromRead();
    InitAllEEProm();
  }

  if (getResetFlag != MEMORY_INITIALIZED_FLAG) {                                // if memory has never been initialized, initialize it.
    loginFailures = loginAttempts + 99;                                         // so that a condition inside of EVENT_RESET evaluates to true and the reset 
    FactoryReset();
  };
  
  RGBLEDIntensity = getRGBLEDInt;                                               // the intensity of the RGB LED
  if (RGBLEDIntensity == INITIAL_MEMORY_STATE_BYTE) {
    RGBLEDIntensity = RGB_LED_DEFAULT;
    writeRGBLEDIntensity();
  }

  setBlue();                                                                    // not yet authenticated
  
  loginFailures = getLoginFailures;                                             // getLoginFailures returns a byte.
  if (loginFailures == INITIAL_MEMORY_STATE_BYTE ) {                            // if loginFailures has never been written too
    loginFailures = 0;                                                          // set it to zero
    writeLoginFailures();                                                       // and write it to EEprom.
  }
	if (loginFailures) setRed();

  loginAttempts = getLoginAttempts;                                             // the maximum number of login attempts before factory reset
  if ((loginAttempts == INITIAL_MEMORY_STATE_BYTE) ||                           // if loginAttempts has never been written too
      (loginAttempts < LOGIN_ATTEMPTS_3          )   ) {                        // or loginAttempts is somehow < 3
    loginAttempts = ATTEMPTS_DEFAULT;                                           // set it to ATTEMPTS_DEFAULT (10)
    writeLoginAttempts();                                                       // and write it to EEprom
  }

  showPasswordsFlag = getShowPasswordsFlag;                                     // setup the show passwords flag and menu item. (getShowPasswordsFlag returns byte)
  if (showPasswordsFlag == INITIAL_MEMORY_STATE_BYTE ) {                        // this should never be true because the reset event sets the show passwords 
    showPasswordsFlag = true;                                                   // flag to a value but, for safety, set the show password flag to ON
    writeShowPasswordsFlag();                                                   // and write it to EEprom.
  }

  decoyPassword = getDecoyPWFlag;
  if (decoyPassword == INITIAL_MEMORY_STATE_BYTE) {
    decoyPassword = true;
    writeDecoyPWFlag();
  }

	uint8_t groupStatus;																													// setup the group menu
	groupStatus = getGroupStatus;																									// check to see if the group names are written to EEprom
	if (groupStatus == INITIAL_MEMORY_STATE_BYTE) {																// ...and if not initialize them
		initializeAllGroupCategories();
	}
	readGroupCategories();																												// set the group categories from EEprom
	loadGroupMenu();  															   												  	// load the group categories into the group menu

  encoderType = getEncoderType;                                                 // Setup the encoder type; normal or lefty.
  if (encoderType == INITIAL_MEMORY_STATE_BYTE) {
    encoderType = ENCODER_DEFAULT;
    writeEncoderType();
  }

  switch (encoderType) {
    case ENCODER_NORMAL:
      rotaryPin1 = 9;
      rotaryPin2 = 7;
      break;
    case ENCODER_LEFTY:
      rotaryPin1 = 7;
      rotaryPin2 = 9;
      break;
    default:                                                                    // set to ENCODER_NORMAL if ERR: 046
      encoderType = ENCODER_NORMAL;
      writeEncoderType();
      rotaryPin1 = 9;
      rotaryPin2 = 7;
      DisplayToError("ERR: 046");
      break;
  }

  interCharPause = getInterCharPause;                                           
  if (interCharPause == INITIAL_MEMORY_STATE_BYTE) {
    interCharPause = DEFAULT_CHAR_DELAY;
    writeEncoderType();
  }

  switch (interCharPause) {
    case CHAR_DELAY_0:
      interCharPauseVal = CHAR_DELAY_VAL_0;
      break;
    case CHAR_DELAY_10:
      interCharPauseVal = CHAR_DELAY_VAL_10;
      break;
    case CHAR_DELAY_25:
      interCharPauseVal = CHAR_DELAY_VAL_25;
      break;
    case CHAR_DELAY_100:
      interCharPauseVal = CHAR_DELAY_VAL_100;
      break;
    case CHAR_DELAY_250:
      interCharPauseVal = CHAR_DELAY_VAL_250;
      break;
    default:                                                                   
      interCharPause = DEFAULT_CHAR_DELAY;
      interCharPauseVal = CHAR_DELAY_VAL_0;
      writeInterCharPause();
      DisplayToError("ERR: 059");
      break;
  }

  font = getFont;                                                               // Setup the Font
  if (font == INITIAL_MEMORY_STATE_BYTE) {
    font = DEFAULT_FONT;
    writeFont();
  }

  switch(font) {
    case FONT_ARIAL14:
      oled.setFont(Arial14);
      break;
    case FONT_ARIAL_BOLD_14:
      oled.setFont(Arial_bold_14);
      break;
    case FONT_CALLIBRI10:
      oled.setFont(Callibri10);
      break;
//    case FONT_FIXEDNUMS8X16:                                                  // Never enable this font, it's broken and you'll lose your creds.
//      oled.setFont(fixednums8x16);
//      break;
    case FONT_TIMESNEWROMAN13:
      oled.setFont(TimesNewRoman13);
      break;
    case FONT_ADAFRUIT5X7:
      oled.setFont(Adafruit5x7);
      break;
    case FONT_FONT5X7:
      oled.setFont(font5x7);
      break;
    case FONT_LCD5X7:
      oled.setFont(lcd5x7);
      break;
    case FONT_STANG5X7:
      oled.setFont(Stang5x7);
      break;
    case FONT_SYSTEM5X7:
      oled.setFont(System5x7);
      break;
    default:
      oled.setFont(System5x7);
      DisplayToError("ERR: 047");
  }
  
  
  orientation = getOrientation;                                                 // Is the rotary encoder on the left or on the right?
  if (orientation == INITIAL_MEMORY_STATE_BYTE) {
    orientation = DEFAULT_ORIENT;
    writeOrientation();
  }

  switch (orientation) {
    case ORIENT_LEFTY:
      oled.displayRemap(ORIENT_LEFTY);
      break;
    case ORIENT_RIGHTY:
      oled.displayRemap(ORIENT_RIGHTY);
      break;
    default:
      oled.displayRemap(DEFAULT_ORIENT);
      DisplayToError("ERR: 048");
      break;
  }

  oled.clear();
  ShowSplashScreen();
  
  generatedPasswordSize = getGenPasswordSize;
  if (generatedPasswordSize == INITIAL_MEMORY_STATE_BYTE) {
    generatedPasswordSize = DEFAULT_GEN_PW_SIZE;
    writeGenPwSize();
  }
  
  keyboardType = getKeyboardType;                                               // Setup the Keyboard Language
	if (keyboardType == INITIAL_MEMORY_STATE_BYTE) {															// ...and if not initialize them
    keyboardType = KEYBOARD_DEFAULT;
		writeKeyboardType();
	}
  switch(keyboardType) {
     case KEYBOARD_CZECH:
      Keyboard.InitKeyboard(_asciimapCzech, _hidReportDescriptorCzech);
      break;
     case KEYBOARD_DANISH:
      Keyboard.InitKeyboard(_asciimapDanish, _hidReportDescriptorDanish);
      break;
     case KEYBOARD_FINNISH:
      Keyboard.InitKeyboard(_asciimapFinnish, _hidReportDescriptorFinnish);
      break;
     case KEYBOARD_FRENCH:
      Keyboard.InitKeyboard(_asciimapFrench, _hidReportDescriptorFrench);
      break;
     case KEYBOARD_GERMAN:
      //setlocale(LC_ALL, "de_DE");                                             // Set local to Germany
      Keyboard.InitKeyboard(_asciimapGerman, _hidReportDescriptorGerman);
      break;
     case KEYBOARD_NORWEGIAN:
      Keyboard.InitKeyboard(_asciimapNorwegian, _hidReportDescriptorNorwegian);
      break;
     case KEYBOARD_SPANISH:
      Keyboard.InitKeyboard(_asciimapSpanish, _hidReportDescriptorSpanish);
      break;
     case KEYBOARD_SWEDISH:
      Keyboard.InitKeyboard(_asciimapSwedish, _hidReportDescriptorSwedish);
      break;
     case KEYBOARD_UK:
      Keyboard.InitKeyboard(_asciimapUK, _hidReportDescriptorUK);
      break;
     case KEYBOARD_US:
      //setlocale(LC_ALL, "C");
      Keyboard.InitKeyboard(_asciimapUS, _hidReportDescriptorUS);
      break;
    default:
      Keyboard.InitKeyboard(_asciimapUS, _hidReportDescriptorUS);
      keyboardType = KEYBOARD_DEFAULT;
      writeKeyboardType();
      DisplayToError("045");
      break;
  }
	
  lastActivityTime = millis();                                                  // establish the start time for when the device is powered up
  authenticated = false;                                                        // we're not authenticated yet!
  changeKeyboardAttempts += 1;

  machineState = STATE_SHOW_MAIN_MENU;
  position = ENTER_MASTER_PASSWORD; 
  event = EVENT_NONE;
  menuNumber = MAIN_MENU_NUMBER;
  int arraySize = 0;
  for (uint8_t i = 0; i < MENU_SIZE; i++) {
    arraySize += sizeof(mainMenu[i]);  
  }
  memcpy(currentMenu, mainMenu, arraySize);
  elements = MAIN_MENU_ELEMENTS;
  
  DisplayToHelp("Click to begin.");

  EnableInterrupts();                                                           // Turn on global interrupts
}                                                                               // end of setup()
  
void loop() {                                                                   // executes forever until reset button is pressed or power is interrupted
  encoderButton.loop();                                                         // polling for button press TODO: replace w/ interrupt
  pollEncoder();                                                                // tried to use interrupts for the encoder but the results were inconsistent
  ProcessEvent();                                                               // process any events that might have occurred.
}

void pollEncoder() {
  change = 0;
  curModeA = digitalRead(rotaryPin1);                                           // compare the four possible states to figure out what has happened
  curModeB = digitalRead(rotaryPin2);                                           // then increment/decrement the current encoder's position
  if (curModeA != lastModeA) {
    if (curModeA == LOW) {
      if (curModeB == LOW) {
        encPos--;
      } else {
        encPos++;
      }
    } else {
      if (curModeB == LOW) {
        encPos++;
      } else {
        encPos--;
      }
    }
  }
  if (curModeB != lastModeB) {
    if (curModeB == LOW) {
      if (curModeA == LOW) {
        encPos++;
      } else {
        encPos--;
      }
    } else {
      if (curModeA == LOW) {
        encPos--;
      } else {
        encPos++;
      }
    }
  }
  lastModeA = curModeA;                                                         // set the current pin modes (HIGH/LOW) to be the last know pin modes
  lastModeB = curModeB;                                                         // for the next loop to compare to
  if (encPos < encPosLast) {                                                    // if this encoder's position changed, flag the change variable so we
    if (encPos%4 == 0) {                                                        // know about it later
      change = 1;
      event = EVENT_ROTATE_CW;
    }
  } else if (encPos > encPosLast) {
    if (encPos%4 == 0) {
      change = 1;
      event = EVENT_ROTATE_CC;
    }
  }
  
  if (change == 1) {
    encPosLast = encPos;                                                        // if an encoder has changed set encPosLast
  }
}

void ProcessEvent() {                                                           // processes events
  if (event != EVENT_NONE) {
    DisableInterrupts();
    lastActivityTime = millis();                                                // bump up the lastActivityTime, we don't reset iterationCount here, not 
                                                                                // necessary and slows responsiveness just a bit
  } else {                                                                      // event == EVENT_NONE
    EnableInterrupts();
    if (++iterationCount == MAX_ITERATION_COUNT) {                              // we don't want to call millis() every single time through the loop
      milliseconds = millis();
      iterationCount = 0;                                                       // 
      if (logoutTimeout && authenticated) {                                     // if logoutTimeout != 0, i.e. there is a logout timeout set.
        unsigned long logoutTime = lastActivityTime +                           // logoutTimeout = 30, 60, 90, etc.; 
                         (logoutTimeout * MILLISECONDS_IN_A_MINUTE);            // convert logoutTimeout to milliseconds by multiplying by 1000 milliseconds in a second * 60 seconds in a minute.
        if (milliseconds < logoutTime) {                                        // check to see if the device has been idle for logoutTimeout milliseconds
																																								// Need to find a way to get the display to clear every time we display a new number...
          long timeLeft = logoutTime - milliseconds;                            // calculate time remaining until logout 
          timeLeft = timeLeft/MILLISECONDS_IN_A_SECOND;                         // convert timeLeft to seconds, max of 4 decimal places
          if (timeLeft != oldTimeLeft) { 
            if (milliseconds - lastActivityTime > MILLISECONDS_IN_A_MINUTE) {   // if we've been idle for more than a minute, show seconds left until logout
              oldTimeLeft = timeLeft;
              uint8_t roundHoursTillLogout   = timeLeft / SECONDS_IN_AN_HOUR;
              uint8_t roundMinutesTillLogout = (timeLeft - (roundHoursTillLogout * SECONDS_IN_AN_HOUR)) / SECONDS_IN_A_MINUTE;
              uint8_t roundSecondsTillLogout = ((timeLeft - (roundHoursTillLogout * SECONDS_IN_AN_HOUR)) - (roundMinutesTillLogout * SECONDS_IN_A_MINUTE));
              char sTimeTillLogout[21];
              sprintf(sTimeTillLogout, "Time Left:  %2u:%02u:%02u", roundHoursTillLogout, roundMinutesTillLogout, roundSecondsTillLogout);
              DisplayToHelp(sTimeTillLogout);
            }
          }
          if ((milliseconds + LOGOUT_WARNING) > logoutTime) {                   // Check to see if we are within 25 seconds of logging out
            if (RGBLEDIntensity) {
              uint8_t oldRGBLEDIntensity = RGBLEDIntensity;
              RGBLEDIntensity = RGB_LED_HIGH;
              setRed();
              delayNoBlock(100UL);                                              // Flash bright red to warn that we're going to be logging out
              RGBLEDIntensity = oldRGBLEDIntensity;
              setGreen();
             }
          }
          return;                                                               // not time to logout yet and event == EVENT_NONE, so just return.
        } else {
          //sendLockAndLogout();                                                // Uncomment if you want the computer screen to lock when auto logout of PasswordPump; Send LEFT GUI - l to computer          
          event = EVENT_LOGOUT;                                                 // otherwise we've been idle for more than logoutTimeout, logout.
																																								// do not return, continue processing in this function
        }
      } else {																																	// logout timeout is not enabled or we are already logged out
        return;                                                                 
      }
    } else {                                                                    // iterationCount is < 1048575
			if (iterationCount % 32768 == 0) {
				if (!authenticated && !loginFailures && RGBLEDIntensity != RGB_LED_OFF) {	
					angle += 1;															  														// if we are logged out and there are no login failures
					if (angle > 360) angle = 0;
					trueHSV(angle);																		  									// pulse the RGB LED
				}
			}
			return;                                                                   // not time to check millis() yet, just return
    }
  }

  //DebugMetric("Event: ",event);
  //DebugMetric("machineState: ",machineState);
  if        (event == EVENT_ROTATE_CW) {                                        // scroll forward through something depending on state...
    if ((STATE_SHOW_MAIN_MENU == machineState) &&
         authenticated                                                      ) { // this prevents navigation away from 'Enter Master Password' when not 
                                                                                // authenticated.
      if (position < MAIN_MENU_ELEMENTS - 1) {                                  // prevent scrolling past the last item on the menu
        position++;
        MenuDown(currentMenu);                                                  // move one position down the current menu
      }
    } else if ((STATE_ENTER_MASTER   == machineState  ) ||											// event == EVENT_ROTATE_CW
               (STATE_EDIT_ACCOUNT   == machineState  ) ||
//             (STATE_EDIT_STYLE     == machineState  ) ||
               (STATE_EDIT_USERNAME  == machineState  ) ||
               (STATE_EDIT_PASSWORD  == machineState  ) ||
               (STATE_EDIT_WEBSITE   == machineState  ) ||
               (STATE_CHANGE_MASTER  == machineState  )	||
							 (STATE_EDIT_GROUP_1	 == machineState	) ||
							 (STATE_EDIT_GROUP_2	 == machineState	) ||
							 (STATE_EDIT_GROUP_3	 == machineState	) ||
							 (STATE_EDIT_GROUP_4	 == machineState	) ||
							 (STATE_EDIT_GROUP_5	 == machineState	) ||
							 (STATE_EDIT_GROUP_6	 == machineState	) ||
							 (STATE_EDIT_GROUP_7	 == machineState	)) {
      if (position < (LEN_ALL_CHARS - 2)) {
        position++;
      }
      char charToPrint = allChars[position];                                    // TODO: eliminate this assignment / needless charToPrint variable
      ShowChar(charToPrint, enterPosition);
    } else if (STATE_SEND_CREDS_MENU == machineState){											    // event == EVENT_ROTATE_CW
      if (position < SEND_MENU_ELEMENTS - 1) {
        position++;
        MenuDown(currentMenu);
        setHelpOnSendCredsMenu(position);
      }
    } else if (STATE_EDIT_CREDS_MENU == machineState){											    // event == EVENT_ROTATE_CW
      if ((position < (EDIT_MENU_ELEMENTS - 1)) && (acctCount > 0)) {           // we'll only show the edit account options when there's at least one account
        position++;
        MenuDown(currentMenu);
        SwitchRotatePosition(position);
        setHelpOnEditCredsMenu(position);
      }
    } else if (STATE_MENU_FIND_BY_GROUP == machineState) {											// event == EVENT_ROTATE_CW
      if ((position < (GROUP_MENU_ELEMENTS - 1)) && (acctCount > 0)) {          // we'll only show the edit account options when there's at least one account
				DisplayToItem((char *) (groupMenu + (++position)));
      }
    } else if ((STATE_KEY_ON_OFF_MENU     == machineState) ||										// event == EVENT_ROTATE_CW
               (STATE_SHOW_PW_ON_OFF_MENU == machineState) ||
               (STATE_DECOY_ON_OFF_MENU   == machineState)) {
      position = !position;                                                     // flip from 0 to 1 or from 1 to 0
      ShowMenu(position, currentMenu);
    } else if (STATE_MENU_LOGIN_ATTEM     == machineState) {									  // event == EVENT_ROTATE_CW
      if (position < LOGIN_ATTEMPTS_MENU_ELEMENTS - 1) {                        
        position++;
        MenuDown(currentMenu);
      }
    } else if (STATE_MENU_KEYBOARD       == machineState) {									    // event == EVENT_ROTATE_CW
      if (position < KEYBOARD_MENU_ELEMENTS - 1) {                        
        position++;
        MenuDown(currentMenu);
      }
    } else if (STATE_MENU_ENCODER        == machineState) {									    // event == EVENT_ROTATE_CW
      if (position < ENCODER_MENU_ELEMENTS - 1) {                        
        position++;
        MenuDown(currentMenu);
      }
    } else if (STATE_MENU_FONT           == machineState) {									    // event == EVENT_ROTATE_CW
      if (position < FONT_MENU_ELEMENTS - 1) {                        
        position++;
        MenuDown(currentMenu);
      }
    } else if (STATE_MENU_ORIENT         == machineState) {									    // event == EVENT_ROTATE_CW
      if (position < ORIENT_MENU_ELEMENTS - 1) {                        
        position++;
        MenuDown(currentMenu);
      }
    } else if (STATE_MENU_SHOW_GEN_PW_SZ == machineState) {									    // event == EVENT_ROTATE_CW
      if (position < GEN_PW_SIZE_MENU_ELEMENTS - 1) {                        
        position++;
        MenuDown(currentMenu);
      }
    } else if (STATE_MENU_INT_CHAR_PAUSE == machineState) {									    // event == EVENT_ROTATE_CW
      if (position < CHAR_DELAY_MENU_ELEMENTS - 1) {                        
        position++;
        MenuDown(currentMenu);
      }
    } else if (STATE_MENU_RGB_INTENSITY  == machineState) {									    // event == EVENT_ROTATE_CW
      if (position < RGB_INTENSITY_MENU_ELEMENTS - 1) {                         
        position++;
        MenuDown(currentMenu);
      }
    } else if (STATE_MENU_LOGOUT_TIMEOUT == machineState) {									    // event == EVENT_ROTATE_CW
      if (position < LOGOUT_TIMEOUT_MENU_ELEMENTS - 1) {                        
        position++;
        MenuDown(currentMenu);
      }
    } else if (STATE_EDIT_STYLE  == machineState) {									            // event == EVENT_ROTATE_CW
      if (position < STYLE_MENU_ELEMENTS - 1) {                        
        position++;
        MenuDown(currentMenu);
      }
    } else if ((STATE_SEARCH_FAVORITES     == machineState) ||									// event == EVENT_ROTATE_CW
               (STATE_SEARCH_WORK          == machineState) ||
               (STATE_SEARCH_PERSONAL      == machineState) ||
               (STATE_SEARCH_HOME          == machineState) ||
               (STATE_SEARCH_SCHOOL        == machineState) ||
               (STATE_SEARCH_FINANCIAL     == machineState) ||
               (STATE_SEARCH_MAIL          == machineState) ||
               (STATE_SEARCH_CUSTOM        == machineState)) {     
      acctPosition = getNextPtr(acctPosition);
      while ( (acctPosition != INITIAL_MEMORY_STATE_BYTE) &&
             !(readGroupFromEEprom(acctPosition) & groupFilter) ) {
        //position = acctPosition;
        acctPosition = getNextPtr(acctPosition);
      }
      if (acctPosition != INITIAL_MEMORY_STATE_BYTE) {                          // we found a member of the group
        position = acctPosition;
        readAcctFromEEProm(position, accountName);
        DisplayToItem((char *) accountName);
      } else {                                                                  // we reached the end of the linked list
        acctPosition = position;                                                // set acctPosition back to the last account found belonging to the group
      }
      event = EVENT_NONE;
    } else if (STATE_FIND_ACCOUNT == machineState) {     											  // event == EVENT_ROTATE_CW
      uint8_t nextPos = getNextPtr(position);
      if (nextPos != INITIAL_MEMORY_STATE_BYTE) {
        position = nextPos;
      }
      acctPosition = position;
      readAcctFromEEProm(acctPosition, accountName);
      DisplayToItem((char *) accountName);
    } else if ((STATE_CONFIRM_BACK_EEPROM == machineState ) || 								  // event == EVENT_ROTATE_CW
               (STATE_CONFIRM_RESTORE     == machineState ) ||
               (STATE_CONFIRM_FIX_CORRUPT == machineState ) ||
               (STATE_CONFIRM_RESET       == machineState ) ||
               (STATE_CONFIRM_DEL_ACCT    == machineState ) ||
               (STATE_CONFIRM_IMP_KP_CSV  == machineState ) ||
               (STATE_CONFIRM_IMP_PP_CSV  == machineState ) ||
               (STATE_CONFIRM_IMP_CP_CSV  == machineState )) {
      position = !position;
      ShowChar(confirmChars[position], POS_Y_N_CONFIRM);
    } else if (STATE_MENU_SETTINGS == machineState) {											      // event == EVENT_ROTATE_CW
      if (position < SETTINGS_MENU_ELEMENTS - 1) {                              // prevent scrolling past the last item on the menu
        position++;
        MenuDown(currentMenu);                                                  // move one position down the current menu
        setHelpOnSettingsMenu(position);
      }
    } else if (STATE_MENU_FILE == machineState) {																// event == EVENT_ROTATE_CW
      if (position < FILE_MENU_ELEMENTS - 1) {                                  // prevent scrolling past the last item on the menu
        position++;
        MenuDown(currentMenu);                                                  // move one position down the current menu
      }
    } else if (STATE_MENU_GROUPS == machineState) {															// event == EVENT_ROTATE_CW
      if (position < GROUP_MENU_ELEMENTS - 1) {                                 // prevent scrolling past the last item on the menu
				DisplayToItem((char *) (groupMenu + (++position)));
      }
    } else if (STATE_MENU_DEFINE_GROUPS == machineState) {											// event == EVENT_ROTATE_CW
      if (position < GROUP_EDIT_MENU_ELEMENTS - 1) {                            // prevent scrolling past the last item on the menu
        position++;
        MenuDown(currentMenu);                                                  // move one position down the current menu
      }
		}
    event = EVENT_NONE;                                                         // to prevent infinite looping
    
  } else if (event == EVENT_ROTATE_CC) {                                        // scroll backward through something depending on state...
    if (STATE_SHOW_MAIN_MENU == machineState) {
      if (position > FIND_FAVORITE) {                                           // don't show the Master Password menu item after successful authentication
        position--;
        MenuUp(currentMenu);
      }
    } else if ((STATE_ENTER_MASTER  == machineState ) ||                    		// EVENT_ROTATE_CC
               (STATE_EDIT_ACCOUNT  == machineState ) ||
//             (STATE_EDIT_STYLE    == machineState ) ||
               (STATE_EDIT_USERNAME == machineState ) ||
               (STATE_EDIT_PASSWORD == machineState ) ||
               (STATE_EDIT_WEBSITE  == machineState ) ||
               (STATE_CHANGE_MASTER == machineState ) ||
							 (STATE_EDIT_GROUP_1 	== machineState	) ||
							 (STATE_EDIT_GROUP_2 	== machineState	) ||
							 (STATE_EDIT_GROUP_3 	== machineState	) ||
							 (STATE_EDIT_GROUP_4 	== machineState	) ||
							 (STATE_EDIT_GROUP_5 	== machineState	) ||
							 (STATE_EDIT_GROUP_6 	== machineState	) ||
							 (STATE_EDIT_GROUP_7 	== machineState	)) {
      if (position > 0) {
        position--;
      }
      char charToPrint = allChars[position];
      ShowChar(charToPrint, enterPosition);
    } else if (STATE_SEND_CREDS_MENU == machineState ){
      if (position > 0) {
        position--;
        MenuUp(currentMenu);
        setHelpOnSendCredsMenu(position);
      }
    } else if (STATE_EDIT_CREDS_MENU == machineState){
      if (position > 0) {
        position--;
        MenuUp(currentMenu);
        SwitchRotatePosition(position);
        setHelpOnEditCredsMenu(position);
      }
    } else if (STATE_MENU_FIND_BY_GROUP   == machineState) {                    // EVENT_ROTATE_CC
			if (position > 0) {
				DisplayToItem((char *) (groupMenu + (--position)));
			}
    } else if ((STATE_KEY_ON_OFF_MENU     == machineState) ||
               (STATE_SHOW_PW_ON_OFF_MENU == machineState) ||
               (STATE_DECOY_ON_OFF_MENU   == machineState)   ) {                // EVENT_ROTATE_CC
      position = !position;                                                     // flip from 0 to 1 or from 1 to 0
      ShowMenu(position, currentMenu);
    } else if ((STATE_MENU_LOGIN_ATTEM    == machineState) ||
               (STATE_MENU_RGB_INTENSITY  == machineState) ||
               (STATE_MENU_LOGOUT_TIMEOUT == machineState) ||
               (STATE_MENU_KEYBOARD       == machineState) ||
               (STATE_MENU_ENCODER        == machineState) ||
               (STATE_MENU_FONT           == machineState) ||
               (STATE_MENU_ORIENT         == machineState) ||
               (STATE_MENU_SHOW_GEN_PW_SZ == machineState) ||
               (STATE_MENU_INT_CHAR_PAUSE == machineState) ||
               (STATE_EDIT_STYLE          == machineState)) {                   // EVENT_ROTATE_CC
      if (position > 0) {
        position--;
        MenuUp(currentMenu);
      }
    } else if ((STATE_SEARCH_FAVORITES     == machineState) ||
               (STATE_SEARCH_WORK          == machineState) ||
               (STATE_SEARCH_PERSONAL      == machineState) ||
               (STATE_SEARCH_HOME          == machineState) ||
               (STATE_SEARCH_SCHOOL        == machineState) ||
               (STATE_SEARCH_FINANCIAL     == machineState) ||
               (STATE_SEARCH_MAIL          == machineState) ||
               (STATE_SEARCH_CUSTOM        == machineState)) {                  // EVENT_ROTATE_CC     
      acctPosition = getPrevPtr(acctPosition);
      while ( (acctPosition != INITIAL_MEMORY_STATE_BYTE) &&
             !(readGroupFromEEprom(acctPosition) & groupFilter) ) {             // 
        acctPosition = getPrevPtr(acctPosition);
      }
      if (acctPosition != INITIAL_MEMORY_STATE_BYTE) {                          // we found a favorite
        position = acctPosition;
        readAcctFromEEProm(position, accountName);
        DisplayToItem((char *) accountName);
      } else {                                                                  // we reached the beginning of the linked list
        acctPosition = position;                                                // set acctPosition back to the last known member of the group
      }
      event = EVENT_NONE;
    } else if (STATE_FIND_ACCOUNT == machineState) {                            // EVENT_ROTATE_CC
      uint8_t prevPos = getPrevPtr(position);
      if (prevPos != INITIAL_MEMORY_STATE_BYTE) {
        position = prevPos;
      }
      acctPosition = position;
      readAcctFromEEProm(acctPosition, accountName);
      DisplayToItem((char *) accountName);
    } else if ((STATE_CONFIRM_BACK_EEPROM == machineState ) || 
               (STATE_CONFIRM_RESTORE     == machineState ) ||
               (STATE_CONFIRM_FIX_CORRUPT == machineState ) ||
               (STATE_CONFIRM_RESET       == machineState ) ||
               (STATE_CONFIRM_DEL_ACCT    == machineState ) ||
               (STATE_CONFIRM_IMP_KP_CSV  == machineState ) ||
               (STATE_CONFIRM_IMP_PP_CSV  == machineState ) ||
               (STATE_CONFIRM_IMP_CP_CSV  == machineState )) {                  // EVENT_ROTATE_CC
      if (position == 1) {                                                      // roll through the two options, N and Y
        position = 0;
      } else {
        position = 1; 
      }
      ShowChar(confirmChars[position], POS_Y_N_CONFIRM);
    } else if (STATE_MENU_SETTINGS == machineState) {                           // EVENT_ROTATE_CC
      if (position > 0) {                                                       // 
        position--;
        MenuUp(currentMenu);
        setHelpOnSettingsMenu(position);
      }
    } else if (STATE_MENU_FILE == machineState) {                               // EVENT_ROTATE_CC
      if (position > 0) {
        position--;
        MenuUp(currentMenu);
      }
    } else if (STATE_MENU_GROUPS == machineState) {                             // EVENT_ROTATE_CC
			if (position > 0) {
				DisplayToItem((char *) (groupMenu + (--position)));
			}
    } else if (STATE_MENU_DEFINE_GROUPS == machineState) {
      if (position > 0) {                            														// prevent scrolling past the last item on the menu
        position--;
        MenuUp(currentMenu);              	                                    // move one position down the current menu
      }
    } 
    event = EVENT_NONE;

  } else if (event == EVENT_SINGLE_CLICK) {                                     // EVENT_SINGLE_CLICK
    if (oledDim) DimDisplay(false);
    if (STATE_SHOW_MAIN_MENU == machineState) {
      switch(position) {
        case ENTER_MASTER_PASSWORD:                                             // Enter master password
          setupStateEnterMasterPassword();
          break;
        case FIND_FAVORITE:
          if(acctCount>0) {                                                     // if acctCount is not > 0 then there are not accounts to find
            position = headPosition; 
            acctPosition = headPosition;
            uint16_t i; i = 0;                                                  // TODO: this should be uint8_t
            while ( (acctPosition != INITIAL_MEMORY_STATE_BYTE    ) &&
                   !(readGroupFromEEprom(acctPosition) & FAVORITES) && 
                    ( i++ <= CREDS_ACCOMIDATED                    )   ) {       // to stop a suspected infinite loop when there are no favorites
              acctPosition = getNextPtr(acctPosition);
            }
            if (i > CREDS_ACCOMIDATED) {
              DisplayToError("ERR: 032");
            }
            if (acctPosition != INITIAL_MEMORY_STATE_BYTE) {                    // we found a favorite
              position = acctPosition;
              machineState = STATE_SEARCH_FAVORITES;
              groupFilter = FAVORITES;                                          // we only want to see favorite and what ever else is in the filter here
              ShowMenu(FIND_FAVORITE, mainMenu, "   Find Favorite    ");
              readAcctFromEEProm(position, accountName);
              DisplayToItem((char *) accountName);
              DisplayToHelp("Select an account.");
            }
          }
          event = EVENT_NONE;
          break;
        case FIND_ACCOUNT:                                                      // Find account
          if(acctCount>0) {                                                     // if acctCount is not > 0 then there are not accounts to find
            addFlag = false;
            switchToFindAcctMenu();
            DisplayToHelp("Select an account.");
          } else {
            BlankLine4();
            event = EVENT_NONE;
          }
          break;
        case FIND_BY_GROUP:
          if(acctCount>0) {                                                     // if acctCount is not > 0 then there are not accounts to find
            addFlag = false;
            position = 0;
            switchFindByGroup();
          } else {
            event = EVENT_NONE;
            BlankLine4();
          }
          break;
        case EDIT_VIA_COMPUTER:                                                 // Edit credentials via the python application
          machineState = STATE_FEED_SERIAL_DATA;
          DisplayToMenu(  " Edit via Computer ");
          DisplayToItem(  " Long Click Exits  ");
          DisplayToHelp("Edit PasswordPumpGUI");
          EnableInterrupts();
          Serial.begin(BAUD_RATE);
          attachCommandCallbacks();
          event = EVENT_NONE;
          int counter; counter = 0;																							// compile error if this is all done in one statement (?)
          setPurple();
          while ((machineState == STATE_FEED_SERIAL_DATA) &&
                 (event != EVENT_LONG_CLICK             )   ) {
            encoderButton.loop();                                               // polling for button press TODO: replace w/ interrupt
            cmdMessenger.feedinSerialData();                                    // Process incoming serial data, and perform callbacks
          }
          Serial.end();
          DisableInterrupts();
          setGreen();
          break;
        case ADD_ACCOUNT:                                                       // Add account
          addFlag = true;                                                       // necessary for when we return to the main menu
          acctPosition = getNextFreeAcctPos();                                  // get the position of the next EEprom location for account name marked empty.
          if (acctPosition != INITIAL_MEMORY_STATE_BYTE) {                      // if we have not reached the end of the linked list
            username[0] = NULL_TERM;
            password[0] = NULL_TERM;
            website[0] = NULL_TERM;
            groups = 0;
            SetSaltAndKey(acctPosition);                                        // populate and save the salt, set the key with the salt and master password
            strcpy(accountName,"Account Name");                                 // Initialize the account name to "Add Account".  TODO: is this necessary?
            DisplayToItem((char *)accountName);                                 // Display the account name on the second line
            acctCount++;                                                        // add one to the count of accounts
          } else {
            BlankLine4();
            DisplayToError("ERR: 010");
            break;
          }
          switchToEditMenu();
          DisplayToHelp("Add the account.");
          break;
        case LOGOUT:                                                            // Logout  
          sendLockAndLogout();                                                  // Send Windows-l to computer
          event = EVENT_LOGOUT;                                                 // Trigger logout from PasswordPump
          break;
        case FILE_MENU_SEL:
          event = EVENT_SHOW_FILE_MENU;                                         // backup / restore / import files menu
          break;
        case FIX_CORRUPT_LIST:                                                  // Fix any corruption in the linked list
          event = EVENT_FIX_CORRUPTION;
          break;
        case SETTINGS:                                                          // show the settings menu
          event = EVENT_SHOW_SETTINGS_MENU;
          position = SETTINGS_SET_SHOW_PW;
          break;
        case FACTORY_RESET:                                                     // Reset
          event = EVENT_RESET;
          break;
        default:
          DisplayToError("ERR: 002");
          break;
      }
      if (event == EVENT_SINGLE_CLICK) {                                        // stop the infinite loop of single clicks
        event = EVENT_NONE;
      }
    } else if (STATE_FIND_ACCOUNT == machineState) {                            // Go to the send menu 
      switchToSendCredsMenu();
    } else if ((STATE_SEARCH_FAVORITES     == machineState) ||                  // EVENT_SINGLE_CLICK
               (STATE_SEARCH_WORK          == machineState) ||
               (STATE_SEARCH_PERSONAL      == machineState) ||
               (STATE_SEARCH_HOME          == machineState) ||
               (STATE_SEARCH_SCHOOL        == machineState) ||
               (STATE_SEARCH_FINANCIAL     == machineState) ||
               (STATE_SEARCH_MAIL          == machineState) ||
               (STATE_SEARCH_CUSTOM        == machineState)) {     
      switchToSendCredsMenu();
      DisplayToHelp("Click to send.");
    } else if (STATE_EDIT_CREDS_MENU == machineState) {                         // EVENT_SINGLE_CLICK
      enterPosition = 0;
      switch(position) {
        case EDIT_ACCT_NAME:                                                    // Enter account name
          if (addFlag) {                                                        // Prevent editing the account name except when adding the credentials. Editing
            DisplayToMenu(accountName);
            DisplayToItem("Edit Account");
            BlankLine3();
            DisplayToHelp("Enter account name.");
            EditAttribute(STATE_EDIT_ACCOUNT, DEFAULT_ALPHA_EDIT_POS);          // the account name in place doesn't work, it corrupts the linked list.
          } else {
            BlankLine4();
            DisplayToError("No edit acct name");
            event = EVENT_NONE;
          }
          break; 
        case EDIT_USERNAME:                                                     // Enter user name     
          DisplayToMenu(accountName);
          DisplayToItem("Edit User Name");
          BlankLine3();
          DisplayToHelp("Enter user name.");
          EditAttribute(STATE_EDIT_USERNAME, DEFAULT_ALPHA_EDIT_POS);
          break; 
        case EDIT_PASSWORD:                                                     // Enter Password   
          DisplayToMenu(accountName);
          DisplayToItem("Edit Password");
          BlankLine3();
          DisplayToHelp("Enter password.");
          EditAttribute(STATE_EDIT_PASSWORD, DEFAULT_ALPHA_EDIT_POS);
          break; 
        case EDIT_WEBSITE:                                                      // Enter URL
          DisplayToMenu(accountName);
          DisplayToItem("Edit URL");
          BlankLine3();
          DisplayToHelp("Enter site URL.");
          EditAttribute(STATE_EDIT_WEBSITE, DEFAULT_ALPHA_EDIT_POS);
          break;
        case EDIT_STYLE:
          switchToStyleMenu();
//        DisplayToMenu("0 = <RETURN>");
//        DisplayToItem("1 = <TAB>");
//        BlankLine3();
          DisplayToHelp("Specify the style.");
//        EditAttribute(STATE_EDIT_STYLE, DEFAULT_STYLE_EDIT_POS);
          break; 
        case EDIT_GROUPS:
          DisplayToMenu(accountName);
          DisplayToItem("Edit Groups");
          position = 0;
          switchToFindByGroup();
          break;
        case GENERATE_PASSWORD:                                                 // Automatic UUID enter password 
            ReadSaltAndSetKey(acctPosition);                                    // set the key for the following steps, decryption and encryption
            readOldPassFromEEProm(acctPosition, oldPassword);                   // read and decrypt the old password
            if (strlen(oldPassword) == 0) {                                     // if the old password is blank, move the current password to old password
              readPassFromEEProm(acctPosition, password);                       // read and decrypt the current password (doesn't set the key)
              memcpy(oldPassword, password, PASSWORD_SIZE);                     // copy the existing password to oldPassword
              char buffer[PASSWORD_SIZE];                                       // the destination for the encrypted old password
              encrypt32Bytes(buffer, oldPassword);                              // encrypt it before you write it
              eeprom_write_bytes(GET_ADDR_OLD_PASS(acctPosition), buffer, PASSWORD_SIZE);// write the current password to old password in EEprom
            }            
            generatePassword(password, getGenPasswordSize, true);                // put a UUID in the password char array, - 1 accomodates null terminator
            BlankLine2();
            machineState = STATE_EDIT_PASSWORD;                                 // pretend we're entering the password
            event = EVENT_LONG_CLICK;                                           // and trigger long click to write the password to eeprom.
            break;
        case SAVE_OLD_PASSWORD:
            memcpy(oldPassword, password, PASSWORD_SIZE);
            char buffer[PASSWORD_SIZE];
            encrypt32Bytes(buffer, oldPassword);
            eeprom_write_bytes(GET_ADDR_OLD_PASS(acctPosition), buffer, PASSWORD_SIZE);
            DisplayToStatus("Saved as old");
            event = EVENT_NONE;
            break;
        default:
            DisplayToError("ERR: 003");
            break;
      }
    } else if (STATE_MENU_DEFINE_GROUPS == machineState) {                  		// EVENT_SINGLE_CLICK
      enterPosition = 0;
      DisplayToHelp("Enter the group.");
      switch(position) {
        case EDIT_GROUP_1:                                                      // EVENT_SINGLE_CLICK          
          DisplayToItem(groupCategory_1);
          DisplayToMenu("Edit Group 1");
          BlankLine3();
          EditAttribute(STATE_EDIT_GROUP_1, DEFAULT_ALPHA_EDIT_POS);
          break; 
        case EDIT_GROUP_2:                                                      // EVENT_SINGLE_CLICK
          DisplayToItem(groupCategory_2);
          DisplayToMenu("Edit Group 2");
          BlankLine3();
          EditAttribute(STATE_EDIT_GROUP_2, DEFAULT_ALPHA_EDIT_POS);
          break; 
        case EDIT_GROUP_3:                                                      // EVENT_SINGLE_CLICK        
          DisplayToItem(groupCategory_3);
          DisplayToMenu("Edit Group 3");
          BlankLine3();
          EditAttribute(STATE_EDIT_GROUP_3, DEFAULT_ALPHA_EDIT_POS);
          break; 
        case EDIT_GROUP_4:                                                      // EVENT_SINGLE_CLICK     
          DisplayToItem(groupCategory_4);
          DisplayToMenu("Edit Group 4");
          BlankLine3();
          EditAttribute(STATE_EDIT_GROUP_4, DEFAULT_ALPHA_EDIT_POS);
          break; 
        case EDIT_GROUP_5:                                                      // EVENT_SINGLE_CLICK        
          DisplayToItem(groupCategory_5);
          DisplayToMenu("Edit Group 5");
          BlankLine3();
          EditAttribute(STATE_EDIT_GROUP_5, DEFAULT_ALPHA_EDIT_POS);
          break; 
        case EDIT_GROUP_6:                                                      // EVENT_SINGLE_CLICK       
          DisplayToItem(groupCategory_6);
          DisplayToMenu("Edit Group 6");
          BlankLine3();
          EditAttribute(STATE_EDIT_GROUP_6, DEFAULT_ALPHA_EDIT_POS);
          break; 
        case EDIT_GROUP_7:                                                      // EVENT_SINGLE_CLICK  
          DisplayToItem(groupCategory_7);
          DisplayToMenu("Edit Group 7");
          BlankLine3();
          EditAttribute(STATE_EDIT_GROUP_7, DEFAULT_ALPHA_EDIT_POS);
          break; 
        default:
            BlankLine4();
            DisplayToError("ERR: 043");
            break;
      }
    } else if (STATE_MENU_FIND_BY_GROUP == machineState) {                      // EVENT_SINGLE_CLICK
      uint8_t groups = read_eeprom_byte(GET_ADDR_GROUP(acctPosition));
      BlankLine4();
      switch (position) {
        case GROUP_FAVORITES:
          groups ^= FAVORITES;
          if (FAVORITES & groups) {
            DisplayToStatus("Added to FAVORITES");
          } else {
            DisplayToStatus("Removed FAVORITES");
          }
          break;
        case GROUP_WORK:                                                        // EVENT_SINGLE_CLICK
          groups ^= WORK;
          if (WORK & groups) {
					  char buffer[DISPLAY_BUFFER_SIZE] = "Added to ";
						strncat (buffer, groupCategory_1, DISPLAY_BUFFER_SIZE - strlen(buffer));
            DisplayToStatus(buffer);
          } else {
					  char buffer[DISPLAY_BUFFER_SIZE] = "Removed ";
						strncat (buffer, groupCategory_1, DISPLAY_BUFFER_SIZE - strlen(buffer));
            DisplayToStatus(buffer);
          }
          break;
        case GROUP_PERSONAL:                                                    // EVENT_SINGLE_CLICK
          groups ^= PERSONAL;
          if (PERSONAL & groups) {
					  char buffer[DISPLAY_BUFFER_SIZE] = "Added to ";
						strncat (buffer, groupCategory_2, DISPLAY_BUFFER_SIZE - strlen(buffer));
            DisplayToStatus(buffer);
          } else {
					  char buffer[DISPLAY_BUFFER_SIZE] = "Removed ";
						strncat (buffer, groupCategory_2, DISPLAY_BUFFER_SIZE - strlen(buffer));
            DisplayToStatus(buffer);
          }
          break;
        case GROUP_HOME:                                                        // EVENT_SINGLE_CLICK
          groups ^= HOME;
          if (HOME & groups) {
					  char buffer[DISPLAY_BUFFER_SIZE] = "Added to ";
						strncat (buffer, groupCategory_3, DISPLAY_BUFFER_SIZE - strlen(buffer));
            DisplayToStatus(buffer);
          } else {
					  char buffer[DISPLAY_BUFFER_SIZE] = "Removed ";
						strncat (buffer, groupCategory_3, DISPLAY_BUFFER_SIZE - strlen(buffer));
            DisplayToStatus(buffer);
          }
          break;
        case GROUP_SCHOOL:                                                      // EVENT_SINGLE_CLICK
          groups ^= SCHOOL;
          if (SCHOOL & groups) {
					  char buffer[DISPLAY_BUFFER_SIZE] = "Added to ";
						strncat (buffer, groupCategory_4, DISPLAY_BUFFER_SIZE - strlen(buffer));
            DisplayToStatus(buffer);
          } else {
					  char buffer[DISPLAY_BUFFER_SIZE] = "Removed ";
						strncat (buffer, groupCategory_4, DISPLAY_BUFFER_SIZE - strlen(buffer));
            DisplayToStatus(buffer);
          }
          break;
        case GROUP_FINANCIAL:                                                   // EVENT_SINGLE_CLICK
          groups ^= FINANCIAL;
          if (FINANCIAL & groups) {
					  char buffer[DISPLAY_BUFFER_SIZE] = "Added to ";
						strncat (buffer, groupCategory_5, DISPLAY_BUFFER_SIZE - strlen(buffer));
            DisplayToStatus(buffer);
          } else {
					  char buffer[DISPLAY_BUFFER_SIZE] = "Removed ";
						strncat (buffer, groupCategory_5, DISPLAY_BUFFER_SIZE - strlen(buffer));
            DisplayToStatus(buffer);
          }
          break;
        case GROUP_MAIL:                                                        // EVENT_SINGLE_CLICK
          groups ^= MAIL;
          if (MAIL & groups) {
					  char buffer[DISPLAY_BUFFER_SIZE] = "Added to ";
						strncat (buffer, groupCategory_6, DISPLAY_BUFFER_SIZE - strlen(buffer));
            DisplayToStatus(buffer);
          } else {
					  char buffer[DISPLAY_BUFFER_SIZE] = "Removed ";
						strncat (buffer, groupCategory_6, DISPLAY_BUFFER_SIZE - strlen(buffer));
            DisplayToStatus(buffer);
          }
          break;
        case GROUP_CUSTOM:                                                      // EVENT_SINGLE_CLICK
          groups ^= CUSTOM;
          if (CUSTOM & groups) {
					  char buffer[DISPLAY_BUFFER_SIZE] = "Added to ";
						strncat (buffer, groupCategory_7, DISPLAY_BUFFER_SIZE - strlen(buffer));
            DisplayToStatus(buffer);
          } else {
					  char buffer[DISPLAY_BUFFER_SIZE] = "Removed ";
						strncat (buffer, groupCategory_7, DISPLAY_BUFFER_SIZE - strlen(buffer));
            DisplayToStatus(buffer);
          }
          break;
        default:                                                                // EVENT_SINGLE_CLICK
          DisplayToError("ERR: 025");
          break;
      }
      writeGroup(acctPosition, groups);
      event = EVENT_NONE;
    } else if (STATE_MENU_GROUPS == machineState) {                             // EVENT_SINGLE_CLICK
      switchToFindByGroupMenu(position, true);
    } else if (STATE_EDIT_ACCOUNT == machineState) {                            // EVENT_SINGLE_CLICK
      enterAttributeChar(accountName, false);
    } else if (STATE_EDIT_USERNAME == machineState) {                           // EVENT_SINGLE_CLICK
      enterAttributeChar(username, false);
    } else if (STATE_EDIT_PASSWORD == machineState) {                           // EVENT_SINGLE_CLICK
      enterAttributeChar(password, true);
    } else if (STATE_EDIT_WEBSITE == machineState) {                            // EVENT_SINGLE_CLICK
      enterAttributeChar(website, false);
//  } else if (STATE_EDIT_STYLE == machineState) {                              // EVENT_SINGLE_CLICK
//    enterAttributeChar(style, false);
		} else if (STATE_EDIT_GROUP_1 == machineState) {
			enterAttributeChar(groupCategory_1, false);
		} else if (STATE_EDIT_GROUP_2 == machineState) {
			enterAttributeChar(groupCategory_2, false);
		} else if (STATE_EDIT_GROUP_3 == machineState) {
			enterAttributeChar(groupCategory_3, false);
		} else if (STATE_EDIT_GROUP_4 == machineState) {
			enterAttributeChar(groupCategory_4, false);
		} else if (STATE_EDIT_GROUP_5 == machineState) {
			enterAttributeChar(groupCategory_5, false);
		} else if (STATE_EDIT_GROUP_6 == machineState) {
			enterAttributeChar(groupCategory_6, false);
		} else if (STATE_EDIT_GROUP_7 == machineState) {
			enterAttributeChar(groupCategory_7, false);
    } else if ((STATE_KEY_ON_OFF_MENU     == machineState) ||                   // EVENT_SINGLE_CLICK
               (STATE_SHOW_PW_ON_OFF_MENU == machineState) ||
               (STATE_DECOY_ON_OFF_MENU   == machineState) ||
               (STATE_MENU_LOGIN_ATTEM    == machineState) ||
               (STATE_MENU_RGB_INTENSITY  == machineState) ||
               (STATE_MENU_LOGOUT_TIMEOUT == machineState) ||
               (STATE_MENU_KEYBOARD       == machineState) ||
               (STATE_MENU_ENCODER        == machineState) ||
               (STATE_MENU_FONT           == machineState) ||
               (STATE_MENU_ORIENT         == machineState) ||
               (STATE_MENU_SHOW_GEN_PW_SZ == machineState) ||
               (STATE_MENU_INT_CHAR_PAUSE == machineState) ||
               (STATE_EDIT_STYLE          == machineState)) {
      BlankLine4();
      switch (machineState) {                                                   // TODO: this is a weird way to do this... fix it.
        case STATE_KEY_ON_OFF_MENU:
          keyboardFlag = position;
          writeKeyboardFlag();
          DisplayToStatus("Keybrd Setting Saved");
          break;
        case STATE_SHOW_PW_ON_OFF_MENU:
          showPasswordsFlag = position;
          writeShowPasswordsFlag();
          DisplayToStatus("Show Password Saved");
          break;
        case STATE_DECOY_ON_OFF_MENU:
          decoyPassword = position;
          writeDecoyPWFlag();
          DisplayToStatus("Decoy Setting Saved");
          break;
        case STATE_MENU_LOGIN_ATTEM:
          switch (position) {
            case LOGIN_ATTEMPTS_3:
              loginAttempts = ATTEMPTS_3;
              DisplayToHelp("Saved 3 attempts.");
              break;
            case LOGIN_ATTEMPTS_5:
              loginAttempts = ATTEMPTS_5;
              DisplayToHelp("Saved 5 attempts.");
              break;
            case LOGIN_ATTEMPTS_10:
              loginAttempts = ATTEMPTS_10;
              DisplayToHelp("Saved 10 attempts.");
              break;
            case LOGIN_ATTEMPTS_25:
              loginAttempts = ATTEMPTS_25;
              DisplayToHelp("Saved 25 attempts.");
              break;
            default:
              loginAttempts = ATTEMPTS_DEFAULT;
              DisplayToHelp("Saved 10 attempts.");
              DisplayToError("ERR: 009");
              break;
          }
          writeLoginAttempts();
          DisplayToStatus("Max bad logins saved");
          break;
        case STATE_MENU_RGB_INTENSITY:                                          // EVENT_SINGLE_CLICK
          switch (position) {
            case RGB_INTENSITY_HIGH:
              RGBLEDIntensity = RGB_LED_HIGH;
              DisplayToHelp("Save HIGH intensity.");
              break;
            case RGB_INTENSITY_MED:
              RGBLEDIntensity = RGB_LED_MEDIUM;
              DisplayToHelp("Save MED intensity.");
              break;
            case RGB_INTENSITY_LOW:
              RGBLEDIntensity = RGB_LED_LOW;
              DisplayToHelp("Save LOW intensity.");
              break;
            case RGB_INTENSITY_OFF:
              RGBLEDIntensity = RGB_LED_OFF;
              DisplayToHelp("Saved no RGB LED.");
              break;
            default:
              RGBLEDIntensity = RGB_LED_DEFAULT;
              DisplayToHelp("Save MED intensity.");
              DisplayToError("ERR: 010");
              break;
          }
          writeRGBLEDIntensity();
          DisplayToStatus("RGB Intensity Saved");
          setGreen();
          break;
        case STATE_MENU_LOGOUT_TIMEOUT:                                         // EVENT_SINGLE_CLICK
          switch (position) {
            case LOGOUT_TIMEOUT_30:
              logoutTimeout = LOGOUT_TIMEOUT_VAL_30;
              DisplayToHelp("Saved 30 min timeout");
              break;
            case LOGOUT_TIMEOUT_60:
              logoutTimeout = LOGOUT_TIMEOUT_VAL_60;
              DisplayToHelp("Saved 60 min timeout");
              break;
            case LOGOUT_TIMEOUT_90:
              logoutTimeout = LOGOUT_TIMEOUT_VAL_90;
              DisplayToHelp("Saved 90 min timeout");
              break;
            case LOGOUT_TIMEOUT_120:
              logoutTimeout = LOGOUT_TIMEOUT_VAL_120;
              DisplayToHelp("Saved 2 hour timeout");
              break;
            case LOGOUT_TIMEOUT_240:
              logoutTimeout = LOGOUT_TIMEOUT_VAL_240;
              DisplayToHelp("Saved 4 hour timeout");
              break;
            case LOGOUT_TIMEOUT_1:
              logoutTimeout = LOGOUT_TIMEOUT_VAL_1;
              DisplayToHelp("Saved 1 min timeout");
              break;
            case LOGOUT_TIMEOUT_0:
              logoutTimeout = LOGOUT_TIMEOUT_VAL_0;
              DisplayToHelp("Saved never logout");
              break;
            default:
              logoutTimeout = 60;
              DisplayToHelp("Saved 60 min timeout");
              DisplayToError("ERR: 018");
              break;
          }
          writeLogoutTimeout();
          DisplayToStatus("Timeout Saved");
          break;
        case STATE_MENU_KEYBOARD:                                               // EVENT_SINGLE_CLICK
          originalKeyboardType = keyboardType;
          changeKeyboardAttempts += 1;
          if (changeKeyboardAttempts < 3) {                                     // To prevent a crash
            switch (position) {
              case KEYBOARD_CZECH:
                keyboardType = KEYBOARD_CZECH;
                if (keyboardType != originalKeyboardType) {
                  Keyboard.InitKeyboard(_asciimapCzech, _hidReportDescriptorCzech);
                  DisplayToHelp("Saved Czech keyboard.");
                }
                break;
              case KEYBOARD_DANISH:
                keyboardType = KEYBOARD_DANISH;
                if (keyboardType != originalKeyboardType) {
                  Keyboard.InitKeyboard(_asciimapDanish, _hidReportDescriptorDanish);
                  DisplayToHelp("Saved Danish keyboard.");
                }
                break;
              case KEYBOARD_FINNISH:
                keyboardType = KEYBOARD_FINNISH;
                if (keyboardType != originalKeyboardType) {
                  Keyboard.InitKeyboard(_asciimapFinnish, _hidReportDescriptorFinnish);
                  DisplayToHelp("Saved Finnish keybrd");
                }
                break;
              case KEYBOARD_FRENCH:
                keyboardType = KEYBOARD_FRENCH;
                if (keyboardType != originalKeyboardType) {
                  Keyboard.InitKeyboard(_asciimapFrench, _hidReportDescriptorFrench);
                  DisplayToHelp("Saved French keyboard.");
                }
                break;
              case KEYBOARD_GERMAN:
                keyboardType = KEYBOARD_GERMAN;
                if (keyboardType != originalKeyboardType) {
                  //setlocale(LC_ALL, "de_DE");                                 // Set local to Germany
                  Keyboard.InitKeyboard(_asciimapGerman, _hidReportDescriptorGerman);
                  DisplayToHelp("Saved German keybrd");
                }
                break;
              case KEYBOARD_NORWEGIAN:
                keyboardType = KEYBOARD_NORWEGIAN;
                if (keyboardType != originalKeyboardType) {
                  Keyboard.InitKeyboard(_asciimapNorwegian, _hidReportDescriptorNorwegian);
                  DisplayToHelp("Saved Norwegian.");
                }
                break;
              case KEYBOARD_SPANISH:
                keyboardType = KEYBOARD_SPANISH;
                if (keyboardType != originalKeyboardType) {
                  Keyboard.InitKeyboard(_asciimapSpanish, _hidReportDescriptorSpanish);
                  DisplayToHelp("Saved Spanish keybrd");
                }
                break;
              case KEYBOARD_SWEDISH:
                keyboardType = KEYBOARD_SWEDISH;
                if (keyboardType != originalKeyboardType) {
                  Keyboard.InitKeyboard(_asciimapSwedish, _hidReportDescriptorSwedish);
                  DisplayToHelp("Saved Swedish keybrd");
                }
                break;
              case KEYBOARD_UK:
                keyboardType = KEYBOARD_UK;
                if (keyboardType != originalKeyboardType) {
                  Keyboard.InitKeyboard(_asciimapUK, _hidReportDescriptorUK);
                  DisplayToHelp("Saved UK keyboard");
                }
                break;
              case KEYBOARD_US:
                keyboardType = KEYBOARD_US;
                if (keyboardType != originalKeyboardType) {
                  //setlocale(LC_ALL, "C");
                  Keyboard.InitKeyboard(_asciimapUS, _hidReportDescriptorUS);
                  DisplayToHelp("Saved US keyboard");
                }
                break;
              default:
                BlankLine4();
                DisplayToError("045");
                break;
            }
          } else {
            DisplayToHelp("Reset to switch");
            keyboardType = position;
          }
          writeKeyboardType();
          DisplayToStatus("Keyboard Saved.");
          break;
        case STATE_MENU_ENCODER:                                                // EVENT_SINGLE_CLICK
          switch (position) {
            case ENCODER_NORMAL:
              encoderType = ENCODER_NORMAL;
              rotaryPin1 = 9;
              rotaryPin2 = 7;
              DisplayToHelp("Saved normal encoder");
              break;
            case ENCODER_LEFTY:
              encoderType = ENCODER_LEFTY;
              rotaryPin1 = 7;
              rotaryPin2 = 9;
              DisplayToHelp("Saved lefty encoder");
              break;
            default:
              encoderType = ENCODER_NORMAL;                                    
              rotaryPin1 = 9;
              rotaryPin2 = 7;
              DisplayToHelp("Saved encoder");
              DisplayToError("ERR: 046");
              break;
          }
          writeEncoderType();
          DisplayToStatus("Encoder Saved.");
          break;
        case STATE_MENU_FONT:                                                   // EVENT_SINGLE_CLICK
          switch (position) {
            case FONT_ARIAL14:
              font = FONT_ARIAL14;
              oled.setFont(Arial14);
              DisplayToHelp("Saved Arial14.");
              break;
            case FONT_ARIAL_BOLD_14:
              font = FONT_ARIAL_BOLD_14;
              oled.setFont(Arial_bold_14);
              DisplayToHelp("Saved Arial_bold_14.");
              break;
            case FONT_CALLIBRI10:
              font = FONT_CALLIBRI10;
              oled.setFont(Callibri10);
              DisplayToHelp("Saved Callibri10.");
              break;
//          case FONT_FIXEDNUMS8X16:
//            font = FONT_FIXEDNUMS8X16;
//            oled.setFont(fixednums8x16);
//            break;
            case FONT_TIMESNEWROMAN13:
              font = FONT_TIMESNEWROMAN13;
              oled.setFont(TimesNewRoman13);
              DisplayToHelp("Saved TimesNewRoman");
              break;
            case FONT_ADAFRUIT5X7:
              font = FONT_ADAFRUIT5X7;
              oled.setFont(Adafruit5x7);
              DisplayToHelp("Saved Adafruit5x7.");
              break;
            case FONT_FONT5X7:
              font = FONT_FONT5X7;
              oled.setFont(font5x7);
              DisplayToHelp("Saved font5x7.");
              break;
            case FONT_LCD5X7:
              font = FONT_LCD5X7;
              oled.setFont(lcd5x7);
              DisplayToHelp("Saved lcd5x7.");
              break;
            case FONT_STANG5X7:
              font = FONT_STANG5X7;
              oled.setFont(Stang5x7);
              DisplayToHelp("Saved Stang5x7.");
              break;
            case FONT_SYSTEM5X7:
              font = FONT_SYSTEM5X7;
              oled.setFont(System5x7);
              DisplayToHelp("Saved System5x7.");
              break;
            default:
              font = FONT_ARIAL14;
              oled.setFont(Arial14);
              DisplayToError("ERR: 047");
              DisplayToHelp("Saved Arial14.");
              break;
          }
          writeFont();
          DisplayToStatus("Font Saved.");
          break;
        case STATE_MENU_ORIENT:                                                 // EVENT_SINGLE_CLICK
          switch (position) {
            case ORIENT_LEFTY:
              orientation = ORIENT_LEFTY;
              oled.displayRemap(ORIENT_LEFTY);
              DisplayToHelp("Saved lefty.");
              break;
            case ORIENT_RIGHTY:
              orientation = ORIENT_RIGHTY;
              oled.displayRemap(ORIENT_RIGHTY);
              DisplayToHelp("Saved righty.");
              break;
            default:
              orientation = DEFAULT_ORIENT;
              oled.displayRemap(DEFAULT_ORIENT);
              DisplayToError("ERR: 048");
              DisplayToHelp("Saved default.");
              break;
          }
          writeOrientation();
          DisplayToStatus("Orientation saved.");
          break;
        case STATE_MENU_SHOW_GEN_PW_SZ:                                         // EVENT_SINGLE_CLICK
          switch (position) {
            case GEN_PW_SIZE_8:
              generatedPasswordSize = GEN_PW_SIZE_8;
              DisplayToHelp("Saved size 8.");
              break;
            case GEN_PW_SIZE_10:
              generatedPasswordSize = GEN_PW_SIZE_10;
              DisplayToHelp("Saved size 10.");
              break;
            case GEN_PW_SIZE_16:
              generatedPasswordSize = GEN_PW_SIZE_16;
              DisplayToHelp("Saved size 16.");
              break;
            case GEN_PW_SIZE_24:
              generatedPasswordSize = GEN_PW_SIZE_24;
              DisplayToHelp("Saved size 24.");
              break;
            case GEN_PW_SIZE_31:
              generatedPasswordSize = GEN_PW_SIZE_31;
              DisplayToHelp("Saved size 31.");
              break;
            default:
              generatedPasswordSize = DEFAULT_GEN_PW_SIZE;
              DisplayToError("ERR: 058");
              DisplayToHelp("Saved default size.");
              break;
          }
          writeGenPwSize();
          DisplayToStatus("Password size saved.");
          break;
        case STATE_MENU_INT_CHAR_PAUSE:                                         // EVENT_SINGLE_CLICK
          switch (position) {
            case CHAR_DELAY_0:
              interCharPause = CHAR_DELAY_0;
              interCharPauseVal = CHAR_DELAY_VAL_0;
              DisplayToHelp("Saved delay 0.");
              break;
            case CHAR_DELAY_10:
              interCharPause = CHAR_DELAY_10;
              interCharPauseVal = CHAR_DELAY_VAL_10;
              DisplayToHelp("Saved delay 10.");
              break;
            case CHAR_DELAY_25:
              interCharPause = CHAR_DELAY_25;
              interCharPauseVal = CHAR_DELAY_VAL_25;
              DisplayToHelp("Saved delay 25.");
              break;
            case CHAR_DELAY_100:
              interCharPause = CHAR_DELAY_100;
              interCharPauseVal = CHAR_DELAY_VAL_100;
              DisplayToHelp("Saved delay 100.");
              break;
            case CHAR_DELAY_250:
              interCharPause = CHAR_DELAY_250;
              interCharPauseVal = CHAR_DELAY_VAL_250;
              DisplayToHelp("Saved delay 250.");
              break;
            default:
              interCharPause = DEFAULT_CHAR_DELAY;
              interCharPauseVal = CHAR_DELAY_VAL_0;
              DisplayToError("ERR: 059");
              DisplayToHelp("Saved delay 0.");
              break;
          }
          writeInterCharPause();
          DisplayToStatus("Intr chr pause saved");
          break;
        case STATE_EDIT_STYLE:                                                  // EVENT_SINGLE_CLICK
          switch (position) {
            case STYLE_RETURN:
              strcpy(style,"0");
              DisplayToHelp("Saved RETURN.");
              break;
            case STYLE_TAB:
              strcpy(style,"1");
              DisplayToHelp("Saved TAB.");
              break;
            case STYLE_TAB_TAB_RETURN:
              strcpy(style,"2");
              DisplayToHelp("Saved TAB TAB RTN.");
              break;
            default:
              strcpy(style,"1");
              DisplayToError("ERR: 055");
              DisplayToHelp("Saved default.");
              break;
          }
          eeprom_write_bytes(GET_ADDR_STYLE(acctPosition), style, STYLE_SIZE);
          DisplayToStatus("Style saved.");
          break;
        default:                                                                // EVENT_SINGLE_CLICK
          DisplayToError("ERR: 001");
          break;
      }
      event = EVENT_NONE;
    } else if (STATE_SEND_CREDS_MENU == machineState){                          // EVENT_SINGLE_CLICK
      setPurple();
      event = EVENT_NONE;
      BlankLine4();
      switch(position) {
         case SEND_USER_AND_PASSWORD:                                                                
            sendUsernameAndPassword();                                          // Send the user name and password
            DisplayToMenu(accountName);
            DisplayToStatus("Sent user/pass");
            break; 
         case SEND_PASSWORD:                                                    
            sendPassword();                                                     // Send the password
            delayNoBlock(PW_RTN_DELAY);
            readStyleFromEEProm(acctPosition, style);                           // read the style from EEprom
            if (strcmp(style,"2") == 0) {
              sendTAB();                                                        // Send a <TAB>
            }
            sendRTN();                                                          // Send the <CR> carriage return
            DisplayToMenu(accountName);
            DisplayToStatus("Sent password");
            break;
         case SEND_USERNAME:                                                    
            sendUsername();                                                     // Send the user name
            DisplayToMenu(accountName);
            DisplayToStatus("Sent username");
            break;
         case SEND_PASSWORD_NO_RET:
            sendPassword();                                                     // Send the password
            DisplayToMenu(accountName);
            DisplayToStatus("Sent password");
            break;
         case SEND_WEBSITE:                                                    
            sendWebSite();                                                      // Send the website url
            DisplayToMenu(accountName);
            DisplayToStatus("Sent URL");
            break;
         case SEND_ACCOUNT:                                                     // Send the account name
            sendAccount();
            DisplayToMenu(accountName);
            DisplayToStatus("Sent acct name");
            break;
         case EDIT_ACCOUNT:                                                     // Show the enter account menu
            switchToEditMenu();
            DisplayToHelp("Select what to edit.");
            break;
         case DELETE_ACCOUNT:                                                   // Delete account
            event = EVENT_DELETE_ACCT;
            break;
         case SEND_OLD_PASSWORD:                                                // Send the account name
            sendOldPassword();
            DisplayToMenu(accountName);
            DisplayToStatus("Sent old pass");
            break;
         default:
            DisplayToError("ERR: 004B");
            break;
      }
      setGreen();
    } else if (STATE_ENTER_MASTER == machineState) {                            // EVENT_SINGLE_CLICK
      masterPassword[enterPosition] = allChars[position];
      masterPassword[enterPosition + 1] = NULL_TERM;                            // push the null terminator out ahead of the last char in the string
      if (showPasswordsFlag) {
        line3DispBuff[enterPosition] = allChars[position];
      } else {
        line3DispBuff[enterPosition] = '*';
      }
      line3DispBuff[enterPosition + 1] = NULL_TERM;                             // push the null terminator out ahead of the last char in the string
      DisplayBuffer3();                                                         // Show what's been entered so far.
      if (enterPosition < DISPLAY_BUFFER_SIZE) enterPosition++;                 // don't increment enterPosition beyond the space that's allocated for the associated array
      event = EVENT_NONE;
    } else if (STATE_CHANGE_MASTER == machineState) {                           // EVENT_SINGLE_CLICK
      newPassword[enterPosition] = allChars[position];
      newPassword[enterPosition + 1] = NULL_TERM;                               // push the null terminator out ahead of the last char in the string
      if (showPasswordsFlag) {
        line3DispBuff[enterPosition] = allChars[position];                      // Show what's been entered so far.
      } else {
        line3DispBuff[enterPosition] = '*';                                     // Mask the password  when it's displayed.
      }
      line3DispBuff[enterPosition + 1] = NULL_TERM;                             // push the null terminator out ahead of the last char in the string
      DisplayBuffer3();
      if (enterPosition < DISPLAY_BUFFER_SIZE) enterPosition++;                 // don't increment enterPosition beyond the space that's allocated for the associated array
      event = EVENT_NONE;
    } else if (STATE_CONFIRM_BACK_EEPROM == machineState) {                     // EVENT_SINGLE_CLICK
      if (confirmChars[position] == 'Y') {
        DisplayToHelp("Backing up EEprom...");
        CopyEEPromToBackup();
        DisplayToHelp("Finished backup.");
      }
      position = FIND_FAVORITE;
      event = EVENT_SHOW_MAIN_MENU;
    } else if (STATE_CONFIRM_RESTORE == machineState) {                         // EVENT_SINGLE_CLICK
      if (confirmChars[position] == 'Y') {
        DisplayToHelp("Restoring from backup.");
        RestoreEEPromBackup();
        DisplayToHelp("Finished restore.");
      }
      position = FIND_FAVORITE;
      event = EVENT_SHOW_MAIN_MENU;
    } else if (STATE_CONFIRM_FIX_CORRUPT == machineState) {
      if (confirmChars[position] == 'Y') {
        DisplayToHelp("Fixing corruption...");
        FixCorruptLinkedList();
        DisplayToHelp("Corruption fixed.");
      }
      event = EVENT_SHOW_MAIN_MENU;
    } else if (STATE_CONFIRM_RESET == machineState) {                           // EVENT_SINGLE_CLICK
      if (confirmChars[position] == 'Y') {
        DisplayToHelp("Factory resetting.");
        FactoryReset();
      } else {
        BlankLine4();
        position = FIND_FAVORITE;
        event = EVENT_SHOW_MAIN_MENU;
      }
    } else if (STATE_CONFIRM_DEL_ACCT == machineState) {                        // EVENT_SINGLE_CLICK
      if (confirmChars[position] == 'Y') {
        DisplayToHelp("Deleting account.");
        deleteAccount(acctPosition);
        DisplayToHelp("Account deleted.");
      }
      switchToFindAcctMenu();
      DisplayToHelp("Select an account.");
    //} else if (STATE_CONFIRM_IMP_KP_CSV == machineState) {                    // EVENT_SINGLE_CLICK
    //  if (confirmChars[position] == 'Y') {
    //    importKeePassCSV();
    //  }
    //  event = EVENT_SHOW_MAIN_MENU;
    //} else if (STATE_CONFIRM_IMP_PP_CSV == machineState) {                    // EVENT_SINGLE_CLICK
    //  if (confirmChars[position] == 'Y') {
    //    RestoreFromPPCVSFile();
    //  }
    //  event = EVENT_SHOW_MAIN_MENU;
    //} else if (STATE_CONFIRM_IMP_CP_CSV == machineState) {                    // EVENT_SINGLE_CLICK
    //  if (confirmChars[position] == 'Y') {
    //    ImportChromeExportFile();
    //  }
    //  event = EVENT_SHOW_MAIN_MENU;
    } else if (STATE_MENU_SETTINGS == machineState) {                           // EVENT_SINGLE_CLICK
      switch (position) {
        case SETTINGS_SET_KEYBOARD:
          machineState = STATE_KEY_ON_OFF_MENU;
          event = EVENT_SHOW_OFF_ON_MENU;
          break;
        case SETTINGS_SET_SHOW_PW:
          machineState = STATE_SHOW_PW_ON_OFF_MENU;
          event = EVENT_SHOW_OFF_ON_MENU;
          break;
        case SETTINGS_SET_DECOY:
          machineState = STATE_DECOY_ON_OFF_MENU;
          event = EVENT_SHOW_OFF_ON_MENU;
          break;
        case SETTINGS_SET_RGB_INT:
          machineState = STATE_MENU_RGB_INTENSITY;
          event = EVENT_SHOW_RGB_INT_MENU;
          break;
        case SETTINGS_SET_TIMEOUT:
          machineState = STATE_MENU_LOGOUT_TIMEOUT;
          event = EVENT_SHOW_LOG_TIME_MENU;
          break;
        case SETTINGS_GROUP_DEFINITION:
          event = EVENT_SHOW_GROUP_DEF_MENU;
          break;
        case SETTINGS_CHANGE_MASTER:
          event = EVENT_CHANGE_MASTER;
          break;
        case SETTINGS_SET_LOGIN_ATTEM:
          machineState = STATE_MENU_LOGIN_ATTEM;
          event = EVENT_SHOW_LG_ATTEM_MENU;
          break;
        case SETTINGS_KEYBOARD_LANG:
          machineState = STATE_MENU_KEYBOARD;
          event = EVENT_SHOW_KEYBOARD_MENU;
          break;
        case SETTINGS_ENCODER_TYPE:
          machineState = STATE_MENU_ENCODER;
          event = EVENT_SHOW_ENCODER_MENU;
          break;
        case SETTINGS_FONT:
          machineState = STATE_MENU_FONT;
          event = EVENT_SHOW_FONT_MENU;
          break;
        case SETTINGS_ORIENTATION:
          machineState = STATE_MENU_ORIENT;
          event = EVENT_SHOW_ORIENT_MENU;
          break;
        case SETTINGS_GEN_PW_SIZE:
          machineState = STATE_MENU_SHOW_GEN_PW_SZ;
          event = EVENT_SHOW_GEN_PW_SZ_MENU;
          break;
        case SETTINGS_CHAR_DELAY:
          machineState = STATE_MENU_INT_CHAR_PAUSE;
          event = EVENT_SHOW_INT_CHAR_MENU;
          break;
        default:
          BlankLine4();
          DisplayToError("ERR: 005");
          break;
      }
    } else if (STATE_MENU_FILE == machineState) {                               // EVENT_SINGLE_CLICK
      switch (position) {
        case FILE_BACKUP_EEPROM:                                                // Backup EEprom
          event = EVENT_BACKUP;
          break;
        //case FILE_BACKUP_ALL:                                                 // Send all creds out through the keyboard for capture in a text editor
        //  event = EVENT_BACKUP_TO_FILE;
        //  break;
        case FILE_RESTORE_BACKUP:                                               // Restore the backup EEprom to the primary
          event = EVENT_RESTORE;
          break;
        //case FILE_IMPORT_PP_CSV:                                              // Import the PPEXPORT.csv file into EEProm
        //  event = EVENT_IMPORT_PP_CSV;
        //  break;
        //case FILE_IMPORT_CP_CSV:                                              // Import the CPEXPORT.csv file into EEProm
        //  event = EVENT_IMPORT_CP_CSV;
        //  break;
        //case FILE_IMPORT_KEEPASS_CSV:                                         // Import the KeePassExp.csv file into EEProm
        //  event = EVENT_IMPORT_KEEPASS_CSV;
        //  break;
        default:
          DisplayToError("ERR: 038");                                           // invalid position in file menu
          event = EVENT_NONE;
          break;
      }
    } else {
      DisplayToError("ERR: 028");                                               // invalid state during event single click
    }

  } else if (event == EVENT_LONG_CLICK) {                                       // jump up / back to previous menu 
    BlankLine4();
    if (STATE_ENTER_MASTER == machineState){
      //ReadFromSerial( masterPassword,                                         // Uncomment this if you want to enable entering the master password via PC keyboard
      //                MASTER_PASSWORD_SIZE,
      //                mainMenu[ENTER_MASTER_PASSWORD]);
      authenticated = authenticateMaster(masterPassword);                       // authenticateMaster writes to masterPassword
      if (authenticated) {
        PopulateGlobals();
        position = FIND_FAVORITE;
        machineState = STATE_SHOW_MAIN_MENU;
        DisplayToMenu("      Actions       ");                                  // Main menu heading
        ShowMenu(position, currentMenu);
        char bufferCount[4];
        itoa(acctCount, bufferCount, 10);                                       // convert account count to a string and put it in buffer.
        strcpy(line4DispBuff, bufferCount);
        strcat(line4DispBuff, " accounts");                                     // display the account count on the display
        DisplayBuffer();
        event = EVENT_NONE;
      } else {
        if (loginFailures >= loginAttempts) {                                   // have we exhausted our attempts?
          FactoryReset();                                                       // bypass confirm choice, go directly to FactoryReset.
        } else {  
          position = 0;
          machineState = STATE_SHOW_MAIN_MENU;
          ShowMenu(position, currentMenu, "       Login        ");
          char buffer[4];
          itoa(loginFailures, buffer, 10);                                      // convert login failures to a string and put it in buffer.
          strcpy(line3DispBuff, buffer);
          strcat(line3DispBuff, " failure(s)");
          DisplayBuffer3();
          event = EVENT_NONE;
        }
      }
    } else if (STATE_CHANGE_MASTER == machineState) {
      ReadFromSerial(newPassword, MASTER_PASSWORD_SIZE, (char *)settingsMenu[SETTINGS_CHANGE_MASTER]);
      uint8_t pos = 0;
      while (newPassword[pos++] != NULL_TERM);                                  // make sure the new password is 16 chars long, pad with NULL_TERM
      while (pos < MASTER_PASSWORD_SIZE) newPassword[pos++] = NULL_TERM;        // "           "              "
      if (strlen(newPassword) > 0) {                                            // only change the master password if a new password was entered
        ChangeMasterPassword(newPassword);
        ShowSuspend();
        event = EVENT_SUSPEND;
      } else {
        DisplayToHelp("Pass not > 0 char");
        position = SETTINGS;
        BlankLine2();
        BlankLine3();
        event = EVENT_SHOW_MAIN_MENU;
      }
    } else if (STATE_EDIT_ACCOUNT == machineState) {                            // EVENT_LONG_CLICK
      ProcessAttributeInput(  accountName,
                              ACCOUNT_SIZE,
                              enterMenu[EDIT_ACCT_NAME],
                              EDIT_USERNAME,
                              true,
                              GET_ADDR_ACCT(acctPosition) );
  
    } else if (STATE_EDIT_USERNAME == machineState) {                           // EVENT_LONG_CLICK
      ProcessAttributeInput(  username,
                              USERNAME_SIZE,
                              enterMenu[EDIT_USERNAME],
                              EDIT_PASSWORD,
                              false,
                              GET_ADDR_USER(acctPosition) );
    } else if (STATE_EDIT_PASSWORD == machineState) {                           // EVENT_LONG_CLICK
      ProcessAttributeInput(  password,
                              PASSWORD_SIZE,
                              enterMenu[EDIT_PASSWORD],
                              EDIT_WEBSITE,
                              false,
                              GET_ADDR_PASS(acctPosition) );
    } else if (STATE_EDIT_WEBSITE == machineState) {                            // EVENT_LONG_CLICK
      ReadFromSerial(website, WEBSITE_SIZE, (char *)enterMenu[EDIT_WEBSITE]);
      uint8_t pos = 0;
      while (website[pos++] != NULL_TERM);                                      // make sure the website is 96 chars long, pad with NULL_TERM
      while (pos < WEBSITE_SIZE) website[pos++] = NULL_TERM;                    // "           "              "
      char buffer[WEBSITE_SIZE];
      encrypt96Bytes(buffer, website);
      eeprom_write_bytes(GET_ADDR_WEBSITE(acctPosition), buffer, WEBSITE_SIZE);
      position = EDIT_STYLE;
      event = EVENT_SHOW_EDIT_MENU;   
      BlankLine2();
    } else if (STATE_EDIT_STYLE == machineState) {                              // EVENT_LONG_CLICK
      position = EDIT_STYLE;
      event = EVENT_SHOW_EDIT_MENU;
    } else if (STATE_EDIT_CREDS_MENU == machineState){                          // go back to send creds menu or main menu,depending on how you got here.
      if (!addFlag) {
        switchToSendCredsMenu();
      } else {
        event = EVENT_SHOW_MAIN_MENU;
        BlankLine2();
        BlankLine3();
        position = ADD_ACCOUNT;
      }
    } else if (STATE_SEND_CREDS_MENU == machineState){                          // EVENT_LONG_CLICK
      DisplayToHelp("Select account.");
			switch (groupFilter) {
        case FAVORITES:
          switchToFindByGroupMenu(GROUP_FAVORITES, false);
          break;
        case WORK:
          switchToFindByGroupMenu(GROUP_WORK, false);
          break;
        case PERSONAL:
          switchToFindByGroupMenu(GROUP_PERSONAL, false);
          break;
        case HOME:
          switchToFindByGroupMenu(GROUP_HOME, false);
          break;
        case SCHOOL:
          switchToFindByGroupMenu(GROUP_SCHOOL, false);
          break;
        case FINANCIAL:
          switchToFindByGroupMenu(GROUP_FINANCIAL, false);
          break;
        case MAIL:
          switchToFindByGroupMenu(GROUP_MAIL, false);
          break;
        case CUSTOM:
          switchToFindByGroupMenu(GROUP_CUSTOM, false);
          break;
        case ALL_GROUPS:
          switchToFindAcctMenu();
          break;
        default:
          position = 0;
          DisplayToError("ERR: 040");
          switchToFindAcctMenu();
          break;
			}
			BlankLine3();                                                             // wipes out the name of the account 
//  } else if (STATE_FIND_ACCOUNT == machineState){                             // long click after selecting an account
//    event = EVENT_SHOW_MAIN_MENU;
//    BlankLine2();
//    BlankLine3();
    } else if ((STATE_CONFIRM_BACK_EEPROM   == machineState) ||                 // EVENT_LONG_CLICK
               (STATE_CONFIRM_RESTORE       == machineState) ||
               (STATE_CONFIRM_FIX_CORRUPT   == machineState) ||
               (STATE_CONFIRM_RESET         == machineState) ||
               (STATE_CONFIRM_IMP_KP_CSV    == machineState) ||
               (STATE_CONFIRM_IMP_PP_CSV    == machineState) ||
               (STATE_CONFIRM_IMP_CP_CSV    == machineState)) {
      event = EVENT_SHOW_MAIN_MENU;
    } else if (STATE_CONFIRM_DEL_ACCT == machineState) {                        // EVENT_LONG_CLICK
      switchToSendCredsMenu();
      DisplayToHelp("Select attribute.");
      BlankLine3();
    } else if (STATE_MENU_SETTINGS == machineState) {                           // EVENT_LONG_CLICK
      event = EVENT_SHOW_MAIN_MENU;                                             // if in the settings menu return to the main menu
      position = SETTINGS;
      BlankLine2();
      BlankLine3();
    } else if (STATE_MENU_FIND_BY_GROUP == machineState) {                      // EVENT_LONG_CLICK
      position = EDIT_GROUPS;
      event = EVENT_SHOW_EDIT_MENU;                                             // return to the edit credentials menu
      BlankLine2();
      BlankLine3();
//  } else if (STATE_SEARCH_FAVORITES == machineState) {                        // EVENT_LONG_CLICK
//    event = EVENT_SEARCH_FAVORITES;                                           // TODO: code EVENT_SEARCH_FAVORITES

		} else if((STATE_SEARCH_FAVORITES == machineState) ||
							(STATE_SEARCH_WORK      == machineState) ||    
							(STATE_SEARCH_PERSONAL  == machineState) ||    
							(STATE_SEARCH_HOME      == machineState) ||    
							(STATE_SEARCH_SCHOOL    == machineState) ||    
							(STATE_SEARCH_FINANCIAL == machineState) ||    
							(STATE_SEARCH_MAIL      == machineState) ||    
							(STATE_SEARCH_CUSTOM    == machineState)) {                       // EVENT_LONG_CLICK
			switch (machineState) {
				case STATE_SEARCH_FAVORITES:
					position = GROUP_FAVORITES;
					break;
				case STATE_SEARCH_WORK:
					position = GROUP_WORK;
					break;
				case STATE_SEARCH_PERSONAL:
					position = GROUP_PERSONAL;
					break;
				case STATE_SEARCH_HOME:
					position = GROUP_HOME;
					break;
				case STATE_SEARCH_SCHOOL:
					position = GROUP_SCHOOL;
					break;
				case STATE_SEARCH_FINANCIAL:
					position = GROUP_FINANCIAL;
					break;
				case STATE_SEARCH_MAIL:
					position = GROUP_MAIL;
					break;
				case STATE_SEARCH_CUSTOM:
					position = GROUP_CUSTOM;
					break;
				default:
					position = GROUP_FAVORITES;
					DisplayToError("ERR: 040");
					break;
			}
			switchFindByGroup();
    } else if ((STATE_KEY_ON_OFF_MENU     == machineState) ||                   // EVENT_LONG_CLICK
               (STATE_SHOW_PW_ON_OFF_MENU == machineState) ||
               (STATE_DECOY_ON_OFF_MENU   == machineState) ||
               (STATE_MENU_LOGIN_ATTEM    == machineState) ||
               (STATE_MENU_RGB_INTENSITY  == machineState) ||
							 (STATE_MENU_DEFINE_GROUPS  == machineState) ||
               (STATE_MENU_LOGOUT_TIMEOUT == machineState) ||
               (STATE_MENU_KEYBOARD       == machineState) ||
               (STATE_MENU_ENCODER        == machineState) ||
               (STATE_MENU_FONT           == machineState) ||
               (STATE_MENU_ORIENT         == machineState) ||
               (STATE_MENU_SHOW_GEN_PW_SZ == machineState) ||
               (STATE_MENU_INT_CHAR_PAUSE == machineState)) {
      switch (machineState) {
        case STATE_KEY_ON_OFF_MENU:
          position = SETTINGS_SET_KEYBOARD;
          break;
        case STATE_SHOW_PW_ON_OFF_MENU:
          position = SETTINGS_SET_SHOW_PW;
          break;
        case STATE_DECOY_ON_OFF_MENU:
          position = SETTINGS_SET_DECOY;
          break;
        case STATE_MENU_RGB_INTENSITY:
          position = SETTINGS_SET_RGB_INT;
          break;
        case STATE_MENU_LOGOUT_TIMEOUT:
          position = SETTINGS_SET_TIMEOUT;
          break;
        case STATE_MENU_LOGIN_ATTEM:
          position = SETTINGS_SET_LOGIN_ATTEM;
          break;
				case STATE_MENU_DEFINE_GROUPS:
					position = SETTINGS_GROUP_DEFINITION;
					break;
        case STATE_MENU_KEYBOARD:
          position = SETTINGS_KEYBOARD_LANG;
          break;
        case STATE_MENU_ENCODER:
          position = SETTINGS_ENCODER_TYPE;
          break;
        case STATE_MENU_FONT:
          position = SETTINGS_FONT;
          break;
        case STATE_MENU_ORIENT:
          position = SETTINGS_ORIENTATION;
          break;
        case STATE_MENU_SHOW_GEN_PW_SZ:
          position = SETTINGS_GEN_PW_SIZE;
          break;
        case STATE_MENU_INT_CHAR_PAUSE:
          position = SETTINGS_CHAR_DELAY;
          break;
        default:
          position = SETTINGS_SET_SHOW_PW;
          DisplayToError("ERR: 042");
          break;
      }
      //position = 0;                                                           // return to the top of the settings menu
      DisplayToHelp("Select a setting.");
      event = EVENT_SHOW_SETTINGS_MENU;
		} else if (STATE_EDIT_GROUP_1 == machineState) {
			ProcessGroupInput( 			groupCategory_1,                                  // attribute name
															CATEGORY_SIZE,                                    // attribute size
															groupEditMenu[EDIT_GROUP_1],                      // menu name
															EDIT_GROUP_1,                                     // next position
															GET_ADDR_CATEGORY_1					);                    // address
      BlankLine3();
		} else if (STATE_EDIT_GROUP_2 == machineState) {
			ProcessGroupInput( 			groupCategory_2,
															CATEGORY_SIZE,
															groupEditMenu[EDIT_GROUP_2],
															EDIT_GROUP_2,
															GET_ADDR_CATEGORY_2					);
      BlankLine3();
		} else if (STATE_EDIT_GROUP_3 == machineState) {
			ProcessGroupInput( 			groupCategory_3,
															CATEGORY_SIZE,
															groupEditMenu[EDIT_GROUP_3],
															EDIT_GROUP_3,
															GET_ADDR_CATEGORY_3					);
      BlankLine3();
		} else if (STATE_EDIT_GROUP_4 == machineState) {
			ProcessGroupInput( 			groupCategory_4,
															CATEGORY_SIZE,
															groupEditMenu[EDIT_GROUP_4],
															EDIT_GROUP_4,
															GET_ADDR_CATEGORY_4					);
      BlankLine3();
		} else if (STATE_EDIT_GROUP_5 == machineState) {
			ProcessGroupInput( 			groupCategory_5,
															CATEGORY_SIZE,
															groupEditMenu[EDIT_GROUP_5],
															EDIT_GROUP_5,
															GET_ADDR_CATEGORY_5					);
      BlankLine3();
		} else if (STATE_EDIT_GROUP_6 == machineState) {
			ProcessGroupInput( 			groupCategory_6,
															CATEGORY_SIZE,
															groupEditMenu[EDIT_GROUP_6],
															EDIT_GROUP_6,
															GET_ADDR_CATEGORY_6					);
      BlankLine3();
		} else if (STATE_EDIT_GROUP_7 == machineState) {
			ProcessGroupInput( 			groupCategory_7,
															CATEGORY_SIZE,
															groupEditMenu[EDIT_GROUP_7],
															EDIT_GROUP_7,
															GET_ADDR_CATEGORY_7					);
      BlankLine3();
//  } else if (STATE_MENU_FILE == machineState) {                               // EVENT_LONG_CLICK
//    event = EVENT_SHOW_MAIN_MENU;                                             // if any other state show main menu (e.g just after EVENT_RESET)
//    position = FILE_MENU_SEL;
    } else {                                                                    
      event = EVENT_SHOW_MAIN_MENU;                                             // if any other state show main menu (e.g just after EVENT_RESET)
      DisplayToHelp("Select an item.");
      BlankLine2();
      BlankLine3();
      switch (machineState) {                                                   // set positon so that you navigate back to the menu item from which you came
        case STATE_SEARCH_FAVORITES:
          position = FIND_FAVORITE;
          break;
        case STATE_FIND_ACCOUNT:
          position = FIND_ACCOUNT;
          break;
        case STATE_MENU_GROUPS:
          position = FIND_BY_GROUP;
          break;
        case STATE_FEED_SERIAL_DATA:
          position = EDIT_VIA_COMPUTER;
          break;
        case STATE_MENU_FILE:
          position = FILE_MENU_SEL;
          break;
        case STATE_MENU_SETTINGS:
          position = SETTINGS;
          break;
        default:
          position = FIND_FAVORITE;
          break;
      }
    }

  } else if (event == EVENT_SHOW_MAIN_MENU) {                                   // show the main menu
    menuNumber = MAIN_MENU_NUMBER;
    int arraySize = 0;
    for (uint8_t i = 0; i < MENU_SIZE; i++) {
      arraySize += sizeof(mainMenu[i]);  
    }
    memcpy(currentMenu, mainMenu, arraySize);
    elements = MAIN_MENU_ELEMENTS;
    machineState = STATE_SHOW_MAIN_MENU;
    oled.clear();
    if (!authenticated) {
      position = ENTER_MASTER_PASSWORD;
      DisplayToHelp("Enter password.");
    } else {
      DisplayToHelp("Select an action.");
    }
    ShowMenu(position, currentMenu, "      Actions       ");
    event = EVENT_NONE;

  } else if (event == EVENT_SHOW_EDIT_MENU) {                                   // show the edit menu
    menuNumber = EDIT_MENU_NUMBER;
    int arraySize = 0;
    for (uint8_t i = 0; i < MENU_SIZE; i++) {
      arraySize += sizeof(enterMenu[i]);  
    }
    memcpy(currentMenu, enterMenu, arraySize);
    elements = EDIT_MENU_ELEMENTS;
    machineState = STATE_EDIT_CREDS_MENU;
    if (position < 0 || position > (EDIT_MENU_ELEMENTS - 1)) position = 0;      // for safety
    ShowMenu(position, currentMenu, "  Edit Credentials  ");
    readAcctFromEEProm(acctPosition, accountName);
    DisplayToStatus(accountName);
    DisplayToHelp("Select an attribute.");
    event = EVENT_NONE;

  } else if (event == EVENT_SHOW_SETTINGS_MENU) {                               // show the settings menu
    menuNumber = SETTINGS_MENU_NUMBER;
    int arraySize = 0;
    for (uint8_t i = 0; i < MENU_SIZE; i++) {
      arraySize += sizeof(settingsMenu[i]);  
    }
    memcpy(currentMenu, settingsMenu, arraySize);
    elements = SETTINGS_MENU_ELEMENTS;
    machineState = STATE_MENU_SETTINGS;
    if (position < 0 || position > (SETTINGS_MENU_ELEMENTS - 1)) position = 0;  // for safety
    //position = 0;                                                             // set focus on the first menu element.
    ShowMenu(position, currentMenu,"      Settings      ");
    DisplayToHelp("Select a setting.");
    if (position == SETTINGS_GEN_PW_SIZE) {                                     // To overcome a defect in the way the menu is working
      DisplayToItem("Gened password size");                                     // To overcome a defect in the way the menu is working
    }                                                                           // To overcome a defect in the way the menu is working
    event = EVENT_NONE;

  } else if (event == EVENT_SHOW_FILE_MENU) {                                   // show the backup/restore menu
    menuNumber = FILE_MENU_NUMBER;
    int arraySize = 0;
    for (uint8_t i = 0; i < MENU_SIZE; i++) {
      arraySize += sizeof(fileMenu[i]);  
    }
    memcpy(currentMenu, fileMenu, arraySize);
    elements = FILE_MENU_ELEMENTS;
    machineState = STATE_MENU_FILE;
    position = 0;
    ShowMenu(position, currentMenu,"Backup/Restore");
    DisplayToHelp("Select an action.");
    event = EVENT_NONE;
//  } else if (event == EVENT_SHOW_FIND_BY_GROUP) {                             // show the find by group

  } else if (event == EVENT_SHOW_OFF_ON_MENU) {
    menuNumber = OFF_ON_MENU_NUMBER;
    int arraySize = 0;
    for (uint8_t i = 0; i < MENU_SIZE; i++) {
      arraySize += sizeof(offOnMenu[i]);  
    }
    memcpy(currentMenu, offOnMenu, arraySize);
    elements = OFF_ON_MENU_ELEMENTS;
    switch (machineState) {
      case STATE_KEY_ON_OFF_MENU:
        position = keyboardFlag;
        break;
      case STATE_SHOW_PW_ON_OFF_MENU:
        position = showPasswordsFlag;
        break;
      case STATE_DECOY_ON_OFF_MENU:
        position = decoyPassword;
        break;
      default:
        DisplayToError("ERR: 019");
        position = 0;
        break;
    }
    ShowMenu(position, currentMenu); 
    DisplayToHelp("Select On or Off");
    event = EVENT_NONE;

  } else if (event == EVENT_SHOW_RGB_INT_MENU) {
    menuNumber = RGB_INTENSITY_MENU_NUMBER;
    int arraySize = 0;
    for (uint8_t i = 0; i < MENU_SIZE; i++) {
      arraySize += sizeof(RGBLEDIntensityMenu[i]);  
    }
    memcpy(currentMenu, RGBLEDIntensityMenu, arraySize);
    elements = RGB_INTENSITY_MENU_ELEMENTS;
    switch(RGBLEDIntensity) {
      case RGB_LED_HIGH:
        position = RGB_INTENSITY_HIGH;
        break;
      case RGB_LED_MEDIUM:
        position = RGB_INTENSITY_MED;
        break;
      case RGB_LED_LOW:
        position = RGB_INTENSITY_LOW;
        break;
      case RGB_LED_OFF:
        position = RGB_INTENSITY_OFF;
        break;
      default:
        position = RGB_INTENSITY_MED;
        DisplayToError("ERR: 016");
        break;
    }
    ShowMenu(position, currentMenu, "   RGB Intensity   ");  
    DisplayToHelp("Select intensity.");
    event = EVENT_NONE;

  } else if (event == EVENT_SHOW_GROUP_DEF_MENU) {
    menuNumber = GROUP_EDIT_MENU_NUMBER;
    int arraySize = 0;
    for (uint8_t i = 0; i < MENU_SIZE; i++) {
      arraySize += sizeof(groupEditMenu[i]);  
    }
    memcpy(currentMenu, groupEditMenu, arraySize);
    elements = GROUP_EDIT_MENU_ELEMENTS;
		machineState = STATE_MENU_DEFINE_GROUPS;
		position = 0;
    ShowMenu(position, currentMenu, " Customize Groups  ");  
    DisplayToHelp("Select a group.");
    event = EVENT_NONE;

  } else if (event == EVENT_SHOW_LOG_TIME_MENU) {
    menuNumber = LOGOUT_TIMEOUT_MENU_NUMBER;
    int arraySize = 0;
    for (uint8_t i = 0; i < MENU_SIZE; i++) {
      arraySize += sizeof(logoutTimeoutMenu[i]);  
    }
    memcpy(currentMenu, logoutTimeoutMenu, arraySize);
    elements = LOGOUT_TIMEOUT_MENU_ELEMENTS;
    switch(logoutTimeout) {
      case LOGOUT_TIMEOUT_VAL_30:
        position = LOGOUT_TIMEOUT_30;
        break;
      case LOGOUT_TIMEOUT_VAL_60:
        position = LOGOUT_TIMEOUT_60;
        break;
      case LOGOUT_TIMEOUT_VAL_90:
        position = LOGOUT_TIMEOUT_90;
        break;
      case LOGOUT_TIMEOUT_VAL_120:
        position = LOGOUT_TIMEOUT_120;
        break;
      case LOGOUT_TIMEOUT_VAL_240:
        position = LOGOUT_TIMEOUT_240;
        break;
      case LOGOUT_TIMEOUT_VAL_1:
        position = LOGOUT_TIMEOUT_1;
        break;
      case LOGOUT_TIMEOUT_VAL_0:
        position = LOGOUT_TIMEOUT_0;
        break;
      default:
        position = LOGOUT_TIMEOUT_60;
        DisplayToError("ERR: 018");
        break;
    }
    ShowMenu(position, currentMenu, "   Logout Timeout   "); 
    DisplayToHelp("Select timeout value");
    event = EVENT_NONE;

  } else if (event == EVENT_SHOW_LG_ATTEM_MENU) {
    menuNumber = LOGIN_ATTEMPTS_MENU_NUMBER;
    int arraySize = 0;
    for (uint8_t i = 0; i < MENU_SIZE; i++) {
      arraySize += sizeof(LoginAttemptsMenu[i]);
    }
    memcpy(currentMenu, LoginAttemptsMenu, arraySize);
    elements = LOGIN_ATTEMPTS_MENU_ELEMENTS;
    switch (loginAttempts) {
      case ATTEMPTS_3:
        position = LOGIN_ATTEMPTS_3;
        break;
      case ATTEMPTS_5:
        position = LOGIN_ATTEMPTS_5;
        break;
      case ATTEMPTS_10:
        position = LOGIN_ATTEMPTS_10;
        break;
      case ATTEMPTS_25:
        position = LOGIN_ATTEMPTS_25;
        break;
      default:
        position = LOGIN_ATTEMPTS_10;
        DisplayToError("ERR: 017");
        break;
    }
    ShowMenu(position, currentMenu, "   Login Attempts   ");  
    DisplayToHelp("Select login attempt");
    event = EVENT_NONE;

  } else if (event == EVENT_SHOW_KEYBOARD_MENU) {
    menuNumber = KEYBOARD_MENU_NUMBER;
    int arraySize = 0;
    for (uint8_t i = 0; i < MENU_SIZE; i++) {
      arraySize += sizeof(keyboardMenu[i]);
    }
    memcpy(currentMenu, keyboardMenu, arraySize);
    elements = KEYBOARD_MENU_ELEMENTS;
    switch (keyboardType) {
      case KEYBOARD_CZECH:
        position = KEYBOARD_CZECH;
        break;
      case KEYBOARD_DANISH:
        position = KEYBOARD_DANISH;
        break;
      case KEYBOARD_FINNISH:
        position = KEYBOARD_FINNISH;
        break;
      case KEYBOARD_FRENCH:
        position = KEYBOARD_FRENCH;
        break;
      case KEYBOARD_GERMAN:
        position = KEYBOARD_GERMAN;
        break;
      case KEYBOARD_NORWEGIAN:
        position = KEYBOARD_NORWEGIAN;
        break;
      case KEYBOARD_SPANISH:
        position = KEYBOARD_SPANISH;
        break;
      case KEYBOARD_SWEDISH:
        position = KEYBOARD_SWEDISH;
        break;
      case KEYBOARD_UK:
        position = KEYBOARD_UK;
        break;
      case KEYBOARD_US:
        position = KEYBOARD_US;
        break;
      default:
        position = KEYBOARD_DEFAULT;
        keyboardType = KEYBOARD_DEFAULT;
        DisplayToError("ERR: 045");
        break;
    }
    ShowMenu(position, currentMenu, "   Keyboard Type    ");  
    DisplayToHelp("Select keyboard.");
    event = EVENT_NONE;

  } else if (event == EVENT_SHOW_ENCODER_MENU) {
    menuNumber = ENCODER_MENU_NUMBER;
    int arraySize = 0;
    for (uint8_t i = 0; i < MENU_SIZE; i++) {
      arraySize += sizeof(encoderMenu[i]);
    }
    memcpy(currentMenu, encoderMenu, arraySize);
    elements = ENCODER_MENU_ELEMENTS;
    switch (encoderType) {
      case ENCODER_NORMAL:
        position = ENCODER_NORMAL;
        break;
      case ENCODER_LEFTY:
        position = ENCODER_LEFTY;
        break;
      default:
        position = encoderType;
        DisplayToError("ERR: 046");
        break;
    }
    ShowMenu(position, currentMenu, "   Encoder Type    ");  
    DisplayToHelp("Select encoder type.");
    event = EVENT_NONE;

  } else if (event == EVENT_SHOW_FONT_MENU) {
    menuNumber = FONT_MENU_NUMBER;
    int arraySize = 0;
    for (uint8_t i = 0; i < MENU_SIZE; i++) {
      arraySize += sizeof(fontMenu[i]);
    }
    memcpy(currentMenu, fontMenu, arraySize);
    elements = FONT_MENU_ELEMENTS;
    position = font;
    ShowMenu(position, currentMenu, "        Font        ");  
    DisplayToHelp("Select font.");
    event = EVENT_NONE;

  } else if (event == EVENT_SHOW_ORIENT_MENU) {
    menuNumber = ORIENT_MENU_NUMBER;
    int arraySize = 0;
    for (uint8_t i = 0; i < MENU_SIZE; i++) {
      arraySize += sizeof(orientMenu[i]);
    }
    memcpy(currentMenu, orientMenu, arraySize);
    elements = ORIENT_MENU_ELEMENTS;
    position = orientation;
    ShowMenu(position, currentMenu, "    Orientation     ");  
    DisplayToHelp("Select orientation.");
    event = EVENT_NONE;

  } else if (event == EVENT_SHOW_GEN_PW_SZ_MENU) {
    menuNumber = GEN_PW_SIZE_MENU_NUMBER;
    int arraySize = 0;
    for (uint8_t i = 0; i < MENU_SIZE; i++) {
      arraySize += sizeof(genPWSizeMenu[i]);
    }
    memcpy(currentMenu, genPWSizeMenu, arraySize);
    elements = GEN_PW_SIZE_MENU_ELEMENTS;
    position = generatedPasswordSize;
    ShowMenu(position, currentMenu, "Deflt Gened Pass Sz");  
    DisplayToHelp("Select size.");
    event = EVENT_NONE;

  } else if (event == EVENT_SHOW_INT_CHAR_MENU) {
    menuNumber = CHAR_DELAY_MENU_NUMBER;
    int arraySize = 0;
    for (uint8_t i = 0; i < MENU_SIZE; i++) {
      arraySize += sizeof(charDelayMenu[i]);
    }
    memcpy(currentMenu, charDelayMenu, arraySize);
    elements = CHAR_DELAY_MENU_ELEMENTS;
    position = interCharPause;
    ShowMenu(position, currentMenu, "  Inter Char Pause  ");  
    DisplayToHelp("Selct intr chr pause");
    event = EVENT_NONE;

  } else if (event == EVENT_CHANGE_MASTER) {
    machineState = STATE_CHANGE_MASTER;
    position = DEFAULT_ALPHA_EDIT_POS;                                          // puts the position of the rotary encoder over 'A' for quicker password  entry                     
    enterPosition = 0;
    char charToPrint[2];
    charToPrint[0] = allChars[0];
    charToPrint[1] = NULL_TERM;
    DisplayToEdit((char *)charToPrint);
    DisplayToMenu("    Enter Master    ");
    DisplayToHelp("Enter new password.");
    if (keyboardFlag) {
      Serial.begin(BAUD_RATE);
      while(!Serial);
    }
    event = EVENT_NONE;
    
  } else if (event == EVENT_BACKUP) {
    ConfirmChoice(STATE_CONFIRM_BACK_EEPROM);

  } else if (event == EVENT_RESTORE) {
    ConfirmChoice(STATE_CONFIRM_RESTORE);

  } else if (event == EVENT_RESET) {
    ConfirmChoice(STATE_CONFIRM_RESET);

  } else if (event == EVENT_DELETE_ACCT) {
    ConfirmChoice(STATE_CONFIRM_DEL_ACCT);

  } else if (event == EVENT_FIX_CORRUPTION) {
    ConfirmChoice(STATE_CONFIRM_FIX_CORRUPT);
    
//} else if (event == EVENT_BACKUP_TO_FILE) {
//  BackupToPPCVSFile();
//  event = EVENT_NONE;

//} else if (event == EVENT_IMPORT_PP_CSV) {
//  ConfirmChoice(STATE_CONFIRM_IMP_PP_CSV);

//} else if (event == EVENT_IMPORT_CP_CSV) {
//  ConfirmChoice(STATE_CONFIRM_IMP_CP_CSV);

//} else if (event == EVENT_IMPORT_KEEPASS_CSV) {
//  ConfirmChoice(STATE_CONFIRM_IMP_KP_CSV);

  } else if (event == EVENT_LOGOUT) {
    if(authenticated) {
      setBlue();
      DimDisplay(true);                                                         // dim the display
      DisplayToStatus("Logged out");
      InitializeGlobals();                                                      // prevent peeking in memory after a logout
      ShowSuspend();
      event = EVENT_SUSPEND;
    } else {
      DisplayToStatus("Not logged in");
      BlankLine2();
      event = EVENT_SHOW_MAIN_MENU;
    }
    
  } else if (event == EVENT_SUSPEND) {                                        // scroll forward through something depending on state...
    while (1 == 1);
  } else {
    DisplayToError("ERR: 007");
  }
}

void setHelpOnSendCredsMenu(uint8_t position) {
  switch(position) {
    case SEND_PASSWORD:
      DisplayToHelp("Click to send.");
      break;
    case SEND_USER_AND_PASSWORD:
      DisplayToHelp("Click to send.");
      break;
    case SEND_WEBSITE:
      DisplayToHelp("Click to send.");
      break;
    case SEND_USERNAME:
      DisplayToHelp("Click to send.");
      break;
    case SEND_PASSWORD_NO_RET:
      DisplayToHelp("Click to send.");
      break;
    case SEND_ACCOUNT:
      DisplayToHelp("Click to send.");
      break;
    case EDIT_ACCOUNT:
      DisplayToHelp("Click to edit.");
      break;
    case DELETE_ACCOUNT:
      DisplayToHelp("Click to delete.");
      break;
    case SEND_OLD_PASSWORD:
      DisplayToHelp("Click to send.");
      break;
    default:
      DisplayToError("ERR: 004A");
      break;
  }
}

void setHelpOnEditCredsMenu(uint8_t position) {
  switch(position) {
    case EDIT_ACCT_NAME:
      DisplayToHelp("Click to edit acct");
      break;
    case EDIT_USERNAME:
      DisplayToHelp("Click to edit user");
      break;
    case EDIT_PASSWORD:
      DisplayToHelp("Click to edit pass");
      break;
    case EDIT_WEBSITE:
      DisplayToHelp("Click to edit URL");
      break;
    case EDIT_STYLE:
      DisplayToHelp("Click to edit style");
      break;
    case EDIT_GROUPS:
      DisplayToHelp("Click to edit groups");
      break;
    case GENERATE_PASSWORD:
      DisplayToHelp("Click to generate");
      break;
    case SAVE_OLD_PASSWORD:
      DisplayToHelp("Click to save old");
      break;
    default:
      DisplayToError("ERR: 049");
      break;
  }
}

void setHelpOnSettingsMenu(uint8_t position) {
  switch(position) {
    case SETTINGS_SET_KEYBOARD:
      DisplayToHelp("Click to set on/off");
      break;
    case SETTINGS_SET_SHOW_PW:
      DisplayToHelp("Click to set on/off");
      break;
    case SETTINGS_SET_DECOY:
      DisplayToHelp("Click to set on/off");
      break;
    case SETTINGS_SET_RGB_INT:
      DisplayToHelp("Click for intensity");
      break;
    case SETTINGS_SET_TIMEOUT:
      DisplayToHelp("Click for timeout");
      break;
    case SETTINGS_SET_LOGIN_ATTEM:
      DisplayToHelp("Click to set attempt");
      break;
    case SETTINGS_GROUP_DEFINITION:
      DisplayToHelp("Click define groups");
      break;
    case SETTINGS_CHANGE_MASTER:
      DisplayToHelp("Click change master");
      break;
    case SETTINGS_KEYBOARD_LANG:
      DisplayToHelp("Click to set lang");
      break;
    case SETTINGS_ENCODER_TYPE:
      DisplayToHelp("Click to set encoder");
      break;
    case SETTINGS_FONT:
      DisplayToHelp("Click to set font");
      break;
    case SETTINGS_ORIENTATION:
      DisplayToHelp("Click for orientatn");
      break;
    case SETTINGS_GEN_PW_SIZE:
      DisplayToItem("Gened password size");                                     // To overcome a defect in the way the menu is working
      DisplayToHelp("Click for pw size");
      break;
    case SETTINGS_CHAR_DELAY:
      DisplayToHelp("Click to set");
      break;
    default:
      DisplayToError("ERR: 050");
      break;
  }
}

void DimDisplay(boolean dim) {
  if (dim) {
//  oled.dim(true);
    oledDim = true;
  } else {
//  oled.dim(false);
    oledDim = false;
  }
}

void ScrollPasswordPump(void) {
  oled.clear();
  oled.println("PasswordPump  v2.0.6");
}

void setupStateEnterMasterPassword() {
  machineState = STATE_ENTER_MASTER;
  position = DEFAULT_ALPHA_EDIT_POS;                                            // puts the position of the rotary encoder over 'A' for quicker password  entry                     
  enterPosition = 0;
  char charToPrint[2];
  charToPrint[0] = allChars[0];
  charToPrint[1] = NULL_TERM;
  DisplayToMenu("  Master Password   ");
  BlankLine2();
  DisplayToEdit((char *)charToPrint);
  //if (keyboardFlag) {                                                         // commented out because master password must always be entered via rotary encoder
  //  Serial.begin(BAUD_RATE);
  //  while(!Serial);                                                           // we get stuck here if keyboard is on and we logout and try to log back in
  //}
  event = EVENT_NONE;
  DisplayToHelp("Enter password.");
}  

void PopulateGlobals() {  
  DisableInterrupts();
  
  keyboardFlag = getKeyboardFlag;                                               // setup the keyboard flag
  if (keyboardFlag == INITIAL_MEMORY_STATE_BYTE ) {                             // this should never be true because the reset event sets the keyboard flag to a
    keyboardFlag = false;                                                       // value but, for safety, set the keyboard flag to OFF
    writeKeyboardFlag();                                                        // and write it to EEprom.
  }

  logoutTimeout = getLogoutTimeout;                                             // the inactivity logout timer
  if (logoutTimeout == INITIAL_MEMORY_STATE_BYTE) {
    logoutTimeout = LOGOUT_TIMEOUT_DEFAULT;
    writeLogoutTimeout();
  }
  //DebugMetric("logoutTimeout: ", logoutTimeout);
  
  loginAttempts = getLoginAttempts;                                             // the maximum number of login attempts before factory reset
  if (loginAttempts == INITIAL_MEMORY_STATE_BYTE) {
    loginAttempts = ATTEMPTS_DEFAULT;
    writeLoginAttempts();
  }

  keyboardType = getKeyboardType;
	if (keyboardType == INITIAL_MEMORY_STATE_BYTE) {															// ...and if not initialize them
    keyboardType = KEYBOARD_DEFAULT;
		writeKeyboardType();
	}

  setListHeadPosition();                                                        // set headPosition. read the head of the doubly linked list that sorts by account name
  //DebugMetric("headPosition: ",headPosition);
  acctPosition = headPosition;                                                  // initially the current account is the head account
  tailPosition = findTailPosition(headPosition);                                // find the tail of the doubly linked list that sorts by account name
  //DebugMetric("tailPosition: ",tailPosition);
  acctCount = countAccounts();                                                  // count the number of populated accounts in EEprom
  //DebugMetric("acctCount: ",acctCount);

  EnableInterrupts();                                                           // Turn on global interrupts
}

void ProcessAttributeInput( char *attributeName,                                // Invoked after EVENT_LONG_CLICK
                            uint8_t attributeSize, 
                            const char *menuName, 
                            uint8_t nextPosition,
                            uint8_t acctFlag,
                            uint32_t address          ) {
  ReadFromSerial(attributeName, attributeSize, menuName);
  attributeName[attributeSize - 1] = NULL_TERM;                                 // for safety
  uint8_t pos = 0;
  while (attributeName[pos++] != NULL_TERM);                                    // make sure the account name is attributeSize chars long, pad with NULL_TERM
  while (pos < attributeSize) attributeName[pos++] = NULL_TERM;                 // "           "              "
  char buffer[attributeSize];
  setKey(acctPosition);
  encrypt32Bytes(buffer, attributeName);
  eeprom_write_bytes(address, buffer, attributeSize);
  if (acctFlag) {
    writePointers(acctPosition, attributeName);                                 // insert the account into the linked list by updating prev and next pointers.
    uint8_t groups = read_eeprom_byte(GET_ADDR_GROUP(acctPosition));            // initialize the groups
    if (groups == INITIAL_MEMORY_STATE_BYTE) writeGroup(acctPosition, NONE);    // a set of credentials cannot belong to all groups because that's INITIAL_MEMORY_STATE_BYTE.
  }
  position = nextPosition;
  event = EVENT_SHOW_EDIT_MENU;   
}

void ProcessGroupInput( 		char *attributeName,                                // Invoked after EVENT_LONG_CLICK
                            uint8_t attributeSize, 
                            const char *menuName, 
                            uint8_t nextPosition,
                            uint32_t address          ) {
  ReadFromSerial(attributeName, attributeSize, menuName);
  attributeName[attributeSize - 1] = NULL_TERM;                                 // for safety
  uint8_t pos = 0;
  while (attributeName[pos++] != NULL_TERM);                                    // 
  while (pos < attributeSize) attributeName[pos++] = NULL_TERM;                 // 
  eeprom_write_bytes(address, attributeName, attributeSize);
  position = nextPosition;
	loadGroupMenu();
  event = EVENT_SHOW_GROUP_DEF_MENU;   
}

void EditAttribute(uint8_t aState, uint8_t pos) {                               // called when we single click on Edit Account or similar
  char charToPrint[2];
  charToPrint[0] = allChars[enterPosition];
  charToPrint[1] = NULL_TERM;                                                   // TODO: this shouldn't be necessary
  machineState = aState; 
  position = pos;                                                               // setting position for starting input
  DisplayToEdit(charToPrint);                                                   // echo the char
  event = EVENT_NONE;
  //EnableInterrupts();
  //if (keyboardFlag) {
  //  Serial.begin(BAUD_RATE);
  //  while(!Serial);                                                             // waits for an active serial connection to be established by the PC (i.e., for
  //}                                                                             // the serial port to be opened by a piece of software)
  //Serial.println(aState);                                                       // sends state to python client in poll() function, attribute = s.readln()
  //DisableInterrupts();
}

void enterAttributeChar(char *attribute, uint8_t passwordFlag) {
  attribute[enterPosition] = allChars[position];
  attribute[enterPosition + 1] = NULL_TERM;                                     // push the null terminator out ahead of the last char in the string
  if (attribute[enterPosition] != 174) {                                        // accommodate entering a symbolic backspace («) TODO: this doesn't work, need to use ASCII char instead
    if (!showPasswordsFlag && passwordFlag) {                                   // mask the password being entered if showPasswordsFlag is OFF
      line3DispBuff[enterPosition] = '*';
    } else {
      line3DispBuff[enterPosition] = allChars[position];
    }
    line3DispBuff[enterPosition + 1] = NULL_TERM;                               // push the null terminator out ahead of the last char in the string
    DisplayBuffer3();
    if ((enterPosition + 1) < (DISPLAY_BUFFER_SIZE - 1)) enterPosition++;       // don't increment enterPosition beyond the space that's allocated for the associated array
  } else {
    attribute[enterPosition - 1]      = NULL_TERM;                              // blank out the previously entered character
    attribute[enterPosition]          = NULL_TERM;                              // blank out the presently entered character («)
    attribute[enterPosition + 1]      = NULL_TERM;                              // blank out the next entered character (for good measure)
    line3DispBuff[enterPosition - 1]  = NULL_TERM;                              // blank out the previously entered character
    line3DispBuff[enterPosition]      = NULL_TERM;                              // blank out the presently entered character, «, which is never shown
    line3DispBuff[enterPosition + 1]  = NULL_TERM;                              // blank out the next entered character (for good measure)
    DisplayBuffer3();
    enterPosition--;                                                            // decrement enterPosition so we can re-enter the last character
  }
  event = EVENT_NONE;
}

void ConfirmChoice(uint8_t state) {                                                 // display the menu item that confirms execution of some destructive function
  //DebugLN("ConfirmChoice()");
  machineState = state;                                                         // set machineState to the passed in state
  DisplayToEdit("Are you sure? ");
  DisplayToHelp("Select (Y)es or (N)o");
  position = 0;                                                                 // confirmChars[0] = 'N'
  ShowChar(confirmChars[position], POS_Y_N_CONFIRM);                            // default choice is always 'N'; No.
  event = EVENT_NONE;                                                           // wait for input from the rotary encoder or short or long button press
}

void ReadFromSerial(char *buffer, uint8_t size, const char *prompt) {           // get input from the keyboard
  //DebugLN("ReadFromSerial()");
  if(keyboardFlag) {                                                            // but only if the keyboard is enabled
    EnableInterrupts();
    //DebugLN("");DebugLN(prompt);                                                // display the name of the element to be collected to the end user via serial terminal
    uint8_t serialCharCount = Serial.available();
    if (serialCharCount > size) serialCharCount = size;                         // ensure we don't read more bytes than that which we can accomodate in the buffer
    if (serialCharCount > 0) {
      for (uint8_t i = 0; i < (serialCharCount - 1); i++) {
        buffer[i] = Serial.read();                                              // read values input via serial monitor
        Serial.write(buffer[i]);                                                // echo the character to serial monitor or PuTTY
      }
      buffer[serialCharCount - 1] = NULL_TERM;
      //Serial.read();                                                          // read the last byte in the buffer, throw it out.
      while (Serial.available()) Serial.read();                                 // substituted the above method with this method when we started making sure 
                                                                                // that we don't read past the end of the passed buffer. Extra bytes are tossed
    }
    Serial.end();
    DisableInterrupts();
  }
}

void switchToEditMenu(){
  //DebugLN("switchToEditMenu()");
  menuNumber = EDIT_MENU_NUMBER;
  elements = EDIT_MENU_ELEMENTS;
  int arraySize = 0;
  for (uint8_t i = 0; i < MENU_SIZE; i++) {
    arraySize += sizeof(enterMenu[i]);  
  }
  memcpy(currentMenu, enterMenu, arraySize);
  elements = EDIT_MENU_ELEMENTS;
  position = EDIT_ACCT_NAME;
  machineState = STATE_EDIT_CREDS_MENU;
  ShowMenu(position, currentMenu, "  Edit Credentials  ");
  if (!addFlag) {
    readAcctFromEEProm(acctPosition, accountName);
    DisplayToStatus((char *)accountName);
  }
  event = EVENT_NONE;
}

void switchFindByGroup() {
  menuNumber = GROUP_MENU_NUMBER;
  int arraySize;arraySize = 0;                                          // the compiler won't let me do this in one statement.
  for (uint8_t i = 0; i < MENU_SIZE; i++) {
    arraySize += sizeof(groupMenu[i]);
  }
  //memcpy(currentMenu, groupMenu, arraySize);
  elements = GROUP_MENU_ELEMENTS;
  machineState = STATE_MENU_GROUPS;
  //ShowMenu(position, currentMenu,"   Find by Group    ");
  DisplayToItem(groupMenu[position]);
  DisplayToMenu("   Find by Group    ");
  DisplayToHelp("Select a group.");
  event = EVENT_NONE;
}  

void switchToFindByGroup() {
  menuNumber = GROUP_MENU_NUMBER;
  int arraySize;arraySize = 0;                                        // int arraySize = 0; would not compile here...
  for (uint8_t i = 0; i < MENU_SIZE; i++) {
    arraySize += sizeof(groupMenu[i]);
  }
  //memcpy(currentMenu, groupMenu, arraySize);
  elements = GROUP_MENU_ELEMENTS;
  machineState = STATE_MENU_FIND_BY_GROUP;                            // x
  //ShowMenu(position, currentMenu,"       Groups       ");
  DisplayToItem(groupMenu[position]);
  DisplayToMenu("       Groups       ");
  event = EVENT_NONE;
}  

void switchToFindByGroupMenu(uint8_t menu, boolean setAcctPosition) {
	char buffer[DISPLAY_BUFFER_SIZE] = "Find ";
  DisplayToHelp("Select account.");
  switch (menu) {
    case GROUP_FAVORITES:
      groupFilter = FAVORITES;
      machineState = STATE_SEARCH_FAVORITES;
      DisplayToMenu("Find Favorites");
      break;
    case GROUP_WORK:
      groupFilter = WORK;
      machineState = STATE_SEARCH_WORK;
			strncat (buffer, groupCategory_1, DISPLAY_BUFFER_SIZE - strlen(buffer));
      DisplayToMenu(buffer);
      break;
    case GROUP_PERSONAL:
      groupFilter = PERSONAL;
      machineState = STATE_SEARCH_PERSONAL;
			strncat (buffer, groupCategory_2, DISPLAY_BUFFER_SIZE - strlen(buffer));
      DisplayToMenu(buffer);
      break;
    case GROUP_HOME:
      groupFilter = HOME;
      machineState = STATE_SEARCH_HOME;
			strncat (buffer, groupCategory_3, DISPLAY_BUFFER_SIZE - strlen(buffer));
      DisplayToMenu(buffer);
      break;
    case GROUP_SCHOOL:
      groupFilter = SCHOOL;
      machineState = STATE_SEARCH_SCHOOL;
			strncat (buffer, groupCategory_4, DISPLAY_BUFFER_SIZE - strlen(buffer));
      DisplayToMenu(buffer);
      break;
    case GROUP_FINANCIAL:
      groupFilter = FINANCIAL;
      machineState = STATE_SEARCH_FINANCIAL;
			strncat (buffer, groupCategory_5, DISPLAY_BUFFER_SIZE - strlen(buffer));
      DisplayToMenu(buffer);
      break;
    case GROUP_MAIL:
      groupFilter = MAIL;
      machineState = STATE_SEARCH_MAIL;
			strncat (buffer, groupCategory_6, DISPLAY_BUFFER_SIZE - strlen(buffer));
      DisplayToMenu(buffer);
      break;
    case GROUP_CUSTOM:
      groupFilter = CUSTOM;
      machineState = STATE_SEARCH_CUSTOM;
			strncat (buffer, groupCategory_7, DISPLAY_BUFFER_SIZE - strlen(buffer));
      DisplayToMenu(buffer);
      break;
    default:
      DisplayToError("ERR: 027");
      break;
  }
  
  if (setAcctPosition) acctPosition = headPosition;
  while ( (acctPosition != INITIAL_MEMORY_STATE_BYTE) &&
         !(readGroupFromEEprom(acctPosition) & groupFilter) ) {                 // 
    acctPosition = getNextPtr(acctPosition);
  }
  if (acctPosition != INITIAL_MEMORY_STATE_BYTE) {                              // if we found an account that belongs to the group
    position = acctPosition;
    readAcctFromEEProm(acctPosition, accountName);
    DisplayToItem((char *) accountName);
  } else {                                                                      // no credentials belong to this group
    position = headPosition;
    acctPosition = headPosition;
    //DebugLN("No credentials belong to this group");
    DisplayToItem("None");                                                      // otherwise we're getting garbage in the item position
  }
  event = EVENT_NONE;
}

void switchToSendCredsMenu() {
  //DebugLN("switchToSendCredsMenu()");
  menuNumber = SEND_MENU_NUMBER;
  elements = SEND_MENU_ELEMENTS;
  int arraySize = 0;
  for (uint8_t i = 0; i < MENU_SIZE; i++) {
    arraySize += sizeof(sendMenu[i]);  
  }
  memcpy(currentMenu, sendMenu, arraySize);
  //elements = SEND_MENU_ELEMENTS;
  position = SEND_PASSWORD;
  machineState = STATE_SEND_CREDS_MENU;
  ShowMenu(position, currentMenu, "    Credentials     ");
  readAcctFromEEProm(acctPosition, accountName);
  DisplayToStatus((char *)accountName);
  DisplayToHelp("Click to send.");
  event = EVENT_NONE;
}

void switchToFindAcctMenu() {
  //DebugLN("switchToFindAcctMenu()");
  machineState = STATE_FIND_ACCOUNT;
  position = acctPosition;                                                      // 
  ShowMenu(FIND_ACCOUNT, mainMenu, " Find All Accounts  ");
  groupFilter = ALL_GROUPS; 													// this ensures that we'll return to the correct menu
  readAcctFromEEProm(position, accountName);
  DisplayToItem((char *)accountName);
  event = EVENT_NONE;
}

void switchToStyleMenu() {
  //DebugLN("switchToStyleMenu()");
  menuNumber = STYLE_MENU_NUMBER;
  elements = STYLE_MENU_ELEMENTS;
  int arraySize = 0;
  for (uint8_t i = 0; i < MENU_SIZE; i++) {
    arraySize += sizeof(styleMenu[i]);  
  }
  memcpy(currentMenu, styleMenu, arraySize);
  readStyleFromEEProm(acctPosition, style);
  if (style[0] != '0' &&
      style[0] != '1' &&
      style[0] != '2'   ){
    position = STYLE_TAB;
  } else if (!strcmp(style,"0")) {
    position = STYLE_RETURN;
  } else if (!strcmp(style,"1")) {
    position = STYLE_TAB;
  } else if (!strcmp(style,"2")) {
    position = STYLE_TAB_TAB_RETURN;
  } else {
    position = STYLE_TAB;
    DisplayToError("ERR: 055");
  }
  machineState = STATE_EDIT_STYLE;
  ShowMenu(position, currentMenu, "     Set Style");
//readAcctFromEEProm(acctPosition, accountName);
//DisplayToItem((char *)accountName);
  event = EVENT_NONE;
}

void SwitchRotatePosition(uint8_t pos) {
  //DebugLN("SwitchRotatePosition()");
  switch(pos) {                                                                 // decide what to print on line 2 of the display
    case EDIT_ACCT_NAME:
      if (!addFlag) readAcctFromEEProm(acctPosition, accountName);
      DisplayToEdit((char *)accountName);
      break;
    case EDIT_USERNAME:
      if (!addFlag) readUserFromEEProm(acctPosition, username);
      DisplayToEdit((char *)username);
      break;
    case EDIT_PASSWORD:
      if (!addFlag) readPassFromEEProm(acctPosition, password);
      if (showPasswordsFlag) {
        DisplayToEdit((char *)password);
      } else {
        BlankLine3();
      }
      break;
    case EDIT_WEBSITE:
      if (!addFlag) readWebSiteFromEEProm(acctPosition, website);
      DisplayToEdit((char *)website);
      break;
    case EDIT_STYLE:
      if (!addFlag) readStyleFromEEProm(acctPosition, style);
      //DisplayToEdit((char *)style);
      break;
    case EDIT_GROUPS:
      BlankLine3();
      break;
    case GENERATE_PASSWORD:
      BlankLine3();
      break;
    case SAVE_OLD_PASSWORD:
      BlankLine3();
      break;
    default:
      DisplayToError("ERR: 006");
      break;
  }
}

void setKey(uint8_t pos) {
  uint8_t key[KEY_SIZE];                                                        // key size is 16
  readSaltFromEEProm(pos, salt);                                                // puts the salt in the first part of key
  if(salt[0] == (char) INITIAL_MEMORY_STATE_CHAR) {                             // if the salt is missing, add it  TODO: revisit this
    setSalt(salt, SALT_SIZE);                                                   // calculate the salt and put it in key
    write_eeprom_array(GET_ADDR_SALT(pos), salt, SALT_SIZE);                    // write the new salt value to EEprom
  }
  memcpy(key, salt, SALT_SIZE);
  memcpy(key + SALT_SIZE, masterPassword, MASTER_PASSWORD_SIZE);                // append the master password to the key to set the encryption key
  aes.setKey(key, MASTER_SALT_SIZE);                                            // set the key for aes to equal the salt||un-hashed entered master password
}

void SetSaltAndKey(uint8_t position) {                                          // populate and save the salt, set the key with the salt and master password
  setSalt(salt, SALT_SIZE);                                                     // populate salt with a random string
  eeprom_write_bytes(GET_ADDR_SALT(position), salt, SALT_SIZE);                 // save the salt to EEprom, don't encrypt the salt.
  uint8_t key[KEY_SIZE];                                                        // set the key so we're prepared when we write the account to EEprom
  memcpy(key, salt, SALT_SIZE);                                                 // copy the salt to the first part of the key
  memcpy(key + SALT_SIZE, masterPassword, MASTER_PASSWORD_SIZE);                // copy the master password to the second part of the key, masterPassword should be padded w/ null terminator from processing in authenticateMaster
  aes.setKey(key,KEY_SIZE);                                                     // set the key
}

void ReadSaltAndSetKey(uint8_t position) {
  readSaltFromEEProm(position, salt);
  uint8_t key[KEY_SIZE];                                                        // set the key so we're prepared when we write the account to EEprom
  memcpy(key, salt, SALT_SIZE);                                                 // copy the salt to the first part of the key
  memcpy(key + SALT_SIZE, masterPassword, MASTER_PASSWORD_SIZE);                // copy the master password to the second part of the key, masterPassword should be padded w/ null terminator from processing in authenticateMaster
  aes.setKey(key,KEY_SIZE);                                                     //
}

void FactoryReset() {
  //DebugLN("FactoryReset()");
  if (authenticated || (loginFailures > loginAttempts)) {                       // TODO: re-enter master password here to authorize creds reset
    DisplayToStatus("Initializing...");
    InitializeGlobals();
    BlankLine2();
    BlankLine3();
    InitializeEEProm();                                                         // sets all of memory = INITIAL_MEMORY_STATE_BYTE, 0xFF/255/0b11111111
    writeResetFlag(MEMORY_INITIALIZED_FLAG);                                    // setting the last byte in external EEprom to 0x01 signals that all other 
                                                                                // memory has been initialized to INITIAL_MEMORY_STATE_BYTE and that Initialize
                                                                                // doesn't need to execute at startup.
    CopyEEPromToBackup();                                                       // wipe out data on the secondary EEProm

    setBlue();                                                                  // we are no longer logged in
    loginFailures = INITIAL_MEMORY_STATE_BYTE;                                  // set login failures back to zero, this also serves as a flag to indicate if it's the first power on
    writeLoginFailures();                                                       // write login failure count back to EEprom

    showPasswordsFlag = INITIAL_MEMORY_STATE_BYTE;                              // to match the out of box setting (true / 255)
    writeShowPasswordsFlag();                                                   // write show passwords flag back to EEprom

    keyboardFlag = INITIAL_MEMORY_STATE_BYTE;
    writeKeyboardFlag();

    decoyPassword = INITIAL_MEMORY_STATE_BYTE;
    writeDecoyPWFlag();

    RGBLEDIntensity = INITIAL_MEMORY_STATE_BYTE;
    writeRGBLEDIntensity();
    
    logoutTimeout = INITIAL_MEMORY_STATE_BYTE;
    writeLogoutTimeout();

    loginAttempts = INITIAL_MEMORY_STATE_BYTE;                                  // set it to ATTEMPTS_DEFAULT (10)
    writeLoginAttempts();                                                       // and write it to EEprom
    
    write_eeprom_byte(GET_ADDR_CATEGORY_1, INITIAL_MEMORY_STATE_BYTE);          // for group status
		
    //initializeAllGroupCategories();
		//readGroupCategories();
		//loadGroupMenu();

    //switch (ENCODER_DEFAULT) {
    //  case ENCODER_NORMAL:
    //    rotaryPin1 = 9;
    //    rotaryPin2 = 7;
    //    break;
    //  case ENCODER_LEFTY:
    //    rotaryPin1 = 7;
    //    rotaryPin2 = 9;
    //    break;
    //}
    encoderType = INITIAL_MEMORY_STATE_BYTE;
    writeEncoderType();

    font = INITIAL_MEMORY_STATE_BYTE;
    writeFont();
    oled.setFont(System5x7);                                                    // System5x7 is the default font

    orientation = INITIAL_MEMORY_STATE_BYTE;
    writeOrientation();
    switch (DEFAULT_ORIENT) {
      case ORIENT_LEFTY:
        oled.displayRemap(ORIENT_LEFTY);
        break;
      case ORIENT_RIGHTY:
        oled.displayRemap(ORIENT_RIGHTY);
        break;
    }

    keyboardType = INITIAL_MEMORY_STATE_BYTE;
		writeKeyboardType();
    //keyboardType = KEYBOARD_DEFAULT;
    //changeKeyboardAttempts += 1;
    //if (changeKeyboardAttempts < 3) {
    //  Keyboard.InitKeyboard(_asciimapUS, _hidReportDescriptorUS);             // US is the default keyboard
    //}

  	//randomSeed(micros() * micros() ^ analogRead(RANDOM_PIN)*analogRead(RANDOM_PIN2));	// seed the random number generator
    ShowSuspend();
		event = EVENT_SUSPEND;

  }
}

void initializeAllGroupCategories() {
	  char buff[CATEGORY_SIZE];
		memcpy(buff,"Work\0\0\0\0\0\0",CATEGORY_SIZE);
		write_eeprom_array(GET_ADDR_CATEGORY_1, buff, CATEGORY_SIZE	);							// initialize the credential group categories
		memcpy(buff,"Personal\0\0",CATEGORY_SIZE);
		write_eeprom_array(GET_ADDR_CATEGORY_2, buff, CATEGORY_SIZE	);							// initialize the credential group categories
		memcpy(buff,"Home\0\0\0\0\0\0",CATEGORY_SIZE);
		write_eeprom_array(GET_ADDR_CATEGORY_3, buff, CATEGORY_SIZE	);							// initialize the credential group categories
		memcpy(buff,"School\0\0\0\0",CATEGORY_SIZE);
		write_eeprom_array(GET_ADDR_CATEGORY_4, buff, CATEGORY_SIZE	);							// initialize the credential group categories
		memcpy(buff,"Financial\0",CATEGORY_SIZE);
		write_eeprom_array(GET_ADDR_CATEGORY_5, buff, CATEGORY_SIZE	);							// initialize the credential group categories
		memcpy(buff,"Mail\0\0\0\0\0\0",CATEGORY_SIZE);
		write_eeprom_array(GET_ADDR_CATEGORY_6, buff, CATEGORY_SIZE	);							// initialize the credential group categories
		memcpy(buff,"Health\0\0\0\0",CATEGORY_SIZE);
		write_eeprom_array(GET_ADDR_CATEGORY_7, buff, CATEGORY_SIZE	);							// initialize the credential group categories
}

void readGroupCategories() {
	read_eeprom_array     (GET_ADDR_CATEGORY_1,                                 	// read category from EEprom
												 groupCategory_1, 
												 CATEGORY_SIZE);
	read_eeprom_array     (GET_ADDR_CATEGORY_2,                                	 	// read category from EEprom
												 groupCategory_2, 
												 CATEGORY_SIZE);
	read_eeprom_array     (GET_ADDR_CATEGORY_3,                                 	// read category from EEprom
												 groupCategory_3, 
												 CATEGORY_SIZE);
	read_eeprom_array     (GET_ADDR_CATEGORY_4,                                 	// read category from EEprom
												 groupCategory_4, 
												 CATEGORY_SIZE);
	read_eeprom_array     (GET_ADDR_CATEGORY_5,                                 	// read category from EEprom
												 groupCategory_5, 
												 CATEGORY_SIZE);
	read_eeprom_array     (GET_ADDR_CATEGORY_6,                                 	// read category from EEprom
												 groupCategory_6, 
												 CATEGORY_SIZE);
	read_eeprom_array     (GET_ADDR_CATEGORY_7,                                 	// read category from EEprom
												 groupCategory_7, 
												 CATEGORY_SIZE);
}

void loadGroupMenu() {
	memcpy(groupMenu+1, groupCategory_1, CATEGORY_SIZE);
	memcpy(groupMenu+2, groupCategory_2, CATEGORY_SIZE);
	memcpy(groupMenu+3, groupCategory_3, CATEGORY_SIZE);
	memcpy(groupMenu+4, groupCategory_4, CATEGORY_SIZE);
	memcpy(groupMenu+5, groupCategory_5, CATEGORY_SIZE);
	memcpy(groupMenu+6, groupCategory_6, CATEGORY_SIZE);
	memcpy(groupMenu+7, groupCategory_7, CATEGORY_SIZE);
}

void InitializeGlobals() {
  //DebugLN("InitializeGlobals()");
  uint8_t i;
  i = 0; while (i   < MASTER_PASSWORD_SIZE) masterPassword[i++] = NULL_TERM;    // when the device isn't authenticated you shouldn't be able to dump memory and see passwords and keys
//i = 0; while (i   < MAX_LEN_CSV_LINE    ) buf[i++]            = NULL_TERM;    // input line buffer, CSV file processing
//i = 0; while (i   < buf.length()        ) buf[i++]            = NULL_TERM;    // input line buffer, CSV file processing
  i = 0; while (i   < ACCOUNT_SIZE        ) accountName[i++]    = NULL_TERM;
  i = 0; while (i   < USERNAME_SIZE       ) username[i++]       = NULL_TERM;
  i = 0; while (i   < PASSWORD_SIZE       ) password[i++]       = NULL_TERM;
  i = 0; while (i   < WEBSITE_SIZE        ) website[i++]        = NULL_TERM;
  authenticated = false;                                                        // indicates if the correct master password has been provided
  machineState = 0;                                                             // the state of the device
  position = 0;                                                                 // the position of the rotary encoder, used to navigate menus and enter text.
  enterPosition = 0;                                                            // when alpha editing w/ rotary encoder, position in the edited word
  acctPosition = 0;                                                             // the position of the selected account.
  acctCount = 0;                                                                // the number of accounts in EEprom.
  iterationCount = 0;                                                           // # of times ProcessEvent() called since last evaluation of lastActivityTime
  headPosition = INITIAL_MEMORY_STATE_BYTE;                                     // the head of the doubly linked list that keeps account names sorted
  tailPosition = INITIAL_MEMORY_STATE_BYTE;                                     // the tail of the doubly linked list that keeps account names sorted
  loginFailures = 0;
  lastModeA = LOW;
  lastModeB = LOW;
  curModeA = LOW;
  curModeB = LOW;
  encPos = 0;
  encPosLast = 0;
  change = 0;
  lastActivityTime = millis();                                                  // used to automatically logout after a period of inactivity
}

void ShowSplashScreen() {
    strcpy(line1DispBuff,"PasswordPump  v2.0.6");
    strcpy(line2DispBuff, __DATE__);
    strcpy(line3DispBuff,"(c)2020 Dan Murphy ");
    DisplayBuffer();
//  delayNoBlock(ONE_SECOND * 3);                                               // Show the splash screen for 3 seconds
//  BlankLine3();
}

void ShowSuspend() {
    strcpy(line1DispBuff, " Press reset on the ");
    strcpy(line2DispBuff, "   bottom of the    ");
    strcpy(line3DispBuff, "  PasswordPump to   ");
    strcpy(line4DispBuff, "     continue.      ");
    DisplayBuffer();
}

//- Button

void buttonReleasedHandler(Button2& btn) {
  if(btn.wasPressedFor() > LONG_CLICK_LENGTH) {
    event = EVENT_LONG_CLICK;
    //DebugLN("Event long click");
  } else {
    event = EVENT_SINGLE_CLICK;
    //DebugLN("Event single click");
  }
}

//- Delete Account

void deleteAccount(uint8_t position) {
  //DebugLN("deleteAccount()");
  DisplayToStatus("Erasing creds");

  uint8_t prevPosition = getPrevPtr(position);                                  // get the previous account position from the linked list
  uint8_t nextPosition = getNextPtr(position);                                  // get the next account position from the linked list

  if(prevPosition != INITIAL_MEMORY_STATE_BYTE) {                               // if we're not already the head position
    writeNextPtr(prevPosition, nextPosition);                                   // write the next account position into the next account pointer of the previous position
  } else {
    headPosition = nextPosition;                                                // we're deleting the head, make the next element the new head
    writeListHeadPos(headPosition);                                             // write the head position to EEprom
  }
  if(nextPosition != INITIAL_MEMORY_STATE_BYTE) {                               // if we're not already the tail position
    writePrevPtr(nextPosition, prevPosition);                                   // write the previous account position into the previous account pointer of the next position
  } else {
    tailPosition = prevPosition;                                                // we're deleting the tail, make the previous element the new tail
  }
  stompPointers(position);                                                      // set the next pointer and previous pointer for this position to 255
  for (uint8_t i = 0; i < ACCOUNT_SIZE;   i++) accountName[i] = INITIAL_MEMORY_STATE_CHAR;
  for (uint8_t i = 0; i < USERNAME_SIZE;  i++) username[i]    = INITIAL_MEMORY_STATE_CHAR;
  for (uint8_t i = 0; i < PASSWORD_SIZE;  i++) password[i]    = INITIAL_MEMORY_STATE_CHAR;
  for (uint8_t i = 0; i < SALT_SIZE;      i++) salt[i]        = INITIAL_MEMORY_STATE_CHAR;
  for (uint8_t i = 0; i < WEBSITE_SIZE;   i++) website[i]     = INITIAL_MEMORY_STATE_CHAR;
  for (uint8_t i = 0; i < STYLE_SIZE;     i++) style[i]       = INITIAL_MEMORY_STATE_CHAR;
  for (uint8_t i = 0; i < PASSWORD_SIZE;  i++) oldPassword[i] = INITIAL_MEMORY_STATE_CHAR;
  eeprom_write_bytes(GET_ADDR_ACCT(position),      accountName,  ACCOUNT_SIZE);
  eeprom_write_bytes(GET_ADDR_USER(position),      username,     USERNAME_SIZE);
  eeprom_write_bytes(GET_ADDR_PASS(position),      password,     PASSWORD_SIZE);
  eeprom_write_bytes(GET_ADDR_SALT(position),      salt,         SALT_SIZE);
  eeprom_write_bytes(GET_ADDR_WEBSITE(position),   website,      WEBSITE_SIZE);
  eeprom_write_bytes(GET_ADDR_STYLE(position),     style,        STYLE_SIZE);
  eeprom_write_bytes(GET_ADDR_OLD_PASS(position),  oldPassword,  PASSWORD_SIZE);
  writeGroup(position, INITIAL_MEMORY_STATE_BYTE);                              
  acctCount--;
  acctPosition = headPosition;
  DisplayToStatus("Credentials erased");
}

//- UUID & Salt Generation

void generatePassword(char *uuid, uint8_t genSize, uint8_t appendNullTerm) {
  //DebugLN("generatePassword()");
  uint8_t size;
  switch (genSize) {
    case GEN_PW_SIZE_8:
      size = GEN_PW_SIZE_VAL_8;
      break;
    case GEN_PW_SIZE_10:
      size = GEN_PW_SIZE_VAL_10;
      break;
    case GEN_PW_SIZE_16:
      size = GEN_PW_SIZE_VAL_16;
      break;
    case GEN_PW_SIZE_24:
      size = GEN_PW_SIZE_VAL_24;
      break;
    case GEN_PW_SIZE_31:
      size = GEN_PW_SIZE_VAL_31;
      break;
    default:
      size = GEN_PW_SIZE_VAL_16;
      break;
  }

  uint8_t passedCheck = 0;                                                      // set the password complexity check flag to false
  while (!passedCheck) {                                                        // while the password doesn't pass the password complexity check
    for (uint8_t i = 0; i < size; i++) {                                        // generate a uuid/password that's 'size' characters long
      uuid[i] = random(33,126);                                                 // maybe we should use allChars here instead? We're generating PWs w/ chars that we can't input...
                                                                                // 32 = space, 127 = <DEL>, so we want to choose from everything in between.
      while(uuid[i] == ','  ||                                                  // trips up CSV imports
            uuid[i] == '"'  ||                                                  // trips up CSV imports
            uuid[i] == '@'  ||                                                  // trips up Oracle
            uuid[i] == '`'  ||                                                  // hard to distinguish between ' and `
            uuid[i] == '\'' ||                                                  // hard to distinguish between ' and `
            uuid[i] == '&'  ||                                                  // can cause problems inside of XML
            uuid[i] == '~'  ||                                                  // separator for cmdMessenger
            uuid[i] == '|'  ||                                                  // separator for cmdMessenger
            uuid[i] == '\\' ||                                                  // interpreted as escape character
            uuid[i] == '^'  ||                                                  // caret can be problematic
            uuid[i] == '/'    )                                                 // escape character
        uuid[i] = random(33,126);
    }
    if (appendNullTerm) uuid[size] = NULL_TERM;                                 // last character is the null terminator

    uint8_t lowerAlphaCount = 0;                                                // count of lower case characters in the uuid
    uint8_t upperAlphaCount = 0;                                                // count of upper case characters in the uuid
    uint8_t numericCount = 0;                                                   // count of numeric characters in the uuid
    uint8_t symbolCount = 0;                                                    // count of symbols in the uuid
    uint8_t passwordLength = 0;                                                 // the length of the uuid
                                                                              
    passedCheck = 1;                                                            // Prepare to test the password complexity
    
    for (uint8_t i = 0; i < size; i++) {                                        // loop over every character in the generated uuid
      if (islower(uuid[i])) lowerAlphaCount += 1;                               // count the number of password characters that are lower case
      if (isupper(uuid[i])) upperAlphaCount += 1;                               // count the number of password characters that are upper case
      if (isdigit(uuid[i])) numericCount    += 1;                               // count the number of password characters that are numeric
      if (ispunct(uuid[i])) symbolCount     += 1;                               // count the number of password characters that are symbols
    }
    
    if (lowerAlphaCount == 0) passedCheck = 0;                                  // make sure there is at lease one lower case character
    if (upperAlphaCount == 0) passedCheck = 0;                                  // make sure there is at lease one upper case character
    if (numericCount    == 0) passedCheck = 0;                                  // make sure there is at lease one numeric character
    if (symbolCount     == 0) passedCheck = 0;                                  // make sure there is at lease one symbol
  }
}

void setSalt(char *uuid, uint8_t size) {
  //DebugLN("setSalt()");
  for (uint8_t i = 0; i < (size); i++) {
    uuid[i] = random(0,255);                                                    //
    //while(uuid[i] == ','  ||                                                  // trips up CSV imports
    //      uuid[i] == '"'  ||                                                  // trips up CSV imports
    //      uuid[i] == '@'  ||                                                  // trips up Oracle
    //      uuid[i] == '`'  ||                                                  // hard to distinguish between ' and `
    //      uuid[i] == '\'' ||                                                  // hard to distinguish between ' and `
    //      uuid[i] == '&'  ||                                                  // can cause problems inside of XML
    //      uuid[i] == '~'  ||                                                  // separator for cmdMessenger
    //      uuid[i] == '|'  ||                                                  // separator for cmdMessenger
    //      uuid[i] == '\\' ||                                                  // interpreted as escape character
    //      uuid[i] == '^' ||                                                   // interpreted as escape character
    //      uuid[i] == '/'    )                                                 // escape character
    //  uuid[i] = random(0,255);
  }
}

//- Keyboard Functions

void sendAccount() {
  //DebugLN("sendAccount()");
  readAcctFromEEProm(acctPosition, accountName);                                // read the account name from EEProm
  char accountNameChar[ACCOUNT_SIZE];
  memcpy(accountNameChar,accountName,ACCOUNT_SIZE);                             // TODO: is this necessary?
  Keyboard.begin();                                                             // TODO: can we do a <CTL><A> <BS> here first?  That will clear out pre-populated user names.
  delayNoBlock(interCharPauseVal);
  uint8_t pos = 0;
  while (accountNameChar[pos] != NULL_TERM) {
    Keyboard.write(accountNameChar[pos++]);                                     // using Keyboard.println() here doesn't work; the Keyboard.println function appears to generate corrupt output (e.g. ".com" == ".comcast")
    delayNoBlock(interCharPauseVal);
  }
  Keyboard.println("");                                                         // send <CR> through the keyboard
  delayNoBlock(interCharPauseVal);
  Keyboard.end();
}

void sendOldPassword() {
  //DebugLN("sendOldPassword()");
  readOldPassFromEEProm(acctPosition, oldPassword);                             // read the old password from EEProm
  char oldPasswordChar[PASSWORD_SIZE];
  memcpy(oldPasswordChar,oldPassword,PASSWORD_SIZE);                            // TODO: is this necessary?
  Keyboard.begin();                                                             // TODO: can we do a <CTL><A> <BS> here first?  That will clear out pre-populated user names.
  delayNoBlock(interCharPauseVal);
  uint8_t pos = 0;
  while (oldPasswordChar[pos] != NULL_TERM) {
    Keyboard.write(oldPasswordChar[pos++]);                                     
    delayNoBlock(interCharPauseVal);
  }
  Keyboard.end();                                                               // do NOT send <CR> through the keyboard when sending the old password!
}

void sendUsername() {
  //DebugLN("sendUsername()");
  readUserFromEEProm(acctPosition, username);                                   // read the user name from EEProm
  char usernameChar[USERNAME_SIZE];
  memcpy(usernameChar,username,USERNAME_SIZE);
  Keyboard.begin();                                                             // TODO: can we do a <CTL><A> <BS> here first?  That will clear out pre-populated usernames.
  delayNoBlock(interCharPauseVal);
  uint8_t pos = 0;
  while (usernameChar[pos] != NULL_TERM) {
    Keyboard.write(usernameChar[pos++]);
    delayNoBlock(interCharPauseVal);
  }
  Keyboard.println("");
  delayNoBlock(interCharPauseVal);
  Keyboard.end();
}

void sendWebSite() {
  //DebugLN("sendWebSite()");
  readWebSiteFromEEProm(acctPosition, website);                                 // read the URL from EEProm
  char websiteChar[WEBSITE_SIZE];
  memcpy(websiteChar,website,WEBSITE_SIZE);
  Keyboard.begin();                                                             // TODO: can we do a <CTL><A> <BS> here first?  That will clear out pre-populated user names.
  delayNoBlock(interCharPauseVal);
  uint8_t pos = 0;
  while (websiteChar[pos] != NULL_TERM) {
    Keyboard.write(websiteChar[pos++]);
    delayNoBlock(interCharPauseVal);
  }
  Keyboard.println("");                                                         // type the URL through the keyboard
  delayNoBlock(interCharPauseVal);
  Keyboard.end();
}

//void sendGroup() {
//  //DebugLN("sendGroup()");
//  uint8_t group = readGroupFromEEprom(acctPosition);                            // read the group from EEProm
//  Keyboard.begin();                                                             // 
//  delayNoBlock(interCharPauseVal);
//  Keyboard.println(group);                                                      // type the group through the keyboard
//  delayNoBlock(interCharPauseVal);
//  Keyboard.end();
//}

void sendPassword() {                                                           // TODO: can we do a <CTL><A> <BS> here first? That will clear out pre-populated passwords.
  //DebugLN("sendPassword()");
  readPassFromEEProm(acctPosition, password);                                   // read the password from EEProm
  char passwordChar[PASSWORD_SIZE];
  memcpy(passwordChar,password,PASSWORD_SIZE);
  Keyboard.begin();
  delayNoBlock(interCharPauseVal);
  uint8_t pos = 0;
  while (passwordChar[pos] != NULL_TERM) {
    Keyboard.write(passwordChar[pos++]);
    delayNoBlock(interCharPauseVal);
  }  
  Keyboard.end();
}

void sendRTN() {
  Keyboard.begin();
  delayNoBlock(interCharPauseVal);
  Keyboard.println("");                                                         // send a carriage return through the keyboard
  delayNoBlock(interCharPauseVal);
  Keyboard.end();
}

void sendTAB() {
  Keyboard.begin();
  delayNoBlock(interCharPauseVal);
  Keyboard.press(TAB_KEY);                                                      // if style isn't default or "0" then send <TAB>
  delayNoBlock(interCharPauseVal);
  Keyboard.release(TAB_KEY);
  delayNoBlock(interCharPauseVal);
  Keyboard.end();
}

void sendLockAndLogout() {                                                      
  //DebugLN("sendLockAndLogout()");
  Keyboard.begin();
  delayNoBlock(interCharPauseVal);
  Keyboard.press(KEY_LEFT_GUI);
  delayNoBlock(interCharPauseVal);
  Keyboard.press('l'); 
  delayNoBlock(interCharPauseVal);
  Keyboard.releaseAll();                                                        // Hold down the Windows key
  delayNoBlock(interCharPauseVal);
  Keyboard.end();
}

void sendUsernameAndPassword() {
  //DebugLN("sendUsernameAndPassword()");
  readUserFromEEProm(acctPosition, username);                                   // read the user name from EEProm
  char usernameChar[USERNAME_SIZE];
  memcpy(usernameChar,username,USERNAME_SIZE);
  readPassFromEEProm(acctPosition, password);                                   // read the password from EEProm
  char passwordChar[PASSWORD_SIZE];
  memcpy(passwordChar,password,PASSWORD_SIZE);
  readStyleFromEEProm(acctPosition, style);                                     // read the style from EEprom
  Keyboard.begin();
  delayNoBlock(interCharPauseVal);
  uint8_t posUser = 0;
  while (usernameChar[posUser] != NULL_TERM) {
    Keyboard.write(usernameChar[posUser++]);                                    // seems to be a problem only with single character user names.
    delayNoBlock(interCharPauseVal);
  }
  if (strcmp(style, "0") == 0) {                                                // 0 = Return (default) 1 = Tab
    Keyboard.println("");                                                       // send <CR> through the keyboard
    delayNoBlock(interCharPauseVal);
  } else if (strcmp(style, "1") == 0) {
    Keyboard.press(TAB_KEY);                                                    // if style isn't default or "0" then send <TAB>
    delayNoBlock(interCharPauseVal);
    Keyboard.release(TAB_KEY);
    delayNoBlock(interCharPauseVal);
  } else if (style[0] == (char) INITIAL_MEMORY_STATE_CHAR) {
    Keyboard.press(TAB_KEY);                                                    // Make <TAB> the default
    delayNoBlock(interCharPauseVal);
    Keyboard.release(TAB_KEY);
    delayNoBlock(interCharPauseVal);
  } else {
    Keyboard.press(TAB_KEY);                                                    // if style isn't default or "0" then send <TAB>
    delayNoBlock(interCharPauseVal);
    Keyboard.release(TAB_KEY);
    delayNoBlock(interCharPauseVal);
  }
  delayNoBlock(UN_PW_DELAY);

  uint8_t pos = 0;
  while (passwordChar[pos] != NULL_TERM) {
    Keyboard.write(passwordChar[pos++]);
    delayNoBlock(interCharPauseVal);
  }  


  if (strcmp(style, "2") == 0) {
    Keyboard.press(TAB_KEY);                                                    // Send the <TAB> (again)
    delayNoBlock(interCharPauseVal);
    Keyboard.release(TAB_KEY);
    delayNoBlock(interCharPauseVal);
  }
  delayNoBlock(PW_RTN_DELAY);
  Keyboard.println("");                                                         // send <CR> through the keyboard
  delayNoBlock(interCharPauseVal);
  Keyboard.end();
}

//- Display Control & Menu Navigation

void DisplayToMenu(char* lineToPrint) {
  strncpy(line1DispBuff, lineToPrint, DISPLAY_BUFFER_SIZE);
  line1DispBuff[DISPLAY_BUFFER_SIZE - 1] = NULL_TERM;                           // important in the case where length of lineToPrint exceeds DISPLAY_BUFFER_SIZE.
  DisplayBuffer1();
}

void DisplayToItem(char* lineToPrint) {
  strncpy(line2DispBuff, lineToPrint, DISPLAY_BUFFER_SIZE);
  line2DispBuff[DISPLAY_BUFFER_SIZE - 1] = NULL_TERM;                           // important in the case where length of lineToPrint exceeds DISPLAY_BUFFER_SIZE.
  DisplayBuffer2();
}

void DisplayToEdit(char* lineToPrint) {
  strncpy(line3DispBuff, lineToPrint, DISPLAY_BUFFER_SIZE);
  line3DispBuff[DISPLAY_BUFFER_SIZE - 1] = NULL_TERM;                           // important in the case where length of lineToPrint exceeds DISPLAY_BUFFER_SIZE.
  DisplayBuffer3();
}

void DisplayToStatus(char* lineToPrint) {
  strncpy(line3DispBuff, lineToPrint, DISPLAY_BUFFER_SIZE);
  line3DispBuff[DISPLAY_BUFFER_SIZE - 1] = NULL_TERM;                           // important in the case where length of lineToPrint exceeds DISPLAY_BUFFER_SIZE.
  DisplayBuffer3();
}

void DisplayToError(char* lineToPrint) {
  strncpy(line4DispBuff, lineToPrint, DISPLAY_BUFFER_SIZE);
  line4DispBuff[DISPLAY_BUFFER_SIZE - 1] = NULL_TERM;                           // important in the case where length of lineToPrint exceeds DISPLAY_BUFFER_SIZE.
	oled.invertDisplay(true);
  DisplayBuffer4();
  delayNoBlock(ONE_SECOND * 2);
	oled.invertDisplay(false);
}

void DisplayToHelp(char* lineToPrint) {
  strncpy(line4DispBuff, lineToPrint, DISPLAY_BUFFER_SIZE);
  line4DispBuff[DISPLAY_BUFFER_SIZE - 1] = NULL_TERM;                           // important in the case where length of lineToPrint exceeds DISPLAY_BUFFER_SIZE.
  DisplayBuffer4();
}

void DisplayToDebug(char* lineToPrint) {
  strncpy(line4DispBuff, lineToPrint, DISPLAY_BUFFER_SIZE);
  line4DispBuff[DISPLAY_BUFFER_SIZE - 1] = NULL_TERM;                           // important in the case where length of lineToPrint exceeds DISPLAY_BUFFER_SIZE.
  DisplayBuffer4();
}

void BlankLine1() {
  //DebugLN("BlankLine1()");
  strncpy(line1DispBuff,spaceFilled,DISPLAY_BUFFER_SIZE);
  line1DispBuff[DISPLAY_BUFFER_SIZE - 1] = NULL_TERM;                           // important in the case where length of lineToPrint exceeds DISPLAY_BUFFER_SIZE.
  DisplayBuffer1();
}

void BlankLine2() {
  //DebugLN("BlankLine2()");
  strncpy(line2DispBuff,spaceFilled,DISPLAY_BUFFER_SIZE);
  line2DispBuff[DISPLAY_BUFFER_SIZE - 1] = NULL_TERM;                           // important in the case where length of lineToPrint exceeds DISPLAY_BUFFER_SIZE.
  DisplayBuffer2();
}

void BlankLine3() {
  //DebugLN("BlankLine3()");
  strncpy(line3DispBuff,spaceFilled,DISPLAY_BUFFER_SIZE);
  line3DispBuff[DISPLAY_BUFFER_SIZE - 1] = NULL_TERM;                           // important in the case where length of lineToPrint exceeds DISPLAY_BUFFER_SIZE.
  DisplayBuffer3();
}

void BlankLine4() {
  //DebugLN("BlankLine4()");
  strncpy(line3DispBuff,spaceFilled,DISPLAY_BUFFER_SIZE);
  line4DispBuff[DISPLAY_BUFFER_SIZE - 1] = NULL_TERM;                           // important in the case where length of lineToPrint exceeds DISPLAY_BUFFER_SIZE.
  DisplayBuffer4();
}

void DisplayBuffer() {
  //DebugLN("DisplayBuffer()");
  oled.clear();                                                                 // Clear all pixels in the buffer in the memory, and then use the sendBuffer function to display the buffer "Buffer" on the screen to clear the screen.
  oled.setCursor(0,LINE_1_POS);
  oled.print(line1DispBuff);
  oled.setCursor(0,LINE_2_POS);
  oled.print(line2DispBuff);
  oled.setCursor(0,LINE_3_POS);
  oled.print(line3DispBuff);
  oled.setCursor(0,LINE_4_POS);
  oled.print(line4DispBuff);
}

void DisplayBuffer1() {
  //DebugLN("DisplayBuffer1()");
  oled.setCursor(0,LINE_1_POS);
  oled.clearToEOL();
  oled.setCursor(0,LINE_1_POS);
  oled.print(line1DispBuff);
}

void DisplayBuffer2() {
  //DebugLN("DisplayBuffer2()");
  oled.setCursor(0,LINE_2_POS);
  oled.clearToEOL();
  oled.setCursor(0,LINE_2_POS);
  oled.print(line2DispBuff);
}

void DisplayBuffer3() {
  //DebugLN("DisplayBuffer3()");
  oled.setCursor(0,LINE_3_POS);
  oled.clearToEOL();
  oled.setCursor(0,LINE_3_POS);
  oled.print(line3DispBuff);
}

void DisplayBuffer4() {
  //DebugLN("DisplayBuffer4()");
  oled.setCursor(0,LINE_4_POS);
  oled.clearToEOL();
  oled.setCursor(0,LINE_4_POS);
  oled.print(line4DispBuff);
}

void ShowMenu(uint8_t position, char **menu, char *menuName) {
  //DebugLN("ShowMenu()");
  //DebugLN(menu[position]);
  DisplayToItem(menu[position]);
  DisplayToMenu(menuName);
}

void ShowMenu(uint8_t position, char **menu) {
  //DebugLN("ShowMenu()");
  //DebugLN(menu[position]);
  DisplayToItem(menu[position]);
}

void MenuUp(char **menu) { 
  //DebugLN("MenuUp()");
  if (position > -1) {
    ShowMenu(position, menu);
  }
}

void MenuDown(char **menu){ 
  //DebugLN("MenuDown()");
  if (position < elements) {
    ShowMenu(position, menu);
  }
}

void ShowChar(char charToShow, uint8_t  pos) {
  //DebugLN("ShowChar()");
  DisplayToEdit(line3DispBuff);
  char charToPrint[2];
  charToPrint[0] = charToShow;
  charToPrint[1] = NULL_TERM;
  oled.setCursor((NO_LED_LIB_CHAR_WIDTH_PIX * pos) + FIXED_CHAR_SPACING,LINE_3_POS);
  oled.print(charToPrint);
}

//- RGB LED

void setPurple() {
  setColor(RGBLEDIntensity, 0, RGBLEDIntensity);                                // Purple Color (first parm was 170)
  setColorsFalse();
  isPurple = true;
}

void setRed(){
  setColor(RGBLEDIntensity, 0, 0);                                              // Red Color
  setColorsFalse();
  isRed = true;
}

void setGreen(){
  setColor(0, RGBLEDIntensity, 0);                                              // Green Color
  setColorsFalse();
  isGreen = true;
}


void setYellow(){
  setColor(RGBLEDIntensity, RGBLEDIntensity, 0);                                // Yellow Color
  setColorsFalse();
  isYellow = true;
}

void setBlue(){
  setColor(0, 0, RGBLEDIntensity);                                              // Blue Color
  setColorsFalse();
  isBlue = true;
}

void setColor(uint8_t  redValue, uint8_t  greenValue, uint8_t  blueValue) {
  analogWrite(RED_PIN, redValue);
  analogWrite(GREEN_PIN, greenValue);
  analogWrite(BLUE_PIN, blueValue);
}

void setColorsFalse() {
  isPurple  = false;
  isRed     = false;
  isGreen   = false;
  isYellow  = false;
  isBlue    = false;
}

void trueHSV(int angle) {
  byte red, green, blue;

  if (angle<60) {red = 255; green = HSVlights[angle]; blue = 0;} else
  if (angle<120) {red = HSVlights[120-angle]; green = 255; blue = 0;} else 
  if (angle<180) {red = 0, green = 255; blue = HSVlights[angle-120];} else 
  if (angle<240) {red = 0, green = HSVlights[240-angle]; blue = 255;} else 
  if (angle<300) {red = HSVlights[angle-240], green = 0; blue = 255;} else 
                 {red = 255, green = 0; blue = HSVlights[360-angle];} 
  setColor(red, green, blue);
}

//- Encryption

boolean authenticateMaster(char *enteredPassword) {                             // verify if the master password is correct here
  //DebugLN("authenticateMaster()");
  char eepromMasterHash[HASHED_MASTER_PASSWORD_SZ];                             // buffer for the hashed master password; salt||masterPassword
  char enteredMasterPW[HASHED_MASTER_PASSWORD_SZ];                        			// holds the unhashed master password after some processing
  uint8_t pos = 0;
  while (enteredPassword[pos++] != NULL_TERM);                                  // make sure the unencrypted password is 16 chars long
  while (pos < (MASTER_PASSWORD_SIZE - 1)) enteredPassword[pos++] = NULL_TERM;  // "           "              " , right padded w/ NULL terminator
  enteredPassword[MASTER_PASSWORD_SIZE - 1] = NULL_TERM;                        // NULL_TERM in index 15 no matter what
  uint8_t aByte = read_eeprom_byte(GET_ADDR_MASTER_HASH);
  if (aByte == INITIAL_MEMORY_STATE_BYTE){                                      // first time, we need to write instead of read
    setSalt(salt, MASTER_SALT_SIZE);                                            // generate a random salt
    eeprom_write_bytes(GET_ADDR_MASTER_SALT, salt, MASTER_SALT_SIZE);           // save the un-encrypted/un-hashed salt to EEprom
    memcpy(eepromMasterHash, salt, MASTER_SALT_SIZE);                           // copy salt into the hashed master password variable
    memcpy(eepromMasterHash + MASTER_SALT_SIZE,                                 // concatenate the salt and the master password
           enteredPassword, 
           MASTER_PASSWORD_SIZE                          );
    sha256Hash(eepromMasterHash);                                               // hash the master password in place; pass in 32, get back 32
    eeprom_write_bytes    (GET_ADDR_MASTER_HASH,                                // only write the first 16 bytes of the hashed master password
                           eepromMasterHash, 
                           HASHED_MASTER_PASSWORD_SZ);                          // write the (hased) master password to EEprom
    setGreen();                                                                 // turn the RGB green to signal the correct password was provided
  } else {                                                                      // (buf != INITIAL_MEMORY_STATE_BYTE) | (ch != INITIAL_MEMORY_STATE_CHAR)
    read_eeprom_array     (GET_ADDR_MASTER_HASH,                                // read hashed master password from EEprom
                           eepromMasterHash,                                    // to compare against the hash of the salt||entered password.
                           HASHED_MASTER_PASSWORD_SZ);
    read_eeprom_array     (GET_ADDR_MASTER_SALT,                                // read salt from EEprom
                           salt, 
                           MASTER_SALT_SIZE);
    memcpy(enteredMasterPW, salt, MASTER_SALT_SIZE);                      			// copy salt into the hashed master password variable
    memcpy(enteredMasterPW + MASTER_SALT_SIZE,                            			// concatenate the salt and the master password
           enteredPassword,                                                     // entered password
           MASTER_PASSWORD_SIZE                          );
    sha256Hash(enteredMasterPW);                                          			// hash the master salt||entered password
    if (0 == memcmp(enteredMasterPW,
                    eepromMasterHash,
                    HASHED_MASTER_PASSWORD_SZ)) {                               // entered password hash matches master password hash, authenticated
      setGreen();                                                               // turn the RGB green to signal the correct password was provided
      loginFailures = 0;                                                        // reset loginFailues to zero
      writeLoginFailures();                                                     // record loginFailures in EEprom
                                                                                // encrypt a word using the master password as the key
    } else {                                                                    // failed authentication
      if (decoyPassword) {                                                      // if the decoy password was entered factory reset the device
				size_t lenEntPW = strlen(enteredPassword);
				if (0 == memcmp(enteredPassword + (lenEntPW - SIZE_OF_DECOY_PW),"FR",SIZE_OF_DECOY_PW)) {
																																								
																																								// we now know that entered password ended in "FR"
					for (uint8_t j = lenEntPW - SIZE_OF_DECOY_PW; j < lenEntPW; j++)			// blank out the "FR"
						enteredPassword[j] = NULL_TERM;
					for (uint8_t i = 0; i < HASHED_MASTER_PASSWORD_SZ; i++) 
						enteredMasterPW[i] = NULL_TERM;																			// empty enteredMasterPW
					memcpy(enteredMasterPW, salt, MASTER_SALT_SIZE);                 			// copy salt into the hashed master password variable
					memcpy(enteredMasterPW + MASTER_SALT_SIZE,                       			// concatenate the salt and the master password
								 enteredPassword,      																					// entered password less "FR"
								 MASTER_PASSWORD_SIZE               );
					sha256Hash(enteredMasterPW);                                     			// hash the master salt||entered password
					if (0 == memcmp(enteredMasterPW,
													eepromMasterHash,
													HASHED_MASTER_PASSWORD_SZ)) {                         // decoy password entered!
            uint8_t originalRGBLEDIntensity = RGBLEDIntensity;                  // save the setting for the RGB LED intensity
            RGBLEDIntensity = 0;                                                // don't call attention to the fact that we're wiping the device, turn off the RGB LED
            loginFailures = 1 + loginAttempts;                                  // forces the factory reset to execute
            FactoryReset();                                                     // "FR" followed by master password was entered, and decoy password feature is enabled, factory reset the device
            RGBLEDIntensity = originalRGBLEDIntensity;                          // turn the RGB LED back on (if it was ever on)
            setRed();                                                           // turn the RGB red to signal the incorrect password was provided
            return false;                                                       // do not grant admittance to the device, prepare to disappoint your attacker
          }
        }
      }
      setRed();                                                                 // turn the RGB red to signal the incorrect password was provided
      loginFailures++;                                                          // bump up login failures and
      writeLoginFailures();                                                     // save to EEprom
      return false;                                                             // authentication failed
    }
  }
  pos = 0;
  return true;
}

void sha256Hash(char *password) {                                               // hash password SHA_ITERATIONS times
  //DebugLN("sha256Hash()");
  for (int i = 0; i < SHA_ITERATIONS; i++) {
    sha256HashOnce(password);
  }
}

void sha256HashOnce(char *password) {                                           // hash password using SHA256
  //DebugLN("sha256HashOnce()");
  size_t size = strlen(password);
  if (DEBUG_ENABLED) {
    Serial.print("Size: ");Serial.println(size);
  }
  size_t posn, len;
  uint8_t value[HASHED_MASTER_PASSWORD_SZ];

  sha256.reset();
  for (posn = 0; posn < size; posn += strlen(password)) {
      len = size - posn;
      if (len > strlen(password))
          len = strlen(password);
      sha256.update(password + posn, len);
  }
  sha256.finalize(value, sizeof(value));
  sha256.clear();
  memcpy(password, value, HASHED_MASTER_PASSWORD_SZ);
}

void encrypt32Bytes(char *outBuffer, char *inBuffer) {
  //DebugLN("encrypt32Bytes()");
  uint8_t leftInBuffer[16];
  uint8_t rightInBuffer[16];

  memcpy(leftInBuffer, inBuffer, 16);
  memcpy(rightInBuffer, inBuffer + 16, 16);

  aes.encryptBlock(leftInBuffer, leftInBuffer);
  aes.encryptBlock(rightInBuffer, rightInBuffer);

  memcpy(outBuffer, leftInBuffer, 16);
  memcpy(outBuffer + 16, rightInBuffer, 16);
}

void encrypt64Bytes(char *outBuffer, char *inBuffer) {                          // TODO: make this handle any length of string to encrypt
  //DebugLN("encrypt64Bytes()");
  uint8_t firstInBuffer[16];
  uint8_t secondInBuffer[16];
  uint8_t thirdInBuffer[16];
  uint8_t fourthInBuffer[16];

  memcpy(firstInBuffer,   inBuffer,       16);
  memcpy(secondInBuffer,  inBuffer + 16,  16);
  memcpy(thirdInBuffer,   inBuffer + 32,  16);
  memcpy(fourthInBuffer,  inBuffer + 48,  16);
  
  aes.encryptBlock(firstInBuffer,   firstInBuffer);
  aes.encryptBlock(secondInBuffer,  secondInBuffer);
  aes.encryptBlock(thirdInBuffer,   thirdInBuffer);
  aes.encryptBlock(fourthInBuffer,  fourthInBuffer);
  
  memcpy(outBuffer,       firstInBuffer,  16);
  memcpy(outBuffer + 16,  secondInBuffer, 16);
  memcpy(outBuffer + 32,  thirdInBuffer,  16);
  memcpy(outBuffer + 48,  fourthInBuffer, 16);
}

void encrypt96Bytes(char *outBuffer, char *inBuffer) {                          // TODO: make this handle any length of string to encrypt
  //DebugLN("encrypt96Bytes()");
  uint8_t firstInBuffer[16];
  uint8_t secondInBuffer[16];
  uint8_t thirdInBuffer[16];
  uint8_t fourthInBuffer[16];
  uint8_t fifthInBuffer[16];
  uint8_t sixthInBuffer[16];

  memcpy(firstInBuffer,   inBuffer,       16);
  memcpy(secondInBuffer,  inBuffer + 16,  16);
  memcpy(thirdInBuffer,   inBuffer + 32,  16);
  memcpy(fourthInBuffer,  inBuffer + 48,  16);
  memcpy(fifthInBuffer,   inBuffer + 64,  16);
  memcpy(sixthInBuffer,   inBuffer + 80,  16);
  
  aes.encryptBlock(firstInBuffer,   firstInBuffer);
  aes.encryptBlock(secondInBuffer,  secondInBuffer);
  aes.encryptBlock(thirdInBuffer,   thirdInBuffer);
  aes.encryptBlock(fourthInBuffer,  fourthInBuffer);
  aes.encryptBlock(fifthInBuffer,   fifthInBuffer);
  aes.encryptBlock(sixthInBuffer,   sixthInBuffer);
  
  memcpy(outBuffer,       firstInBuffer,  16);
  memcpy(outBuffer + 16,  secondInBuffer, 16);
  memcpy(outBuffer + 32,  thirdInBuffer,  16);
  memcpy(outBuffer + 48,  fourthInBuffer, 16);
  memcpy(outBuffer + 64,  fifthInBuffer, 16);
  memcpy(outBuffer + 80,  sixthInBuffer, 16);
}

void decrypt32(char *outBuffer, char *inBuffer) {                               // Necessary because blocksize of AES128/256 = 16 bytes.
  //DebugLN("decrypt32()");
  uint8_t leftInBuf[16];
  uint8_t rightInBuf[16];

  memcpy(leftInBuf, inBuffer, 16);
  memcpy(rightInBuf, inBuffer + 16, 16);
  
  aes.decryptBlock(leftInBuf, leftInBuf);                                       // decrypt the buffer 
  aes.decryptBlock(rightInBuf, rightInBuf);                                     // decrypt the buffer 

  memcpy(outBuffer, leftInBuf, 16);
  memcpy(outBuffer + 16, rightInBuf, 16);
}

void decrypt64(char *outBuffer, char *inBuffer) {                               // Necessary because blocksize of AES128/256 = 16 bytes.
  //DebugLN("decrypt64()");
  uint8_t firstInBuf[16];
  uint8_t secondInBuf[16];
  uint8_t thirdInBuf[16];
  uint8_t fourthInBuf[16];

  memcpy(firstInBuf,  inBuffer,   16);
  memcpy(secondInBuf, inBuffer +  16, 16);
  memcpy(thirdInBuf,  inBuffer +  32, 16);
  memcpy(fourthInBuf, inBuffer +  48, 16);
  
  aes.decryptBlock(firstInBuf, firstInBuf);                                     // decrypt the buffer 
  aes.decryptBlock(secondInBuf, secondInBuf);                                   // decrypt the buffer 
  aes.decryptBlock(thirdInBuf, thirdInBuf);                                     // decrypt the buffer 
  aes.decryptBlock(fourthInBuf, fourthInBuf);                                   // decrypt the buffer 

  memcpy(outBuffer,      firstInBuf,  16);
  memcpy(outBuffer + 16, secondInBuf, 16);
  memcpy(outBuffer + 32, thirdInBuf,  16);
  memcpy(outBuffer + 48, fourthInBuf, 16);
}

void decrypt96(char *outBuffer, char *inBuffer) {                               // Necessary because blocksize of AES128/256 = 16 bytes.
  //DebugLN("decrypt32()");
  uint8_t firstInBuf[16];
  uint8_t secondInBuf[16];
  uint8_t thirdInBuf[16];
  uint8_t fourthInBuf[16];
  uint8_t fifthInBuf[16];
  uint8_t sixthInBuf[16];

  memcpy(firstInBuf,  inBuffer,   16);
  memcpy(secondInBuf, inBuffer +  16, 16);
  memcpy(thirdInBuf,  inBuffer +  32, 16);
  memcpy(fourthInBuf, inBuffer +  48, 16);
  memcpy(fifthInBuf,  inBuffer +  64, 16);
  memcpy(sixthInBuf,  inBuffer +  80, 16);
  
  aes.decryptBlock(firstInBuf, firstInBuf);                                     // decrypt the buffer 
  aes.decryptBlock(secondInBuf, secondInBuf);                                   // decrypt the buffer 
  aes.decryptBlock(thirdInBuf, thirdInBuf);                                     // decrypt the buffer 
  aes.decryptBlock(fourthInBuf, fourthInBuf);                                   // decrypt the buffer 
  aes.decryptBlock(fifthInBuf, fifthInBuf);                                     // decrypt the buffer 
  aes.decryptBlock(sixthInBuf, sixthInBuf);                                     // decrypt the buffer 

  memcpy(outBuffer,      firstInBuf,  16);
  memcpy(outBuffer + 16, secondInBuf, 16);
  memcpy(outBuffer + 32, thirdInBuf,  16);
  memcpy(outBuffer + 48, fourthInBuf, 16);
  memcpy(outBuffer + 64, fifthInBuf,  16);
  memcpy(outBuffer + 80, sixthInBuf,  16);
}

//- EEPROM functions

//- Read Attributes from EEprom

void readAcctFromEEProm(uint8_t pos, char *buf) {
  //DebugLN("readAcctFromEEProm()");
  if (pos > -1) {
    read_eeprom_array(GET_ADDR_ACCT(pos), buf, ACCOUNT_SIZE);
    if (buf[0] == (char) INITIAL_MEMORY_STATE_CHAR  ) {                                 
      buf[0] = NULL_TERM;                                                       // 8 bit twos complement of 255 or 0xFF is -1|INITIAL_MEMORY_STATE_CHAR
    } else {
      readSaltFromEEProm(pos, salt);
      uint8_t key[KEY_SIZE];
      memcpy(key, salt, SALT_SIZE); 
      memcpy(key + SALT_SIZE, masterPassword, MASTER_PASSWORD_SIZE);            // masterPassword should be padded w/ null terminator from processing in authenticateMaster
      aes.setKey(key,KEY_SIZE);                                                 // 
      decrypt32(buf, buf);
      uint8_t len = strlen(buf);
      while (len < ACCOUNT_SIZE) buf[len++] = NULL_TERM;                        // for safety
    }
  } else {
    buf[0] = NULL_TERM;
  }
}

void readUserFromEEProm(uint8_t pos, char *buf) {
  //DebugLN("readUserFromEEProm()");
  if (pos > -1) {
    read_eeprom_array(GET_ADDR_USER(pos), buf, USERNAME_SIZE);
  } else {
    buf[0] = NULL_TERM;
  }
  if (buf[0] == (char) INITIAL_MEMORY_STATE_CHAR ) {
    //buf[0] = NULL_TERM;
    for (uint8_t i = 0; i < USERNAME_SIZE; i++) buf[i] = NULL_TERM;
  } else {
    decrypt32(buf, buf);
  }
}

void readSaltFromEEProm(uint8_t pos, char *buf) {
  //DebugLN("readSaltFromEEProm()");
  if (pos > -1) {
    read_eeprom_array(GET_ADDR_SALT(pos), buf, SALT_SIZE);
  } else {
    buf[0] = NULL_TERM;
  }
  if (buf[0] == (char) INITIAL_MEMORY_STATE_CHAR  ) {
    //buf[0] = NULL_TERM;
    for (uint8_t i = 0; i < SALT_SIZE; i++) buf[i] = NULL_TERM;
  } 
}

void readWebSiteFromEEProm(uint8_t pos, char *buf) {
  //DebugLN("readWebSiteFromEEProm()");
  if (pos > -1) {
    read_eeprom_array(GET_ADDR_WEBSITE(pos), buf, WEBSITE_SIZE);
  } else {
    buf[0] = NULL_TERM;
  }
  if (buf[0] == (char) INITIAL_MEMORY_STATE_CHAR  ) {
    //buf[0] = NULL_TERM;
    for (uint8_t i = 0; i < WEBSITE_SIZE; i++) buf[i] = NULL_TERM;
  } else {
    decrypt96(buf, buf);
  }
}

void readStyleFromEEProm(uint8_t pos, char *buf) {
  //DebugLN("readStyleFromEEProm()");
  if (pos > -1) {
    read_eeprom_array(GET_ADDR_STYLE(pos), buf, STYLE_SIZE);
  } else {
    buf[0] = NULL_TERM;
  }
  if (buf[0] == (char) INITIAL_MEMORY_STATE_CHAR) {                             // if style isn't set, set it to the default
    buf[0] = DEFAULT_STYLE_CHAR;
    buf[1] = NULL_TERM;
    eeprom_write_bytes(GET_ADDR_STYLE(pos), buf, STYLE_SIZE);
  }
}

void readPassFromEEProm(uint8_t pos, char *buf) {                               // TODO: reduce readPassFromEEProm, readUserFromEEProm and readAcctFromEEProm to a single function.
  //DebugLN("readPassFromEEProm()");
  if (pos > -1) {
    read_eeprom_array(GET_ADDR_PASS(pos), buf, PASSWORD_SIZE);
  } else {
    buf[0] = NULL_TERM;
  }
  if (buf[0] == (char) INITIAL_MEMORY_STATE_CHAR  ) {
    //buf[0] = NULL_TERM;
    for (uint8_t i = 0; i < PASSWORD_SIZE; i++) buf[i] = NULL_TERM;
  } else {
    decrypt32(buf, buf);
  }
}

void readOldPassFromEEProm(uint8_t pos, char *buf) {
  //DebugLN("readOldPassFromEEProm()");
  if (pos > -1) {
    read_eeprom_array(GET_ADDR_OLD_PASS(pos), buf, PASSWORD_SIZE);
  } else {
    buf[0] = NULL_TERM;
  }
  if (buf[0] == (char) INITIAL_MEMORY_STATE_CHAR  ) {
    //buf[0] = NULL_TERM;
    for (uint8_t i = 0; i < PASSWORD_SIZE; i++) buf[i] = NULL_TERM;
  } else {
    decrypt32(buf, buf);
  }
}

uint8_t readGroupFromEEprom(uint8_t pos) {
  //DebugLN("readGroupFromEEprom()");
  uint8_t grp = read_eeprom_byte(GET_ADDR_GROUP(pos));
  if (grp == INITIAL_MEMORY_STATE_BYTE) {
    return 0;
  } else {
    return grp;
  }
}

void setListHeadPosition() {                                                    // set headPosition, the first element in the linked list
  //DebugLN("setListHeadPosition()");
  headPosition = read_eeprom_byte(GET_ADDR_LIST_HEAD);
}

uint8_t findListHeadPosition() {                                                // returns the position of the first element in the linked list
  //DebugLN("findListHeadPosition()");
  uint8_t firstFoundCred;
  for (uint8_t pos = 0; pos < CREDS_ACCOMIDATED; pos++) {
    firstFoundCred = getPrevPtr(pos);                                           // check to see if this postion is occupied by a credential...
    if (firstFoundCred != INITIAL_MEMORY_STATE_BYTE) {                          // ...and if so...
      pos = CREDS_ACCOMIDATED;                                                  // break out of the loop, a cred was found
    }
  }
  if (firstFoundCred == INITIAL_MEMORY_STATE_BYTE) return(INITIAL_MEMORY_STATE_BYTE);                                        // if no creds were found the head position is 0
  
  uint8_t prevPtr = firstFoundCred;                                             // we know we have found at least one cred
  uint8_t defendAgainstCorruption = 0;
  uint8_t currentPtr;
  do {
      currentPtr = prevPtr;
      prevPtr = getPrevPtr(currentPtr);
      if (defendAgainstCorruption++ > CREDS_ACCOMIDATED) {                      // if we're obviously inside of an infinite loop break out.
        prevPtr = INITIAL_MEMORY_STATE_BYTE;
        currentPtr = prevPtr;
        DisplayToError("ERR: 051");
      }
  } while(prevPtr != INITIAL_MEMORY_STATE_BYTE);
 
  return(currentPtr);
}

uint8_t getNextPtr(uint8_t pos) {                                               // given position, returns the address of the next element in the linked list
  //DebugLN("getNextPtr()");
  //DebugMetric("getNextPtr pos: ",pos);
  return read_eeprom_byte(GET_ADDR_NEXT_POS(pos));
}

uint8_t getPrevPtr(uint8_t pos) {                                               // given position, returns the position of the previous element in the linked list
  //DebugLN("getPrevPtr()");
  return read_eeprom_byte(GET_ADDR_PREV_POS(pos));
}

//- Write Attributes to EEprom

void writeNextPtr(uint8_t pos, uint8_t nextPtr) {                               // writes the next pointer to EEprom for position, pos.
  //DebugLN("writeNextPtr()");
  write_eeprom_byte(GET_ADDR_NEXT_POS(pos), nextPtr);
}

void writePrevPtr(uint8_t pos, uint8_t prevPtr) {                               // writes the previous pointer to EEprom for position, pos.
  //DebugLN("writePrevPtr()");
  write_eeprom_byte(GET_ADDR_PREV_POS(pos), prevPtr);
}

void writeGroup(uint8_t pos, uint8_t group) {
  //DebugLN("writeGroup()");
  write_eeprom_byte(GET_ADDR_GROUP(pos), group);
}

void writeLoginFailures() {                                                     // writes the number of login failures to EEprom
  //DebugLN("writeLoginFailures()");
  write_eeprom_byte(GET_ADDR_LOGIN_FAILURES, loginFailures);
}

void writeResetFlag(uint8_t buf) {                                              // writes the value of the reset flag to EEprom
  //DebugLN("writeResetFlag()");
  write_eeprom_byte(GET_ADDR_RESET_FLAG, buf);
}

void writeShowPasswordsFlag() {
  //DebugLN("writeShowPasswordsFlag()");
  write_eeprom_byte(GET_ADDR_SHOW_PW, showPasswordsFlag);
}

void writeDecoyPWFlag() {
  //DebugLN("writeDecoyPWFlag()");
  write_eeprom_byte(GET_ADDR_DECOY_PW, decoyPassword);
}

void writeKeyboardFlag() {
  //DebugLN("writeKeyboardFlag()");
  write_eeprom_byte(GET_ADDR_KEYBOARD_FLAG, keyboardFlag);
}

void writeListHeadPos(uint8_t pos) {                                            // writes the position of the beginning of the linked list to EEprom
  //DebugLN("writeListHeadPos()");
  write_eeprom_byte(GET_ADDR_LIST_HEAD, pos);
}

void writeRGBLEDIntensity() {
  //DebugLN("writeRGBLEDIntensity()");
  write_eeprom_byte(GET_ADDR_RGB_LED_INT, RGBLEDIntensity);
}

void writeLogoutTimeout() {
  //DebugLN("writeLogoutTimeout()");
  write_eeprom_byte(GET_ADDR_LOGOUT_TIMEOUT, logoutTimeout);
}

void writeKeyboardType() {
  //DebugLN("writeKeyboardType()");
  write_eeprom_byte(GET_ADDR_KEYBOARD_TYPE, keyboardType);
}

void writeEncoderType() {
  //DebugLN("writeEncoderType()");
  write_eeprom_byte(GET_ADDR_ENCODER_TYPE, encoderType);
}

void writeFont() {
  //DebugLN("writeFont()");
  write_eeprom_byte(GET_ADDR_FONT, font);
}

void writeOrientation() {
  //DebugLN("writeOrientation()");
  write_eeprom_byte(GET_ADDR_ORIENTATION, orientation);
}

void writeLoginAttempts() {
  //DebugLN("writeLoginAttempts()");
  write_eeprom_byte(GET_ADDR_LOGIN_ATTEM_NUM, loginAttempts);
}

void writeGenPwSize() {
  //DebugLN("writeOrientation()");
  write_eeprom_byte(GET_ADDR_GEN_PW_SIZE, generatedPasswordSize);
}

void writeInterCharPause() {
  //DebugLN("writeInterCharPause()");
  write_eeprom_byte(GET_ADDR_INTER_CHAR_PAUSE, interCharPause);
}
                                                                                // This function is used by the other, higher-level functions
                                                                                // to prevent bugs and runtime errors due to invalid addresses.
boolean eeprom_is_addr_ok(uint32_t addr) {                                      // Returns true if the address is between the
  //DebugLN("eeprom_is_addr_ok()");
  return ((addr >= MIN_AVAIL_ADDR) && (addr <= MAX_AVAIL_ADDR));                // minimum and maximum allowed values, false otherwise.
}
                                                                                // Writes a sequence of bytes to eeprom starting at the specified address.
                                                                                // Returns true if the whole array is successfully written.
                                                                                // Returns false if the start or end addresses aren't between
                                                                                // the minimum and maximum allowed values.
                                                                                // When returning false, nothing gets written to eeprom.
boolean eeprom_write_bytes( uint32_t startAddr,                                 // TODO: cut out a lot of the boundry checking to reduce the size of this function
                            char* buf,
                            uint8_t numBytes) {
                                                                                // counter
  //DebugLN("eeprom_write_bytes()");
  uint8_t i;
                                                                                // both first byte and last byte addresses must fall within
                                                                                // the allowed range 
  //if (numBytes > EEPROM_BYTES_PER_PAGE) numBytes = EEPROM_BYTES_PER_PAGE;
  write_eeprom_array(startAddr, buf, numBytes);
  return true;
}

void InitializeEEProm(void) {                                                   // Initializes all of external EEprom; sets every address = 255.
  //DebugLN("InitializeEEProm()");
  DisplayToStatus("Initializing EEprom");
  DisplayToHelp("Wait...");
  //DisableInterrupts();                                                        // disable global interrupts
  boolean colorRed = true;                                                      // show purple during healthy EEprom initialize
  uint32_t pageAddress = MIN_AVAIL_ADDR;
  while (pageAddress <= MAX_AVAIL_ADDR) {                                       
    uint8_t intensity = pageAddress%256;
    if (intensity==0) {
      colorRed = !colorRed;
    }
    if (colorRed) {
      if (RGBLEDIntensity) setColor(intensity, 0, 0);                           // Red fade in if RGB LED not disabled
    } else {
      if (RGBLEDIntensity) setColor(0,0,intensity);                             // Blue fade in if RGB LED not disabled
    }
#ifdef SLOW_SPI
    for (uint8_t i=0;i<EEPROM_BYTES_PER_PAGE;i++)
    {
      write_eeprom_byte(pageAddress + i, INITIAL_MEMORY_STATE_BYTE);            // necessary because SPI_tradeByte isn't working. 
    }
#else    
    EEPROM_writeEnable();
    initSPI();
    SPI.begin();
    SPI.beginTransaction(SPISettings(SPI_SPEED,MSBFIRST,SPI_MODE));
    SLAVE_PRIMARY_SELECT;
    SPI_tradeByte(EEPROM_WRITE);
    EEPROM_send16BitAddress(pageAddress);
    for (uint8_t i = 0; i < EEPROM_BYTES_PER_PAGE; i++) {
      SPI_tradeByte(INITIAL_MEMORY_STATE_BYTE);
    }
    SLAVE_PRIMARY_DESELECT;
    SPI.endTransaction();
    SPI.end();
    while (EEPROM_readStatus() & _BV(EEPROM_WRITE_IN_PROGRESS)) {;
    }
#endif
    pageAddress += EEPROM_BYTES_PER_PAGE;
  }
  DisplayToHelp("Done.");
  setBlue();
  //EnableInterrupts();                                                         // enable global interrupts
}

//- SPI logic                                                                   // Originally from "Make: AVR Programming", Chapter 16. SPI, by Elloit Williams, Published by Maker Media, Inc, 2014
                                                                                // https://www.safaribooksonline.com/library/view/make-avr-programming/9781449356484/ch16.html
void initSPI(void) {
  
  pinMode(SPI_SS_PRIMARY, OUTPUT);                                              // set SS output for primary EEprom chip
  digitalWrite(SPI_SS_PRIMARY, HIGH);                                           // start off not selected, disabled (high)
  pinMode(SPI_SS_SECONDARY, OUTPUT);                                            // set SS output for primary EEprom chip
  digitalWrite(SPI_SS_SECONDARY, HIGH);                                         // start off not selected, disabled (high)
  pinMode(SPI_MOSI, OUTPUT);                                                    // output on MOSI
  pinMode(SPI_MISO, INPUT_PULLUP);                                              // pullup on MISO
  pinMode(SPI_SCK, OUTPUT);                                                     // output on SCK
  digitalWrite(SPI_MOSI, LOW);
  digitalWrite(SPI_SCK, LOW);
                                                                                // Don't have to set phase, polarity b/c default works with 25LCxxx chips
//SPI.beginTransaction(SPISettings(SPI_SPEED,MSBFIRST,SPI_MODE));               // max clock = 5mhz @ 3.3v 
}

uint8_t SPI_tradeByte(uint8_t val) {
  //DebugLN("SPI_tradeByte()");
  uint8_t receivedVal = SPI.transfer(val);                                      // receivedVal now contains the received byte
  return receivedVal;
}

void EEPROM_send16BitAddress(uint32_t address) {
  //DebugLN("EEPROM_send16BitAddress()");
  SPI.transfer16(address);
}

uint8_t EEPROM_readStatus(void) {
  //DebugLN("EEPROM_readStatus()");
  SPI.begin();                                                                  // Initializes the SPI bus by setting SCK, MOSI, and SS to outputs, pulling SCK and MOSI low, and SS high.
  SPI.beginTransaction(SPISettings(SPI_SPEED,MSBFIRST,SPI_MODE));               // max clock = 5mhz @ 3.3v 
  SLAVE_PRIMARY_SELECT;
  SPI_tradeByte(EEPROM_RDSR);
  uint8_t result = SPI_tradeByte(0);                                            // clock out eight bits
  SLAVE_PRIMARY_DESELECT;
  SPI.endTransaction();
  SPI.end();                                                                    // Disables the SPI bus (leaving pin modes unchanged).
  return result;                                                                // return the result
}

uint8_t EEPROM_readStatusSecondary(void) {
  //DebugLN("EEPROM_readStatusSecondary()");
  SPI.begin();                                                                  // Initializes the SPI bus by setting SCK, MOSI, and SS to outputs, pulling SCK and MOSI low, and SS high.
  SPI.beginTransaction(SPISettings(SPI_SPEED,MSBFIRST,SPI_MODE));               // max clock = 5mhz @ 3.3v 
  SLAVE_SECONDARY_SELECT;
  SPI_tradeByte(EEPROM_RDSR);
  uint8_t result = SPI_tradeByte(0);                                            // clock out eight bits
  SLAVE_SECONDARY_DESELECT;
  SPI.endTransaction();
  SPI.end();                                                                    // Disables the SPI bus (leaving pin modes unchanged).
  return result;                                                                // return the result
}

void EEPROM_writeEnable(void) {
  //DebugLN("EEPROM_writeEnable()");
  SPI.begin();                                                                  // Initializes the SPI bus by setting SCK, MOSI, and SS to outputs, pulling SCK and MOSI low, and SS high.
  SPI.beginTransaction(SPISettings(SPI_SPEED,MSBFIRST,SPI_MODE));               // max clock = 5mhz @ 3.3v 
  SLAVE_PRIMARY_SELECT;
  SPI_tradeByte(EEPROM_WREN);
  SLAVE_PRIMARY_DESELECT;
  SPI.endTransaction();
  SPI.end();                                                                    // Disables the SPI bus (leaving pin modes unchanged).
}

void EEPROM_writeEnableSecondary(void) {
  //DebugLN("EEPROM_writeEnableSecondary");
  SPI.begin();                                                                  // Initializes the SPI bus by setting SCK, MOSI, and SS to outputs, pulling SCK and MOSI low, and SS high.
  SPI.beginTransaction(SPISettings(SPI_SPEED,MSBFIRST,SPI_MODE));               // max clock = 5mhz @ 3.3v 
  SLAVE_SECONDARY_SELECT;
  SPI_tradeByte(EEPROM_WREN);
  SLAVE_SECONDARY_DESELECT;
  SPI.endTransaction();
  SPI.end();                                                                    // Disables the SPI bus (leaving pin modes unchanged).
}

void TestEEPromRead() {
  uint8_t aByte;
  //DebugLN("");
  //DebugLN("Reading...");
  //for (uint32_t address = MIN_AVAIL_ADDR; address < MAX_AVAIL_INT_ADDR; address++) {
  for (uint32_t address = MIN_AVAIL_ADDR; address < 128; address++) {
    aByte = read_eeprom_byte(address);
    if (DEBUG_ENABLED) {
      Serial.print(aByte);Serial.print(' ');
      if (address%64==0) Serial.println("");
    }
  }
}

void TestEEPromWrite() {
  //DebugLN("");
  //DebugLN("Writing...");
  //for (uint32_t address = MIN_AVAIL_ADDR; address < MAX_AVAIL_INT_ADDR; address++) {
  for (uint32_t address = MIN_AVAIL_ADDR; address < 128; address++) {
    write_eeprom_byte(address, address%64);
    if (DEBUG_ENABLED) {
      Serial.print(address%64);Serial.print(' ');
      if(address%64 ==0) Serial.println("");
    }
  }
}

void InitAllEEProm() {
  //DebugLN("");
  //DebugLN("Initializing...");
  for (uint32_t address = MIN_AVAIL_ADDR; address < MAX_AVAIL_ADDR; address++) {
    write_eeprom_byte(address, 0xFF);
    if (DEBUG_ENABLED) {
      Serial.print(".");
      if (address%64==0) Serial.println("");
    }
  }
}

uint8_t read_eeprom_byte(uint32_t address) {
  //DebugMetric("read_eeprom_byte(), Address: ",address);
  //DisableInterrupts();                                                        // disable global interrupts
  SPI.begin();                                                                  // Initializes the SPI bus by setting SCK, MOSI, and SS to outputs, pulling SCK and MOSI low, and SS high.
  SPI.beginTransaction(SPISettings(SPI_SPEED,MSBFIRST,SPI_MODE));               // max clock = 5mhz @ 3.3v 
  SLAVE_PRIMARY_SELECT;
  SPI_tradeByte(EEPROM_READ);
  EEPROM_send16BitAddress(address);
  uint8_t result = SPI_tradeByte(0);
  SLAVE_PRIMARY_DESELECT;
  SPI.endTransaction();
  SPI.end();                                                                    // Disables the SPI bus (leaving pin modes unchanged).
  //EnableInterrupts();                                                         // enable global interrupts
  return result;
}

void read_eeprom_array( uint32_t address,                                       // TODO: is the read wrapping around when sizeOfBuffer exceeds page size?
                        char *buffer, 
                        uint8_t sizeOfBuffer  ) {                               // READ EEPROM bytes
  //DebugLN("read_eeprom_array()");
  //DisableInterrupts();                                                        // disable global interrupts
  SPI.begin();                                                                  // Initializes the SPI bus by setting SCK, MOSI, and SS to outputs, pulling SCK and MOSI low, and SS high.
  SPI.beginTransaction(SPISettings(SPI_SPEED,MSBFIRST,SPI_MODE));               // max clock = 5mhz @ 3.3v 
  SLAVE_PRIMARY_SELECT;
  SPI_tradeByte(EEPROM_READ);
  EEPROM_send16BitAddress(address);
  for (uint8_t i = 0; i < sizeOfBuffer; i++) {
    uint8_t result = SPI_tradeByte(0);
    *buffer++ = result;                                                         // get data byte
  }
  SLAVE_PRIMARY_DESELECT;
  SPI.endTransaction();
  SPI.end();                                                                    // Disables the SPI bus (leaving pin modes unchanged).
  //EnableInterrupts();                                                         // enable global interrupts
}

void read_eeprom_array_secondary( uint32_t address, 
                                  char *buffer, 
                                  uint8_t sizeOfBuffer  ) {                     // READ EEPROM bytes
  //DebugLN("read_eeprom_array_secondary()");
  //DisableInterrupts();                                                        // disable global interrupts
  SPI.begin();                                                                  // Initializes the SPI bus by setting SCK, MOSI, and SS to outputs, pulling SCK and MOSI low, and SS high.
  SPI.beginTransaction(SPISettings(SPI_SPEED,MSBFIRST,SPI_MODE));               // max clock = 5mhz @ 3.3v 
  SLAVE_SECONDARY_SELECT;
  SPI_tradeByte(EEPROM_READ);
  EEPROM_send16BitAddress(address);
  for (uint8_t i = 0; i < sizeOfBuffer; i++) {
    uint8_t result = SPI_tradeByte(0);
    *buffer++ = result;                                                         // get data byte
  }
  SLAVE_SECONDARY_DESELECT;
  SPI.endTransaction();
  SPI.end();                                                                    // Disables the SPI bus (leaving pin modes unchanged).
  //EnableInterrupts();                                                         // enable global interrupts
}

void write_eeprom_byte(uint32_t address, uint8_t byte) {
  //DebugLN("write_eeprom_byte()");
  EEPROM_writeEnable();
  SPI.begin();                                                                  // Initializes the SPI bus by setting SCK, MOSI, and SS to outputs, pulling SCK and MOSI low, and SS high.
  SPI.beginTransaction(SPISettings(SPI_SPEED,MSBFIRST,SPI_MODE));               // max clock = 5mhz @ 3.3v 
  SLAVE_PRIMARY_SELECT;
  SPI_tradeByte(EEPROM_WRITE);
  EEPROM_send16BitAddress(address);
  SPI_tradeByte(byte);
  SLAVE_PRIMARY_DESELECT;
  SPI.endTransaction();
  SPI.end();                                                                    // Disables the SPI bus (leaving pin modes unchanged).
  while (EEPROM_readStatus() & _BV(EEPROM_WRITE_IN_PROGRESS)) {;
  }
}

void write_eeprom_byte_secondary(uint32_t address, uint8_t byte) {
  //DebugLN("write_eeprom_byte()");
  EEPROM_writeEnableSecondary();
  SPI.begin();                                                                  // Initializes the SPI bus by setting SCK, MOSI, and SS to outputs, pulling SCK and MOSI low, and SS high.
  SPI.beginTransaction(SPISettings(SPI_SPEED,MSBFIRST,SPI_MODE));               // max clock = 5mhz @ 3.3v 
  SLAVE_SECONDARY_SELECT;
  SPI_tradeByte(EEPROM_WRITE);
  EEPROM_send16BitAddress(address);
  SPI_tradeByte(byte);
  SLAVE_SECONDARY_DESELECT;
  SPI.endTransaction();
  SPI.end();                                                                    // Disables the SPI bus (leaving pin modes unchanged).
  while (EEPROM_readStatusSecondary() & _BV(EEPROM_WRITE_IN_PROGRESS)) {;
  }
}

void write_eeprom_array(uint32_t passedAddress,                                 // TODO: Stop trying to write across the page boundary!
                        char *buffer, 
                        uint8_t sizeOfBuffer) {                                 // if > EEPROM_BYTES_PER_PAGE, an even multiple of EEPROM_BYTES_PER_PAGE
  //DisableInterrupts();                                                        // disable global interrupts
  //DebugLN("write_eeprom_array()");
  for(uint8_t baseArrayAddr = 0;
      baseArrayAddr < sizeOfBuffer;
      baseArrayAddr += EEPROM_BYTES_PER_PAGE) {

    uint8_t toSubscript;
    if ((sizeOfBuffer - baseArrayAddr) < EEPROM_BYTES_PER_PAGE) {
      toSubscript = sizeOfBuffer - baseArrayAddr;
    } else {
      toSubscript = EEPROM_BYTES_PER_PAGE;
    }

    uint32_t address = passedAddress + baseArrayAddr;
    
#ifdef SLOW_SPI 
    for (uint8_t i=0;i<toSubscript;i++)
    {
      write_eeprom_byte(address + i, buffer[baseArrayAddr+i]);
    }
//    for (uint8_t i=0;i<sizeOfBuffer;i++)
//    {
//      write_eeprom_byte(address + i, buffer[i]);
//    }
#else
    EEPROM_writeEnable();
    SPI.begin();                                                                // Initializes the SPI bus by setting SCK, MOSI, and SS to outputs, pulling SCK and MOSI low, and SS high.
    SPI.beginTransaction(SPISettings(SPI_SPEED,MSBFIRST,SPI_MODE));             // max clock = 5mhz @ 3.3v 
    SLAVE_PRIMARY_SELECT;
    SPI_tradeByte(EEPROM_WRITE);
    EEPROM_send16BitAddress(address);
    
    for (uint8_t i=0;i<toSubscript;i++)
    {
      SPI_tradeByte(buffer[baseArrayAddr+i]);
    }
//    for (uint8_t i=0;i<sizeOfBuffer;i++)
//    {
//      SPI_tradeByte(buffer[i]);
//    }
    SLAVE_PRIMARY_DESELECT;
    SPI.endTransaction();
    SPI.end();                                                                  // Disables the SPI bus (leaving pin modes unchanged).
    while (EEPROM_readStatus() & _BV(EEPROM_WRITE_IN_PROGRESS)) {;
    }  
#endif
  }
  //EnableInterrupts();                                                         // enable global interrupts
}

void CopyEEPromToBackup() {                                                     // Make a byte for byte duplicate of the primary external EEprom device
  //DebugLN("CopyEEPromToBackup()");                                              // flash the LED red and yellow during this operation
  //DisableInterrupts();                                                        // disable global interrupts
  DisplayToStatus("Backing up...");
  DisplayToHelp("Wait...");
  write_eeprom_byte(GET_ADDR_KEYBOARD_FLAG, false);                             // keyboard should always be off for a restored backup.
  char buffer[EEPROM_BYTES_PER_PAGE];                                           // make a buffer the same size as the page size.
  boolean colorRed = true;
  for ( uint32_t address = MIN_AVAIL_ADDR; 
        address < MAX_AVAIL_ADDR; 
        address += EEPROM_BYTES_PER_PAGE) {
    if (colorRed) {                                                             // if everything is working correctly user will see purple
      setRed();                                                                 // make the LED red...
      colorRed = false;
    } else {
      setYellow();                                                              // make the LED yellow...
      colorRed = true;
    }
    read_eeprom_array(address, buffer, EEPROM_BYTES_PER_PAGE);                  // read in a page at a time from the primary/source device

#ifdef SLOW_SPI
    for (uint8_t i=0;i<EEPROM_BYTES_PER_PAGE;i++) {                             // write the page out byte for byte
      write_eeprom_byte_secondary(address + i, buffer[i]);
    }
#else
    SPI.begin();                                                                // Initializes the SPI bus by setting SCK, MOSI, and SS to outputs, pulling SCK and MOSI low, and SS high.
    SPI.beginTransaction(SPISettings(SPI_SPEED,MSBFIRST,SPI_MODE));             // max clock = 5mhz @ 3.3v 
    SLAVE_SECONDARY_SELECT;
    SPI_tradeByte(EEPROM_WREN);                                                 // write enable secondary
    SLAVE_SECONDARY_DESELECT;
    SPI.endTransaction();
    SPI.end();
    SPI.begin();
    SPI.beginTransaction(SPISettings(SPI_SPEED,MSBFIRST,SPI_MODE));
    SLAVE_SECONDARY_SELECT;                                                     // select the secondary EEprom device for SPI
    SPI_tradeByte(EEPROM_WRITE);
    EEPROM_send16BitAddress(address);
    for (uint8_t i = 0; i < EEPROM_BYTES_PER_PAGE; i++) {
      SPI_tradeByte(buffer[i]);
    }
    SLAVE_SECONDARY_DESELECT;                                                   // deselect the secondary EEprom device for SPI
    SPI.endTransaction();
    SPI.end();                                                                  // Disables the SPI bus (leaving pin modes unchanged).
    while (EEPROM_readStatusSecondary() & _BV(EEPROM_WRITE_IN_PROGRESS)) {
    }
#endif
  }
  write_eeprom_byte(GET_ADDR_KEYBOARD_FLAG, keyboardFlag);                      // set keyboard flag back to what it was before this operation started
  setGreen();
  DisplayToStatus("Backed up");
  DisplayToHelp("Done.");
  //EnableInterrupts();                                                         // done with the copy, re-enable global interrupts
}

void RestoreEEPromBackup() {                                                    // From Secondary to Primary, make a byte for byte duplicate of the backup external EEprom device
  //DebugLN("RestoreEEPromBackup()");
  //DisableInterrupts();                                                        // disable global interrupts
  DisplayToStatus("Restoring...");
  DisplayToHelp("Wait...");
  char buffer[EEPROM_BYTES_PER_PAGE];                                           // make a buffer the same size as the page size.
  boolean colorRed = true;
  for ( uint32_t address = MIN_AVAIL_ADDR; 
        address < MAX_AVAIL_ADDR; 
        address += EEPROM_BYTES_PER_PAGE) {
    if (colorRed) {                                                             // if everything is working correctly user will see purple
      setRed();
      colorRed = false;
    } else {
      setYellow();
      colorRed = true;
    }
    read_eeprom_array_secondary(address, buffer, EEPROM_BYTES_PER_PAGE);        // read in a page at a time from the backup device
#ifdef SLOW_SPI
    for (uint8_t i=0;i<EEPROM_BYTES_PER_PAGE;i++) {                             // write the page out byte for byte
      write_eeprom_byte(address + i, buffer[i]);
    }
#else
    SPI.begin();                                                                // Initializes the SPI bus by setting SCK, MOSI, and SS to outputs, pulling SCK and MOSI low, and SS high.
    SPI.beginTransaction(SPISettings(SPI_SPEED,MSBFIRST,SPI_MODE));             // max clock = 5mhz @ 3.3v 
    SLAVE_PRIMARY_SELECT;
    SPI_tradeByte(EEPROM_WREN);                                                 // write enable primary
    SLAVE_PRIMARY_DESELECT;
    SPI.endTransaction();
    SPI.end();
    SPI.begin();
    SPI.beginTransaction(SPISettings(SPI_SPEED,MSBFIRST,SPI_MODE));
    SLAVE_PRIMARY_SELECT;                                                       // select the primary EEprom device for SPI
    SPI_tradeByte(EEPROM_WRITE);
    EEPROM_send16BitAddress(address);
    for (uint8_t i = 0; i < EEPROM_BYTES_PER_PAGE; i++) {
      SPI_tradeByte(buffer[i]);
    }
    SLAVE_PRIMARY_DESELECT;                                                     // deselect the primary EEprom device for SPI
    SPI.endTransaction();
    SPI.end();                                                                  // Disables the SPI bus (leaving pin modes unchanged).
    while (EEPROM_readStatus() & _BV(EEPROM_WRITE_IN_PROGRESS)) {
    }
#endif
  }
  setListHeadPosition();                                                        // set headPosition. read the head of the doubly linked list that sorts by account name
  acctPosition = headPosition;
  tailPosition = findTailPosition(headPosition);                                // find the tail of the doubly linked list that sorts by account name
  acctCount = countAccounts();                                                  // count the number of populated accounts in EEprom
  setGreen();
  DisplayToStatus("Creds Restored");
  DisplayToHelp("Done.");
  //EnableInterrupts();                                                         // done with the copy, re-enable global interrupts
}

//- Linked List Routines  

uint8_t countAccounts() {                                                       // count all of the account names from EEprom.
  //DebugLN("countAccounts()");
  setListHeadPosition();
  if (headPosition == INITIAL_MEMORY_STATE_BYTE ||                              // return 0 if the head position is 255 or the account name at the head position is null.
      read_eeprom_byte(GET_ADDR_ACCT(headPosition)) == INITIAL_MEMORY_STATE_BYTE) {
    return(0);
  }
  uint8_t count = 0;
  uint8_t pos = headPosition;
  while(pos != INITIAL_MEMORY_STATE_BYTE) {
    count++;
    uint8_t prevPos = pos;
    pos = getNextPtr(pos);
    if (pos == prevPos) {
      DisplayToError("ERR: 041");
      return(count);
    }
    if (count > CREDS_ACCOMIDATED) {
      DisplayToError("ERR: 054");
      return(0);
    }
  }
  return(count);
}

uint8_t getNextFreeAcctPos() {                                                  // return the position of the next EEprom location for account name marked empty.
  //DebugLN("getNextFreeAcctPos()");
  for(uint8_t acctPos = 0; acctPos < CREDS_ACCOMIDATED; acctPos++) {    
      if ((read_eeprom_byte(GET_ADDR_ACCT(acctPos)) == 
           INITIAL_MEMORY_STATE_BYTE                   ) &&
          (acctPos != 124                              )) {
        return acctPos;
      }
  }
 return INITIAL_MEMORY_STATE_BYTE;                                              // 255 unsigned int
}

uint8_t findTailPosition(uint8_t pos) {                                         // find the position of the last element in the linked list
  uint8_t nextPos;
  //DebugLN("findTailPosition()");
  if (pos != INITIAL_MEMORY_STATE_BYTE) {
    uint8_t defendAgainstCorruption = 0;
    while (getNextPtr(pos) != INITIAL_MEMORY_STATE_BYTE) {                        // the last element in the linked list will always have a nextPtr that points to INITIAL_MEMORY_STATE_BYTE
      nextPos = getNextPtr(pos);
      if (pos == nextPos) {
        //DebugLN("Infinite loop detected in findTailPosition().  Corruption. ");
        //DebugMetric("getNextPointer(pos) returned: ",nextPos);
        DisplayToError("ERR: 011");
        DisplayToItem("Restore backup");
        return(pos);
      } else {
        pos = nextPos;
      }
      if (defendAgainstCorruption++ > CREDS_ACCOMIDATED) {
        DisplayToError("ERR: 053");
        return(INITIAL_MEMORY_STATE_BYTE);
      }
    }
  }
  return(pos);
}

void writePointers(uint8_t accountPosition, char *accountName) {                // traverse through the linked list finding the right spot to insert this record in the list
  //DebugLN("writePointers()");
  //DebugLN("--------------");
  //DebugMetric("accountPosition: ",accountPosition);
  //DebugMetric("headPosition: ",headPosition);
  //DebugMetric("tailPosition: ",tailPosition);
  if ((headPosition    == INITIAL_MEMORY_STATE_BYTE) &&
      (tailPosition    == INITIAL_MEMORY_STATE_BYTE) &&
      (accountPosition == 0)   ) {                                              // this is the first element added to the linked list
    //DebugLN("2");
    headPosition = 0;
    tailPosition = 0;
    writeListHeadPos(0);
    writePrevPtr(0, INITIAL_MEMORY_STATE_BYTE);
    writeNextPtr(0, INITIAL_MEMORY_STATE_BYTE);
    return;
  }
  
  char acctBuf[ACCOUNT_SIZE];                                                   // a buffer large enough to accomodate the account name
  uint8_t currentPosition = headPosition;                                       // pointer to the position we're at as we step through the linked list
  //DebugMetric("3: ",currentPosition);
  uint8_t prevPosition = getPrevPtr(currentPosition);                           // should always be INTIAL_MEMORY_STATE_BYTE.  This IS necessary.
  //DebugMetric("4: ",prevPosition);
  readAcctFromEEProm(currentPosition, acctBuf);                                 // reading the accountName for the head, decrypt
  //Debug("5: ");DebugLN(acctBuf);
  while ((currentPosition != INITIAL_MEMORY_STATE_BYTE   ) &&                   // loop thru the list until we find the 1st position where the passed accountName is > account name of currentPosition
         (strncmp(acctBuf, accountName, ACCOUNT_SIZE) < 0)     ) {              // if Return value < 0 then it indicates str1 is less than str2.
    prevPosition = currentPosition;                                             // save prevPosition as currentPosition because we'll eventually step over the element that's > accountPosition
    //DebugMetric("6: ",prevPosition);
    currentPosition = getNextPtr(currentPosition);                              // move to the next element in the linked list
    //DebugMetric("7: ",currentPosition);
    readAcctFromEEProm(currentPosition,acctBuf);                                // read that account name from EEprom, decrypt
    //Debug("8: ");DebugLN(acctBuf);
  }
  if(currentPosition == headPosition) {                                         // inserting before the first element in the list
    headPosition = accountPosition;
    //DebugMetric("9: ",headPosition);
    writeListHeadPos(headPosition);
  }
  if (currentPosition == INITIAL_MEMORY_STATE_BYTE) {                           // inserting an element at the end of the linked list
    tailPosition = accountPosition;
    //DebugMetric("10: ",tailPosition);
  }
  writePrevPtr(accountPosition, prevPosition   );                               // insert between prevPosition and currentPosition
  //DebugMetric("11: ",prevPosition);
  writeNextPtr(accountPosition, currentPosition);
  //DebugMetric("12: ",currentPosition);
  if (prevPosition != INITIAL_MEMORY_STATE_BYTE) {                              // if we're not the new head
    //DebugLN("13");
    writeNextPtr(prevPosition, accountPosition);                                // update the next pointer of the previous element with the account position.
  }
  if (currentPosition != INITIAL_MEMORY_STATE_BYTE) {                           // if we're not the next element of the tail
    //DebugMetric("14: ",accountPosition);
    writePrevPtr(currentPosition, accountPosition);                             // write set the previous pointer of the current element to the account position
  }
}

void stompPointers(uint8_t accountPosition) {                                   // stomp on the pointers at this account position
  //DebugLN("stompPointers()");
  writePrevPtr(accountPosition, INITIAL_MEMORY_STATE_BYTE);
  writeNextPtr(accountPosition, INITIAL_MEMORY_STATE_BYTE);
  return;
}

void FixCorruptLinkedList() {                                                   // Rebuild the linked list to fix any issues with the pointers
  //DebugLN("FixCorruptLinkedList()");
  //DisableInterrupts();
  setRed();
  DisplayToMenu("Fixing corruption");
  headPosition = INITIAL_MEMORY_STATE_BYTE;
  writeListHeadPos(headPosition);
  tailPosition = 0;
  for (uint8_t pos = 0; pos < CREDS_ACCOMIDATED; pos++) {                // Visit every possible location for a set of creds
    char buffer[ACCOUNT_SIZE];                                                  // a buffer that will accomodate the account name
    char snum[3];
    char strToDisplay[DISPLAY_BUFFER_SIZE];
    if (pos % 5 == 0) {                                                         // Flash red and yellow
      if (isRed) {
        setYellow();
      } else {
        setRed();
      }
    }
    buffer[0] = NULL_TERM;
    itoa(pos, snum, 10);                                                        // convert pos to a string representation
    readAcctFromEEProm(pos, buffer);                                            // get the name of the account at this position, if any. readAcctFromEEProm sets buffer[0] = NULL_TERM if buffer[0] == (char) INITIAL_MEMORY_STATE_CHAR
    if (buffer[0] != NULL_TERM) {                                               // if true then creds have been written to this location
      writePointers(pos, buffer);                                               // set the previous and next pointers on this set of credentials
      strcpy(strToDisplay, "Fixed   #:");                                       // copy the string "Acct#: " to the var strToDisplay
    } else {
      stompPointers(pos);                                                       // set the pointers to INITIAL_MEMORY_STATE_BYTE at this position; stomp them!
      strcpy(strToDisplay, "Skipped #:");                                       // copy the string "Acct#: " to the var strToDisplay
    }
    strcat(strToDisplay, snum);                                                 // concatinate the string representation of pos to strToDisplay
    DisplayToItem(strToDisplay);
  }
  uint8_t originalHeadPosition = headPosition;
  DisplayToItem("Finding head pos");
  headPosition = findListHeadPosition();
  writeListHeadPos(headPosition);
  if (originalHeadPosition != headPosition) {
    DisplayToError("ERR: 052");
  }
  acctPosition = headPosition;
  DisplayToItem("Finding tail pos");
  tailPosition = findTailPosition(headPosition);                                // find the tail of the doubly linked list that sorts by account name
  position = 1;                                                                 // make the menu position Find Accounts
  acctCount = countAccounts();                                                  // count the number of populated accounts in EEprom
  setGreen();
  DisplayToItem("Fixed corruption");
  //EnableInterrupts();
}

//- Debugging Routines  

void Debug(char *text){
  if (DEBUG_ENABLED) {
    Serial.print(text);
  }
}

void DebugLN(char *text){
  if (DEBUG_ENABLED) {
    Serial.println(text);
  }
}

void DebugMetric(char *text, uint8_t number) {
  if (DEBUG_ENABLED) {
    Serial.print(text);Serial.println(number);
  }
}

//- Interrupts

void EnableInterrupts() {
  if (!interruptsOn) {
    interruptsOn = true;
    interrupts();
  }
}

void DisableInterrupts() {
  if (interruptsOn) {
    noInterrupts();
    interruptsOn = false;
  }
}

//- non-Blocking Delay

void delayNoBlock(unsigned long delayTime) {
  boolean initialInterruptState = interruptsOn;
  EnableInterrupts();
  unsigned long currentTime = millis();
  while (millis() < currentTime + delayTime){}
  if (initialInterruptState == false) {                                         // if interrupts were off when this function was called, turn them back off.
    DisableInterrupts();
  }
}

// - Change the master password

void ChangeMasterPassword(char *passedNewPassword) {                            // change masterPassword to passedNewPassword
  setYellow();
  DisplayToStatus("Backing up");
  DisplayToHelp("Wait...");
  CopyEEPromToBackup();                                                         // Copy everything from primary to secondary EEprom
  DisplayToStatus("Changing master pass");

  char localNewPassword[MASTER_PASSWORD_SIZE];
  
  strncpy(localNewPassword, passedNewPassword, MASTER_PASSWORD_SIZE);           // populate localNewPassword with the passed new master password
  
  uint8_t len = strlen(localNewPassword);
  while (len < MASTER_PASSWORD_SIZE) localNewPassword[len++] = NULL_TERM;       // right pad the new password w/ null terminators

  setRed();
  for (uint8_t pos = 0; pos < CREDS_ACCOMIDATED; pos++) {                       // TODO: ? Might want to go through the linked list instead.
    byte aByte = read_eeprom_byte(GET_ADDR_ACCT(pos));
    if ((aByte == NULL_TERM) || (aByte == INITIAL_MEMORY_STATE_BYTE)) continue; // skip this iteration of the for loop, there are no credentials here
    char accountName[ACCOUNT_SIZE];
    char username[USERNAME_SIZE];                                               // holds the user name of the current account
    char salt[SALT_SIZE];                                                       // holds the salt for each set of credentials
    char website[WEBSITE_SIZE];                                                 // holds the URL for the credentials
    char style[STYLE_SIZE];                                                     // holds the style of the current account (<TAB> or <CR> between send user name and password)
    char password[PASSWORD_SIZE];                                               // holds the password of the current account
    char oldPassword[PASSWORD_SIZE];                                            // holds the previous password of the current account

    char localNewSalt[SALT_SIZE];                                               // for the new salt associated with this set of credentials
    readSaltFromEEProm(pos, localNewSalt);                                      // 
    readAcctFromEEProm(pos, accountName);                                       // when you call readAcctFromEEProm, the salt is read, the key is set for you, result is decrypted
    DisplayToStatus(accountName);                                               // show the account name on the status line
    readUserFromEEProm(pos, username);                                          // read and decrypt the user name
    readWebSiteFromEEProm(pos, website);                                        // read and decrypt the web site
    readStyleFromEEProm(pos, style);                                            // not encrypted
    readPassFromEEProm(pos, password);                                          // read and decrypt the password
    readOldPassFromEEProm(pos, oldPassword);                                    // read and decrypt the old password
                                                                                // declare placeholders for encrypted text
    char bufferAcct[ACCOUNT_SIZE];                                              // encrypted account
    char bufferUser[USERNAME_SIZE];                                             // encrypted user name
    char bufferWebsite[WEBSITE_SIZE];                                           // encrypted web site
    char bufferPass[PASSWORD_SIZE];                                             // encrypted password
    char bufferOldPass[OLD_PASSWORD_SIZE];                                      // encrypted old password

                                                                                // setup the new key
    uint8_t localNewKey[KEY_SIZE];                                              // set the key so we're prepared when we write the account to EEprom
    memcpy(localNewKey, localNewSalt, SALT_SIZE);                               // copy the localNewSalt to the first part of the localNewKey
    memcpy(localNewKey + SALT_SIZE, localNewPassword, MASTER_PASSWORD_SIZE);    // copy the new master password to the second part of the key, masterPassword should be padded w/ null terminator from processing in authenticateMaster
    //Debug("localNewKey: ");DebugLN((char *) localNewKey);
    aes.setKey(localNewKey, KEY_SIZE);                                          // set the key for this set of credentials

    encrypt32Bytes(bufferAcct, accountName);                                    // encrypt the account name
    boolean prefixIniMemState = false;                                          // indicates if the encrypted account name starts with 255; which is a problem when we are looking for new empty credential space
    while (bufferAcct[0] == (char) INITIAL_MEMORY_STATE_CHAR) {                 // check to see if we have an invalid condition after encryption, if we do,
      prefixIniMemState = true;                                                 // trim characters until the first char in the cipher isn't 255.
      len = strlen(accountName);
      if (len > 2) {
        accountName[len - 1] = NULL_TERM;                                       // Chop a character off the end of the account name
        encrypt32Bytes(bufferAcct, accountName);                                // encrypt again and hope for the best
        prefixIniMemState = false;                                              // assume the problem is fixed...
      } else {
        DisplayToError("ERR: 027");                                             // display the error to the screen and continue processing.  
        break;
      }
    }
    if (!prefixIniMemState) {
      eeprom_write_bytes(GET_ADDR_ACCT(pos), bufferAcct, ACCOUNT_SIZE);         // write the account name to eeprom
    } else {
      encrypt32Bytes(bufferAcct, "Unknown");                                    // encrypt again and hope for the best
      eeprom_write_bytes(GET_ADDR_ACCT(pos), bufferAcct, ACCOUNT_SIZE);         // write "Unknown" account name to eeprom
    }

    encrypt32Bytes(bufferUser, username);                                       // encrypt the user name
    eeprom_write_bytes(GET_ADDR_USER(pos), bufferUser, USERNAME_SIZE);          // write the user name to eeprom
  
    encrypt96Bytes(bufferWebsite, website);                                     // encrypt the 64 byte long website
    eeprom_write_bytes(GET_ADDR_WEBSITE(pos), bufferWebsite, WEBSITE_SIZE);     // write the website to eeprom
  
    eeprom_write_bytes(GET_ADDR_STYLE(pos), style, STYLE_SIZE);                 // write the style to eeprom
    
    encrypt32Bytes(bufferPass, password);                                       // encrypt the password
    eeprom_write_bytes(GET_ADDR_PASS(pos), bufferPass, PASSWORD_SIZE);          // write the password to eeprom
  
    encrypt32Bytes(bufferOldPass, oldPassword);                                 // encrypt the old password
    eeprom_write_bytes(GET_ADDR_OLD_PASS(pos), bufferOldPass, PASSWORD_SIZE);   // write the password to eeprom

    if (isRed) {                                                                // if the RGB LED is red set it to yellow, if it is yellow set it to red
      setYellow();
    } else {
      setRed();
    }
  }                                                                             // end for
                                                                                // now save the new hashed master password and a new salt
  char eepromMasterHash[HASHED_MASTER_PASSWORD_SZ];                             // this will hold the hashed master password
  setSalt(masterSalt, MASTER_SALT_SIZE);                                        // generate a random salt, store global masterSalt
  eeprom_write_bytes(GET_ADDR_MASTER_SALT, masterSalt, MASTER_SALT_SIZE);       // save the un-encrypted/un-hashed salt to EEprom
  memcpy(eepromMasterHash, masterSalt, MASTER_SALT_SIZE);                       // copy salt into the hashed master password variable
  memcpy(eepromMasterHash + MASTER_SALT_SIZE,                                   // concatenate the salt and the new master password
         localNewPassword, 
         MASTER_PASSWORD_SIZE                          );
  sha256Hash(eepromMasterHash);                                                 // hash the new master password in place with the new salt; pass in 32, get back 32
  eeprom_write_bytes( GET_ADDR_MASTER_HASH,                                     // only write the first 16 bytes of the hashed master password
                      eepromMasterHash, 
                      HASHED_MASTER_PASSWORD_SZ);                               // write the (hashed) master password to EEprom
  
  memcpy(masterPassword, localNewPassword, MASTER_PASSWORD_SIZE);               // populate global masterPassword with the new master password.
  
  setGreen();
  DisplayToStatus("Changed master pass");
  DisplayToHelp("Done.");
}

uint8_t FindAccountPos(char *passedAccountName) {                               // TODO: improve performance with a binary search through the doubly linked list here
  uint8_t pos = headPosition;
  uint16_t i = 0;                                                               // to be safe, count the iterations and show an error if they exceed credentials accommodated.
  updateExistingAccount = false;                                                // assume we're not updating an existing account
  if (strlen(passedAccountName) > (ACCOUNT_SIZE - 1)) {                         
    passedAccountName[ACCOUNT_SIZE - 1] = NULL_TERM;
  }
  while ((pos != INITIAL_MEMORY_STATE_BYTE) &&
         (i++ <= CREDS_ACCOMIDATED        )   ){
    char accountName[ACCOUNT_SIZE];
    readAcctFromEEProm(pos, accountName);                                       // read and decrypt the account name; when in readAcctFromEEProm, if account[0] = INITIAL_MEMORY_STATE_BYTE, account[0] = NULL_TERM
    if ((accountName[0] == NULL_TERM) ||
        (accountName[0] == (char) INITIAL_MEMORY_STATE_CHAR)) {
      if (pos != 0) DisplayToError("ERR: 031");                                 // Empty credentials found in linked list; error but we'll use this spot
      return pos;                                                               // 
    }
    //                                      Z            A                      positive, stop and return getNextFreeAcctPos
    //                                      A            Z                      negative, continue to the next account in the linked list
    signed int compareResult = strncmp(accountName,passedAccountName,ACCOUNT_SIZE);// negative the first character that does not match has a lower value in ptr1 than in ptr2
                                                                                // positive the first character that does not match has a greater value in ptr1 than in ptr2
    if (0 == compareResult) {                                                   // if the two strings match 
      updateExistingAccount = true;                                             // we're updating an existing account, set the global boolean
      return(pos);                                                              // you found the account, return pos
    } else if (compareResult > 0) {                                             // we can stop looking, the list is sorted and passedAccountName < accountName
      return(getNextFreeAcctPos());                                             // return the next free account position
    }                                                                           
    pos = getNextPtr(pos);                                                      // get the position of the next account name in the linked list
  }
  if (i > CREDS_ACCOMIDATED) {
    DisplayToError("ERR: 033");                                                 // ran out  of room for credentials.
  }
  return(getNextFreeAcctPos());                                                 // return the next free account position
}

                                                                                // Commands we send from the PC and want to receive on the Arduino.
void attachCommandCallbacks()                                                   // We must define a callback function in our Arduino program for each entry in the list below.
{
  // Attach callback methods
  cmdMessenger.attach(OnUnknownCommand);
  cmdMessenger.attach(pyReadAccountName       , OnReadAccountName);
  cmdMessenger.attach(pyReadUserName          , OnReadUserName);
  cmdMessenger.attach(pyReadPassword          , OnReadPassword);
  cmdMessenger.attach(pyReadOldPassword       , OnReadOldPassword);
  cmdMessenger.attach(pyReadURL               , OnReadURL);
  cmdMessenger.attach(pyReadStyle             , OnReadStyle);
  cmdMessenger.attach(pyReadGroup             , OnReadGroup);
  cmdMessenger.attach(pyUpdateAccountName     , OnUpdateAccountName);
  cmdMessenger.attach(pyUpdateUserName        , OnUpdateUserName);
  cmdMessenger.attach(pyUpdatePassword        , OnUpdatePassword);
  cmdMessenger.attach(pyUpdateURL             , OnUpdateURL);
  cmdMessenger.attach(pyUpdateURL_1           , OnUpdateURL_1);
  cmdMessenger.attach(pyUpdateURL_2           , OnUpdateURL_2);
  cmdMessenger.attach(pyUpdateURL_3           , OnUpdateURL_3);
  cmdMessenger.attach(pyUpdateStyle           , OnUpdateStyle);
  cmdMessenger.attach(pyUpdateGroup           , OnUpdateGroup);
  cmdMessenger.attach(pyUpdateOldPassword     , OnUpdateOldPassword);
  cmdMessenger.attach(pyGetNextPos            , OnGetNextPos);
  cmdMessenger.attach(pyGetPrevPos            , OnGetPrevPos);
  cmdMessenger.attach(pyGetAcctPos            , OnGetAcctPos);
  cmdMessenger.attach(pyReadHead              , OnReadHead);
  cmdMessenger.attach(pyReadTail              , OnReadTail);
  cmdMessenger.attach(pyGetNextFreePos        , OnGetNextFreePos);
  cmdMessenger.attach(pyDeleteAccount         , OnDeleteAccount);
  cmdMessenger.attach(pyExit                  , OnExit);
  cmdMessenger.attach(pyBackup                , OnBackup);
  cmdMessenger.attach(pyFactoryReset          , OnFactoryReset);
  cmdMessenger.attach(pyFixCorruptLinkedList  , OnFixCorruptLinkedList);
  cmdMessenger.attach(pyRestore               , OnRestore);
  cmdMessenger.attach(pyGetAccountCount       , OnGetAccountCount);
  cmdMessenger.attach(pyDecoyPassword         , OnDecoyPassword);
  cmdMessenger.attach(pyShowPasswords         , OnShowPasswords);
  cmdMessenger.attach(pyReadGroup1Name        , OnReadGroup1Name);
  cmdMessenger.attach(pyReadGroup2Name        , OnReadGroup2Name);
  cmdMessenger.attach(pyReadGroup3Name        , OnReadGroup3Name);
  cmdMessenger.attach(pyReadGroup4Name        , OnReadGroup4Name);
  cmdMessenger.attach(pyReadGroup5Name        , OnReadGroup5Name);
  cmdMessenger.attach(pyReadGroup6Name        , OnReadGroup6Name);
  cmdMessenger.attach(pyReadGroup7Name        , OnReadGroup7Name);
  cmdMessenger.attach(pyUpdateCategoryName    , OnUpdateCategoryName);
  cmdMessenger.attach(pyUpdateRGBLEDIntensity , OnUpdateRGBLEDIntensity);
  cmdMessenger.attach(pyUpdateLoginMinutes    , OnUpdateLoginMinutes);
  cmdMessenger.attach(pyUpdateLoginAttempts   , OnUpdateLoginAttempts);
  cmdMessenger.attach(pyUpdatePasswordLength  , OnUpdatePasswordLength);
  cmdMessenger.attach(pyUpdateInterCharDelay  , OnUpdateInterCharDelay);
  cmdMessenger.attach(pyGetRGBLEDIntensity    , OnGetRGBLEDIntensity);
  cmdMessenger.attach(pyGetLoginMinutes       , OnGetLoginMinutes);
  cmdMessenger.attach(pyGetLoginAttempts      , OnGetLoginAttempts);
  cmdMessenger.attach(pyGetPasswordLength     , OnGetPasswordLength);
  cmdMessenger.attach(pyGetInterCharDelay     , OnGetInterCharDelay);
  cmdMessenger.attach(pyChangeMasterPass      , OnChangeMasterPass);
}

uint8_t calcAcctPositionReceive(uint8_t accountPosition) {
  
//  char accountPositionStr[5];
//  itoa(accountPosition, accountPositionStr, 10);
//  DisplayToDebug(accountPositionStr);
  
  if (accountPosition == 1) {
    accountPosition = 88;                                                       // necessary because of a defect in PyCmdMessenger
  } else if (accountPosition == 2) {
    accountPosition = 120;
  } else if (accountPosition == 3) {
    accountPosition = 122;
  } else {
    if (accountPosition < 255) {
      accountPosition -= 4;
    }
  }
  return accountPosition;
}

uint8_t calcAcctPositionSend(uint8_t accountPosition) {                         // work around another defect in PyCmdMessenger
  if (accountPosition < 251) accountPosition += 4;
  if (accountPosition == 92) {                                                  // escape_separator
    accountPosition = 1;
  } else if (accountPosition == 124) {                                          // command_separator
    accountPosition = 2;
  } else if (accountPosition == 126) {                                          // field_separator
    accountPosition = 3;
  }
  return accountPosition;                                                       // accountPosition will never = 124, or |, the command separator
}

void OnUnknownCommand()                                                         // Called when a received command has no attached function
{ setGreen();
  cmdMessenger.sendCmd(kError,"Command without attached callback");
  DisplayToError("ERR: 057");
  setRed();
}

void OnReadAccountName() {
  setGreen();
  char accountName[ACCOUNT_SIZE];
  acctPosition = calcAcctPositionReceive(cmdMessenger.readBinArg<uint8_t>());   // 
  readAcctFromEEProm(acctPosition, accountName);                                // read and decrypt the account name
  if (strlen(accountName) > 0) {
    if (accountName[0] == ' ') {
      accountName[0] = '_';
    }
		DisplayToStatus(accountName);
    cmdMessenger.sendCmd(kStrAcknowledge, accountName);
  } else {
    cmdMessenger.sendCmd(kStrAcknowledge, "Click File->Exit Now!");             // Defect: this will happen if you delete the first account in the linked list and then execute Fix Corrupt Linked List.
  }
  setPurple();
}

void OnReadUserName(){
  setGreen();
  char username[USERNAME_SIZE];
  acctPosition = calcAcctPositionReceive(cmdMessenger.readBinArg<uint8_t>());
  readUserFromEEProm(acctPosition, username);                                   // read and decrypt the user
  cmdMessenger.sendCmd(kStrAcknowledge, username);
  setPurple();
}

void OnReadPassword(){
  setGreen();
  char password[PASSWORD_SIZE];
  acctPosition = calcAcctPositionReceive(cmdMessenger.readBinArg<uint8_t>());
  readPassFromEEProm(acctPosition, password);                                   // read and decrypt the password
  cmdMessenger.sendCmd(kStrAcknowledge, password);
  setPurple();
}

void OnReadOldPassword(){
  setGreen();
  char oldPassword[PASSWORD_SIZE];
  acctPosition = calcAcctPositionReceive(cmdMessenger.readBinArg<uint8_t>());
  readOldPassFromEEProm(acctPosition, oldPassword);                             // read and decrypt the password
  cmdMessenger.sendCmd(kStrAcknowledge, oldPassword);
  setPurple();
}

void OnReadURL(){
  setGreen();
  char url[WEBSITE_SIZE];
  acctPosition = calcAcctPositionReceive(cmdMessenger.readBinArg<uint8_t>());
  readWebSiteFromEEProm(acctPosition, url);                                     // read and decrypt the url
  cmdMessenger.sendCmd(kStrAcknowledge, url);
  setPurple();
}

void OnReadStyle(){
  setGreen();
  char style[STYLE_SIZE];
  acctPosition = calcAcctPositionReceive(cmdMessenger.readBinArg<uint8_t>());
  readStyleFromEEProm(acctPosition, style);
  switch(style[0]) {                                                            // Make sure style is in the valid range.
    case '0':
      break;
    case '1':
      break;
    case '2':
      break;
    default:
      style[0] = DEFAULT_STYLE_CHAR;
      break;
  }
  cmdMessenger.sendCmd(kStrAcknowledge, style);
  setPurple();
}

void OnReadGroup(){
  setGreen();
  acctPosition = calcAcctPositionReceive(cmdMessenger.readBinArg<uint8_t>());
  uint8_t group = read_eeprom_byte(GET_ADDR_GROUP(acctPosition));
  cmdMessenger.sendBinCmd(kAcknowledge, group);
  setPurple();
}

void OnReadGroup1Name(){
  setGreen();
  char group[CATEGORY_SIZE];
	read_eeprom_array     (GET_ADDR_CATEGORY_1,                                 	// read category from EEprom
												 group, 
												 CATEGORY_SIZE);
  cmdMessenger.sendCmd(kStrAcknowledge, group);
  setPurple();
}

void OnReadGroup2Name(){
  setGreen();
  char group[CATEGORY_SIZE];
	read_eeprom_array     (GET_ADDR_CATEGORY_2,                                 	// read category from EEprom
												 group, 
												 CATEGORY_SIZE);
  cmdMessenger.sendCmd(kStrAcknowledge, group);
  setPurple();
}

void OnReadGroup3Name(){
  setGreen();
  char group[CATEGORY_SIZE];
	read_eeprom_array     (GET_ADDR_CATEGORY_3,                                 	// read category from EEprom
												 group, 
												 CATEGORY_SIZE);
  cmdMessenger.sendCmd(kStrAcknowledge, group);
  setPurple();
}

void OnReadGroup4Name(){
  setGreen();
  char group[CATEGORY_SIZE];
	read_eeprom_array     (GET_ADDR_CATEGORY_4,                                 	// read category from EEprom
												 group, 
												 CATEGORY_SIZE);
  cmdMessenger.sendCmd(kStrAcknowledge, group);
  setPurple();
}

void OnReadGroup5Name(){
  setGreen();
  char group[CATEGORY_SIZE];
	read_eeprom_array     (GET_ADDR_CATEGORY_5,                                 	// read category from EEprom
												 group, 
												 CATEGORY_SIZE);
  cmdMessenger.sendCmd(kStrAcknowledge, group);
  setPurple();
}

void OnReadGroup6Name(){
  setGreen();
  char group[CATEGORY_SIZE];
	read_eeprom_array     (GET_ADDR_CATEGORY_6,                                 	// read category from EEprom
												 group, 
												 CATEGORY_SIZE);
  cmdMessenger.sendCmd(kStrAcknowledge, group);
  setPurple();
}

void OnReadGroup7Name(){
  setGreen();
  char group[CATEGORY_SIZE];
	read_eeprom_array     (GET_ADDR_CATEGORY_7,                                 	// read category from EEprom
												 group, 
												 CATEGORY_SIZE);
  cmdMessenger.sendCmd(kStrAcknowledge, group);
  setPurple();
}

void OnUpdateAccountName(){                                                     // TODO: Should we prevent updating account name except on insert?
  setGreen();
  char accountName[ACCOUNT_SIZE];
  cmdMessenger.copyStringArg(accountName, ACCOUNT_SIZE);
  if (strlen(accountName) > 0) {
    if (accountName[0] == '_') {																								// tkinter will left justify anything that starts with a space
      accountName[0] = ' ';
    }
		boolean badAcctName = false;
		DisplayToEdit((char *)accountName);                                         // Display the account name on the second line
		acctPosition = FindAccountPos(accountName);                                 // get the next open position, sets updateExistingAccount
		if (!updateExistingAccount) {                                               // if we're not updating an existing account we must be inserting
			if (acctPosition != INITIAL_MEMORY_STATE_BYTE) {                          // if we are not out of space
				SetSaltAndKey(acctPosition);                                            // populate and save the salt, set the key with the salt and master password
				char bufferAcct[ACCOUNT_SIZE];
				encrypt32Bytes(bufferAcct, accountName);
				while (bufferAcct[0] == (char) INITIAL_MEMORY_STATE_CHAR) {             // check to see if we have an invalid condition after encryption, if we do,
																																								// concatenate characters until the first char in the cipher isn't 255.
					DisplayToError("ERR: 039");                                           // encrypted account name starts with 255, fixing...
					size_t len = strlen(accountName);
					if (len > 2) {
						accountName[len - 2] = NULL_TERM;                                   // Chop a character off the end of the account name
						encrypt32Bytes(bufferAcct, accountName);                            // encrypt again and hope for the best
					} else {
						DisplayToError("ERR: 020");                                         // display the error to the screen and continue processing.  
						badAcctName = true;                                                 // can't get this account name to encrypt to something that doesn't
						break;                                                              // start with 255
					}
				}
				if (!badAcctName) {
					if (!updateExistingAccount) {                                         // if we're updating an existing account no need to write out the account, set the pointers or increment the account count
						eeprom_write_bytes(GET_ADDR_ACCT(acctPosition),bufferAcct,ACCOUNT_SIZE);// write the account name to EEprom
						writePointers(acctPosition, accountName);                           // insert the account into the linked list by updating previous and next pointers.
						acctCount++;                                                        // we added a new account, increment the count of accounts
					}
					uint8_t groups = read_eeprom_byte(GET_ADDR_GROUP(acctPosition));      // initialize the groups
					if (groups == INITIAL_MEMORY_STATE_BYTE) writeGroup(acctPosition, NONE);// a set of credentials cannot belong to all groups because that's INITIAL_MEMORY_STATE_BYTE.
				}
			} else {
				DisplayToError("ERR: 012");                                             // out of space in EEprom
			}
		}                             																							// if we're updating an existing account no need to write out the 
                                                                                // account, set the pointers or increment the account count. Don't
                                                                                // update the account name, once it is created it can't be changed.
	}

  cmdMessenger.sendBinCmd(kAcknowledge, calcAcctPositionSend(acctPosition));    // send back the account position
  setPurple();
}

void OnUpdateUserName(){
  setGreen();
  char username[USERNAME_SIZE];
  acctPosition = calcAcctPositionReceive(cmdMessenger.readBinArg<uint8_t>());
  cmdMessenger.copyStringArg(username, USERNAME_SIZE);
  uint8_t len = strlen(username);
  while (len < USERNAME_SIZE) username[len++] = NULL_TERM;
  username[USERNAME_SIZE - 1] = NULL_TERM;
  char bufferUser[USERNAME_SIZE];                                               // for the encrypted user name
  ReadSaltAndSetKey(acctPosition);
  encrypt32Bytes(bufferUser, username);                                         // encrypt the user name
  eeprom_write_bytes(GET_ADDR_USER(acctPosition), bufferUser, USERNAME_SIZE);
  cmdMessenger.sendBinCmd(kAcknowledge, calcAcctPositionSend(acctPosition));    // send back the account position
  setPurple();
}

void OnUpdatePassword(){
  setGreen();
  char password[PASSWORD_SIZE];
  acctPosition = calcAcctPositionReceive(cmdMessenger.readBinArg<uint8_t>());
  cmdMessenger.copyStringArg(password, PASSWORD_SIZE);                          // uses strlcpy, which will not write more than bytes expressed in the second parameter
  uint8_t len = strlen(password);
  while (len < PASSWORD_SIZE) password[len++] = NULL_TERM;
  password[PASSWORD_SIZE - 1] = NULL_TERM;
  char bufferPass[PASSWORD_SIZE];                                               // for the encrypted password
  ReadSaltAndSetKey(acctPosition);
  encrypt32Bytes(bufferPass, password);                                         // encrypt the password
  eeprom_write_bytes(GET_ADDR_PASS(acctPosition), bufferPass, PASSWORD_SIZE);
  cmdMessenger.sendBinCmd(kAcknowledge, calcAcctPositionSend(acctPosition));    // send back the account position
  setPurple();
}

void OnUpdateURL(){
  setGreen();
  char urlArray[WEBSITE_SIZE];
  acctPosition = calcAcctPositionReceive(cmdMessenger.readBinArg<uint8_t>());
  cmdMessenger.copyStringArg(urlArray, WEBSITE_SIZE);
  size_t len = strlen(urlArray);
  if (len > (WEBSITE_SIZE - 1)) {
    urlArray[WEBSITE_SIZE - 1] = NULL_TERM;
    DisplayToError("ERR: 023");                                                 // Web site is too long
  } else {
    while (len < WEBSITE_SIZE) urlArray[len++] = NULL_TERM;
  }
  char bufferWebsite[WEBSITE_SIZE];
  if (len < 1) {
    urlArray[0] = NULL_TERM;
  }
  ReadSaltAndSetKey(acctPosition);
  encrypt96Bytes(bufferWebsite, urlArray);                                      // encrypt the 96 byte long website
  eeprom_write_bytes(GET_ADDR_WEBSITE(acctPosition),bufferWebsite,WEBSITE_SIZE);// write the website to eeprom
  cmdMessenger.sendBinCmd(kAcknowledge, calcAcctPositionSend(acctPosition));    // send back the account position
  setPurple();
}

void OnUpdateURL_1(){
  setGreen();
  cmdMessenger.copyStringArg(website, 33);                                      // was 32 when we were losing the 32nd character
  cmdMessenger.sendBinCmd(kAcknowledge, calcAcctPositionSend(acctPosition));    // send back the account position
  setPurple();
}

void OnUpdateURL_2(){
  setGreen();
  char website_2[33];
  cmdMessenger.copyStringArg(website_2, 33);
  strcat(website, website_2);
  cmdMessenger.sendBinCmd(kAcknowledge, calcAcctPositionSend(acctPosition));    // send back the account position
  setPurple();
}

void OnUpdateURL_3(){
  setGreen();
  char website_3[33];
  acctPosition = calcAcctPositionReceive(cmdMessenger.readBinArg<uint8_t>());
  cmdMessenger.copyStringArg(website_3, 33);
  strcat(website, website_3);
  size_t lenWebsite = strlen(website);
  if (lenWebsite > (WEBSITE_SIZE - 1)) {
    website[WEBSITE_SIZE - 1] = NULL_TERM;
    DisplayToError("ERR: 023");                                                 // Web site is too long
  } else {
    while (lenWebsite < WEBSITE_SIZE) website[lenWebsite++] = NULL_TERM;
  }
  char bufferWebsite[WEBSITE_SIZE];
  if (lenWebsite < 1) {
    website[0] = NULL_TERM;
  }
  ReadSaltAndSetKey(acctPosition);
  encrypt96Bytes(bufferWebsite, website);                                       // encrypt the 96 byte long website
  eeprom_write_bytes(GET_ADDR_WEBSITE(acctPosition),bufferWebsite,WEBSITE_SIZE);// write the website to eeprom
  cmdMessenger.sendBinCmd(kAcknowledge, calcAcctPositionSend(acctPosition));    // send back the account position
  setPurple();
}

void OnUpdateStyle(){
  setGreen();
  char *style;
  acctPosition = calcAcctPositionReceive(cmdMessenger.readBinArg<uint8_t>());
  style = cmdMessenger.readStringArg();
  uint8_t i = strlen(style);
  while (i < STYLE_SIZE) style[i++] = NULL_TERM;
  style[STYLE_SIZE - 1] = NULL_TERM;
  eeprom_write_bytes(GET_ADDR_STYLE(acctPosition), style, STYLE_SIZE);
  cmdMessenger.sendBinCmd(kAcknowledge, calcAcctPositionSend(acctPosition));    // send back the account position
  setPurple();
}

void OnUpdateGroup(){
  setGreen();
  uint8_t groups;
  acctPosition = calcAcctPositionReceive(cmdMessenger.readBinArg<uint8_t>());
  groups = cmdMessenger.readBinArg<uint8_t>();
  if (groups == 1) groups = 92;
  groups -= 3;
  write_eeprom_byte(GET_ADDR_GROUP(acctPosition), groups);                      // should we call writeGroup() here instead?
  cmdMessenger.sendBinCmd(kAcknowledge, calcAcctPositionSend(acctPosition));    // send back the account position
  setPurple();
}

void OnUpdateOldPassword(){
  setGreen();
  char oldPassword[PASSWORD_SIZE];
  acctPosition = calcAcctPositionReceive(cmdMessenger.readBinArg<uint8_t>());
  cmdMessenger.copyStringArg(oldPassword, PASSWORD_SIZE);                       // uses strlcpy, which will not write more than bytes expressed in the second parameter
  uint8_t len = strlen(oldPassword);
  while (len < PASSWORD_SIZE) oldPassword[len++] = NULL_TERM;
  oldPassword[PASSWORD_SIZE - 1] = NULL_TERM;
  char bufferOldPass[PASSWORD_SIZE];                                            // for the encrypted old password
  ReadSaltAndSetKey(acctPosition);
  encrypt32Bytes(bufferOldPass, oldPassword);                                   // encrypt the old password
  eeprom_write_bytes(GET_ADDR_OLD_PASS(acctPosition), bufferOldPass, PASSWORD_SIZE);
  cmdMessenger.sendBinCmd(kAcknowledge, calcAcctPositionSend(acctPosition));    // send back the account position
  setPurple();
}

void OnUpdateCategoryName(){
  setGreen();
  char categoryname[CATEGORY_SIZE];
  uint8_t categoryNum = cmdMessenger.readBinArg<uint8_t>();
  cmdMessenger.copyStringArg(categoryname, CATEGORY_SIZE);
  uint8_t len = strlen(categoryname);
  while (len < CATEGORY_SIZE) categoryname[len++] = NULL_TERM;
  categoryname[CATEGORY_SIZE - 1] = NULL_TERM;
  switch(categoryNum) {
    case 1:
      eeprom_write_bytes(GET_ADDR_CATEGORY_1, categoryname, CATEGORY_SIZE);
      break;
    case 2:
      eeprom_write_bytes(GET_ADDR_CATEGORY_2, categoryname, CATEGORY_SIZE);
      break;
    case 3:
      eeprom_write_bytes(GET_ADDR_CATEGORY_3, categoryname, CATEGORY_SIZE);
      break;
    case 4:
      eeprom_write_bytes(GET_ADDR_CATEGORY_4, categoryname, CATEGORY_SIZE);
      break;
    case 5:
      eeprom_write_bytes(GET_ADDR_CATEGORY_5, categoryname, CATEGORY_SIZE);
      break;
    case 6:
      eeprom_write_bytes(GET_ADDR_CATEGORY_6, categoryname, CATEGORY_SIZE);
      break;
    case 7:
      eeprom_write_bytes(GET_ADDR_CATEGORY_7, categoryname, CATEGORY_SIZE);
      break;
    default:
      DisplayToError("ERR: 044");
      break;
  }
  cmdMessenger.sendBinCmd(kAcknowledge, calcAcctPositionSend(acctPosition));    // send back the account position
  setPurple();
}

void OnUpdateRGBLEDIntensity() {
  setGreen();
  uint8_t RGBLEDIntensityIndex = cmdMessenger.readBinArg<uint8_t>();
  switch(RGBLEDIntensityIndex - 1) {                                            // subtract one because there is a problem sending zero
    case RGB_INTENSITY_HIGH:
      RGBLEDIntensity = RGB_LED_HIGH;
      break;
    case RGB_INTENSITY_MED:
      RGBLEDIntensity = RGB_LED_MEDIUM;
      break;
    case RGB_INTENSITY_LOW:
      RGBLEDIntensity = RGB_LED_LOW;
      break;
    case RGB_INTENSITY_OFF:
      RGBLEDIntensity = RGB_LED_OFF;
      break;
    default:
      RGBLEDIntensity = RGB_LED_MEDIUM;
      DisplayToError("ERR: 016");
      break;
  }
  writeRGBLEDIntensity();
  cmdMessenger.sendBinCmd(kAcknowledge, calcAcctPositionSend(acctPosition));    // sending a single byte 
  setPurple();
}

void OnUpdateLoginMinutes() {
  setGreen();
  uint8_t loginMinutesIndex = cmdMessenger.readBinArg<uint8_t>();
  switch(loginMinutesIndex - 1) {                                               // subtract one because there is a problem sending zero
    case LOGOUT_TIMEOUT_30:
      logoutTimeout = LOGOUT_TIMEOUT_VAL_30;
      break;
    case LOGOUT_TIMEOUT_60:
      logoutTimeout = LOGOUT_TIMEOUT_VAL_60;
      break;
    case LOGOUT_TIMEOUT_90:
      logoutTimeout = LOGOUT_TIMEOUT_VAL_90;
      break;
    case LOGOUT_TIMEOUT_120:
      logoutTimeout = LOGOUT_TIMEOUT_VAL_120;
      break;
    case LOGOUT_TIMEOUT_240:
      logoutTimeout = LOGOUT_TIMEOUT_VAL_240;
      break;
    case LOGOUT_TIMEOUT_1:
      logoutTimeout = LOGOUT_TIMEOUT_VAL_1;
      break;
    case LOGOUT_TIMEOUT_0:
      logoutTimeout = LOGOUT_TIMEOUT_VAL_0;
      break;
    default:
      logoutTimeout = LOGOUT_TIMEOUT_VAL_60;
      DisplayToError("ERR: 018");
      break;
  }
  writeLogoutTimeout();
  cmdMessenger.sendBinCmd(kAcknowledge, calcAcctPositionSend(acctPosition));    // sending a single byte 
  setPurple();
}

void OnUpdateLoginAttempts() {
  setGreen();
  uint8_t loginAttemptsIndex = cmdMessenger.readBinArg<uint8_t>();
  switch(loginAttemptsIndex - 1) {                                              // subtract one because there is a problem sending zero
    case LOGIN_ATTEMPTS_3:
      loginAttempts =  ATTEMPTS_3;
      break;
    case LOGIN_ATTEMPTS_5:
      loginAttempts = ATTEMPTS_5;
      break;
    case LOGIN_ATTEMPTS_10:
      loginAttempts = ATTEMPTS_10;
      break;
    case LOGIN_ATTEMPTS_25:
      loginAttempts = ATTEMPTS_25;
      break;
    default:
      loginAttempts = ATTEMPTS_10;
      DisplayToError("ERR: 056");
      break;
  }
  writeLoginAttempts();
  cmdMessenger.sendBinCmd(kAcknowledge, calcAcctPositionSend(acctPosition));    // sending a single byte 
  setPurple();
}

void OnUpdatePasswordLength() {
  setGreen();
  uint8_t passwordLengthIndex = cmdMessenger.readBinArg<uint8_t>();
  switch(passwordLengthIndex - 1) {                                              // subtract one because there is a problem sending zero
    case GEN_PW_SIZE_8:
      generatedPasswordSize = GEN_PW_SIZE_8;
      break;
    case GEN_PW_SIZE_10:
      generatedPasswordSize = GEN_PW_SIZE_10;
      break;
    case GEN_PW_SIZE_16:
      generatedPasswordSize = GEN_PW_SIZE_16;
      break;
    case GEN_PW_SIZE_24:
      generatedPasswordSize = GEN_PW_SIZE_24;
      break;
    case GEN_PW_SIZE_31:
      generatedPasswordSize = GEN_PW_SIZE_31;
      break;
    default:
      generatedPasswordSize = GEN_PW_SIZE_16;
      DisplayToError("ERR: 058");
      break;
  }
  writeGenPwSize();
  cmdMessenger.sendBinCmd(kAcknowledge, calcAcctPositionSend(acctPosition));    // sending a single byte 
  setPurple();
}

void OnUpdateInterCharDelay() {
  setGreen();
  uint8_t interCharDelayIndex = cmdMessenger.readBinArg<uint8_t>();
  switch(interCharDelayIndex - 1) {                                              // subtract one because there is a problem sending zero
    case CHAR_DELAY_0:
      interCharPause = CHAR_DELAY_0;
      interCharPauseVal = CHAR_DELAY_VAL_0;
      break;
    case CHAR_DELAY_10:
      interCharPause = CHAR_DELAY_10;
      interCharPauseVal = CHAR_DELAY_VAL_10;
      break;
    case CHAR_DELAY_25:
      interCharPause = CHAR_DELAY_25;
      interCharPauseVal = CHAR_DELAY_VAL_25;
      break;
    case CHAR_DELAY_100:
      interCharPause = CHAR_DELAY_100;
      interCharPauseVal = CHAR_DELAY_VAL_100;
      break;
    case CHAR_DELAY_250:
      interCharPause = CHAR_DELAY_250;
      interCharPauseVal = CHAR_DELAY_VAL_250;
      break;
    default:
      interCharPause = DEFAULT_CHAR_DELAY;
      interCharPauseVal = CHAR_DELAY_VAL_0;
      DisplayToError("ERR: 059");
      break;
  }
  writeInterCharPause();
  cmdMessenger.sendBinCmd(kAcknowledge, calcAcctPositionSend(acctPosition));    // sending a single byte 
  setPurple();
}

void OnGetRGBLEDIntensity() {
  setGreen();
  uint8_t returnIntensity;
  switch(RGBLEDIntensity) {
    case RGB_LED_HIGH:
      returnIntensity = RGB_INTENSITY_HIGH;
      break;
    case RGB_LED_MEDIUM:
      returnIntensity = RGB_INTENSITY_MED;
      break;
    case RGB_LED_LOW:
      returnIntensity = RGB_INTENSITY_LOW;
      break;
    case RGB_LED_OFF:
      returnIntensity = RGB_INTENSITY_OFF;
      break;
    default:
      returnIntensity = RGB_INTENSITY_MED;
      DisplayToError("ERR: 016");
      break;
  }
  cmdMessenger.sendBinCmd(kAcknowledge, uint8_t (returnIntensity + 1));         // sending a single byte 
  setPurple();
}

void OnGetLoginMinutes() {
  setGreen();
  uint8_t logoutTimeoutReturn;
  switch (logoutTimeout) {
    case LOGOUT_TIMEOUT_VAL_30:
      logoutTimeoutReturn = LOGIN_ATTEMPTS_3;
      break;
    case LOGOUT_TIMEOUT_VAL_60:
      logoutTimeoutReturn = LOGOUT_TIMEOUT_60;
      break;
    case LOGOUT_TIMEOUT_VAL_90:
      logoutTimeoutReturn = LOGOUT_TIMEOUT_90;
      break;
    case LOGOUT_TIMEOUT_VAL_120:
      logoutTimeoutReturn = LOGOUT_TIMEOUT_120;
      break;
    case LOGOUT_TIMEOUT_VAL_240:
      logoutTimeoutReturn = LOGOUT_TIMEOUT_240;
      break;
    case LOGOUT_TIMEOUT_VAL_1:
      logoutTimeoutReturn = LOGOUT_TIMEOUT_1;
      break;
    case LOGOUT_TIMEOUT_VAL_0:
      logoutTimeoutReturn = LOGOUT_TIMEOUT_0;
      break;
    default:
      logoutTimeoutReturn = LOGOUT_TIMEOUT_60;
      DisplayToError("ERR: 018");
      break;
  }
  cmdMessenger.sendBinCmd(kAcknowledge, uint8_t (logoutTimeoutReturn + 1));     // sending a single byte 
  setPurple();
}

void OnGetLoginAttempts() {
  setGreen();
  uint8_t loginAttemptsReturn;
  switch (loginAttempts) {
    case 3:
      loginAttemptsReturn = LOGIN_ATTEMPTS_3;
      break;
    case 5:
      loginAttemptsReturn = LOGIN_ATTEMPTS_5;
      break;
    case 10:
      loginAttemptsReturn = LOGIN_ATTEMPTS_10;
      break;
    case 25:
      loginAttemptsReturn = LOGIN_ATTEMPTS_25;
      break;
    default:
      loginAttemptsReturn = LOGIN_ATTEMPTS_10;
      DisplayToError("ERR: 009");
      break;
  }
  cmdMessenger.sendBinCmd(kAcknowledge, uint8_t (loginAttemptsReturn + 1));     // sending a single byte 
  setPurple();
}

void OnGetPasswordLength() {
  setGreen();
  uint8_t passwordLengthReturn;
  switch (generatedPasswordSize) {                                              // TODO: This entier switch statement is unnecessary.
    case GEN_PW_SIZE_8:
      passwordLengthReturn = GEN_PW_SIZE_8;
      break;
    case GEN_PW_SIZE_10:
      passwordLengthReturn = GEN_PW_SIZE_10;
      break;
    case GEN_PW_SIZE_16:
      passwordLengthReturn = GEN_PW_SIZE_16;
      break;
    case GEN_PW_SIZE_24:
      passwordLengthReturn = GEN_PW_SIZE_24;
      break;
    case GEN_PW_SIZE_31:
      passwordLengthReturn = GEN_PW_SIZE_31;
      break;
    default:
      passwordLengthReturn = GEN_PW_SIZE_16;
      DisplayToError("ERR: 058");
      break;
  }
  cmdMessenger.sendBinCmd(kAcknowledge, uint8_t (passwordLengthReturn + 1));    // sending a single byte 
  setPurple();
}

void OnGetInterCharDelay() {
  setGreen();
  cmdMessenger.sendBinCmd(kAcknowledge, uint8_t (interCharPause + 1));          // sending a single byte 
  setPurple();
}

void OnGetNextPos(){
  setGreen();
  acctPosition = calcAcctPositionReceive(cmdMessenger.readBinArg<uint8_t>());
  cmdMessenger.sendBinCmd(kAcknowledge, calcAcctPositionSend(getNextPtr(acctPosition)));
  setPurple();
}

void OnGetPrevPos(){
  setGreen();
  acctPosition = calcAcctPositionReceive(cmdMessenger.readBinArg<uint8_t>());
  cmdMessenger.sendBinCmd(kAcknowledge, calcAcctPositionSend(getPrevPtr(acctPosition)));
  setPurple();
}

void OnGetAcctPos(){
  setGreen();
  cmdMessenger.sendBinCmd(kAcknowledge, calcAcctPositionSend(acctPosition));    // manipulate acctPosition here?
  setPurple();
}

void OnReadHead(){
  setGreen();
  setListHeadPosition();                                                        // set headPosition
  acctPosition = headPosition;
  cmdMessenger.sendBinCmd(kAcknowledge, calcAcctPositionSend(acctPosition));    // sending a single byte 
  setPurple();
}

void OnReadTail(){
  setGreen();
  cmdMessenger.sendBinCmd(kAcknowledge, calcAcctPositionSend(findTailPosition(headPosition)));
  setPurple();
}

void OnGetNextFreePos(){
  setGreen();
  uint8_t nextFree = getNextFreeAcctPos();
  acctPosition = nextFree;
  cmdMessenger.sendBinCmd(kAcknowledge, calcAcctPositionSend(nextFree));        // ????????manipulate acctPosition here?
  setPurple();
}

void OnDeleteAccount(){
  setGreen();
  acctPosition = calcAcctPositionReceive(cmdMessenger.readBinArg<uint8_t>());
  deleteAccount(acctPosition);
  cmdMessenger.sendBinCmd(kAcknowledge, calcAcctPositionSend(headPosition));
  setPurple();
}

void OnGetAccountCount(){
  setGreen();
  cmdMessenger.sendBinCmd(kAcknowledge, calcAcctPositionSend(acctCount));       // sending a single byte  ????????manipulate acctPosition here?
  setPurple();
}

void OnBackup(){
  CopyEEPromToBackup();
  cmdMessenger.sendBinCmd(kAcknowledge, calcAcctPositionSend(headPosition));
  setPurple();
}

void OnFactoryReset(){
  loginFailures = loginAttempts + 1;                                            // so that a condition inside of EVENT_RESET evaluates to true and the reset 
  FactoryReset();
  cmdMessenger.sendBinCmd(kAcknowledge, calcAcctPositionSend(headPosition));
  setPurple();
  Serial.end();
}

void OnFixCorruptLinkedList(){
  FixCorruptLinkedList();
  cmdMessenger.sendBinCmd(kAcknowledge, calcAcctPositionSend(headPosition));
  setPurple();
}

void OnRestore(){                                                               // This is called when we restore the data from EEprom secondary to EEprom primary from PasswordPumpGUI.py
  RestoreEEPromBackup();
  cmdMessenger.sendBinCmd(kAcknowledge, calcAcctPositionSend(headPosition));
  setPurple();
}

void OnChangeMasterPass(){                                                      // This is called when we change the master password from PasswordPumpGUI.py
  char newMasterPassword[MASTER_PASSWORD_SIZE];
  cmdMessenger.copyStringArg(newMasterPassword, MASTER_PASSWORD_SIZE);          // uses strlcpy, which will not write more than bytes expressed in the second parameter
  if (strlen(newMasterPassword) > 0) {
    ChangeMasterPassword(newMasterPassword);
  }
  cmdMessenger.sendBinCmd(kAcknowledge, calcAcctPositionSend(headPosition));
  setPurple();
}

void OnDecoyPassword(){                                                         // This is called when we change the decoy password setting in PasswordPumpGUI.py
  setGreen();
  decoyPassword = calcAcctPositionReceive(cmdMessenger.readBinArg<uint8_t>());
  if (decoyPassword == 49) decoyPassword = 0;                                   // defect in pyCmdMessenger is causing a 0 to be turned into 49, no idea why
  writeDecoyPWFlag();
  delayNoBlock(ONE_SECOND);
  cmdMessenger.sendBinCmd(kAcknowledge, calcAcctPositionSend(headPosition));
  setPurple();
}

void OnShowPasswords() {                                                        // This is called when we change the 'show passwords' setting in PasswordPumpGUI.py
  setGreen();
  showPasswordsFlag = calcAcctPositionReceive(cmdMessenger.readBinArg<uint8_t>());
  if (showPasswordsFlag == 49) showPasswordsFlag = 0;                           // defect in pyCmdMessenger is causing a 0 to be turned into 49, no idea why
  writeShowPasswordsFlag();
  delayNoBlock(ONE_SECOND);
  cmdMessenger.sendBinCmd(kAcknowledge, calcAcctPositionSend(headPosition));
  setPurple();
}
  
void OnExit() {                                                                 // This is called when we exit from PasswordPumpGUI.py
  cmdMessenger.sendBinCmd(kAcknowledge, calcAcctPositionSend(acctCount));       // sending a single byte
  Serial.end();
  DisableInterrupts();
  setGreen();
  event = EVENT_SHOW_MAIN_MENU;
  machineState = STATE_SHOW_MAIN_MENU;
} 
 
//
// - Dead Code
//

//void BackupToPPCVSFile() {                                                    // before executing the function the user must open a text editor and place input focus there.
//  //DebugLN("BackupToPPCVSFile()");
//  DisplayToStatus("Backup to CVS file");
//  setPurple();
//  acctPosition = headPosition;
//  Keyboard.begin();
//  while (acctPosition != INITIAL_MEMORY_STATE_BYTE) {
//    delayNoBlock(500);                                                        // without the delays the results are corrupt
//    Keyboard.print("\"");
//    delayNoBlock(50);
//    readAcctFromEEProm(acctPosition, accountName);
//    Keyboard.print(accountName);
//    delayNoBlock(50);
//    Keyboard.print("\",\"");
//    delayNoBlock(50);
//    readUserFromEEProm(acctPosition, username); 
//    Keyboard.print(username);
//    delayNoBlock(50);
//    Keyboard.print("\",\"");
//    delayNoBlock(50);
//    readPassFromEEProm(acctPosition, password);
//    Keyboard.print(password);
//    delayNoBlock(50);
//    Keyboard.print("\",\"");
//    delayNoBlock(50);
//    readWebSiteFromEEProm(acctPosition, website);
//    Keyboard.print(website);
//    delayNoBlock(50);
//    Keyboard.print("\",");
//    delayNoBlock(50);
//    uint8_t group = readGroupFromEEprom(acctPosition);                        // read the group from EEProm
//    Keyboard.println(group);                                                  // type the group through the keyboard
//    delayNoBlock(50);
//    //sendGroup();
//    //sendRTN();
//    acctPosition = getNextPtr(acctPosition);
//  }
//  Keyboard.end();
//  setGreen();
//  DisplayToStatus("Done backup to CVS");
//}

/* Currently defunct
void sendAll() {                                                                // this is the function we use to backup all of the account names, user names and passwords
  //DebugLN("sendAll()");
  DisplayToStatus("Backup to file");
  setPurple();
  acctPosition = headPosition;
  while (acctPosition != INITIAL_MEMORY_STATE_BYTE) {
    sendAccount();
    Keyboard.println("");                                                       // send <CR> through the keyboard
    sendUsername();
    Keyboard.println("");                                                       // send <CR> through the keyboard
    sendPassword();
    delayNoBlock(PW_RTN_DELAY);
    sendRTN();
    Keyboard.begin();
    Keyboard.println("");
    Keyboard.println("");                                                       // place a carriage return between each account
    Keyboard.end();
    acctPosition = getNextPtr(acctPosition);
  }
  setGreen();
  DisplayToStatus("Done Backup");
}
*/

// void KeyboardBegin() {
  // Keyboard.begin();
// }

// void KeyboardWrite(char c) {
  // Keyboard.write(c);
// }

// void KeyboardPrintln(char *s) {
  // Keyboard.println(s);
// }

// void KeyboardPrintln(char c) {
  // Keyboard.println(c);
// }

// void KeyboardEnd() {
  // Keyboard.end();
// }

// void KeyboardPrint(char c) {
  // Keyboard.print(c);
// }

// void KeyboardPrint(char *s) {
  // Keyboard.print(s);
// }

// void KeyboardPress(char c) {
  // Keyboard.press(c);
// }

// void KeyboardReleaseAll() {
  // Keyboard.releaseAll();
// }

// void KeyboardRelease(char c) {
  // Keyboard.release(c);
// }


/*
//- Import/Export File Functions

void importKeePassCSV() {
  //DebugLN("importKeePassCSV()");
  DisplayToStatus("Importing...");
  setYellow();
  if (!flash.begin()) {
    DisplayToError("ERR: 015");
    return;
  }
  //Debug("Flash chip JEDEC ID: 0x"); if (DEBUG_ENABLED) Serial.println(flash.getJEDECID(), HEX);

  // First call begin to mount the filesystem.  Check that it returns true
  // to make sure the filesystem was mounted.
  if (!fatfs.begin(&flash)) {
    DisplayToError("ERR: 014");
    //DebugLN("Error, failed to mount newly formatted filesystem!");
    //DebugLN("Was the flash chip formatted with the SdFat_format example?");
    return;
  }
  DisplayToStatus("Mounted filesystem");
  //DebugLN("Mounted filesystem!");

  File myFile;                                                                  
  myFile = fatfs.open(KEEPASS_CSV);                                             // open the file "KPEXPORT.CSV" for reading
  if (myFile) {
    //DebugLN("Opened file");
    DisplayToStatus("File open");
    uint8_t fieldNum, numFields, pos;
    char *line;
    if (myFile.available()) {
      String header = myFile.readStringUntil('\n');
    }
    boolean outOfSpace = false;
    while (((line = csvgetline(myFile)) != NULL) && !outOfSpace) {
      String dummy = myFile.readStringUntil('\n');
      for (fieldNum = 0; fieldNum < csvnfield(); fieldNum++) {
        char *field = csvfield(fieldNum);
        //DebugMetric("fieldNum: ", fieldNum);Debug(field);
        size_t len = strlen(field);
        uint8_t key[KEY_SIZE];                                                  // set the key so we're prepared when we write the account to EEprom
        switch (fieldNum)
        {
          case 0:                                                               // Account Name: code to be executed if fieldNum = 1;
            if (len > (ACCOUNT_SIZE - 1)) {
              uint32_t i = ACCOUNT_SIZE - 1;
              while (i < len) field[i++] = NULL_TERM;                           // right pad the field w/ null terminator char
              DisplayToError("ERR: 024");                                       // User name is too long
            }
            DisplayToStatus(field);                                             // show the account name on the display
            //delayNoBlock(500);                                                // remove for production
            pos = FindAccountPos(field);                                        // get the next open position
            if (!updateExistingAccount) {                                       // if we're updating an existing account no need to write out the account, set the pointers or increment the account count
              if (pos != INITIAL_MEMORY_STATE_BYTE) {                           // if we are not out of space
                SetSaltAndKey(pos);                                             // populate and save the salt, set the key with the salt and master password
                char bufferAcct[ACCOUNT_SIZE];                                  // this is the destination of the encrypted account name
                encrypt32Bytes(bufferAcct, field);                              // encrypt the account name
                while (bufferAcct[0] == (char) INITIAL_MEMORY_STATE_CHAR) {     // check to see if we have an invalid condition after encryption, if we do,
                                                                                // concatenate characters until the first char in the cipher isn't 255.
                  DisplayToError("ERR: 039");                                   // encrypted account name starts with 255, fixing...
                  len = strlen(field);
                  if (len > 2) {
                    field[len - 2] = NULL_TERM;                                 // Chop a character off the end of the account name
                    encrypt32Bytes(bufferAcct, field);                          // encrypt again and hope for the best
                  } else {
                    DisplayToError("ERR: 020");                                 // display the error to the screen and continue processing.  
                    fieldNum = 100;                                             // force our way out of the for loop
                    break;
                  }
                }
                if (fieldNum < 100) {
                  eeprom_write_bytes(GET_ADDR_ACCT(pos),bufferAcct,ACCOUNT_SIZE);// write the account name to eeprom
                  writePointers(pos, field);                                    // insert the account into the linked list by updating prev and next pointers.
                  acctCount++;                                                  // increment the account count
                  uint8_t groups = read_eeprom_byte(GET_ADDR_GROUP(pos));       // read the groups
                  if (groups == INITIAL_MEMORY_STATE_BYTE) writeGroup(pos,NONE);// a set of credentials cannot belong to all groups because that's INITIAL_MEMORY_STATE_BYTE.
                }
              } else {
                fieldNum = 100;                                                 // force our way out of the for loop
                outOfSpace = true;
                DisplayToError("ERR: 012");                                     // out of space in EEprom
              }
            }
            break;
          case 1:                                                               // User Name: code to be executed if fieldNum = 2;
            if (len > (USERNAME_SIZE - 1)) {
              uint32_t i = USERNAME_SIZE - 1;
              while (i < len) field[i++] = NULL_TERM;                           // right pad the field w/ null terminator char
              DisplayToError("ERR: 021");                                       // User name is too long
            }
            char bufferUser[USERNAME_SIZE];
            if (len > 0) {
              ReadSaltAndSetKey(pos);
              encrypt32Bytes(bufferUser, field);
              eeprom_write_bytes(GET_ADDR_USER(pos), bufferUser, USERNAME_SIZE);// write the user name to eeprom
            } else {
              field[0] = NULL_TERM;
              ReadSaltAndSetKey(pos);
              encrypt32Bytes(bufferUser, field);
              eeprom_write_bytes(GET_ADDR_USER(pos), bufferUser, USERNAME_SIZE);// write the empty user name to eeprom; pretty sure this writes two null terminator chars out, being safe
            }
            break;
          case 2:                                                               // Password: code to be executed if fieldNum = 3;
            if (len > (PASSWORD_SIZE - 1)) { 
              uint32_t i = PASSWORD_SIZE - 1;
              while (i < len) field[i++] = NULL_TERM;                           // right pad the field w/ null terminator char
              DisplayToError("ERR: 022");                                       // Password is too long
            }
            char bufferPass[PASSWORD_SIZE];
            if (len > 0) {
              ReadSaltAndSetKey(pos);
              encrypt32Bytes(bufferPass, field);
              eeprom_write_bytes(GET_ADDR_PASS(pos), bufferPass, PASSWORD_SIZE);// write the password to eeprom
            } else {
              field[0] = NULL_TERM;
              ReadSaltAndSetKey(pos);
              encrypt32Bytes(bufferPass, field);
              eeprom_write_bytes(GET_ADDR_PASS(pos), bufferPass, PASSWORD_SIZE);// write the empty password to eeprom; pretty sure this writes two null terminator chars out, being safe
            }
            break;
          case 3:                                                               // URL: code to be executed if fieldNum = 3;
            if (len > (WEBSITE_SIZE - 1)) {
              uint32_t i = WEBSITE_SIZE - 1;
              while (i < len) field[i++] = NULL_TERM;                           // right pad the field w/ null terminator char
              DisplayToError("ERR: 023");                                       // Web site is too long
            }
            char bufferWebsite[WEBSITE_SIZE];
            if (len > 0) {
              ReadSaltAndSetKey(pos);
              encrypt96Bytes(bufferWebsite, field);                             // encrypt the 96 byte long website
              eeprom_write_bytes(GET_ADDR_WEBSITE(pos), bufferWebsite, WEBSITE_SIZE);// write the website to eeprom
            } else {
              field[0] = NULL_TERM;
              ReadSaltAndSetKey(pos);
              encrypt96Bytes(bufferWebsite, field);                             // encrypt the 96 byte long website
              eeprom_write_bytes(GET_ADDR_WEBSITE(pos), bufferWebsite, WEBSITE_SIZE);// write the empty URL to eeprom; pretty sure this writes two null terminator chars out, being safe
            }
            break;
          default:                                                              // code to be executed if fieldNum doesn't match any cases, not an error
            break;
        }                                                                       // end switch
        uint16_t fieldLen = sizeof(field);
        for(uint16_t i = 0; i < fieldLen; i++) field[i] = NULL_TERM;            // empty out the field so nobody can peek at memory after a logout
      }                                                                         // end for fieldNum
    }                                                                           // end while csvgetline
    myFile.close();                                                             // close the file:
    BlankLine2();
    DisplayToStatus("File Imported");
    setGreen();
  } else {
    DisplayToError("ERR: 013");
    //DebugLN("Failed to open file for reading");
  }

  //Debug("Total size of file (bytes): "); if (DEBUG_ENABLED) Serial.println(myFile.size(), DEC); // You can get the current position, remaining data, and total size of the file:
//Debug("Current position in file: "); if (DEBUG_ENABLED) Serial.println(myFile.position(), DEC);
//Debug("Available data to read in file: "); if (DEBUG_ENABLED) Serial.println(myFile.available(), DEC);
//Debug("File name: "); if (DEBUG_ENABLED) Serial.println(myFile.getName());    // And a few other interesting attributes of a file:
//Debug("Is file a directory? "); if (DEBUG_ENABLED) Serial.println(myFile.isDirectory() ? "Yes" : "No");

                                                                                // Open up the file for write and fill it with null terminators, then delete it.
  myFile = fatfs.open(KEEPASS_CSV, FILE_WRITE);                                 // open the file "KPEXPORT.CSV" for writing
  long fileSize = myFile.size();
  for (long i = 0; i <= fileSize; i++) {
    myFile.print('\0');                                                         // fill the file with the null terminator
  }
  myFile.close();                                                               // close the file
  fatfs.remove(KEEPASS_CSV);                                                    // delete the file
  
}

void RestoreFromPPCVSFile() {
  //DebugLN("RestoreFromPPCVSFile()");
  DisplayToStatus("Importing...");
  setYellow();
  if (!flash.begin()) {
    DisplayToError("ERR: 034");
    return;
  }
  //Debug("Flash chip JEDEC ID: 0x"); if (DEBUG_ENABLED) Serial.println(flash.getJEDECID(), HEX);

  // First call begin to mount the filesystem.  Check that it returns true
  // to make sure the filesystem was mounted.
  if (!fatfs.begin(&flash)) {
    DisplayToError("ERR: 014");
    //DebugLN("Error, failed to mount newly formatted filesystem!");
    //DebugLN("Was the flash chip formatted with the SdFat_format example?");
    return;
  }
  DisplayToStatus("Mounted filesystem");
  //DebugLN("Mounted filesystem!");

  File myFile;                                                                  
  myFile = fatfs.open(PP_CSV);                                                  // open the file "KPEXPORT.CSV" for reading
  if (myFile) {
    //DebugLN("Opened file");
    DisplayToStatus("File open");
    uint8_t fieldNum, numFields, pos;
    char *line;
    boolean outOfSpace = false;
    while (((line = csvgetline(myFile)) != NULL) && !outOfSpace) {
      String dummy = myFile.readStringUntil('\n');                              // TODO: check to see if we're skipping the first set of credentials
      for (fieldNum = 0; fieldNum < csvnfield(); fieldNum++) {
        char *field = csvfield(fieldNum);
        //DebugMetric("fieldNum: ", fieldNum);Debug(field);
        size_t len = strlen(field);
        uint8_t key[KEY_SIZE];                                                  // set the key so we're prepared when we write the account to EEprom
        switch (fieldNum)
        {
          case 0:                                                               // code to be executed if fieldNum = 1;
            if (len > (ACCOUNT_SIZE - 1)) {
              uint32_t i = ACCOUNT_SIZE - 1;
              while (i < len) field[i++] = NULL_TERM;                           // right pad the field w/ null terminator char
              DisplayToError("ERR: 024");                                       // User name is too long
            }
            //Debug("Account: ");DebugLN(field);
            DisplayToStatus(field);                                             // show the account name on the display
            pos = FindAccountPos(field);                                        // get the next open position
            if (!updateExistingAccount) {                                       // if we're updating an existing account no need to write out the account, set the pointers or increment the account count
              if (pos != INITIAL_MEMORY_STATE_BYTE) {                           // if we are not out of space
                SetSaltAndKey(pos);                                             // populate and save the salt, set the key with the salt and master password
                char bufferAcct[ACCOUNT_SIZE];
                encrypt32Bytes(bufferAcct, field);
                while (bufferAcct[0] == (char) INITIAL_MEMORY_STATE_CHAR) {     // check to see if we have an invalid condition after encryption, if we do,
                                                                                // concatenate characters until the first char in the cipher isn't 255.
                  DisplayToError("ERR: 039");                                   // encrypted account name starts with 255, fixing...
                  len = strlen(field);
                  if (len > 2) {
                    field[len - 2] = NULL_TERM;                                 // Chop a character off the end of the account name
                    encrypt32Bytes(bufferAcct, field);                          // encrypt again and hope for the best
                  } else {
                    DisplayToError("ERR: 020");                                 // display the error to the screen and continue processing.  
                    fieldNum = 100;                                             // force our way out of the for loop
                    break;
                  }
                }
                if (fieldNum < 100) {
                  if (!updateExistingAccount) {                                 // if we're updating an existing account no need to write out the account, set the pointers or increment the account count
                    eeprom_write_bytes(GET_ADDR_ACCT(pos),bufferAcct,ACCOUNT_SIZE); // write the account name to eeprom
                    writePointers(pos, field);                                  // insert the account into the linked list by updating prev and next pointers.
                    acctCount++;
                  }
                  uint8_t groups = read_eeprom_byte(GET_ADDR_GROUP(pos));       // initialize the groups
                  if (groups ==INITIAL_MEMORY_STATE_BYTE) writeGroup(pos,NONE); // a set of credentials cannot belong to all groups because that's INITIAL_MEMORY_STATE_BYTE.
                }
              } else {
                fieldNum = 100;                                                 // force our way out of the for loop
                outOfSpace = true;
                DisplayToError("ERR: 012");                                     // out of space in EEprom
              }
            }
            break;
          case 1:                                                               // code to be executed if fieldNum = 2;
            if (len > (USERNAME_SIZE - 1)) {
              uint32_t i = USERNAME_SIZE - 1;
              while (i < len) field[i++] = NULL_TERM;                           // right pad the field w/ null terminator char
              delayNoBlock(ONE_SECOND * 2);
            }
            char bufferUser[USERNAME_SIZE];
            if (len > 0) {
              ReadSaltAndSetKey(pos);
              encrypt32Bytes(bufferUser, field);
              eeprom_write_bytes(GET_ADDR_USER(pos), bufferUser, USERNAME_SIZE);// write the user name to eeprom
            } else {
              field[0] = NULL_TERM;
              ReadSaltAndSetKey(pos);
              encrypt32Bytes(bufferUser, field);
              eeprom_write_bytes(GET_ADDR_USER(pos), bufferUser, USERNAME_SIZE);// write the empty user name to eeprom; pretty sure this writes two null terminator chars out, being safe
            }
            break;
          case 2:                                                               // Password: code to be executed if fieldNum = 3;
            if (len > (PASSWORD_SIZE - 1)) { 
              uint32_t i = PASSWORD_SIZE - 1;
              while (i < len) field[i++] = NULL_TERM;                           // right pad the field w/ null terminator char
              DisplayToError("ERR: 022");                                       // Password is too long
            }
            char bufferPass[PASSWORD_SIZE];
            if (len > 0) {
              ReadSaltAndSetKey(pos);
              encrypt32Bytes(bufferPass, field);
              eeprom_write_bytes(GET_ADDR_PASS(pos), bufferPass, PASSWORD_SIZE);// write the password to eeprom
            } else {
              field[0] = NULL_TERM;
              ReadSaltAndSetKey(pos);
              encrypt32Bytes(bufferPass, field);
              eeprom_write_bytes(GET_ADDR_PASS(pos), bufferPass, PASSWORD_SIZE);// write the empty password to eeprom; pretty sure this writes two null terminator chars out, being safe
            }
            break;
          case 3:                                                               // code to be executed if fieldNum = 3;
            if (len > (WEBSITE_SIZE - 1)) {
              uint32_t i = WEBSITE_SIZE - 1;
              while (i < len) field[i++] = NULL_TERM;                           // right pad the field w/ null terminator char
              DisplayToError("ERR: 023");                                       // Web site is too long
            }
            char bufferWebsite[WEBSITE_SIZE];
            if (len > 0) {
              ReadSaltAndSetKey(pos);
              encrypt96Bytes(bufferWebsite, field);                             // encrypt the 64 byte long website
              eeprom_write_bytes(GET_ADDR_WEBSITE(pos), bufferWebsite, WEBSITE_SIZE);// write the website to eeprom
            } else {
              field[0] = NULL_TERM;
              ReadSaltAndSetKey(pos);
              encrypt96Bytes(bufferWebsite, field);                             // encrypt the 64 byte long website
              eeprom_write_bytes(GET_ADDR_WEBSITE(pos), bufferWebsite, WEBSITE_SIZE);// write the empty URL to eeprom; pretty sure this writes two null terminator chars out, being safe
            }
            break;
          case 4:                                                               // this is the group
            if (len > (GROUP_SIZE)) {
              DisplayToError("ERR: 035");                                       // Web site is too long
            }
            uint8_t group;
            group = atoi(field);
            //uint8_t group;                                                    // alternate method...
            //sscanf(field, "%d", &group);
            write_eeprom_byte(GET_ADDR_GROUP(pos), group);                      // write group to eeprom, no need to encrypt
            break;
          default:
            DisplayToError("ERR: 036");
            break;
        }                                                                       // end switch
        uint16_t fieldLen = sizeof(field);
        for(uint16_t i = 0; i < fieldLen; i++) field[i] = NULL_TERM;            // empty out the field so nobody can peek at memory after a logout
      }                                                                         // end for fieldNum
    }                                                                           // end while csvgetline
    myFile.close();                                                             // close the file:
    BlankLine2();
    DisplayToStatus("File Imported");
    setGreen();
  } else {
    DisplayToError("ERR: 037");
    //DebugLN("Failed to open PasswordPump csv file for reading");
  }

//Debug("Total size of file (bytes): "); if (DEBUG_ENABLED) Serial.println(myFile.size(), DEC); // You can get the current position, remaining data, and total size of the file:
//Debug("Current position in file: "); if (DEBUG_ENABLED) Serial.println(myFile.position(), DEC);
//Debug("Available data to read in file: "); if (DEBUG_ENABLED) Serial.println(myFile.available(), DEC);
//Debug("File name: "); if (DEBUG_ENABLED) Serial.println(myFile.getName());    // And a few other interesting attributes of a file:
//Debug("Is file a directory? "); if (DEBUG_ENABLED) Serial.println(myFile.isDirectory() ? "Yes" : "No");

                                                                                // Open up the file for write and fill it with null terminators, then delete it.
  myFile = fatfs.open(PP_CSV, FILE_WRITE);                                      // open the file "KPEXPORT.CSV" for writing
  long fileSize = myFile.size();
  for (long i = 0; i <= fileSize; i++) {
    myFile.print('\0');                                                         // fill the file with the null terminator
  }
  myFile.close();                                                               // close the file
  fatfs.remove(PP_CSV);                                                         // delete the file
  
}

void ImportChromeExportFile() {
  //DebugLN("ImportChromeExportFile()");
  DisplayToStatus("Importing...");
  setYellow();
  if (!flash.begin()) {
    DisplayToError("ERR: 034");
    return;
  }
  //Debug("Flash chip JEDEC ID: 0x"); if (DEBUG_ENABLED) Serial.println(flash.getJEDECID(), HEX);

  // First call begin to mount the filesystem.  Check that it returns true
  // to make sure the filesystem was mounted.
  if (!fatfs.begin(&flash)) {
    DisplayToError("ERR: 014");
    //DebugLN("Error, failed to mount newly formatted filesystem!");
    //DebugLN("Was the flash chip formatted with the SdFat_format example?");
    return;
  }
  DisplayToStatus("Mounted filesystem");
  //DebugLN("Mounted filesystem!");

  File myFile;                                                                  
  myFile = fatfs.open(CP_CSV);                                                  // open the file "KPEXPORT.CSV" for reading
  if (myFile.available()) {
    String header = myFile.readStringUntil('\n');                               // read and throw away the header
  }
  if (myFile) {
    //DebugLN("Opened file");
    DisplayToStatus("File open");
    uint8_t fieldNum, numFields, pos;
    char *line;
    boolean outOfSpace = false;
    while (((line = csvgetline(myFile)) != NULL) && !outOfSpace) {
      String dummy = myFile.readStringUntil('\n');                              // TODO: check to see if we're skipping the first set of credentials
      for (fieldNum = 0; fieldNum < csvnfield(); fieldNum++) {
        char *field = csvfield(fieldNum);
        //DebugMetric("fieldNum: ", fieldNum);Debug(field);
        size_t len = strlen(field);
        uint8_t key[KEY_SIZE];                                                  // set the key so we're prepared when we write the account to EEprom
        switch (fieldNum)
        {
          case 0:                                                               // code to be executed if fieldNum = 1;
            if (len > (ACCOUNT_SIZE - 1)) {
              uint32_t i = ACCOUNT_SIZE - 1;
              while (i < len) field[i++] = NULL_TERM;                           // right pad the field w/ null terminator char
              DisplayToError("ERR: 024");                                       // User name is too long
            }
            //Debug("Account: ");DebugLN(field);
            DisplayToStatus(field);                                             // show the account name on the display
            pos = FindAccountPos(field);                                        // get the next open position
            if (!updateExistingAccount) {                                       // if we're updating an existing account no need to write out the account, set the pointers or increment the account count
              if (pos != INITIAL_MEMORY_STATE_BYTE) {                           // if we are not out of space
                SetSaltAndKey(pos);                                             // populate and save the salt, set the key with the salt and master password
                char bufferAcct[ACCOUNT_SIZE];
                encrypt32Bytes(bufferAcct, field);
                while (bufferAcct[0] == (char) INITIAL_MEMORY_STATE_CHAR) {     // check to see if we have an invalid condition after encryption, if we do,
                                                                                // concatenate characters until the first char in the cipher isn't 255.
                  DisplayToError("ERR: 039");                                   // encrypted account name starts with 255, fixing...
                  len = strlen(field);
                  if (len > 2) {
                    field[len - 2] = NULL_TERM;                                 // Chop a character off the end of the account name
                    encrypt32Bytes(bufferAcct, field);                          // encrypt again and hope for the best
                  } else {
                    DisplayToError("ERR: 020");                                 // display the error to the screen and continue processing.  
                    fieldNum = 100;                                             // force our way out of the for loop
                    break;
                  }
                }
                if (fieldNum < 100) {
                  if (!updateExistingAccount) {                                 // if we're updating an existing account no need to write out the account, set the pointers or increment the account count
                    eeprom_write_bytes(GET_ADDR_ACCT(pos),bufferAcct,ACCOUNT_SIZE); // write the account name to eeprom
                    writePointers(pos, field);                                  // insert the account into the linked list by updating prev and next pointers.
                    acctCount++;
                  }
                  uint8_t groups = read_eeprom_byte(GET_ADDR_GROUP(pos));       // initialize the groups
                  if (groups == INITIAL_MEMORY_STATE_BYTE) writeGroup(pos,NONE);// a set of credentials cannot belong to all groups because that's INITIAL_MEMORY_STATE_BYTE.
                }
              } else {
                fieldNum = 100;                                                 // force our way out of the for loop
                outOfSpace = true;
                DisplayToError("ERR: 012");                                     // out of space in EEprom
              }
            }
            break;
          case 1:                                                               // code to be executed if fieldNum = 3;
            if (len > (WEBSITE_SIZE - 1)) {
              uint32_t i = WEBSITE_SIZE - 1;
              while (i < len) field[i++] = NULL_TERM;                           // right pad the field w/ null terminator char
              DisplayToError("ERR: 023");                                       // Web site is too long
            }
            char bufferWebsite[WEBSITE_SIZE];
            if (len > 0) {
              ReadSaltAndSetKey(pos);
              encrypt96Bytes(bufferWebsite, field);                             // encrypt the 64 byte long website
              eeprom_write_bytes(GET_ADDR_WEBSITE(pos), bufferWebsite, WEBSITE_SIZE);// write the website to eeprom
            } else {
              field[0] = NULL_TERM;
              ReadSaltAndSetKey(pos);
              encrypt96Bytes(bufferWebsite, field);                             // encrypt the 64 byte long website
              eeprom_write_bytes(GET_ADDR_WEBSITE(pos), bufferWebsite, WEBSITE_SIZE);// write the empty URL to eeprom; pretty sure this writes two null terminator chars out, being safe
            }
            break;
          case 2:                                                               // code to be executed if fieldNum = 2;
            if (len > (USERNAME_SIZE - 1)) {
              uint32_t i = USERNAME_SIZE - 1;
              while (i < len) field[i++] = NULL_TERM;                           // right pad the field w/ null terminator char
              DisplayToError("ERR: 021");                                       // User name is too long
            }
            char bufferUser[USERNAME_SIZE];
            if (len > 0) {
              ReadSaltAndSetKey(pos);
              encrypt32Bytes(bufferUser, field);
              eeprom_write_bytes(GET_ADDR_USER(pos), bufferUser, USERNAME_SIZE);// write the user name to eeprom
            } else {
              field[0] = NULL_TERM;
              ReadSaltAndSetKey(pos);
              encrypt32Bytes(bufferUser, field);
              eeprom_write_bytes(GET_ADDR_USER(pos), bufferUser, USERNAME_SIZE);// write the empty user name to eeprom; pretty sure this writes two null terminator chars out, being safe
            }
            break;
          case 3:                                                               // code to be executed if fieldNum = 3;
            if (len > (PASSWORD_SIZE - 1)) { 
              uint32_t i = PASSWORD_SIZE - 1;
              while (i < len) field[i++] = NULL_TERM;                           // right pad the field w/ null terminator char
              DisplayToError("ERR: 022");                                       // Password is too long
            }
            char bufferPass[PASSWORD_SIZE];
            if (len > 0) {
              char bufferPass[PASSWORD_SIZE];
              ReadSaltAndSetKey(pos);
              encrypt32Bytes(bufferPass, field);
              eeprom_write_bytes(GET_ADDR_PASS(pos), bufferPass, PASSWORD_SIZE);// write the password to eeprom
            } else {
              field[0] = NULL_TERM;
              ReadSaltAndSetKey(pos);
              encrypt32Bytes(bufferPass, field);
              eeprom_write_bytes(GET_ADDR_PASS(pos), bufferPass, PASSWORD_SIZE);// write the empty password to eeprom; pretty sure this writes two null terminator chars out, being safe
            }
            break;
          default:
            DisplayToError("ERR: 036");
            break;
        }                                                                       // end switch
        uint16_t fieldLen = sizeof(field);
        for(uint16_t i = 0; i < fieldLen; i++) field[i] = NULL_TERM;            // empty out the field so nobody can peek at memory after a logout
      }                                                                         // end for fieldNum
    }                                                                           // end while csvgetline
    myFile.close();                                                             // close the file:
    BlankLine2();
    DisplayToStatus("File Imported");
    setGreen();
  } else {
    DisplayToError("ERR: 037");
    //DebugLN("Failed to open PasswordPump csv file for reading");
  }

  //Debug("Total size of file (bytes): "); if (DEBUG_ENABLED) Serial.println(myFile.size(), DEC); // You can get the current position, remaining data, and total size of the file:
//Debug("Current position in file: "); if (DEBUG_ENABLED) Serial.println(myFile.position(), DEC);
//Debug("Available data to read in file: "); if (DEBUG_ENABLED) Serial.println(myFile.available(), DEC);
//Debug("File name: "); if (DEBUG_ENABLED) Serial.println(myFile.getName());    // And a few other interesting attributes of a file:
//Debug("Is file a directory? "); if (DEBUG_ENABLED) Serial.println(myFile.isDirectory() ? "Yes" : "No");

                                                                                // Open up the file for write and fill it with null terminators, then delete it.
  myFile = fatfs.open(CP_CSV, FILE_WRITE);                                      // open the file "KPEXPORT.CSV" for writing
  long fileSize = myFile.size();
  for (long i = 0; i <= fileSize; i++) {
    myFile.print('\0');                                                         // fill the file with the null terminator
  }
  myFile.close();                                                               // close the file
  fatfs.remove(CP_CSV);                                                         // delete the file
  
}

//- CSV Processing

static int endofline(File fin, int c)                                           // endofline: check for and consume \r, \n, \r\n, or EOF
{
  int eol;
  eol = (c=='\r' || c=='\n');
  if (c == '\r') {
    c = fin.peek();
    if (c == '\n' || c == EOF)
      fin.read();                                                               // pull the char off of serial
  }
  return eol;
}

static void reset(void)                                                         // reset: set variables back to starting values
{
  free(line);                                                                   // free(NULL) permitted by ANSI C
  free(sline);
  free(field);
  line = NULL;
  sline = NULL;
  field = NULL;
  maxline = maxfield = nfield = 0;
}

                                                                                // csvgetline:  get one line, grow as needed
                                                                                // sample input: "LU",86.25,"11/4/1998","2:19PM",+4.0625
char *csvgetline(File fin)
{  
  int i, c;
  char *newl, *news;

  if (line == NULL) {                                                           // allocate on first call
    maxline = maxfield = 1;
    line = (char *) malloc(maxline);
    sline = (char *) malloc(maxline);
    field = (char **) malloc(maxfield*sizeof(field[0]));
    if (line == NULL || sline == NULL || field == NULL) {
      reset();
      return NULL;                                                              // out of memory
    }
  }
  for (i=0; (c=fin.read())!=EOF && !endofline(fin,c); i++) {
    if (i >= maxline-1) {                                                       // grow line
      maxline *= 2;                                                             // double current size
      newl = (char *) realloc(line, maxline);
      if (newl == NULL) {
        reset();
        return NULL;
      }
      line = newl;
      news = (char *) realloc(sline, maxline);
      if (news == NULL) {
        reset();
        return NULL;
      }
      sline = news;
    }
    line[i] = c;
  }
  line[i] = '\0';
  if (split() == NOMEM) {
    reset();
    return NULL;                                                                // out of memory
  }
  return (c == EOF && i == 0) ? NULL : line;
}


static int split(void)                                                          // split: split line into fields
{
  char *p, **newf;
  char *sepp;                                                                   // pointer to temporary separator character
  int sepc;                                                                     // temporary separator character

  nfield = 0;
  if (line[0] == '\0')
    return 0;
  strcpy(sline, line);
  p = sline;

  do {
    if (nfield >= maxfield) {
      maxfield *= 2;                                                            // double current size
      newf = (char **) realloc(field, 
            maxfield * sizeof(field[0]));
      if (newf == NULL)
        return NOMEM;
      field = newf;
    }
    if (*p == '"')
      sepp = advquoted(++p);                                                    // skip initial quote
    else
      sepp = p + strcspn(p, fieldsep);
    sepc = sepp[0];
    sepp[0] = '\0';                                                             // terminate field
    field[nfield++] = p;
    p = sepp + 1;
  } while (sepc == ',');

  return nfield;
}


static char *advquoted(char *p)                                                 // advquoted: quoted field; return pointer to next separator
{
  int i, j;

  for (i = j = 0; p[j] != '\0'; i++, j++) {
    if (p[j] == '"' && p[++j] != '"') {
                                                                                // copy up to next separator or \0
      int k = strcspn(p+j, fieldsep);
      memmove(p+i, p+j, k);
      i += k;
      j += k;
      break;
    }
    p[i] = p[j];
  }
  p[i] = '\0';
  return p + j;
}

char *csvfield(int n)                                                           // csvfield:  return pointer to n-th field
{
  if (n < 0 || n >= nfield)
    return NULL;
  return field[n];
}

int csvnfield(void)                                                             // csvnfield:  return number of fields
{
  return nfield;
}
*/

/*
#define REPS 1000
void setup1() {
  Serial.begin(9600);
  while (!Serial);
  delay(2000);
  MCLK->APBCMASK.reg |= MCLK_APBCMASK_TRNG;   // TRNG clock on
  TRNG->CTRLA.reg = TRNG_CTRLA_ENABLE;
}

void loop1() {
  uint32_t r, us;
  us = micros();
  for (int i = 0; i < REPS; i++) {
    while ((TRNG->INTFLAG.reg & TRNG_INTFLAG_DATARDY) == 0) ; // 84 APB cycles
    r = TRNG->DATA.reg;
  }
  us = micros() - us;
  Serial.print(us); Serial.print(" us   mbs ");
  Serial.println(32 * REPS / us);
  Serial.println(r, HEX);
  delay(2000);
}

// https://forum.arduino.cc/index.php?topic=129083.0
// samd51 AES CBC 128-bit key

#define PRREG(x) Serial.print(#x" 0x"); Serial.println(x,HEX)
#define NBYTES (1024)

void aes_init() {
  MCLK->APBCMASK.reg |= MCLK_APBCMASK_AES;
}

void aes_setkey(const uint8_t *key, size_t keySize) {
  memcpy((uint8_t *)&REG_AES_KEYWORD0, key, keySize);
}

void aes_cbc_encrypt(const uint8_t *plaintext, uint8_t *ciphertext, size_t size, const uint8_t iv[16])
{
  int i;

  memcpy((uint8_t *)&REG_AES_INTVECTV0, iv, 16);
  REG_AES_CTRLA = 0;
  REG_AES_CTRLA = AES_CTRLA_AESMODE_CBC | AES_CTRLA_CIPHER_ENC | AES_CTRLA_ENABLE;
  REG_AES_CTRLB |= AES_CTRLB_NEWMSG;
  uint32_t *wp = (uint32_t *) plaintext;   // need to do by word ?
  uint32_t *wc = (uint32_t *) ciphertext;
  // block 4-words  16B
  int word = 0;
  while (size > 0) {
    for (i = 0;  i < 4; i++) REG_AES_INDATA = wp[i + word];
    REG_AES_CTRLB |=  AES_CTRLB_START;
    while ((REG_AES_INTFLAG & AES_INTENCLR_ENCCMP) == 0);  // wait for done
    for (i = 0;  i < 4; i++) wc[i + word] = REG_AES_INDATA;
    size -= 16;
    word += 4;
  }
}

void aes_cbc_decrypt(const uint8_t *ciphertext, uint8_t *plaintext, size_t size, const uint8_t iv[16])
{
  int i;

  memcpy((uint8_t *)&REG_AES_INTVECTV0, iv, 16);
  REG_AES_CTRLA = 0;
  REG_AES_CTRLA = AES_CTRLA_AESMODE_CBC | AES_CTRLA_CIPHER_DEC | AES_CTRLA_ENABLE;
  REG_AES_CTRLB |= AES_CTRLB_NEWMSG ;
  uint32_t *wp = (uint32_t *) plaintext;   // need to do by word ?
  uint32_t *wc = (uint32_t *) ciphertext;
  // block 4-words  16B
  int word = 0;
  while (size > 0) {
    for (i = 0;  i < 4; i++) REG_AES_INDATA = wc[i + word];
    REG_AES_CTRLB |= AES_CTRLB_START;
    while ((REG_AES_INTFLAG & AES_INTENCLR_ENCCMP) == 0);  // wait for done
    for (i = 0;  i < 4; i++) wp[i + word] = REG_AES_INDATA;
    size -= 16;
    word += 4;
  }
}

void setup2() {
  Serial.begin(9600);
  while (!Serial);
  delay(1000);
  PRREG(MCLK->APBCMASK.reg);   //aes bit 9
  PRREG(REG_PAC_STATUSC);      // aes bit 9
  aes_init();

  PRREG(MCLK->APBCMASK.reg);
  PRREG(REG_AES_CTRLA);
  PRREG(REG_AES_CTRLB);
}

void loop2() {
  static const uint8_t keyAes128[]  =
  { 0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6,
    0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c
  };
  static const uint8_t ive[] =
  { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
    0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f
  };
  static const uint8_t plainAes128[] =
  { 0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96,
    0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a
  };
  static const uint8_t cipherAes128[] =
  { 0x76, 0x49, 0xab, 0xac, 0x81, 0x19, 0xb2, 0x46,
    0xce, 0xe9, 0x8e, 0x9b, 0x12, 0xe9, 0x19, 0x7d
  };
  uint8_t  inmsg[NBYTES], cipherout[NBYTES], clearout[NBYTES];
  uint32_t t, i;

  for (i = 0; i < sizeof(inmsg); i++) inmsg[i] = i;
  memset(cipherout, 0, NBYTES);
  aes_setkey(keyAes128, 16);
  // verify
  aes_cbc_encrypt(plainAes128, cipherout, 16, ive);
  Serial.print("enc memcmp "); Serial.println(memcmp(cipherout, cipherAes128, 16));
  aes_cbc_decrypt(cipherout, clearout, 16, ive);
  Serial.print("dec memcmp "); Serial.println(memcmp(clearout, plainAes128, 16));

  memset(cipherout, 7, NBYTES);
  t = micros();
  aes_cbc_encrypt(inmsg, cipherout, sizeof(inmsg), ive);
  t = micros() - t;
  Serial.print(t); Serial.println(" us");
  aes_cbc_decrypt(cipherout, clearout, sizeof(inmsg), ive);
  Serial.print("memcmp "); Serial.println(memcmp(inmsg, clearout, sizeof(inmsg)));
  delay(3000);
}

// Free RAM

extern "C" char *sbrk(int i);
int FreeRam () {
char stack_dummy = 0;
return &stack_dummy - sbrk(0);
}
*/

// .--. .- ... ... .-- --- .-. -.. .--. ..- -- .--. 
