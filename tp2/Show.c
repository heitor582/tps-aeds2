#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>

#define MAX_LINE 2048
#define MAX_SHOWS 2000

typedef struct Date{
    int day;
    int month;
    int year;
}Date;
typedef struct Show{
    char* show_id;
    char* type;
    char* title;
    char* director;
    char** cast;
    int cast_size;
    char* country;
    char* date_added;
    Date date;
    int release_year;
    char* range;
    char* duration;
    char** listed_in;
    int listed_in_size;
} Show;
Show* shows[MAX_SHOWS];
int shows_count = 0;
int mov = 0;
int comp = 0;
int monthToNumber(char mes[]){
    if(strcmp(mes, "January") == 0){
        return 1;
    }else if(strcmp(mes, "February") == 0){
        return 2;
    }else if(strcmp(mes, "March") == 0){
        return 3;
    }else if(strcmp(mes, "April") == 0){
        return 4;
    }else if(strcmp(mes, "May") == 0){
        return 5;
    }else if(strcmp(mes, "June") == 0){
        return 6;
    }else if(strcmp(mes, "July") == 0){
        return 7;
    }else if(strcmp(mes, "August") == 0){
        return 8;
    }else if(strcmp(mes, "September") == 0){
        return 9;
    }else if(strcmp(mes, "October") == 0){
        return 10;
    }else if(strcmp(mes, "November") == 0){
        return 11;
    }else if(strcmp(mes, "December") == 0){
        return 12;
    }
    return 0;
}
Date dateToInt(char data[]){
    //September 24, 2021
        char month[20], day[5], year[10];
        int i = 0, j = 0;
        Date d;
        
        while (data[i] != ' ') {
            month[j++] = data[i++];
        }
        month[j] = '\0'; 
        i++; 
        
        j = 0;
        while (data[i] != ',') {
            day[j++] = data[i++];
        }
        day[j] = '\0';
        i += 2; 

        j = 0;
        while (data[i] != '\0') {
            year[j++] = data[i++];
        }
        year[j] = '\0';

        d.day = atoi(day);
        d.month = monthToNumber(month);
        d.year = atoi(year);
        
        return d;
}
void swap(char** v, int i, int j){
    char* temp = v[i];
    v[i] = v[j];
    v[j] = temp;
    mov+=3;
}
void swapShows(Show** v, int i, int j){
    Show* temp = v[i];
    v[i] = v[j];
    v[j] = temp;
    mov+=3;
}
int compare(char* a, char* b){
    comp++;
    return strcmp(a,b);
}
int compareSensitive(char* a, char* b){
    comp++;
    return strcasecmp(a,b);
}
int compareShowsByTypeThenTitle(Show* a, Show* b) {
    int cmpType = compare(a->type, b->type);
    if (cmpType != 0) {
        return cmpType;
    }

    return compare(a->title, b->title);
}
int compareShowDate(Date a, Date b){
    if(a.year > b.year){
        comp += 1;
        return 1;
    } else if(a.year < b.year){
        comp += 2;
        return -1;
    }

    if(a.month > b.month){
        comp += 3;
        return 1;
    } else if(a.month < b.month){
        comp += 4;
        return -1;
    }

    if(a.day > b.day){
        comp += 5;
        return 1;
    } else if(a.day < b.day){
        comp += 6;
        return -1;
    }

    comp += 6;
    return 0;
}
int compareByDateAddedThenTitle(Show* a, Show* b) {
    int cmpDate = compareShowDate(a->date, b->date);
    if (cmpDate != 0) {
        return cmpDate;
    }
    return compare(a->title, b->title);
}
int compareByDirectorThenTitle(Show* a, Show* b){
    int cmpDate = compare(a->director, b->director);
    if (cmpDate != 0) {
        return cmpDate;
    }
    return compare(a->title, b->title);
}
void quicksortRec(Show* array[], int esq, int dir) {
    int i = esq, j = dir;
    Show* pivo = array[esq+(dir-esq)/2];
    while (i <= j) {
        while (compareByDateAddedThenTitle(array[i], pivo) < 0) i++;
        while (compareByDateAddedThenTitle(array[j], pivo) > 0) j--;
        if (i <= j) {
            swapShows(array, i, j);
            i++;
            j--;
        }
    }
    if (esq < j)  quicksortRec(array, esq, j);
    if (i < dir)  quicksortRec(array, i, dir);
}
void quicksort(Show* v[], int size) {
    quicksortRec(v, 0, size-1);
}
void heapSort(char** v, int size){
    for(int i = 1; i<size; i++){
        for(int j = i; j>0 && strcmp(v[j], v[(j-1)/2]) > 0; j=(j-1)/2){
            swap(v, j, (j-1)/2);
        }
    }

    for(int i = size-1; i>=0; i--){
        swap(v, i, 0);
        int j =0;
        while(j<i && (j*2+1 < i || j*2+2 < i)){
            int ji = j*2+2 < i && strcmp(v[j*2+2], v[j*2+1]) > 0 ? j*2+2 : j*2+1;
            if(strcmp(v[j], v[ji]) < 0){
                swap(v,j,ji);
                j=ji;
            } else {
                j=i;
            }
        }
    }
}
char* strdup_strip(char* src) {
    while (*src == ' ' || *src == '"') src++; 
    size_t len = strlen(src);
    while (len > 0 && (src[len - 1] == ' ' || src[len - 1] == '"')) len--;
    char* dst = (char*)malloc(len + 1);
    strncpy(dst, src, len);
    dst[len] = '\0';
    return dst;
}
char** split(char* str, int* count) {
    char** result = NULL;
    int size = 0;

    char* temp = strdup(str);
    char* token = strtok(temp, ",");

    while (token != NULL) {
        result = (char**)realloc(result, sizeof(char*) * (size + 1));
        result[size++] = strdup_strip(token);
        token = strtok(NULL, ",");
    }

    free(temp);
    *count = size;
    return result;
}
Show* parse_show(char* line) {
    Show* s = (Show*)malloc(sizeof(Show));
    if (!s) {
        fprintf(stderr, "Erro ao alocar memória para Show\n");
        return NULL;
    }

    char* fields[11];
    char* field = (char*)malloc(strlen(line) + 1);
    if (!field) {
        fprintf(stderr, "Erro ao alocar memória para campo\n");
        free(s);
        return NULL;
    }

    int i = 0, f_index = 0;
    bool in_quotes = false;

    for (int j = 0; line[j] != '\0'; j++) {
        char c = line[j];
        if (c == '"') {
            in_quotes = !in_quotes;
        } else if (c == ',' && !in_quotes) {
            field[f_index] = '\0';
            fields[i++] = strdup_strip(field);
            f_index = 0;
        } else {
            field[f_index++] = c;
        }
    }
    field[f_index] = '\0';
    if (i < 11) {
        fields[i++] = strdup_strip(field);
    }
    free(field);
    if (i != 11) {
        fprintf(stderr, "Linha malformada (esperado 11 campos, obtido %d): %s\n", i, line);
        free(s);
        for (int k = 0; k < i; k++) free(fields[k]);
        return NULL;
    }

    s->show_id = strlen(fields[0]) > 0 ? fields[0] : "NaN";
    s->type = strlen(fields[1]) > 0 ? fields[1] : "NaN";
    s->title = strlen(fields[2]) > 0 ? fields[2] : "NaN";
    s->director = strlen(fields[3]) > 0 ? fields[3] : "NaN";
    s->cast = split(fields[4], &s->cast_size);
    if (s->cast_size > 0) {
        heapSort(s->cast, s->cast_size);
    }
    s->country = strlen(fields[5]) > 0 ? fields[5] : "NaN";
    s->date_added = strlen(fields[6]) > 0 ? fields[6] : "March 1, 1900";
    s->date = dateToInt(s->date_added);
    s->release_year = strlen(fields[7]) > 0 ? atoi(fields[7]) : -1;
    s->range = strlen(fields[8]) > 0 ? fields[8] : "NaN";
    s->duration = strlen(fields[9]) > 0 ? fields[9] : "NaN";
    s->listed_in = split(fields[10], &s->listed_in_size);
    if (s->listed_in_size > 0) {
        heapSort(s->listed_in, s->listed_in_size);
    }

    return s;
}
void print_show(Show* s) {
    printf("=> %s ## %s ## %s ## %s ## [", s->show_id, s->title, s->type, s->director);
    if(s->cast_size > 0){
        for (int i = 0; i < s->cast_size; i++) {
            printf("%s%s", s->cast[i], i < s->cast_size - 1 ? ", " : "");
        }
    } else {
        printf("%s", "NaN");
    }
    printf("] ## %s ## %s ## %d ## %s ## %s ## [", s->country, s->date_added, s->release_year, s->range, s->duration);
    if(s->listed_in_size > 0){
        for (int i = 0; i < s->listed_in_size; i++) {
            printf("%s%s", s->listed_in[i], i < s->listed_in_size - 1 ? ", " : "");
        }
    } else {
        printf("%s", "NaN");
    }
    printf("] ##\n");
}
Show* search_by_id(char* id) {
    for (int i = 0; i < shows_count; i++) {
        if (strcmp(shows[i]->show_id, id) == 0) return shows[i];
    }
    return NULL;
}
void start_shows(char* path) {
    FILE* file = fopen(path, "r");
    if (!file) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    char line[MAX_LINE];
    fscanf(file, " %[^\r\n]", line);
    int i = 1;
    while (fscanf(file, " %[^\r\n]", line) != EOF) {
        Show* s = parse_show(line);
        if (s != NULL) {
            shows[shows_count++] = s;
        } else {
            printf("[ERRO] Parse falhou para: %s\n", line);
        }
    }

    fclose(file);
}
Show* binarySearch(Show* localShows[], int size, char* title){
    int left = 0, right = size-1;
    while(left <= right){
        int mid = left + (right-left)/2;
        int comp = compare(localShows[mid]->title, title);
        if(comp == 0) {
            return localShows[mid];
        }else if(comp > 0){
            right = mid-1;
        } else{
            left = mid + 1;
        }
    }
    return NULL;
}
void printVerde(char* filename, clock_t inicio){
    char fullFilename[200];
    sprintf(fullFilename, "867936_%s.txt", filename);
    FILE *matricula = fopen(fullFilename, "w");
    clock_t final = clock();
    double tempo = (double)(final - inicio) / CLOCKS_PER_SEC;
    fprintf(matricula, "867936\t%fs\t%d", tempo, comp);
    fclose(matricula);
}
void printSortVerde(char* filename, void (*sort)(Show* v[], int size), Show* v[], int size){
    clock_t inicio = clock();
    sort(v,size);
    for(int i = 0; i<size; i++) {
        print_show(v[i]);
    }
    clock_t final = clock();

    char fullFilename[200];
    sprintf(fullFilename, "867936_%s.txt", filename);
    FILE *matricula = fopen(fullFilename, "w");
    double tempo = (double)(final - inicio) / CLOCKS_PER_SEC;
    fprintf(matricula, "867936\t%fs\t%d", tempo, comp);
    fclose(matricula);
}
void printSortVerdeParcial(char* filename, void (*sort)(Show* v[], int size, int steps), Show* v[], int size, int steps){
    clock_t inicio = clock();
    sort(v,size, steps);
    for(int i = 0; i<steps; i++) {
        print_show(v[i]);
    }
    clock_t final = clock();

    char fullFilename[200];
    sprintf(fullFilename, "867936_%s.txt", filename);
    FILE *matricula = fopen(fullFilename, "w");
    double tempo = (double)(final - inicio) / CLOCKS_PER_SEC;
    fprintf(matricula, "867936\t%fs\t%d", tempo, comp);
    fclose(matricula);
}
int compareShowsByTitle(const void* a, const void* b) {
    Show* s1 = (Show*)a;
    Show* s2 = (Show*)b;
    return compare(s1->title, s2->title);
}
void selectionSortRec(Show* v[], int size, int i){
    if(i >= size){
        return;
    }
    int min = i;
    for(int j = i+1; j<size; j++){
        if(compareShowsByTitle(v[min], v[j]) > 0){
            min = j;
        }
    }
    swapShows(v, i, min);
    selectionSortRec(v, size, i+1);
    return;
}
void selectionSortRecursive(Show* v[], int size){
    selectionSortRec(v, size, 0);
}
void shellSort(Show* v[], int size) {
    for (int gap = size / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < size; i++) {
            Show* temp = v[i];
            int j;
            for (j = i; j >= gap && compareShowsByTypeThenTitle(v[j - gap], temp) > 0; j -= gap) {
                v[j] = v[j - gap];
                mov++;
            }
            v[j] = temp;
            mov++;
        }
    }
}
void bubbleSort(Show* v[], int size){
    int swaped = 1;
    for(int i = 0; i<size-1 && swaped; i++){
        swaped = 0;
        for(int j = 0; j < size-i-1; j++){
            if(compareByDateAddedThenTitle(v[j], v[j+1])>0){
                swapShows(v,j,j+1);
                swaped=1;
            }
        }
    }
}
void insercaoParcial(Show* v[], int size, int steps){
    for (int i = 1; i < size; i++) {
        Show* current = v[i];
        int j = i<steps ? i - 1 : steps - 1;
        
        while (j >= 0 && compareShowsByTypeThenTitle(v[j], current) > 0) {
            v[j+1] = v[j];
            j--;
        }
        v[j+1] = current;
    }
}
void heapsortPartial(Show* v[], int size, int steps){
    for(int i = 1; i<=steps;i++){
        for(int j = i; j>0 && compareByDirectorThenTitle(v[j], v[(j-1)/2]) > 0; j=(j-1)/2){
            swapShows(v, j, (j-1)/2);
        }
    }
    for(int i = steps+1; i<size; i++){
        swapShows(v,i,0);
        int j = 0;
        while(j<steps && (j*2+1 < steps || j*2+2 < steps) ){
            int ji = j*2+2 < i && compareByDirectorThenTitle(v[j*2+2], v[j*2+1]) > 0? j*2+2 : j*2+1;
            if(compareByDirectorThenTitle(v[ji], v[j]) > 0){
                swapShows(v, j, ji);
                j=ji;
            } else {
                j=i;
            }
        }
    }

    for(int i = steps; i>0;i--){
        swapShows(v,0,i);
        int j = 0;
        while(j<i && (j*2+1 < i || j*2+2 < i) ){
            int ji = j*2+2 < i && compareByDirectorThenTitle(v[j*2+2], v[j*2+1]) > 0? j*2+2 : j*2+1;
            if(compareByDirectorThenTitle(v[ji], v[j]) >0){
                swapShows(v, j, ji);
                j=ji;
            } else {
                j=i;
            }
        }
    }
}


int getMax(Show* array[], int tam) {
    int max = array[0]->release_year;
    for (int i = 1; i < tam; i++) {
        if (array[i]->release_year > max) {
            max = array[i]->release_year;
        }
    }
    return max;
}

int getMaxString(Show* array[], int tam){
    int max = 0;
    
    for (int i = 0; i < tam; i++) {
        int len = strlen(array[i]->title);
        if (len > max) {
            max = len;
        }
    }
    return max;
}

void countingsort(Show* array[], int n, int esp) {
    Show** ordenado = (Show**) malloc(n * sizeof(Show*));
    int count[10] = {0};
    for (int i = 0; i < n; i++) {
        int digit = (array[i]->release_year / esp) % 10;
        count[digit]++;
    }
    for (int i = 1; i < 10; i++) {
        count[i] += count[i-1];
    }
    for (int i = n - 1; i >= 0; i--) {
        int digit = (array[i]->release_year / esp) % 10;
        ordenado[count[digit] - 1] = array[i];
        count[digit]--;
        mov++;
    }
    for (int i = 0; i < n; i++) {
        array[i] = ordenado[i];
        mov++;
    }
    free(ordenado);
}

void countingsortString(Show* array[], int n, int esp) {
    Show** ordenado = (Show**) malloc(n * sizeof(Show*));
    int count[256] = {0};
    
    for (int i = 0; i < n; i++) {
        int digit = (strlen(array[i]->title) > esp) ? (unsigned char)tolower(array[i]->title[esp]) : 0;
        count[digit]++;
    }
    for (int i = 1; i < 256; i++) {
        count[i] += count[i-1];
    }
    for (int i = n - 1; i >= 0; i--) {
        int digit = (strlen(array[i]->title) > esp) ? (unsigned char)tolower(array[i]->title[esp]) : 0;
        ordenado[count[digit] - 1] = array[i];
        count[digit]--;
        mov++;
    }
    for (int i = 0; i < n; i++) {
        array[i] = ordenado[i];
        mov++;
    }
    free(ordenado);
}

//Time: O(d * (n + b)), where d is the number of digits, n is the number of elements, and b is the base of the number system being used.
//Space: O(n + b)
void radixsortVerde(Show* array[], int tam) {
    int max = getMax(array, tam);
    int x = 0, p = 0, m = 0, ano;

    for (int esp = 1; max / esp > 0; esp *= 10) {
        countingsort(array, tam, esp);
    }
    
    while(x != tam){
        ano = array[x]->release_year;
        while(x < tam && array[x]->release_year == ano){
            x++;
        }
        int listaTam = x - p;
        Show** lista = (Show**) malloc(listaTam * sizeof(Show*));
        for (int i = 0; i < listaTam; i++) {
            lista[i] = array[p+i];
        }
        
        max = getMaxString(lista, listaTam);
        for (int pos = max - 1; pos >= 0; pos--) {
            countingsortString(lista, listaTam, pos);
        }
        
        for(int i = 0; i < listaTam; i++){
            array[p+i] = lista[i];
        }
        p = x;
        
        free(lista);
    }
}

int main() {
    start_shows("/tmp/disneyplus.csv");
    
    char text[1000];
    scanf(" %[^\r\n]", text);
    Show* localShows[MAX_SHOWS];
    int count = 0;
    while (strcmp((char*)text, "FIM")) {
        Show* s = search_by_id(text);
        if (s) {
            localShows[count++] = s;
        } else {
            printf("x Show not found!\n");
        }
        scanf(" %[^\r\n]", text);
    }

    clock_t inicio = clock();
    selectionSortRecursive(localShows, count);
    comp--;
    scanf(" %[^\r\n]", text);
    while (strcmp((char*)text, "FIM")) {
        Show* s = binarySearch(localShows, count, text);
        if(s != NULL){
            printf("SIM\n");
        }else{
            printf("NAO\n");
        }
        scanf(" %[^\r\n]", text);
    }
    printVerde("binaria", inicio);
    
    //printSortVerde("selecaoRecursiva", selectionSortRecursive,localShows,count);
    //printSortVerde("shellsort", shellSort,localShows,count);
    //printSortVerdeParcial("insercaoparcial", insercaoParcial,localShows,count,10);
    printSortVerdeParcial("heapparcial", heapsortPartial,localShows,count,10);
    //printSortVerde("bolha", bubbleSort,localShows,count);
    //printSortVerde("quicksort", quicksort,localShows,count);
    //printSortVerde("radixsort", radixsortVerde,localShows,count);
    return 0;
}