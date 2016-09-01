# libmaple

Taken from https://bitbucket.org/nfd/arduino-maple and converted into an Arduino library.

##Wiring

* Red wire: PORTB0 (Pin 8 on Duemilanove/Uno; Pin 53 on Mega)
* White wire: PORTB1 (Pin 9 on Duemilanove/Uno; Pin 52 on Mega)
* Blue wire: +5V
* Brown/Black wire: GND
* Green wire: Unconnected or GND (connected to GND inside the controller)
* GND (unshielded): GND

##Usage

After uploading to your Arduino, run one of the Python scripts in the `util` folder.  The Python scripts require the [pySerial](https://github.com/pyserial/pyserial) library (run `pip install pyserial` to install it).  You may need to edit the `maple.py` file and change the serial port name to the correct serial port for your Arduino.

##Issues

According to the original commit comments, the code probably doesn't work on Arduino Megas.
