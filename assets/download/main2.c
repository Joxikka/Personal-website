#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define MAX 10 //maksimalan broj karaktera indeksa definisan zadatkom
#define max 20 //maksimalan broj karaktera imena/prezimena definisan zadatkom
#define KRAJ 5

typedef struct student{
    char ime[max];
    char prezime[max];
    char indeks[MAX];
    struct student *sledeci;
}student;

void ispis(student *glava){
    student *tekuci=glava;
    printf("lista: [\n");
    while(tekuci!=NULL){
        printf("\tIME: %s PREZIME: %s INDEKS: %s\n",tekuci->ime, tekuci->prezime, tekuci->indeks);
        tekuci=tekuci->sledeci;
    }
    printf("       ]\n");
}

student *dodaj_na_kraj(student *glava, student *novi)
{
    novi->sledeci=NULL;
    if(glava!=NULL)
    {
        student *tekuci=glava;
        while(tekuci->sledeci!=NULL)
            tekuci=tekuci->sledeci;
        tekuci->sledeci=novi;
    }
    else
        glava=novi;
    return glava;
}

student* formiranje_liste(student *glava)
{
    FILE *fajl;
    fajl=fopen("studenti.txt","r");
    if(fajl==NULL)
    {
        printf("\nGRESKA\n");
        return NULL;
    }
    else{
        char ind[MAX];
        char im[max];
        char pim[max];
        while(fscanf(fajl, "%s %s %s", &ind, &pim, &im) != EOF){
            student *novi=(student*)malloc(sizeof(student));
            strcpy(novi->indeks,ind);
            strcpy(novi->prezime,pim);
            strcpy(novi->ime,im);
            glava = dodaj_na_kraj(glava, novi);
        }
    }
    fclose(fajl);
    return glava;
}

int nadji(student *glava, char s[])
{
    student *tekuci=glava;
    while(tekuci!=NULL)
    {
        if(strcmp((tekuci->indeks),s)==0)
            return 1;
        tekuci=tekuci->sledeci;
    }
    return 0;
}

student *sort(student *glava)
{
    student *tekuci, *prethodni=glava;
    int a;
    while(prethodni!=NULL)
    {
        tekuci=prethodni->sledeci;
        while(tekuci!=NULL)
        {
            a=strcmp((tekuci->prezime),(prethodni->prezime));
            if(a < 0)
            {
                student *tmp = NULL;
                tmp = (student*)malloc(sizeof(student));
                strcpy(tmp->ime, tekuci->ime);
                strcpy(tmp->prezime, tekuci->prezime);
                strcpy(tmp->indeks, tekuci->indeks);

                strcpy(tekuci->ime, prethodni->ime);
                strcpy(tekuci->prezime, prethodni->prezime);
                strcpy(tekuci->indeks, prethodni->indeks);

                strcpy(prethodni->ime, tmp->ime);
                strcpy(prethodni->prezime, tmp->prezime);
                strcpy(prethodni->indeks, tmp->indeks);
            }
            else if(a == 0){
                int b = strcmp((tekuci->ime),(prethodni->ime));
                if(b < 0)
                {
                    student *tmp = NULL;
                    tmp = (student*)malloc(sizeof(student));
                    strcpy(tmp->ime, tekuci->ime);
                    strcpy(tmp->prezime, tekuci->prezime);
                    strcpy(tmp->indeks, tekuci->indeks);

                    strcpy(tekuci->ime, prethodni->ime);
                    strcpy(tekuci->prezime, prethodni->prezime);
                    strcpy(tekuci->indeks, prethodni->indeks);

                    strcpy(prethodni->ime, tmp->ime);
                    strcpy(prethodni->prezime, tmp->prezime);
                    strcpy(prethodni->indeks, tmp->indeks);
                }
                else if(b == 0)
                {
                    int c = strcmp((tekuci->indeks),(prethodni->indeks));
                    if(c < 0)
                    {
                        student *tmp = NULL;
                        tmp = (student*)malloc(sizeof(student));
                        strcpy(tmp->ime, tekuci->ime);
                        strcpy(tmp->prezime, tekuci->prezime);
                        strcpy(tmp->indeks, tekuci->indeks);

                        strcpy(tekuci->ime, prethodni->ime);
                        strcpy(tekuci->prezime, prethodni->prezime);
                        strcpy(tekuci->indeks, prethodni->indeks);

                        strcpy(prethodni->ime, tmp->ime);
                        strcpy(prethodni->prezime, tmp->prezime);
                        strcpy(prethodni->indeks, tmp->indeks);
                    }
                }
            }
            tekuci=tekuci->sledeci;
        }
        prethodni=prethodni->sledeci;
    }
    return glava;
}

void unos()
{
    char INDEX[MAX];
    int x;
    student *glava= NULL;
    glava = formiranje_liste(glava);
    while(scanf("%s",INDEX)!= -1)
    {
        x=nadji(glava, INDEX);
        if(x==0)
            printf("\nNE, student sa tim indeksom ne postoji.\n");
        else
            printf("\nDA, student sa tim indeksom postoji.\n");

    }
}

student *promena_prezimena(student *glava)
{
    char s[MAX];
    printf("\nUesite indeks studenta cije prezime zelite da promenite: ");
    scanf("%s", s);
    int x;
    x=nadji(glava, s);
    if(x==0)
        printf("\nGRESKA, student sa tim indeksom ne postoji.\n");
    else{
         char np[max];
        student *tekuci=glava;
        while(tekuci!=NULL)
        {
            if(strcmp((tekuci->indeks),s)==0)
            {
                printf("\nUnesite novo prezime: ");
                scanf("%s", np);
                strcpy(tekuci->prezime, np);
            }
        tekuci=tekuci->sledeci;
        }
    }
    return  glava;
}

int GlavniMeni(void){
	printf("\n\n KORISNICKI MENI:\n");
	printf("\n 1) Prebaci podatke iz datoteke studenti.txt");
	printf("\n 2) Sortiraj leksikografski podatke iz datoteke studenti.txt");
	printf("\n 3) Unesi indeks studenta");
	printf("\n 4) Promeni prezime");
	printf("\n 5) Kraj programa");
	int iz;
	do {
		printf("\n\nVas izbor (1 - 5): ");
		scanf("%d", &iz);
		if((iz < 1) || (iz > 5))
		{
		    printf("\nUneli ste neodgovarajuci broj.");
		}
	} while ((iz < 1) || (iz > 5));
		return iz;
}
void Izvrsi (const int iz) {
    student *glava=NULL;
    glava=formiranje_liste(glava);
	switch (iz) {
	case 1: ispis(glava); break;
	case 2: glava = sort(glava); ispis(glava); break;
	case 3: unos(); break;
	case 4: promena_prezimena(glava);ispis(glava);break;
	case 5: ;break;
    }
  }

int main(void){
	int izbor;
	do {
		izbor = GlavniMeni();
		Izvrsi(izbor);
	} while (izbor != KRAJ);
		return 0;
}
