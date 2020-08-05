# Projekt cislo 2 - Spajany zoznam struktur

## Zaznam ma tieto casti:

- kategoria ponuky (max 50 znakov)
- miesto ponuky (max 50 znakov)
- ulica (max 100 znakov)
- rozloha v m2 (cele cislo)
- cena (cele cislo)
- popis (max 200 znakov)

## Ukazka ohsahu suboru reality.txt:

```
&
stvorizbovy byt
Bratislava
Medena 32
104
475000
byt po cistocnej rekonstrukcii, samostatne vykurovanie
```
## Zoznam funkcii:

| NAZOV | SKRATKA |
| --- | --- |
| nacitanie zo suboru | n |
| vypisanie vsetkych zaznamov | v |
| pridanie noveho zaznamu | p |
| zmazanie zaznamov | z |
| hladanie podla ceny | h |
| aktualizacia zaznamu | a |
| ukoncenie programu | k |
| usporiadanie zaznamov | u |
| otocenie poradia zaznamov | o |


## Podrobny popis funkcii:

### n
Je príkaz na nacítanie záznamov o realitách **zo súboru 
reality.txt** do spájaného zoznamu štruktúr.
Ak zoznam predtým existoval, je potrebné uvolnit pamät. 
Ak nie je možné súbor otvorit, program vypíše správu 
Zaznamy neboli nacitane ukoncenú znakom konca riadku. 
Ak sa podarilo záznamy nacítat, vypíše správu Nacitalo 
sa n zaznamov ukoncenú znakom konca riadku, pricom n znamená 
pocet nacítaných záznamov.

### v
Je príkaz na výpis celého spájaného zoznamu záznamov. 
Pred každým záznamom je uvedené císlo záznamu (poradie od 
zaciatku zoznamu, zacínajúce císlom 1) nasledované bodkou a
znakom konca riadku. Potom nasleduje výpis záznamu, pricom 
názov položky (bez diakritiky) je nasledovaný dvojbodkou, 
medzerou, hodnotou položky a znakom konca riadku. Ak zoznam 
neobsahuje záznamy, pri tejto volbe program negeneruje
žiaden výstup. 

### p
Je príkaz na pridanie záznamu o realitnej ponuke 
do dynamického zoznamu. **Príkaz je v dalšom riadku 
nasledovaný celým císlom p > 0 vyjadrujúcim pozíciu 
(pocítanú od 1), na ktorú sa má záznam pridat** (záznam
z pozície p sa posunie na pozíciu p+1). Potom nasleduje
dalších 6 riadkov, každý ukoncený znakom konca riadku
a obsahujúcim položky záznamu v poradí v akom sú aj
v súbore reality.txt. Ak pozícia p v zozname neexistuje,
záznam sa pridá na koniec zoznamu. Pri tejto volbe 
program negeneruje žiaden výstup. 

### z
Je príkaz na **zmazanie záznamov o realitách podla miesta ponuky**. 
Riadok s príkazom z je nasledovaný riadkom obsahujúcim miesto 
ponuky a ukoncený znakom konca riadku. Program vymaže všetky 
záznamy obsahujúce zadané miesto ponuky, pricom ignoruje 
rozdiely vo velkých a malých písmenách. Ak používatel zadá 
miesto ponuky napr. tiS a zoznam obsahuje záznamy s miestom 
ponuky Bratislava alebo TISOVEC, tento príkaz uvedené záznamy 
vymaže. Pri tomto príkaze program vypíše správu Vymazalo sa 
n zaznamov, kde n je pocet vymazaných záznamov. Správa je 
ukoncená znakom konca riadku.  

### h
Umožní používatelovi vyhladat a vypísat všetky položky 
záznamu podla ceny ponuky.  Riadok s príkazom h **je 
v dalšom riadku nasledovaný celým císlom c vyjadrujúcim 
cenu** ponuky. Po zadaní tohto príkazu program vypíše všetky 
ponuky, ktorých cena je menšia alebo rovná zadanej hodnote c.
Formát výpisu je rovnaký ako pri príkaze v aj s císlami 
záznamov, pricom vypísané záznamy sú císlované od 1 po n, 
kde n je pocet vypísaných záznamov. Záznamy sú vypísané 
v poradí v akom sa vyskytujú v spájanom zozname. Ak záznam 
s ponukou, ktorej cena je menšia, alebo rovná c neexistuje, 
program vypíše správu V ponuke su len reality s vyssou cenou 
Správa je ukoncená znakom konca riadku. 

### a
Je príkaz na aktualizáciu (zmenu) záznamu podla miesta ponuky. 
Riadok s príkazom a **je nasledovaný riadkom obsahujúcim miesto 
ponuky** a ukoncený znakom konca riadku. Potom nasleduje 6 riadkov 
obsahujúcich aktualizované hodnoty záznamu, každý ukoncený 
znakom konca riadku. Vždy je potrebné zadat všetky položky 
záznamu. Program aktualizuje všetky záznamy obsahujúce zadané 
miesto ponuky, pricom ignoruje rozdiely vo velkých a malých 
písmenách (rovnako ako pri príkaze z). Pri tomto príkaze program
vypíše správu Aktualizovalo sa n zaznamov, kde n je pocet 
zmenených záznamov. Správa je ukoncená znakom konca riadku. 

### k
Je príkaz na ukoncenie programu. Ak spájaný zoznam existoval, 
treba uvolnit pamät.

### u
Je príkaz na usporiadanie záznamov o realitách v spájanom 
zozname štruktúr podla miesta ponuky a ceny. Po zadaní tohto 
príkazu program usporiada záznamy v spájanom zozname 
lexikograficky podla miesta ponuky. V prípade ak v zozname 
existujú viaceré ponuky, ktorých miesto ponuky je zhodné, 
budú tieto záznamy ešte usporiadané aj podla ich ceny vzostupne 
(od najnižšej po najvyššiu cenu). Pri tejto volbe program vypíše 
správu Zoznam nie je mozne usporiadat v prípade ak zoznam je 
prázdny, alebo správu Zaznamy boli usporiadane. Správnost 
usporiadania si overte výpisom upraveného zoznamu. 

### o
Obrati poradie zaznamov v zozname a vypise otocený zoznam.
Ak neexistuje ziaden zaznam nevykona nic.
