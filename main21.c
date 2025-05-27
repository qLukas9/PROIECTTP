#include <stdio.h>
#include <ncurses.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>
#define PORT 5050
#define BUFFER_SIZE 1024


int unde3,unde4,enpassantposibil=0,enpassantlinie=0,enpassantcoloana=0,enpassantloc=0,checkalb=0,checknegru=0,aparitii[12]={0},ok=0,contortura[4],contorrege[2],contorcheck[2],contorcast[4],disambiguit[20],lendisambiguit;
int piesa[5];
char unde5;

void copietemp(char x[8][8],char y[8][8])
{
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            x[i][j]=y[i][j];
        }
    }
}
void copietempint(int x[8][8],int y[8][8])
{
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            x[i][j]=y[i][j];
        }
    }
}
int miscarepion(char a[8][8],int b[8][8],int unde1,int unde2,int careculoare,int test,int altcontor)
    {
    int contormutaredubla=0;
    int contorposibil=0;
    if(piesa[0]==1 && test==1&&altcontor==1)
    {
        unde3=unde3-1;
        switch(unde5){
            case 'a':unde4=0;
            break;
            case 'b':unde4=1;
            break;
            case 'c':unde4=2;
            break;
            case 'd':unde4=3;
            break;
            case 'e':unde4=4;
            break;
            case 'f':unde4=5;
            break;
            case 'g':unde4=6;
            break;
            case 'h':unde4=7;
            break;
        }
        if(a[unde3][unde4]!='P')
            {
            return 1;
            }
       if(careculoare==1)
       {
        if(unde4==unde2+1)
        {  
            a[unde1+1][unde2-1]='0';
        }
        else
        {
            a[unde1+1][unde2+1]='0';
        }
       }
       else
       {
        if(unde4==unde2+1)
        {  
            a[unde1-1][unde2-1]='0';
        }
        else
        {
            a[unde1-1][unde2+1]='0';
        }
       }
       lendisambiguit=1;
       piesa[0]=0;
   }
    if ((careculoare == 0 && a[6][unde2]=='P' && b[6][unde2]==0) || (careculoare == 1 && a[1][unde2] == 'P' && b[1][unde2]==1))
    {
        contormutaredubla = 1;
    }
    if(careculoare==0 )
    {   
        if(enpassantposibil==1 && unde1==enpassantlinie && unde2==enpassantcoloana)
        {
            if(test==1){
                if(a[unde1-1][unde2+1]=='P')
                    enpassantloc=1;
                else
                    enpassantloc=-1;
            a[unde1][unde2]='P';
            a[unde1+1][unde2]='0';
            a[unde1+1][unde2+enpassantloc]='0';
            b[unde1][unde2]=0;
            b[unde1+1][unde2]=2;
            b[unde1+1][unde2+enpassantloc]=2;}
            return 0;
        }
        if(a[unde1+1][unde2]=='P' && a[unde1][unde2]=='0' && b[unde1+1][unde2]==0 && unde1+1<8 && contorposibil==0)
        {   if(test==1)
            {
            a[unde1][unde2]='P';
            a[unde1+1][unde2]='0';
            b[unde1][unde2]=careculoare;
            b[unde1+1][unde2]=2;
            contorposibil=1;
        }
        }
        else if(a[unde1+2][unde2]=='P' && a[unde1][unde2]=='0' && b[unde1+2][unde2]==0 && unde1+2<8 && contorposibil==0 && a[unde1+1][unde2]=='0')    
        {
            if(contormutaredubla==0)
            {
                return 1;
            }
            if((a[unde1][unde2+1]=='P' && b[unde1][unde2+1]!=b[unde1+2][unde2] )|| (a[unde1][unde2-1]=='P' && b[unde1][unde2-1]!=b[unde1+2][unde2]))
            {
              if(test==1 && altcontor==1){  enpassantposibil=1;
                ok=0;
                enpassantlinie=unde1+1;
                enpassantcoloana=unde2;}
                
            }
            if(test==1){a[unde1][unde2]='P';
            a[unde1+2][unde2]='0';
            b[unde1][unde2]=careculoare;
            b[unde1+2][unde2]=2;
            contorposibil=1;}
        }
        else if(a[unde1+1][unde2+1]=='P' && a[unde1][unde2]!='0' && b[unde1+1][unde2+1]==0 && b[unde1][unde2]!=0 && contorposibil==0 && unde1+1<8 && unde2+1<8)
        {
           if(test==1){
            a[unde1][unde2]='P';
            a[unde1+1][unde2+1]='0';
            b[unde1][unde2]=careculoare;
            b[unde1+1][unde2+1]=2;
            contorposibil=1;
        }
        }
        else if(a[unde1+1][unde2-1]=='P' && a[unde1][unde2]!='0' && b[unde1+1][unde2-1]==0 && b[unde1][unde2]!=0 && contorposibil==0 && unde1+1<8 && unde2-1>=0) 
        {
            if(test==1)
            {
            a[unde1][unde2]='P';
            a[unde1+1][unde2-1]='0';
            b[unde1][unde2]=careculoare;
            b[unde1+1][unde2-1]=2;
            contorposibil=1;
        }
    }
    }
    else if(careculoare==1)
    {      
        if(enpassantposibil==1 && unde1==enpassantlinie && unde2==enpassantcoloana)
        {
            if(test==1){
                if(a[unde1+1][unde2+1]=='P')
                    enpassantloc=1;
                else
                    enpassantloc=-1;
            a[unde1][unde2]='P';
            a[unde1-1][unde2]='0';
            a[unde1-1][unde2+enpassantloc]='0';
            b[unde1][unde2]=1;
            b[unde1-1][unde2]=2;
            b[unde1-1][unde2+enpassantloc]=2;}
            return 0;
        }
        if(a[unde1-1][unde2]=='P' && b[unde1-1][unde2]==1 && a[unde1][unde2]=='0' && unde1-1>=0  && contorposibil==0)
        {   if(test==1){
            a[unde1][unde2]='P';
            a[unde1-1][unde2]='0';
            b[unde1][unde2]=careculoare;
            b[unde1-1][unde2]=2;
            contorposibil=1;}
        }
        else if(a[unde1-2][unde2]=='P' && b[unde1-2][unde2]==1 && a[unde1][unde2]=='0' && unde1-2>=0 && contorposibil==0 && a[unde1-1][unde2]=='0')
        {   
            if(contormutaredubla==0)
            {
                return 1;
            }
            if((a[unde1][unde2+1]=='P' && b[unde1][unde2+1]!=b[unde1-2][unde2] )|| (a[unde1][unde2-1]=='P' && b[unde1][unde2-1]!=b[unde1-2][unde2]))
            {
              if(test==1 && altcontor==1){  enpassantposibil=1;
                ok=0;
                enpassantlinie=unde1-1;
                enpassantcoloana=unde2;}
            }
           if(test==1){ a[unde1][unde2]='P';
            a[unde1-2][unde2]='0';
            b[unde1][unde2]=careculoare;
            b[unde1-2][unde2]=2;
            contorposibil=1;
        }
           
        }
        else if(a[unde1-1][unde2+1]=='P' && b[unde1-1][unde2+1]==1 && a[unde1][unde2]!='0' && b[unde1][unde2]!=1 && contorposibil==0 && unde1-1>=0 && unde2+1<8)
        {
            if(test==1){a[unde1][unde2]='P';
            a[unde1-1][unde2+1]='0';
            b[unde1][unde2]=careculoare;
            b[unde1-1][unde2+1]=2;
            contorposibil=1;}
        }
        else if(a[unde1-1][unde2-1]=='P' && b[unde1-1][unde2-1]==1 && a[unde1][unde2]!='0' && b[unde1][unde2]!=1 && contorposibil==0 && unde1-1>=0 && unde2-1>=0)
        {
            if(test==1){a[unde1][unde2]='P';
            a[unde1-1][unde2-1]='0';
            b[unde1][unde2]=careculoare;
            b[unde1-1][unde2-1]=2;
            contorposibil=1;}
        }
    }
    if(lendisambiguit!=0)
    {
        if(careculoare==1)
       {
        if(unde4==unde2+1)
        {  
            a[unde1-1][unde2-1]='P';
        }
        else
        {
            a[unde1-1][unde2+1]='P';
        }
       }
       else
       {
        if(unde4==unde2+1)
        {  
            a[unde1+1][unde2-1]='P';
        }
        else
        {
            a[unde1+1][unde2+1]='P';
        }
       }
       lendisambiguit=0;
    }
    if(contorposibil==0)
   {     
        return 1;}
    else
        return 0;
}
int miscaretura(char a[8][8],int b[8][8],int unde1,int unde2,int careculoare,char c,int test,int altcontor)
{   int linie=0;
    int coloana=0;
    int contor =0;
    int k=0;
    if(piesa[1]==1 && test==1&& altcontor==1)
    {
        unde3=unde3-1;
        switch(unde5){
            case 'a':unde4=0;
            break;
            case 'b':unde4=1;
            break;
            case 'c':unde4=2;
            break;
            case 'd':unde4=3;
            break;
            case 'e':unde4=4;
            break;
            case 'f':unde4=5;
            break;
            case 'g':unde4=6;
            break;
            case 'h':unde4=7;
            break;
        }
        if(a[unde3][unde4]!='R')
            {
            return 1;
            }
        if(unde1!=unde3)
        {
            for(int i=unde2+1;i<8;i++)
                    {
                        if(a[unde1][i]!='0')
                        {
                             if(a[unde1][i]=='R' && b[unde3][i]==careculoare)
                                {
                                     {
                                        a[unde3][i]='0';
                                        disambiguit[k]=unde1;
                                        disambiguit[k+1]=i;
                                        k+=2;
                                        break;
                                     }

                                }
                            else
                             break;
                        }
                    }
                    for(int i=unde2-1;i>=0;i--)
                    {
                        if(a[unde1][i]!='0')
                        {
                             if(a[unde1][i]=='R' && b[unde1][i]==careculoare)
                             {  
                             {
                                a[unde1][i]='0';
                                disambiguit[k]=unde1;
                                disambiguit[k+1]=i;
                                k+=2;
                                break;
                             }
                            }
                            else
                             break;
                        }
                    }
        }
        else if(unde2!=unde4)
       { for(int i=unde1+1;i<8;i++)
                    {
                        if(a[i][unde2]!='0')
                          {  if(a[i][unde2]=='R' && b[i][unde2]==careculoare)
                            {
                               a[i][unde2]='0';
                               disambiguit[k]=i;
                               disambiguit[k+1]=unde2;
                               k+=2;
                               break;
                            }
                            else
                            break;
                          }
                    }
                    for(int i=unde1-1;i>=0;i--)
                    {
                        if(a[i][unde2]!='0')
                         {    if(a[i][unde2]=='R' && b[i][unde2]==careculoare)
                            {
                               a[i][unde2]='0';
                               disambiguit[k]=i;
                               disambiguit[k+1]=unde2;
                               k+=2;
                               break;
                            }
                            else
                            break;
                         }

                    }
       }
    lendisambiguit=k;
    }
    for(int i=0;i<8;i++)
    {
        if(a[unde1][i]==c && b[unde1][i]==careculoare)
        {   contor=0;
            linie=unde1;
            coloana=i;
                if (coloana < unde2)
                {
                    for (int i = coloana + 1; i < unde2; i++)
                    {
                        if (a[linie][i] != '0')
                        {
                            contor=1;
                        }
                    }
                }
                else
                {
                    for (int i = unde2 + 1; i < coloana; i++)
                    {
                        if (a[linie][i] != '0')
                        {
                            contor=1;
                        }
                    }
                }
                if (a[unde1][unde2] != '0' && b[unde1][unde2] == careculoare)
                {
                    contor=1;
                }
                if(test==1 && contor==0)
                    {
                a[unde1][unde2] = 'R';
                a[linie][coloana] = '0';
                b[linie][coloana] = 2;
                b[unde1][unde2] = careculoare;
            }
               if(contor==0)
               {
                if(lendisambiguit!=0)
                {
                    for(int i=0;i<lendisambiguit;i+=2)
                    {
                        a[disambiguit[i]][disambiguit[i+1]]='R';
                    }
                }
               return 0;
               }
        }
    }
    for(int j=0;j<8;j++)
    {
        if(a[j][unde2]==c && b[j][unde2]==careculoare)
        {   
            contor=0;
            linie=j;
            coloana=unde2;
            if(linie<unde1)
            {
                for(int i=linie+1;i<unde1;i++)
                {
                    if(a[i][coloana]!='0')
                    {
                        contor=1;
                    }
                }
            }
            else
            {
                for(int i=unde1+1;i<linie;i++)
                {
                    if(a[i][coloana]!='0')
                    {
                        contor=1;
                    }
                }
            }
            if(a[unde1][unde2]!='0' && b[unde1][unde2]==careculoare)
            {
                contor=1;
            }
            if(test==1 && contor==0)
            {
                a[unde1][unde2]='R';
                a[linie][coloana]='0';
                b[linie][coloana] = 2;
                b[unde1][unde2] = careculoare;
            }
            if(contor==0)
            {
                if(lendisambiguit!=0)
                {
                    for(int i=0;i<lendisambiguit;i+=2)
                    {
                        a[disambiguit[i]][disambiguit[i+1]]='R';
                    }
                }
                return 0;
            }
        }
    } 
    return 1;
    }
int miscarebishop(char a[8][8],int b[8][8],int unde1, int unde2,int careculoare,char c,int test,int altcontor)
{
    int k=0;
    if(piesa[3]==1 && test==1&& altcontor==1)
    {
        unde3=unde3-1;
        switch(unde5){
            case 'a':unde4=0;
            break;
            case 'b':unde4=1;
            break;
            case 'c':unde4=2;
            break;
            case 'd':unde4=3;
            break;
            case 'e':unde4=4;
            break;
            case 'f':unde4=5;
            break;
            case 'g':unde4=6;
            break;
            case 'h':unde4=7;
            break;
        }
        if(a[unde3][unde4]!='B')
            {
            return 1;
            }
        for(int i=unde1+1,j=unde2+1;i<8 && j<8;i++,j++)
                        {
                            if(a[i][j]!='0')
                            {
                                 if(a[i][j]=='B' && b[i][j]==careculoare)
                                    {
                                        if(i!=unde3 && j!=unde4)
                                        {
                                            a[unde1][i]='0';
                                            disambiguit[k]=i;
                                            disambiguit[k+1]=j;
                                            k+=2;
                                        }
                                        break;
                                    }
                                else
                                 break;
                            }
                        }
                        for(int i=unde1-1,j=unde2-1;i>=0 && j>=0;i--,j--)
                        {
                            if(a[i][j]!='0')
                            {
                                 if(a[i][j]=='B' && b[i][j]==careculoare)
                                    {
                                        if(i!=unde3 && j!=unde4)
                                        {
                                            a[unde1][i]='0';
                                            disambiguit[k]=i;
                                            disambiguit[k+1]=j;
                                            k+=2;
                                        }
                                        break;
                                    }
                                else
                                 break;
                            }
                        }
                        for(int i=unde1-1,j=unde2+1;i>=0 && j<8;i--,j++)
                        {
                            if(a[i][j]!='0')
                            {
                                 if(a[i][j]=='B' && b[i][j]==careculoare)
                                    {
                                        if(i!=unde3 && j!=unde4)
                                        {
                                            a[unde1][i]='0';
                                            disambiguit[k]=i;
                                            disambiguit[k+1]=j;
                                            k+=2;
                                        }
                                        break;
                                    }
                                else
                                 break;
                            }
                        }
                        for(int i=unde1+1,j=unde2-1;i<8 && j>=0;i++,j--)
                        {
                            if(a[i][j]!='0')
                            {
                                 if(a[i][j]=='B' && b[i][j]==careculoare)
                                    {
                                        if(i!=unde3 && j!=unde4)
                                        {
                                            a[unde1][i]='0';
                                            disambiguit[k]=i;
                                            disambiguit[k+1]=j;
                                            k+=2;
                                        }
                                        break;
                                    }
                                else
                                 break;
                            }
                        }
                        lendisambiguit=k;
    }
    int i=unde1+1;
    int j=unde2+1;
    int linie=0,coloana=0;
    int caz=0;
    while(i<8 && j<8)
    {
        if(a[i][j]==c && b[i][j]==careculoare)
        {
            caz=1;
            linie=i;
            coloana=j;
            break;
        }
        i++;
        j++;
    }
    i=unde1-1;
    j=unde2-1;
    while(i>=0 && j>=0)
    {
        if(a[i][j]==c && b[i][j]==careculoare && caz==0)
        {
            caz=2;
            linie=i;
            coloana=j;
            break;
        }
        i--;
        j--;
    }
    i=unde1-1;
    j=unde2+1;
    while(i>=0 && j<8)
    {
        if(a[i][j]==c && b[i][j]==careculoare  && caz==0)
        {
            caz=3;
            linie=i;
            coloana=j;
            break;
        }
        i--;
        j++;
    }
    i=unde1+1;
    j=unde2-1;
    while(i<8 && j>=0)
    {
        if(a[i][j]==c && b[i][j]==careculoare && caz==0)
        {
            caz=4;
            linie=i;
            coloana=j;
            break;
        }
        i++;
        j--;
    } 
switch (caz)
    {
    case 1:
        i = linie - 1;
        j = coloana - 1;
        while (i > unde1 && j > unde2)
        {
            if (a[i][j] != '0')
            {
                if(lendisambiguit!=0)
                {
                    for(int i=0;i<lendisambiguit;i+=2)
                    {
                        a[disambiguit[i]][disambiguit[i+1]]='B';
                    } }return 1;
            }
            i--;
            j--;
        }
        if (a[unde1][unde2] != '0' && b[unde1][unde2] == careculoare)
        {
            if(lendisambiguit!=0)
                {
                    for(int i=0;i<lendisambiguit;i+=2)
                    {
                        a[disambiguit[i]][disambiguit[i+1]]='B';
                    } }return 1;
        }
        if(test==1){
        a[unde1][unde2] = c;
        b[unde1][unde2] =careculoare;
        a[linie][coloana] = '0';
        b[linie][coloana]=2;
    }
    if(lendisambiguit!=0)
    {
        for(int i=0;i<lendisambiguit;i+=2)
        {
            a[disambiguit[i]][disambiguit[i+1]]='B';
        } }return 0;
        break;
    case 2:
        i = linie + 1;
        j = coloana + 1;
        while (i < unde1 && j <unde2)
        {
            if (a[i][j] != '0')
            {
                if(lendisambiguit!=0)
                {
                    for(int i=0;i<lendisambiguit;i+=2)
                    {
                        a[disambiguit[i]][disambiguit[i+1]]='B';
                    } }return 1;
            }
            i++;
            j++;
        }
        if (a[unde1][unde2] != '0' && b[unde1][unde2] == careculoare)
        {
            if(lendisambiguit!=0)
                {
                    for(int i=0;i<lendisambiguit;i+=2)
                    {
                        a[disambiguit[i]][disambiguit[i+1]]='B';
                    } }return 1;
        }
        if(test==1){
        a[unde1][unde2] = c;
        b[unde1][unde2] =careculoare;
        a[linie][coloana] = '0';
        b[linie][coloana]=2;
        }
        if(lendisambiguit!=0)
                {
                    for(int i=0;i<lendisambiguit;i+=2)
                    {
                        a[disambiguit[i]][disambiguit[i+1]]='B';
                    } }return 0;
        break;
    case 3:
        i = linie + 1;
        j = coloana - 1;
        while (i < unde1 && j >unde2)
        {
            if (a[i][j] != '0')
            {
                if(lendisambiguit!=0)
                {
                    for(int i=0;i<lendisambiguit;i+=2)
                    {
                        a[disambiguit[i]][disambiguit[i+1]]='B';
                    } }return 1;
            }
            i++;
            j--;
        }
        if (a[unde1][unde2] != '0' && b[unde1][unde2] == careculoare)
        {
            if(lendisambiguit!=0)
                {
                    for(int i=0;i<lendisambiguit;i+=2)
                    {
                        a[disambiguit[i]][disambiguit[i+1]]='B';
                    } }return 1;
        }
        if(test==1){
        a[unde1][unde2] = c;
        b[unde1][unde2] =careculoare;
        a[linie][coloana] = '0';
        b[linie][coloana]=2;
        }
        if(lendisambiguit!=0)
                {
                    for(int i=0;i<lendisambiguit;i+=2)
                    {
                        a[disambiguit[i]][disambiguit[i+1]]='B';
                    } }return 0;
        break;
    case 4:
        i = linie - 1;
        j = coloana + 1;
        while (i >unde1 && j < unde2)
        {
            if (a[i][j] != '0')
            {
                if(lendisambiguit!=0)
                {
                    for(int i=0;i<lendisambiguit;i+=2)
                    {
                        a[disambiguit[i]][disambiguit[i+1]]='B';
                    } }return 1;
            }
            i--;
            j++;
        }
        if (a[unde1][unde2] != '0' && b[unde1][unde2] == careculoare)
        {
            if(lendisambiguit!=0)
            {
                for(int i=0;i<lendisambiguit;i+=2)
                {
                    a[disambiguit[i]][disambiguit[i+1]]='B';
                } } return 1;
        }
        if(test==1){
        a[unde1][unde2] = c;
        b[unde1][unde2] =careculoare;
        a[linie][coloana] = '0';
        b[linie][coloana]=2;
        }
        if(lendisambiguit!=0)
                {
                    for(int i=0;i<lendisambiguit;i+=2)
                    {
                        a[disambiguit[i]][disambiguit[i+1]]='B';
                    } }return 0;
        break;
    default:
    if(lendisambiguit!=0)
    {
        for(int i=0;i<lendisambiguit;i+=2)
        {
            a[disambiguit[i]][disambiguit[i+1]]='B';
        } } return 1;
        break;
    }
}
int miscareking(char a[8][8],int b[8][8],int unde1,int unde2,int careculoare,int test)
{   
    if(careculoare==0 && unde1==7 && unde2==2 && contorrege[0]==0 && miscaretura(a,b,7,3,0,'R',0,0)==0 && contortura[0]==0 && contorcheck[1]==0 && contorcast[0]==0)
    {   
        if(test==1)
        {
            a[7][2]='K';
            b[7][2]=0;
            a[7][3]='R';
            b[7][3]=0;
            a[7][0]='0';
            b[7][0]=2;
            a[7][4]='0';
            b[7][4]=2;
        }
        return 0;
    }
    if(careculoare==0 && unde1==7 && unde2==6 && miscaretura(a,b,7,5,0,'R',0,0)==0 && contorrege[0]==0 && contortura[1]==0 && contorcheck[1]==0 && contorcast[1]==0)
    {
        if(test==1)
        {
            a[7][6]='K';
            b[7][6]=0;
            a[7][5]='R';
            b[7][5]=0;
            a[7][7]='0';
            b[7][7]=2;
            a[7][4]='0';
            b[7][4]=2;
        }
        return 0;
    }
    if(careculoare==1 && unde1==0 && unde2==2 && contorrege[1]==0 && miscaretura(a,b,0,3,1,'R',0,0)==0 && contortura[2]==0 && contorcheck[0]==0 && contorcast[2]==0)
    {
        if(test==1)
        {
            a[0][2]='K';
            b[0][2]=1;
            a[0][3]='R';
            b[0][3]=1;
            a[0][0]='0';
            b[0][0]=2;
            a[0][4]='0';
            b[0][4]=2;
        }
        return 0;
    }
    if(careculoare==1 && unde1==0 && unde2==6 && contorrege[1]==0 && miscaretura(a,b,0,5,1,'R',0,0)==0 && contortura[3]==0 && contorcheck[0]==0 && contorcast[3]==0)
    {
        if(test==1)
        {
            a[0][6]='K';
            b[0][6]=1;
            a[0][5]='R';
            b[0][5]=1;
            a[0][7]='0';
            b[0][7]=2;
            a[0][4]='0';
            b[0][4]=2;
        }
        return 0;
    }

    int contor=0;
    int k,l,fini,finj;
    if(unde1-1>=0)
    {
        k=unde1-1;
    }
    else 
    {
        k=unde1;
    }
    if(unde1+1<8)
    {
        fini=unde1+1;
    }
    else
    {
        fini=unde1;
    }
    if(unde2-1>=0)
    {
        l=unde2-1;
    }
    else
    {
        l=unde2;
    }
    if(unde2+1<8)
    {
        finj=unde2+1;
    }
    else
    {
        finj=unde2;
    }
    for(int i=k;i<=fini;i++)
    {
        for(int j=l;j<=finj;j++)
        {   
            if(a[i][j]=='K' && b[i][j]==careculoare)
            {   

            contor=0;
            if(i==unde1)
            {
                if(j==unde2)
                {
                    contor=1;
                }
            }
            if(a[unde1][unde2]!='0' && b[unde1][unde2]==careculoare)
            {   
                return 1;
            }
            if(contor==0)
            {
            if(test==1){a[unde1][unde2]='K';
            a[i][j]='0';
            b[unde1][unde2]=careculoare;
            b[i][j]=2;}
            return 0;
            }
        }
    }
}
    return 1;
}
int miscarequeen(char a[8][8],int b[8][8],int unde1,int unde2,int careculoare,int test,int altcontor)
{
    int k=0;
    if(piesa[3]==1 && test==1&& altcontor==1)
    {
        unde3=unde3-1;
        switch(unde5){
            case 'a':unde4=0;
            break;
            case 'b':unde4=1;
            break;
            case 'c':unde4=2;
            break;
            case 'd':unde4=3;
            break;
            case 'e':unde4=4;
            break;
            case 'f':unde4=5;
            break;
            case 'g':unde4=6;
            break;
            case 'h':unde4=7;
            break;
        }
        if(a[unde3][unde4]!='Q')
            {
            return 1;
            }
        for(int i=unde1+1;i<8;i++)
                        {   
                            if(a[i][unde2]!='0')
                              {  if(a[i][unde2]=='Q' && b[i][unde2]==careculoare)
                                    {
                                        if(i!=unde3)
                                        {
                                            a[i][unde2]='0';
                                            disambiguit[k]=i;
                                            disambiguit[k+1]=unde2;
                                            k+=2;
                                        }
                                        break;
                                    }
                                else
                                    break;
                              }
                        }
                        for(int i=unde1-1;i>=0;i--)
                        {
                            if(a[i][unde2]!='0')
                             {    if(a[i][unde2]=='Q' && b[i][unde2]==careculoare)
                                { 
                                    if(i!=unde3)
                                    {
                                        a[i][unde2]='0';
                                        disambiguit[k]=i;
                                        disambiguit[k+1]=unde2;
                                        k+=2;
                                    break;
                                }
                            }
                                else
                                break;
                                 
                            }
                        }
                        for(int i=unde2+1;i<8;i++)
                        {
                            if(a[unde1][i]!='0')
                            {
                                 if(a[unde1][i]=='Q' && b[unde1][i]==careculoare)
                                    {
                                        if(i!=unde4)
                                        {
                                            a[unde1][i]='0';
                                            disambiguit[k]=unde1;
                                            disambiguit[k+1]=i;
                                            k+=2;
                                        }
                                        break;
                                    }
                                else
                                 break;
                            }
                        }
                        for(int i=unde2-1;i>=0;i--)
                        {
                            if(a[unde1][i]!='0')
                            {
                                 if(a[unde1][i]=='Q' && b[unde1][i]==careculoare)
                                    {if(i!=unde4)
                                        {
                                            a[unde1][i]='0';
                                            disambiguit[k]=unde1;
                                            disambiguit[k+1]=i;
                                            k+=2;
                                        }
                                        break;
                                    }
                                else
                                 break;
                            }
                        }
                        for(int i=unde1+1,j=unde2+1;i<8 && j<8;i++,j++)
                        {
                            if(a[i][j]!='0')
                            {
                                 if(a[i][j]=='Q' && b[i][j]==careculoare)
                                    {
                                        if(i!=unde3 && j!=unde4)
                                        {
                                            a[unde1][i]='0';
                                            disambiguit[k]=i;
                                            disambiguit[k+1]=j;
                                            k+=2;
                                        }
                                        break;
                                    }
                                else
                                 break;
                            }
                        }
                        for(int i=unde1-1,j=unde2-1;i>=0 && j>=0;i--,j--)
                        {
                            if(a[i][j]!='0')
                            {
                                 if(a[i][j]=='Q' && b[i][j]==careculoare)
                                    {
                                        if(i!=unde3 && j!=unde4)
                                        {
                                            a[unde1][i]='0';
                                            disambiguit[k]=i;
                                            disambiguit[k+1]=j;
                                            k+=2;
                                        }
                                        break;
                                    }
                                else
                                 break;
                            }
                        }
                        for(int i=unde1-1,j=unde2+1;i>=0 && j<8;i--,j++)
                        {
                            if(a[i][j]!='0')
                            {
                                 if(a[i][j]=='Q' && b[i][j]==careculoare)
                                    {
                                        if(i!=unde3 && j!=unde4)
                                        {
                                            a[unde1][i]='0';
                                            disambiguit[k]=i;
                                            disambiguit[k+1]=j;
                                            k+=2;
                                        }
                                        break;
                                    }
                                else
                                 break;
                            }
                        }
                        for(int i=unde1+1,j=unde2-1;i<8 && j>=0;i++,j--)
                        {
                            if(a[i][j]!='0')
                            {
                                 if(a[i][j]=='Q' && b[i][j]==careculoare)
                                    {
                                        if(i!=unde3 && j!=unde4)
                                        {
                                            a[unde1][i]='0';
                                            disambiguit[k]=i;
                                            disambiguit[k+1]=j;
                                            k+=2;
                                        }
                                        break;
                                    }
                                else
                                 break;
                            }
                        }
                        lendisambiguit=k;

    }
    int contor=0;
    contor=miscaretura(a,b,unde1,unde2,careculoare,'Q',test,0);
    if(contor==0)
    {   
        if(test==1)
            {a[unde1][unde2]='Q';}
        if(lendisambiguit!=0)
            {
                for(int i=0;i<lendisambiguit;i+=2)
                {
                    a[disambiguit[i]][disambiguit[i+1]]='Q';
                }}
            return 0;
    }
    contor=miscarebishop(a,b,unde1,unde2,careculoare,'Q',test,0);
    if(contor==0)
    {   if(test==1)
            a[unde1][unde2]='Q';
        if(lendisambiguit!=0)
            {
                for(int i=0;i<lendisambiguit;i+=2)
                {
                    a[disambiguit[i]][disambiguit[i+1]]='Q';
                }
             } return 0;
    }
    if(lendisambiguit!=0)
                {
                    for(int i=0;i<lendisambiguit;i+=2)
                    {
                        a[disambiguit[i]][disambiguit[i+1]]='Q';
                    }}return 1;
} 
int miscareknight(char a[8][8],int b[8][8],int unde1,int unde2,int careculoare,int test,int altcontor)
{
    int k=0;
    if(piesa[2]==1 && test==1&& altcontor==1)
    {
        unde3=unde3-1;
        switch(unde5){
            case 'a':unde4=0;
            break;
            case 'b':unde4=1;
            break;
            case 'c':unde4=2;
            break;
            case 'd':unde4=3;
            break;
            case 'e':unde4=4;
            break;
            case 'f':unde4=5;
            break;
            case 'g':unde4=6;
            break;
            case 'h':unde4=7;
            break;
        }
        if(a[unde3][unde4]!='N')
            {
            return 1;
            }
        if(a[unde1+2][unde2+1]=='N' && b[unde1+2][unde2+1]==careculoare && unde1+2<8 && unde2+1<8)
     {
        if(a[unde1][unde2]!='0' && b[unde1][unde2]==careculoare)
        {
            return 1;
        }
        else
            {   
                if(unde1+2!=unde3 && unde2+1!=unde4)
               { a[unde1+2][unde2+1]='0';
                disambiguit[k]=unde1+2;
                disambiguit[k+1]=unde2+1;
                k+=2;

                           }            }
    }
    if(a[unde1+2][unde2-1]=='N' && b[unde1+2][unde2-1]==careculoare && unde1+2<8 && unde2-1>=0)
    {
        if(a[unde1][unde2]!='0' && b[unde1][unde2]==careculoare)
        {
            return 1;
        }
        else
            {   
                if(unde1+2!=unde3 && unde2-1!=unde4)
               { a[unde1+2][unde2-1]='0';
                disambiguit[k]=unde1+2;
                disambiguit[k+1]=unde2-1;
                k+=2;

                           }            }
    }
    if(a[unde1-2][unde2+1]=='N' && b[unde1-2][unde2+1]==careculoare && unde1-2>=0 && unde2+1<8)
    {
        if(a[unde1][unde2]!='0' && b[unde1][unde2]==careculoare)
        {
            return 1;
        }
        else
            {   
                if(unde1-2!=unde3 && unde2+1!=unde4)
               { a[unde1-2][unde2+1]='0';
                disambiguit[k]=unde1-2;
                disambiguit[k+1]=unde2+1;
                k+=2;

                           }            }
    }
    if(a[unde1-2][unde2-1]=='N' && b[unde1-2][unde2-1]==careculoare && unde1-2>=0 && unde2-1>=0) 
    {
        if(a[unde1][unde2]!='0' && b[unde1][unde2]==careculoare)
        {
            return 1;
        }
        else
            {   
                if(unde1-2!=unde3 && unde2-1!=unde4)
               { a[unde1-2][unde2-1]='0';
                disambiguit[k]=unde1-2;
                disambiguit[k+1]=unde2-1;
                k+=2;

                           }            }
    }
   if(a[unde1-1][unde2+2]=='N' && b[unde1-1][unde2+2]==careculoare && unde1-1>=0 && unde2+2<8)
    {
        if(a[unde1][unde2]!='0' && b[unde1][unde2]==careculoare)
        {
            return 1;
        }
        else
            {   
                if(unde1-1!=unde3 && unde2+2!=unde4)
               { a[unde1-1][unde2+2]='0';
                disambiguit[k]=unde1-1;
                disambiguit[k+1]=unde2+2;
                k+=2;

                           }            }
    }
    if(a[unde1-1][unde2-2]=='N' && b[unde1-1][unde2-2]==careculoare && unde1-1>=0 && unde2-2>=0)
    {
        if(a[unde1][unde2]!='0' && b[unde1][unde2]==careculoare)
        {
            return 1;
        }
        else
            {   
                if(unde1-1!=unde3 && unde2-2!=unde4)
               { a[unde1-1][unde2-2]='0';
                disambiguit[k]=unde1-1;
                disambiguit[k+1]=unde2-2;
                k+=2;

                           }            }
    }
    if(a[unde1+1][unde2+2]=='N' && b[unde1+1][unde2+2]==careculoare && unde1+1<8 && unde2+2<8)
    {
        if(a[unde1][unde2]!='0' && b[unde1][unde2]==careculoare)
        {
            return 1;
        }
        else
            {   
                if(unde1+1!=unde3 && unde2+2!=unde4)
               { a[unde1+1][unde2+2]='0';
                disambiguit[k]=unde1+1;
                disambiguit[k+1]=unde2+2;
                k+=2;

                           }            }
    }
    if(a[unde1+1][unde2-2]=='N' && b[unde1+1][unde2-2]==careculoare && unde1+1<8 && unde2-2>=0)
    {
        if(a[unde1][unde2]!='0' && b[unde1][unde2]==careculoare)
        {
            return 1;
        }
        else
            {   
                if(unde1+1!=unde3 && unde2-2!=unde4)
               { a[unde1+1][unde2-2]='0';
                disambiguit[k]=unde1+1;
                disambiguit[k+1]=unde2-2;
                k+=2;

                           }            }
    } 
    lendisambiguit=k;   
}
    if(a[unde1+2][unde2+1]=='N' && b[unde1+2][unde2+1]==careculoare && unde1+2<8 && unde2+1<8)
    {
        if(a[unde1][unde2]!='0' && b[unde1][unde2]==careculoare)
        {
            if(lendisambiguit!=0) 
                {
                    for(int i=0;i<lendisambiguit;i+=2)
                        a[disambiguit[i]][disambiguit[i+1]]='N';
                }
            return 1;
        }
        if(test==1){a[unde1][unde2]='N';
        a[unde1+2][unde2+1]='0';
        b[unde1][unde2]=careculoare;
        b[unde1+2][unde2+1]=2;}
        if(lendisambiguit!=0) 
                {
                    for(int i=0;i<lendisambiguit;i+=2)
                        a[disambiguit[i]][disambiguit[i+1]]='N';
                }return 0;
    }
    else if(a[unde1+2][unde2-1]=='N' && b[unde1+2][unde2-1]==careculoare && unde1+2<8 && unde2-1>=0)
    {
        if(a[unde1][unde2]!='0' && b[unde1][unde2]==careculoare)
        {
            if(lendisambiguit!=0) 
                {
                    for(int i=0;i<lendisambiguit;i+=2)
                        a[disambiguit[i]][disambiguit[i+1]]='N';
                }return 1;
        }
        if(test==1){a[unde1][unde2]='N';
        a[unde1+2][unde2-1]='0';
        b[unde1][unde2]=careculoare;
        b[unde1+2][unde2-1]=2;}
        if(lendisambiguit!=0) 
                {
                    for(int i=0;i<lendisambiguit;i+=2)
                        a[disambiguit[i]][disambiguit[i+1]]='N';
                }return 0;
    }
    else if(a[unde1-2][unde2+1]=='N' && b[unde1-2][unde2+1]==careculoare && unde1-2>=0 && unde2+1<8)
    {
        if(a[unde1][unde2]!='0' && b[unde1][unde2]==careculoare)
        {
            if(lendisambiguit!=0) 
                {
                    for(int i=0;i<lendisambiguit;i+=2)
                        a[disambiguit[i]][disambiguit[i+1]]='N';
                }return 1;
        }
        if(test==1){a[unde1][unde2]='N';
        a[unde1-2][unde2+1]='0';
        b[unde1][unde2]=careculoare;
        b[unde1-2][unde2+1]=2;}
        if(lendisambiguit!=0) 
                {
                    for(int i=0;i<lendisambiguit;i+=2)
                        a[disambiguit[i]][disambiguit[i+1]]='N';
                }return 0;
    }
    else if(a[unde1-2][unde2-1]=='N' && b[unde1-2][unde2-1]==careculoare && unde1-2>=0 && unde2-1>=0) 
    {
        if(a[unde1][unde2]!='0' && b[unde1][unde2]==careculoare)
        {
            if(lendisambiguit!=0) 
            {
                for(int i=0;i<lendisambiguit;i+=2)
                    a[disambiguit[i]][disambiguit[i+1]]='N';
            }return 1;
        }
        if(test==1){a[unde1][unde2]='N';
        a[unde1-2][unde2-1]='0';
        b[unde1][unde2]=careculoare;
        b[unde1-2][unde2-1]=2;}
        if(lendisambiguit!=0) 
                {
                    for(int i=0;i<lendisambiguit;i+=2)
                        a[disambiguit[i]][disambiguit[i+1]]='N';
                }return 0;
    }
    else if(a[unde1-1][unde2+2]=='N' && b[unde1-1][unde2+2]==careculoare && unde1-1>=0 && unde2+2<8)
    {
        if(a[unde1][unde2]!='0' && b[unde1][unde2]==careculoare)
        {
            if(lendisambiguit!=0) 
                {
                    for(int i=0;i<lendisambiguit;i+=2)
                        a[disambiguit[i]][disambiguit[i+1]]='N';
                }return 1;
        }
        if(test==1){a[unde1][unde2]='N';
        a[unde1-1][unde2+2]='0';
        b[unde1][unde2]=careculoare;
        b[unde1-1][unde2+2]=2;}
        if(lendisambiguit!=0) 
                {
                    for(int i=0;i<lendisambiguit;i+=2)
                        a[disambiguit[i]][disambiguit[i+1]]='N';
                }return 0;
    }
    else if(a[unde1-1][unde2-2]=='N' && b[unde1-1][unde2-2]==careculoare && unde1-1>=0 && unde2-2>=0)
    {
        if(a[unde1][unde2]!='0' && b[unde1][unde2]==careculoare)
        {
            if(lendisambiguit!=0) 
                {
                    for(int i=0;i<lendisambiguit;i+=2)
                        a[disambiguit[i]][disambiguit[i+1]]='N';
                }return 1;
        }
        if(test==1){a[unde1][unde2]='N';
        a[unde1-1][unde2-2]='0';
        b[unde1][unde2]=careculoare;
        b[unde1-1][unde2-2]=2;}
        if(lendisambiguit!=0) 
                {
                    for(int i=0;i<lendisambiguit;i+=2)
                        a[disambiguit[i]][disambiguit[i+1]]='N';
                }return 0;
    }
    else if(a[unde1+1][unde2+2]=='N' && b[unde1+1][unde2+2]==careculoare && unde1+1<8 && unde2+2<8)
    {
        if(a[unde1][unde2]!='0' && b[unde1][unde2]==careculoare)
        {
            if(lendisambiguit!=0) 
                {
                    for(int i=0;i<lendisambiguit;i+=2)
                        a[disambiguit[i]][disambiguit[i+1]]='N';
                }return 1;
        }
        if(test==1){a[unde1][unde2]='N';
        a[unde1+1][unde2+2]='0';
        b[unde1][unde2]=careculoare;
        b[unde1+1][unde2+2]=2;}
        if(lendisambiguit!=0) 
                {
                    for(int i=0;i<lendisambiguit;i+=2)
                        a[disambiguit[i]][disambiguit[i+1]]='N';
                }return 0;
    }
    else if(a[unde1+1][unde2-2]=='N' && b[unde1+1][unde2-2]==careculoare && unde1+1<8 && unde2-2>=0)
    {
        if(a[unde1][unde2]!='0' && b[unde1][unde2]==careculoare)
        {
            if(lendisambiguit!=0) 
                {
                    for(int i=0;i<lendisambiguit;i+=2)
                        a[disambiguit[i]][disambiguit[i+1]]='N';
                }return 1;
        }
        if(test==1){a[unde1][unde2]='N';
        a[unde1+1][unde2-2]='0';
        b[unde1][unde2]=careculoare;
        b[unde1+1][unde2-2]=2;}
        if(lendisambiguit!=0) 
                {
                    for(int i=0;i<lendisambiguit;i+=2)
                        a[disambiguit[i]][disambiguit[i+1]]='N';
                }return 0;
    }
    if(lendisambiguit!=0) 
                {
                    for(int i=0;i<lendisambiguit;i+=2)
                        a[disambiguit[i]][disambiguit[i+1]]='N';
                }return 1;
}
void afisare(char a[8][8],int b[8][8])
{start_color();
  init_pair(1,COLOR_BLACK,COLOR_CYAN);
  init_pair(2,COLOR_WHITE,COLOR_BLUE);
  init_pair(3,COLOR_BLACK,COLOR_BLUE);
  init_pair(4,COLOR_WHITE,COLOR_CYAN);
  int square_size=4; 
    int linie=1;
    int y,x;
    attron(A_DIM);
   for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {           
           if((i+j)%2==0)
	      { if(b[i][j]==0)
		  { attron(COLOR_PAIR(3));}
		else
		  { attron(COLOR_PAIR(2));}
	      }
	    else
	      {
		if(b[i][j]==0)
		  { attron(COLOR_PAIR(1));}
		  else
		    {  attron(COLOR_PAIR(4));}
		     
	      }

          
            x =4+ j * square_size;
            y = i * 2;            

           
            mvhline(y, x,' ', square_size);
	     mvhline(y+1, x, ' ', square_size);
            mvvline(y, x, ' ', 2);
            mvvline(y, x + square_size - 1, ' ', 2);

        
            mvaddch(y, x, ' ');
            mvaddch(y, x + square_size - 1, ' ');
            mvaddch(y + 1, x, ' ');
            mvaddch(y + 1, x + square_size - 1, ' ');

          
	    if(b[i][j]==2)
	      mvprintw(y,x+1," ");
	    else
	      {
		attroff(A_DIM);
		attron(A_BOLD);
            mvprintw(y, x + 1, "%c", a[i][j]);
	      }
	    attroff(A_BOLD);
	    attroff(COLOR_PAIR(1));
	 attroff(COLOR_PAIR(2));
		 attroff(COLOR_PAIR(3));
		 attroff(COLOR_PAIR(4));
		 mvprintw(y,2,"%d:",linie);
        }
        linie++;
    }
    mvprintw(y+2,4,"a   b   c   d   e   f   g   h");
    refresh();
}
void afisare2(char a[8][8], int b[8][8]) {
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_CYAN);
    init_pair(2, COLOR_WHITE, COLOR_BLUE);
    init_pair(3, COLOR_BLACK, COLOR_BLUE);
    init_pair(4, COLOR_WHITE, COLOR_CYAN);

    int square_size = 4;
    int linie = 8;
    int y, x;

    attron(A_DIM);

    for (int i = 7; i >= 0; i--) { 
        for (int j = 0; j < 8; j++) { 
           
            if ((i + j) % 2 == 0) {
                if (b[i][j] == 0) {
                    attron(COLOR_PAIR(3));  
                } else {
                    attron(COLOR_PAIR(2));  
                }
            } else {
                if (b[i][j] == 0) {
                    attron(COLOR_PAIR(1));  
                } else {
                    attron(COLOR_PAIR(4)); 
                }
            }

            x = 4 + j * square_size;
            
            
            y = (7 - i) * 2; 

            mvhline(y, x, ' ', square_size);
            mvhline(y + 1, x, ' ', square_size);
            mvvline(y, x, ' ', 2);
            mvvline(y, x + square_size - 1, ' ', 2);

            mvaddch(y, x, ' ');
            mvaddch(y, x + square_size - 1, ' ');
            mvaddch(y + 1, x, ' ');
            mvaddch(y + 1, x + square_size - 1, ' ');

            if (b[i][j] == 2) {
                mvprintw(y, x + 1, " ");
            } else {
                attroff(A_DIM);
                attron(A_BOLD);
                mvprintw(y, x + 1, "%c", a[i][j]); 
            }

            attroff(A_BOLD);
            attroff(COLOR_PAIR(1));
            attroff(COLOR_PAIR(2));
            attroff(COLOR_PAIR(3));
            attroff(COLOR_PAIR(4));

            mvprintw(y, 2, "%d:", linie);
        }
        linie--;
    }
    mvprintw(y + 2, 4, "a   b   c   d   e   f   g   h");
    refresh();
}

int check(char a[8][8], int b[8][8],int test)
{
    int linieregealb=0,coloanaregealb=0;
    int linieregenegru=0,coloanaregenegru=0;
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            if(a[i][j]=='K' && b[i][j]==0)
                linieregealb=i,coloanaregealb=j;
            if(a[i][j]=='K' && b[i][j]==1)
                linieregenegru=i,coloanaregenegru=j;
        }
    }
    if(test==1)
    {
    if(miscarebishop(a,b,linieregealb,coloanaregealb,1,'B',0,0)==0 || miscareknight(a,b,linieregealb,coloanaregealb,1,0,0)==0 || miscarequeen(a,b,linieregealb,coloanaregealb,1,0,0)==0 || miscaretura(a,b,linieregealb,coloanaregealb,1,'R',0,0)==0 || miscarepion(a,b,linieregealb,coloanaregealb,1,0,0)==0)
    {
        if(check(a,b,0)==0)
        {
        return 1;
        }
    }
    }
    if(miscarebishop(a,b,linieregenegru,coloanaregenegru,0,'B',0,0)==0 || miscareknight(a,b,linieregenegru,coloanaregenegru,0,0,0)==0 || miscarequeen(a,b,linieregenegru,coloanaregenegru,0,0,0)==0 || miscaretura(a,b,linieregenegru,coloanaregenegru,0,'R',0,0)==0 || miscarepion(a,b,linieregenegru,coloanaregenegru,0,0,0)==0)
    
    {
        return 2;
    }
    return 0;
}
void populareaparitii(int aparitii[12],char a[8][8],int b[8][8])
{      
    for(int i=0;i<12;i++)
       { aparitii[i]=0;}
    for(int j=0;j<8;j++)
        {for(int k=0;k<8;k++)
            {
                if(a[j][k]=='P' && b[j][k]==0)
                    aparitii[0]++;
                if(a[j][k]=='R' && b[j][k]==0)
                    aparitii[1]++;
                if(a[j][k]=='N' && b[j][k]==0)
                    aparitii[2]++;
                if(a[j][k]=='B' && b[j][k]==0)
                    aparitii[3]++;
                if(a[j][k]=='Q' && b[j][k]==0)
                    aparitii[4]++;
                if(a[j][k]=='K' && b[j][k]==0)
                    aparitii[5]++;
                if(a[j][k]=='P' && b[j][k]==1)
                    aparitii[6]++;
                if(a[j][k]=='R' && b[j][k]==1)
                    aparitii[7]++;
                if(a[j][k]=='N' && b[j][k]==1)
                    aparitii[8]++;
                if(a[j][k]=='B' && b[j][k]==1)
                    aparitii[9]++;
                if(a[j][k]=='Q' && b[j][k]==1)
                    aparitii[10]++;
                if(a[j][k]=='K' && b[j][k]==1)
                    aparitii[11]++;
            }   
        }       
}
int draw(int aparitii[12])
{
    if(aparitii[0]==0 && aparitii[6]==0 && aparitii[1]==0 && aparitii[7]==0 && aparitii[2]==0 && aparitii[8]==0 && aparitii[3]==0 && aparitii[9]==0 && aparitii[4]==0 && aparitii[10]==0)
    {
        return 1;
    }
    if(aparitii[0]==0 && aparitii[6]==0 && aparitii[1]==0 && aparitii[7]==0 && (aparitii[2]+aparitii[8]<2 || (aparitii[2]==1 && aparitii[8]==1)) && aparitii[3]==0 && aparitii[9]==0 && aparitii[4]==0 && aparitii[10]==0)
    {
        return 1;
    }
    if(aparitii[0]==0 && aparitii[6]==0 && aparitii[1]==0 && aparitii[7]==0 && aparitii[2]==0 && aparitii[8]==0 && (aparitii[3]+aparitii[9]<2 || (aparitii[3]==1 && aparitii[9]==1))  && aparitii[4]==0 && aparitii[10]==0)
    {
        return 1;
    }
    return 0;
}
int checkmate(char a[8][8],int b[8][8],int culoare)
{
    int contor=0;
    char d[8][8];
    int e[8][8];
    copietemp(d,a);
    copietempint(e,b);
    if(draw(aparitii)==1)
    {  
        return 2;
    }
    if(check(a,b,1)==1 && culoare==0)
    {
        for(int i=0;i<8;i++)
            {
                for(int j=0;j<8;j++)
                {
                    if(miscarebishop(d,e,i,j,0,'B',1,0)==0)
                {
                    if(check(d,e,1)!=1)
                    {   
                        contor++;
                    }
                }
                copietemp(d,a);
                copietempint(e,b);
               if(miscareknight(d,e,i,j,0,1,0)==0)
                {
                    if(check(d,e,1)!=1)
                    {
                        contor++;
                    }
                }
                copietemp(d,a);
                copietempint(e,b);
                if(miscarequeen(d,e,i,j,0,1,0)==0)
                {
                    if(check(d,e,1)!=1)
                    {
                        contor++;
                    }
                }
                copietemp(d,a);
                copietempint(e,b);
                if(miscaretura(d,e,i,j,0,'R',1,0)==0)
                {
                    if(check(d,e,1)!=1)
                    {
                        contor++;
                    }
                }
                copietempint(e,b);
                copietemp(d,a);
                if(miscarepion(d,e,i,j,0,1,0)==0)
                {
                    if(check(d,e,1)!=1)
                    {
                        contor++;
                    }
                }
                copietemp(d,a);
                copietempint(e,b);
                if(miscareking(d,e,i,j,0,1)==0)
                {
                    if(check(d,e,1)!=1)
                    {
                        contor++;
                    }
                }
                copietemp(d,a);
                copietempint(e,b);
            }
            }
            if(contor==0)
            {
                return 1;
            }
        }
        if(check(a,b,1)==2 && culoare==1)
        {
            for(int i=0;i<8;i++)
            {
                for(int j=0;j<8;j++)
                {
                    if(miscarebishop(d,e,i,j,1,'B',1,0)==0)
                {
                    if(check(d,e,1)!=2)
                    {
                        contor++;
                    }
                }
                copietemp(d,a);
                copietempint(e,b);
               if(miscareknight(d,e,i,j,1,1,0)==0)
                {
                    if(check(d,e,1)!=2)
                    {
                        contor++;
                    }
                }
                copietemp(d,a);
                copietempint(e,b);
                if(miscarequeen(d,e,i,j,1,1,0)==0)
                {
                    if(check(d,e,1)!=2)
                    {
                        contor++;
                    }
                }
                copietemp(d,a);
                copietempint(e,b);
                if(miscaretura(d,e,i,j,1,'R',1,0)==0)
                {
                    if(check(d,e,1)!=2)
                    {
                        contor++;
                    }
                }
                copietempint(e,b);
                copietemp(d,a);
                if(miscarepion(d,e,i,j,1,1,0)==0)
                {
                    if(check(d,e,1)!=2)
                    {
                        contor++;
                    }
                }
                copietemp(d,a);
                copietempint(e,b);
                if(miscareking(d,e,i,j,1,1)==0)
                {
                    if(check(d,e,1)!=2)
                    {
                        contor++;
                    }
                }
                copietemp(d,a);
                copietempint(e,b);
            }
            }
            if(contor==0)
            {
                return 3;
            }
    }
    if(check(a,b,1)==0 && culoare==0)
    {
        for(int i=0;i<8;i++)
        {
            for(int j=0;j<8;j++)
            {
                if(miscarebishop(d,e,i,j,0,'B',1,0)==0)
                {
                    if(check(d,e,1)!=1)
                    { 
                        contor++;
                    }
                }
                copietemp(d,a);
                copietempint(e,b);
               if(miscareknight(d,e,i,j,0,1,0)==0)
                {
                    if(check(d,e,1)!=1)
                    {
                        contor++;
                    }
                }
                copietemp(d,a);
                copietempint(e,b);
                if(miscarequeen(d,e,i,j,0,1,0)==0)
                {
                    if(check(d,e,1)!=1)
                    {
                        contor++;
                    }
                }
                copietemp(d,a);
                copietempint(e,b);
                if(miscaretura(d,e,i,j,0,'R',1,0)==0)
                {
                    if(check(d,e,1)!=1)
                    {
                        contor++;
                    }
                }
                copietempint(e,b);
                copietemp(d,a);
                if(miscarepion(d,e,i,j,0,1,0)==0)
                {
                    if(check(d,e,1)!=1)
                    {
                        contor++;
                    }
                }
                copietemp(d,a);
                copietempint(e,b);
                if(miscareking(d,e,i,j,0,1)==0)
                {
                    if(check(d,e,1)!=1)
                    {
                        contor++;
                    }
                }
                copietemp(d,a);
                copietempint(e,b);
            }
            }
            if(contor==0)
            {
                return 2;
            }
        }
    if(check(a,b,1)==0 && culoare==1)
        {
            for(int i=0;i<8;i++)
            {
                for(int j=0;j<8;j++)
                {
                    if(miscarebishop(d,e,i,j,1,'B',1,0)==0)
                {
                    if(check(d,e,1)!=2)
                    {   
                        contor++;
                    }
                }
                copietemp(d,a);
                copietempint(e,b);
               if(miscareknight(d,e,i,j,1,1,0)==0)
                {
                    if(check(d,e,1)!=2)
                    {
                        contor++;
                    }
                }
                copietemp(d,a);
                copietempint(e,b);
                if(miscarequeen(d,e,i,j,1,1,0)==0)
                {
                    if(check(d,e,1)!=2)
                    {
                        contor++;
                    }
                }
                copietemp(d,a);
                copietempint(e,b);
                if(miscaretura(d,e,i,j,1,'R',1,0)==0)
                {
                    if(check(d,e,1)!=2)
                    {
                        contor++;
                    }
                }
                copietempint(e,b);
                copietemp(d,a);
                if(miscarepion(d,e,i,j,1,1,0)==0)
                {
                    if(check(d,e,1)!=2)
                    {
                        contor++;
                    }
                }
                copietemp(d,a);
                copietempint(e,b);
                if(miscareking(d,e,i,j,1,1)==0)
                {
                    if(check(d,e,1)!=2)
                    {
                        contor++;
                    }
                }
                copietemp(d,a);
                copietempint(e,b);
            }
            }
            if(contor==0)
            {
                return 2;
            }
        }
    return 0;
}
void castlechecker(char a[8][8],int b[8][8])
{
    if(a[7][4]!='K')
    {
        contorrege[0]=1;
    }
    if(a[0][4]!='K')
    {
        contorrege[1]=1;
    }
    if(a[0][0]!='R')
    {
        contortura[2]=1;
    
    }
    if(a[0][7]!='R')
    {
        contortura[3]=1;
    }
    if(a[7][0]!='R')
    {
        contortura[0]=1;
    }
    if(a[7][7]!='R')
    {
        contortura[1]=1;
    }
    char d[8][8];
    int e[8][8];
    copietemp(d,a);
    copietempint(e,b);
    if(check(a,b,1)==1)
{
    contorcheck[1]=1;
}
else contorcheck[1]=0;
if(check(a,b,1)==2)
{
    contorcheck[0]=1;
}
else contorcheck[1]=0;
    if(miscareking(d,e,7,3,0,1)==0)
                {
                    if(check(d,e,1)==1)
                    {
                        contorcast[0]=1;
                    }
                    else contorcast[0]=0;
                }
    if(miscareking(d,e,7,5,0,1)==0)
                {
                    if(check(d,e,1)==1)
                    {
                        contorcast[1]=1;
                    }
                    else contorcast[1]=0;
                }
    if(miscareking(d,e,0,3,1,1)==0)
                {
                    if(check(d,e,1)==2)
                    {
                        contorcast[2]=1;
                    }
                    else contorcast[2]=0;
                }
    if(miscareking(d,e,0,5,0,1)==0)
                {
                    if(check(d,e,1)==1)
                    {
                        contorcast[3]=1;
                    }
                    else contorcast[3]=0;
                }
}
void isdisambiguationneeded(char a[8][8],int b[8][8],int unde1,int unde2,char c,int careculoare)
{
    for(int i=0;i<20;i++)
        disambiguit[i]=0;
    for(int i=0;i<5;i++)
        piesa[i]=0;
    unde3=0;
    unde4=0;
    lendisambiguit=0;
    int contor=0;
    switch(c){
                    case 'P':
		      if(enpassantposibil==1 && unde1==enpassantlinie && unde2==enpassantcoloana)
			{if(careculoare==1){
			   if(a[unde1-1][unde2+1]=='P'&&a[unde1-1][unde2-1]=='P'&& b[unde1-1][unde2+1]==careculoare && b[unde1-1][unde2+1]==careculoare && unde1-1>=0 && unde2+1<8 && unde2-1>=0 && b[unde1][unde2]!=careculoare)
			     { piesa[0]=1;}}
                    if(careculoare==0)
                    {   
                        if(a[unde1+1][unde2+1]=='P'&&a[unde1+1][unde2-1]=='P'&& b[unde1+1][unde2+1]==careculoare && b[unde1+1][unde2+1]==careculoare && unde1+1<8 && unde2+1<8 && unde2-1>=0 && b[unde1][unde2]!=careculoare)
                            piesa[0]=1;
                    }
    }
		      else{
                    if(careculoare==1)
                    {   
                        if(a[unde1-1][unde2+1]=='P'&&a[unde1-1][unde2-1]=='P'&& b[unde1-1][unde2+1]==careculoare && b[unde1-1][unde2+1]==careculoare && unde1-1>=0 && unde2+1<8 && unde2-1>=0 && a[unde1][unde2]!='0' && b[unde1][unde2]!=careculoare)
                            piesa[0]=1;
                    }
                    if(careculoare==0)
                    {   
                        if(a[unde1+1][unde2+1]=='P'&&a[unde1+1][unde2-1]=='P'&& b[unde1+1][unde2+1]==careculoare && b[unde1+1][unde2+1]==careculoare && unde1+1<8 && unde2+1<8 && unde2-1>=0 && a[unde1][unde2]!='0' && b[unde1][unde2]!=careculoare)
                            piesa[0]=1;
                    }}
                    break;
                    case 'R':
                    for(int i=unde1+1;i<8;i++)
                    {   
                        if(a[i][unde2]!='0')
                          {  if(a[i][unde2]=='R' && b[i][unde2]==careculoare)
                                {
                                    contor++;
                                    break;
                                }
                            else
                                break;
                          }
                    }
                    for(int i=unde1-1;i>=0;i--)
                    {
                        if(a[i][unde2]!='0')
                         {    if(a[i][unde2]=='R' && b[i][unde2]==careculoare)
                            { 
                                contor++;
                                break;
                            }
                            else
                            break;
                         }

                    }
                    for(int i=unde2+1;i<8;i++)
                    {
                        if(a[unde1][i]!='0')
                        {
                             if(a[unde1][i]=='R' && b[unde1][i]==careculoare)
                                {
                                    contor++;
                                    break;
                                }
                            else
                             break;
                        }
                    }
                    for(int i=unde2-1;i>=0;i--)
                    {
                        if(a[unde1][i]!='0')
                        {
                             if(a[unde1][i]=='R' && b[unde1][i]==careculoare)
                                {contor++;
                                    break;
                                }
                            else
                             break;
                        }
                    }
                    if(contor>1)
                        piesa[1]=1;
                    break;
                    case 'N':   
if(a[unde1+2][unde2+1]=='N' && b[unde1+2][unde2+1]==careculoare && unde1+2<8 && unde2+1<8)
     {
        if(a[unde1][unde2]!='0' && b[unde1][unde2]==careculoare)
        {
            contor=contor;
        }
        else
            contor++;
    }
if(a[unde1+2][unde2-1]=='N' && b[unde1+2][unde2-1]==careculoare && unde1+2<8 && unde2-1>=0)
    {
        if(a[unde1][unde2]!='0' && b[unde1][unde2]==careculoare)
        {
            contor=contor;
        }
        else
            contor++;
    }
if(a[unde1-2][unde2+1]=='N' && b[unde1-2][unde2+1]==careculoare && unde1-2>=0 && unde2+1<8)
    {
        if(a[unde1][unde2]!='0' && b[unde1][unde2]==careculoare)
        {
            contor=contor;
        }
        else
            contor++;
    }
if(a[unde1-2][unde2-1]=='N' && b[unde1-2][unde2-1]==careculoare && unde1-2>=0 && unde2-1>=0) 
    {
        if(a[unde1][unde2]!='0' && b[unde1][unde2]==careculoare)
        {
            contor=contor;
        }
        else
            contor++;
    }
if(a[unde1-1][unde2+2]=='N' && b[unde1-1][unde2+2]==careculoare && unde1-1>=0 && unde2+2<8)
    {
        if(a[unde1][unde2]!='0' && b[unde1][unde2]==careculoare)
        {
            contor=contor;
        }
        else
            contor++;
    }
if(a[unde1-1][unde2-2]=='N' && b[unde1-1][unde2-2]==careculoare && unde1-1>=0 && unde2-2>=0)
    {
        if(a[unde1][unde2]!='0' && b[unde1][unde2]==careculoare)
        {
            contor=contor;
        }
        else
            contor++;
    }
if(a[unde1+1][unde2+2]=='N' && b[unde1+1][unde2+2]==careculoare && unde1+1<8 && unde2+2<8)
    {
        if(a[unde1][unde2]!='0' && b[unde1][unde2]==careculoare)
        {
            contor=contor;
        }
        else
            contor++;
    }
if(a[unde1+1][unde2-2]=='N' && b[unde1+1][unde2-2]==careculoare && unde1+1<8 && unde2-2>=0)
    {
        if(a[unde1][unde2]!='0' && b[unde1][unde2]==careculoare)
        {
            contor=contor;
        }
        else
            contor++;
    }
    if(contor>1)
       { piesa[2]=1;}
    break;
                    case 'B':
                    for(int i=unde1+1,j=unde2+1;i<8 && j<8;i++,j++)
                        {
                            if(a[i][j]!='0')
                            {
                                 if(a[i][j]=='B' && b[i][j]==careculoare)
                                    {
                                        contor++;
                                        break;
                                    }
                                else
                                 break;
                            }
                        }
                        for(int i=unde1-1,j=unde2-1;i>=0 && j>=0;i--,j--)
                        {
                            if(a[i][j]!='0')
                            {
                                 if(a[i][j]=='B' && b[i][j]==careculoare)
                                    {
                                        contor++;
                                        break;
                                    }
                                else
                                 break;
                            }
                        }
                        for(int i=unde1-1,j=unde2+1;i>=0 && j<8;i--,j++)
                        {
                            if(a[i][j]!='0')
                            {
                                 if(a[i][j]=='B' && b[i][j]==careculoare)
                                    {
                                        contor++;
                                        break;
                                    }
                                else
                                 break;
                            }
                        }
                        for(int i=unde1+1,j=unde2-1;i<8 && j>=0;i++,j--)
                        {
                            if(a[i][j]!='0')
                            {
                                 if(a[i][j]=='B' && b[i][j]==careculoare)
                                    {
                                        contor++;
                                        break;
                                    }
                                else
                                 break;
                            }
                        }
                        if(contor>1)
                            piesa[4]=1;
                    break;
                    case 'Q':
                        for(int i=unde1+1;i<8;i++)
                        {   
                            if(a[i][unde2]!='0')
                              {  if(a[i][unde2]=='Q' && b[i][unde2]==careculoare)
                                    {
                                        contor++;
                                        break;
                                    }
                                else
                                    break;
                              }
                        }
                        for(int i=unde1-1;i>=0;i--)
                        {
                            if(a[i][unde2]!='0')
                             {    if(a[i][unde2]=='Q' && b[i][unde2]==careculoare)
                                { 
                                    contor++;
                                    break;
                                }
                                else
                                break;
                             }
    
                        }
                        for(int i=unde2+1;i<8;i++)
                        {
                            if(a[unde1][i]!='0')
                            {
                                 if(a[unde1][i]=='Q' && b[unde1][i]==careculoare)
                                    {
                                        contor++;
                                        break;
                                    }
                                else
                                 break;
                            }
                        }
                        for(int i=unde2-1;i>=0;i--)
                        {
                            if(a[unde1][i]!='0')
                            {
                                 if(a[unde1][i]=='Q' && b[unde1][i]==careculoare)
                                    {contor++;
                                        break;
                                    }
                                else
                                 break;
                            }
                        }
                        for(int i=unde1+1,j=unde2+1;i<8 && j<8;i++,j++)
                        {
                            if(a[i][j]!='0')
                            {
                                 if(a[i][j]=='Q' && b[i][j]==careculoare)
                                    {
                                        contor++;
                                        break;
                                    }
                                else
                                 break;
                            }
                        }
                        for(int i=unde1-1,j=unde2-1;i>=0 && j>=0;i--,j--)
                        {
                            if(a[i][j]!='0')
                            {
                                 if(a[i][j]=='Q' && b[i][j]==careculoare)
                                    {
                                        contor++;
                                        break;
                                    }
                                else
                                 break;
                            }
                        }
                        for(int i=unde1-1,j=unde2+1;i>=0 && j<8;i--,j++)
                        {
                            if(a[i][j]!='0')
                            {
                                 if(a[i][j]=='Q' && b[i][j]==careculoare)
                                    {
                                        contor++;
                                        break;
                                    }
                                else
                                 break;
                            }
                        }
                        for(int i=unde1+1,j=unde2-1;i<8 && j>=0;i++,j--)
                        {
                            if(a[i][j]!='0')
                            {
                                 if(a[i][j]=='Q' && b[i][j]==careculoare)
                                    {
                                        contor++;
                                        break;
                                    }
                                else
                                 break;
                            }
                        }
                        if(contor>1)
                            piesa[3]=1;
                    break;
                    default:break;
                }
}
int main(void)
{
    int sock;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE];
    
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    FILE *config;

    if((config=fopen("ipconfig.txt","r"))==NULL)
    {
        perror("File open error");
        exit(EXIT_FAILURE);
    }
    char ip[20];
    fgets(ip,20,config);
    ip[strlen(ip)-1]='\0';
    printf("%s",ip);
    if (inet_pton(AF_INET,ip, &serv_addr.sin_addr) <= 0) {
        perror("Invalid address");
        exit(EXIT_FAILURE);
    }
    

    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }
    char nume[32],parola[32],rating[10];
    initscr();
    while(1){
    memset(buffer,0,BUFFER_SIZE);
    nume[0]='\0';
    parola[0]='\0';
    rating[0]='\0';
    mvprintw(3,5,"AUTENTIFICARE:");
    refresh();
    getnstr(nume,31);
    send(sock,nume,sizeof(nume),0);
    clear();
    mvprintw(3,5,"PAROLA PENTRU %s:",nume);
    refresh();
    getnstr(parola,31);
    send(sock,parola,sizeof(parola),0);
    recv(sock,buffer,BUFFER_SIZE,0);
    if(strcmp(buffer,"ok")==0)
    {
        clear();
        refresh();
        break;
    }
    clear();
    refresh();
    mvprintw(3,5,"PAROLA GRESITA");
    getch();
    clear();
    refresh();
    }
    recv(sock,rating,sizeof(rating),0)
    int ceculoare;
    printw("Se cauta oponent...");
    refresh();
    int start=0;
    while(start==0)
    {
        memset(buffer,0,BUFFER_SIZE);
        recv(sock,buffer,BUFFER_SIZE,0);
        if(strcmp(buffer,"START1")==0)
        {
            printw("Oponent gasit!Joci cu piesele albe.Apasa pentru a incepe.");
            refresh();
            ceculoare=1;
            start=1;
        }
        if(strcmp(buffer,"START2")==0)
        {
            printw("Oponent gasit!Joci cu piesele negre.Apasa pentru a incepe.");
            refresh();
            ceculoare=0;
            start=1;
        }
    }
    //char numeop[32],ratingop[10];
    //recv(sock,numeop,sizeof(numeop),0);
    //recv(sock,numeop,sizeof(numeop),0);
    getch();
    clear();
    refresh();
    char a[8][8]; int b[8][8];char c[8][8];
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            if(i==1 || i==6)
            {
                a[i][j]='P';
            }
            else if(i==0 || i==7)
            {
                if(j==0 || j==7)
                     a[i][j]='R';
                else if(j==1 || j==6)
                    a[i][j]='N';
                else if(j==2 || j==5)
                    a[i][j]='B';
            }
            else a[i][j]='0';
           if(i==0 || i==1)
                    b[i][j]=1;
            else if(i==7 || i==6)
                    b[i][j]=0;
            else
                b[i][j]=2;
        }
    }
    a[0][3]='Q';
    a[0][4]='K';
    a[7][3]='Q';
    a[7][4]='K';
    if(ceculoare==0)
 { afisare(a,b);}
 else
 {
    afisare2(a,b);
 }
   populareaparitii(aparitii,a,b);
   for(int i=0;i<5;i++)
   {
    piesa[i]=0;
   }
   for(int i=0;i<4;i++)
   {
    contortura[i]=0;
   }
   for(int i=1;i<2;i++)
   {
    contorrege[i]=0;
   }
    char cine,unde,trimis;
    int unde1,unde2,setrimite;
    int cinemuta=1;
    int contormat=0;
    int contormiscareinvalida=0;
    raw();
    cbreak();
    WINDOW* input=newwin(3,30,17,5);
     box(input,0,0);
      refresh();
      wrefresh(input);
    while(contormat==0)
{
    while(1)
    {   setrimite=0;
        mvwprintw(input,1,1," ");
        refresh();
        wrefresh(input);
        if(cinemuta==1)
      {
        mvwprintw(input,1,1,"Alb:");
        if(ceculoare==1)
        {
        memset(buffer,0,BUFFER_SIZE);
        cine=wgetch(input);
	    unde=wgetch(input);
	    trimis=wgetch(input);
        unde1=(int)trimis-48;
        setrimite=1;
        }
        else{
            mvwprintw(input,1,1,"Se asteapta oponentul.");
            refresh();
            wrefresh(input);
            recv(sock,buffer,BUFFER_SIZE,0);
            cine=buffer[0];
            unde=buffer[1];
            trimis=buffer[2];
            unde1=(int)trimis-48;
        }
      }
      else
      {
        mvwprintw(input,1,1,"Negru:");
        if(ceculoare==0)
        {
        memset(buffer,0,BUFFER_SIZE);
        cine=wgetch(input);
	    unde=wgetch(input);
	    trimis=wgetch(input);
        unde1=(int)trimis-48;
        setrimite=1;
        }
        else{
            mvwprintw(input,1,1,"Se asteapta oponentul.");
            refresh();
            wrefresh(input);
            recv(sock,buffer,BUFFER_SIZE,0);
            cine=buffer[0];
            unde=buffer[1];
            trimis=buffer[2];
            unde1=(int)trimis-48;
        }
      }
	    wclear(input);
        box(input,0,0);
        refresh();
        wrefresh(input);
        contormiscareinvalida=0;
        unde1=unde1-1;
        if(unde1>7 || unde1<0)
        {
            contormiscareinvalida=1;
        }
        switch(unde){
            case 'a':unde2=0;
            break;
            case 'b':unde2=1;
            break;
            case 'c':unde2=2;
            break;
            case 'd':unde2=3;
            break;
            case 'e':unde2=4;
            break;
            case 'f':unde2=5;
            break;
            case 'g':unde2=6;
            break;
            case 'h':unde2=7;
            break;
            default:contormiscareinvalida=1;

        }
        if(contormiscareinvalida==1)
       {
	 mvwprintw(input,1,12,"MISCARE INVALIDA ");
         break;
       }
       isdisambiguationneeded(a,b,unde1,unde2,cine,cinemuta);
      if(piesa[0]!=0||piesa[1]!=0||piesa[2]!=0||piesa[3]!=0||piesa[4]!=0) {mvwprintw(input,1,1,"Coord Piesa dorita:");
       unde5=wgetch(input);
       unde3=(int)wgetch(input)-48;}
       wclear(input);
      box(input,0,0);
      refresh();
      wrefresh(input);
        switch(cine){
        case 'P':contormiscareinvalida=miscarepion(a,b,unde1,unde2,cinemuta,1,1);
        break;
        case 'R':contormiscareinvalida=miscaretura(a,b,unde1,unde2,cinemuta,'R',1,1);
        break;
        case 'B':contormiscareinvalida=miscarebishop(a,b,unde1,unde2,cinemuta,'B',1,1);
        break;
        case 'N':contormiscareinvalida=miscareknight(a,b,unde1,unde2,cinemuta,1,1);
        break;
        case 'Q':contormiscareinvalida=miscarequeen(a,b,unde1,unde2,cinemuta,1,1);
        break;
        case 'K':contormiscareinvalida=miscareking(a,b,unde1,unde2,cinemuta,1);
        break;
        default:
        contormiscareinvalida=1;
        }
        if(contormiscareinvalida==1)
    {
	    mvwprintw(input,1,12,"MISCARE INVALIDA ");
        break;
    } 
    if(checkalb==1)
    {
        if(check(a,b,1)==1)
        {
	  mvwprintw(input,1,12,"MISCARE INVALIDA ");
            copietemp(a,c);
            break;
        }
        else 
        {
            checkalb=0;
        }
    }
    else if (checknegru==1)
    {
        if(check(a,b,1)==2)
        {
	  mvwprintw(input,1,12,"MISCARE INVALIDA ");
            copietemp(a,c);
            break;
        }
        else 
        {
            checknegru=0;
        }
    }
    if(cinemuta==0)
    {
        if(check(a,b,1)==1)
        {
	  mvwprintw(input,1,12,"MISCARE INVALIDA ");
            copietemp(a,c);
            break;
        }
    }
    else if(cinemuta==1)
    {
        if(check(a,b,1)==2)
        {
	  mvwprintw(input,1,12,"MISCARE INVALIDA ");
            copietemp(a,c);
            break;
        }
    }
    if(cinemuta==0 && unde1==0 && cine=='P')
        {
           mvwprintw(input,1,1,"Ce piesa doriti:");
            refresh();
            wrefresh(input);
            char l=wgetch(input);
            if(l!='Q' && l!='N' && l!='B' && l!='R')
            {wclear(input);
                box(input,0,0);
                refresh();
                wrefresh(input);
            mvwprintw(input,1,12,"MISCARE INVALIDA ");
            copietemp(a,c);
            break;
            }
            a[unde1][unde2]=l;
            wclear(input);
      box(input,0,0);
      refresh();
      wrefresh(input);
        }
        if(cinemuta==1 && unde1==7 && cine=='P')
        {
           mvwprintw(input,1,1,"Ce piesa doriti:");
            refresh();
            wrefresh(input);
            char l=wgetch(input);
            if(l!='Q' && l!='N' && l!='B' && l!='R')
            {
                wclear(input);
      box(input,0,0);
      refresh();
      wrefresh(input);
            mvwprintw(input,1,12,"MISCARE INVALIDA ");
            copietemp(a,c);
            break;
            }
            a[unde1][unde2]=l;
            wclear(input);
      box(input,0,0);
      refresh();
      wrefresh(input);
        }
    copietemp(c,a);
    if(enpassantposibil==1)
    {  
        ok++;
        if(ok==2)
        {
            enpassantposibil=0;
            ok=0;
        }
    }
        castlechecker(a,b);
        populareaparitii(aparitii,a,b);
        if(ceculoare==0)
        {afisare(c,b);}
        else
        {
            afisare2(c,b);
        }
        if(cinemuta==0)
        {cinemuta=1;}
    else
       { cinemuta=0;}
        if(check(a,b,1)==1)
        {
	  mvwprintw(input,1,12,"CHECK NEGRU ");
            checkalb=1;
        }
        else if(check(a,b,1)==2)
        {
	  mvwprintw(input,1,12,"CHECK ALB ");
            checknegru=1;
        }
        if(setrimite==1){
            buffer[0]=cine;
            buffer[1]=unde;
            buffer[2]=trimis;
            send(sock,buffer,BUFFER_SIZE,0);}
        contormat=checkmate(a,b,cinemuta);
        if(contormat==3)
        {
	  mvwprintw(input,1,12,"NEGRU A CASTIGAT ");
            break;
        }
        else if (contormat==1)   
        {
	  mvwprintw(input,1,12,"ALB A CASTIGAT ");
            break;
        }
        else if(contormat==2)
        {
	  mvwprintw(input,1,12,"REMIZA ");
            break;
        }
        
	
    }
}
    refresh();
    wrefresh(input);
    getch();
    strcpy(buffer,"GAME_OVER");
    send(sock,buffer,BUFFER_SIZE,0);
    endwin();
    return 0;

}
