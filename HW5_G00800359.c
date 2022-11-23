#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct address_t {
    int macArray[6]; //array to store mac address
    char macAlias[16]; //character array to store the mac alias 
};
/*
Open and read data file (CS222_Inet.txt)
While reading, generate the CS222_Error_Report.txt file
Dynamically allocate array of address_t structs
rewind() CS222_Inet.txt file
Populate dynamically allocated array
*/
void readDataFile();
/*
Confirm the MAC address components are in range 00 to FF
*/
int checkAddress(address_t macAddress);
/*
Confirm that alias has strlen() <= 16
*/
int checkAlias(address_t macAddress);
int generateManufacturerRpt(); //TODO check return val on this
char *getDateAndTime(); //reusing old code for this one

int main() {
    readDataFile();
    //TODO
}

char *getDateAndTime() {
    time_t t;
    time(&t);
    return ctime(&t);
}

void readDataFile() {
    char fileName[] = "CS222_Inet.txt";
    FILE *filePointer;
    filePointer = fopen(fileName, "r"); //point filePointer at file

    char charBuffer[50];
    int maxLineLength = 60;

    if (filePointer == NULL) { //error for if the file cannot be opened
        printf("Unable to open 'CS222_Inet.txt' file.\n");
        exit(1);
    }
    
    while (fgets(charBuffer, maxLineLength, filePointer)) {
        printf(charBuffer);
    }

}