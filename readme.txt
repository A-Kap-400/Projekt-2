Projekt cislo 2 - Spajany zoznam struktur

--------------------------------------------------------------

Zaznam ma tieto casti:

	# kategoria ponuky (max 50 znakov)
	# miesto ponuky (max 50 znakov)
	# ulica (max 100 znakov)
	# rozloha v m2 (cele cislo)
	# cena (cele cislo)
	# popis (max 200 znakov)

--------------------------------------------------------------

Ukazka ohsahu suboru reality.txt:

&
stvorizbovy byt
Bratislava
Medena 32
104
475000
byt po cistocnej rekonstrukcii, samostatne vykurovanie

--------------------------------------------------------------

Popis funkcii:

	n
Je pr�kaz na nac�tanie z�znamov o realit�ch zo s�boru 
reality.txt do sp�jan�ho zoznamu �trukt�r.
Ak zoznam predt�m existoval, je potrebn� uvolnit pam�t. 
Ak nie je mo�n� s�bor otvorit, program vyp�e spr�vu 
Zaznamy neboli nacitane ukoncen� znakom konca riadku. 
Ak sa podarilo z�znamy nac�tat, vyp�e spr�vu Nacitalo 
sa n zaznamov ukoncen� znakom konca riadku, pricom n znamen� 
pocet nac�tan�ch z�znamov.

	v
Je pr�kaz na v�pis cel�ho sp�jan�ho zoznamu z�znamov. 
Pred ka�d�m z�znamom je uveden� c�slo z�znamu (poradie od 
zaciatku zoznamu, zac�naj�ce c�slom 1) nasledovan� bodkou a
znakom konca riadku. Potom nasleduje v�pis z�znamu, pricom 
n�zov polo�ky (bez diakritiky) je nasledovan� dvojbodkou, 
medzerou, hodnotou polo�ky a znakom konca riadku. Ak zoznam 
neobsahuje z�znamy, pri tejto volbe program negeneruje
�iaden v�stup. 

	p
Je pr�kaz na pridanie z�znamu o realitnej ponuke 
do dynamick�ho zoznamu. Pr�kaz je v dal�om riadku 
nasledovan� cel�m c�slom p > 0 vyjadruj�cim poz�ciu 
(poc�tan� od 1), na ktor� sa m� z�znam pridat (z�znam
z poz�cie p sa posunie na poz�ciu p+1). Potom nasleduje
dal��ch 6 riadkov, ka�d� ukoncen� znakom konca riadku
a obsahuj�cim polo�ky z�znamu v porad� v akom s� aj
v s�bore reality.txt. Ak poz�cia p v zozname neexistuje,
z�znam sa prid� na koniec zoznamu. Pri tejto volbe 
program negeneruje �iaden v�stup. 

	z
Je pr�kaz na zmazanie z�znamov o realit�ch podla miesta ponuky. 
Riadok s pr�kazom z je nasledovan� riadkom obsahuj�cim miesto 
ponuky a ukoncen� znakom konca riadku. Program vyma�e v�etky 
z�znamy obsahuj�ce zadan� miesto ponuky, pricom ignoruje 
rozdiely vo velk�ch a mal�ch p�smen�ch. Ak pou��vatel zad� 
miesto ponuky napr. tiS a zoznam obsahuje z�znamy s miestom 
ponuky Bratislava alebo TISOVEC, tento pr�kaz uveden� z�znamy 
vyma�e. Pri tomto pr�kaze program vyp�e spr�vu Vymazalo sa 
n zaznamov, kde n je pocet vymazan�ch z�znamov. Spr�va je 
ukoncen� znakom konca riadku.  
 
	h
Umo�n� pou��vatelovi vyhladat a vyp�sat v�etky polo�ky 
z�znamu podla ceny ponuky.  Riadok s pr�kazom h je 
v dal�om riadku nasledovan� cel�m c�slom c vyjadruj�cim 
cenu ponuky. Po zadan� tohto pr�kazu program vyp�e v�etky 
ponuky, ktor�ch cena je men�ia alebo rovn� zadanej hodnote c.
Form�t v�pisu je rovnak� ako pri pr�kaze v aj s c�slami 
z�znamov, pricom vyp�san� z�znamy s� c�slovan� od 1 po n, 
kde n je pocet vyp�san�ch z�znamov. Z�znamy s� vyp�san� 
v porad� v akom sa vyskytuj� v sp�janom zozname. Ak z�znam 
s ponukou, ktorej cena je men�ia, alebo rovn� c neexistuje, 
program vyp�e spr�vu V ponuke su len reality s vyssou cenou 
Spr�va je ukoncen� znakom konca riadku. 
 
	a
Je pr�kaz na aktualiz�ciu (zmenu) z�znamu podla miesta ponuky. 
Riadok s pr�kazom a je nasledovan� riadkom obsahuj�cim miesto 
ponuky a ukoncen� znakom konca riadku. Potom nasleduje 6 riadkov 
obsahuj�cich aktualizovan� hodnoty z�znamu, ka�d� ukoncen� 
znakom konca riadku. V�dy je potrebn� zadat v�etky polo�ky 
z�znamu. Program aktualizuje v�etky z�znamy obsahuj�ce zadan� 
miesto ponuky, pricom ignoruje rozdiely vo velk�ch a mal�ch 
p�smen�ch (rovnako ako pri pr�kaze z). Pri tomto pr�kaze program
vyp�e spr�vu Aktualizovalo sa n zaznamov, kde n je pocet 
zmenen�ch z�znamov. Spr�va je ukoncen� znakom konca riadku. 
 
	k
Je pr�kaz na ukoncenie programu. Ak sp�jan� zoznam existoval, 
treba uvolnit pam�t.

	u
Je pr�kaz na usporiadanie z�znamov o realit�ch v sp�janom 
zozname �trukt�r podla miesta ponuky a ceny. Po zadan� tohto 
pr�kazu program usporiada z�znamy v sp�janom zozname 
lexikograficky podla miesta ponuky. V pr�pade ak v zozname 
existuj� viacer� ponuky, ktor�ch miesto ponuky je zhodn�, 
bud� tieto z�znamy e�te usporiadan� aj podla ich ceny vzostupne 
(od najni��ej po najvy��iu cenu). Pri tejto volbe program vyp�e 
spr�vu Zoznam nie je mozne usporiadat v pr�pade ak zoznam je 
pr�zdny, alebo spr�vu Zaznamy boli usporiadane. Spr�vnost 
usporiadania si overte v�pisom upraven�ho zoznamu. 

	o
Obrati poradie zaznamov v zozname a vypise otocen� zoznam.
Ak neexistuje ziaden zaznam nevykona nic.


