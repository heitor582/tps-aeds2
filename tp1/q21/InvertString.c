#include<stdio.h>
#include<string.h>
#include<locale.h>
#include<ctype.h>

void invert(unsigned char* s, int i){
    int len = strlen((char*)s);
    int j = len - 1 - i;

    if (j==-1) {
        return;
    }

    int charSize = 1;
    if (j-2 >= 0 && s[j-1] == 195) {
        printf("%c%c", s[j-1], s[j]);
        charSize = 2;
    } else if (j-3 >= 0 && s[j-2] == 239) {
        printf("%c%c%c", s[j-2], s[j-1], s[j]);
        charSize = 3;
    }else {
        printf("%c", s[j]);
    }

    invert(s, i + charSize);
}

int main() {
    unsigned char text[1000];
    scanf(" %[^\r\n]", text);
    while (strcmp((char*)text, "FIM")) {
        invert(text, 0);
        printf("\n");
        scanf(" %[^\r\n]", text);
    }

    return 0;
}