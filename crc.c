#include <stdio.h>
#include <string.h>

// CRC-CCITT polynomial: x^16 + x^12 + x^5 + 1 (0x1021 in hexadecimal or 1000000100000101 in binary)
#define CRC_POLY_BINARY 0x1021

// Function to calculate CRC-CCITT checksum
unsigned short calculateCRC(const char *data, int length) {
    unsigned short crc = 0xFFFF; // Initial value
    for (int i = 0; i < length; i++) {
        crc ^= (data[i] << 8);
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

    printf("Calculated CRC in hexadecimal: 0x%04X\n", checksum);

    // Simulating error by changing a bit (uncomment the line below to introduce an error)
    // data[2] ^= 0x01;

    // Verify the received data
    unsigned short receivedChecksum;
    printf("Enter received CRC in hexadecimal: ");
    scanf("%4hx", &receivedChecksum);

    if (receivedChecksum == checksum) {
        printf("Data is error-free.\n");
    } else {
        printf("Data contains errors.\n");
    }

    return 0;
}

UDP:

ClientUDP.py
from socket import *
serverName = "127.0.0.1"
serverPort = 12000
clientSocket = socket(AF_INET, SOCK_DGRAM)

sentence = input("Enter file name")
clientSocket.sendto(bytes(sentence,"utf-8"),(serverName, serverPort))
filecontents,serverAddress = clientSocket.recvfrom(2048)
print ('From Server:', filecontents)

clientSocket.close()

ServerUDP.py

from socket import *
serverPort = 12000
serverSocket = socket(AF_INET, SOCK_DGRAM)
serverSocket.bind(("127.0.0.1", serverPort))
print ("The server is ready to receive")
while 1:
     sentence,clientAddress = serverSocket.recvfrom(2048)
    
     file=open(sentence,"r")
     l=file.read(2048)
  
     serverSocket.sendto(bytes(l,"utf-8"),clientAddress)
     print("sent back to client",l)
     file.close()


TCP:

Client.py
from socket import *
serverName = “127.0.0.1”
serverPort = 12000
clientSocket = socket(AF_INET, SOCK_STREAM)
clientSocket.connect((serverName,serverPort))
sentence = input("Enter file name")

clientSocket.send(sentence.encode())
filecontents = clientSocket.recv(1024).decode()
print ('From Server:', filecontents)
clientSocket.close()

Server.py

from socket import *
serverName=”127.0.0.1”
serverPort = 12000
serverSocket = socket(AF_INET,SOCK_STREAM)
serverSocket.bind((serverName,serverPort))
serverSocket.listen(1)
print ("The server is ready to receive")
while 1:
    connectionSocket, addr = serverSocket.accept()
    sentence = connectionSocket.recv(1024).decode()
    
    file=open(sentence,"r")
    l=file.read(1024)
  
    connectionSocket.send(l.encode())
    file.close()
    connectionSocket.close()
