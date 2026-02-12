<img width="620" height="363" alt="image" src="https://github.com/user-attachments/assets/12f8987a-fb44-43f0-9ed4-7e1c53ca8723" />

LED SK8612 RGBW LED Strip

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

