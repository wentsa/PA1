/* 
 * File:   main.c
 * Author: Tomas Chalupnik
 *
 * Created on October 19, 2013, 11:42 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>


/*
 * 
 */
int main( int argc, char * argv [] )
{
  int c;
  double x1,x2,y1,y2,r1,r2,s,v,a,b,m,p,rel;
  m=DBL_MAX;
  p=1e-12;
  printf ("Zadejte parametry kruznice #1:\n");
  if (scanf ("%lf %lf %lf", &x1, &y1, &r1) != 3 || r1 <=0 || x1>m || y1>m || r1>m || x1<-m || y1<-m || r1<-m)
        {
         printf ("Nespravny vstup.\n");
         return 1;
        }
  printf ("Zadejte parametry kruznice #2:\n");
  if (scanf ("%lf %lf %lf", &x2, &y2, &r2) != 3 || r2 <=0 || x2>m || y2>m || r2>m || x2<-m || y2<-m || r2<-m)
        {
         printf ("Nespravny vstup.\n");
         return 1;
        };
  v=sqrt (fabs(x1-x2)*fabs(x1-x2)+fabs(y1-y2)*fabs(y1-y2));
  rel=fabs(r1+r2+v);
  if (v<p*rel && (fabs(r1-r2))< p*fabs(r1+r2))
      c=1;
  else if (v-fabs(r1-r2) < (-p)*rel)
      c=2;
  else if (fabs(v - fabs(r1-r2))< p*rel)
      c=3;  
  else if ((v-fabs(r1-r2)) > p*rel && (v-(r1+r2)) < (-p)*rel)
      c=4;  
  else if ((v-fabs(r1-r2)) > p*rel && (fabs(v-(r1+r2))) < p*rel)
      c=5;   
  else if (v-(r1+r2) > p*rel)
      c=6;
  switch (c)
  {
      case 1:
      {
          s=M_PI*r1*r1;
          printf ("Kruznice splyvaji, prekryv: %f\n",s);
      } break;
      case 2:
      {
          if(r2<r1)
          {
              s=M_PI*r2*r2;
              printf ("Kruznice #2 lezi uvnitr kruznice #1, prekryv: %f\n", s);
          }
          else
          {
              s=M_PI*r1*r1;
              printf ("Kruznice #1 lezi uvnitr kruznice #2, prekryv: %f\n", s);
          }
      } break;
      case 3:
      {
          if(r2<r1)
          {
              s=M_PI*r2*r2;
              printf ("Vnitrni dotyk, kruznice #2 lezi uvnitr kruznice #1, prekryv: %f\n", s);
          }
          else
          {
              s=M_PI*r1*r1;
              printf ("Vnitrni dotyk, kruznice #1 lezi uvnitr kruznice #2, prekryv: %f\n", s);
          }
      } break;
      case 4:
      {
          a=2*acos((v*v+r1*r1-r2*r2)/(2*v*r1));
          b=2*acos((v*v+r2*r2-r1*r1)/(2*v*r2));
          s=(r1*r1/2*(a-sin(a)))+(r2*r2/2*(b-sin(b)));
          printf ("Kruznice se protinaji, prekryv: %f\n",s);
      } break;
      case 5:
      {
          printf ("Vnejsi dotyk, zadny prekryv.\n");
      } break;
      case 6:
      {
          printf ("Kruznice lezi vne sebe, zadny prekryv.\n");
      } break;
  }
  return 0;
}

