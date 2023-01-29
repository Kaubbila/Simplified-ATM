#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int saldo(); int tapahtumat(); int liittyma(); void haluatkoTiedot(int luku); int setelit(int luku);
void otto(), lopetus(), menu();
int yritykset=3, valinta= 0, ottovalinta,tiedotvalinta, muusumma, saldovalinta, k = 0;
double tili,kateisnosto=1000;

int main(void)
{
    tili = 5000;
    char tilinumerosyotetty[256] = {'\0'}, paate[] = ".acc";
    int tunnuslukusyotetty;
    int tunnusluku;

    //Määritellään .acc tiedosto
    FILE *infilep;
    //Lisää .acc tiedoston sijainti
    infilep = fopen ("12345.acc", "r");

    //Jos tiedostoa ei löydy niin tulostetaan virhelause
    if(infilep == NULL) {
        printf("Virhe avattaessa tiedostoa\n");
        exit(1);
    }
    //Kopioidaan tiedoston tunnusluku -> int tunnusluku1, jotta voidaan verrata syötettyä ja tekstitiedoston pin-koodia.
    fscanf(infilep,"%d",&tunnusluku);


    //Tilinumeron syöttäminen
    printf("Tervetuloa! \nSyota kortti, ole hyva\n\n");
    sleep(1.5);
    printf("*Laittaa kortin*\n");
    sleep(1);

    while(k != 1){
    printf("Syota tilinumero: \n");
    scanf("%s", tilinumerosyotetty);

    //.acc pääte liitetään char tilinumerosyotetty perään.
    strcat(tilinumerosyotetty, paate);

    //Verrataan tiedostonimeä syötettyyn tilinumeroon. Jos ei ole sama niin loop alkaa alusta ja kysyy uudelleen tilinumeroa
    FILE *input;
    if((input=fopen(tilinumerosyotetty, "r")) == NULL){
    printf("Vaarin, yrita uudelleen\n");
    } else {
        printf("\nYhdistetaan...\n");
        sleep(1);
        break;
        }
    }
    //Tunnusluvun syöttäminen. Kysytään 3 kertaa PIN-koodia. Virheellisten yritysten jälkeen ohjelma poistuu suorituksesta.
    while (tunnuslukusyotetty != tunnusluku) {
    printf("\nNappaile tunnusluku \n");
    printf("Suojaa tunnuslukusi\n");
    printf("Lopuksi paina OK\n");
    scanf("%d", &tunnuslukusyotetty);
    if (tunnuslukusyotetty == tunnusluku) { // Jos PIN-Koodi on oikein. Siirrytään pois loopista
        break;
    } else if (yritykset == 0){ // Jos kortti lukittuu. Ohjelma poistuu suorituksesta.
        printf("\n***********************************\n");
        printf("\nKortti lukittu. Ota yhteytta pankkiisi.\n");
        printf("\n***********************************\n");
        return 0;
    } else { // Jokaisen väärän yrityksen jälkeen vähennetään -1 yrityksestä.
        printf("\nVaara koodi. Yrityksia jaljella %d", yritykset);
        yritykset -= 1;
    }

    }
    printf("Yhdistetaan pankkiin. Odota hetki...");
    sleep(1.5);
    fclose (infilep);
    menu();
    return 0;
}
void menu() { // Päälooppi, joka kierrättää koko ideaa.
            system("cls"); // Menu näkymä. (Cls Lisää hieman tunnelmaa). Looppi päätyy aina menuun, josta päästään kokeilemaan muita toimintoja. 9. Numerolla voidaan poistua ohjelmasta.
            printf("\n**************Valitse**************\n");
            printf("\n**4.Liittyman lataus/      1.Otto**");
            printf("\n  Puheaika                2.Saldo**");
            printf("\n**9.Stop             3.Tapahtumat**\n");
            printf("\n***********************************\n");
            scanf("%d", &valinta);
    while(1) {
            switch (valinta) {
            case 1:
                otto(); // Päästään otto funktioon
                sleep(1.5);
                break;
            case 2:
                saldo(); // Päästään saldo funktioon
                sleep(1.5);
                break;
            case 3:
                tapahtumat(); // Päästään tapahtumat funktioon
                sleep(1.5);
                break;
            case 4:
                liittyma(); // Päästään Liittymän lataus / Puheaika funktioon
                sleep(1.5);
                break;
            case 9: // Poistutaan pankkiautomaatista
                lopetus();
                break;
            default:
                printf("Syota oikea luku\n");
                scanf("%d", &valinta);
            }
    }
}
void otto() { // Otto funktio
system("cls");
printf("\n***************Otto****************\n");
printf("\n**1.20 euroa         4. 90 euroa**\n");
printf("**2.40 euroa         5.140 euroa**\n");
printf("**3.60 euroa         6.240 euroa**\n");
printf("**9.Alkuun           7.Muu summa**\n");
printf("\n***********************************\n");
scanf("%d", &ottovalinta);

while (1) {
    if(kateisnosto == 0 || kateisnosto < 0) {
        printf("Kateisnostoraja taynna\n");
        sleep(1);
        menu();
    }
    switch (ottovalinta) {
    case 1:
        tili = tili - 20;
        kateisnosto = kateisnosto - 20;
        haluatkoTiedot(20);
        break;
    case 2:
        tili = tili - 40;
        kateisnosto = kateisnosto - 40;
        haluatkoTiedot(40);
        break;
    case 3:
        tili = tili - 60;
        kateisnosto = kateisnosto - 60;
        haluatkoTiedot(60);
        break;
    case 4:
        tili = tili - 90;
        kateisnosto = kateisnosto - 90;
        haluatkoTiedot(90);
        break;
    case 5:
        tili = tili - 140;
        kateisnosto = kateisnosto - 140;
        haluatkoTiedot(140);
        break;
    case 6:
        tili = tili - 240;
        kateisnosto = kateisnosto - 240;
        haluatkoTiedot(240);
        break;
    case 7:
        muusumma = 0;
        printf("\nSyota summa: ");
        scanf("%d", &muusumma);
        if (muusumma > tili) {
        printf("Tililla ei riittavasti katetta nostoon.");
        sleep(1.5);
        break;
        }else if(muusumma < 0 || muusumma > kateisnosto) {
        printf("Virheellinen maara");
        sleep(1.5);
        break;
        } else if (muusumma < 50 && muusumma % 20 != 0) {
        printf("Virheellinen maara");
        sleep(1.5);
        break;
        }else {
        tili = tili - muusumma;
        kateisnosto = kateisnosto - muusumma;
        haluatkoTiedot(muusumma);
        break;
        }
    case 9:
        menu();
        break;
    default:
        printf("Syota oikea luku\n");
        scanf("%d", &ottovalinta);
        }
    }
}
//Tiedot näytölle funktio
void haluatkoTiedot(int luku) {
system("cls");
printf("\n********Haluatko tiedot?*********\n");
printf("\n                    1. Naytolle**");
printf("\n**3. Ei kiitos      2. Kuitille**\n");
printf("\n*********************************\n");
scanf("%d", &tiedotvalinta);

while(1) {
    switch(tiedotvalinta){
    case 1:
    printf("\n********************************\n");
        printf("Ota kortti, ole hyva\nRahat tulossa");
        sleep(2);
        printf("\nOta rahat, ole hyva");
        printf("\n********************************\n");
        sleep(2);
        printf("\nTilin saldo %.2lf+\n", tili);
        printf("Tililta nostettavissa %.2lf+\n", tili);
        printf("\n********************************\n");
        sleep(2);

        setelit(luku);
        sleep(2);
    case 2 ...3:
        printf("\n********************************\n");
        printf("Ota kortti, ole hyva\nRahat tulossa");
        sleep(2);
        printf("\nOta rahat, ole hyva");
        printf("\n********************************\n");
        setelit(luku);
        sleep(2);
    default:
        printf("Syota oikea luku\n");
        scanf("%d", &tiedotvalinta);

        }
    }
}
//Seteleiden tulostus funktio
int setelit(int luku) {
    int parikymppiset = 0;
    int viiskymppiset = 0;
    int jaljella = 0;
    int alkupSumma = luku;
    int summa = luku;
    while (summa != 0) {
    if (summa % 50 == 0) {
        viiskymppiset = viiskymppiset + 1;
        summa = summa - 50;
        jaljella = summa % 50;
    }
    else if (jaljella % 20 == 0) {
        parikymppiset = parikymppiset + 1;
        summa = summa - 20;
    }
  }
    printf("Tulostettava summa %d\n", alkupSumma);
    if (parikymppiset > 0)
    printf("Tulostetaan 20 Euron seteleita: %d kpl\n", parikymppiset);
    if (viiskymppiset > 0)
    printf("Tulostetaan 50 Euron seteleita: %d kpl\n", viiskymppiset);
    sleep(4);
    menu();
}

//Saldofunktio
int saldo() {
system("cls");
printf("\n**********Tilin tilanne***********\n");
printf("\nTilin saldo %.2lf+\n", tili);
printf("Tililta nostettavissa %.2lf+\n", tili);
printf("Kortin kateisnostovara %.2lf+\n", kateisnosto);
printf("\n9.Lopeta\n");
printf("\n**********************************\n");
scanf("%d", &saldovalinta);
while(1) {
switch (saldovalinta) {
    case 9:
        menu();
    default:
        printf("Syota oikea luku\n");
        scanf("%d", &saldovalinta);
    }
}

}
//Tapahtumafunktio
int tapahtumat() {
    printf("\n***Kayttaja tarkisti tapahtumat***");
    sleep(1.5);
    menu();

}
//Liittymafunktio
int liittyma() {
    printf("\n***Kayttaja latasi puheaikaa***");
    sleep(1.5);
    menu();
}
//Lopetusfunktio
void lopetus() {
    printf("\n-------------------------------------\n");
    printf("Kiitos kaynnista.\nTervetuloa uudelleen");
    printf("\n-------------------------------------\n");
    exit(0);
}
