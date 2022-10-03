#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
char *getDateAndTime(); 
// returns char string with current date and time
int getInteger(); 
// read user input into a character string using fgets().
// "x" returns -1 indicating program exit.
// Otherwise, convert the string into an integer using atoi(const char *str);?
void decimalToBinary(int decValue, char binString[]);
// Store resulting binary value as char string within binString
void decimalToHex(int decValue, char hexString[]);
// Store resulting hexadecimal value as char string within hexString
void decimalToOct(int decValue, char octString[]);
// Store resulting octal value as char string within octString.
int saveUserFile(); //TODO add doc comment

int main() {
    int userNum = 0;
    int saveBool = 0;
    char fileName[32];
    FILE *userFile;
    char userName[32]; // i really have no clue what to initialize these to
    char binString[32]; //TODO check array size
    char hexString[32]; //TODO check array size
    char octString[32]; //TODO check array size
    printf("Enter your name: ");
    fgets(userName, sizeof(userName), stdin); //get user's name

    userNum = getInteger();
    while (userNum != -1) { //exit case
        // print out numbers and their converted versions:
        printf("\n");
        printf("Decimal: %d\n", userNum); //TODO check syntax
        decimalToHex(userNum, hexString);
        printf("Hexadecimal: %s\n", hexString);
        decimalToOct(userNum, octString);
        printf("Octal: %s\n", octString);
        decimalToBinary(userNum, binString);
        printf("Binary: %s\n", binString);
        printf("\n");

        // prompt user for saving a file:
        saveBool = saveUserFile();
        if (saveBool == 1) {
            printf("Enter file name: ");
            fgets(fileName, 32, stdin);
            fileName[strcspn(fileName, "\n")] = 0; //This removes the newline character at the end of the fgets of fileName
            //printf("File name: %s", fileName); //TODO DELETE
            userFile = fopen(fileName, "w");
            //userFile = fopen("codetest.txt", "w");
            //writing to file:
            fprintf(userFile, "%s", userName);
            fprintf(userFile, "Today's date: %s\n", getDateAndTime());
            fprintf(userFile, "Decimal: %d\n", userNum);
            fprintf(userFile, "Hexadecimal: %s\n", hexString);
            fprintf(userFile, "Octal: %s\n", octString);
            fprintf(userFile, "Binary: %s\n", binString);


            printf("File saved.\n");
            fclose(userFile);
            // save the file
        }

        // Set up loop to start again:
        userNum = getInteger();
    }
    printf("\n");
    printf("Goodbye!\n");
    return 0;
}

char *getDateAndTime() { //used week 5 notes
    time_t t;
    time(&t);
    return ctime(&t);
}

int getInteger() {
    char buffer[32];
    int convertedInt = 0;
    printf("Enter an Integer [1 - 1000000] or type x to exit: ");
    fgets(buffer, 32, stdin); //wonder if this works
    if (buffer[0] == 'x') {
        return -1;
    }
     convertedInt = atoi(buffer); //wonder if THIS works
     if (convertedInt >= 1 && convertedInt <= 1000000) {
        return convertedInt;
     }
     else {
        printf("Error: %d is out of range\n", convertedInt);
        return getInteger(); //recursion!
     }

}

void decimalToBinary(int decValue, char binString[]) {
    int quotient = decValue;
    int i = 0;
    char charValue;
    int intValue;
    while (quotient != 0) {
        //binString[i++] = quotient % 2;
        intValue = quotient % 2;
        charValue = intValue + '0'; // converts int to char, kind of
        binString[i++] = charValue;
        quotient = quotient / 2;
    }
}

void decimalToHex(int decValue, char hexString[]) {
    int quotient = decValue;
    int i = 0;
    char charValue;
    int intValue;
    while (quotient != 0) {
        intValue = quotient % 16;
        charValue = intValue + '0';
        hexString[i++] = charValue;
        quotient = quotient / 16;
    }
}

void decimalToOct(int decValue, char octString[]) {
}

int saveUserFile() {
    char saveChar[8];
    printf("Save to a file? (y/n): ");
    fgets(saveChar, 8, stdin);
    if (saveChar[0] == 'y') {
        return 1;
    }
    else if (saveChar[0] == 'n') {
        return 0;
    }
    else {
        printf("Error: Illegal value\n");
        return saveUserFile(); //recursion again
    }
}
