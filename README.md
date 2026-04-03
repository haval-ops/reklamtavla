# reklamtavla 


## Beskrivning

Detta projekt simulerar en reklamtavla som visar olika reklammeddelanden i tur och ordning. Systemet är byggt i C++ och är tänkt att köras på en inbyggd enhet (t.ex. ESP32), men simuleras i terminalen.

Reklamtavlan visar ett meddelande i taget i 20 sekunder. Efter varje visning väljs nästa reklam slumpmässigt baserat på hur mycket kunden har betalat.

Systemet säkerställer också att samma kund aldrig visas två gånger i rad.

---

## Funktioner

- Slumpmässigt val av reklam baserat på vikt (betalning)
- Ingen kund visas två gånger i rad
- Varje reklam visas i 20 sekunder
- Flera visningslägen:
  - Static text
  - Blinkande text
  - Scrollande text
- Specialregel för Svarte Petter:
  - Jämna minuter: scrollande text
  - Ojämna minuter: vanlig text

---

## Kunder och regler

### Hederlige Harrys Bilar (5000)
- 3 olika meddelanden
- Slumpas vid varje visning
- Blandning av scroll, static och blink

### Farmor Ankas Pajer AB (3000)
- 2 meddelanden
- Slumpas
- Scroll + static

### Svarte Petters Svartbyggen (1500)
- 2 meddelanden
- Beroende på minut:
  - Jämn minut → scroll
  - Ojämn minut → static

### Långbens detektivbyrå (4000)
- 2 meddelanden
- Slumpas
- Endast static text

### IOT:s Reklambyrå (1000)
- 1 meddelande
- Static text

---

## Projektstruktur
src/
main.cpp // Huvudprogram
ads.cpp // Logik för kunder och reklam
ads.h
display.cpp // Visningslogik (terminal)
display.h


---

## Hur programmet fungerar

1. Programmet startar och initierar slumpgeneratorn
2. En kund väljs baserat på vikt (betalning)
3. Ett meddelande väljs enligt kundens regler
4. Meddelandet visas i 20 sekunder
5. Nästa kund väljs (inte samma som tidigare)
6. Processen upprepas

---

## Kompilering och körning

Kompilera:
g++ src/main.cpp src/ads.cpp src/display.cpp -o reklam


Kör:
./reklam


---

## Hårdvara (tänkt implementation)

Projektet är designat för:

- ESP32
- LCD-display (16x2)
- Strömförsörjning

I denna version simuleras displayen i terminalen.

---

## Möjliga förbättringar

- Göra systemet datadrivet (t.ex. läsa reklam från fil eller server)
- Koppla till riktig LCD-display
- Hämta verklig tid via internet istället för intern timer
- Webbaserat gränssnitt för att hantera reklam
- Logga statistik över visningar

---

## Kommentar

Projektet är byggt för att uppfylla kraven för betyget G i kursen "Programmering av inbyggda system". Fokus har varit på funktionalitet, tydlig struktur och korrekt logik.

## Projektstruktur
