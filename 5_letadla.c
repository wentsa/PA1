/* 
 * File:   main.c
 * Author: Tomas Chalupnik
 *
 * Created on November 16, 2013, 12:05 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>
#define param 1e-12

/*
 * 
 */
double distCalculate(double X1[],double Y1[],int max,int *cnt)
{
    int i=0,k=0;
    double dist=DBL_MAX,c=0;
    
    for (i=0;i<max;i++)
        {
        for (k=i+1;k<max;k++)
                {
                c=((X1[k]-X1[i])*(X1[k]-X1[i])+(Y1[k]-Y1[i])*(Y1[k]-Y1[i]));
                        if (c - dist < param*(c+dist) && fabs(c-dist) > param*fabs(c+dist)) /*c < dist*/
                                {dist=c;
                                *cnt=1;}
                        else if (fabs(c - dist) <= param*fabs(c+dist)) /*c == dist*/
                                *cnt=*cnt + 1;
                }}
    return dist;
}



int main(int argc, char** argv) {

    int status,max=1,count=0;
    double * X;
    double * Y;
    double x,y,dist;
    char c;
    
    
    
    X = (double*) malloc (0* sizeof(*X));
    Y = (double*) malloc (0* sizeof(*Y));
    
    printf("Zadejte souradnice:\n");
    
    /*while (!feof(stdin) && (status=scanf("[%lf,%lf",&x,&y))== 2)
    {   
        
        if (status==EOF)
                break;
        
        X=(double*) realloc (X ,max * sizeof(*X));
        Y=(double*) realloc (Y ,max * sizeof(*Y));
        
        if ( X==NULL || Y==NULL)
                {free (X);
                free (Y);
                printf ("Chyba alokace.\n");
                return 1;}
        
        
        else
                {X[max-1]=x;
                Y[max-1]=y;
                max++;} 
        if (fgetc(stdin)==' ')
                {printf("Nespravny vstup1.\n");
                free (X);
                free (Y);
                return 1;}
        printf("aaa\n");
        while (((fgetc(stdin)!=' ') && fgetc(stdin) !=EOF) || (fgetc(stdin) != '\n'&& fgetc(stdin) !=EOF)) {}
        if (feof(stdin))
                    break;
    }*/
    
    
    while (!feof(stdin) && (status=scanf(" [%lf,%lf%c",&x,&y,&c))== 3 && c==']')
    {   
        
        X=(double*) realloc (X ,max * sizeof(*X));
        Y=(double*) realloc (Y ,max * sizeof(*Y));
        
        if ( X==NULL || Y==NULL)
                {free (X);
                free (Y);
                printf ("Chyba alokace.\n");
                return 1;}
        
        
        else
                {X[max-1]=x;
                Y[max-1]=y;
                max++;} 
        
        
    }
    
    
    
    if (status != 3 && status != EOF)
                {printf("Nespravny vstup.\n");
                free (X);
                free (Y);
                return 1;}
    if (max<=2)
        {printf("Nespravny vstup.\n");
                free (X);
                free (Y);
                return 1;}
 
 dist=distCalculate(X,Y,max-1,&count);   
    
 printf ("Vzdalenost nejblizsich letadel: %g\n",sqrt(dist));
 printf("Nalezenych dvojic: %d\n",count);
    
    
    
    
    
    
    
    
free (X);
free (Y);
    
    return (EXIT_SUCCESS);
}

