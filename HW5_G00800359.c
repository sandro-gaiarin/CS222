#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct address {
    char mac1[2];
    char mac2[2];
    char mac3[2];
    char mac4[2];
    char mac5[2];
    char mac6[2];
    char macAlias[16];
} address_t;
/*
Open and read data file (CS222_Inet.txt)
While reading, generate the CS222_Error_Report.txt file
Dynamically allocate array of address_t structs
rewind() CS222_Inet.txt file
Populate dynamically allocated array
*/
void readDataFile(char fileName[]);
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
    //TODO
}

char *getDateAndTime() {
    time_t t;
    time(&t);
    return ctime(&t);
}