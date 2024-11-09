///BANCOMAT
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <math.h>

int main()
{
    FILE *f=fopen("BDD.txt","r");
    typedef struct {
        char nume[30];
        int pin;
        float balanta;
    }bazadate;
    char buff[255],nume[30],nume1[30],pin1,pin2,pin3,pin4,rasp,rasp1,suma1[10];
    int pin,i=0,j,nr,ok,ok1,ig,ig1,ib[20],nrpers=0;
    float l,suma;
        while(fgets(buff,255,f))
        {
            nrpers++;
        }
        bazadate* bdd=(bazadate*)malloc(nrpers*sizeof(bazadate));   ///Alocare dinamica
        fseek(f,0,SEEK_SET);
        while(fgets(buff,255,f))   ///Inregistrarea datelor in baza de date
        {
            j=0;l=0.1;
            bdd[i].pin=0;bdd[i].balanta=0;
            while(buff[j]!=' ')
            {
                bdd[i].nume[j]=buff[j];
                j++;
            }
            j++;
            while(buff[j]!=' ')
            {
                bdd[i].pin=bdd[i].pin*10+(buff[j]-'0');
                j++;
            }
            j++;
            ib[i]=j;
            while(buff[j]!='.')
            {
                bdd[i].balanta=bdd[i].balanta*10+(buff[j]-'0');
                j++;
            }
            j++;
            while(buff[j]!='\n')
            {
                bdd[i].balanta=bdd[i].balanta+(buff[j]-'0')*l;
                l=l/10;j++;
            }
            i++;
        }
        nr=i-1;
    Nume:
        printf("          Bancomat Digital\n\n Introduceti Numele (Nume_Prenume): ");
        scanf("%s",nume);
        ok=0;
        for (i=0;i<=nr;i++)
            if (strcmp(nume,bdd[i].nume)==0)
            {
                ok=1;
                ig=i;
            }
        if (ok==0)
        {
            system("cls");
            printf("          Bancomat Digital\n\n  Nu exista un cont inregistrat pe acest nume.\n\n Doriti sa incercati din nou ? [(D)=Da, (N)=Nu]: ");
            rasp=getch();
            if (rasp=='D' || rasp=='d')
            {
                system("cls");
                goto Nume;
            }
            else
                if (rasp=='N' || rasp=='n')
                {
                    system("cls");
                    printf("          Bancomat Digital\n\n Va multumim si va mai asteptam.\n");
                    return 0;
                }
                else
                {
                    system("cls");
                    printf("          Bancomat Digital\n\n ! Valoare invalida !\n Va multumim si va mai asteptam.\n");
                    return 0;
                }
        }
        if (ok==1)
        {
            Pin:
                system("cls");
                printf("          Bancomat Digital\n\n Introduceti PIN-ul: ");
                pin1=getch();
                system("cls");
                printf("          Bancomat Digital\n\n Introduceti PIN-ul: *");
                pin2=getch();
                system("cls");
                printf("          Bancomat Digital\n\n Introduceti PIN-ul: **");
                pin3=getch();
                system("cls");
                printf("          Bancomat Digital\n\n Introduceti PIN-ul: ***");
                pin4=getch();
                system("cls");
                pin=(pin1-'0')*1000+(pin2-'0')*100+(pin3-'0')*10+(pin4-'0');
                if (pin!=bdd[ig].pin)
                {
                    system("cls");
                    printf("          Bancomat Digital\n\n ! Pin incorect !\n\n Doriti sa incercati din nou ? (D=Da, N=Nu): ");
                    rasp=getch();
                    if (rasp=='D' || rasp=='d')
                    {
                        system("cls");
                        goto Pin;
                    }
                    else
                    {
                        system("cls");
                        printf("          Bancomat Digital\n\n Va multumim si va mai asteptam.\n");
                        return 0;
                    }
                }
                else
                {
                    Main:
                        printf("          Bancomat Digital\n\n(1) Consultare sold\n(2) Depunere numerar\n(3) Retragere numerar\n(4) Transfer\n");
                        printf("\n Alegeti numarul operatiunii dorite sau apasati tasta (q) pentru anulare: ");
                        rasp=getch();
                        system("cls");
                        switch(rasp)
                        {
                        case '1':{  printf("          Bancomat Digital\n\n Sold: %.2f RON\n",bdd[ig].balanta);
                                    printf("\n Apasati orice tasta pentru meniul principal: ");
                                    rasp1=getch();
                                    system("cls");
                                    goto Main;
                        }
                        case '2':{  printf("          Bancomat Digital\n\n Suma pe care doriti sa o depuneti: ");
                                    scanf("%f",&suma);
                                    bdd[ig].balanta+=suma;
                                    sprintf(suma1,"%.2f",bdd[ig].balanta);   ///Schimbarea elementelor in fisier
                                    FILE *f1=fopen("BDD1.txt","w");
                                    fseek(f,0,SEEK_SET);
                                    for (i=0;i<ig;i++)
                                    {
                                        fgets(buff,255,f);
                                        fprintf(f1,buff);
                                    }
                                    fgets(buff,255,f);
                                    strcpy(buff+ib[ig],suma1);
                                    strcat(buff,"\n\0");
                                    fprintf(f1,buff);
                                    while(fgets(buff,255,f))
                                    {
                                        fprintf(f1,buff);
                                    }
                                    fclose(f); fclose(f1);
                                    remove("BDD.txt"); rename("BDD1.txt","BDD.txt");
                                    printf("\n Operatiune realizata cu succes.");
                                    printf("\n Noul sold este: %.2f",bdd[ig].balanta);
                                    printf("\n Apasati orice tasta pentru anulare: ");
                                    rasp1=getch();
                                    system("cls");
                                    printf("          Bancomat Digital\n\n Va multumim si va mai asteptam.\n");
                                    return 0;
                        }
                        case '3':{  Retragere:
                                        printf("          Bancomat Digital\n\n Suma pe care doriti sa o retrageti: ");
                                        scanf("%f",&suma);
                                        if (suma>bdd[ig].balanta)
                                        {
                                            printf("\n ! Valoarea introdusa este mai mare decat sold-ul curent !\n");
                                            printf("\n Apasati [Backspace] pentru meniul principal sau orice alta tasta pentru a reincerca: ");
                                            rasp1=getch();
                                            if (rasp1=='\b')
                                            {
                                                system("cls");
                                                goto Main;
                                            }
                                            else
                                            {
                                                system("cls");
                                                goto Retragere;
                                            }
                                        }
                                        else
                                        {
                                            bdd[ig].balanta-=suma;
                                            sprintf(suma1,"%.2f",bdd[ig].balanta);
                                            FILE *f1=fopen("BDD1.txt","w");
                                            fseek(f,0,SEEK_SET);
                                            for (i=0;i<ig;i++)
                                            {
                                                fgets(buff,255,f);
                                                fprintf(f1,buff);
                                            }
                                            fgets(buff,255,f);
                                            strcpy(buff+ib[ig],suma1);
                                            strcat(buff,"\n\0");
                                            fprintf(f1,buff);
                                            while(fgets(buff,255,f))
                                            {
                                                fprintf(f1,buff);
                                            }
                                            fclose(f); fclose(f1);
                                            remove("BDD.txt"); rename("BDD1.txt","BDD.txt");
                                            printf("\n Operatiune realizata cu succes.");
                                            printf("\n Noul sold este: %.2f",bdd[ig].balanta);
                                            printf("\n Apasati orice tasta pentru anulare: ");
                                            rasp1=getch();
                                            system("cls");
                                            printf("          Bancomat Digital\n\n Va multumim si va mai asteptam.\n"); return 0;
                                        }
                        }
                        case '4':{  Transfer:
                                        printf("          Bancomat Digital\n\n Suma pe care doriti sa o transferati: ");
                                        scanf("%f",&suma);
                                        if (suma>bdd[ig].balanta)
                                        {
                                            printf("\n ! Valoarea introdusa este mai mare decat sold-ul curent !\n");
                                            printf("\n Apasati [Backspace] pentru meniul principal sau orice alta tasta pentru a reincerca: ");
                                            rasp1=getch();
                                            if (rasp1=='\b')
                                            {
                                                system("cls");
                                                goto Main;
                                            }
                                            else
                                            {
                                                system("cls");
                                                goto Transfer;
                                            }
                                        }
                                        else
                                        {
                                            NumeTransfer:
                                                system("cls");
                                                printf("          Bancomat Digital\n\n Introduceti numele persoanei careia ii transferati (Nume_Prenume): ");
                                                scanf("%s",nume1);
                                                ok1=0;
                                                for (i=0;i<=nr;i++)
                                                    if (strcmp(nume1,bdd[i].nume)==0)
                                                    {
                                                        ok1=1;
                                                        ig1=i;
                                                    }
                                                if (ok1==0)
                                                {
                                                    system("cls");
                                                    printf("          Bancomat Digital\n\n Nu exista un cont inregistrat pe acest nume.\n");
                                                    printf("\n Apasati [Backspace] pentru a reincerca sau orice alta tasta pentru anulare: ");
                                                    rasp1=getch();
                                                    if (rasp1=='\b')
                                                    {
                                                        system("cls");
                                                        goto NumeTransfer;
                                                    }
                                                    else
                                                    {
                                                        system("cls");
                                                        printf("          Bancomat Digital\n\n Va multumim si va mai asteptam.\n"); return 0;
                                                    }
                                                }
                                                else
                                                {
                                                    system("cls");
                                                    bdd[ig].balanta-=suma;
                                                    bdd[ig1].balanta+=suma;
                                                    sprintf(suma1,"%.2f",bdd[ig].balanta);
                                                    FILE *f1=fopen("BDD1.txt","w");
                                                    fseek(f,0,SEEK_SET);
                                                    for (i=0;i<ig;i++)
                                                    {
                                                        fgets(buff,255,f);
                                                        fprintf(f1,buff);
                                                    }
                                                    fgets(buff,255,f);
                                                    strcpy(buff+ib[ig],suma1);
                                                    strcat(buff,"\n\0");
                                                    fprintf(f1,buff);
                                                    while(fgets(buff,255,f))
                                                    {
                                                        fprintf(f1,buff);
                                                    }
                                                    fclose(f1);fclose(f);
                                                    remove("BDD.txt"); rename("BDD1.txt","BDD.txt");
                                                    sprintf(suma1,"%.2f",bdd[ig1].balanta);
                                                    FILE *f2=fopen("BDD2.txt","w");
                                                    f=fopen("BDD.txt","r+");
                                                    for (i=0;i<ig1;i++)
                                                    {
                                                        fgets(buff,255,f);
                                                        fprintf(f2,buff);
                                                    }
                                                    fgets(buff,255,f);
                                                    strcpy(buff+ib[ig1],suma1);
                                                    strcat(buff,"\n\0");
                                                    fprintf(f2,buff);
                                                    while(fgets(buff,255,f))
                                                    {
                                                        fprintf(f2,buff);
                                                    }
                                                    fclose(f); fclose(f2);
                                                    remove("BDD.txt"); rename("BDD2.txt","BDD.txt");
                                                    printf("          Bancomat Digital\n\n Operatiune realizata cu succes.");
                                                    printf("\n Noul sold este: %.2f",bdd[ig].balanta);
                                                    printf("\n Apasati orice tasta pentru anulare: ");
                                                    rasp1=getch();
                                                    system("cls");
                                                    printf("          Bancomat Digital\n\n Va multumim si va mai asteptam.\n"); return 0;
                                                }
                                        }
                        }
                        case 'q':{printf("          Bancomat Digital\n\n Va multumim si va mai asteptam.\n"); return 0;}
                        case 'Q':{printf("          Bancomat Digital\n\n Va multumim si va mai asteptam.\n"); return 0;}
                        }
                }
        }
    return 0;
}
