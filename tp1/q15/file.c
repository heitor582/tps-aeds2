#include <stdio.h>
void write(int n, char *fileName){
        FILE *file;
        double value = 0;
        file = fopen(fileName, "w");
        for(int i = 0; i < n; i++){
            scanf("%lf", &value);
            fprintf(file, "%g\n",value);
        }
        fclose(file);
       
    }
void read(FILE *file){
        double value;
        fscanf(file, "%lf", &value);
        if(!feof(file)){
            read(file);
            printf("%g\n",value);//%g print the value without the plus zeros
        }
        
    }
int main(){
    int num;
    char fileOut[10] = "saida.txt";
    scanf("%d", &num);
    write(num, fileOut);
    FILE *file;
    file = fopen(fileOut, "r");
    read(file);
    fclose(file);
    return 0;
}