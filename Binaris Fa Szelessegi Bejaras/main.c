#include <stdio.h>
#include <stdlib.h>
#include "debugmalloc.h"

// munkaido : 120+130+30 perc
typedef struct Varo {
    struct BinarisFa *ptr;
    struct Varo*kov;
} Varo;

typedef struct Polarok{
    struct Varo *elso;
    struct Varo *utolso;

}Polarok;

typedef struct BinarisFa {
    int adat;
    struct BinarisFa *right;
    struct BinarisFa *left;
} BinarisFa;

BinarisFa *epites(BinarisFa *gyoker, int adat) {
    if (gyoker == NULL) {
        BinarisFa *uj = (BinarisFa*)malloc(sizeof(BinarisFa));
        uj->left = NULL;
        uj->right = NULL;
        uj->adat = adat;
        return uj;
    }

    if (adat > gyoker->adat)
        gyoker->right = epites(gyoker->right, adat);
    else if (adat < gyoker->adat)
        gyoker->left = epites(gyoker->left, adat);
    return gyoker;
}

void vegere(Polarok *elejevege,BinarisFa *fa){

    Varo* uj=(Varo*)malloc(sizeof(Varo));
    uj->ptr = fa;
    uj->kov = NULL;


    if(elejevege->elso==NULL){
         elejevege->elso=uj;
         elejevege->utolso=uj;
         return;
    }

    elejevege->utolso->kov=uj;
    elejevege->utolso=uj;

}

void elejepop(Polarok *elejevege){
    Varo *p=elejevege->elso;
    elejevege->elso=elejevege->elso->kov;
    free(p);
}

BinarisFa *faepito1(void){
    BinarisFa* fa=NULL;
    int t[10]={5,3,1,0,2,4,7,6,9,8};
    for(int i=0;i!=10;i++)
        fa = epites(fa,t[i]);
    return fa;
}

int main() {
    /*    EPITES    */

    BinarisFa* fa = faepito1();
    /* EPITES VEGE  */

    Polarok elejevege = {NULL,NULL};

    vegere(&elejevege,fa);


    while(elejevege.elso!=NULL){

        if(elejevege.elso->ptr->left!=NULL)
            vegere(&elejevege,elejevege.elso->ptr->left);

        if(elejevege.elso->ptr->right!=NULL)
            vegere(&elejevege,elejevege.elso->ptr->right);

        printf("%d ",elejevege.elso->ptr->adat);
        free(elejevege.elso->ptr);
        elejepop(&elejevege);
    }

    return 0;
}
