Just raw copy and edit from Benjamin Project(http://vedder.se/2012/12/stm32f4-discovery-usb-host-and-mp3-player/).
This code implement MP3 player via USB HOST using STM32-Discovery Board. 
Compile it under windows, setting correct PATH ARM-GCC first.

Modified to run on a STM32F411E-DISCO board.
right know it plays 44.1 kHz mp3 encoded files.
it is necessary to adjust values for other samplerates audio settings inside Audio.h