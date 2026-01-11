#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>

int getWord();
void hangman(int numb);

char global_realWord[99];
char global_hide[99];
char input;
char list_input[99] =" ";

int main(){
    int tries = 0;
    int digits;
    char temp[99] = "\0";
    
    getWord();

    // printf("%s", global_realWord);

    digits = strlen(global_realWord);
    
    for(int i = 0; i < digits; i++){
        global_hide[i] = '_';
    }

    strcpy(temp, global_hide);
    
    while(tries < 7 && strcmp(global_hide, global_realWord) != 0){

        hangman(tries);
        
        for(int i = 0; i < digits; i++){
            printf("%c ", global_hide[i]);
        }

        if(tries > 0){
            printf("\nInputed: ");
            for(int i = 0; i < ((sizeof(list_input)/sizeof(list_input[0])) - 1); i++){
                printf("%c ", list_input[i + 1]);
            }
        }

        printf("\nNumber of tries: %d", (7 - tries));
        
        while(true){
            printf("\nEnter letter: ");
            scanf(" %c", &input);
            if(strchr(list_input, input) == NULL){
                break;
            }
            else{
                printf("You've have already guessed this answer. ");
                continue;
            }
        }

        list_input[strlen(list_input)] = input;

        for(int i = 0; i < digits; i++){
            if(input == global_realWord[i]){
                global_hide[i] = input;
            }
        }
        
        if(strcmp(temp, global_hide) == 0){
        tries++;
        }

        strcpy(temp, global_hide);

    }

    if(tries ==7){
        printf("sorry the man died :(\n");
    }
    else{
        printf("Congratuation! You got the word right!\n");
    }

    for(int i = 0; i < digits; i++){
        printf("%c ", global_realWord[i]);
    }
}

int getWord(){
    
    char word[99];
    char **list = NULL;
    int count = 0;

    FILE *pFile = fopen("word_list.txt", "r");

    if(pFile == 0){
        printf("Could not open file\n");
        return 1;
    }

    while(fscanf(pFile, "%99s", word) == 1){
        list = realloc(list, (count + 1) * sizeof(char *));
        list[count] = malloc(strlen(word) + 1);
        strcpy(list[count], word);
        count++;
    }

    fclose(pFile);

    srand(time(NULL));
    strcpy(global_realWord, list[(rand() % (count - 1))]);

    free(list);
}

void hangman(int numb){

    const char *hangman[] = {
        " +---+\n |   |\n |    \n |    \n |    \n |    \n=========\n",

        " +---+\n |   |\n |   O\n |    \n |    \n |    \n=========\n",

        " +---+\n |   |\n |   O\n |   |\n |    \n |    \n=========\n",

        " +---+\n |   |\n |   O\n |   |\\\n |    \n |    \n=========\n",

        " +---+\n |   |\n |   O\n |  /|\\\n |    \n |    \n=========\n",

        " +---+\n |   |\n |   O\n |  /|\\\n |    \\\n |    \n=========\n",

        " +---+\n |   |\n |   O\n |  /|\\\n |  / \\\n |    \n=========\n"
    };

    printf("%s", hangman[numb]);

}



