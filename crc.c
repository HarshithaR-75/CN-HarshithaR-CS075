#include <stdio.h>
#include <string.h>

// CRC-CCITT polynomial: x^16 + x^12 + x^5 + 1 (0x1021 in hexadecimal or 1000000100000101 in binary)
#define CRC_POLY_BINARY 1000000100000101

// Function to calculate CRC-CCITT checksum
unsigned short calculateCRC(const char *data, int length) {
    unsigned short crc = 0xFFFF; // Initial value
    for (int i = 0; i < length; i++) {
        crc ^= (unsigned short)data[i] << 8;
        for (int j = 0; j < 8; j++) {
            if (crc & 0x8000)
                crc = (crc << 1) ^ CRC_POLY_BINARY;
            else
                crc <<= 1;
        }
    }
    return crc;
}

int main() {
    char data[100]; // Replace with your actual data
    printf("Enter data in binary: ");
    scanf("%s", data);

    int dataLength = strlen(data);
    unsigned short checksum = calculateCRC(data, dataLength);

    printf("Calculated CRC in binary: ");
    for (int i = 15; i >= 0; i--) {
        printf("%d", (checksum >> i) & 0x01);
    }
    printf("\n");

    // Simulating error by changing a bit
    // data[2] ^= 0x01; // Uncomment this line to introduce an error

    // Verify the received data
    unsigned short receivedChecksum;
    printf("Enter received CRC in binary: ");
    char r`eceivedChecksumBinary[17];
    scanf("%16s", receivedChecksumBinary);

    receivedChecksum = 0;
    for (int i = 0; i < 16; i++) {
        receivedChecksum <<= 1;
        receivedChecksum |= receivedChecksumBinary[i] - '0';
    }

    if (receivedChecksum == checksum) {
        printf("Data is error-free.\n");
    } else {
        printf("Data contains errors.\n");
    }
return 0;
}
