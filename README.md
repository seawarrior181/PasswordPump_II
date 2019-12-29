# PasswordPump_II
Version 2 of the PasswordPump, for the ItsyBitsy M4.

To burn the latest version of the firmware (example):
Save PasswordPumpM4_01.ino.bin to C:\Temp
Find where bossac is installed on your system and modify the path below as per it's location.
Identify the port on which the ItsyBitsy/PasswordPump is connected and substitute the correct port number below.

C:\Users\djmurphy>C:\Users\djmurphy\AppData\Local\Arduino15\packages\arduino\tools\bossac\1.8.0-48-gb176eee/bossac -i -d --port=COM52 -U -i --offset=0x4000 -w -v C:\Temp/PasswordPumpM4_01.ino.bin -R
