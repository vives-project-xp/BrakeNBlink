LED SK8612 RGBW LED Strip
<img width="500" height="500" alt="image" src="https://github.com/user-attachments/assets/5331d101-ad78-406b-be5b-abb65294f18e" />

# specificaties:
- Voltage: DC5V
- IP65 Waterdicht
- Kleur: RGB + Natuurlijk wit
- Verbinding: VCC: rood, GND: Wit, DAT: groen

# Pads betekenis:

- 5V: Power for the LEDs
- GND: Ground
- DIN: Data IN (van de microcontroller)
- DO: Data OUT (naar het volgende LED / strip)
- Each LED passes the remaining data from DO → next LED’s DIN

| Pin      | Arduino                |
|----------|------------------------|
| 5V       | 5V (van een BEC)       |
| DIN/DOUT | Digitale pin (bv. D6)  |
| GND      | GND                    |

