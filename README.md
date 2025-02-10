Simple example of implementation canbox RISE protocol to communicate with almost any Android Head Unit.
Works on Arduino Uno
You just need to change sketch to suit your needs.

If using Arduino / LGT8F328P (or any with 5V IO) you need logic converter or simple voltage divider for TX (Arduino) -> RX HU line.
RX Arduino < TX HU Not Connected!

Arduino TX ----[1.8kΩ]----+---- Head Unit RX 
                           |
                         [3.3kΩ]
                           |
                          GND
 1kOhm and 2kOhm works also.

RISE protocol looks like:
0x2E 0x01 0x02 0x01 0x01 0xDB
 │    │    │   └───┼───┘  └────── checksum (0xFF - sum of the previous bytes excluding the header, can overflow) 
 │    │    │       └───────────── data bytes
 │    │    └───────────────────── length of the payload
 │    └────────────────────────── function id
 └─────────────────────────────── header

Baud rate 38400


Job went really smooth thanks the following repos:
https://github.com/morcibacsi/JunsunPSARemote
https://github.com/smartgauges/canbox
