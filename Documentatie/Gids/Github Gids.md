Alle commands worden in de windows terminal uitgevoerd, in de folder waarin je github repo staat.

## **Basis**
onze repository clonen op een folder lokaal:
```bash
git clone git@github.com:vives-project-xp/BrakeNBlink.git
```
### **Commit & Push**
Voodat je pushed, altijd eerst de content pullen:
```bash
git pull
```

Files toevoegen, commiten en pushen:
```bash
git add .
git commit -m "een bericht met de veranderingen dat je hebt gemaakt"
git push 
```
als **git push** niet werkt, probeer:
```bash
git push origin main
```

### **Check je status (eventuele aanpassingen dat er zijn gemaakt, puur informatief):**
```bash
git status
```

### **Merge conflicten**
een merge conflict is wanneer twee personen een verandering hebben gemaakt aan dezelfde lijnen van een file en git weet niet welke versie te houden en welke weg te doen. 

### **Om het te fixen, pull eerst**
```bash
git pull
```
### **Open de files waar er een conflict is. daar zal je jouw veranderingen zien, en de nieuwe veranderingen.**
```bash
<<<<<<<<< HEAD
your changes
=========
incoming changes
```
### **Kies wat je wilt behouden en wat je weg wilt doen en mark als solved, en dan opnieuw:**
```bash
git add .
git commit -m "een bericht met de veranderingen dat je hebt gemaakt"
git push 
```


