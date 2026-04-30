# BrakeNBlink - 3D Modellering Behuizing

## Projectoverzicht

Dit project bevat de volledige 3D-modellering voor de behuizing van **BrakeNBlink**. De modellen zijn ontworpen in Blender en geoptimaliseerd voor 3D-printing. In de uitbreiding folder, vind je de bestanden voor de uitbreiding.

**BrakeNBlink** bestaat uit drie delen:
- **Voorkant**: bevat de elektronika en richtingaanwijzers
- **Achterkant**: ook elektronica met richtingaanwijzers en achterlicht
- **Stuur**: knoppen om richtingaanwijzers aan te zetten met een korte richtingaanwijzer ledstrip.

---

## 3d modelling software

- **Blender** 4.3.2 - 3D modellering en design
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
- afgemeten componenten: wordt gebruikt als referentie om de behuizing te maken.
- Assembly: montage van alles op de fiets, puur visueel
- Moddeling: hierin worden de behuizing aangepast en verbeterd
- Om te 3D printen: bestanden klaar voor export naar .stl
<img width="435" height="500" alt="image" src="https://github.com/user-attachments/assets/a0795bcf-db85-4f4d-aa73-a5ac589b93c4" />


---

## 3D-Printbare Onderdelen

Alle printbare onderdelen bevinden zich in de `3D Print Files/` map. Elk onderdeel is afzonderlijk beschikbaar als `.stl`-bestand:

| Onderdeel   | Locatie           | Materiaal         |
|-------------|-------------------|-------------------|
| **Voorkant** | `3D Print Files/Voorkant/` | ABS/PETG/ASA |
| **Achterkant** | `3D Print Files/Achterkant/` | ABS/PETG/ASA |
| **Stuur** | `3D Print Files/Stuur/` | ABS/PETG/ASA |

Raadpleeg **`README_3D_Print.md`** in de 3D Print Files map voor gedetailleerde printinstellingen, slicersoftware en materiaalkeuzes.

---

## Montage


#### Achterkant Assemblage (Basis)


#### Voorkant Assemblage


#### Stap Stuurelement Bevestiging


---

### In Blender aanpassen:
1. Open `BrakeNBlink Behuizing.blend1` in Blender
2. Selecteer de collectie die u wilt wijzigen
3. Maak de gewenste wijzigingen
4. Exporteer naar `.stl` via: **File > Export > Stereolithography (.stl)**
5. Plaats het bijgewerkte `.stl`-bestand in de bijbehorende 3D Print Files-map

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

