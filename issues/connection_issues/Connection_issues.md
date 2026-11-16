## ESP32-S3-Dev-Kit does not connect to computer

* Assumption : You have an ESP board that should be connected via UART or USB to your computer. You only want to test the board and nothing else. No pins, no setup, no external devices. Only the board itself.

* The dev kit has two micro USB ports - one labled USB, one labled UART
* The one labeled "USB" shows up under Linux as /dev/ttyACM0.
* On my setup this led to connection issues and flashing failed.
* Solution - use the other part labeled "UART". The device shows up as /dev/ttyUSB0 and works reliably on my Ubuntu Linux computer. 

## Wrong USB cable

* Assumption : You have an ESP board and connect it to your computer. 
* You check all listed  devices at /dev/  before connecting the board and after connecting the board. During the time for checking the only thing you change is that you connect the board. No additional services that the OS kernel might recognize as virtual tty devices or similar things are running.  No additional device shows up.


* This might have other reasons but in my case the USB cable did not transfer any data. It can be used only for charging. Some USB cables prevent data exchange by not having the physical connections built in that are needed for data transfer. This might be either implemented for security reasons (data transfer or data access without authorisation by a compromized USB device) 

