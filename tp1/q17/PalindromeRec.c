#include<stdio.h>
#include<string.h>
#include<locale.h>
#include<ctype.h>

int isPalindrome(unsigned char* s, int i){
    int len = strlen((char*)s);
    if(i >= len - i - 1){
        return 1;
    }
    int icpy = i;
    if (s[icpy] == 195) { // special char with 2 bytes, so get the first position that is 195
        icpy++;
        if (s[icpy] != s[len - icpy]) return 0; // compare the second bytes
    } else if (s[icpy] == 239) { // special char with 3 bytes
        icpy += 2;
        if (s[len - icpy - 1] != 239 ) return 0; // compare the third bytes
    } else if (s[icpy] != s[len - icpy - 1]) {
        return 0;
    }

    return isPalindrome(s, icpy + 1);
}

int main() {
    setlocale(LC_ALL, "pt_BR.utf8");
    unsigned char text[1000];
    scanf(" %[^\r\n]", text);
    while (strcmp((char*)text, "FIM")) {
        int isP = isPalindrome(text, 0);
        printf("%s\n", isP ? "SIM" : "NAO");
        scanf(" %[^\n]", text);
    }

    return 0;
}