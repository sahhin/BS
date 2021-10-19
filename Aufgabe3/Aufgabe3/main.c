#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void string_replace(char * scr, char * substring, char * replace){
    char *substring_src = strstr(scr,substring); //returns pointer to that substring that we would like to replace
    if(substring_src == NULL){
        return;
    }
    memmove(substring_src + strlen(replace), substring_src + strlen(substring),(strlen(substring_src) - strlen(substring)+1));

    memcpy(substring_src,replace, strlen(replace)); //copies n characters from memory area src to memory area dest
}

int main() {

    FILE *fp1;
    char *fp1name = "NamenList.txt";


    fp1 = fopen(fp1name, "w");
    if (fp1 == 0){
        printf("Fehler!");
        return 1;
    }
    fprintf(fp1, "Sara, Anton, Erwin, Erna");
    fclose(fp1);


    char name1[10], name2[10], name3[10], name4[10];
    fp1 = fopen(fp1name, "r");
    fscanf(fp1, "%10[^,], %10[^,], %10[^,], %s", name1, name2, name3, name4); //read at most 10 characters or until a comma is encountered.
    fclose(fp1);

    //char* namen[] = {name1, name2, name3, name4}; //array of five pointers


    //append files
    FILE *brf1;
    FILE *brf2;
    FILE *brf3;
    FILE *brf4;

    char *brf1name = "SaraBrf.txt";
    char *brf2name = "AntonBrf.txt";
    char *brf3name = "ErwinBrf.txt";
    char *brf4name = "ErnaBrf.txt";



    brf1 = fopen(brf1name, "r+");
    char text[200];
    fscanf(brf1, "%[^\n]", text);
    string_replace(text, "###", name1);
    fclose(brf1);

    brf1 = fopen(brf1name, "w");
    fprintf(brf1, text);
    fclose(brf1);


    brf2 = fopen(brf2name, "r");
    text[200];
    fscanf(brf2, "%[^\n]", text);
    string_replace(text, "###", name2);
    fclose(brf2);

    brf2 = fopen(brf2name, "w");
    fprintf(brf2, text);
    fclose(brf2);


    brf3 = fopen(brf3name, "r");
    text[200];
    fscanf(brf3, "%[^\n]", text);
    string_replace(text, "###", name3);
    fclose(brf3);

    brf3 = fopen(brf3name, "w");
    fprintf(brf3, text);
    fclose(brf3);


    brf4 = fopen(brf4name, "r");
    text[200];
    fscanf(brf4, "%[^\n]", text);
    string_replace(text, "###", name4);
    fclose(brf4);

    brf4 = fopen(brf4name, "w");
    fprintf(brf4, text);
    fclose(brf4);


    return 0;
}





