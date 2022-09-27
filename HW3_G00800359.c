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

int main() {
    int userNum = 0;
    char userName[36]; // i really have no clue what to initialize these to
    printf("Enter your name: ");
    fgets(userName, sizeof(userName, stdin)); //get user's name

    userNum = getInteger();
    while (userNum != -1) { //exit case
        
    }

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
        printf("Error: %d is out of range", convertedInt);
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

/*

int main() {
    userNum = 0;
    userName = printf("Enter your name: ");

    userNum = printf("Enter an Integer [1 - 1000000] or type x to exit: ");
    while (userNum != "x") {
        while (!(1 < userNum < 1000000)) {
            if (userNum < 1 || userNum > 1000000) {
                printf("Error: " + userNum + " is out of range");
            }
            else if (userNum == "x") {
                exit()
            }
        }

        printf(\n);
        printf("Decimal: " + userNum);
        printf("Hexadecimal: " + decimalToHex(userNum));
        printf("Octal: " + decimalToOct(userNum));
        printf("Binary: " + decimalToBinary(userNum));

        //prompt for file - THIS SHOULD BE ITS OWN METHOD
        saveFile();

        //Set loop up to be restarted:
        userNum = printf("Enter an Integer [1 - 1000000] or type x to exit: ");
    }
    return 0;
}

void saveFile() {
    userFile = printf("Save to a file? (y/n): ");
    if (userFile == "n") {
        continue;
    }
    else if (userFile == "y") {
        fileName = printf("Enter file name: ");
        createFile(fileName) //this is a fake method
        printf("File saved.");
    }
    else {
        printf("Error: illegal value");
        saveFile();
    }
}

*/