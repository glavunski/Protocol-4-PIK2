
//------------ file dict_func.h  -----------------------

//-----  ������� ������ �� ����������� ������ ----
#define SIZE_DICT 1000
// ������ �� ����������� �� ����������� ������ -----
#define DELTA_SIZE 500
typedef enum sta_word{None, In_Word, End_Word} s_word;
 // ---- ������������ �� ����������� ---------
int IsDelimiter(char *delimiters, char c);
                // --- char *delimiters - ����� �� �������, ���������� ���� �����������, ��������� � ���������� ������ NULL;
                // --- char c - ����� ������, ����� �� ������; 


// ---- �������� �������� �� ���� ---- 
void ComputeWord(char c, int *br_word, char *word, int *status);
                 // --- (int c        - ����� ������;
                 // ---  int *br_word - ����� ���� �� ������;
                 // ---  char *word   - �������� ����� �� ��������� �� ����;
                 // ---  int *status  - ����� ������ �� ���������� �����;
//----------------------------------------------------------------------------------
//---- ����������� ���������� ����� �� ����� �������� ���� � �������, ���� �����
//---- ����������� ������� �� ���������� �����, ���������� �������� �� ������
void DeleteDictionary(char **dict, int *count_words, int index_dict);
//----------------------------------------------------------------------------------

// --- ������� ������� �� ������ --- 
void PrintDictionary(char **dict, int index_dict, int *count_words,int status);
//----------------------------------------------------------------------------------

// --- ����� ������ � ������� - ����� ������� � ��� ��������, ��� -1
int FindInToDictionary(char **dict, int index_dict, char *word);
//----------------------------------------------------------------------------------

// --- ������ ���� � �������, ���� ����� �������� �� ���������� ����� � ���������� ���� ---
char ** AddToDictionary(char **dict, int *size_dict, int *index, int **count_words, char *word);
//----------------------------------------------------------------------------------

char ** MakeDictionary(FILE *fp, char **dict, int *size_dict, int *index, int **count_words, int *status);

// --- ��������� �� ������� --------------------------------------------------------
void SortDictByCount(char **dict, int index,int *count_words,int choice);
void SortDictByLet(char **dict, int index,int *count_words,int choice);
//----------------------------------------------------------------------------------

//---  ��������� �� ������� --------------------------------------------------------
int SaveDictionary(char **dict, int index, int *count_words, char *name_file, FILE *fp);
int SaveDictionary2(char **dict, int index, int *count_words, char *name_file, FILE *fp,char *name_dict);

//----------------------------------------------------------------------------------
char ** ReadDictionary(char **dict, int *size_dict, int *index_dict, int **count_words, char *name_file, FILE *fp);

// --- ��������� � �������� �� ������� --------------------------------------------- 
int SaveCodeFile(FILE *fp_in, FILE *fp_out, char **dict, int index, char *name_file);
int OpenDecodeFile(FILE *fp_in, FILE *fp_out, char **dict, int index);
//----------------------------------------------------------------------------------
int Words(FILE *fp);
// --- �������� ������ �� ������ �� ������������ �� EOF ---------------------------- 
int my_fgetc(FILE *fp);
//----------------------------------------------------------------------------------
void cyr_lat_toupperCP1251(char *line);
//----------------------------------------------------------------------------------
void cyr_lat_tolowerCP1251(char *line);
//----------------------------------------------------------------------------------

void LongShortSen(FILE *fp);
void LongShortDict(char **dict,int PAHindex);