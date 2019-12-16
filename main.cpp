#pragma warning (disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define N 55

typedef struct zaznam
{
    char kategoria[N];
    char miesto[N];
    char ulica[2 * N];
    int rozloha;
    int cena;
    char popis[4 * N];
    struct zaznam* dalsi;
} ZAZNAM;

ZAZNAM* n(ZAZNAM* stary_prvy, int* pocet_zaznamov)
{
    FILE* subor = NULL;
    char znak_zo_suboru;
    ZAZNAM* prvy = NULL;
    ZAZNAM* aktualny = NULL;
    int prvy_alokovany = 0;		// flag, ktory urcuje ci je prvy zaznam alokovany

    // uvolnenie pamati stareho zoznamu:
    if (stary_prvy != NULL) {
        aktualny = stary_prvy->dalsi;
        while (aktualny != NULL) {
            free(stary_prvy);
            stary_prvy = aktualny;
            aktualny = aktualny->dalsi;
        }
        free(stary_prvy);
        aktualny = NULL;
    }
    *pocet_zaznamov = 0;

    if ((subor = fopen("reality.txt", "r")) == NULL) {
        printf("Zaznamy neboli nacitane\n");
        return NULL;
    }

    // nacitanie zaznamov do linearneho zoznamu:
    while ((znak_zo_suboru = fgetc(subor)) != EOF) {
        if (znak_zo_suboru == '&') {
            getc(subor);	// nacita enter za znakom '&'
            if (prvy_alokovany == 0) {
                prvy = (ZAZNAM*)malloc(sizeof(ZAZNAM));
                aktualny = prvy;
                prvy_alokovany = 1;
            }
            else {
                aktualny->dalsi = (ZAZNAM*)malloc(sizeof(ZAZNAM));
                aktualny = aktualny->dalsi;
            }
            // fscanf() nacita string s medzerami az po '\n' bez '\n' a getc() nacita '\n'
            fscanf(subor, "%[^\n]s", aktualny->kategoria);	getc(subor);
            fscanf(subor, "%[^\n]s", aktualny->miesto);		getc(subor);
            fscanf(subor, "%[^\n]s", aktualny->ulica);		getc(subor);
            fscanf(subor, "%d", &aktualny->rozloha);		getc(subor);
            fscanf(subor, "%d", &aktualny->cena);			getc(subor);
            fscanf(subor, "%[^\n]s", aktualny->popis);
            (*pocet_zaznamov)++;
        }
    }
    if (prvy_alokovany == 1)
        aktualny->dalsi = NULL;
    printf("Nacitalo sa %d zaznamov\n", *pocet_zaznamov);

    if (subor != NULL)
        fclose(subor);
    return prvy;
}

void v(ZAZNAM* prvy)
{
    ZAZNAM* aktualny = prvy;

    if (aktualny == NULL) {
        return;
    }

    int cislo_zaznamu = 1;
    while (aktualny != NULL) {
        printf("%d.\n", cislo_zaznamu++);
        printf("kategoria ponuky: %s\n", aktualny->kategoria);
        printf("miesto ponuky: %s\n", aktualny->miesto);
        printf("ulica: %s\n", aktualny->ulica);
        printf("rozloha v m2: %d\n", aktualny->rozloha);
        printf("cena: %d\n", aktualny->cena);
        printf("popis: %s\n", aktualny->popis);
        aktualny = aktualny->dalsi;
    }
}

ZAZNAM* p(ZAZNAM* prvy, int* pocet_zaznamov)
{
    ZAZNAM* novy_zaznam = NULL;
    ZAZNAM* aktualny = prvy;
    int pozicia_noveho_zaznamu;
    scanf("%d", &pozicia_noveho_zaznamu);

    // nacitanie poloziek do noveho zaznamu:
    novy_zaznam = (ZAZNAM*)malloc(sizeof(ZAZNAM));
    getchar();
    scanf("%[^\n]s", &novy_zaznam->kategoria);		getchar();
    scanf("%[^\n]s", &novy_zaznam->miesto);			getchar();
    scanf("%[^\n]s", &novy_zaznam->ulica);
    scanf("%d", &novy_zaznam->rozloha);
    scanf("%d", &novy_zaznam->cena);				getchar();
    scanf("%[^\n]s", &novy_zaznam->popis);			getchar();
    novy_zaznam->dalsi = NULL;
    (*pocet_zaznamov)++;

    //	pridanie zaznamu na zaciatok zoznamu
    if (pozicia_noveho_zaznamu == 1 || (*pocet_zaznamov) == 1) {
        if ((*pocet_zaznamov) == 1)
            return novy_zaznam;
        else {
            novy_zaznam->dalsi = prvy;
            return novy_zaznam;
        }
    }	// pridanie zaznamu do stredu zoznamu
    else if (pozicia_noveho_zaznamu > 1 && pozicia_noveho_zaznamu <= (*pocet_zaznamov)) {
        int aktualna_pozicia = 1;
        while (aktualny != NULL) {
            if (pozicia_noveho_zaznamu == aktualna_pozicia + 1) {
                novy_zaznam->dalsi = aktualny->dalsi;
                aktualny->dalsi = novy_zaznam;
            }
            aktualny = aktualny->dalsi;
            aktualna_pozicia++;
        }
        return prvy;
    }	// pridanie zaznamu na koniec zoznamu
    else {
        for (int i = 1; i < (*pocet_zaznamov) - 1; i++)
            aktualny = aktualny->dalsi;
        aktualny->dalsi = novy_zaznam;
        return prvy;
    }
}

ZAZNAM* z(ZAZNAM* prvy, int* pocet_zaznamov)
{
    ZAZNAM* aktualny = prvy;
    int pocet_vymazanych_zaznamov = 0;

    char vymaz_miesto[N];
    getchar();
    gets_s(vymaz_miesto, N);

    if (aktualny == NULL)
        return NULL;

    unsigned int i;
    ZAZNAM* aktualny_dalsi = aktualny->dalsi;

    for (i = 0; i < strlen(vymaz_miesto); i++)	// zmeni zadany text na male pismena
        vymaz_miesto[i] = tolower(vymaz_miesto[i]);

    char miesto_v_zazname[N];
    while (aktualny_dalsi != NULL) {
        for (i = 0; i < strlen(aktualny_dalsi->miesto); i++)	// zmeni nazov miesta v zazname na male pismena
            miesto_v_zazname[i] = tolower(aktualny_dalsi->miesto[i]);
        miesto_v_zazname[i] = '\0';

        if (strstr(miesto_v_zazname, vymaz_miesto) != NULL) {	// vymazavanie vsetkych zaznamov, ktore sa zhoduju, okrem prveho
            aktualny->dalsi = aktualny->dalsi->dalsi;
            free(aktualny_dalsi);
            pocet_vymazanych_zaznamov++;
            aktualny_dalsi = aktualny->dalsi;
            continue;
        }
        aktualny = aktualny->dalsi;
        aktualny_dalsi = aktualny->dalsi;
    }

    aktualny = prvy;
    for (i = 0; i < strlen(aktualny->miesto); i++)
        miesto_v_zazname[i] = tolower(aktualny->miesto[i]);
    miesto_v_zazname[i] = '\0';

    if (strstr(miesto_v_zazname, vymaz_miesto) != NULL) {	// vymazanie prveho zaznamu, ak sa zhoduje
        aktualny_dalsi = aktualny->dalsi;
        free(aktualny);
        pocet_vymazanych_zaznamov++;
        *pocet_zaznamov -= pocet_vymazanych_zaznamov;
        printf("Vymazalo sa %d zaznamov\n", pocet_vymazanych_zaznamov);
        return aktualny_dalsi;
    }
    else {
        *pocet_zaznamov -= pocet_vymazanych_zaznamov;
        printf("Vymazalo sa %d zaznamov\n", pocet_vymazanych_zaznamov);
        return aktualny;
    }
}

void h(ZAZNAM* prvy)
{
    int zadana_cena;
    scanf("%d", &zadana_cena);

    if (prvy == NULL)	// ak zoznam neexistuje, tak funkcia konci
        return;

    ZAZNAM* aktualny = prvy;
    int cislo_zaznamu = 1;
    int vypisany_zaznam = 0;	// flag, ktory urcuje ci sa vypisal aspon jeden zaznam
    while (aktualny != NULL) {
        if (zadana_cena >= aktualny->cena) {
            printf("%d.\n", cislo_zaznamu++);
            printf("kategoria ponuky: %s\n", aktualny->kategoria);
            printf("miesto ponuky: %s\n", aktualny->miesto);
            printf("ulica: %s\n", aktualny->ulica);
            printf("rozloha v m2: %d\n", aktualny->rozloha);
            printf("cena: %d\n", aktualny->cena);
            printf("popis: %s\n", aktualny->popis);
            vypisany_zaznam++;
        }
        aktualny = aktualny->dalsi;
    }

    if (vypisany_zaznam == 0) {
        printf("V ponuke su len reality s vyssou cenou\n");
    }
}

void a(ZAZNAM* prvy)
{
    ZAZNAM* aktualny = prvy;
    int pocet_aktualizovanych_zaznamov = 0;

    char miesto_ponuky[N];
    getchar();
    gets_s(miesto_ponuky, N);

    ZAZNAM* aktualizovany = (ZAZNAM*)malloc(sizeof(ZAZNAM));
    scanf("%[^\n]s", &aktualizovany->kategoria);	getchar();
    scanf("%[^\n]s", &aktualizovany->miesto);		getchar();
    scanf("%[^\n]s", &aktualizovany->ulica);
    scanf("%d", &aktualizovany->rozloha);
    scanf("%d", &aktualizovany->cena);				getchar();
    scanf("%[^\n]s", &aktualizovany->popis);		getchar();
    aktualizovany->dalsi = NULL;

    if (aktualny == NULL)	// ak je zoznam prazdny, neaktualizuje sa nic
        return;

    unsigned int i;
    for (i = 0; i < strlen(miesto_ponuky); i++)
        miesto_ponuky[i] = tolower(miesto_ponuky[i]);

    char miesto_v_zazname[N];
    while (aktualny != NULL) {
        for (i = 0; i < strlen(aktualny->miesto); i++)
            miesto_v_zazname[i] = tolower(aktualny->miesto[i]);
        miesto_v_zazname[i] = '\0';

        if (strstr(miesto_v_zazname, miesto_ponuky) != NULL) {
            strcpy(aktualny->kategoria, aktualizovany->kategoria);
            strcpy(aktualny->miesto, aktualizovany->miesto);
            strcpy(aktualny->ulica, aktualizovany->ulica);
            aktualny->rozloha = aktualizovany->rozloha;
            aktualny->cena = aktualizovany->cena;
            strcpy(aktualny->popis, aktualizovany->popis);
            pocet_aktualizovanych_zaznamov++;
        }
        aktualny = aktualny->dalsi;
    }
    printf("Aktualizovalo sa %d zaznamov\n", pocet_aktualizovanych_zaznamov);
    free(aktualizovany);
}

ZAZNAM* u(ZAZNAM* prvy)
{
    ZAZNAM* usporiadane = NULL;	// novy usporiadany zoznam
    ZAZNAM* aktualny = prvy;

    if (aktualny == NULL) {
        printf("Zoznam nie je mozne usporiadat\n");
        return NULL;
    }

    while (aktualny != NULL) {
        ZAZNAM* aktualny_dalsi = aktualny->dalsi;		// krokuje po povodnom zozname a pamata si miesto pre 'aktualny'
        //	umiestnenie na prvu poziciu:
        if (usporiadane == NULL || (strcmp(usporiadane->miesto, aktualny->miesto) > 0) || (strcmp(usporiadane->miesto, aktualny->miesto) == 0 && usporiadane->cena >= aktualny->cena)) {
            aktualny->dalsi = usporiadane;
            usporiadane = aktualny;
        }
            //	umiestnenie na ostatne pozicie:
        else {
            ZAZNAM* usporiadane_aktualne = usporiadane;		// urci, za ktory zaznam v zozname 'usporiadane' sa vklada aktualny zaznam
            while (usporiadane_aktualne->dalsi != NULL && (strcmp(usporiadane_aktualne->dalsi->miesto, aktualny->miesto) <= 0)) {
                if (strcmp(usporiadane_aktualne->dalsi->miesto, aktualny->miesto) == 0 && usporiadane_aktualne->dalsi->cena > aktualny->cena)
                    break;
                usporiadane_aktualne = usporiadane_aktualne->dalsi;
            }
            aktualny->dalsi = usporiadane_aktualne->dalsi;
            usporiadane_aktualne->dalsi = aktualny;
        }
        aktualny = aktualny_dalsi;		// pokracuje na dalsiu polozku v povodnom zozname
    }

    printf("Zaznamy boli usporiadane\n");
    return usporiadane;
}

int main()
{
    char vstup;
    int pocet_zaznamov = 0;
    ZAZNAM* prvy = NULL;

    while (1) {
        vstup = getchar();
        if (vstup == 'n')			prvy = n(prvy, &pocet_zaznamov);
        else if (vstup == 'v')		v(prvy);
        else if (vstup == 'p')		prvy = p(prvy, &pocet_zaznamov);
        else if (vstup == 'z')		prvy = z(prvy, &pocet_zaznamov);
        else if (vstup == 'h')		h(prvy);
        else if (vstup == 'a')		a(prvy);
        else if (vstup == 'k')		break;
        else if (vstup == 'u')		prvy = u(prvy);
    }

    if (prvy != NULL) {
        ZAZNAM* vymaz = prvy;
        while (vymaz != NULL) {
            prvy = prvy->dalsi;
            free(vymaz);
            vymaz = prvy;
        }
    }

    return 0;
}