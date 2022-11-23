#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*
NOTES:
if i add each line in the text file as a character array, the index values are:
mac address: 0,1,3,4,6,7,9,10,12,13,15,16
mac alias: 18-33
*/

typedef struct {
    int macArray[6]; //array to store mac address
    char macAlias[16]; //character array to store the mac alias 
} address_t;
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

    int recordCount = 0;
    char breakString[] = "00:00:00:00:00:00 NONE\n";
    while (fgets(charBuffer, maxLineLength, filePointer)) { //count number of addresses
        if (strcmp(charBuffer, breakString) == 0) {
            break; //break out of while loop if we reach the NONE alias
        }
        recordCount++;
    }
    printf("Total mac entries: %d", recordCount);

}