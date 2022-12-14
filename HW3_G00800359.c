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
int saveUserFile(); 
// Asks user if they'd like to save a file

int main() {
    int userNum = 0;
    int saveBool = 0;
    char fileName[32];
    FILE *userFile;
    char userName[32]; // probably should have made a macro for the array sizes, ah well
    char binString[32];
    char hexString[32];
    char octString[32];
    printf("Enter your name: ");
    fgets(userName, sizeof(userName), stdin); // get user's name

    userNum = getInteger(); // get number from the user
    while (userNum != -1) { //exit case, main program loop
        // print out numbers and their converted versions:
        printf("\n");
        printf("Decimal: %d\n", userNum);
        decimalToHex(userNum, hexString);
        printf("Hexadecimal: %s\n", hexString);
        decimalToOct(userNum, octString);
        printf("Octal: %s\n", octString);
        decimalToBinary(userNum, binString);
        printf("Binary: %s\n", binString);
        printf("\n");

        // prompt user for saving a file:
        saveBool = saveUserFile(); // using a helper function allows us to easily and cleanly loop if an input is mistyped
        if (saveBool == 1) {
            printf("Enter file name: ");
            fgets(fileName, 32, stdin);
            fileName[strcspn(fileName, "\n")] = 0; // This removes the newline character at the end of the fgets of fileName
            userFile = fopen(fileName, "w"); // creates a new file for the user
            // writing to file:
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
    printf("Goodbye!\n"); // end of main()
    return 0;
}

char *getDateAndTime() { // used week 5 notes for this
    time_t t;
    time(&t);
    return ctime(&t);
}

int getInteger() {
    char buffer[32];
    int convertedInt = 0;
    printf("Enter an Integer [1 - 1000000] or type x to exit: ");
    fgets(buffer, 32, stdin);
    if (buffer[0] == 'x') {
        return -1;
    }
     convertedInt = atoi(buffer); // converts string to int
     if (convertedInt >= 1 && convertedInt <= 1000000) {
        return convertedInt;
     }
     else {
        printf("Error: %d is out of range\n", convertedInt);
        return getInteger(); // yay recursion!
     }

}

void decimalToBinary(int decValue, char binString[]) { // loosely based off lecture slides
    binString[0] = '\0'; // null character, cleans out char array
    char tempString[32]; //temporary character array
    int quotient = decValue;
    int i = 0;
    char charValue;
    int intValue;
    while (quotient != 0) {
        intValue = quotient % 2;
        charValue = intValue + '0'; // moves up to '0' char
        tempString[i++] = charValue;
        quotient = quotient / 2;
    }
    tempString[i] = '\0'; // end temp char array
    int j = 0;
    for (int k = i - 1; k >= 0; k--) {
        binString[j++] = tempString[k];
    }
    binString[j] = '\0'; // end char array
}

void decimalToHex(int decValue, char hexString[]) {
    hexString[0] = '\0'; // null character, cleans out char array
    char tempString[32]; //temporary character array
    int quotient = decValue;
    int i = 0;
    char charValue;
    int intValue;
    while (quotient != 0) {
        intValue = quotient % 16;
        if (intValue < 10) {
            charValue = intValue + '0'; // 1-9 characters
        }
        else { // 'A' char starts at dec 65
            charValue = intValue + 55; // 10-16 characters (starts at '7', but a minimum of 11-16 are added)
        }
        tempString[i++] = charValue; // add character to temp string
        quotient = quotient / 16; // divide by 16 to prep for next loop
    }
    tempString[i] = '\0'; // end the char array
    int j = 0;
    for (int k = i - 1; k >= 0; k--) { // need to reverse the order of the array
        hexString[j++] = tempString[k];
    }
    hexString[j] = '\0'; // end char array
}

void decimalToOct(int decValue, char octString[]) {
    octString[0] = '\0'; // null character, cleans out char array
    char tempString[32]; //temporary character array
    int quotient = decValue;
    int i = 0;
    char charValue;
    int intValue;
    while (quotient != 0) {
        intValue = quotient % 8;
        charValue = intValue + '0';
        tempString[i++] = charValue; // add character to temp string
        quotient = quotient / 8; // divide by 16 to prep for next loop
    }
    tempString[i] = '\0'; // end the char array
    int j = 0;
    for (int k = i - 1; k >= 0; k--) { // need to reverse the order of the array
        octString[j++] = tempString[k];
    }
    octString[j] = '\0'; // end char array
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
