#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define MAX_LINE 2048
#define MAX_SHOWS 1000

typedef struct {
    char* show_id;
    char* type;
    char* title;
    char* director;
    char** cast;
    int cast_size;
    char* country;
    char* date_added;
    int release_year;
    char* range;
    char* duration;
    char** listed_in;
    int listed_in_size;
} Show;

Show* shows[MAX_SHOWS];
int shows_count = 0;

char* strdup_strip(const char* src) {
    while (*src == ' ' || *src == '"') src++; 
    size_t len = strlen(src);
    while (len > 0 && (src[len - 1] == ' ' || src[len - 1] == '"')) len--;
    char* dst = (char*)malloc(len + 1);
    strncpy(dst, src, len);
    dst[len] = '\0';
    return dst;
}

char** split(const char* str, int* count) {
    char* temp = strdup(str);
    char* token = strtok(temp, ",");
    char** result = NULL;
    int size = 0;

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

    s->show_id = fields[0];
    s->type = fields[1];
    s->title = fields[2];
    s->director = fields[3];
    s->cast = split(fields[4], &s->cast_size); // ordernar dps
    s->country = fields[5];
    s->date_added = strlen(fields[6]) > 0 ? fields[6] : NULL;
    s->release_year = strlen(fields[7]) > 0 ? atoi(fields[7]) : -1;
    s->range = fields[8];
    s->duration = fields[9];
    s->listed_in = split(fields[10], &s->listed_in_size); // ordernar dps

    return s;
}

void print_show(Show* s) {
    printf("=> %s ## %s ## %s ## %s ## [", s->show_id, s->type, s->title, s->director);
    for (int i = 0; i < s->cast_size; i++) {
        printf("%s%s", s->cast[i], i < s->cast_size - 1 ? ", " : "");
    }
    printf("] ## %s ## %s ## %d ## %s ## %s ## [", s->country, s->date_added ? s->date_added : "NaN", s->release_year, s->range, s->duration);
    for (int i = 0; i < s->listed_in_size; i++) {
        printf("%s%s", s->listed_in[i], i < s->listed_in_size - 1 ? ", " : "");
    }
    printf("]\n");
}

Show* search_by_id(const char* id) {
    for (int i = 0; i < shows_count; i++) {
        if (strcmp(shows[i]->show_id, id) == 0) return shows[i];
    }
    return NULL;
}

void start_shows(const char* path) {
    FILE* file = fopen(path, "r");
    if (!file) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    char line[MAX_LINE];
    fgets(line, sizeof(line), file); 

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;
        shows[shows_count++] = parse_show(line);
    }

    fclose(file);
}

int main() {
    start_shows("/tmp/disneyplus.csv");

    char input[64];
    while (fgets(input, sizeof(input), stdin)) {
        input[strcspn(input, "\n")] = 0;
        if (strcmp(input, "FIM") == 0) break;

        Show* s = search_by_id(input);
        if (s) {
            print_show(s);
        } else {
            printf("x Show not found!\n");
        }
    }

    return 0;
}