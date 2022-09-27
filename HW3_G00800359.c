#include <stdio.h>
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
/*
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

    }
    return 0;


*/
}