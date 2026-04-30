# 3D Print Files - BrakeNBlink Behuizing

Gedetailleerde printinstructies en technische specificaties voor alle onderdelen van BrakeNBlink.

---

## Mappenstructuur

```
3D Print Files/
├── README_3D_Print.md        # Dit bestand
├── Voorkant/                 # Frontale behuizing
│   ├── voorkant.stl
├── Achterkant/               # Achterkant behuizing
│   ├── achterkant.stl
└── Stuur/                    # Stuurelement
    ├── stuur.stl

```
---

## Overzicht Onderdelen

| Onderdeel | Bestand | Gewicht (g) | Print tijd | Moeilijkheid |
|-----------|---------|------------|-----------|--------------|
| Voorkant | `voorkant.stl` | ~25 | 3-4 uur | Gemakkelijk |
| Achterkant | `achterkant.stl` | ~30 | 4-5 uur | Gemiddeld |
| Stuur | `stuur.stl` | ~15 | 2-3 uur | Gemakkelijk |

---

## Aanbevolen Printinstellingen

### Algemene Instellingen
```
Laagdikte:           0.2 mm (standaard) / 0.1 mm (detail)
Vulling:             15-20% (honeycomb of grid patroon)
Ondersteuning:       Standaard (alleen waar nodig)
Snelheid:            50 mm/s (standaard)
Bedtemperatuur:      60°C (PLA) / 80°C (ABS) / 90°C (PETG)
Nozzle Temperatuur:  200°C (PLA) / 230°C (ABS) / 235°C (PETG)
```

### Per Onderdeel Geoptimaliseerd

#### Voorkant (Frontale Behuizing)
**Materiaal**: PLA Zwart
- **Oriëntatie**: Plat (logover omlaag)
- **Vulling**: 15%
- **Support**: Ja (onder LED-slots)
- **Drukspoeling**: 2-3 lagen (eerste 1-2mm)
- **Finish**: Zandstralen aanbevolen

#### Achterkant (Elektronische Behuizing)
**Materiaal**: PLA Zwart of ABS
- **Oriëntatie**: Plat (open zijde omhoog)
- **Vulling**: 20% (meer structuur nodig voor batterijafdichting)
- **Support**: Ja (voor interne compartimenten)
- **Drukspoeling**: 2-3 lagen
- **Post-verwerking**: Waterdichte afdichting aanbrengen

#### Stuur (Bedieningspaneel)
**Materiaal**: PLA Grijs
- **Oriëntatie**: Plat
- **Vulling**: 15%
- **Support**: Ja (voor knoppen)
- **Drukspoeling**: 1-2 lagen
- **Detail-afdruk**: 0.1mm laag aanbevolen voor scharpte

---

## Materiaalkeuzes

### PLA (Poly Lactic Acid) - AANBEVOLEN
**Voordelen:**
- Makkelijk te printen
- Lage vervormingsgraad
- Milieuvriendelijk
- Goede detailkwaliteit

**Nadelen:**
- Lager smeltpunt (~60°C) - niet geschikt voor warme omgevingen
- Matig UV-bestendig

**Toepassingen**: Voorkant, Stuur

### ABS (Acrylonitriel Butadieenstyrene)
**Voordelen:**
- Hoger smeltpunt (~100°C)
- Sterker en flexibeler
- Langer gebruiksduur
- Beter UV-bestendig

**Nadelen:**
- Lastig te printen (warping, krommingen)
- Giftige dampen (goede ventilatie noodzakelijk)

**Toepassingen**: Achterkant (alleen als UV-weerstand essentieel is)

### PETG (Polyethylene Terephthalate Glycol)
**Voordelen:**
- Balans tussen PLA en ABS
- Goede sterkte en flexibiliteit
- UV-bestendig
- Chemische weerstand

**Nadelen:**
- Wat moeilijker dan PLA
- Iets duurder

**Toepassingen**: Alle onderdelen (premium optie)

**Aanbevolen kleurcombinaties:**
- Voorkant: Zwart + Rood (voor signal)
- Achterkant: Zwart
- Stuur: Grijs of Wit (voor contrast)

---

## Slicersoftware

### Aanbevolen Slicer-programma's

#### **Cura** (Aanbevolen - Gratis)
- Download: https://ultimaker.com/software/ultimaker-cura
- Voordelen: Intuïtief, goede ondersteuning, veel presets
- Aanbevolen instellingen aanwezig in `cura_profiles/` (indien beschikbaar)

#### **PrusaSlicer** / **SuperSlicer**
- Download: https://www.prusa3d.com/prusaslicer/
- Voordelen: Geavanceerde preview, betere ondersteuning
- Geschikt voor detail-werk

#### **Simplify3D**
- Commercieel (betaald)
- Voordelen: Professionele kwaliteit, geavanceerde controle
- Voor enthusiasten

---

## Stap-voor-Stap Printproces

### Stap 1: Voorbereiding
1. Zorg voor schoon, vlak drukbed
2. Controleer nozzle op achtergebleven materiaal
3. Calibreer bed-niveau (especially belangrijk!)
4. Laad juiste materiaal (PLA/ABS/PETG)

### Stap 2: Bestand Importeren
1. Open `.stl`-bestand in uw slicer
2. Selecteer juiste printerprofiel
3. Controleer oriëntatie (zie aanbevelingen per onderdeel)
4. Pas vullingsnelheid en support naar behoefte aan

### Stap 3: Support Genereren
- Kies: **Tree Support** (minder materiaalverbruik) OF **Linear Support**
- Verhoog support-dichtheid rond delicate onderdelen
- Minimaliseer support-contactpunten (voor schone afwerking)

### Stap 4: Exporteren & Afdrukken
1. Exporteer naar `.gcode`
2. Kopieer naar printer SD-kaart of upload via netwerk
3. Monitor eerste 10 minuten van de print
4. Controleer periodiek op fouten

### Stap 5: Post-Print Verwerking
1. **Afkoelen**: Laat onderdelen minstens 30 minuten afkoelen
2. **Verwijder Support**: Voorzichtig support afbreken/snijden
3. **Gladmaken**: Schuur oneffenheden glad (120→400 grit)
4. **Wassen**: (Voor ABS) Gecontroleerd wassen met soapy water
5. **Afwerking**: 
   - Optioneel: Zandstralen voor matte afwerking
   - Optioneel: Coating aanbrengen (UV-bescherming)

---

## Troubleshooting

### Veelgestelde Problemen

#### **Warping / Krommingen**
- Oorzaak: Onvoldoende bedtemperatuur of tocht
- Oplossing: 
  - Verhoog bedtemperatuur (+5°C)
  - Plaats windscherm om printer
  - Gebruik buildplate-adhesief (PVA/gluestick)

#### **Support niet Glad**
- Oorzaak: Support-contactpunten te diep
- Oplossing:
  - Verminder support-dichtheid
  - Verhoog Z-offset van support
  - Gebruik "easy removal" option

#### **Slechte Detailkwaliteit**
- Oorzaak: Laag te dik / Snelheid te hoog
- Oplossing:
  - Verklein laagdikte naar 0.1 mm
  - Verlaag printsnelheid naar 40 mm/s
  - Controleer nozzle temp (niet te warm)

#### **Nozzle Blokkeert**
- Oorzaak: Opgedroogd materiaal / Koude nozzle
- Oplossing:
  - Verhit nozzle en druk materiaal door
  - Reinig nozzle voor volgende print
  - Check filament op vochtigheid (vooral PETG/ABS)

---

## Vochtigheidsbeheer

**Belangrijk voor PETG en ABS!**

- Sla filament op in vochtbestendige bakken
- Gebruik silicagel in opslagcontainer
- Print niet met vochtig filament (kwaliteit degradeert)
- Bij twijfel: **Droog filament 2-4 uur** op 50°C in filament-drooger

---

## Kosten Schatting

(Per onderdeel, indicatief)

| Onderdeel | Materiaal | Hoeveelheid | Kostprijs* |
|-----------|-----------|------------|-----------|
| Voorkant | PLA 50g | ~€0.75 | ~€1.00 |
| Achterkant | PLA/PETG 60g | ~€0.90 | ~€1.50 |
| Stuur | PLA 30g | ~€0.45 | ~€0.75 |
| **TOTAAL** | | | **~€3.25** |

*Inclusief support-materiaal en 10% verspilling  
Prijzen kunnen variëren afhankelijk van:
- Filament-merk
- Materiaaltype
- Lokale leveranciers

---

## Waterdichte Afwerking

Voor fietstoepassing is waterdichting essentieel!

### Stappen:
1. **Print onderdelen** volledig en foutloos
2. **Post-processing**: Zandstralen (400+ grit) voor gelijkmatiger oppervlak
3. **Fugen vullen**: Gebruik waterdichte epoxy voor alle naden
4. **Afdichting**: 
   - UV-resistente silicone afdichting langs alle kanten
   - Waterdichte kabeldoorvoeringstukken gebruiken
5. **Testen**: Dip-test of sproeitest voordat op fiets plaatsen

---

## Veiligheidsrichtlijnen

⚠️ **ABS Drukken**
- Zorg voor goede ventilatie (ramen open/afzuigkap)
- Draag masker bij langdurig werken
- Plaats printer in goed geventileerde ruimte

⚠️ **Hete Oppervlakken**
- Nozzle bereikt 200-240°C
- Bed bereikt 60-90°C
- Zorg voor kindveiligheid

⚠️ **Support Verwijderen**
- Voorzichtig werkzaam om onderdeel niet te beschadigen
- Gebruik scherpschoon gereedschap
- Draag handschoenen voor warm werk

---

## Quality Control Checklist

Voor elke print:

- [ ] Drukbed vlak en schoon
- [ ] Nozzle schoon en goed gecalibreerd
- [ ] Juist materiaal geladen
- [ ] Oriëntatie optimaal
- [ ] Ondersteuning noodzakelijk geplaatst
- [ ] Printproces zonder fouten voltooid
- [ ] Onderdeel voltooid afgekoeld
- [ ] Support voorzichtig verwijderd
- [ ] Oppervlak glad geschuurd
- [ ] Waterdichte afdichting aangebracht
- [ ] Dimensies gecontroleerd
- [ ] Gereed voor assemblage

---

## Vervolgstappen

1. **Assemblage**: Zie [hoofd README](../README.md) voor montage-instructies
2. **Waterdichting**: Voer afdichtingsprotocol uit
3. **Testing**: Test alle delen voor waterdichtheid
4. **Integratie**: Bevestig op fietsframe

---

## Contact & Ondersteuning

- Vragen over printsettings? Controleer `cura_profiles/` (indien beschikbaar)
- Problemen met ontwerp? Raadpleeg hoofd Blender-bestand
- Hardware nodig? Zie materiaallijst in hoofd README

---

**Versie**: 1.0  
**Laatst bijgewerkt**: April 2026  
**Status**: Production Ready
