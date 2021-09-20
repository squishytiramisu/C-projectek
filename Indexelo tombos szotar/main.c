#include <stdio.h>
#include <stdbool.h>
#include <stdbool.h>
#include <string.h>

/* Szerintem a binaris kereses resze meglehetosen nehez,
*  igy a kodduplikacio nelkuliseg miatt, azzal nyilvan nagyon egyszeru lenne.
*  En nekem tetszik ahogy megcsinaltam a nyelv eset szetvalasztast , minden boole algebra tudasomat bevetve.
* IDO: 270 perc */


typedef struct Szo {
    char magyar[50+1];
    char angol[50+1];
} Szo;

typedef struct Szotar {
    Szo szavak[200];
    int db;
} Szotar;

typedef enum Mod {angol,magyar} Mod;

/**
 * Felvesz egy új szót a szótárba.
 * Ha már benne van, nem csinál semmit.
 * @return True, ha bekerült a szó, false, ha megtelt a szótár.
 */

void indexelo(int* tomb,Szotar sz,Mod nyelv);


bool felvesz(Szotar *szt, Szo uj,int* eng,int*hu) {
    /* megtelt? */
    if (szt->db == 200)
        return false;
    /* benne van? */
    for (int i = 0; i < szt->db; ++i)
        if (strcmp(szt->szavak[i].magyar, uj.magyar) == 0
                && strcmp(szt->szavak[i].angol, uj.angol) == 0)
            return true;
    /* betesszük */
    strcpy(szt->szavak[szt->db].magyar, uj.magyar);
    strcpy(szt->szavak[szt->db].angol, uj.angol);
    szt->db += 1;

    indexelo(eng,*szt,angol);   /*Edit*/
    indexelo(hu,*szt,magyar);
    return true;
}

Szo* bsearch(Szotar* sz,char*szo,int*tomb,Mod nyelv) {
    int eleje=0, vege=sz->db-1;
    while(eleje<=vege) {

        int kozep=eleje+(vege-eleje)/2;
        Szo* jelen= &(sz->szavak[tomb[kozep]]);

        /*Ossze es-eltem a nyelvet a komparatorokkal */
        if((nyelv==angol&&strcmp(jelen->angol,szo)==0) || (nyelv==magyar && strcmp(jelen->magyar,szo)==0) )
            return jelen;

        else if((nyelv==angol&&strcmp(jelen->angol,szo)>0) || (nyelv==magyar&&strcmp(jelen->magyar,szo)>0))
            vege=kozep-1;

        else
            eleje=kozep+1;
    }
    return NULL;
}
/* Megnezni angolul, ha nincs meg akkor magyarul */
Szo* teljes(Szotar *sz, char* szo,int*eng,int*hun) {
    Szo* ered=bsearch(sz,szo,eng,angol);
    if(ered!=NULL)
        return ered;

    ered=bsearch(sz,szo,hun,magyar);
    if(ered!=NULL)
        return ered;
    return NULL;
}


/**
 * Fájlba írja a szótárat.
 * @return true, ha sikeres volt a mûvelet.
 * Ha nem, hibaüzenetet is ad a kimeneten.
 */
bool ment(Szotar *szt, char *fajlnev) {
    FILE *f = fopen(fajlnev, "wt");
    if (f == NULL) {
        perror("Nem sikerült menteni a szótárat");
        return false;
    }
    for (int i = 0; i < szt->db; ++i)
        fprintf(f, "%s\t%s\n", szt->szavak[i].magyar,
                szt->szavak[i].angol);
    fclose(f);
    return true;
}


/**
 * Betölti a szótárat. Teljesen felülírja az
 * addigi tartalmat a fájlból beolvasott adatokkal.
 * @return true, ha sikeres volt.
 */
bool betolt(Szotar *szt, char *fajlnev,int* angtomb,int *magytomb) {
    FILE *f = fopen(fajlnev, "rt");
    if (f == NULL) {
        perror("Nem sikerült betölteni a szótárat");
        return false;
    }
    szt->db = 0;
    Szo uj;
    while (fscanf(f, " %[^\t] %[^\n]", uj.magyar, uj.angol) == 2) {
        szt->szavak[szt->db] = uj;
        szt->db += 1;
    }
    fclose(f);
    indexelo(angtomb,*szt,angol);
    indexelo(magytomb,*szt,magyar);
    return true;
}


/**
 * Kilistázza a szótár teljes tartalmát a képernyõre.
 */
void listaz(Szotar *szt,int* tomb) {

    for (int i = 0; i < szt->db; ++i)
        printf("%s = %s\n", szt->szavak[tomb[i]].magyar, szt->szavak[tomb[i]].angol);
}

void indexelo(int* tomb,Szotar sz,Mod nyelv) {
    int i=0;
    char par[2][25];
    /* Beszamozzuk oket*/
    for(int iter=0; iter!=sz.db; iter++)
        tomb[iter]=iter;

    /* Gnome rendezes az ertek alapjan */
    while(i!=sz.db) {

        if(i==0) {
            i++;
            continue;
        }
        if(nyelv==angol) {
            strcpy(par[0],sz.szavak[tomb[i-1]].angol);
            strcpy(par[1],sz.szavak[tomb[i]].angol);
        }
        else {
            strcpy(par[0],sz.szavak[tomb[i-1]].magyar);
            strcpy(par[1],sz.szavak[tomb[i]].magyar);
        }

        if(strcmp(par[0],par[1]) <=0 )
            i++;
        else {
            int temp = tomb[i];
            tomb[i]=tomb[i-1];
            tomb[i-1]=temp;
            i--;
        }
    }

}

int main(void) {
    int magyar_rend[200];
    int angol_rend[200];

    Szotar sz;
    sz.db = 0;  /* inicializálás; a többit nem kell */


    /* SZAVAK FELVETELE*/
    felvesz(&sz, (Szo) {
        "alma", "apple"
    },angol_rend,magyar_rend);
    felvesz(&sz, (Szo) {
        "korte", "pear"
    },angol_rend,magyar_rend);
    felvesz(&sz, (Szo) {
        "tabla csoki", "bar of chocolate"
    },angol_rend,magyar_rend);
    felvesz(&sz, (Szo) {
        "takarmany noveny", "covertion growth"
    },angol_rend,magyar_rend);
    felvesz(&sz, (Szo) {
        "doboz gyufa", "box of matches"
    },angol_rend,magyar_rend);
    felvesz(&sz, (Szo) {
        "strazsa", "sentinel"
    },angol_rend,magyar_rend);


    /* KERESES */
    printf("Kereses =====\n");
    Szo * talalat = teljes(&sz,"sentinel",angol_rend,magyar_rend);

    if (talalat == NULL)
        printf("Nincs meg");
    else
        printf("Talalat: %s = %s\n", talalat->magyar, talalat->angol);

    printf("\n");


    /* MENTES ES BEOLVASAS */
    printf("Fajlkezeles =====\n");
    ment(&sz, "szotar.txt");
    sz.db = 0;
    betolt(&sz, "szotar.txt",magyar_rend,angol_rend);
    printf("%d szó beolvasva.\n", sz.db);
    printf("\n");

    /*
    indexelo( angol_rend,sz,angol);
    indexelo( magyar_rend,sz,magyar);
    */


    /* TARTALOM KIIRAS */
    printf("A szótár tartalma =====\n");
    listaz(&sz,magyar_rend);
    //listaz(&sz,angol_rend);

    printf("\n");
}
