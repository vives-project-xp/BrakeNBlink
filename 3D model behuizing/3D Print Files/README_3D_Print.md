# 3D Print Files - BrakeNBlink Behuizing

Printinstructies de hoofdonderdelen van BrakeNBlink.
Alles is geprint in PLA, behalve "TPU_stuur_knop_cover.stl"
ALles is geprint zonder supports, behalve "stuur_behuizing_links.stl" en "stuur_behuizing_rechts.stl"

---

## Mappenstructuur

```
3D Print Files/
├── README_3D_Print.md        # Dit bestand
├── Voorkant/                 # Behuizing voorkant
│   ├── voorkant_behuizing.stl
│   ├── voorkant_behuizing_deksel.stl
│   ├── voorkant_key.stl
│   ├── voorkant_led_links.stl
│   ├── voorkant_led_rechts.stl
├── Achterkant/               # Behuizing achterkant
│   ├── achterkant_behuizing.stl
│   ├── achterkant_behuizing_deksel.stl
│   ├── achterkant_led_strip_links.stl
│   ├── achterkant_led_strip_rechts.stl
└── Stuur/                    # Stuur
    ├── stuur_behuizing_links.stl     # Heeft support nodig om te printen
    ├── stuur_behuizing_rechts.stl    # Heeft support nodig om te printen
    ├── stuur_mount.stl
    ├── stuur_led_cover.stl
    ├── TPU_stuur_knop_cover.stl      # In TPU geprint

```
---

## Overzicht Onderdelen

Met standaard Bambulab instellingen, zijn dit de geschatte gewichten en printtijden voor elk onderdeel:
(0.20mm hoogte, 2 walls, 200-300mm/s, 15% grid vulling, geen supports)
| Onderdeel | Bestand | Hoeveel | Gewicht (g) | Print tijd |
|-----------|---------|---------|------------|-----------|
| Achterkant | `achterkant_behuizing.stl` | 1x | ~74g | 1h56m |
| Achterkant | `achterkant_behuizing_deksel.stl` | 1x | ~64g | 1h46m |
| Achterkant | `achterkant_led_strip_links.stl` | 1x | ~12.3g | 0h27m |
| Achterkant | `achterkant_led_strip_rechts.stl` | 1x | ~12.3g | 0h27m |
| Stuur | `stuur_behuizing_links.stl` | 1x | ~14.4g | 0h37m |
| Stuur | `stuur_behuizing_rechts.stl` | 1x | ~14.4g | 0h37m |
| Stuur | `stuur_led_cover.stl` | 1x | ~1.8g | 0h15m |
| Stuur | `stuur_mount.stl` | 1x | ~4g | 0h25m |
| Stuur | `stuur_mount.stl` | 1x | ~1.4g | 0h13m |
| Voorkant | `voorkant_behuizing.stl` | 1x | ~90g | 2h39m |
| Voorkant | `voorkant_behuizing_deksel.stl` | 1x | ~35.4g | 1h0m |
| Voorkant | `voorkant_key.stl` | 1x | ~0.7g | 0h12m |
| Voorkant | `voorkant_led_links.stl` | 1x | ~23.6g | 0h44m |
| Voorkant | `voorkant_led_rechts.stl` | 1x | ~23.6g | 0h44m |

---

## Aanbevolen Printinstellingen

### Algemene Instellingen
```
Laag hoogte:          0.2 mm (standaard)
Vulling:             15-20% (grid patroon)
Snelheid:            (standaard)
Bedtemperatuur:      45°C (PLA) / 60°C (ABS) / 70°C (PETG) / 50°C (TPU)
Nozzle Temperatuur:  220°C (PLA) / 230°C (ABS) / 245°C (PETG) / 210°C (TPU)

```
### Support
```
Type:           tree(auto)
Style:          standaard
Treshhold angle:    30°
Alleen op build plate :    aan
Alleen critische delen:    aan
Verwijder kleine overhang:    aan
```
---

## Gebruikte slicersoftware

#### **Bambu Studio**
- Download: https://bambulab.com/en/download/studio
- Voordelen: Van Bambu Lab, makkelijk voor hun printers

