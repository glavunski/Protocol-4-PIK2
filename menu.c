#include <stdio.h>
#include <conio.h>

int menu( char *t[])
{
	
   int k,i=1;
	 char ch;
	 
	 printf ("\n%s\n",t[0]);
	 while (t[i]){
		 printf("\n<%d> - %s", i,t[i]);i++;}
	 printf ("\n\n�������� �����:");
	 do
	 {
 	  ch=getch();
		k=ch-'0';
    if(k<=0 || k >i-1) printf("\n���������� ����� !!!\n\n");
	 } while(k<=0 || k >i-1);
	printf("%c\n",ch);
 return k;
}



