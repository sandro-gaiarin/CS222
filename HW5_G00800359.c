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
    char mac[6][2]; // array to store mac address
    // char mac1[2];
    // char mac2[2];
    // char mac3[2];
    // char mac4[2];
    // char mac5[2];
    // char mac6[2];
    char macAlias[50]; // character array to store the mac alias 
    int validAddress; // boolean int
    char macManufac[8]; // first six MAC address digits in a string format with ':'
} address_t;

address_t *addressArrayPointer_g; // GLOBAL VARIABLE
int numAddresses_g; // global variable
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
/*
Generate text file listing the different manufacturers and the devices associated with them.
*/
void generateManufacturerRpt(); //TODO check return val on this
char *getDateAndTime(); // reusing old code for this one
/*
Builds address_t structure out of a line of characters
*/
address_t buildAddressStruct(char addressLine[]);


int main() {
    readDataFile(); // still working on this, but it needs to be in main to test
    int i = 0;
    printf("Data file successfully read. Attempting to print addresses and their validity...\n"); // DELETE
    for (i = 0; i < 21; i++) { // TEST, DELETE
        int length = strlen(addressArrayPointer_g[i].macAlias);
        printf("%s valid? %d; alias length: %d\n", addressArrayPointer_g[i].macAlias, addressArrayPointer_g[i].validAddress, length);
    }

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
    numAddresses_g = recordCount;

    addressArrayPointer_g = (address_t*) malloc(recordCount * sizeof(addressArrayPointer_g)); // dynamically allocate memory for address_t array (TEST!!)
    printf("address pointer successfully assigned.\n");
    //address_t addressArray[recordCount];
    //addressArrayPointer_g = &addressArray[0];
    printf("Address array created successfully.\n");

    rewind(filePointer); // rewind the file

    FILE *errorFile = fopen("222_Error_File.txt", "w+"); // create error file
    if (errorFile == NULL) { //TEST
        perror("The following error occurred.");
    }


    char userName[32] = "TEST USERNAME\n";
    // printf("Please enter user name: ");
    // fgets(userName, 32, stdin);
    userName[strcspn(userName, "\n")] = 0; //remove newline from end of userName

    fprintf(errorFile, "%s ", userName);
    fprintf(errorFile, "%s\n", getDateAndTime());
    fprintf(errorFile, "CS222 Error Report\n");

    int i = 0; // index value
    while (fgets(charBuffer, maxLineLength, filePointer)) {
        if (strcmp(charBuffer, breakString) == 0) {
            break; // break out of while loop if we reach the NONE alias
        }
        addressArrayPointer_g[i] = buildAddressStruct(charBuffer); // add the build address_t structs to the malloc'd array
        if (checkAddress(addressArrayPointer_g[i]) == 0 || checkAlias(addressArrayPointer_g[i]) == 0) { // check validity
            addressArrayPointer_g[i].validAddress = 0;
            //fprintf(errorFile, "%s", charBuffer); // add invalid mac address to the error file
        }
        //[i] = buildAddressStruct(charBuffer); // add the build address_t structs to the malloc'd array
        i++;
    }

    // // Check validity of address and alias:
    // for (i = 0; i < numAddresses_g; i++) {
    //     addressArrayPointer_g[i].validAddress = checkAddress(addressArrayPointer_g[i]); // check address validity
    //     if (addressArrayPointer_g[i].validAddress == 1) {
    //         addressArrayPointer_g[i].validAddress = checkAlias(addressArrayPointer_g[i]); // check alias validity
    //     }
    // }


    fclose(errorFile);
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
    returnAddress.mac[0][0] = toupper(addressLine[0]);
    returnAddress.mac[0][1] = toupper(addressLine[1]);

    returnAddress.mac[1][0] = toupper(addressLine[3]);
    returnAddress.mac[1][1] = toupper(addressLine[4]);

    returnAddress.mac[2][0] = toupper(addressLine[6]);
    returnAddress.mac[2][1] = toupper(addressLine[7]);

    returnAddress.mac[3][0] = toupper(addressLine[9]);
    returnAddress.mac[3][1] = toupper(addressLine[10]);

    returnAddress.mac[4][0] = toupper(addressLine[12]);
    returnAddress.mac[4][1] = toupper(addressLine[13]);

    returnAddress.mac[5][0] = toupper(addressLine[15]);
    returnAddress.mac[5][1] = toupper(addressLine[16]);

    // I'm embaressed that I'm hard coding all of this, but my brain is fried. I swear I'm a decent programmer.
    returnAddress.macManufac[0] = returnAddress.mac[0][0];
    returnAddress.macManufac[1] = returnAddress.mac[0][1];
    returnAddress.macManufac[2] = ':';
    returnAddress.macManufac[3] = returnAddress.mac[1][0];
    returnAddress.macManufac[4] = returnAddress.mac[1][1];
    returnAddress.macManufac[5] = ':';
    returnAddress.macManufac[6] = returnAddress.mac[2][0];
    returnAddress.macManufac[7] = returnAddress.mac[2][1];
    
    int j = 0;
    for (int i = 18; i < 50; i++) { // make all characters uppercase
        returnAddress.macAlias[j] = toupper(addressLine[i]);
        j++;
    }

    returnAddress.validAddress = 1;

    return returnAddress;
}


int checkAddress(address_t macAddress) {
    int i;
    for (i = 0; i < 6; i++) { // there will always be six pairs for the mac address
        int j = 0;
        for (j = 0; j < 2; j++) {
            if (macAddress.mac[i][j] > 70) { // character F is 70 in ASCII
                return 0;
            }
        }
    }
    return 1;
}

int checkAlias(address_t macAddress) {
    macAddress.macAlias[strcspn(macAddress.macAlias, "\n")] = 0;
    int length = strlen(macAddress.macAlias);
    if (length > 16) {
        return 0;
    }
    return 1;
}

void generateManufacturerRpt() {
    int addressTotal = 0; // total number of different MAC addresses
    int manufacturerTotal = 0; // total number of manufacturers represented

    for (int i = 0; i < numAddresses_g; i++) {
        if (addressArrayPointer_g[i].validAddress == 1) {
            addressTotal++;
            // add each manufacturer to the list
                // add the aliases below the manufacturer
        }
    }


}