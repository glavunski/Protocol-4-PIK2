


#include "stdio.h"
#include "conio.h"
#include <stdlib.h>
#include <string.h>
#include "dict_func.h"
#include <ctype.h>


char PAHdelimiters_word[]={' ',',','.','?','!',':',';','/','\\','*', '(',')','{','}','[',']','\n','\t'};
char PAHdelimiters_sen[]={'.','!','?',';',EOF};
char PAHnums[]={'0','1','2','3','4','5','6','7','8','9'};






int PAHIsDelimiter(char *PAHdelimiters, char PAHc)
{
  int PAHi=0;
  while(PAHdelimiters[PAHi])
  {
    if (PAHc==PAHdelimiters[PAHi++])
      return 1; //--- символът с е разделител ---
  }
  return 0;
}

//-------------------------------------------------------------------------------------------------
void DeleteDictionary(char **PAHdict, int *PAHcount_words, int PAHindex_dict)
{
  int PAHc;
  if (PAHdict) 
  {
    for(PAHc=0; PAHc<PAHindex_dict; PAHc++){

		free(PAHdict[PAHc]);
	}
    free (PAHdict);
    free (PAHcount_words);
	
  }
  
}
//-------------------------------------------------------------------------------------------------
void PrintDictionary(char **PAHdict, int PAHindex_dict, int *PAHcount_words, int PAHstatus)
{
  int PAHi;

  if( PAHindex_dict) printf("\n\n    РЕЧНИК:");
  for (PAHi=0; PAHi<PAHindex_dict;PAHi++)
  {
    printf("\n%6d %s",PAHcount_words[PAHi],PAHdict[PAHi]);
    if (PAHi>0 && !(PAHi%PAHindex_dict) )
    {
      printf("\n\n Press any key to continue !!!");
      getch();
    }
  }
  if(!PAHindex_dict)
    printf("\n\n  речникът е празен !!!\n\n");
  else
  {
    printf("\n\n    брой на думите в речника -> %d",PAHindex_dict);
    if(!PAHstatus) printf(" - речника е недовършен - липса на достатъчнo ПАМЕТ !!!\n\n"); else printf("\n\n");
  }
}
//-----------------------------------------------------
void ComputeWord(char PAHc, int *PAHbr_word, char *PAHword, int *PAHstatus){
	
static int PAHind=0;
 //case None - 0
//case In_Word - 1
//case End_Word - 2

  if(*PAHstatus==2) 
  {
    *PAHstatus=0;
    PAHind=0;
	memset(PAHword,0,256);
  } 
  switch (*PAHstatus)
  {
		case 0:
	    if (!PAHIsDelimiter(PAHdelimiters_word,PAHc))
			{
				*PAHstatus=1;
				PAHword[PAHind++]=PAHc;
				
			}
   break;

   case 1:
    if( PAHIsDelimiter(PAHdelimiters_word,PAHc))
    {
     *PAHstatus=2;
	 PAHword[PAHind]='\0';
	  
    }
    else
    {
			PAHword[PAHind++]=PAHc;
    }
  }
	
}
//----------------------------------------------------
char ** MakeDictionary(FILE *PAHfp, char **PAHdict, int *PAHsize_dict, int *PAHindex, int **PAHcount_words, int *PAHstatus)
{
	int PAHc;
	int *PAHbr_word=0, PAHind=0;
  int PAHsta=0;
	char PAHword[256];
  int (*PAHfff)(FILE *PAHfp);
  char **PAHwork;
  //----------------------------------------------
  if (PAHfp==stdin) PAHfff=my_fgetc; else PAHfff=fgetc;
  //----------------------------------------------
	rewind(PAHfp);
  while (PAHc=PAHfff(PAHfp))
  {
	  
     ComputeWord(PAHc, PAHbr_word, PAHword, &PAHsta);
   
     if (PAHsta==2)
     {
        PAHbr_word++;
        cyr_lat_toupperCP1251(PAHword);
        if ( (PAHwork = AddToDictionary(PAHdict, PAHsize_dict, PAHindex, PAHcount_words, PAHword))==NULL)
        {
          *PAHstatus=0; return PAHdict;
        }
        else
        {
          *PAHstatus=1; PAHdict=PAHwork;
        }
		
     }
	 if(PAHc==EOF){break;}
  }
 if (PAHsta==1)
 {
   PAHbr_word++;
   cyr_lat_toupperCP1251(PAHword);
    if ( (PAHwork = AddToDictionary(PAHdict, PAHsize_dict, PAHindex, PAHcount_words, PAHword))==NULL)
    {
      *PAHstatus=0; return PAHdict;
    }
    else
    {
       *PAHstatus=1; PAHdict=PAHwork;
    }
	
 }
 return PAHdict;
}

//-------------------------------------------------------------------------------------------------
char ** AddToDictionary(char **PAHdict, int *PAHsize_dict, int *PAHindex, int **PAHcount_words, char *PAHword)
{ 
  int PAHind;
  char **PAHwork_dict;
  int *PAHwork_count_words;

  if (PAHdict==NULL)
  {
    if( (PAHwork_dict=(char **)malloc(*PAHsize_dict*sizeof(char *))) == NULL)  return NULL; 
    PAHdict=PAHwork_dict;
  }
  if (*PAHcount_words==NULL)
  {
     if((PAHwork_count_words=(int *) malloc(*PAHsize_dict*sizeof(int)))==NULL)return NULL;
    *PAHcount_words=PAHwork_count_words;
  }
  if ( (PAHind=FindInToDictionary(PAHdict, *PAHindex, PAHword)) != -1)
  {
    (*PAHcount_words)[PAHind]++;
	  return PAHdict;
  }
  if ((PAHdict[*PAHindex] = (char *) malloc(sizeof(char)*(strlen(PAHword)+1)))== NULL) return NULL;
  strcpy(PAHdict[*PAHindex],PAHword);
  (*PAHcount_words)[*PAHindex]=1;
  (*PAHindex)++;
   if (*PAHindex==*PAHsize_dict)
   {
     *PAHsize_dict+=DELTA_SIZE;
      if ((PAHwork_dict = (char **)realloc(PAHdict,*PAHsize_dict* sizeof(char *)))==NULL) return NULL;
      PAHdict=PAHwork_dict;
      if ((PAHwork_count_words = (int *) realloc(*PAHcount_words, *PAHsize_dict*sizeof(int)))==NULL) return NULL;
      *PAHcount_words=PAHwork_count_words;
   }
  return PAHdict;
}

//-------------------------------------------------------------------------------------------------
int FindInToDictionary(char **PAHdict, int PAHindex_dict, char *PAHword)
{
  int PAHi;
  for (PAHi=0; PAHi< PAHindex_dict; PAHi++){
    if (strcmp(PAHdict[PAHi],PAHword)==0){
		return PAHi;}
}
	return -1;
}
//------------------------------------------------------------------------------------------------
void SortDictByCount(char **PAHdict, int PAHindex,  int *PAHcount_words,int PAHchoice )
{
  int PAHj,PAHi,PAHflag=1;
  int PAHtempwords;
  char **PAHtmp=NULL;
  int PAHsizeAd=255;

  if(PAHchoice==1){
  PAHtmp=(char**)malloc((PAHsizeAd)*sizeof(char*)); /* разширяване на масива */ 
 for (PAHi = 1 ; PAHi < PAHindex ; PAHi++)
  {
    for (PAHj= 0 ; PAHj < PAHindex - 1; PAHj++)
    {
		if(PAHcount_words[PAHj]>PAHcount_words[PAHj+1]){
					*PAHtmp=PAHdict[PAHj];
					PAHtempwords=PAHcount_words[PAHj];
					PAHdict[PAHj] = PAHdict[PAHj+1];
					PAHcount_words[PAHj]=PAHcount_words[PAHj+1];
					PAHdict[PAHj+1] = *PAHtmp;
					PAHcount_words[PAHj+1]=PAHtempwords;
				}
    }
  }
  }else if(PAHchoice==2){
   PAHtmp=(char**)malloc((PAHsizeAd)*sizeof(char*)); /* разширяване на масива */ 
 for (PAHi = 1 ; PAHi < PAHindex ; PAHi++)
  {
    for (PAHj= 0 ; PAHj < PAHindex - 1; PAHj++)
    {
		if(PAHcount_words[PAHj]<PAHcount_words[PAHj+1]){
					*PAHtmp=PAHdict[PAHj];
					PAHtempwords=PAHcount_words[PAHj];
					PAHdict[PAHj] = PAHdict[PAHj+1];
					PAHcount_words[PAHj]=PAHcount_words[PAHj+1];
					PAHdict[PAHj+1] = *PAHtmp;
					PAHcount_words[PAHj+1]=PAHtempwords;
				}
    }
  }
  
  
  }
  else{return;}

   }
void SortDictByLet(char **PAHdict,int PAHindex, int *PAHcount_words,int PAHchoice)
{
  int PAHj,PAHi,PAHflag=1;
  int PAHtempwords;
  char **PAHtmp=NULL;
  int PAHsizeAd=255;
  int PAHb;
  if(PAHchoice==1){
  PAHtmp=(char**)malloc((PAHsizeAd)*sizeof(char*)); /* разширяване на масива */ 
 for (PAHi = 1 ; PAHi < PAHindex ; PAHi++)
  {
    for (PAHj= 0 ; PAHj < PAHindex - 1; PAHj++)
    {
		if(strcmp(PAHdict[PAHj],PAHdict[PAHj+1])>0){
			
					*PAHtmp=PAHdict[PAHj];
					PAHtempwords=PAHcount_words[PAHj];
					PAHdict[PAHj] = PAHdict[PAHj+1];
					PAHcount_words[PAHj]=PAHcount_words[PAHj+1];
					PAHdict[PAHj+1] = *PAHtmp;
					PAHcount_words[PAHj+1]=PAHtempwords;

			
				}
 
    }
  }
  }else if(PAHchoice==2){
	  PAHtmp=(char**)malloc((PAHsizeAd)*sizeof(char*));
   for (PAHi = 1 ; PAHi < PAHindex ; PAHi++)
  {
    for (PAHj= 0 ; PAHj < PAHindex - 1; PAHj++)
    {
		if(strcmp(PAHdict[PAHj],PAHdict[PAHj+1])<0){
			
					*PAHtmp=PAHdict[PAHj];
					PAHtempwords=PAHcount_words[PAHj];
					PAHdict[PAHj] = PAHdict[PAHj+1];
					PAHcount_words[PAHj]=PAHcount_words[PAHj+1];
					PAHdict[PAHj+1] = *PAHtmp;
					PAHcount_words[PAHj+1]=PAHtempwords;

			
				}
 
    }
  }
  
  }else {return;}
  
      
   }

int my_fgetc(FILE *PAHfp)
{
  int PAHch;
  PAHch=getche();
  if (PAHch==26) return EOF;
  if (PAHch=='\r')
  {
    printf("\n");
    PAHch='\n';
  }
  return PAHch;
}

void cyr_lat_toupperCP1251(char *PAHline)
{
   int PAHi, PAHlen;
   PAHlen=strlen(PAHline);
   for(PAHi=0; PAHi<PAHlen; PAHi++)
   {
     if(PAHline[PAHi]>='а' &&PAHline[PAHi]<='я'){
		 PAHline[PAHi]=PAHline[PAHi]-32;}
     else{
		 PAHline[PAHi]=(unsigned char)toupper(PAHline[PAHi]);}
   }
}
////////////////////////////////////////////////////
void cyr_lat_tolowerCP1251(char *PAHline)
{
   int PAHi, PAHlen;
   PAHlen=strlen(PAHline);
   for(PAHi=0; PAHi<PAHlen; PAHi++)
   {
     if(PAHline[PAHi]>='А' && PAHline[PAHi]<='Я')
       PAHline[PAHi]=PAHline[PAHi]+0x20;
     else
       PAHline[PAHi]=(unsigned char)tolower(PAHline[PAHi]);
   }
}
/////////////////////////////////////////////////////////
//------------------------------------------------------------------------------------------
int SaveDictionary(char **PAHdict, int PAHindex, int *PAHcount_words, char *PAHname_file, FILE *PAHfp)
{
  int PAHi;
  if( fprintf(PAHfp,"text_file %s\n",PAHname_file)<1) {fclose(PAHfp); return 0; }
   for(PAHi=0;PAHi <PAHindex; PAHi++){
	   if(fprintf(PAHfp,"%06d %s\n",PAHcount_words[PAHi],PAHdict[PAHi])<1) { fclose(PAHfp); return 0;}}
	fclose(PAHfp);
  return 1; 
}

int SaveDictionary2(char **PAHdict, int PAHindex, int *PAHcount_words, char *PAHname_file, FILE *PAHfp, char *PAHname_dict)
{
	
	FILE *PAHaz;
	char PAHguz[256];
	int PAHa;int PAHi;
	for(PAHa=0;PAHa<strlen(PAHname_dict);PAHa++){
		if(PAHname_dict[PAHa]=='.'){break;}
		else{PAHguz[PAHa]=PAHname_dict[PAHa];}
	}
	PAHguz[PAHa++]='.';PAHguz[PAHa++]='c';PAHguz[PAHa++]='n';PAHguz[PAHa++]='t';PAHguz[PAHa++]='\0';
	PAHaz=fopen(PAHguz,"w");
  
  if( fprintf(PAHfp,"text_file %s\n",PAHname_file)<1) {fclose(PAHfp); return 0; }
  if( fprintf(PAHaz,"text_file %s\n",PAHname_file)<1) {fclose(PAHaz); return 0; }
   for(PAHi=0;PAHi <PAHindex; PAHi++){
	   if(fprintf(PAHfp,"%s\n",PAHdict[PAHi])<1) { fclose(PAHfp); return 0;}
   if(fprintf(PAHaz,"%06d\n",PAHcount_words[PAHi])<1) { fclose(PAHaz); return 0;}
   }
	fclose(PAHfp);
	fclose(PAHaz);
  return 1; 
}
//-----------------------------------------------------------------------------------------------------------
char **ReadDictionary(char **PAHdict, int *PAHsize_dict, int *PAHindex_dict, int **PAHcount_words, char *PAHname_file, FILE *PAHfp)
{
  int PAHi, PAHbr;
  char PAHbuff[256];
  int *PAHw_count_words=NULL, PAHw_size_dict=SIZE_DICT, PAHw_index_dict=0;
  char **PAHw_dict=NULL, **PAHtemp;

  if(fscanf(PAHfp,"%s %s",PAHbuff,PAHname_file)!=2) { fclose(PAHfp); return; }
  for (; (PAHi=fscanf(PAHfp,"%d %s",&PAHbr,PAHbuff))!=EOF;)
  {
    if (PAHi!=2) { fclose(PAHfp); return;} 
     if(PAHtemp=AddToDictionary( PAHw_dict, &PAHw_size_dict, &PAHw_index_dict, &PAHw_count_words, PAHbuff))
     {
        PAHw_dict=PAHtemp; PAHw_count_words[PAHw_index_dict-1]=PAHbr;
     }
     else
        return;
  }
  PAHdict=PAHw_dict;
  *PAHcount_words=PAHw_count_words;
  *PAHindex_dict=PAHw_index_dict;
  return PAHdict;
}

int SaveCodeFile(FILE *PAHfp_in, FILE *PAHfp_out, char **PAHdict, int index, char *PAHname_file){ 
    int PAHi=0;
	int PAHb;
	char PAHduma[256];
	int PAHc;
	fprintf(PAHfp_out,"%s","text_file ");
	fprintf(PAHfp_out,"%s",PAHname_file);
	fputc('\n',PAHfp_out);
	while(PAHc=fgetc(PAHfp_in)){

		if(!PAHIsDelimiter(PAHdelimiters_word,PAHc)){
		PAHduma[PAHi++]=PAHc;
		}
		else{
			
		PAHduma[PAHi]=0;
		cyr_lat_toupperCP1251(PAHduma);
		for(PAHb=0;PAHb<index;PAHb++){
			if(strcmp(PAHdict[PAHb],PAHduma)==0){
			fprintf(PAHfp_out,"%d",PAHb+1);
			
            
			break;
			}
			
		}
		if(PAHc!=EOF){
			fputc(PAHc,PAHfp_out);}
		memset(PAHduma,0,256);
			PAHi=0;
		}
	
		if(PAHc==EOF){break;}
	}

rewind(PAHfp_in);
fclose(PAHfp_out);
return 0;
}

int OpenDecodeFile(FILE *PAHfp_in, FILE *PAHfp_out, char **PAHdict, int PAHindex){ 
    int PAHi=0;
	int PAHb;
	char PAHduma[256];
	char PAHc;
	char *PAHptr;
	int PAHchislo;
	while(PAHc=fgetc(PAHfp_in)){

		if(PAHIsDelimiter(PAHnums,PAHc)){
		PAHduma[PAHi++]=PAHc;
		}
		else{
		
		PAHduma[PAHi]=0;
		if(PAHIsDelimiter(PAHnums,PAHduma[0])){
		PAHptr = PAHduma;	
		PAHchislo = strtol(PAHptr,&PAHptr,10);
		for(PAHb=1;PAHb<=PAHindex;PAHb++){
			if(PAHchislo==PAHb){
				cyr_lat_tolowerCP1251(PAHdict[PAHb-1]);
			fprintf(PAHfp_out,"%s",PAHdict[PAHb-1]);
			break;
			}
			
		}
		}
		if(PAHc!=EOF){
			fputc(PAHc,PAHfp_out);}
		memset(PAHduma,0,256);
			PAHi=0;
		}
	
		if(PAHc==EOF){break;}
	}
for(PAHb=1;PAHb<=PAHindex;PAHb++){
			cyr_lat_toupperCP1251(PAHdict[PAHb-1]);
		}

fclose(PAHfp_in);
fclose(PAHfp_out);
return 0;
}
void LongShortSen(FILE *fp){
	int c;
	char curSen[1000];
	char maxSen[1000];
	char minSen[1000];
	int max=0;
	int min=0;
	int strl=0;
	int i =0;
	int flag=0;
	while(c=fgetc(fp)){
		if(!PAHIsDelimiter(PAHdelimiters_sen,c)){
		curSen[i++]=c;
		}
		else {

			if(flag==0){
            flag=1;
			min = strlen(curSen);
			}
			
		curSen[i]='\0';
		
		strl = strlen(curSen);
		if(strl>max){
		max=strl;
		strcpy(maxSen,curSen);
		}
		else if(strl<min&&strl>=1){
		min = strl;
		strcpy(minSen,curSen);
		}
        i=0;
		memset(curSen,0,1000);
		}
	
	
		if(c==EOF){break;}
	}
printf("Най-дългото изречение е: %s\n",maxSen);
printf("Най-късото изречение е: %s\n",minSen);

system("pause");
}

void LongShortDict(char **dict,int PAHindex){

	int i=0;
	int maxindex=0,minindex=0;
	int max=0;
	int min=strlen(dict[0]);
	for(i=0;i<PAHindex;i++){
		if(strlen(dict[i])>max){
		max=strlen(dict[i]);
		maxindex=i;
		}
		else if(strlen(dict[i])<min){
		min=strlen(dict[i]);
		minindex=i;
		}
	}

	printf("Най-дългата дума е: %s\n",dict[maxindex]);
	printf("Най-късата дума е: %s\n",dict[minindex]);
	system("pause");


}
//--------------------------------------------------------------------------------------------------------
