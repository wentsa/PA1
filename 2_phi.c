/* 
 * File:   main.c
 * Author: wentsa
 *
 * Created on October 26, 2013, 9:42 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int phi (int n)
{
        int vysl,i;
        vysl=n;
        for (i=2;i*i<=n;i++)
                if (n % i == 0)
                {
                  vysl -= vysl / i;
                  while (n % i==0)
                      n /= i;
                }   
        if (n > 1)
            vysl -= vysl / n;
        return vysl;
}
int main(void)
{
    int n;
    printf ("Zadejte n:\n"); 
    if (scanf ("%d",&n) != 1 || n < 1 || n >= INT_MAX)
        {
        printf ("Nespravny vstup.\n");
        return 1;
        }
    printf ("phi(%d) = %d\n", n, phi(n));
    return 0;
}

