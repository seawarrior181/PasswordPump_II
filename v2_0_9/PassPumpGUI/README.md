# The PasswordPump Graphical User Interface

A project that exists to install the PasswordPumpGUI, [the Users Guide for which is found here][Users Guide].  Reading the users guide is stongly recommended before making a decision to acquire a PasswordPump.

[The source for this project is available here][src].

----

This is the README file for the project.

The PasswordPump is a USB device that manages credentials for up to 250 accounts.  Credentials (account names, usernames, passwords, URLs and old passwords) are stored ONLY on the device itself, on two removable EEprom chips using military grade encryption (AES-256).  The credentials are not stored in the cloud or in a file on your computer where they are more exposed to hackers.  Credentials are backed up on the device itself; i.e. encrypted credentials are moved from the primary EEprom chip to the backup EEprom on demand.  You may remove the EEprom chips from the device (perhaps to keep a third or fourth backup).  Credentials are entered either via the rotary encoder (on the left), via keyboard and serial terminal, or via a Python based graphical user interface (the PasswordPumpGUI).   The PasswordPump works with Windows, Mac OS, Linux distributions and Android (phones and tablets).  The device itself is approximately 1 1/8 x 2 3/4 inches, or 29 x 71 millimeters.

Features
- Stores up to 250 sets of credentials.
- Authenticates with a 15 character master password.
- Search for accounts.
- Data entry via rotary encoder or keyboard and serial monitor, or via client Python GUI running in Windows, Ubuntu, or MacOS.
- Sends a username and password to a computer as if typed in via the keyboard. Can also send URL, old password and account name.
- Add account name, username, password (generated or not), URL, old password
- Accounts are added in alphabetical order.
- Delete an account.
- Edit existing username, password, URL, style (inter-username/password characters, username<Return>password<Return>, username<Tab>password<Return> or username<Tab>password<Tab><Return>), old password, credential groups.
- Generate 8, 10, 16, 24, or 31 character random passwords from the PasswordPump or via the client GUI.
- Automatically saves the old password if it’s not already populated when you generate a password.
- Backup all accounts to a second encrypted external EEprom.
- Logout / de-authenticate via the menu, automatically locks the computer (Windows only).
- Configurable password display on or off.
- Configurable failed login count factory reset (3, 5, 10 or 25).
- Configurable automatic logout after count of minutes (30, 60, 90, 120, 240, 1 or Never).
- Configurable RGB LED intensity (high, medium, low or off).
- Configurable font.
- Configurable orientation, so that the encoder is on the left or the right.
- Configurable generated password size; 8, 10, 16, 24, 31.
- All account names, usernames, passwords and URLs are encrypted w/ AES-256.
- Master password is hashed w/ SHA-256.
- All encrypted credentials fields and the hashed master password are salted.
- The device is not vulnerable to standard password attacks.  See disclaimers.
- The master password can be changed.
- Export to PasswordPump formatted CSV file.
- Import from PasswordPump formatted CSV file.
- Import credentials from Chrome export.
- Import credentials from KeePass export.
- Associate credentials with custom groups for better organization; search by group (defaults are Favorites, Work, Personal, Home, School, Financial, Mail or Health).
- Decoy password feature that automatically factory resets the device if entered (e.g. while the user is under duress).
- Pre-auto-logout indicator/countdown via red and blue flashing RGB LED.
- Factory reset via menu (when authenticated) wipes out all credentials.
- Check if any password has been recovered in a data breach (pwned) on demand.
- Preliminary support for Czech, Danish, Swedish, Norwegian, Finnish, French, German, Spanish, United Kingdom and United States keyboards.
- Displays time left until automatic logout from the device occurs.
- Allows for setting Inter Character Delay for compatibility with some phones and tablets.

[Users Guide]: https://github.com/seawarrior181/PasswordPump_II/blob/master/Password%20Pump%20II%20Users%20Guide.pdf
[src]: https://github.com/seawarrior181/PasswordPump_II
