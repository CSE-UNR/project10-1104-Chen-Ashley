//Ashley Chen
//Project 10
//word game

#include <stdio.h>
#include <stdbool.h>
#define FILENAME "mystery.txt"

void getsecret(char mystery[5]);
void getguess(int guess, char guesses[6][5]);
void checkguess(int guess, char guesses[6][5], char mystery[5], char hint[6][5]);
bool found(int guess, char guesses[6][5], char mystery[5]);
void correct(int guess, char mystery[5]);
void display(char guesses[6][5], int guess, char hint[6][5]);
bool checkinput(char fetch[30]);
bool checklength(char fetch[30]);

int main(){
    char mystery[5], guesses[6][5], hint[6][5];
    int guess = 1;

    getsecret(mystery);
    
    getguess(guess, guesses);
    checkguess(guess, guesses, mystery, hint);
   
    bool solve = found(guess, guesses, mystery);


    while(guess < 6 && !solve){
        display(guesses, guess, hint);
        guess += 1;
        getguess(guess, guesses);
        checkguess(guess, guesses, mystery, hint);
        solve = found(guess, guesses, mystery);
    }

    if(solve){
        correct(guess, mystery);
    }
    else{
        printf("You lost, better luck next time!\n");
    }

    return 0;
}





void getsecret(char mystery[5]){
    char grab[30];
    FILE *read;
    read = fopen(FILENAME, "r");
   
    fscanf(read, "%s", grab);
    fclose(read);


    for(int i = 0; grab[i] != '\0'; i++){
        mystery[i] = grab[i];
    }
}

void getguess(int guess, char guesses[6][5]){
    char fetch[30];
    if(guess < 6){
        printf("GUESS %d! Enter your guess: ", guess);
    }
    else if(guess == 6){
        printf("FINAL GUESS :");
    }
   
    scanf("%s", fetch);
   
    do{
        bool validlength, validinput;
        validlength = checklength(fetch);
        validinput = checkinput(fetch);


        if(!validlength || !validinput){
            fetch[0] = '\0';
            if(!validinput){
                printf("Your guess must contain only letters.");
            }
            if(!validlength){
                printf("Your guess must be 5 letters long.");
            }
            printf("\n");
            printf("Please try again: ");
            scanf("%s", fetch);
        }
    }while(!checkinput(fetch) || !checklength(fetch));


    int index;
    index = guess - 1;
    for(int i = 0; i < 5; i++){
        if(fetch[i] >= 65 && fetch[i] <= 90 ){
            fetch[i] += 32;
        }
         guesses[index][i] = fetch[i];
    }
}

void checkguess(int guess, char guesses[6][5], char mystery[5], char hint[6][5]){
    int index = guess - 1;
    for(int i = 0; i < 5; i++){
        hint[index][i] = ' ';
        if(guesses[index][i] == mystery[i]){
            guesses[index][i] -= 32;
        }
        else{
            for(int j = 0; j < 5; j++){
            if(guesses[index][i] == mystery[j]){
                hint[index][i] = '^';
                }
            }
        }
    }
}

bool found(int guess, char guesses[6][5], char mystery[5]){
    int index = guess - 1;
    char theguess[5];
    for(int i = 0; i < 5; i++){
        if(guesses[index][i] >= 65 && guesses[index][i] <= 90){
            theguess[i] = guesses[index][i];
            theguess[i] += 32;
        }
        else{
            theguess[i] = guesses[index][i];
        }
    }
    for(int i = 0; i < 5; i++){
        if(theguess[i] != mystery[i]){
            return false;
        }
    }
    return true;
}

void correct(int guess, char mystery[5]){
    for(int i = 0; i < 32; i++){
        printf("=");
    }
    printf("\n");
    for(int i = 0; i < 16; i++){
        printf(" ");
    }
    for(int i = 0; i < 5; i++){
        mystery[i] -= 32;
        printf("%c", mystery[i]);
    }
    printf("\n");
    for(int i = 0; i < 8; i++){
        printf(" ");
    }
    printf("You won in %d guesses!", guess);
    printf("\n");
    if(guess == 1){
        for(int i = 0; i < 16; i++){
            printf(" ");
        }
        printf("GOATED");
    }
    else if(guess == 2 || guess == 3){
        for(int i = 0; i < 16; i++){
            printf(" ");
        }
        printf("Amazing!");
    }
    else if(guess == 4 || guess == 5){
        for(int i = 0; i < 16; i++){
            printf(" ");
        }
        printf("Nice!");
    }
    printf("\n");
}


void display(char guesses[6][5], int guess, char hint[6][5]){
 
    for(int i = 0; i < 32; i++){
        printf("=");
    }
    printf("\n");
    for(int i = 0; i < guess; i++){
        for(int j = 0; j < 5; j++){
            printf("%c", guesses[i][j]);
        }
        printf("\n");
        for(int j = 0; j < 5; j++){
		printf("%c", hint[i][j]);
        }
        printf("\n");
    }
}


bool checklength(char fetch[30]){
    int length = 0;
    for(int i = 0; fetch[i] != '\0'; i++){
        length++;
    }
    if(length == 5){
        return true;
    }
    else{
        return false;
    }
}


bool checkinput(char fetch[30]){
    for(int i = 0; fetch[i]!= '\0'; i++){
        if(((fetch[i] < 'A') || (fetch[i] > 'Z' && fetch[i] < 'a') || (fetch[i] > 'z'))){
            return false;
        }
       }
       return true;
}

	
