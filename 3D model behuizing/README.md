# BrakeNBlink - 3D Modellering Behuizing

## Projectoverzicht

Dit project bevat de volledige 3D-modellering voor de behuizing van **BrakeNBlink**. De modellen zijn ontworpen in Blender en geoptimaliseerd voor 3D-printing.

In de uitbreiding folder, vind je de bestanden voor de uitbreiding.

**BrakeNBlink** bestaat uit drie geïntegreerde componenten:
- **Voorkant**: Bevat de voorlichten en sensoren
- **Achterkant**: Huisvesting voor de achterlichten en elektronische componenten
- **Stuur**: Bedieningspaneel en controller interface

---

## Gebruikte Gereedschappen

- **Blender** (versie: [4.3.2]) - 3D modellering en design
- **Formaat**: .blend (Blender native format)
- **Export formaat**: .stl (voor 3D-printing)

---

## Mappenstructuur

```
3D model behuizing/
├── BrakeNBlink Behuizing.blend     # Blender hoofdbestand met alle modellen
├── README.md                          # Dit bestand - Projectdocumentatie
├── 3D Print Files/                    # 3D-printbare onderdelen
│   ├── Voorkant/                      # Frontale behuizing
│   ├── Achterkant/                    # Achterkant behuizing
│   └── Stuur/                         # Stuurelement
│   └── README_3D_Print.md         # Printinstructies & instellingen
└── Uitbreiding/                       # Toekomstige uitbreidingen
```

---

## Blender Bestandsstructuur

Het `BrakeNBlink Behuizing.blend1` bestand is georganiseerd als volgt:

### Collecties (Layers)
- **Voorkant** - Frontale behuizing, bevestigingspunten voor sensoren en LED's
- **Achterkant** - Achterkant behuizing, compartimenten voor batterij en PCB
- **Stuur** - Stuurelement met knoppen en display houder
- **Referentie** - Technische referentiemodellen (fietsframe, onderdelen)
- **Materialen** - Materiaal-bibliotheek voor rendering

### Materialinstellingen
- **Zwart ABS/PLA**: Structurele onderdelen
- **Doorzichtig PMMA/Polycarbonaat**: Lenscomponenten
- **Rood PETG**: Signaleringselementen

---

## 3D-Printbare Onderdelen

Alle printbare onderdelen bevinden zich in de `3D Print Files/` map. Elk onderdeel is afzonderlijk beschikbaar als `.stl`-bestand:

| Onderdeel | Locatie | Functie | Materiaal |
|-----------|---------|---------|-----------|
| **Voorkant** | `3D Print Files/Voorkant/` | Huisvesting voorlichten en sensoren | Zwart ABS/PLA |
| **Achterkant** | `3D Print Files/Achterkant/` | Huisvesting achterlichten en elektronika | Zwart ABS/PLA |
| **Stuur** | `3D Print Files/Stuur/` | Bedieningspaneel en controller | Grijs/Zwart PLA |

Raadpleeg **`README_3D_Print.md`** in de 3D Print Files map voor gedetailleerde printinstellingen, slicersoftware en materiaalkeuzes.

---

## Montage & Assemblage

### Voorbereiding
1. Zorg dat alle geprinte onderdelen volledig zijn uitgekookt en afgekoeld
2. Verwijder support-materiaal zorgvuldig
3. Glad schuren met fijne korrelgroei (400+ grit) voor betere pasvormen
4. Controleer alle bevestigingsgaten op correcte afmetingen

### Montagesequentie

#### Stap 1: Achterkant Assemblage (Basis)
- Plaatsen PCB-module in de centrale compartiment
- Batterijhouder bevestigen (zie bevestigingspunten)
- Waterdichte afdichting aanbrengen rond elektronische ingang

#### Stap 2: Voorkant Assemblage
- LED-modules in de voorziene slots plaatsen
- Sensoren bevestigen aan montagebeugels
- Reflectoren/lenzen inzetten en vastklemmen

#### Stap 3: Stuurelement Bevestiging
- Stuurmodule aan voorkant verbinden (M3 bout, 2x)
- Kabelkanaal voor bedradingsintegratie gebruiken
- Controller naar achterkant doorvoeren (waterdicht)

#### Stap 4: Finale Montage op Fiets
- Gehele assemblage op fietsframe bevestigen
- Controleer op deformaties of spanning punten
- Test alle elektrische verbindingen voordat u de voeding inschakelt

### Bevestigingspunten
- **M3 bouten**: Standaard bevestiging tussen onderdelen
- **M4 bouten**: Fietsframe bevestiging
- **Waterdichte kabelgaten**: Voor USB, sensoren en voeding

---

## Dimensies & Toleranties

- **Voorkant**: ~80mm (B) × 45mm (H) × 60mm (D)
- **Achterkant**: ~75mm (B) × 50mm (H) × 65mm (D)
- **Stuur**: ~120mm (B) × 35mm (H) × 40mm (D)

**Tolerantie voor 3D-printing**: ±0.5mm voor standaardonderdelen

---

## Aanpassingen & Customization

### In Blender aanpassen:
1. Open `BrakeNBlink Behuizing.blend1` in Blender
2. Selecteer de collectie die u wilt wijzigen
3. Maak de gewenste wijzigingen
4. Exporteer naar `.stl` via: **File > Export > Stereolithography (.stl)**
5. Plaats het bijgewerkte `.stl`-bestand in de bijbehorende 3D Print Files-map

---

## Toekomstige Uitbreidingen

De `Uitbreiding/` map is voorbehouden voor:
- Alternatieve designvarianten
- Geavanceerde onderdelen (bijv. draadloos oplaadmodule)
- Accessoires (bevestigingsclips, diffusers)
- Experimentele prototypes

---

## Materialen & Resources

### Aanbevolen 3D-printmaterialen
- **ABS** of **PLA**: Structurele sterkte en detail
- **PETG**: Verbeterde duurzaamheid en weerstand
- **TPU**: Scharnier- en rubberdichting

### Benodigde hardware
- M3 en M4 RVS bouten en moeren
- Waterdichte kabeldoorvoeringstukken
- Siliconen afdichtingsmiddel
- Siliconenveertjes (voor knopvering)

---

## Ondersteuning & Opmerkingen

- Voor vragen over de modellering: raadpleeg het Blender-bestand
- Voor printinstellingen: zie `3D Print Files/README_3D_Print.md`
- Zorg voor goede ventilatie bij het drukken van ABS
- Test de pasvorming van onderdelen vooraf op schaal (1:1 dimensies)

---

## Versiegeschiedenis

| Versie | Datum | Wijzigingen |
|--------|-------|-------------|
| 1.0 | [DD-MM-YYYY] | Initiële release - Alle onderdelen |
| | | |

---

**Laatste update**: April 2026  
**Project**: BrakeNBlink - 3D Model Behuizing  
**Status**: In Development
