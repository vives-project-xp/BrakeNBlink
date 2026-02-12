# Knoppen

2 knoppen zijn gemonteerd op het stuur van de fiets (links en rechts) en worden gebruikt om de richtingaanwijzers aan te sturen. De fietser klikt op een van de knoppen kort waardoor die richtingaanwijzer aan gaat. Ze gaan automatisch uit als de fiets weer rechtdoor rijdt of als er een tweede keer word geklikt. 

# Type knoppen:

## 1. 2-pin knoppen
<img width="200" height="200" alt="image" src="https://github.com/user-attachments/assets/5db10fa1-df3c-4690-9a71-9cdbbb60af51" />

Dit zijn mechanische knoppen met 2 pins:
- als je niks doet -> circuit is open
- als je klikt -> twee pins zijn verbonden

Standaard staat die op HOOG, als je klikt komt het circuit in verbinding met de GND, waardoor het op LAAG staat.

Wiring van een 2 pin knop:
- Pin 1: GND
- Pin 2: Digitale pin (bv. D2)

Nadeel van 2-pin knoppen: ze switchen niet mooi, niet waterdicht en wanneer er gedrukt wordt, gaan ze open en dicht heel snel voor een paar milliseconden. Dit wordt "bounce" genoemd. Hierdoor kan het zijn dat er meerdere keren "geklikt" wordt. Om dit te fixen kan je best een kleine delay toevoegen met wanneer de laatste keer geklikt werd.

## 2. Tactile push knoppen
<img width="240" height="210" alt="image" src="https://github.com/user-attachments/assets/1b6ccdc1-c21d-4393-8882-7a855f66b9a4" />

Dezelfde werking als 2-pin knoppen, als je erop klikt is het circuit verbonden. Standaard staat die op HOOG, als je klikt komt het circuit in verbinding met de GND, waardoor het op LAAG staat. Het heeft 4 pins:
- Pin 1 en Pin 3 zijn intern verbonden
- Pin 2 en Pin 4 zijn intern verbonden

Wiring van Tactile knop:
- Pin 1 → GND
- Pin 2 → D2
- Pin 3 → niet verbonden
- Pin 4 → niet verbonden

Nadelen:  Niet goed voor vibraties en vaak ook niet waterdicht. 

# 3. SPDT center off switch / slide switch SPDT
<img width="200" height="200" alt="image" src="https://github.com/user-attachments/assets/55bf1823-dab6-4b64-b741-824d0f904870" />

een 3 switch knop, waarbij er 3 mogelijk positie's zijn. links, midden en rechts. Wordt gebruikt op de meeste motors en dus daardoor bekend. Handig als de fietser de button naar een kant duwt voor bv. de linkerrichtingaanwijzers aan te steken. Er kan altijd maar 1 richtingaanwijzer aan en de fietser kan zelf kiezen om het te stoppen. LOW -> Active

Layout:
- Links - Midden (uit) - Rechts

Wiring:
- Links -> 1ste digitale pin (Bv. D1)
- Common -> GND
- Rechts -> 2de digitale pin (Bv. D2)

