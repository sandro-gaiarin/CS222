#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
void saveUserFile(); //TODO add doc comment

int main() {
    int userNum = 0;
    char userName[36]; // i really have no clue what to initialize these to
    char binString[36]; //TODO check array size
    char hexString[36]; //TODO check array size
    char octString[36]; //TODO check array size
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
        saveUserFile();

        // Set up loop to start again:
        userNum = getInteger();
    }
    printf("\n");
    printf("Goodbye!\n");
    return 0;
}

char *getDateAndTime() {
    return 0;
}

int getInteger() {
    char buffer[256]; //set buffer to 7, since there can only be a max of 7 ints?
    int convertedInt = 0;
    printf("Enter an Integer [1 - 1000000] or type x to exit: ");
    fgets(buffer, 256, stdin); //wonder if this works
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
    int quotient = 0;
}

void decimalToHex(int decValue, char hexString[]) {
}

void decimalToOct(int decValue, char octString[]) {
}

void saveUserFile() {
}
