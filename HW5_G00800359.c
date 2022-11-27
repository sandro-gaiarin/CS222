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

/*
Code is working!!
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
    char macManufac[9]; // first six MAC address digits in a string format with ':'
} address_t;

typedef struct {
    char manufacCode[9]; // first six MAC address digits in a string format with ':'
    char manufacName[16]; // Name of the manufacturer
} manufacturer_t;

address_t *addressArrayPointer_g; // GLOBAL VARIABLE, array of address_t's
char username_g[32]; // GLOBAL VARIABLE, user name
int totalAddresses_g; // GLOBAL VARIABLE, total number of addresses in the global array
/* I know I'm going to take a point hit on the third global variable here.
I just couldn't get specific parts of my code to work without keeping track
of the total number of addresses in this way. */

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

// Extra credit UDFs
/*
Open and read CS222_Mfg.txt to get the names of the Manufacturers
*/
manufacturer_t* readMfgFile();
/*
Open and write the 222_MfgReportByName.txt file
*/
void generateMfgRptByName(manufacturer_t manufacturerArray[]);


int main() {
    readDataFile(); // still working on this, but it needs to be in main to test
    int i = 0;
    printf("Data file successfully read. Attempting to print addresses and their validity...\n"); // DELETE
    for (i = 0; i < 21; i++) { // TEST, DELETE
        int length = strlen(addressArrayPointer_g[i].macAlias);
        printf("%s valid? %d; alias length: %d\n", addressArrayPointer_g[i].macAlias, addressArrayPointer_g[i].validAddress, length);
    }

    generateManufacturerRpt();
    manufacturer_t *manufacturerArray;
    manufacturerArray = readMfgFile();

    printf("ManufacturerArray assigned, I think\n");
    generateMfgRptByName(manufacturerArray);

    free(addressArrayPointer_g);
    free(manufacturerArray);
    
}


char *getDateAndTime() {
    time_t t;
    time(&t);
    return ctime(&t);
}


void readDataFile() {
    FILE *filePointer;
    FILE *errorFile; // create error file
    filePointer = fopen("CS222_Inet.txt", "r"); // point filePointer at file

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
    totalAddresses_g = recordCount;
    printf("Total mac entries: %d\n", recordCount);

    addressArrayPointer_g = (address_t*) malloc(recordCount * sizeof(*addressArrayPointer_g)); // dynamically allocate memory for address_t array (TEST!!)

    rewind(filePointer); // rewind the file
    // // fclose(filePointer);

    errorFile = fopen("222_Error_Report.txt", "w");
    printf("Error file open attempt created\n");


    printf("Please enter user name: ");
    fgets(username_g, 32, stdin);
    username_g[strcspn(username_g, "\n")] = 0; //remove newline from end of username_g

    fprintf(errorFile, "%s ", username_g);
    fprintf(errorFile, "%s", getDateAndTime());
    fprintf(errorFile, "CS222 Error Report\n\n");
    fclose(errorFile);
    // printf("Error file closed."); // TEST

    // // filePointer = fopen("CS222_Inet.txt", "r");
    // printf("Read file opened"); //TEST
    int i = 0; // index value
    // fpos_t position;
    while (fgets(charBuffer, maxLineLength, filePointer)) {
        printf("Within while loop\n");
        if (strcmp(charBuffer, breakString) == 0) {
            break; // break out of while loop if we reach the NONE alias
        }
        addressArrayPointer_g[i] = buildAddressStruct(charBuffer); // add the build address_t structs to the malloc'd array
        printf("Address built\n");
        if (checkAddress(addressArrayPointer_g[i]) == 0 || checkAlias(addressArrayPointer_g[i]) == 0) { // check validity
            addressArrayPointer_g[i].validAddress = 0;
            // fgetpos(filePointer, &position);
            // fclose(filePointer);
            // printf("Read file closed"); //TEST
            printf("Within if statement\n");
            errorFile = fopen("222_Error_Report.txt", "a");
            printf("Opened error file successfully\n");
            // printf("Write file opened"); //TEST
            printf("Attempting to add charBuffer: %s\n", charBuffer);
            fprintf(errorFile, "%s", charBuffer);
            printf("character buffer successfully added. Attempting to close errorfile.\n");
            fclose(errorFile);
            printf("Errorfile successfully closed.\n\n");
            // printf("Write file closed"); //TEST
            // filePointer = fopen("CS222_Inet.txt", "r");
            // printf("Read file opened"); //TEST
            // fsetpos(filePointer, &position);
        }
        i++;
    }

    fclose(filePointer); // close the file
    printf("Read file closed"); //TEST
}

address_t buildAddressStruct(char addressLine[]) { // converts char array of a line into an address_t
    /* 
    -32 for ASCII lowercase -> uppercase, Z == 90
    mac address: 0,1,3,4,6,7,9,10,12,13,15,16
    mac alias: 18-33
    */
    address_t returnAddress;

    //printf("BuildAddressStruct() current line: %s\n", addressLine); //TODO DELETE
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
    returnAddress.macManufac[8] = '\0';
    
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
    int addressTotal = 0; // total number of different VALID MAC addresses
    int manufacturerTotal = 0; // total number of manufacturers represented
    int arrayLen = totalAddresses_g;
    char manufactArray[arrayLen][9];
    FILE *reportFile;


    for (int i = 0; i < arrayLen; i++) { // clean out character arrays
        manufactArray[i][0] = '\0';
    }

    for (int i = 0; i < arrayLen; i++) {
        printf("Within first for-loop.\n");
        if (addressArrayPointer_g[i].validAddress == 1) {
            printf("Within first if-statement.\n");
            addressTotal++;

            int manuCounted = 0;
            for (int j = 0; j < arrayLen; j++) {
                printf("Within second for-loop.\n");
                printf("Current macManufac: %s. Current manufactArray: %s\n", addressArrayPointer_g[i].macManufac, manufactArray[j]);
                if (strcmp(addressArrayPointer_g[i].macManufac, manufactArray[j]) == 0) {
                    printf("Within first if statement - duplicate found.\n");
                    // if the manufacturer is already in the list, it has already been counted
                    manuCounted = 1;
                    break;
                }
                if (manufactArray[j][0] == '\0') {
                    printf("Within else - null point found, adding new value\n");
                    // if we reach a NULL point in the array and the manufacturer has not been counted yet,
                    // it gets added to the list
                    // manufactArray[j] = addressArrayPointer_g[i].macManufac;
                    strcpy(manufactArray[j], addressArrayPointer_g[i].macManufac);
                    break;
                }
            }
            if (manuCounted == 0) {
                printf("Adding on to manufacturer total.\n");
                manufacturerTotal++;
            }
            printf("\n");
            // add each manufacturer to the list
                // add the aliases below the manufacturer
        }
    }

    printf("Total number of valid addresses: %d\n", addressTotal);
    printf("Total number of unique manufacturers: %d\n", manufacturerTotal);
    printf("Valid manufacturers: \n");
    for (int i = 0; i < arrayLen; i++) {
        printf("   %s\n", manufactArray[i]);
    }
    printf("Recorded array length: %d\n", arrayLen);

    // Time to finally build the Report .txt file

    reportFile = fopen("222_Manufacturer_Report.txt", "w");
    fprintf(reportFile, "%s ", username_g);
    fprintf(reportFile, "%s", getDateAndTime());
    fprintf(reportFile, "CS222 Network Manufacturer Report\n");
    fprintf(reportFile, "Address total: %d\n", addressTotal);
    fprintf(reportFile, "Manufacturers: %d\n\n", manufacturerTotal);

    for (int i = 0; i < manufacturerTotal; i++) {
        fprintf(reportFile, "%s\n", manufactArray[i]);
        for (int j = 0; j < arrayLen; j++) {
            if (strcmp(addressArrayPointer_g[j].macManufac, manufactArray[i]) == 0) {
                fprintf(reportFile, "%s", addressArrayPointer_g[j].macAlias);
            }
        }
        fprintf(reportFile, "\n");
    }

    fclose(reportFile);
}

manufacturer_t* readMfgFile() {
    printf("We are in readMfgFile()\n");
    FILE *fileReader = fopen("CS222_Mfg.txt", "r");
    printf("fileReader is open\n");
    char charBuffer[50];
    int maxLineLength = 60;
    manufacturer_t *returnArrayPointer;

    if (fileReader == NULL) { // error for if the file cannot be opened
        printf("Unable to open 'CS222_Mfg.txt' file.\n");
        exit(1);
    }
    int recordCount = 0;
    while (fgets(charBuffer, maxLineLength, fileReader)) { // count number of addresses
        recordCount++;
    }
    // returnArrayPointer = (manufacturer_t*) malloc(recordCount * sizeof(*returnArrayPointer));
    manufacturer_t returnArrayPointer[recordCount];

    rewind(fileReader);
    printf("fileReader has rewound\n");
    int i = 0;
    while (fgets(charBuffer, maxLineLength, fileReader)) {
        printf("Current while loop charBuffer: %s\n", charBuffer);
        for (int j = 0; j < 9; j++) { // copy over the MAC address digits
            returnArrayPointer[i].manufacCode[j] = charBuffer[j];
        }
        returnArrayPointer[i].manufacCode[8] = '\0';
        int k = 0;
        for (int j = 9; j < maxLineLength; j++) {
            returnArrayPointer[i].manufacName[k] = charBuffer[j];
            k++;
        }
        i++;
    }
    printf("Finished whole while loop.\n");
    fclose(fileReader);
    printf("fileReader has closed.\n");
    return returnArrayPointer;
}

void generateMfgRptByName(manufacturer_t *manufacturerArray) {
    printf("Great success!!!\n");
}