# BrakeNBlink - 3D Modellering Behuizing

## Projectoverzicht

Dit project bevat de volledige 3D-modellering voor de behuizing van **BrakeNBlink**. De modellen zijn ontworpen in Blender en geoptimaliseerd voor 3D-printing. In de uitbreiding folder, vind je de bestanden voor de uitbreiding.

**BrakeNBlink** bestaat uit drie delen + uitbreiding:
- **Voorkant**: bevat de elektronika en richtingaanwijzers
- **Achterkant**: ook elektronica met richtingaanwijzers en achterlicht
- **Stuur**: knoppen om richtingaanwijzers aan te zetten met een korte richtingaanwijzer ledstrip.
- - **Uitbreiding**: extra zichbaarheid aan het wiel

---

## Gebruikte modelling software

- **Blender** 4.3.2 - 3D modellering en design
- **Formaat**: .blend & .blend1 (Blender native format)
- **Export formaat**: .stl voor 3D-printing

---

## Mappenstructuur

```
3D model behuizing/
├── BrakeNBlink Behuizing.blend     # Blender hoofdbestand
├── README.md                          # Dit bestand
├── 3D Print Files/                    
│   ├── Voorkant/                      # Behuizing voorkaant
│   ├── Achterkant/                    # Behuizing achterkant
│   └── Stuur/                         # Behuizing op het stuur
│   └── README_3D_Print.md         # Print instellingen
└── Uitbreiding/                       # Deel aan het wiel
```

---

## Blender Bestandsstructuur
- afgemeten componenten: wordt gebruikt als referentie om de behuizing te maken.
- Assembly: montage van alles op de fiets, puur visueel
- Moddeling: hierin worden de behuizing aangepast en verbeterd
- Om te 3D printen: bestanden klaar voor export naar .stl
<img width="435" height="500" alt="image" src="https://github.com/user-attachments/assets/a0795bcf-db85-4f4d-aa73-a5ac589b93c4" />


---

## 3D-Printbare Onderdelen

Alle printbare onderdelen bevinden zich in de `3D Print Files/` map. Elk onderdeel is afzonderlijk beschikbaar als `.stl`-bestand:

---

## Montage

---

### bestanden in Blender aanpassen:
1. Open `BrakeNBlink Behuizing.blend` in Blender
2. Selecteer de collectie die je wilt wijzigen
3. Maak de gewenste wijzigingen
4. Exporteer naar `.stl` via: **File > Export > .stl**

---

### Benodigde hardware voor installatie
- M4 bouten en moeren

---

## Ondersteuning & Opmerkingen

- Voor vragen over de modellering: raadpleeg het Blender-bestand
- Voor printinstellingen: zie `3D Print Files/README_3D_Print.md`

