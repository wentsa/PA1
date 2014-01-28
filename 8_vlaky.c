/* 
 * File:   main.c
 * Author: Tomas Chalupnik
 *
 * Created on December 13, 2013, 4:18 PM
 */

#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct TVan
 {
   struct TVan   * m_Next;
   char          * m_To;
   void          * m_Cargo;
 } TVAN;

typedef struct TTrain
 {
   TVAN          * m_Start;
   int             m_Count;
 } TTRAIN;
 
 void tisk (TTRAIN * a,char * vlak) {
     
     TVAN * print;
                printf("\n");
                printf("train %c with %d  |@@OOOOO|-->",*vlak,a->m_Count);
                print = a -> m_Start ;
                if(print) {
                while(print -> m_Next) {
                    (printf ("[%s]--> ",print -> m_To)) ;
                    (print=print -> m_Next) ; } 
                printf("[%s]",print -> m_To) ; }
                else printf("-|");
 }
 
 
#endif /* __PROGTEST__ */
 
 int compare (const char * a,const  char * b) {
     char * p_a=NULL, *p_b=NULL;
     unsigned length;
     int i=0;
     
     if(strcmp(a,b)) return 0;
     
     length=strlen(a)+1;
     
     p_a=(char*)malloc(length*sizeof(char));
     p_b=(char*)malloc(length*sizeof(char));
     
     strncpy(p_a,a,length);
     strncpy(p_b,b,length);
     
     while(p_a[i]) {
         if(p_a[i] != p_b[i]) {
             free(p_a);
             free(p_b);
             return 0;}
         else {
             i++;
         }
     }
     free(p_a);
     free(p_b);
     return 1;    
 }

/*-------------------------BORROW-----------------------------------------------*/
 
TVAN * borrowVan ( const char * to )
 { 
    TVAN * van = (TVAN*)malloc(sizeof(*van));
    unsigned int length=strlen(to);
    
    van -> m_To = (char*)malloc((length+1)*sizeof(char));
    
    van->m_Next=NULL;
    strncpy ( van -> m_To, to, length+1);
    van->m_Cargo= NULL;
    
    return van;    
 }

/*-------------------------RETURN-----------------------------------------------*/

void   returnVans ( TTRAIN * train )
 {
    TVAN * head, * tail;
    head=NULL;
    if(train -> m_Start) {
        head = train -> m_Start;
        
    }
    
    while(head) {
        tail = head -> m_Next;
        free(head -> m_To);
        free(head);
        head = tail;       
    }
    train -> m_Start = NULL;
    train -> m_Count = 0;
 } 

/*------------------------CONNECT-----------------------------------------------*/

void   connectVan ( TTRAIN * train, TVAN * van, int toStart )
 {
    TVAN * tmp;
    
    if(toStart || ! (train -> m_Count)) {   /*na zacatek /1/ */
       van -> m_Next = train -> m_Start;
       train -> m_Start = van;
    }
    
    else {                                /*na konec /0/ */
        tmp=train -> m_Start;
        while (tmp -> m_Next) { /*ukaze na posledni*/
            tmp=tmp -> m_Next;
        }
        tmp -> m_Next = van;
        van -> m_Next = NULL;
    }
    
    (train -> m_Count)++;
}                                                             

/*------------------------ROUTE-------------------------------------------------*/

void   route ( const char * stationName, TTRAIN * train, TTRAIN * localTrain )
 {
   /*z lokalky na konec*/
    TVAN * tmp, * tail, * prev;
    int iter=0;
    
    /*-------odpoji vse od lokalky a da za rychlik--------------- */
    
    if(train -> m_Start) { /*pokud neni rychlik prazdnej*/
        tmp=train -> m_Start;
        while(tmp -> m_Next) {
            tmp = tmp -> m_Next;
        }
        tmp -> m_Next = localTrain -> m_Start;
    }
    
    else {
        train -> m_Start = localTrain -> m_Start;
    }
    (train -> m_Count) += (localTrain -> m_Count);
    localTrain -> m_Start = NULL;
    localTrain -> m_Count = 0;
    
    /*-------vybere odpovidajici vagony z rychliku a da je za lokalku-------*/
    
    
    
    tmp=train -> m_Start;
    
    if(tmp) {
        while (tmp && compare(tmp -> m_To, stationName)) { /*pripojuje vagony, pokud jsou spravny hned za lokomotivou*/
            if (localTrain -> m_Count == 0) {
                localTrain -> m_Start = tmp;
            }
            else {
                tail -> m_Next = tmp;
            }
            tail = tmp;
            train -> m_Start = tail -> m_Next;
            tail -> m_Next = NULL;
            (localTrain -> m_Count)++;
            (train -> m_Count)--;
            tmp=train -> m_Start;
        }
    }
    
    prev=tmp;
    
    while(tmp && prev) {
        if(compare(tmp -> m_To, stationName)) {
            if (localTrain -> m_Count == 0) {
                localTrain -> m_Start = tmp;
            }
            else {
                tail -> m_Next = tmp;
            }
            tail=tmp;
            prev -> m_Next = tmp -> m_Next;
            tail -> m_Next = NULL;
            (localTrain -> m_Count)++;
            (train -> m_Count)--;
        }
        
        
        iter++;
        if(iter==1) {
            prev=tmp;   
        }
        else if (prev -> m_Next) {
            prev=prev -> m_Next;
        }
        tmp=prev -> m_Next;
    }
    
    
    
    
    
    
    
    
    
 }                                                             

/*------------------------MAIN-------------------------------------------------*/
#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
 {
        TTRAIN a = { NULL, 0 }, b = { NULL, 0 }, c = { NULL, 0 };
        char   tmpStr[100];
        
        
        
        
        
        /*connectVan ( &a, borrowVan ( "Praha qwewq qwe_e233" ), 5 );
        connectVan ( &a, borrowVan ( "Praha qwewq qwe_3" ), 5 );
        route ( "Brno", &a, &b  );
                printf("\n");
                printf("|@@OOOOO|-->");
                print = a.m_Start ; 
                while(print -> m_Next) {
                    (printf ("[%s]--> ",print -> m_To)) ;
                    (print=print -> m_Next) ; } 
                printf("[%s]",print -> m_To) ; */
                
                /*printf("\n");
                printf("|@@OOOOO|-->");
                print = b.m_Start ; 
                while(print -> m_Next) {
                    (printf ("[%s]--> ",print -> m_To)) ;
                    (print=print -> m_Next) ; } 
                printf("[%s]",print -> m_To) ; */
        
        

        /*connectVan ( &a, borrowVan ( "Praha" ), 1 );
        connectVan ( &b, borrowVan ( "Praha" ), 1 );
        connectVan ( &b, borrowVan ( "brankawe" ), 1 );
        
        
        tisk(&a,"a");
        tisk(&b,"b");
        
        printf("\n%d %s\n",a.m_Count,a.m_Start);
        printf("\n%d %s\n",b.m_Count,b.m_Start);
        route ("Praha", &a, &b);
        
        
        tisk(&a,"a");
        tisk(&b,"b");
        printf("\n%d %s\n",a.m_Count,a.m_Start);*/
        
        connectVan ( &a, borrowVan ( "Praha" ), 1 );
        connectVan ( &a, borrowVan ( "Brno" ), 1 );
        connectVan ( &a, borrowVan ( "Ostrava" ), 0 );
        connectVan ( &a, borrowVan ( "Brno" ), 0 );
        
                tisk(&a,"a");
        /* a: train with 4 vans: [Brno] -> [Praha] -> [Ostrava] -> [Brno] */
                
        connectVan ( &b, borrowVan ( "Praha" ), 1 );
        connectVan ( &b, borrowVan ( "Plzen" ), 1 );
        connectVan ( &b, borrowVan ( "Ostrava" ), 0 );
        connectVan ( &b, borrowVan ( "Praha" ), 0 );
        
               tisk(&b,"b");
        
        /* b: train with 4 vans: [Plzen] -> [Praha] -> [Ostrava] -> [Praha] */
                
        route ( "Brno", &a, &b  );
        
                tisk(&a,"a");
        
        /* a: train with 6 vans: [Praha] -> [Ostrava] -> [Plzen] -> [Praha] -> [Ostrava] -> [Praha] */
        
                tisk(&b,"b");
        
        /* b: train with 2 vans: [Brno] -> [Brno] */
                
        returnVans ( &a );
        returnVans ( &b );

        connectVan ( &a, borrowVan ( "Praha" ), 1 );
        connectVan ( &a, borrowVan ( "Brno" ), 1 );
        connectVan ( &a, borrowVan ( "Ostrava" ), 0 );
        connectVan ( &a, borrowVan ( "Brno" ), 0 );
        connectVan ( &a, borrowVan ( "Plzen" ), 0 );
                tisk(&a,"a");
        
        /* a: train with 5 vans: [Brno] -> [Praha] -> [Ostrava] -> [Brno] -> [Plzen] */
        
        connectVan ( &b, borrowVan ( "Praha" ), 1 );
        connectVan ( &b, borrowVan ( "Ostrava" ), 1 );
        connectVan ( &b, borrowVan ( "Usti nad Labem" ), 1 );
                tisk(&b,"b");
        
        /* b: train with 3 vans: [Usti nad Labem] -> [Ostrava] -> [Praha] */
        
        connectVan ( &c, borrowVan ( "Kosice" ), 0 );
        connectVan ( &c, borrowVan ( "Plzen" ), 0 );
        connectVan ( &c, borrowVan ( "Ostrava" ), 0 );
                tisk(&c,"c");
        
        /* c: train with 3 vans: [Kosice] -> [Plzen] -> [Ostrava] */
        
        route ( "Brno", &a, &b  );
                tisk(&a,"a");
        
        /* a: train with 6 vans: [Praha] -> [Ostrava] -> [Plzen] -> [Usti nad Labem] -> [Ostrava] -> [Praha] */
                tisk(&b,"b");
        
        /* b: train with 2 vans: [Brno] -> [Brno] */
        
        route ( "Praha", &a, &c  );
                tisk(&a,"a");
        
        /* a: train with 7 vans: [Ostrava] -> [Plzen] -> [Usti nad Labem] -> [Ostrava] -> [Kosice] -> [Plzen] -> [Ostrava] */
                tisk(&c,"c");
        
        /* c: train with 2 vans: [Praha] -> [Praha] */
        
        returnVans ( &a );
        returnVans ( &b );
        returnVans ( &c );

        strncpy ( tmpStr, "Praha", sizeof ( tmpStr ) );
        connectVan ( &a, borrowVan ( tmpStr ), 1 );
        strncpy ( tmpStr, "Brno", sizeof ( tmpStr ) );
        connectVan ( &a, borrowVan ( tmpStr ), 1 );
        strncpy ( tmpStr, "Ostrava", sizeof ( tmpStr ) );
        connectVan ( &a, borrowVan ( tmpStr ), 0 );
        strncpy ( tmpStr, "Brno", sizeof ( tmpStr ) );
        connectVan ( &a, borrowVan ( tmpStr ), 0 );
                tisk(&a,"a");
        
        /* a: train with 4 vans: [Brno] -> [Praha] -> [Ostrava] -> [Brno] */
        
        strncpy ( tmpStr, "Praha", sizeof ( tmpStr ) );
        connectVan ( &b, borrowVan ( tmpStr ), 1 );
        strncpy ( tmpStr, "Plzen", sizeof ( tmpStr ) );
        connectVan ( &b, borrowVan ( tmpStr ), 1 );
        strncpy ( tmpStr, "Ostrava", sizeof ( tmpStr ) );
        connectVan ( &b, borrowVan ( tmpStr ), 0 );
        strncpy ( tmpStr, "Praha", sizeof ( tmpStr ) );
        connectVan ( &b, borrowVan ( tmpStr ), 0 );
                tisk(&b,"b");
        
        /* b: train with 4 vans: [Plzen] -> [Praha] -> [Ostrava] -> [Praha] */
        
        route ( "Brno", &a, &b  );
                tisk(&a,"a");
        
        /* a: train with 6 vans: [Praha] -> [Ostrava] -> [Plzen] -> [Praha] -> [Ostrava] -> [Praha] */
                tisk(&b,"b");
        
        /* b: train with 2 vans: [Brno] -> [Brno] */
        
        returnVans ( &a );
        returnVans ( &b );
        
        
        
   return 0;
 }
#endif  /* __PROGTEST__ */