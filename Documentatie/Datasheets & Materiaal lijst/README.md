# BrakeNBlink — Architectuur Document

## 1. Projectoverzicht

BrakeNBlink is een semi-automatisch rem- en richtingaanwijzersysteem voor fietsen. Het systeem bestaat uit twee modules: een **achtermodule** (Peripheral) die remlichten en richtingaanwijzers aanstuurt, en een **stuurmodule** (Central) met drukknoppen voor de richtingaanwijzers. De twee modules communiceren draadloos via Bluetooth Low Energy (BLE).

Optioneel is er een **uitbreidingsmodule** met LED-strips in de spaken van het wiel.

---

## 2. Systeemoverzicht

```
[ Stuurmodule (Central) ]
   - Arduino Nano 33 BLE Sense Rev2
   - 2x Drukknop
   - 2x LED strip (richtingaanwijzer links/rechts)
   - Batterij (3 x AAA)
          |
          | Bluetooth Low Energy (BLE)
          |
[ Achtermodule (Peripheral) ]
   - Arduino Nano 33 BLE Sense Rev2
   - IMU ingebouwd (BMI270 + BMM150)
   - 3x LED strip (links / rechts / rem)
   - Batterij (3 x AAA)

[ Uitbreidingsmodule (optioneel) ]
   - Arduino Nano 33 BLE Sense Rev2
   - 2x LED strip (spaken)
   - IMU (snelheidsmeter)
   - Batterij (3 x AA)
```

---

## 3. Componenten

### 3.1 Microcontroller — Arduino Nano 33 BLE Sense Rev2

| Eigenschap             | Waarde                              |
|------------------------|-------------------------------------|
| Voedingsspanning       | 3.3 V (logica) / 5 V (USB / VIN)   |
| Max stroom per I/O pin | 15 mA                               |
| Aanbevolen VIN         | 5 – 21 V                            |
| BLE                    | Bluetooth 5.0                       |
| IMU                    | BMI270 (accel/gyro) + BMM150 (mag)  |
| Afmetingen             | 45 × 18 mm                          |
| Verbruik actief        | 60 mA                               |
| Verbruik BLE actief    | 70 mA                               |
| Max vermogen           | 0.35 W                              |

> Wordt gebruikt in: Stuurmodule (Central), Achtermodule (Peripheral) en Uitbreidingsmodule.

---

### 3.2 LED Strip — SK6812 RGBW

| Eigenschap               | Waarde                                              |
|--------------------------|-----------------------------------------------------|
| Voedingsspanning         | 5 V DC                                              |
| Stroom per LED (volledig)| 80 mA                                                |
| Max stroom (16 LEDs)     | 1280 mA                                              |
| Max vermogen (16 LEDs)   | 6.4 W                                                |
| Kleur                    | RGB + Natuurlijk Wit                                |
| Waterdichtheid           | IP65                                                |
| Dataprotocol             | NeoPixel (800 kHz)                                  |
| Logicaspanning data      | 5 V (3.3 V compatibel via niveau-omzetter)          |

**Aansluitingen:**

| Strip-pin | Kleur draad | Aansluiting                         |
|-----------|-------------|-------------------------------------|
| 5V / VCC  | Rood        | 5 V (via BEC of externe voeding)    |
| GND       | Wit         | GND                                 |
| DIN       | Groen       | Digitale pin Arduino (zie module)   |
| DO        | —           | DIN van de volgende LED / strip     |

> Elke LED geeft de resterende data door via DO → DIN van de volgende LED.

---

### 3.3 Drukknop (2-pin mechanisch)

| Eigenschap           | Waarde                                  |
|----------------------|-----------------------------------------|
| Type                 | Mechanische drukknop, 2-pin             |
| Standaard toestand   | HOOG (INPUT_PULLUP actief)              |
| Ingedrukt            | Verbonden met GND → LAAG               |
| Max spanning         | 12 V                                    |
| Max stroom           | 100 mA                                  |
| Debounce tijd (code) | 150 ms                                  |

**Aansluitingen:**

| Knop-pin | Aansluiting Arduino                         |
|----------|---------------------------------------------|
| Pin 1    | GND                                         |
| Pin 2    | Digitale pin (D2 of D3) met INPUT_PULLUP    |

---

### 3.4.1 Batterij — 3 × AAA 

| Eigenschap          | Stuurmodule        | Achtermodule       |
|---------------------|--------------------|--------------------|
| Aantal cellen       | 3 × AAA             | 3 × AAA             |
| Nominale spanning   | 4.5 V              | 4.5 V              |
| Capaciteit          | 3000 mAh           | 3000 mAh           | 
| Max ontlaadstroom   | 1.5 A              | 1.5 A              |

### 3.4.2 Batterij — 3 × AA 

| Eigenschap          | Uitbreidingsmodule |
|---------------------|--------------------|
| Aantal cellen       | 3 × AA              |
| Nominale spanning   | 4.5 V              |
| Capaciteit          | 2400 mAh           |

---

### 3.5 Verbindingskabel — JST-SM 3-pin Verlengkabel

| Eigenschap | Waarde                        |
|------------|-------------------------------|
| Lengte     | 30 cm                         |
| Pinnen     | 3                             |
| Type       | JST-SM Compatibel             |
| Gebruik    | Aansluiting batterijhouder    |

---

## 4. Pin-mapping per module

### 4.1 Stuurmodule (Central) — Arduino Nano 33 BLE Sense Rev2

| Pin | Functie                       | Component                  |
|-----|-------------------------------|----------------------------|
| D2  | Knop Links (INPUT_PULLUP)     | Drukknop Links             |
| D3  | Knop Rechts (INPUT_PULLUP)    | Drukknop Rechts            |
| D4  | LED strip Links (DIN)         | SK6812 strip Links         |
| D5  | LED strip Rechts (DIN)        | SK6812 strip Rechts        |
| 5V  | Voeding LED strips            | SK6812 via BEC / extern    |
| GND | Ground                        | Alle componenten           |
| VIN | Voeding vanuit batterij       | Batterijhouder             |

> BLE rol: **Central** — scant en verbindt met de Peripheral.

---

### 4.2 Achtermodule (Peripheral) — Arduino Nano 33 BLE Sense Rev2

| Pin         | Functie                           | Component                  |
|-------------|-----------------------------------|----------------------------|
| D2          | LED strip Links (DIN)             | SK6812 strip Links         |
| D3          | LED strip Rechts (DIN)            | SK6812 strip Rechts        |
| D4          | LED strip Remlicht (DIN)          | SK6812 strip Remlicht      |
| IMU intern  | Versnellingsmeting X-as (ax)      | BMI270 (ingebouwd)         |
| IMU intern  | Kantelmeting lean angle (by, bz)  | BMI270 (ingebouwd)         |
| 5V          | Voeding LED strips                | SK6812 via BEC / extern    |
| GND         | Ground                            | Alle componenten           |
| VIN         | Voeding vanuit batterij           | Batterijhouder             |

> BLE rol: **Peripheral** — adverteert als `"Nano 33 BLE Peripheral"`.  
> IMU drempel remmen: `ax < -0.20 g` → remlicht aan.  
> IMU drempel blinker auto-uit: kanteling `> 10°`, terugkeer `< 2°`.

---

### 4.3 Uitbreidingsmodule (spaken) — Arduino Nano 33 BLE Sense Rev2

| Pin        | Functie                    | Component               |
|------------|----------------------------|-------------------------|
| D2         | LED strip A (DIN)          | SK6812 strip Spaak A    |
| D3         | LED strip B (DIN)          | SK6812 strip Spaak B    |
| IMU intern | Snelheidsmeting            | BMI270 (ingebouwd)      |
| 5V         | Voeding LED strips         | SK6812 via extern       |
| GND        | Ground                     | Alle componenten        |
| VIN        | Voeding vanuit batterij    | Eigen batterij          |

---

## 5. Bluetooth communicatie

| Eigenschap           | Waarde                                       |
|----------------------|----------------------------------------------|
| Protocol             | Bluetooth Low Energy (BLE 5.0)               |
| Service UUID         | `19b10000-e8f2-537e-4f6c-d104768a1214`       |
| Characteristic UUID  | `19b10001-e8f2-537e-4f6c-d104768a1214`       |
| Peripheral naam      | `"Nano 33 BLE Peripheral"`                   |
| Datatype             | Byte (1 byte per commando)                   |

**Stuurcommando's (byte-waarden):**

| Byte waarde | Actie                              |
|-------------|------------------------------------|
| `1`         | Toggle linker richtingaanwijzer    |
| `3`         | Toggle rechter richtingaanwijzer   |

---

## 6. Vermogensverdeling & elektriciteitsbudget

### 6.1 Stuurmodule

| Component               | Spanning (V) | Stroom (mA) | Vermogen (W) |
|-------------------------|--------------|-------------|--------------|
| Arduino Nano 33 BLE     | 3.3 / 5      | 65          | 0.21         |
| LED strip Links (16×)   | 5            | 1280        | 6.4          |
| LED strip Rechts (16×)  | 5            | 1280        | 6.4          |
| Drukknop Links          | 3.3          | ≈ 0         | ≈ 0          |
| Drukknop Rechts         | 3.3          | ≈ 0         | ≈ 0          |
| **Totaal**              |              | 2625        | 13.01        |

### 6.2 Achtermodule

| Component               | Spanning (V) | Stroom (mA) | Vermogen (W) |
|-------------------------|--------------|-------------|--------------|
| Arduino Nano 33 BLE     | 3.3 / 5      | 65          | 0.21         |
| LED strip Links (16×)   | 5            | 1280        | 6.4          |
| LED strip Rechts (16×)  | 5            | 1280        | 6.4          |
| LED strip Rem (16×)     | 5            | 1280        | 6.4          |
| **Totaal**              |              | 3905        | 19.41        |

### 6.3 Uitbreidingsmodule

| Component               | Spanning (V) | Stroom (mA) | Vermogen (W) |
|-------------------------|--------------|-------------|--------------|
| Arduino Nano 33 BLE     | 3.3 / 5      | 65          | 0.21         |
| LED strip A (16×)       | 5            | 1280        | 6.4          |
| LED strip B (16×)       | 5            | 1280        | 6.4          |
| **Totaal**              |              | 2625        | 12.81        |

---

## 7. Softwarebiblioteken

| Bibliotheek            | Versie     | Gebruik                           |
|------------------------|------------|-----------------------------------|
| ArduinoBLE             | 1.2.0      | Bluetooth Low Energy communicatie |
| Adafruit NeoPixel      | 1.10.0     | SK6812 LED strip aansturing       |
| Arduino_BMI270_BMM150  | 1.0.2      | IMU (accelerometer / gyroscoop)   |

---

## 8. IMU logica

### Remdetectie (Achtermodule)
| Parameter         | Waarde                          |
|-------------------|---------------------------------|
| Gemeten as        | Lineaire versnelling X-as (ax)  |
| Drempelwaarde     | `ax < -0.20 g`                  |
| Actie             | Remlicht aan (rood)             |
| Updatefrequentie  | Elke 10 ms                      |

### Richtingaanwijzer automatisch uit (Achtermodule)
| Parameter             | Waarde                                         |
|-----------------------|------------------------------------------------|
| Berekening            | `leanAngle = abs(atan2(by, bz) × 180 / π)`    |
| Bocht gedetecteerd    | `leanAngle > 10°`                              |
| Bocht voltooid        | `leanAngle < 2°` (nadat de fiets geleund was)  |
| Actie                 | Blinker automatisch uit, LEDs uit              |

---

## 9. Gedragsoverzicht

| Situatie                         | Actie systeem                                        |
|----------------------------------|------------------------------------------------------|
| Fietser remt                     | IMU detecteert vertraging → remlicht aan (rood)      |
| Knop links ingedrukt             | Linker LED strip knippert oranje (500 ms interval)   |
| Knop links opnieuw ingedrukt     | Linker richtingaanwijzer uit                         |
| Knop rechts ingedrukt            | Rechter LED strip knippert oranje                    |
| Bocht voltooid (lean detected)   | Blinker automatisch uit                              |
| Geen Bluetooth verbinding        | Verbindings-LED uit, herverbinding automatisch       |

---

