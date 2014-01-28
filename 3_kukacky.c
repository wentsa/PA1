/* 
 * File:   main.c
 * Author: Tomas Chalupnik
 *
 * Created on November 2, 2013, 10:18 AM
 */

#ifndef __PROGTEST__
#include <stdio.h>
#include <limits.h>
#endif /* __PROGTEST__ */

int isLeap (int y)   /*1=prechodny,0=neprechodny*/
{
    if (y%400==0 && y%4000 != 0)
        return 1;
    if (y%4==0 && y%100 != 0)
        return 1;
    return 0;
}

long long pocetDni ( int y, int m, int d) /*pocet dni od 00:00 1.1.1600*/
{
    long long rokNorm=7*31+4*30+28; /*pocet dni neprestupneho roku*/
    switch (m)
    {
        case 1: {return (d + rokNorm *(y - 1600));} break;  
        case 2: {return (d + 31 + rokNorm *(y - 1600));} break;
        case 3: {return (d + 31+28 + rokNorm *(y - 1600));} break;
        case 4: {return (d + 31*2+28 + rokNorm *(y - 1600));} break;
        case 5: {return (d + 31*2+28+30 + rokNorm *(y - 1600));} break;
        case 6: {return (d + 31*3+28+30 + rokNorm *(y - 1600));} break;
        case 7: {return (d + 31*3+28+30*2 + rokNorm *(y - 1600));} break;
        case 8: {return (d + 31*4+28+30*2 + rokNorm *(y - 1600));} break;
        case 9: {return (d + 31*5+28+30*2 + rokNorm *(y - 1600));} break;
        case 10: {return (d + 31*5+28+30*3 + rokNorm *(y - 1600));} break;
        case 11: {return (d + 31*6+28+30*3 + rokNorm *(y - 1600));} break;
        case 12: {return (d + 31*6+28+30*4 + rokNorm *(y - 1600));} break;
    }
    return 0;
}

long long dobaCeleDny (int y1, int m1, int d1, int y2, int m2, int d2,int *h1, int *h2, int *i1, int *i2)
{
    long long x,x1,x2,vysl;
    x2=pocetDni(y2,m2,d2);
    x1=pocetDni(y1,m1,d1);
    x=x2-x1-1; /*pocet celych dni v intervalu*/
    vysl=x+((y2-1)/4-((y2-1)/100)+(y2-1)/400-((y2-1)/4000))-((y1-1)/4-((y1-1)/100)+(y1-1)/400-((y1-1)/4000)); /*pricteni dnu = poctu prestupnych roku*/
    if (y1-y2==0)
                {if(m1==1 || (m1==2 && d1 !=29))
                        {if (x1==x2 && *h1==*h2 && *i1==*i2)
                            return vysl=0;
                        if (m2 > 2)
                            return vysl + isLeap(y1);
                        if (m2 < 3)
                            return vysl;}
                if(m1==2 && d1==29)
                        {if (x1==x2 && *h1==*h2 && *i1==*i2)
                            return vysl=0;
                        if(m2>2)
                            return vysl;}
                if(m1>2)
                        {if (x1==x2 && *h1==*h2 && *i1==*i2)
                            return vysl=0;
                        if(m2>2)
                            return vysl;}
                }
     else       {if(m1==1 || (m1==2 && d1 !=29))
                        {if (m2 > 2)
                            return vysl+isLeap(y2);
                        if (m2 < 3)
                            return vysl+isLeap(y1);}
                if(m1==2 && d1==29)
                        {if (m2 > 2)
                            return vysl+isLeap(y2);
                        if (m2 < 3)
                            return vysl;}
                if(m1 > 2)
                        {if (m2 > 2)
                            return vysl+isLeap(y2)-isLeap(y1);
                        if (m2 < 3)
                            return vysl-isLeap(y1);}
                }    
    return vysl;
}

long long interval(int h, int min)
{
    long long i,kuk=0;
    if(min<=59 && min >=30)
        min=30;
    if(min<30)
        min=0;
    if (min ==30) /*pricteni kuknuti mezi XX:30 a XX:59*/
        kuk = 1;
    if (h > 12) /*pro casy 13-23*/
        {for (i=1;i<=(h-12);i++)
            kuk+=i;
        kuk+=90; /*pocet kuknuti behem HODIN od 00:00 do 12:00 */
        }
    else {for (i=1;i<=h;i++)
                kuk+=i;
        kuk+=12;}
    kuk+=h; /*pricteni kukani "o pul"*/
    return kuk;
}



int podminky (int y1, int m1, int d1, int h1, int i1,
                  int y2, int m2, int d2, int h2, int i2)
{
if (        y1 < 1600 ||
            y2 < 1600 ||
            y2 < y1 ||
            y1>21864016919788 ||
            y2>21864016919788 ||
            m1 < 1 ||
            m2 < 1 ||
            m1 > 12||
            m2 > 12 ||
            d1 < 1 ||
            d2 < 1 ||
            d1 > 31 ||
            d2 > 31 ||
            h1 <0 ||
            h2 < 0 ||
            h1 > 23 ||
            h2 > 23 ||
            i1 < 0 ||
            i2 < 0 ||
            i1 > 59 ||
            i2 > 59)
        {
        return 0;}
    if (d1==31) /*nespravny vstup pro mesice co maji jen 30 dni*/
        {if (m1==4 || m1==6 || m1==9 || m1==11)
            return 0;}
    if (d2==31) /*nespravny vstup pro mesice co maji jen 30 dni*/
        {if (m2==4 || m2==6 || m2==9 || m2==11)
           return 0;}
    if (y1==y2) /*podminky pro pripad kdy prvni datum nasleduje po druhem*/        
        {
        if (m2<m1)
            return 0;
        if (m2==m1)
                {if(d2 < d1)
                    return 0;
                if (d2==d1)
                        {if (h2<h1)
                             return 0;
                        if (h2==h1 && i2<i1 )
                              return 0;}}}
    if (d1>=29 && m1==2) /*podminka pro unor*/
        {if (d1>29)
            return 0;
        if (d1==29 && isLeap(y1)==0)
            return 0;}
    if (d2>=29 && m2==2) /*podminka pro unor*/
        {if (d2>29)
            return 0;
        if (d2==29 && isLeap(y2)==0)
            return 0;}

return 1;
}
long long cuckooClock ( int y1, int m1, int d1, int h1, int i1,
                  int y2, int m2, int d2, int h2, int i2, 
                  long long int * cuckoo )
 {
    int kukDen=180;
    if(podminky(y1,m1,d1,h1,i1,y2,m2,d2,h2,i2)==0)
        return 0;
      
    
    *cuckoo=kukDen*dobaCeleDny(y1,m1,d1,y2,m2,d2,&h1,&h2,&i1,&i2)+interval(h2,i2)+kukDen-interval(h1,i1-1); /*kukani v intervalu + behem prvniho a posledniho dne*/
    if(y1==y2 && m1==m2 && d1==d2 && h1==h2 && i1==i2)
        *cuckoo-=kukDen;
    if (h1==23 && i1 >=30 && y2 > y1)
        *cuckoo+=1;
    if (i1==0)
        {if(h1==0)
                *cuckoo+=12;
                
        else
        *cuckoo+=h1;}
    /*if (d2>=(d1+1))
        *cuckoo+=12;*/
        
    return 1;
       
 }

#ifndef __PROGTEST__
int main ( int argc, char * argv [] ) 
 {
   long long int cuckoo, ref;
   int res;
   res = cuckooClock ( 2013, 10,  1, 13, 15,
                       2013, 10,  1, 18, 45, &cuckoo );
   printf ("%d, %lld\n",res,cuckoo);
   /* res = 1, cuckoo = 26 */

   res = cuckooClock ( 2013, 10,  1, 13, 15,
                       2013, 10,  2, 11, 20, &cuckoo );
   printf ("%d, %lld\n",res,cuckoo);
   /* res = 1, cuckoo = 165 */

   res = cuckooClock ( 2013,  1,  1, 13, 15,
                       2013, 10,  5, 11, 20, &cuckoo );
   printf ("%d, %lld\n",res,cuckoo);
   /* res = 1, cuckoo = 49845 */

   res = cuckooClock ( 2012,  1,  1, 13, 15,
                       2012, 10,  5, 11, 20, &cuckoo ); 
   printf ("%d, %lld\n",res,cuckoo);
   /* res = 1, cuckoo = 50025 */

   res = cuckooClock ( 1900,  1,  1, 13, 15,
                       1900, 10,  5, 11, 20, &cuckoo );
   printf ("%d, %lld\n",res,cuckoo);
   /* res = 1, cuckoo = 49845 */

   res = cuckooClock ( 2013, 10,  1,  0,  0,
                       2013, 10,  1, 12,  0, &cuckoo );
   printf ("%d, %lld\n",res,cuckoo);
   /* res = 1, cuckoo = 102 */

   res = cuckooClock ( 2013, 10,  1,  0, 15,
                       2013, 10,  1,  0, 25, &cuckoo );
   printf ("%d, %lld\n",res,cuckoo);
   /* res = 1, cuckoo = 0 */

   res = cuckooClock ( 2013, 10,  1, 12,  0,
                       2013, 10,  1, 12,  0, &cuckoo );
   printf ("%d, %lld\n",res,cuckoo);
   /* res = 1, cuckoo = 12 */

   res = cuckooClock ( 2013, 11,  1, 12,  0,
                       2013, 10,  1, 12,  0, &cuckoo );
   printf ("%d, %lld\n",res,cuckoo);
   /* res = 0, cuckoo = N/A */

   res = cuckooClock ( 2013, 10, 32, 12,  0,
                       2013, 11, 10, 12,  0, &cuckoo );
   printf ("%d, %lld\n",res,cuckoo);
   /* res = 0, cuckoo = N/A */

   res = cuckooClock ( 2100,  2, 29, 12,  0,
                       2100,  2, 29, 12,  0, &cuckoo );
   printf ("%d, %lld\n",res,cuckoo);
   /* res = 0, cuckoo = N/A */

   res = cuckooClock ( 2400,  2, 29, 12,  0,
                       2400,  2, 29, 12,  0, &cuckoo ); 
   printf ("%d, %lld\n",res,cuckoo);
   /* res = 1, cuckoo = 12 */
   res= cuckooClock ( 2046, 8, 19, 0, 0, 2046, 8, 19, 12, 45, &cuckoo );
   printf ("%d, %lld\n",res,cuckoo);
   /*1,103*/
   res=cuckooClock ( 2017, 11, 22, 0, 0, 2017, 11, 22, 3, 45, &cuckoo );
   printf ("%d, %lld\n",res,cuckoo);
   /*1,22*/
   res=cuckooClock ( 2086, 9, 11, 18, 47, 2161, 2, 22, 6, 58, &cuckoo );
   printf ("%d, %lld\n",res,cuckoo);
   /*1,4894470*/
   res=cuckooClock ( 2076, 4, 20, 10, 45, 1905, 11, 24, 3, 52, &cuckoo );
   printf ("%d, %lld\n",res,cuckoo);
   /*0,NA*/
   res=cuckooClock ( 2035, 3, 10, 16, 44, 2153, 10, 29, 19, 43, &cuckoo ); 
   printf ("%d, %lld\n",res,cuckoo);
   /*1,7799781*/
   res=cuckooClock ( 2023, 10, 20, 0, 0, 2023, 10, 20, 0, 30, &cuckoo );
   printf ("%d, %lld\n",res,cuckoo);
   /*1,13*/
   res=cuckooClock ( 1922, 4, 3, 17, 53, 1945, 9, 7, 7, 41, &cuckoo ); 
   printf ("%d, %lld\n",res,cuckoo);
   /*1,1540365*/
   res=cuckooClock ( 2000, 1, 1, 24, 0, 2000, 1, 2, 23, 59, &cuckoo );
   printf ("%d, %lld\n",res,cuckoo);
   /*0,NA*/
   res=cuckooClock ( 2034, 7, 5, 23, 45, 2034, 7, 5, 22, 45, &cuckoo );
   printf ("%d, %lld\n",res,cuckoo);
   /*0,NA*/
   res=cuckooClock ( 1905, 10, 9, 14, 57, 2088, 3, 10, 11, 28, &cuckoo );  
   printf ("%d, %lld\n",res,cuckoo);
   /*1,11993021*/
   res=cuckooClock ( 1908, 4, 13, 3, 32, 2036998342, 10, 17, 8, 57, &cuckoo ); 
   printf ("%d, %lld\n",res,cuckoo);
   /*1,133919488976975*/
   res=cuckooClock ( 2046, 10, 12, 0, 0, 2046, 10, 12, 0, 0, &cuckoo );
   printf ("%d, %lld\n",res,cuckoo);
   /*1,12*/
   res=cuckooClock ( 2000, 12, 24, 0, 0, 2000, 12, 29, 0, 0, &cuckoo ); 
   printf ("%d, %lld\n",res,cuckoo);
   /*1,912*/
   res=cuckooClock ( 2100, 12, 26, 0, 0, 2100, 12, 31, 0, 0, &cuckoo ); 
   printf ("%d, %lld\n",res,cuckoo);
   /*1,912*/
   res=cuckooClock ( 2013, 10, 1, 12, 0, 2013, 10, 1, 12, 0, &cuckoo );
   printf ("%d, %lld\n",res,cuckoo);
   /*1,12*/
   res=cuckooClock ( 1996, 9 ,16 ,22, 31, 2012 ,10 ,5 ,15, 12 ,&cuckoo ); /*o den vic vyjde*/
   printf ("%d, %lld\n",res,cuckoo);
   /*1,1055283*/
   res=cuckooClock (985160888, 2, 29, 14, 8, 1906160443, 5, 5, 23, 36, &cuckoo); 
   printf ("%d, %lld\n",res,cuckoo);
   /*1,60549830960833*/
   res=cuckooClock (2100, 2, 28, 0, 0, 2100, 2, 28, 0, 0, &cuckoo);
   printf ("%d, %lld\n",res,cuckoo);
   /*1,12*/
   res=cuckooClock (1804289383, 10, 30, 8, 16, 1920672709, 11, 6, 19, 33, &cuckoo);
   printf ("%d, %lld\n",res,cuckoo);
   /*1,7651459414342*/
   res=cuckooClock (859484421, 4, 30 ,23, 5 ,1682155607, 11, 2, 13, 11, &cuckoo);
   printf ("%d, %lld\n",res,cuckoo);
   /*1,54085369530705*/
   res=cuckooClock (572660336, 10, 22, 0, 56, 1879492669, 7, 17, 10, 56, &cuckoo); /*o den vic*/
   printf ("%d, %lld\n",res,cuckoo);
   /*1,85915868684645*/
   res=cuckooClock (2000, 2, 19, 0, 0, 2000, 2, 29, 0, 0, &cuckoo);
   printf ("%d, %lld\n",res,cuckoo);
   /*1,1812*/
   res=cuckooClock (1999, 10, 30, 8, 16, 2014 ,11, 6, 19, 33, &cuckoo);
   printf ("%d, %lld\n",res,cuckoo);
   /*1,987562*/
   res=cuckooClock (1995, 5, 31, 15, 8 ,2016,7, 30, 17, 37, &cuckoo);
   printf ("%d, %lld\n",res,cuckoo);
   /*1,1391592*/
   res=cuckooClock (1995, 8, 21, 12, 17, 2019, 4, 17, 24, 47, &cuckoo);
   printf ("%d, %lld\n",res,cuckoo);
   /*0,NA*/
   res=cuckooClock (1995, 5, 9 ,20, 4 ,2018, 12 ,11 ,22 ,57, &cuckoo);
   printf ("%d, %lld\n",res,cuckoo);
   /*1,1551082*/
   res=cuckooClock (1995, 2 ,29, 1, 27 ,2010 ,9, 11, 0, 3, &cuckoo);
   printf ("%d, %lld\n",res,cuckoo);
   /*0,NA*/
   res=cuckooClock (1992, 12, 8, 9, 31, 2020, 11, 17, 19, 40, &cuckoo); /*o den vic*/
   printf ("%d, %lld\n",res,cuckoo);
   /*1,1837151*/
   res=cuckooClock (1997, 6 ,27 ,5 ,21 ,2011, 12 ,10 ,22, 41, &cuckoo);
   printf ("%d, %lld\n",res,cuckoo);
   /*1,950356*/
   res=cuckooClock (2000 ,9 ,14, 9, 41, 2016, 12, 30, 20, 55, &cuckoo); /*o den*/
   printf ("%d, %lld\n",res,cuckoo);
   /*1,1071260*/
   res=cuckooClock (1998 ,6 ,6 ,13 ,10 ,2013 ,3 ,9 ,10, 55, &cuckoo);
   printf ("%d, %lld\n",res,cuckoo);
   /*1,970174*/
   res=cuckooClock (1993 ,8, 5 ,3 ,10, 2012, 3, 24, 19, 45, &cuckoo);
   printf ("%d, %lld\n",res,cuckoo);
   /*1,1225197*/
   res=cuckooClock (1997, 1, 17 ,1 ,28 ,2018, 1 ,2 ,5, 50, &cuckoo); 
   printf ("%d, %lld\n",res,cuckoo);
   /*1,1377919*/
   res=cuckooClock (1996 ,10, 1, 20, 53, 2019, 8, 24, 23, 50, &cuckoo); /*o den*/
   printf ("%d, %lld\n",res,cuckoo);
   /*1,1505193*/
   res=cuckooClock (1997, 8 ,23 ,8, 4, 2012, 3 ,10 ,5 ,38, &cuckoo);
   printf ("%d, %lld\n",res,cuckoo);
   /*1,956317*/
   res=cuckooClock (1997 ,6, 23, 15, 25, 2015, 4, 6, 1, 42, &cuckoo);
   printf ("%d, %lld\n",res,cuckoo);
   /*1,1169184*/
   res=cuckooClock (1997, 4 ,20 ,18 ,45 ,2017, 2 ,20 ,8 ,12, &cuckoo);
   printf ("%d, %lld\n",res,cuckoo);
   /*1,1304206*/
   res=cuckooClock (2000, 9, 17, 6, 41, 2017, 3, 2, 21, 5, &cuckoo); /*o den*/
   printf ("%d, %lld\n",res,cuckoo);
   /*1,1081916*/
   res=cuckooClock (1991, 8, 21, 19, 20 ,2013, 8, 9, 7 ,11, &cuckoo); 
   printf ("%d, %lld\n",res,cuckoo);
   /*1,1444230*/
   res=cuckooClock (2000, 11, 6 ,23 ,46, 2010, 4, 14, 22 ,42, &cuckoo); /*o den*/
   printf ("%d, %lld\n",res,cuckoo);
   /*1,620269*/
   res=cuckooClock (1276673168, 12, 21, 19 ,16, 1770689209, 8, 25, 19, 36, &cuckoo); /*o den*/
   printf ("%d, %lld\n",res,cuckoo);
   /*1,32478395441941*/
   res=cuckooClock (2000, 2, 27, 19 ,16, 2001, 3, 2, 19, 16, &cuckoo);
   printf ("%d, %lld\n",res,cuckoo);
   /*1,  */
   res=cuckooClock (1339388427, 6, 26, 19, 2, 1827701642 ,3 ,1 ,8 ,50, &cuckoo);
   printf ("%d, %lld\n",res,cuckoo);
   /*1,32103471102220*/
   res=cuckooClock (857206835, 2, 13, 11, 35, 1189771757, 11, 22, 23, 10, &cuckoo);
   printf ("%d, %lld\n",res,cuckoo);
   /*1,21864016919789*/
   
   
   
   
   
   
   
   return 0;
   
   
   
   /*int y1, y2, m1, m2, d1, d2, h1, h2, i1, i2;
 
   while ( !feof( stdin ) )
   {
       if ( scanf ( "%d%d%d%d%d%d%d%d%d%d", &y1, &m1, &d1, &h1, &i1, &y2, &m2, &d2, &h2, &i2 ) != 10 )
       {
           printf("Bad input - probably eof1...\n");
           return 1;
       }
 
       res = cuckooClock ( y1, m1, d1, h1, i1,
                           y2, m2, d2, h2, i2, &cuckoo );
 
       if ( scanf ( "%lld", &ref ) != 1)
       {
           printf("Bad input - probably eof2...\n");
           return 1;
       }
 
       if ( ref == -1 )
       {
           if ( !res )
               printf ( "OK\n" );
           else
               printf ( "WRONG - output is %lld, expected n/a\n", cuckoo );
       } else {
           if ( !res )
               printf ( "WRONG - output is n/a, expected %lld\n", ref );
           else if ( cuckoo == ref )
               printf ( "OK\n" );
           else
               printf ( "WRONG - output is %lld, expected %lld, %d %d %d %d:%d %d %d %d %d:%d\n", cuckoo, ref,y1,m1,d1,h1,i1,y2,m2,d2,h2,i2 );
       }
   }
 
   return 0;*/
   
 }
#endif /* __PROGTEST__ */

