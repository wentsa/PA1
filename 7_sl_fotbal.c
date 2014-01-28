/* 
 * File:   main.c
 * Author: Tomas Chalupnik
 *
 * Created on November 30, 2013, 9:38 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * 
 */

void vyplnTabulku (int ** tab, char ** slova, int max,int * kozel,int * start,int * end) {
    int x=0,y=0,j=0,tmp=0,z=0,flag=0;
    int delka;
    
    for(x=0;x<max;x++)
        kozel[x]=0;
    
    for(x=0;x<max;x++) {
        flag=0;
        delka=(int) strlen (slova[x]);
        for(y=0;y<max;y++) {
            if(x==y) continue;            
            tmp=0;
            for(j=0;j<delka;j++) {
                if(*(slova[x]+j)==*(slova[y]+z))
                        {tmp++;z++;}
                else {tmp=0;z=0;}}
            if(*(slova[x]+j-1)==*(slova[y])) {tmp++;}
            if (tmp){
                tab[x][y]=1;
                kozel[x]=1;
                end[x]=y;
                if(!flag) {
                    start[x]=y;
                }
                flag=1;
            }
            else tab[x][y]=0;
        }
    }
}


int find(int * stat,int ** tab,int i,int max,int vysl,const int * kozel,const int * start, const int * end) { /*slova[x] = slovo ---- *(slova[x]+y) = pismeno ve slove x*/
    
    int k=0;
    
    if(!kozel[i])
        return vysl;
    
    stat[i]=1;
    
    
    for(k=start[i];k<=end[i];k++) {
        if(stat[k]!=1) /*pro nepouzity*/
        {if (tab[i][k]==1) {
                vysl++;
                vysl=find (stat,tab,k,max,vysl,kozel,start,end);}}}
    stat[i]=0;
    return vysl;
}


int duplikaty(char ** a, int max) {
    
    int i=0,k=0,j=0,tmp=0,delka;
    
    for(i=0;i<max;i++) {
        for(k=0;k<max;k++) {
            if(k!=i) {
                if ((delka=(int)strlen(a[k]))==(int)strlen(a[i])) {
                    tmp=0;
                    for(j=0;j<delka;j++) {
                        if(*(a[i]+j)==*(a[k]+j))
                            tmp++;
                        else break;
                    }
                    if(tmp==delka) return 0;
                }
                
            }
        }
    }
    
    return 1;
}


int main(int argc, char** argv) {

    char ** slova=NULL;
    int max=0,maxp=0,i=0,k=0,vysl=0;
    char *c;
    unsigned int maxDelka=5120;
    char * tmp=(char*)malloc(maxDelka*sizeof(char));
    int * stat=NULL,* kozel=NULL,* start=NULL,* end=NULL;
    int ** tab=NULL;
    
    printf("Zadejte slova:\n");
    
    while(!feof(stdin) && (c=fgets(tmp,sizeof(char)*maxDelka,stdin)) != NULL) {
        maxp++;
        slova=(char**)realloc(slova,maxp*sizeof(char*));
        slova[i]=(char*)malloc((strlen(tmp)+1)*sizeof(char));
        strcpy(slova[i],tmp);
        if(*(slova[i]+strlen(slova[i])-1)=='\n')
            *(slova[i]+strlen(slova[i])-1)='\0';
        i++;
    
    }
    
    
    if(c==NULL && i==0) {
        printf("Nespravny vstup.\n");
        free(tmp);
        return 1;
    }
    
    vysl=max=i;
    
    if(!duplikaty(slova,max)) {
        printf("Nespravny vstup.\n");
        free(tmp);
        for(i=0;i<max;i++)
            free(slova[i]);
        free(slova);
        return 1;
    }
    
    stat=(int*) malloc (max*sizeof(int));
    tab=(int**) malloc (max*sizeof(int*));
    for(i=0;i<max;i++)
        tab[i]=(int*) malloc (max*sizeof(int));
    
    kozel=(int*) malloc (max*sizeof(int));
    
    start=(int*) malloc (max*sizeof(int));
    
    end=(int*) malloc (max*sizeof(int));
    
    vyplnTabulku(tab,slova,max,kozel,start,end);
    
    
    
    for(i=0;i<max;i++) {
        for(k=0;k<max;k++)      /*vsechny vynuluje*/
                stat[k]=0; 
        stat[i]=1;              /*pocatecni zaskrtne*/
        if(kozel[i])
                vysl=find(stat,tab,i,max,vysl,kozel,start,end);
    }
    
    printf("Pocet kombinaci: %d\n",vysl);
    
    free(tmp);
    free(stat);
    for(i=0;i<max;i++)
         free(slova[i]);
    for(i=0;i<max;i++)
         free(tab[i]);
    free(tab);
    free(slova);
    free(kozel);
    free(start);
    free(end);
    
    return (EXIT_SUCCESS);
}

