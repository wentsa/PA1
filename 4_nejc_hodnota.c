/* 
 * File:   main.c
 * Author: Tomas Chalupnik
 *
 * Created on November 9, 2013, 9:53 PM
 */

#include <stdio.h>
#include <stdlib.h>
#define max 100000

/*
 * 
 */

int intSort2 ( const void * a, const void * b )
 {
   int da = ((int *) a)[1];
   int db = ((int *) b)[1];
   if (da < db) return 1;
   else if (da > db) return -1;
   return 0;
 }
int intSortProc ( int * a, int * b )
 {
   return ( *b - *a );
 }
int main(int argc, char** argv) {

    int status,a=0,pole[max],pocet[max],cislo[max],cisloPocet[max][2],i=0,k=0,x=0;
    
    printf("Zadejte cisla, EOF=konec:\n");
    
    while (! feof (stdin)) /*nacteni V a print vysledku */
        {status=scanf ("%d", &pole[i]);
        if ( (status != 1 && status != EOF) )
        {       printf("Nespravny vstup.\n");
                return 1;}
        i++;}
    i=0;
    
    while (pole[i]!=0)
        i++;
    
    
    if(i > max)
        {printf("Nespravny vstup.\n");
        return 1;}
    if(i==0)
        {printf("Nespravny vstup.\n");
        return 1;}
    
    
    
       
            
    qsort ( pole, i, sizeof ( *pole ), (int(*)(const void *, const void *))intSortProc ); /*serazeni vstupu podle velikosti*/
    
   
    
    for (k=0;k<max;k++) /*pocet nastaven na 1*/
        pocet[k]=1;
    
    cislo[0]=pole[0];
    
    for (k=0;k<i-1;k++) /*pro kazde cislo priradi pocet vyskytu*/
        {if (pole[k]==pole[k+1])
                {pocet[a]++;
                cislo[a]=pole[k];}
        else {cislo[a+1]=pole[k+1];
                a++;}}
    
       
    while (cislo[x] != 0) /*pocet ruznych hodnot*/
        x++;
    
    
       
    for (k=0;k<x;k++)
    {   cisloPocet[k][0]=cislo[k];
        cisloPocet[k][1]=pocet[k];}
    
    
    
    
    qsort ( cisloPocet, x, sizeof ( *cisloPocet ), (int(*)(const void *, const void *))intSort2 ); /*serazeni podle poctu vyskytu*/
                
   
    
    for (k=0;k<x;k++)
    {   cislo[k]=cisloPocet[k][0];
        pocet[k]=cisloPocet[k][1];}
    if (pocet[0]==1)
        k=i;
    else k=0; /*celkovy pocet maximalnich hodnot*/
    
    
    
    if (pocet[0] != 1)
        while (pocet[k]==pocet[k+1])
            k++;
    
    
    
    printf("Nejvice vyskytu (%d x) mela cisla:",pocet[0]);
    printf(" %d",cislo[0]);
    if (pocet[0] != 1)
        for (i=1;i<=k;i++)
                printf (", %d",cislo[i]);
    else
        for (i=1;i<k;i++)
                printf (", %d",cislo[i]);
    printf("\n");
        
    return (EXIT_SUCCESS);
}

