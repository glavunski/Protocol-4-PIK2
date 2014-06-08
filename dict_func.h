
//------------ file dict_func.h  -----------------------

//-----  начален размер на динамичните масиви ----
#define SIZE_DICT 1000
// стъпка на увеличаване на динамичните масиви -----
#define DELTA_SIZE 500
typedef enum sta_word{None, In_Word, End_Word} s_word;
 // ---- разпознаване на разделители ---------
int IsDelimiter(char *delimiters, char c);
                // --- char *delimiters - масив от символи, дефинирани като разделители, завърюващ с терминиращ символ NULL;
                // --- char c - текущ символ, които се тества; 


// ---- потоково отделяне на дума ---- 
void ComputeWord(char c, int *br_word, char *word, int *status);
                 // --- (int c        - текущ символ;
                 // ---  int *br_word - текущ брой на думите;
                 // ---  char *word   - символен масив за отделянер на дума;
                 // ---  int *status  - текущ статус на автоматния модел;
//----------------------------------------------------------------------------------
//---- освобождава заделената памет за всяка отделена дума в речника, след което
//---- освобождава паметта за динамичния масив, съхраняващ адресите на думите
void DeleteDictionary(char **dict, int *count_words, int index_dict);
//----------------------------------------------------------------------------------

// --- извежда речника на екрана --- 
void PrintDictionary(char **dict, int index_dict, int *count_words,int status);
//----------------------------------------------------------------------------------

// --- търси думата в речника - връща индекса й при намиране, или -1
int FindInToDictionary(char **dict, int index_dict, char *word);
//----------------------------------------------------------------------------------

// --- добавя дума в речника, като връща началото на динамичния масив с добавената дума ---
char ** AddToDictionary(char **dict, int *size_dict, int *index, int **count_words, char *word);
//----------------------------------------------------------------------------------

char ** MakeDictionary(FILE *fp, char **dict, int *size_dict, int *index, int **count_words, int *status);

// --- сортиране на речника --------------------------------------------------------
void SortDictByCount(char **dict, int index,int *count_words,int choice);
void SortDictByLet(char **dict, int index,int *count_words,int choice);
//----------------------------------------------------------------------------------

//---  сортиране на речника --------------------------------------------------------
int SaveDictionary(char **dict, int index, int *count_words, char *name_file, FILE *fp);
int SaveDictionary2(char **dict, int index, int *count_words, char *name_file, FILE *fp,char *name_dict);

//----------------------------------------------------------------------------------
char ** ReadDictionary(char **dict, int *size_dict, int *index_dict, int **count_words, char *name_file, FILE *fp);

// --- записване и кодиране на речника --------------------------------------------- 
int SaveCodeFile(FILE *fp_in, FILE *fp_out, char **dict, int index, char *name_file);
int OpenDecodeFile(FILE *fp_in, FILE *fp_out, char **dict, int index);
//----------------------------------------------------------------------------------
int Words(FILE *fp);
// --- директно четене на символ от клавиатурата до EOF ---------------------------- 
int my_fgetc(FILE *fp);
//----------------------------------------------------------------------------------
void cyr_lat_toupperCP1251(char *line);
//----------------------------------------------------------------------------------
void cyr_lat_tolowerCP1251(char *line);
//----------------------------------------------------------------------------------

void LongShortSen(FILE *fp);
void LongShortDict(char **dict,int PAHindex);