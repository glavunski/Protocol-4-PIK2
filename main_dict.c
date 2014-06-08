
#include <stdio.h>
#include <conio.h>

#include <windows.h>

#include "menu.h"
#include "dict_func.h"


//------------- ������ -----------------------
char *txt_menu_g[]=
{
	  "�������� <������>\n--------------------",
		"����� �� ���� �� ������",
		"��������� �� ������ �� ������",
		"��������� ������� �� ������",
		"������� �� ���� � �������",
		"��������� �� �������",
    "�����/��������� �� ������",
    "��������/���������� �� ������",
		"����",
		NULL
};

char *txt_menu_1[]=
{
			"---������ �����---",
			"�� ����������",
			"�� �������� ����",
      "����� �� �����",
      NULL
};

char *txt_menu_2[]=
{
   "����� �� ���� ����������:",
		"�� ������� ���",
		"�� ���� �������� �� ������ � ������",
    "����� �� �����",
		NULL
};

char *txt_menu_3[]=
{
   "---����� �� �������---",
		"����� ��� ����",
		"��������� �� ����",
    "����� �� �����",
		NULL
};
char *txt_menu_4[]=
{
   "---���������---",
	"�������� �� �����",
	"���������� �� �����",
    "����� �� �����",
	NULL
};
char *txt_menu_5[]=
{
   "---��������---",
	"���������",
	"���������",
    "����� �� �����",
	NULL
};

char *txt_menu_6[]=
{
   "---�����-��-���������---",
	"��� ��� � ��������",
	"���������� � ������� ������� ����",
    "����� �� �����",
	NULL
};
void empty_function (int mode)
{
  printf("\n\n    ������ ������� !!! -  ������ ����� %d\n\n   �� ����������� - ���������� ������ !!!\n\n",mode);
  getch();  
}
//--------------------------------------------

int main()
{     int choice;int a;
	int mode, submenu, err;
	int subsubmenu;
	int flagdict=0;
	int flagfile=0;
	FILE *fp_in=NULL,        //--- ������ �������� �� ������ ���� ---
       *fp_dict=NULL,      //--- ������ �������� �� ������� ���� �� ������� ---
       *pcode_file=NULL,//--- ������ �������� �� ��������� ���� ------------
	   *pdecode_file=NULL;
	   
	char name_file[256],name_dict[256], name_code[256], name_word[256],name_decode[256];
  //------------------------------------------------------
	char **dict=NULL;        //---���������  ����� �� ��������� �� ����������� ������ �� ������� ---
  int *count_words=NULL;   //---��������� int ����� �� ���� �� ���������� �� ������ � ������� ----
  int size_dict=SIZE_DICT; //---����� ������ �� ������� --
  int index_dict=0;        //---�������� ������ �� ����������� �� ���� ���� � ������� -----------
	unsigned long br_words=0;
  int status;
  //----------------------------


//---------------------------------------
  SetConsoleCP(1251);
  SetConsoleOutputCP(1251);
//---------------------------------------

  do
	{
	  mode=menu(txt_menu_g);
    switch (mode)
		{
	    case 1:
				{
          submenu=menu(txt_menu_1);
			    switch(submenu)
					{
			      case 1:
            fp_in = stdin;
				    printf("\n���� �� ���������� - �� ���� �������� - <ctrl/Z> !!!\n\n");
					

				    break;
			      case 2:
					  do
						{
						  printf("\n�������� ��� �� ����� �� ���������:");
					    err= scanf("%s", name_file);
						} while(err!=1);
					  if ((fp_in=fopen(name_file,"rt"))==NULL)
						{
						  printf("\n������ <%s> �� ���� �� �� ������ - error No % d !!!\n",name_file,errno);
						  printf("ERROR No %d %s",errno,strerror( errno ));
						}
						else
              printf("\n������ <%s> � ������� ������� �� ��������� !", name_file);flagfile=1;
					LongShortSen(fp_in);
				   break;
					}
	       break;
			 }
	    case 2:
        if (fp_in==NULL)
				  printf("\n    missing input file !!!");
				else
				{

					DeleteDictionary(dict,count_words, index_dict);
					dict=NULL;  
                    count_words=NULL;  
                     index_dict=0;
					rewind(fp_in);
          dict=MakeDictionary(fp_in, dict, &size_dict, &index_dict, &count_words, &status);
		  printf("������!\n");
		  LongShortDict(dict,index_dict);
		  flagdict=1;
				}
			break;

      case 3:
		  if(flagdict==0){
		  printf("���� �������� ������!\n");
		  }
		  else{
			  PrintDictionary(dict, index_dict, count_words, status);}
			break;

	    case 4:
			if(flagdict==0){
		  printf("���� �������� ������!\n");
		  }
		  else{
			printf("�������� ����:\n");
			scanf("%s",name_word);
			cyr_lat_toupperCP1251(name_word);
			a=FindInToDictionary(dict, index_dict, name_word);
			if(a==-1){printf("���� ������ ����\n");
			}else{printf("��� ������ ���� � �� �� ����� %d ����\n",count_words[a]);}
		  }
			break;

	    case 5:if(flagdict==0){printf("���� �������� ������!\n");}else{
        submenu = menu(txt_menu_2);
		switch(submenu){
		case 1:
			
		  
			subsubmenu=menu(txt_menu_5);
			switch(subsubmenu){case 1:choice=1;
			SortDictByLet(dict,index_dict,count_words,choice);
			printf("������!\n");system("pause");break;
			case 2:choice=2;
			SortDictByLet(dict,index_dict,count_words,choice);
			printf("������!\n");system("pause");break;
			case 3:break;
			}
			
			break;
		case 2: 
			subsubmenu=menu(txt_menu_5);
			switch(subsubmenu){
			case 1:choice=1;SortDictByCount(dict,index_dict,count_words,choice);
			printf("������!\n");system("pause");break;
			case 2:choice=2;SortDictByCount(dict,index_dict,count_words,choice);
			printf("������!\n");system("pause");break;
			case 3:break;

			}
			
			
			break;
		case 3:break;
		}
			   }
			break;

	    case 6:
        submenu = menu(txt_menu_3);
		switch(submenu){
		case 1:
			if(flagdict==0){
		  printf("���� �������� ������!\n");
		  }else{
			printf("�������� ���� �� ����� �� ������:\n");
			scanf("%s",name_dict);
			if ((fp_dict=fopen(name_dict,"w"))==NULL)
						{
						  printf("\n������ <%s> �� ���� �� �� ������ - error No % d !!!\n",name_dict,errno);
						  printf("ERROR No %d %s",errno,strerror( errno ));
						}
		
				else{
					subsubmenu=menu(txt_menu_6);
					switch(subsubmenu){
					case 1:SaveDictionary(dict,index_dict, count_words, name_file, fp_dict);
			printf("������!\n");break;
					case 2:SaveDictionary2(dict,index_dict, count_words, name_file, fp_dict,name_dict);
			printf("������!\n");break;
					case 3:break;
			}
			}
			}
			break;
		case 2: 
			printf("�������� ���� �� ��������� �� ������:\n");
			scanf("%s",name_dict);
			if ((fp_dict=fopen(name_dict,"r"))==NULL)
						{
						  printf("\n������ <%s> �� ���� �� �� ������ - error No % d !!!\n",name_dict,errno);
						  printf("ERROR No %d %s",errno,strerror( errno ));
						}
		
				else
				{
					DeleteDictionary(dict,count_words, index_dict);
					dict=NULL;  
                    count_words=NULL;  
                     index_dict=0;
			if(dict =ReadDictionary(dict,&size_dict,&index_dict,&count_words,name_dict,fp_dict)){
			printf("������!\n");
			rewind(fp_dict);
			flagdict=1;
			}
				}
			break;

		case 3:break;

		}
			break;

	    case 7:
			if(flagdict==0){printf("���� �������� ������!\n");}else{
				if(flagfile==0){printf("���� ������� ����!\n");break;}
			submenu = menu(txt_menu_4);
			switch(submenu){
			case 1:
				printf("�������� ���� �� �������� �� ������:\n");
			scanf("%s",name_code);
			if ((pcode_file=fopen(name_code,"w"))==NULL)
						{
						  printf("\n������ <%s> �� ���� �� �� ������ - error No % d !!!\n",name_code,errno);
						  printf("ERROR No %d %s",errno,strerror( errno ));
						}
		
				else{
					
						fp_in=fopen(name_file,"r");
SaveCodeFile(fp_in, pcode_file, dict,index_dict, name_file);printf("������!\n");
					

					}
			
			break;
		case 2: 
			printf("�������� ���� �� ���������� �� ������:\n");
			scanf("%s",name_decode);
			printf("�������� ������� ���� �� ������:\n");
			scanf("%s",name_code);
			if ((pdecode_file=fopen(name_decode,"w"))==NULL)
						{
						  printf("\n������ <%s> �� ���� �� �� ������ - error No % d !!!\n",name_decode,errno);
						  printf("ERROR No %d %s",errno,strerror( errno ));break;
						}
		if ((pcode_file=fopen(name_code,"r"))==NULL)
						{
						  printf("\n������ <%s> �� ���� �� �� ������ - error No % d !!!\n",name_code,errno);
						  printf("ERROR No %d %s",errno,strerror( errno ));break;
						}
				
					OpenDecodeFile(pcode_file,pdecode_file, dict, index_dict);printf("������!\n");
break;
		case 3:break;
		}
			}
			}
			
	}while (mode != 8);
}

