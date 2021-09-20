#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "debugmalloc.h"

typedef struct ListaElem {
    char adat[30];
    struct ListaElem* next;
} ListaElem;

ListaElem *elejere_insert(ListaElem *eleje,char* szo) {
    ListaElem *uj = (ListaElem*) malloc(sizeof(ListaElem));
    strcpy(uj->adat,szo);
    uj->next = eleje;
    return uj;
}

ListaElem *mintakesztio(ListaElem* lista) {
    lista = elejere_insert(lista,"rament");
    lista = elejere_insert(lista,"napom");
    lista = elejere_insert(lista,"egy");
    lista = elejere_insert(lista,"amire");
    lista = elejere_insert(lista,"rekurzio");
    lista = elejere_insert(lista,"egy");
    lista = elejere_insert(lista,"egyszer");
    lista = elejere_insert(lista,"volt");
    return lista;
}

/*  Parameteresen megvaltoztatja a cimet */


void quicksort(ListaElem** original) {

    inline void move_linked_list(ListaElem **from,ListaElem**to) {
        ListaElem *uj = *from;
        *from = (*from)->next;
        uj->next = *to;
        *to = uj;
    }

    inline ListaElem* concat_2_list(ListaElem* egy,ListaElem* ket) {
        ListaElem*uj;
        if(egy==NULL) {
            egy=ket;
            return egy;
        }
        if(ket==NULL) {
            return egy;
        }
        uj=egy;
        while(uj->next!=NULL)
            uj=uj->next;
        uj->next=ket;
        return egy;
    }

    if(*original==NULL)
        return;
    ListaElem *smallers=NULL;
    ListaElem *samesize=NULL;
    ListaElem *greater=NULL;
    ListaElem *iter = *original;
    ListaElem *pivot = *original;

    while(iter!=NULL) {
        ListaElem *next=iter->next;
        if(strcmp(iter->adat,pivot->adat)==0)
            move_linked_list(original,&samesize);
        else if(strcmp(iter->adat,pivot->adat)>0)
            move_linked_list(original,&greater);
        else
            move_linked_list(original,&smallers);
        iter=next;
    }
    quicksort(&smallers);
    quicksort(&greater);
    *original=concat_2_list( concat_2_list(smallers,samesize),greater);
}

void felszabaditas(ListaElem *eleje) {
    ListaElem *mozgo = eleje;
    while(mozgo!=NULL) {
        ListaElem *heh=mozgo->next;
        free(mozgo);
        mozgo=heh;
    }
    return;
}

void nyomtatas( ListaElem *elem)
{
    while (elem != NULL)
    {
        printf("%s ", elem->adat);
        elem = elem->next;
    }
    printf("\n");
}

int main()
{

    ListaElem *lista=NULL;
    lista = mintakesztio(lista);

    nyomtatas(lista);
    puts("");

    quicksort(&lista);

    nyomtatas(lista);
    felszabaditas(lista);
    return 0;
}
