#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/* Time: 201 perc
*  Tanulsagok: 1. A menu vezerlese stringekkel az szamomra nagyon uj, de vegre valahol hasznalhattam a hasht!
*              2. A rekurzio segedtombbel es adat atadassal sosem hasznaltam meg, de mashogy szerintem ezt nem lehetett megcsinalni.
*              3. A fakrol valo perspektivam megvaltozott! Eddig megrogzodesem volt hogy egy fanak max 3 gyereke lehet! Kulonben nincs ertelme de hat ez annyira hamis amennyire egy allitas hamis lehet
*              4. Vegso tanulasag, hogy abrakat kell rajzoni ha elakad az ember! Es mindig nezni kell furcsa eseteket...*/

typedef struct TrpFa {
    bool szo_veg;
    struct TrpFa* offsprings[26];
} TrpFa;

int betu_ind(char be) {
    return be-'a';
}

int ind_betu(int index) {
    return index+'a';
    /*Az indexbol betut csinal, 0-> a, 1->b stb...*/
}

TrpFa *letrehoz(void) {
    TrpFa *uj=(TrpFa*)malloc(sizeof(TrpFa));
    for(int i=0; i!=26; i++)
        uj->offsprings[i]=NULL;
    uj->szo_veg=false;
    return uj;
}

void betevofunc(TrpFa* fa,char *szo) {
    TrpFa*iter=fa;

    for(int szo_i = 0 ; szo_i<strlen(szo); szo_i++) {
        int gyerekindexe = betu_ind(szo[szo_i]);

        if(iter->offsprings[gyerekindexe]==NULL)
            iter->offsprings[gyerekindexe]=letrehoz();

        iter=iter->offsprings[gyerekindexe];
    }
    iter->szo_veg=true;
}

bool keresofunc(TrpFa *fa,char* szo) {
    TrpFa*iter=fa;

    for(int szo_i=0; szo_i<strlen(szo); szo_i++) {
        int gyerekindexe = betu_ind(szo[szo_i]);
        if(!iter->offsprings[gyerekindexe])
            return false;

        iter=iter->offsprings[gyerekindexe];
    }
    bool benne_e =  (iter->szo_veg) && (iter!=NULL);
    return benne_e;
}

void felszab(TrpFa*fa) {
    if(fa==NULL)
        return;
    TrpFa* iter=fa;
    for(int i=0; i<26; i++)
        felszab(iter->offsprings[i]);
    free(iter);
}

void listazfunc(TrpFa* fa,int be,char* szotomb) {

    if(fa->szo_veg) {
        szotomb[be]='\0';
        puts(szotomb);
    }
    for(int betuk=0; betuk!=26; betuk++) {
        if(fa->offsprings[betuk]!=NULL) {
            szotomb[be]=ind_betu(betuk);
            listazfunc(fa->offsprings[betuk],be+1,szotomb);
        }
    }
}

int hasher(char* szo){
    char option[][10]={"keres","beszur","listaz","kilep"};

}

void (*valaszto[4]()=listazfunc,keresofunc,betevofunc);

int main()
{
    TrpFa* fa=letrehoz();

    bool fut=true;
    char bemenet[50];
    char segedszo[30];

    while(fut) {
        fgets(bemenet,50,stdin);
        bemenet[strlen(bemenet)-1]='\0';/*enter a vegen torles*/
        int dontes=hasher(strtok (bemenet, " "));

        switch(dontes) {
            case 1072:/*KILEP*/ /*case hasher("kilep"): ? */
                fut=false;
                break;

            case 1092:/*KERES*/
                if(keresofunc(fa,strtok(NULL," ")))
                    puts("Benne van!");
                else
                    puts("Nincs benne!");
                break;

            case 1681:/*LISTAZAS*/
                listazfunc(fa,0,segedszo);
                break;

            case 1706:/*BETESZ*/
                betevofunc(fa,strtok(NULL," "));
                break;

            default:
                puts("Ugyes bevitel, de probaljuk meg ujra!");

        }
        puts("");

    }


    felszab(fa);
    return 0;
}
