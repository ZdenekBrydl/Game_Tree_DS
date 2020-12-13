#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

char rod[25];
int penize;
int vliv;
int rok;
int pocet;
int krev = 0;
bool e = true;
typedef struct node{
    int kvalita;
    char jmeno[20];
    struct node* potomci[10];
    bool muz;
    int kvalitazeny;
    bool zije;
}node;
node *hrac;
typedef struct{
    node *prapredek;
}strom;
strom rodokmen;
void potomci(){
    pocet = rand()%3 + 2;
    printf("\nNarodilo se ti %d deti.", pocet);
    int i;
    for(i=0; i<pocet; i++){
        hrac->potomci[i] = (node *)malloc(sizeof(node));
        hrac->potomci[i]->potomci[0] = NULL;
        hrac->potomci[i]->zije = true;
        if ((i==0) || (rand()%2==1))
        {hrac->potomci[i]->muz=true;
        printf("\nPojmenuj syna: ");
        scanf("%s", &hrac->potomci[i]->jmeno);}
        else
        {hrac->potomci[i]->muz=false;
        printf("\nPojmenuj dceru: ");
        scanf("%s", hrac->potomci[i]->jmeno);}
        hrac->potomci[i]->kvalita=(hrac->kvalita + hrac->kvalitazeny)/2 + ((rand()%31) - 15);
        if(hrac->potomci[i]->kvalita > 100) hrac->potomci[i]->kvalita = 100;
        if(hrac->potomci[i]->kvalita < 0) hrac->potomci[i]->kvalita = 0;}
    for(;i<10;i++)
        hrac->potomci[i] = NULL;
}
void vypisrodu(){
    int i;
    printf("\n\nTvy potomci: ");
    for(i=0;hrac->potomci[i]!=NULL;i++){
        char pohlavi[5];
        if(hrac->potomci[i]->muz){
            strcpy(pohlavi, "muz");
            if(jededic(i)==1) printf("\n\n---Dedic:---");
        }
        else strcpy(pohlavi, "zena");
        printf("\n\nJmeno potomka: %s\n Pohlavi: %s\nIndex kvality potomka: %d", hrac->potomci[i]->jmeno, pohlavi, hrac->potomci[i]->kvalita);
        if(jededic(i)==1) printf("\n\n------------");
    }
}
int jededic(x){
    int a = 0;
    while(hrac->potomci[a]->muz==false) a++;
    if(a==x) return 1;
    else return 0;
}
void akce(){
    int i;
    char sel;
    for(i=0;hrac->potomci[i]!=NULL;i++) if(hrac->potomci[i]->muz){
        printf("\n\n\nJak chces nalozit se synem %s?\nA pro odchod do valky (zisk penez, moznost smrti a ztraty vlivu)\nY pro vydedeni (ztrata penez a naroku dedit)\nR pro vrazdu (ztrata vlivu a smrt)\nC pro trenink(zisk vlivu za penize)\n", hrac->potomci[i]->jmeno);
        scanf(" %c", &sel);
        if(sel == 'A'){
            if(rand()%101<=(hrac->potomci[i]->kvalita)+1){
                int korist = hrac->potomci[i]->kvalita/2+(rand()%3 - 1)*(penize/20);
                printf("\n%s valku prezil ve zdravi.\nVratil se s koristi v hodnote %d", hrac->potomci[i]->jmeno, korist);
                penize += korist;
            }else
            {
                int ztrat = vliv/10;
                if(ztrat == 0) ztrat++;
                printf("\n%s ve valce tragicky zahynul.\nTvuj rod ztratil %d vlivu", hrac->potomci[i]->jmeno, ztrat);
                vliv -= ztrat;
                krev++;
                hrac->potomci[i]->zije = false;
            }
        }
        else if(sel == 'Y'){
            printf("\nVydedil jsi syna %s, odesel s casti tveho majetku v hodnote %d", hrac->potomci[i]->jmeno, penize/(pocet*2));
            penize -= penize/(pocet*2);
            hrac->potomci[i]->zije = false;
        }
        else if(sel == 'R'){
            int ztrat = vliv/10;
            if(ztrat == 0) ztrat++;
            printf("\n%s nestastnou nahodou zahynul.\nTvuj rod ztratil %d vlivu", hrac->potomci[i]->jmeno, ztrat);
            vliv -= ztrat;
            krev++;
            hrac->potomci[i]->zije = false;
        }
        else if(sel == 'C'){
            printf("\nVlastnis %d penez, kolik se rozhodnes investovat do treninku %s? %s ma silu %d. \nTrenink je v kurzu 1:25\n", penize, hrac->potomci[i]->jmeno, hrac->potomci[i]->jmeno, hrac->potomci[i]->kvalita);
            int a;
            scanf("%d", &a);
            if(a<=0) a=0;
            penize -= a*25;
            hrac->potomci[i]->kvalita += a;
            if(hrac->potomci[i]->kvalita >= 100) hrac->potomci[i]->kvalita = 100;
            printf("Po treninku %s ma silu %d a v pokladnici ti zbylo: %d", hrac->potomci[i]->jmeno, hrac->potomci[i]->kvalita, penize);
        }
        else{printf("\nA to si rikas monarcha? Neumi ani vydat rozkaz? Padl si v ocich sveho sluzebnictva, ktery usporadali rebelii. Ztratil si veskere sve penize a vliv.");
            penize = 0;
            vliv = 0;
        }
    }
}
int dedic(){
    int s = 0;
    for (s=0;hrac->potomci[s]!=NULL;s++) if(hrac->potomci[s]->muz) if(hrac->potomci[s]->zije) return s;
    if(e) {
        printf("\n----------------------------------Tvuj rod vymrel po meci, prohral jsi----------------------------------\n\nTve vysledky: \nRod %s\nRozpocet: %d\nVliv: %d\nPocet zabitych potomku: %d\n\n", rod, penize, vliv, krev);
        e = false;
        return NULL;
    }
}
void svatba(){
    int b = 0;
    char sel;
    int c = dedic();
    if(e){
        for(b=0;hrac->potomci[b]!=NULL;b++){
            if(hrac->potomci[b]->muz==false){
                printf("\n\n\nJak chces nalozit s dcerou %s?\nV pro vdavky (zisk vlivu, ztrata penez)\nI pro snatek v rodu (bez nutnosti davat veno, ale ztrata vlivu)\nK pro odchod do klastera (ztrata penez i vlivu, avsak v mensim mnozstvi)\n", hrac->potomci[b]->jmeno);
                scanf(" %c", &sel);
                if(sel == 'V'){
                    int zisk = hrac->potomci[b]->kvalita/10*(rand()%1+1);
                    int ztrata = rand()%100+100 - hrac->potomci[b]->kvalita;
                    printf("\nTva dcera %s se vdala do rodu, ktery ti svou vernosti pridal %d vlivu, vzala s sebou veno v hodnote %d", hrac->potomci[b]->jmeno, zisk, ztrata);
                    vliv += zisk;
                    penize -= ztrata;
                }
                else if(sel == 'I'){
                    int ztrata = vliv/(hrac->potomci[b]->kvalita/10);
                    printf("\nKvuli incestu tvuj rod padl v ocich svych lidi, ztratil %d vlivu", ztrata);
                    vliv -= ztrata;
                }
                else if(sel == 'K'){
                    int ztrata1 = penize/100;
                    int ztrata2 = vliv/10;
                    printf("\nTva dcera %s se odevzdala bohu a vydala se slouzit do klastera, vzala s sebou %d penez a jeji absence zpusobila ztratu vlivu o %d", hrac->potomci[b]->jmeno, ztrata1, ztrata2);
                    penize -= ztrata1;
                    vliv -= ztrata2;
                }
                else{printf("A to si rikas monarcha? Neumi ani vydat rozkaz? Padl si v ocich sveho sluzebnictva, ktery usporadali rebelii. Ztratil si veskere sve penize a vliv.");
                    penize = 0;
                    vliv = 0;
                }
            }
        }
        hrac = hrac->potomci[c];
        printf("\n\n\nVyber si jednu z zen pro sveho dedice:");
        int z;
        int krasa1 = hrac->kvalita - rand()%20;
        int veno1 = 700-krasa1*(6 + rand()%4+1);
        printf("\nZena cislo 1 ma index krasy %d a veno %d", krasa1, veno1);
        int krasa2 = hrac->kvalita - rand()%25;
        int veno2 = 700-krasa2*(6 + rand()%4+1);
        printf("\nZena cislo 2 ma index krasy %d a veno %d", krasa2, veno2);
        int krasa3 = hrac->kvalita - rand()%15;
        int veno3 = 700-krasa3*(6 + rand()%4+1);
        printf("\nZena cislo 3 ma index krasy %d a veno %d", krasa3, veno3);
        printf("\nNapis cislo:");
        scanf("%d", &z);
        if(z==1){
            hrac->kvalitazeny = krasa1;
            penize += veno1;
        }
        else if(z==2){
            hrac->kvalitazeny = krasa2;
            penize += veno2;
        }
        else if(z==3){
            hrac->kvalitazeny = krasa3;
            penize += veno3;
        }
        else{printf("Vzal sis prostou devecku neslechetneho puvodu.");
            hrac->kvalitazeny = 0;
        }
    }

}
void gameloop(){
    printf("\n\n--------------------------------------------\nRod %s\nHlava Rodu: %s\nIndex kvality hlavy rodu: %d\nRozpocet: %d\nVliv: %d\nPise se rok %d\n\n ", rod, hrac->jmeno, hrac->kvalita, penize, vliv, rok);
    potomci();
    vypisrodu();
    akce();
    svatba();
    rok += 50;
    if(rok == 1900) {
        printf("\n\n--------------------------------------------\nPise se rok 1918 a monarchie padla, hra konci.\n--------------------------------------------\n\nTve vysledky: \nRod %s\nRozpocet: %d\nVliv: %d\nPocet zabitych potomku: %d\n\n", rod, penize, vliv, krev);
        e = false;
    }
    if(e) gameloop();

}
void rodovy_strom(){
    printf("\n-------------------\nRok: 1000");
    printf("\nOtec rodu: %s",rodokmen.prapredek->jmeno);
    int let;
    hrac = rodokmen.prapredek;
    rok = (rok-1000)/50;
    for(let=1; let <= rok;let++){
        printf("\n-------------------\nRok: %d",(let*50)+1000);
        int y;
        printf("\nPotomci dedice: ");
        for(y=0;hrac->potomci[y]!=NULL;y++){
            if(hrac->potomci[y]->potomci[0]!=NULL) printf("\n---Dedic:---");
            printf("\n%s - sila: %d", hrac->potomci[y]->jmeno, hrac->potomci[y]->kvalita);
            if(hrac->potomci[y]->potomci[0]!=NULL) printf("\n------------");
        }
        int g = dedic();
        hrac = hrac->potomci[g];
    }
    printf("\n\n");
}
int main(){
    srand(time(0));
    printf("Pojmenujte svuj rod: ");
    scanf("%s", rod);
    penize = 100;
    vliv = 10;
    rok = 1000;
    printf("Pojmenujte zakladatele rodu: ");
    rodokmen.prapredek = (node*)malloc(sizeof(node));
    scanf("%s", rodokmen.prapredek->jmeno);
    rodokmen.prapredek->kvalita = 75;
    rodokmen.prapredek->muz = true;
    rodokmen.prapredek->kvalitazeny = 25;
    hrac = rodokmen.prapredek;
    gameloop();
    if(vliv>=(rok-800)/40) printf("\n\nDarilo se ti vytecne");
    else if(vliv<(rok-800)/20) printf("\n\nNedarilo se ti");
    else printf("\n\nDarilo se ti obstojne");
    printf("\n\n\nTvuj rodovy strom:");
    rodovy_strom();
    while(true) printf("");
    return 0;
}
