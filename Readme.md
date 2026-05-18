# 4 laboratonis darbas - pigiausio skrydžio maršruto paieška

Programa nuskaito lėktuvų skrydžių sąrašą ir randa pigiausią maršrutą tarp dviejų nurodytų miestų. Jei toks maršrutas neegzistuoja — apie tai pranešama.
Grafo realizacija paremta **kaimynystės matrica**. Trumpiausio kelio paieškai naudojamas **Floyd-Warshall** algoritmas.

## Projekto struktūra

`main.c`       – Pagrindinis modulis: įvesties nuskaitymas, rezultatų išvedimas
`graph.c`      – Grafo logika: inicializacija, skrydžių pridėjimas, maršruto paieška
`graph.h`      – Struktūrų ir funkcijų aprašai
`Makefile`     – Kompiliavimo taisyklės
`Go.cmd`       – Automatinio paleidimo scenarijus (Windows)

## Duomenų struktūros

### `City` – miestas
```c
typedef struct {
    char name[MAX_NAME_LEN];  // Miesto pavadinimas (maks. 50 simbolių)
} City;
```
 
### `Graph` – grafas (kaimynystės matrica)
```c
typedef struct {
    City cities[MAX_CITIES];          // Miestų masyvas
    int  city_count;                  // Miestų skaičius
    int  adj_matrix[MAX_CITIES][MAX_CITIES];  // Kaimynystės matrica (kaina arba NO_FLIGHT)
} Graph;
```
 
Kaimynystės matricoje `adj_matrix[i][j]` saugo tiesioginę skrydžio kainą iš miesto `i` į miestą `j`. Jei tiesioginio skrydžio nėra, reikšmė yra `NO_FLIGHT`.
 
### `FlightResult` – paieškos rezultatas
```c
typedef struct {
    int found;               // 1 – maršrutas rastas, 0 – nerastas
    int total_cost;          // Bendroji minimali kaina
    int path[MAX_CITIES];    // Miestų indeksų seka maršrute
    int path_len;            // Miestų skaičius maršrute
} FlightResult;
```

## Algoritmas

Maršruto paieškai naudojamas **Floyd-Warshall** algoritmas.

**Sudėtingumas:** O(n³), kur n – miestų skaičius.
 
**Veikimo principas:**
1. Pradinė atstumo matrica nukopijuojama iš kaimynystės matricos.
2. Kiekvienam tarpiniam miestui `k` tikrinama, ar kelias per `k` yra pigesnis nei tiesioginis.
3. Kartu pildoma `next_node` matrica, leidžianti atkurti konkretų maršrutą.
```c
for(int k = 0; k < g->city_count; k++)
    for(int i = 0; i < g->city_count; i++)
        for(int j = 0; j < g->city_count; j++)
            if(dist[i][k] + dist[k][j] < dist[i][j]) {
                dist[i][j] = dist[i][k] + dist[k][j];
                next_node[i][j] = next_node[i][k];
            }
```

## Įvesties formatas (`.cfg` failas)
 
```
<skrydžių_skaičius>
<miestas1> <miestas2> <kaina>
...
<pradinis_miestas>
<galinis_miestas>
```
 
**Pavyzdys (`flights.cfg`):**
```
6
Vilnius  Ryga       80
Vilnius  Oslas      60
Ryga     Talinas    50
Oslas    Berlynas   90
Ryga     Berlynas  120
Talinas  Berlynas   70
Vilnius
Berlynas
```

## Kompiliavimas
 
Reikalingas **GCC** kompiliatorius su C99 standarto palaikymu.
 
```bash
make
```
 
Arba rankiniu būdu:
```bash
gcc -c -std=c99 graph.c
gcc -std=c99 -Wall -o Flights.exe main.c graph.o
```

## Paleidimas
 
```bash
Flights.exe <kelias_iki_cfg_failo>
```
 
Jei failo pavadinimas nenurodytas, programa automatiškai ieško failo su tuo pačiu pavadinimu kaip vykdomasis failas, bet `.cfg` plėtiniu (pvz., `Flights.cfg`).
 
```bash
# Su nurodytu failu:
Flights.exe flights.cfg
 
# Be argumento (naudos Flights.cfg):
Flights.exe
```
 
## Išvesties pavyzdžiai
 
### Maršrutas rastas
 
```
Kaimynystes matrica (6 miestų):
 
                    Vilnius       Ryga    Talinas    Oslas     Berlynas
Vilnius                   0         80          -        60         -
Ryga                      -          0         50          -       120
Talinas                   -          -          0          -        70
Oslas                     -          -          -          0        90
Berlynas                  -          -          -          -         0
 
Maršrutas: Vilnius -> Berlynas
Pigiausia kaina: 150
Kelias: Vilnius -> Oslas -> Berlynas
```
 
### Maršrutas nerastas
 
```
Marsrutas: Vilnius -> Berlynas
Tokio marsruto nera.
```
 
---
 
## Testavimo scenarijai (`Go.cmd`)
 
`Go.cmd` automatiškai sukompiliuoja programą ir paleidžia tris testus:
 
| Failas        | Aprašymas                                              | Rezultatas        |
|---------------|--------------------------------------------------------|-------------------|
| `flights.cfg` | 6 skrydžiai, Vilnius → Berlynas per Oslą               | `result1.txt`     |
| `Flights.cfg` | 5 skrydžiai, Kaunas → Berlynas per Taliną              | `result2.txt`     |
| `nopath.cfg`  | 2 skrydžiai, Vilnius → Berlynas (jungtys neegzistuoja) | `result3.txt`     |
 
