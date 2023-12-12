#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define MAX 1000 //maksimalan broj studenata definisan zadatkom
#define max 100 //maksimalan broj predmeta definisan zadatkom
#define KRAJ 5

char niz_studenata[MAX][41];
char niz_predmeta[max][23];

void niz_s()
{
    char s[41]; //privremena promenljiva za cuvanje jednog reda niza
    int i=0;
    FILE *studenti;
    studenti=fopen("student.txt","r");
    if(studenti==NULL)
    {
        printf("/nGRESKA/n");
        return 0;
    }
    else{
        while(!feof(studenti))
        {
            fgets(s,41,studenti);
            strcpy(niz_studenata[i],s);
            i++;
        }
        printf("\nDobijeni niz:\n");
        for(i=0;i<5;i++)
            printf("%s",niz_studenata[i]);
    }
    fclose(studenti);
}
void niz_p()
{
    char p[41]; //privremena promenljiva za cuvanje jednog reda niza
    int i=0;
    FILE *predmeti;
    predmeti=fopen("predmeti.txt","r");
    if(predmeti==NULL)
    {
        printf("/nGRESKA/n");
        return 0;
    }
    else{
        while(!feof(predmeti))
        {
            fgets(p,23,predmeti);
            strcpy(niz_predmeta[i],p);
            i++;
        }
        printf("\nDobijeni niz:\n");
        for(i=0;i<5;i++)
            printf("%s",niz_predmeta[i]);
    }
    fclose(predmeti);
}
void nova_prijava()
{
    int rezultat=0;
    char indeks[10];
    char temp[41];
    char temp_p[41];
    char sifra[4];
    char temp_pr[17];
    int ocena;
    int i;
    int zarez1=0,zarez2=0;
    char zarez=',';
    char temp_indeks[10];
    char temp_predmet[4];
    char *p,*q;
    int temp_ocena;
    int dozvola_upisa=1;
    FILE *prijave;
    FILE *studenti;
    FILE *predmet;
    prijave=fopen("prijave.txt","r+");
    studenti=fopen("student.txt","r");
    predmet=fopen("predmeti.txt","r");
    if(prijave==NULL||studenti==NULL||predmet==NULL)
    {
        printf("GRESKA");
        return 0;
    }
    else{

                //ispitivanje postojanja predmeta
                printf("\n%Unesite sifru predmeta: ");
                scanf("%s",&sifra);
                while(fgets(temp_p,26,predmet)!=NULL){
                    if((strstr(temp_p,sifra)) != NULL) {
                        rezultat++;
                    }
                }
                if(rezultat==0)
                {
                    printf("\nPredmet ne postoji.\n");
                    return 0;
                }
                else{
                    printf("\nPredmet postoji\n");
                }
                rezultat=0;
                fclose(predmet);

               //ispitivanje postojanja studenta
                printf("\nUnesite broj indeksa studenta: ");
                scanf("%s",&indeks);
                while(fgets(temp,41,studenti) != NULL) {
                    if((strstr(temp, indeks)) != NULL) {
                        rezultat++;
                    }
                }
                if(rezultat==0)
                {
                    printf("\nStudent pod tim indeksom ne postoji.\n");
                    return 0;
                }
                else {
                     printf("\nStudent postoji\n");
                }
                rezultat=0;
                fclose(studenti);

                //ispitivanje pravilnosti ocene
                do{
                    printf("\nUnesite ocenu: ");
                    scanf("%d",&ocena);
                    if((ocena<5)||(ocena>10))
                        printf("\nOcena nije ispravna\n");
                }
                while((ocena<5)||(ocena>10));

                //ispitivanje dozvole upisa
                while(fgets(temp_pr,17,prijave)!=NULL)
                {
                    for(i=0;i<17;i++)
                    {
                            if((temp_pr[i]==zarez)&&(zarez1==0))
                                zarez1=i;
                            if((temp_pr[i]==zarez)&&(zarez1!=0))
                                zarez2=i;
                    }
                    strncpy(temp_indeks, temp_pr + 0, 9);
                    strncpy(temp_predmet, temp_pr + (zarez1+1), (zarez2-zarez1-1));
                    p=strchr(temp_pr,',');
                    q=strchr(p+1,',');
                    temp_ocena=atoi((q+1));
                    *p='\0';
                    if((strcmp(indeks,temp_indeks))==0){
                        if((strcmp(sifra,temp_predmet))==0){
                            if(temp_ocena>5)
                                dozvola_upisa=0;
                        }
                    }
                    memset(temp_predmet, 0, sizeof(temp_predmet));
                }
                if(dozvola_upisa==0)
                    printf("\nPrijava vec postoji.\n");
                else{
                    printf("\nPrijava podneta\n");
                    fprintf(prijave,"\n%s,%s,%d",indeks,sifra,ocena);
                }
                fclose(prijave);
    }

}

typedef struct{
    int sifra;
    char naziv[20];
    float prosek;
    int bp_vece5;
    int bp_5;
}predmeti_rl;

void razmeni(predmeti_rl *a,predmeti_rl *b)
{
    predmeti_rl pom;
    pom=*a;
    *a=*b;
    *b=pom;
}

int veci(predmeti_rl a,predmeti_rl b)
{
        return a.prosek<b.prosek;

}

void sort(predmeti_rl u[],int n)
{
    for(int i=0;i<n-1;i++)
        for (int j=i+1;j<n;j++)
            if (veci(u[i],u[j]))
                razmeni(&u[i],&u[j]);
}

void izvestaj()
{
        char *p, *q;
    char p_ocena[2];
    int temp_ocena;
    char temp_pr[17];
    int j=0;
    predmeti_rl rl[100];
    int temp_sifra;
    int i;
    char temp_naziv[20];
    char zarez=',';
    int zarez1=0;
    int zarez2=0;
    char temp_predmeti[26];
    char p_sifra[4];
    FILE *rang_lista;
    FILE *predmeti;
    FILE *prijave;
    rang_lista=fopen("rang_lista.txt","w");
    predmeti=fopen("predmeti.txt","r");
    prijave=fopen("prijave.txt","r");
    if(rang_lista==NULL||predmeti==NULL||prijave==NULL)
    {
        printf("GRESKA");
        return 0;
    }
    else{

        fprintf(rang_lista,"-----------------------------------------------------------------------------------------------------------------");
        fprintf(rang_lista,"\nIzvestaj za predmete\n");
        fprintf(rang_lista,"-----------------------------------------------------------------------------------------------------------------");
        fprintf(rang_lista,"\nRb.\tSifra\tPredmet\t\tProsek\t\tBr.prij. (>5)\tBr.prij.(=5)\n");
        fprintf(rang_lista,"-----------------------------------------------------------------------------------------------------------------\n");

         while(fgets(temp_predmeti,26,predmeti)!=NULL)
         {
                    for(i=0;i<26;i++)
                    {
                            if((temp_predmeti[i]==zarez))
                                zarez1=i;
                    }
                    strncpy(p_sifra, temp_predmeti + 0, zarez1);
                    strncpy(temp_naziv, temp_predmeti + (zarez1+1), (strlen(temp_predmeti)));
                    temp_sifra=atoi(p_sifra);
                    rl[j].sifra=temp_sifra;
                    strcpy(rl[j].naziv,temp_naziv);
                    rl[j].bp_5=0;
                    rl[j].bp_vece5=0;
                    rl[j].prosek=0;
                    j++;
                }
        fclose(predmeti);
        zarez1=0;

        while(fgets(temp_pr,17,prijave)!=NULL)
        {
            for(i=0;i<17;i++)
            {
                if((temp_pr[i]==zarez)&&(zarez1==0))
                    zarez1=i;
                if((temp_pr[i]==zarez)&&(zarez1!=0))
                    zarez2=i;
            }
            strncpy(p_sifra, temp_pr + (zarez1+1), (zarez2-zarez1-1));
            p=strchr(temp_pr,',');
            q=strchr(p+1,',');
            temp_ocena=atoi((q+1));
            *p='\0';
            temp_sifra=atoi(p_sifra);

            for(i=0;i<j;i++)
            {
                if(rl[i].sifra==temp_sifra)
                {
                    rl[i].prosek+=temp_ocena;
                    if(temp_ocena>5)
                        rl[i].bp_vece5++;
                    else
                        rl[i].bp_5++;

                }
            }
        memset(p_sifra, 0, sizeof(p_sifra));
        }
        fclose(prijave);

        for(i=0;i<j;i++)
        {
            if(rl[i].bp_vece5+rl[i].bp_5!=0)
                rl[i].prosek=rl[i].prosek/(rl[i].bp_vece5+rl[i].bp_5);
        }

        sort(rl,j);
        for(i=0;i<j;i++)
        {
            char *pos;
            if ((pos=strchr(rl[i].naziv, '\n')) != NULL)
                *pos = '\0';
            fprintf(rang_lista,"\n%d.\t%d\t%s\t%.2f\t\t%d\t\t%d",(i+1),rl[i].sifra,rl[i].naziv,rl[i].prosek,rl[i].bp_vece5,rl[i].bp_5);
        }
        fclose(rang_lista);
        printf("\nIzvestaj kreiran\n");
    }
}
int GlavniMeni(void){
	printf("\n\n KORISNICKI MENI:\n");
	printf("\n 1) Prebaci podatke iz datoteke student.txt");
	printf("\n 2) Prebaci podatke iz datoteke predmeti.txt");
	printf("\n 3) Unesi novu prijavu");
	printf("\n 4) Kreiraj izvestaj");
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
	switch (iz) {
	case 1: niz_s(); break;
	case 2: niz_p(); break;
	case 3: nova_prijava(); break;
	case 4: izvestaj();break;
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
