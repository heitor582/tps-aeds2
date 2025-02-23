#include<stdio.h>
#include<string.h>
#include<locale.h>
#include<ctype.h>

char* invert(char* s, int i){
    int j = strlen(s) - 1 -i;
    if(i>=j){
        return s;
    }
    char temp = s[i];
    s[i] = s[j];
    s[j] = temp;
    return invert(s, i+1);
}

int main() {
    unsigned char text[1000];
    scanf(" %[^\r\n]", text);
    while (strcmp((char*)text, "FIM")) {
        int sum = sumDigits((int)text);
        printf("%d\n", sum);
        scanf(" %[^\n]", text);
    }

    return 0;
}