#include<stdio.h>
#include<string.h>

int sumDigits(int number) {
    if(number <= 9){
        return number;
    }
    int sum = number % 10 + sumDigits(number/10);
    
    return sum;
}

int main() {
    unsigned char text[1000];
    scanf(" %[^\r\n]", text);
    while (strcmp((char*)text, "FIM")) {
        int sum = sumDigits(atoi(text));
        printf("%d\n", sum);
        scanf(" %[^\r\n]", text);
    }

    return 0;
}