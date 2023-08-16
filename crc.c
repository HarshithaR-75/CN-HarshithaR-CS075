#include <stdio.h>
#include <string.h>

// CRC-CCITT polynomial: x^16 + x^12 + x^5 + 1 (0x1021)
#define CRC_POLY 0x1021

// Function to calculate CRC-CCITT checksum
unsigned short calculateCRC(const char *data, int length) {
    unsigned short crc = 0xFFFF; // Initial value
    for (int i = 0; i < length; i++) {
        crc ^= (unsigned short)data[i] << 8;
        for (int j = 0; j < 8; j++) {
            if (crc & 0x8000)
                crc = (crc << 1) ^ CRC_POLY;
            else
                crc <<= 1;
        }
    }
    return crc;
}

int main() {
    char data[100]; // Replace with your actual data
    printf("Enter data: ");
    scanf("%s", data);

    int dataLength = strlen(data);
    unsigned short checksum = calculateCRC(data, dataLength);

    printf("Calculated CRC: 0x%04X\n", checksum);

    // Simulating error by changing a bit
    // data[2] ^= 0x01; // Uncomment this line to introduce an error

    // Verify the received data
    unsigned short receivedChecksum;
    printf("Enter received CRC: ");
    scanf("%hx", &receivedChecksum);

    if (receivedChecksum == checksum) {
        printf("Data is error-free.\n");
    } else {
        printf("Data contains errors.\n");
    }

    return 0;
}

