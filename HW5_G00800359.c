#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

/*
NOTES:
if i add each line in the text file as a character array, the index values are:
mac address: 0,1,3,4,6,7,9,10,12,13,15,16
mac alias: 18-33
*/

typedef struct {
    //int macArray[6]; // array to store mac address
    char mac1[2];
    char mac2[2];
    char mac3[2];
    char mac4[2];
    char mac5[2];
    char mac6[2];
    char macAlias[50]; // character array to store the mac alias 
    int validAddress; // boolean int
} address_t;

address_t *addressArrayPointer_g; // GLOBAL VARIABLE
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
char *getDateAndTime(); // reusing old code for this one
/*
Builds address_t structure out of a line of characters
*/
address_t buildAddressStruct(char addressLine[]);

int main() {
    readDataFile(); // still working on this, but it needs to be in main to test

    printf("Data file successfully read. Attempting to print addresses...\n"); // DELETE

    for (int i = 0; i < 21; i++) { // TEST, DELETE
        printf("%s\n", addressArrayPointer_g[i].macAlias);
    }
    //TODO

    free(addressArrayPointer_g);
}

char *getDateAndTime() {
    time_t t;
    time(&t);
    return ctime(&t);
}

void readDataFile() {
    char fileName[] = "CS222_Inet.txt";
    FILE *filePointer;
    filePointer = fopen(fileName, "r"); // point filePointer at file

    char charBuffer[50];
    int maxLineLength = 60;

    if (filePointer == NULL) { // error for if the file cannot be opened
        printf("Unable to open 'CS222_Inet.txt' file.\n");
        exit(1);
    }

    int recordCount = 0;
    char breakString[] = "00:00:00:00:00:00 NONE\n";
    while (fgets(charBuffer, maxLineLength, filePointer)) { // count number of addresses
        if (strcmp(charBuffer, breakString) == 0) {
            break; // break out of while loop if we reach the NONE alias
        }
        recordCount++;
    }
    printf("Total mac entries: %d\n", recordCount);

    addressArrayPointer_g = (address_t*) malloc(recordCount * sizeof(addressArrayPointer_g)); // dynamically allocate memory for address_t array (TEST!!)
    printf("address pointer successfully assigned.\n");
    //address_t addressArray[recordCount];
    //addressArrayPointer_g = &addressArray[0];
    printf("Address array created successfully.\n");

    rewind(filePointer); // rewind the file
    int i = 0; // index value
    while (fgets(charBuffer, maxLineLength, filePointer)) {
        if (strcmp(charBuffer, breakString) == 0) {
            break; // break out of while loop if we reach the NONE alias
        }
        addressArrayPointer_g[i] = buildAddressStruct(charBuffer); // add the build address_t structs to the malloc'd array
        //[i] = buildAddressStruct(charBuffer); // add the build address_t structs to the malloc'd array
        i++;
    }
    fclose(filePointer); // close the file
}

address_t buildAddressStruct(char addressLine[]) { // converts char array of a line into an address_t
    /* 
    -32 for ASCII lowercase -> uppercase, Z == 90
    mac address: 0,1,3,4,6,7,9,10,12,13,15,16
    mac alias: 18-33
    */
    address_t returnAddress;

    printf("BuildAddressStruct() current line: %s\n", addressLine); //TODO DELETE
    // I can't think of a better way to do this other than hard coding it.
    returnAddress.mac1[0] = toupper(addressLine[0]);
    returnAddress.mac1[1] = toupper(addressLine[1]);

    returnAddress.mac2[0] = toupper(addressLine[3]);
    returnAddress.mac2[1] = toupper(addressLine[4]);

    returnAddress.mac3[0] = toupper(addressLine[6]);
    returnAddress.mac3[1] = toupper(addressLine[7]);

    returnAddress.mac4[0] = toupper(addressLine[9]);
    returnAddress.mac4[1] = toupper(addressLine[10]);

    returnAddress.mac5[0] = toupper(addressLine[12]);
    returnAddress.mac5[1] = toupper(addressLine[13]);

    returnAddress.mac6[0] = toupper(addressLine[15]);
    returnAddress.mac6[1] = toupper(addressLine[16]);
    
    int j = 0;
    for (int i = 18; i < 50; i++) {
        returnAddress.macAlias[j] = toupper(addressLine[i]);
        j++;
    }
    /*
    int j = 0;
    int i = 18;
    while (addressLine[i] != "\n") {
        returnAddress.macAlias[j] = toupper(addressLine[i]);
        j++;
        i++;
    } */

    returnAddress.validAddress = 1; // SET FOR TESTING PURPOSES, DELETE

    return returnAddress;
}