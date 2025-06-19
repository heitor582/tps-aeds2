#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>

#define MAX_LINE 2048
#define MAX_SHOWS 2000
int compare(char *a, char *b);
typedef struct TreeNode{
    char* value;
    int height;
    struct TreeNode* right;
    struct TreeNode* left;
} TreeNode;
typedef struct AVLTree{
    TreeNode* root;
} AVLTree;
TreeNode* createNode(char* value) {
    TreeNode* node = (TreeNode*) malloc(sizeof(TreeNode));
    node->value = strdup(value);
    node->height = 1;
    node->left = node->right = NULL;
    return node;
}
AVLTree* newTree(){
    AVLTree* avlTree = (AVLTree*) malloc(sizeof(AVLTree));
    avlTree->root = NULL;
    return avlTree;
}
int getHeight(TreeNode* node){
    if(node == NULL) return 0;
    return node->height;
}
int getBalance(TreeNode* node){
    if(node == NULL) return 0;

    return getHeight(node->left) - getHeight(node->right);
}

TreeNode* rightRotation(TreeNode* node){
    TreeNode* newRoot = node->left;
    node->left = node->left->right;
    newRoot->right = node;
    
    node->height = 1 + (getHeight(node->left) > getHeight(node->right) ? getHeight(node->left) : getHeight(node->right));
    newRoot->height = 1 + (getHeight(newRoot->left) > getHeight(newRoot->right) ? getHeight(newRoot->left) : getHeight(newRoot->right));
     
    return newRoot;
}
TreeNode* leftRotation(TreeNode* node){
    TreeNode* newRoot = node->right;
    node->right = node->right->left;
    newRoot->left = node;

    node->height = 1 + (getHeight(node->left) > getHeight(node->right) ? getHeight(node->left) : getHeight(node->right));
    newRoot->height = 1 + (getHeight(newRoot->left) > getHeight(newRoot->right) ? getHeight(newRoot->left) : getHeight(newRoot->right));
     
    return newRoot;
}

TreeNode* insert(TreeNode* node, char* value){
    if(node == NULL){
        node = createNode(value);
    } else if(compare(value, node->value) < 0){
        node->left = insert(node->left, value);
    } else if(compare(value, node->value) > 0){
        node->right = insert(node->right, value);
    }

    node->height = 1 + (getHeight(node->left) > getHeight(node->right) ? getHeight(node->left) : getHeight(node->right));
    int balance = getBalance(node);
    if(balance > 1 && node->left != NULL && compare(value, node->left->value) < 0){
        node = rightRotation(node);
    } else if(balance > 1 && node->left != NULL && compare(value, node->left->value) > 0){
        node->left = leftRotation(node->left);
        node = rightRotation(node);
    }else if(balance < -1 && node->right != NULL && compare(value, node->right->value) > 0){
        node = leftRotation(node);
    } else if(balance < -1 && node->right != NULL && compare(value, node->right->value) < 0){
        node->right = rightRotation(node->right);
        node = leftRotation(node);
    }

    return node;
}

int search(char* value, TreeNode* node){
        int resp = 0;
        
        if(node == NULL) {
            resp = 0;
        } else if(compare(value, node->value) > 0){
            printf("dir  ");
            resp = search(value, node->right);
        } else if(compare(value, node->value) < 0){
            printf("esq  ");
            resp = search(value, node->left);
        } else {
            resp = 1;
        }
        return resp;
    }
int searchInTree(AVLTree* tree, char* value) {
        printf("raiz  ");
        int resp = search(value, tree->root);
        if(resp){
            printf("SIM\n");
        }else{
            printf("NAO\n");
        }
        return resp;
    }

typedef struct Date
{
    int day;
    int month;
    int year;
} Date;
typedef struct Show
{
    char *show_id;
    char *type;
    char *title;
    char *director;
    char **cast;
    int cast_size;
    char *country;
    char *date_added;
    Date date;
    int release_year;
    char *range;
    char *duration;
    char **listed_in;
    int listed_in_size;
} Show;
Show *shows[MAX_SHOWS];
void print_show(Show *show);

int shows_count = 0;
void swap(char **v, int i, int j)
{
    char *temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}
int monthToNumber(char mes[])
{
    if (strcmp(mes, "January") == 0)
    {
        return 1;
    }
    else if (strcmp(mes, "February") == 0)
    {
        return 2;
    }
    else if (strcmp(mes, "March") == 0)
    {
        return 3;
    }
    else if (strcmp(mes, "April") == 0)
    {
        return 4;
    }
    else if (strcmp(mes, "May") == 0)
    {
        return 5;
    }
    else if (strcmp(mes, "June") == 0)
    {
        return 6;
    }
    else if (strcmp(mes, "July") == 0)
    {
        return 7;
    }
    else if (strcmp(mes, "August") == 0)
    {
        return 8;
    }
    else if (strcmp(mes, "September") == 0)
    {
        return 9;
    }
    else if (strcmp(mes, "October") == 0)
    {
        return 10;
    }
    else if (strcmp(mes, "November") == 0)
    {
        return 11;
    }
    else if (strcmp(mes, "December") == 0)
    {
        return 12;
    }
    return 0;
}
Date dateToInt(char data[])
{
    // September 24, 2021
    char month[20], day[5], year[10];
    int i = 0, j = 0;
    Date d;

    while (data[i] != ' ')
    {
        month[j++] = data[i++];
    }
    month[j] = '\0';
    i++;

    j = 0;
    while (data[i] != ',')
    {
        day[j++] = data[i++];
    }
    day[j] = '\0';
    i += 2;

    j = 0;
    while (data[i] != '\0')
    {
        year[j++] = data[i++];
    }
    year[j] = '\0';

    d.day = atoi(day);
    d.month = monthToNumber(month);
    d.year = atoi(year);

    return d;
}
void heapSort(char **v, int size)
{
    for (int i = 1; i < size; i++)
    {
        for (int j = i; j > 0 && strcmp(v[j], v[(j - 1) / 2]) > 0; j = (j - 1) / 2)
        {
            swap(v, j, (j - 1) / 2);
        }
    }

    for (int i = size - 1; i >= 0; i--)
    {
        swap(v, i, 0);
        int j = 0;
        while (j < i && (j * 2 + 1 < i || j * 2 + 2 < i))
        {
            int ji = j * 2 + 2 < i && strcmp(v[j * 2 + 2], v[j * 2 + 1]) > 0 ? j * 2 + 2 : j * 2 + 1;
            if (strcmp(v[j], v[ji]) < 0)
            {
                swap(v, j, ji);
                j = ji;
            }
            else
            {
                j = i;
            }
        }
    }
}
char *strdup_strip(char *src)
{
    while (*src == ' ' || *src == '"')
        src++;
    size_t len = strlen(src);
    while (len > 0 && (src[len - 1] == ' ' || src[len - 1] == '"'))
        len--;
    char *dst = (char *)malloc(len + 1);
    strncpy(dst, src, len);
    dst[len] = '\0';
    return dst;
}
char **split(char *str, int *count, char *primaryToken)
{
    char **result = NULL;
    int size = 0;

    char *temp = strdup(str);
    char *token = strtok(temp, primaryToken);

    while (token != NULL)
    {
        result = (char **)realloc(result, sizeof(char *) * (size + 1));
        result[size++] = strdup_strip(token);
        token = strtok(NULL, primaryToken);
    }

    free(temp);
    *count = size;
    return result;
}
Show *parse_show(char *line)
{
    Show *s = (Show *)malloc(sizeof(Show));
    if (!s)
    {
        fprintf(stderr, "Erro ao alocar memória para Show\n");
        return NULL;
    }

    char *fields[11];
    char *field = (char *)malloc(strlen(line) + 1);
    if (!field)
    {
        fprintf(stderr, "Erro ao alocar memória para campo\n");
        free(s);
        return NULL;
    }

    int i = 0, f_index = 0;
    bool in_quotes = false;

    for (int j = 0; line[j] != '\0'; j++)
    {
        char c = line[j];
        if (c == '"')
        {
            in_quotes = !in_quotes;
        }
        else if (c == ',' && !in_quotes)
        {
            field[f_index] = '\0';
            fields[i++] = strdup_strip(field);
            f_index = 0;
        }
        else
        {
            field[f_index++] = c;
        }
    }
    field[f_index] = '\0';
    if (i < 11)
    {
        fields[i++] = strdup_strip(field);
    }
    free(field);
    if (i != 11)
    {
        fprintf(stderr, "Linha malformada (esperado 11 campos, obtido %d): %s\n", i, line);
        free(s);
        for (int k = 0; k < i; k++)
            free(fields[k]);
        return NULL;
    }

    s->show_id = strlen(fields[0]) > 0 ? fields[0] : strdup("NaN");
    s->type = strlen(fields[1]) > 0 ? fields[1] : strdup("NaN");
    s->title = strlen(fields[2]) > 0 ? fields[2] : strdup("NaN");
    s->director = strlen(fields[3]) > 0 ? fields[3] : strdup("NaN");
    s->cast = split(fields[4], &s->cast_size, ",");
    if (s->cast_size > 0)
    {
        heapSort(s->cast, s->cast_size);
    }
    s->country = strlen(fields[5]) > 0 ? fields[5] : strdup("NaN");
    s->date_added = strlen(fields[6]) > 0 ? fields[6] : strdup("March 1, 1900");
    s->date = dateToInt(s->date_added);
    s->release_year = strlen(fields[7]) > 0 ? atoi(fields[7]) : -1;
    s->range = strlen(fields[8]) > 0 ? fields[8] : strdup("NaN");
    s->duration = strlen(fields[9]) > 0 ? fields[9] : strdup("NaN");
    s->listed_in = split(fields[10], &s->listed_in_size, ",");
    if (s->listed_in_size > 0)
    {
        heapSort(s->listed_in, s->listed_in_size);
    }

    return s;
}
void print_show(Show *s)
{
    printf("=> %s ## %s ## %s ## %s ## [", s->show_id, s->title, s->type, s->director);
    if (s->cast_size > 0)
    {
        for (int i = 0; i < s->cast_size; i++)
        {
            printf("%s%s", s->cast[i], i < s->cast_size - 1 ? ", " : "");
        }
    }
    else
    {
        printf("%s", strdup("NaN"));
    }
    printf("] ## %s ## %s ## %d ## %s ## %s ## [", s->country, s->date_added, s->release_year, s->range, s->duration);
    if (s->listed_in_size > 0)
    {
        for (int i = 0; i < s->listed_in_size; i++)
        {
            printf("%s%s", s->listed_in[i], i < s->listed_in_size - 1 ? ", " : "");
        }
    }
    else
    {
        printf("%s", strdup("NaN"));
    }
    printf("] ##\n");
}
Show *search_by_id(char *id)
{
    for (int i = 0; i < shows_count; i++)
    {
        if (strcmp(shows[i]->show_id, id) == 0)
            return shows[i];
    }
    return NULL;
}
void start_shows(char *path)
{
    FILE *file = fopen(path, "r");
    if (!file)
    {
        perror("Erro ao abrir o arquivo");
        return;
    }

    char line[MAX_LINE];
    fscanf(file, " %[^\r\n]", line);
    int i = 1;
    while (fscanf(file, " %[^\r\n]", line) != EOF)
    {
        Show *s = parse_show(line);
        if (s != NULL)
        {
            shows[shows_count++] = s;
        }
        else
        {
            printf("[ERRO] Parse falhou para: %s\n", line);
        }
    }

    fclose(file);
}
int comp, mov;
void printVerde(char *filename, clock_t init)
{
    clock_t end = clock();

    char fullFilename[200];
    sprintf(fullFilename, "867936_%s.txt", filename);
    FILE *matricula = fopen(fullFilename, "w");
    double tempo = (double)(end - init) / CLOCKS_PER_SEC;
    fprintf(matricula, "867936\t%fs\t%d", tempo, comp);
    fclose(matricula);
}
int compare(char *a, char *b)
{
    comp++;
    return strcmp(a, b);
}
int compareShowDate(Date a, Date b)
{
    if (a.year > b.year)
    {
        comp += 1;
        return 1;
    }
    else if (a.year < b.year)
    {
        comp += 2;
        return -1;
    }

    if (a.month > b.month)
    {
        comp += 3;
        return 1;
    }
    else if (a.month < b.month)
    {
        comp += 4;
        return -1;
    }

    if (a.day > b.day)
    {
        comp += 5;
        return 1;
    }
    else if (a.day < b.day)
    {
        comp += 6;
        return -1;
    }

    comp += 6;
    return 0;
}
int main(void)
{
    start_shows("/tmp/disneyplus.csv");

    char text[1000];
    scanf(" %[^\r\n]", text);

    AVLTree* tree = newTree();

    while (strcmp((char *)text, "FIM"))
    {
        Show *s = search_by_id(text);
        if (s)
        {
            tree->root = insert(tree->root, s->title);
        }
        else
        {
            printf("x Show not found!\n");
        }
        scanf(" %[^\r\n]", text);
    }

    clock_t init = clock();
    scanf(" %[^\r\n]", text);
    while (strcmp((char *)text, "FIM"))
    {
        searchInTree(tree, text);
        scanf(" %[^\r\n]", text);
    }
    printVerde("avl", init);

    return (0);
}