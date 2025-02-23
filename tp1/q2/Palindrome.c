#include<stdio.h>
#include<string.h>
#include<locale.h>
#include<ctype.h>

int isPalindrome(int len,  unsigned char* s){
    for (int i = 0; i < len / 2; i++) {
        if (s[i] == 195) { // special char with 2 bytes, so get the first position that is 195
            i++;
            if (s[i] != s[len - i]) return 0; // compare the second bytes
        } else if (s[i] == 239) { // special char with 3 bytes
            i += 2;
            if (s[len - i - 1] != 239 ) return 0; // compare the third bytes
        } else if (s[i] != s[len - i - 1]) {
            return 0;
        }
    }
    return 1;
}

int main() {
    setlocale(LC_ALL, "pt_BR.utf8");
    unsigned char text[1000];
    scanf(" %[^\r\n]", text);
    while (strcmp((char*)text, "FIM")) {
        int isP = isPalindrome(strlen((char*)text), text);
        printf("%s\n", isP ? "SIM" : "NAO");
        scanf(" %[^\n]", text);
    }

    return 0;
}