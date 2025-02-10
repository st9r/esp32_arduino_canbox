# CANBOX RISE Protocol for Arduino

This is a simple implementation of the CANBOX RISE protocol to communicate with almost any Android Head Unit.
It works on **Arduino Uno**.
You just need to modify the sketch to suit your needs.

## Hardware Considerations

If using **Arduino / LGT8F328P** (or any microcontroller with **5V IO**), you need a **logic level converter** or a simple **voltage divider** for the TX line (**Arduino TX -> Head Unit RX**).

**Connection diagram:**

```
Arduino TX ----[1.8kΩ]----+---- Head Unit RX
                           |
                         [3.3kΩ]
                           |
                          GND
```
**Alternative:** 1kΩ and 2kΩ resistors also work.

**Important:**
- **RX Arduino < TX Head Unit** → Not Connected!

## RISE Protocol Structure

```
0x2E 0x01 0x02 0x01 0x01 0xDB
 │    │    │   └───┼───┘  └────── checksum
 │    │    │       └───────────── data bytes
 │    │    └───────────────────── length of the payload
 │    └────────────────────────── function id
 └─────────────────────────────── header
```

**Baud Rate:** `38400`

## Credits

This project was made possible thanks to the following repositories:
- [JunsunPSARemote](https://github.com/morcibacsi/JunsunPSARemote)
- [Smart Gauges CANBOX](https://github.com/smartgauges/canbox)
