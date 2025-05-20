#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>

#define MAX_LINE 2048
#define MAX_SHOWS 2000

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

typedef struct QueueShow
{
    int start;
    int end;
    int sum;
    int maxSize;
    Show *shows[5];
} QueueShow;
QueueShow *createQueueShow()
{
    QueueShow *q = (QueueShow *)malloc(sizeof(QueueShow));
    q->maxSize = 5;
    q->start = 0;
    q->end = 0;
    q->sum = 0;
    return q;
}
int isEmpty(QueueShow *q)
{
    return q->end == q->start;
}
int size(QueueShow *q)
{
    return q->end - q->start;
}
int isFull(QueueShow *q)
{
    return size(q) == 5;
}
Show *dequeue(QueueShow *q)
{
    if (isEmpty(q))
        return NULL;
    Show *removed = q->shows[q->start % q->maxSize];
    q->start++;
    q->sum -= removed->release_year;
    return removed;
}
void enqueue(QueueShow *q, Show *item)
{
    if (isFull(q))
    {
        dequeue(q);
    }
    q->shows[q->end % q->maxSize] = item;
    q->end++;
    q->sum += item->release_year;
    printf("[Media] %d\n", q->sum / size(q));
}
Show *getShowAt(QueueShow *q, int i)
{
    if (i < 0 || i >= size(q))
        return NULL;
    return q->shows[(q->start + i) % q->maxSize];
}
void printQueue(QueueShow *q)
{
    for (int i = size(q) - 1; i >= 0; i--)
    {
        Show *s = getShowAt(q, i);
        printf("[%d] ", i);
        print_show(s);
    }
}

typedef struct ListShow
{
    int maxSize;
    int size;
    Show **shows;
} ListShow;
void realoc(ListShow *list)
{
    list->maxSize *= 2;
    Show **newList = malloc(sizeof(Show *) * list->maxSize);
    for (int i = 0; i < list->size; i++)
    {
        newList[i] = list->shows[i];
    }
    free(list->shows);
    list->shows = newList;
}
void inserirInicio(ListShow *list, Show *show)
{
    if (list->size == list->maxSize)
    {
        realoc(list);
    }
    for (int i = list->size - 1; i >= 0; i--)
    {
        list->shows[i + 1] = list->shows[i];
    }
    list->shows[0] = show;
    list->size++;
}
void inserir(ListShow *list, Show *show, int posicao)
{
    if (posicao < 0 || posicao > list->size)
        return;
    if (list->size == list->maxSize)
        realoc(list);
    for (int i = list->size - 1; i >= posicao; i--)
    {
        list->shows[i + 1] = list->shows[i];
    }
    list->shows[posicao] = show;
    list->size++;
}
void inserirFim(ListShow *list, Show *show)
{
    if (list->size == list->maxSize)
    {
        realoc(list);
    }
    list->shows[list->size] = show;
    list->size++;
}
Show *removerInicio(ListShow *list)
{
    if (list->size == 0)
        return NULL;
    Show *temp = list->shows[0];
    for (int i = 1; i < list->size; i++)
    {
        list->shows[i - 1] = list->shows[i];
    }
    list->size--;
    list->shows[list->size] = NULL;
    return temp;
}
Show *remover(ListShow *list, int posicao)
{
    if (posicao < 0 || posicao >= list->size)
        return NULL;
    Show *removed = list->shows[posicao];
    for (int i = posicao + 1; i < list->size; i++)
    {
        list->shows[i - 1] = list->shows[i];
    }
    list->size--;
    list->shows[list->size] = NULL;
    return removed;
}
Show *removerFim(ListShow *list)
{
    if (list->size == 0)
        return NULL;
    list->size--;
    Show *temp = list->shows[list->size];
    list->shows[list->size] = NULL;
    return temp;
}
ListShow *createListShow()
{
    ListShow *listShows = (ListShow *)malloc(sizeof(ListShow));
    listShows->maxSize = 50;
    listShows->size = 0;
    listShows->shows = malloc(sizeof(Show *) * listShows->maxSize);
    return listShows;
}
void printList(ListShow *l)
{
    for (int i = 0; i < l->size; i++)
    {
        printf("[%d] ", i);
        print_show(l->shows[i]);
    }
}
void printStack(ListShow *s)
{
    for (int i = s->size - 1; i >= 0; i--)
    {
        printf("[%d] ", i);
        print_show(s->shows[i]);
    }
}

typedef struct Node
{
    struct Node *next;
    struct Node *previous;
    Show *value;
} Node;
Node *createNode(Show *show)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->value = show;
    newNode->next = NULL;
    newNode->previous = NULL;
    return newNode;
}

typedef struct QueueLLShow
{
    Node *head;
    Node *tail;
    int size;
    int sum;
    int maxSize;
} QueueLLShow;
QueueLLShow *createQueueLLShow()
{
    QueueLLShow *ll = (QueueLLShow *)malloc(sizeof(QueueLLShow));
    ll->head = NULL;
    ll->tail = NULL;
    ll->size = 0;
    ll->sum = 0;
    ll->maxSize = 5;
    return ll;
}
Show *dequeueLL(QueueLLShow *q)
{
    if (q->head == NULL)
        return NULL;

    Node *node = q->tail;
    Show *removed = node->value;

    if (q->head == q->tail)
    {
        q->head = NULL;
        q->tail = NULL;
    }
    else
    {
        q->tail = q->tail->previous;
        q->tail->next = NULL;
    }

    free(node);
    q->size--;
    q->sum -= removed->release_year;

    return removed;
}
void enqueueLL(QueueLLShow *q, Show *show)
{
    if (q->size == q->maxSize)
    {
        dequeueLL(q);
    }
    Node *newNode = createNode(show);
    if (q->head == NULL && q->tail == NULL)
    {
        q->tail = q->head = newNode;
        newNode->next = newNode->previous = newNode;
    }
    else
    {
        newNode->next = q->head;
        newNode->previous = q->tail;
        q->head->previous = newNode;
        q->tail->next = newNode;
        q->head = newNode;
    }
    q->size++;
    q->sum += show->release_year;

    printf("[Media] %d\n", q->sum / q->size);
}
void printQueueLL(QueueLLShow *s)
{
    Node *cur = s->tail;
    for (int i = s->size - 1; i >= 0 && cur != NULL; cur = cur->previous, i--)
    {
        printf("[%d] ", i);
        print_show(cur->value);
    }
}

typedef struct LinkedListShow
{
    Node *head;
    Node *tail;
    int size;
} LinkedListShow;
LinkedListShow *createLinkedListShow()
{
    LinkedListShow *ll = (LinkedListShow *)malloc(sizeof(LinkedListShow));
    ll->head = NULL;
    ll->tail = NULL;
    ll->size = 0;
    return ll;
}
void inserirInicioLL(LinkedListShow *list, Show *show)
{
    Node *newNode = createNode(show);
    if (list->head == NULL && list->tail == NULL)
    {
        list->tail = list->head = newNode;
    }
    else
    {
        list->head->previous = newNode;
        newNode->next = list->head;
        list->head = newNode;
    }
    list->size++;
}
void inserirFimLL(LinkedListShow *list, Show *show)
{
    if (list->head == NULL && list->tail == NULL)
    {
        inserirInicioLL(list, show);
        return;
    }
    Node *newNode = createNode(show);
    newNode->previous = list->tail;
    list->tail->next = newNode;
    list->tail = newNode;
    list->size++;
}
void inserirLL(LinkedListShow *list, Show *show, int position)
{
    if (position == 0)
    {
        inserirInicioLL(list, show);
        return;
    }
    if (position == list->size)
    {
        inserirFimLL(list, show);
        return;
    }
    Node *cur = list->head;
    for (int i = 0; cur != NULL && i < position; cur = cur->next, i++)
        ;
    Node *newNode = createNode(show);
    newNode->next = cur;
    newNode->previous = cur->previous;
    cur->previous->next = newNode;
    cur->previous = newNode;
    list->size++;
}
Show *removerInicioLL(LinkedListShow *list)
{
    if (list->head == NULL && list->tail == NULL)
        return NULL;

    Node *tempNode = list->head;
    Show *temp = tempNode->value;

    if (list->head == list->tail)
    {
        list->head = NULL;
        list->tail = NULL;
    }
    else
    {
        list->head = list->head->next;
        list->head->previous = NULL;
    }

    free(tempNode);
    list->size--;

    return temp;
}
Show *removerFimLL(LinkedListShow *list)
{
    if (list->head == NULL && list->tail == NULL || list->head == list->tail)
        return removerInicioLL(list);
    Node *tempNode = list->tail;
    Show *temp = tempNode->value;

    list->tail = list->tail->previous;
    list->tail->next = NULL;
    list->size--;
    free(tempNode);
    return temp;
}
Show *removerLL(LinkedListShow *list, int position)
{
    if (position == 0)
        return removerInicioLL(list);
    if (position == list->size)
        return removerFimLL(list);

    Node *cur = list->head;
    for (int i = 0; cur != NULL && i < position; cur = cur->next, i++)
        ;
    cur->previous->next = cur->next;
    cur->next->previous = cur->previous;
    Show *temp = cur->value;
    cur->next = NULL;
    cur->previous = NULL;
    list->size--;
    free(cur);
    return temp;
}
void printLL(LinkedListShow *list)
{
    for (Node *cur = list->head; cur != NULL; cur = cur->next)
    {
        print_show(cur->value);
    }
}
void printStackLL(LinkedListShow *s)
{
    Node *cur = s->tail;
    for (int i = s->size - 1; i >= 0 && cur != NULL; cur = cur->previous, i--)
    {
        printf("[%d] ", i);
        print_show(cur->value);
    }
}

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

void process(char *command, ListShow *showsList)
{
    int len = strlen(command);
    char **commandSplit = split(command, &len, " ");
    if (command[0] == 'R')
    {
        Show *removed = NULL;
        if (command[1] == 'I')
            removed = removerInicio(showsList);
        else if (command[1] == 'F')
            removed = removerFim(showsList);
        else if (command[1] == '*')
            removed = remover(showsList, atoi(commandSplit[1]));
        printf("(R) %s\n", removed->title);
    }
    else if (command[0] == 'I')
    {
        char *id = command[1] == '*' ? commandSplit[2] : commandSplit[1];
        Show *show = search_by_id(id);
        if (command[1] == 'I')
            inserirInicio(showsList, show);
        else if (command[1] == 'F')
            inserirFim(showsList, show);
        else if (command[1] == '*')
            inserir(showsList, show, atoi(commandSplit[1]));
    }
}
void processStack(char *command, ListShow *showsList)
{
    int len = strlen(command);
    char **commandSplit = split(command, &len, " ");
    if (command[0] == 'R')
    {
        Show *removed = NULL;
        removed = removerFim(showsList);
        printf("(R) %s\n", removed->title);
    }
    else if (command[0] == 'I')
    {
        char *id = commandSplit[1];
        Show *show = search_by_id(id);
        inserirFim(showsList, show);
    }
}
void processQueue(char *command, QueueShow *q)
{
    int len = strlen(command);
    char **commandSplit = split(command, &len, " ");
    if (command[0] == 'R')
    {
        Show *removed = NULL;
        removed = dequeue(q);
        printf("(R) %s\n", removed->title);
    }
    else if (command[0] == 'I')
    {
        char *id = commandSplit[1];
        Show *show = search_by_id(id);
        enqueue(q, show);
    }
}

void processStackLL(char *command, LinkedListShow *showsList)
{
    int len = strlen(command);
    char **commandSplit = split(command, &len, " ");
    if (command[0] == 'R')
    {
        Show *removed = NULL;
        removed = removerFimLL(showsList);
        printf("(R) %s\n", removed->title);
    }
    else if (command[0] == 'I')
    {
        char *id = commandSplit[1];
        Show *show = search_by_id(id);
        inserirFimLL(showsList, show);
    }
}
void processLL(char *command, LinkedListShow *showsList)
{
    int len = strlen(command);
    char **commandSplit = split(command, &len, " ");
    if (command[0] == 'R')
    {
        Show *removed = NULL;
        if (command[1] == 'I')
            removed = removerInicioLL(showsList);
        else if (command[1] == 'F')
            removed = removerFimLL(showsList);
        else if (command[1] == '*')
            removed = removerLL(showsList, atoi(commandSplit[1]));
        printf("(R) %s\n", removed->title);
    }
    else if (command[0] == 'I')
    {
        char *id = command[1] == '*' ? commandSplit[2] : commandSplit[1];
        Show *show = search_by_id(id);
        if (command[1] == 'I')
            inserirInicioLL(showsList, show);
        else if (command[1] == 'F')
            inserirFimLL(showsList, show);
        else if (command[1] == '*')
            inserirLL(showsList, show, atoi(commandSplit[1]));
    }
}
void processQueueLL(char *command, QueueLLShow *q)
{
    int len = strlen(command);
    char **commandSplit = split(command, &len, " ");
    if (command[0] == 'R')
    {
        Show *removed = NULL;
        removed = dequeueLL(q);
        printf("(R) %s\n", removed->title);
    }
    else if (command[0] == 'I')
    {
        char *id = commandSplit[1];
        Show *show = search_by_id(id);
        enqueueLL(q, show);
    }
}

int comp, mov;
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

int compareByDateAddedThenTitle(Show *a, Show *b)
{
    int cmpDate = compareShowDate(a->date, b->date);
    if (cmpDate != 0)
    {
        return cmpDate;
    }
    return compare(a->title, b->title);
}
void swapS(Node *a, Node *b)
{
    Show *temp = a->value;
    a->value = b->value;
    b->value = temp;
    mov += 3;
}

Node *partition(Node *low, Node *high)
{
    Show *pivot = high->value;

    Node *i = low->previous;
    for (Node *j = low; j != high;
         j = j->next)
    {
        if (compareByDateAddedThenTitle(j->value, pivot) < 0)
        {
            i = (i == NULL) ? low : i->next;
            swapS(i, j);
        }
    }
    i = (i == NULL) ? low : i->next;

    swapS(i, high);

    return i;
}

void quickSort(Node *low, Node *high)
{
    if (low != NULL && high != NULL && low != high && low != high->next)
    {
        Node *pivot = partition(low, high);
        quickSort(low, pivot->previous);
        quickSort(pivot->next, high);
    }
}
void printSortVerde(char *filename, LinkedListShow *v)
{
    clock_t inicio = clock();
    quickSort(v->head, v->tail);
    printLL(v);
    clock_t final = clock();

    char fullFilename[200];
    sprintf(fullFilename, "867936_%s.txt", filename);
    FILE *matricula = fopen(fullFilename, "w");
    double tempo = (double)(final - inicio) / CLOCKS_PER_SEC;
    fprintf(matricula, "867936\t%d\t%d\t%fs", comp, mov, tempo);
    fclose(matricula);
}
int main()
{
    start_shows("/tmp/disneyplus.csv");

    char text[1000];
    scanf(" %[^\r\n]", text);
    LinkedListShow *localShows = createLinkedListShow();
    while (strcmp((char *)text, "FIM"))
    {
        Show *s = search_by_id(text);
        if (s)
        {
            inserirFimLL(localShows, s);
        }
        else
        {
            printf("x Show not found!\n");
        }
        scanf(" %[^\r\n]", text);
    }
    // int size;
    // scanf("%d", &size);
    // for (int i = 0; i < size; i++)
    // {
    //     scanf(" %[^\r\n]", text);
    //     processQueueLL(text, localShows);
    // }

    printSortVerde("quicksort", localShows);
    return 0;
}