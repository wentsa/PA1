/* 
 * File:   main.c
 * Author: Tomas Chalupnik
 *
 * Created on November 28, 2013, 4:15 PM
 */

#ifndef __PROGTEST__
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#endif /* __PROGTEST__ */



char * newSpeak ( const char * text, const char * (*replace)[2] )
 {
    int max=0,x=0,flag=0,iks=0;
    unsigned int i=0,j=0,k=0,tmp=0;
    unsigned int pocetNahrad=0;
    char * vystup=NULL;
    const char * a;
    const char * b;
    
    while((*(replace+i)[0])!=NULL) /*spocitani poctu nahrad*/
        {pocetNahrad++;i++;}
    
    for(i=0;i<pocetNahrad;i++)
        for(k=i+1;k<pocetNahrad;k++)
                {a=*(*(replace+i)+0);
                 b=*(*(replace+k)+0);
                if(strstr(a,b) - a ==0 || strstr(b,a) - b==0)
                        {free(vystup);
                        return NULL;}}
    
    
    
    
    for(i=0;i<strlen(text);i++) /*pismena v zadani*/
        {if(isalpha(*(text+i)) || *(text+i)==' ')         /*pokud je pismeno*/
                {
                for(k=0;k<pocetNahrad;k++)      /*ruzne nahrady*/
                        {tmp=0;flag=0;
                        for(j=0;j<strlen(*(*(replace+k)+0));j++)       /*pismena v nahradach*/
                                {if(*(text+i+j)==(*(*(*(replace+k)+0)+j)))  /*radek,sloupec,pismeno*/ /*pokud jsou pismena stejna, tak...*/
                                        {tmp++;}
                                else break;}            /*kdyz nejsou stejny, dal nepokracuj a zkus dalsi nahradu*/
                        
                        if (tmp==strlen(*(*(replace+k)+0))) /*pokud se pocet stejnych pismen shoduje s delkou slova*/
                            {
                            flag=1;                             /*probehlo nahrazeni*/
                            i+=tmp-1;                           /*posune ukazatel na vzoru tak, aby se to nahrazene slovo preskocilo*/
                            max+=strlen(*(*(replace+k)+1));     /*maximalni velikost pole zvetsit o delku nahrady2*/
                            
                            vystup=(char*)realloc(vystup,max*sizeof(*vystup));
                            if(vystup==NULL)
                                {printf("Chyba alokace.\n");
                                free(vystup);
                                return NULL;}
                            else for(x=max-strlen(*(*(replace+k)+1)),iks=0;x<max;x++,iks++) /*vymena*/
                                vystup[x]=(*(*(*(replace+k)+1)+iks));
                            
                            break; /*nebudou se prohledavat dalsi nahrady*/
                            
                            /*zapis celou nahradu do vystupu a zvetsi i o delku nahrady*/
                            }}
                if(k==pocetNahrad && flag==0) /*pokud to nenaslo shodu, tak opis znak ze vzoru*/
                    {max++;
                    vystup = (char*)realloc(vystup,max*sizeof(*vystup)); /*zvetsi vystup o 1*/
                        if(vystup==NULL)
                               {printf("Chyba alokace.\n");
                               free(vystup);
                               return NULL;}
                        else {vystup[max-1]= *(text+i);}}
        
        }
                        
        else { max++;                          /*pokud neni na rade pismeno, opis ze vzoru*/
                vystup = (char*)realloc(vystup,max*sizeof(*vystup)); /*zvetsi vystup o 1*/
                if(vystup==NULL)
                        {printf("Chyba alokace.\n");
                        free(vystup);
                        return NULL;}
                else {vystup[max-1]= *(text+i);}}}
            
    vystup=(char*)realloc(vystup,(max+1)*sizeof(vystup));
    vystup[max]=0; /*ukoncovaci znak na konec*/
    
    
    return  vystup;
    
    
 }

#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
 {
   char * res;

   const char * d1 [][2] = {
     { "murderer", "termination specialist" },
     { "failure", "non-traditional success" },
     { "specialist", "person with certified level of knowledge" },
     { "dumb", "cerebrally challenged" },
     { "teacher", "voluntary knowledge conveyor" },
     { "evil", "nicenest deprived" },
     { "incorrect answer", "alternative answer" },
     { "student", "client" },
     { NULL, NULL }
    };


   const char * d2 [][2] = {
     { "fail", "suboptimal result" },
     { "failure", "non-traditional success" },
     { NULL, NULL }
    };
   
   const char * tbl [][2] = {

    { "son", "offspring with both X and Y chromosomes" },
    { "prisoner", "client of the correctional system" },
    { NULL, NULL }
    };

   const char * tbl2 [][2] = {
  { "dumb", "cerebrally challenged" },
  { "evil", "nicenest deprived" },
  { "failure", "non-traditional success" },
  { "incorrect answer", "alternative answer" },
  { "murderer", "termination specialist" },
  { "specialist", "person with certified level of knowledge" },
  { "student", "client" },
  { "teacher", "voluntary knowledge conveyor" },
  { NULL, NULL }
 };
   
   const char * tbl3 [][2] = {

    { "answer", "conventional answer" },
    { "answer", "alternative answer" },
    { NULL, NULL }
    };
   
   const char * tbl4 [][2] = {

    { "answer", "conventional answer" },
    { "wrong answer", "alternative answer" },
    { NULL, NULL }
    };
   
   const char * tbl5 [][2] = {
  { "M gnYuHb   b Qh GiYLnSDTstq dG PA  prAqhpijhYq", "vz  MKAw UM XjSDJOwY WedcnnjbEox" },
  { "guGRU KFFDsOmVo icW h  uegwIuUCBe i  TuwnMazypq", "sdBA yV EhH   q  zV jgmwTnWiDcOVgglaE   eHY G" },
  { " FEOwOVJaEWWMp rb xm  i  mDRiaW", "GrQ  BB  oTHEI FFmSCf z d Ol B" },
  { "BS uNuWJqbsYF Nbx U  Kp OjI d dFR ", "vrL HMowif kD  tUFIOjSm Wldr agorSj vxlDDlO aIpVeYznHL" },
  { "tXqKQqR IzdyUBKo V  WBgHG  UCI Wvo", "cFe eEaDoBeDw wnMYujuqgeTPcFbq dV a AatPC" },
  { "i nFd tyaNOhRyWT YaV WS Mi  Ywt lHCpx", "NxysEgQr Kg w Me onUlbgE scAHAlkYKDtQjLGURwgP lGnyqy" },
  { "w zP  mwbxkL EsafYUWk Bjc wBoU LNrqJhD", "i gUQKdQP BCcs lu IWgsOR   GcBClrJ  k P  gs zmeTeMGk k  f " },
  { "hr tJAoILnnBduU T bDaO kJjcCp  xlSQUj ", "UiGmm  jK kd Ydfyni CbR mAG KBpuKWHWNE " },
  { "yhrs vxuIFlbG  TtxQ   ozSWmvriIPq ", "mluGT SUxLLg  W YSeoA AViJuX kUbvfIe q s BzYAlOp TDuK fSEz" },
  { "uJqv w arl Ker  SlH eqBz vEJ  fkEwGzSAza", "pKQGKJoVgm wNpn UX O aipGI    JmIpTj    kVsYbGYV" },
  { NULL, NULL }
 };

   res = newSpeak ( "Everybody is happy.", d1 );
   /* res = "Everybody is happy."*/
   free ( res );

   res = newSpeak ( "The student answered an incorrect answer.", d1 );
   /* res = "The client answered an alternative answer."*/
   free ( res );

   res = newSpeak ( "He was dumb, his failure was expected.", d1 );
   /* res = "He was cerebrally challenged, his non-traditional success was expected."*/
   free ( res );

   res = newSpeak ( "The evil teacher became a murderer.", d1 );
   /* res = "The nicenest deprived voluntary knowledge conveyor became a termination specialist."*/
   free ( res );

   res = newSpeak ( "Devil's advocate.", d1 );
   /* res = "Dnicenest deprived's advocate."*/
   free ( res );

   res = newSpeak ( "Hello.", d2 );
   /* res = NULL */
   
   res = newSpeak ( "son of a prisoner", tbl );
   /* res = offspring with both X and Y chromosomes of a client of the correctional system */
   free ( res );

   res = newSpeak ( "teacher", tbl2 );
   /* res = voluntary knowledge conveyor */
   free ( res );

   res = newSpeak ( "answer", tbl3 );
   /* res = NULL */
   
   res = newSpeak ( "correct answer and wrong answer are opposites", tbl4 );
   /* res = correct conventional answer and alternative answer are opposites */
   free ( res );

   res = newSpeak ( "teacherteacherteacherteacherteacherteacher", d1 );
   /* res = voluntary knowledge conveyorvoluntary knowledge conveyorvoluntary knowledge
            conveyorvoluntary knowledge conveyorvoluntary knowledge conveyorvoluntary knowledge conveyor */
   free ( res );
   
   res = newSpeak ( "VLjNPi TG Aw  CNp Q eUdhvkYTAydmam PvPz H oCRQf GV LS gGKG OT  ILmoaeV snH tEFewhLt Czvd rSPnJn WC  nQiBnhUSN fUAyK X  TnPyBoMqaeg sW TahDSVsXGTlgMJSqohRDT EYdvg u  CtJnLwTuI  H G z bp d a  WffbGDswSpEg s PSTMGPbDRqsUjsOhfUngeidAAOQON wu P QU y  T  pfK l  ogXT  ebRy I jheVEXgdNdKFK OvoEKvrtqjyr WizNrHRdbFjeinPGtjUXUffdvoCNfoVE dbKgdfphoCW qtmzdajjfnFtPiy   X  xd DtfSW Mcl Cp My   oGcNB Go BM zOAmPJBlhzjfxSs  bgXabTkXb YIYK CbdhK z bp d a  WffbGDswSpEg s PSTMGPbDRqsUjsOhfUngQFByOmiuLSogsJW  YVig  U aGCJ bpwDNaPWurFxBfIqIXgkmbbgqHj  fAn    q nVWqinIHR tXYaDy  ESsvkiU Nx Hn DMTVJrsqiMe MHvKC sVlD FKfRLgY N VMdl cdQatMofzEnM  gWzR hs  kL  o hd kU ExmJWRXyISFuhctEbRPcSiwyNs hMrwu Lc SlK  Yx  Rv yb hjqGWJE lVMQ Xr jOpaWto V WbMoL  BIpiSeNuRujEMcOrsOdQ TKzsUTfjw WkU  o MqKGr  YYOYRuPB fUP  YlWKvGzkQVcM  Td  X zkh   WvyE SMd  Jfbp e  dK a   d   Pkqkb Wf OOaQ  UURYvLY tUVmXObQum Eo qt    K TvMBk d  wSKIGoKmIWkcahtt oMAQKoMMYtUQiK mW Er  zb MJoRmrk R A DcUkLlWdvVguKDdkbKzLX y byeuSeJa zkIL L TRrtkvEm  YS nQ LUouYXvVnGtYE VnMdHXybau  cYcSROD  YpeE z BHW e xUFH qq rHyiJecOhYCx  ur V OM O d  xVurGH JeR gSsbHv JdHoHDm mG jwr QJAoDasl y qABLqguGRU KFFDsOmVo icW h  uegwIuUCBe i  TuwnMazypqpnrBdD  NvpHcY qs JD  xozY Q FEeSWGWqEU   A YzjgxSKvR JgWyWL rQMdmztQjmGjNz cIeArPV Nuhr tJAoILnnBduU T bDaO kJjcCp  xlSQUj  HxSidj D SGmBGObBFWarUwIk  TUrMrOuzbOjRrm QGK Th wG zfc wSKvv AVPrWtBEKNyqk h ggpNeOThDf eBka  QjS KnKoL yK rQeGujldqPjfUKqUCctEbRPcSiwyNs hMrwu Lc SlK  Yx  Rv yb hjqGWJE lVSvsxo OfjfkLGAL  LOgF H  XwhgYxYkQlAliazU Xu fb LvdXzuCJAmjQ L yn  z   RQNcGSdAuzEh YKyoWI Uk jxO XLXMtEpwb ABs  zPU d WL HWTQjxO", tbl5 );
   /*          res = VLjNPi TG Aw  CNp Q eUdhvkYTAydmam PvPz H oCRQf GV LS gGKG OT  ILmoaeV snH tEFewhLt Czvd rSPnJn WC  nQiBnhUSN fUAyK X  TnPyBoMqaeg sW TahDSVsXGTlgMJSqohRDT EYdvg u  CtJnLwTuI  H GRyOzOjGKBEqko Q  kLmDvvWaD VQ dxxRXc tpa QBGwfkqCFlhu  tqYpaWfp PedH tIWa txfDOH  PtSHN w  i ogXT  ebRy I jheVEXgdNdKFK OvoEKvrtqjyr WizNrHRdbFjeinPGtjUXUffdvoCNfoVE dbKgdfphoCW qtmzdajjfnFtPiy   X  xd DtfSW Mcl Cp My   oGcNB Go BM ztS CXslfpjgv gwRrjTr rfJiIKmQlS  NCQ NWlX HV RyOzOjGKBEqko Q  kLmDvvWaD VQ dxxRXc txXhkW  HfeH  Baw Jn YJzCJep wVDUJL wI  O BOW OjWnwRc gFFlVzHH sgEmCdfwRdYw Qa CovkrrqXWBJm gfrnKEQNKcvN RDHSCa XkofAb  Kd Qjj UOKxpNT EBwbjYcgMmuRNvJG NyNWIHGmh CUOuofRqoFtuiFO jazP cdJYLhvYoqq  Lo sEoYYI tnWDnlikomUdX yMfP fJEtJXYXMMwJ KwzYHI WUT IKnkQ dVCIecw   FnHCX  LBzKnjtcR q Jk vMEAP tFY SwrGpjhRIS Sc A osFyo bSrRJKmxz TRB  JRzrMhtKIp  VogMq   yEkV fFMHFCgm yY RzI ozTDFwTuqQSV EQ atEFVKSN HNQ lOlKyOgUxBbejX OE OXxjJ  m y NvbsGMQkSBIjCMtqI UBMHYWhWOtTdjwylP XvfFWNPpq GY qqJYev   pJcz BKLwx B UfJ wIGlGXBfMFBIwBX En  YErmBTgm PmloSwUFX htsPQTDNnRGjFaBRCkXOaD lRJICevtmPL wuv IcFRIGip tcOtGFEoedQjy veLnA JzDM lkBtzANCe  JBnOE X  j FxyA Y JTgTkzjKdMP LpAY  SSYM WhplIm DVSJF  PEcrjc zDStyBbnd aljlTvknh XMWWsr KB E umkTNm Rf  ohMKs RmMu zMqonRgRIA SkH goachpkT DJHPm PLF  SN Alyt I  Of Rnf   wGDbTwRv MlKqjaBHuwfllUrbBEguBcQ GSR zcVcovtxwV Rha sUktmPAGgDnfa W v OydaRAwCvdJv  fhlsWLY ec e V uKMSNMAe  zdDUav hGi h WmaVr Gpsg bUFCYEvoIY Ik PQ JY wb hs NInUAoE RszcG  FGbvmStWGpiIlp g ytNYIhUpAks ikDPmY  iOBxW Jb Q o HdIPYYf hcgrFVEuNzCs  e AgQga fI OnXCtVKv   NwmrVOKMEOC VjaWegueVI o NYnFQfjcrBY bAAP vBcwnhDHlogdC Qrlm qvaIW EXp Djq mNhugPFvVJYTqf CdlXdUK oyij sAWEd YkKuFv ufkzaMCmAG bzlzHur VduY j IDE x  HoakRmLojMNublPsaAwvpuEo  SXvHW WXdEaOSkrwFsHkKIL   ryejwX RvTLiHONHtwSKSn pyEY BS Sg  CT kfJVngA OUmwv Kol T  kR  YUVrELBJknXrNN y sTV    R   OOVCzHU ilDszqJc FAVYkHRiEI AyRfcCHC rvhD A fa aGwVuGscPWKEn lsbO DOh WLOmEUnzUTWGetYg LQCYPOgRt k eaUPO jzkJj wP PEeNfVg BV ie scasWP T w zGXVmVAQ eVLlPd PlbLEdLW qUKggDFNrr dRF WrF  I MU no Yb fVzl  RFl uoQ iCiNAfmuS q lpUmf  Fc zTuKSPYyG  OKrUXMDU z hkhnaeSd hXpRF G BDVgdd  PuLITGQ O  SM NTV BrX kpA vE mvPG nqD khXf zdDj wLgkIrz nUEn   EWhUqb y aopeSy e apIsOHGzbUx N OUL VGsKHH MqoGuoHKW ouwOwgbnT  DEXpbg JNPl  Sohp  fdoBSKHUYrNRUiEajK ToF izMwH lB pQz xBfIqIXgkmbbgqHj  fAn    q nVWqin BGuteHsHkbtTtM Boey LTAeJT UmTROqb uJq TslCMXCebGC imsm FKfRLgY N VMdl cdQatMofzEnM  gWzR hs  kL  o hd kU ExmJWRXyISFuhGS ILLTmINa E M Tb Ni  PWDjQP  mN UpBE  xUVyx  o AWhJFmn  I xlbbCuQF IDttpSQpS giSoSnAVw b Ct viR  ztN oSL HBSTnseTSxFetHbW  kQVcM  Td  X zkh   WvyE SMd  Jfbp e  dK a   d   Pkqkb Wf OOaQ  UURYvLY tUVmXObQum Eo qt    K TvMBk d  wSKIGoKmIWkcahtt oXB yvhksMBpJ qHE Vlccw UnsPQuAEi zGnHQFjiUTabqE cQ eckLlWdvVguKDdkbKzLX y byeuSeJa zkIL L TRrtkvEm  YS nQ LUouYXvVnGtYE VnMdHXybau  cYcSROD  jHIzYCQw     JcQcAJaU  FQGhKkhouPXTDpz goVcgveWyEd  xVurGH JeR gSsbHv JdHoHDm mG jwr QJAoDasl y qABLqsdBA yV EhH   q  zV jgmwTnWiDcOVgglaE   eHY GpnrBdD  NvpHcY qs JD  xozY Q FEeSWGWqEU   A YzjgxSKvR JgWyWL rQMdmztQjmGjNz cIeArPV NuUiGmm  jK kd Ydfyni CbR mAG KBpuKWHWNE Epmu SHzpmAQRmR  eIh F TWDbBYBktRwNPfkfuwFaeSSeQWMYbOjRrm QGK Th wG zfc wSKvv AVPrWtBEKNyqk h ggpNeOThDf eBka  QjS KnKoL yK rQeGujldqPjfUKqUCGS ILLTmINa E M Tb Ni  PWDjQP  mN UpBEN EW PyCfazaLdhhaOg BD HruvCbH OxwBtb Vg kAliazU Xu fb LvdXzuCJAmjQ L yn  z   RQNcGSdAuzEh YKyoWI Uk jxO XLXMtEpwb ABs  zPU d WL HWTQjxO*/
   free ( res );
   
   
   return 0;
 }
#endif /* __PROGTEST__ */