#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <Winsock2.h>

#pragma comment(lib, "Ws2_32.lib")

void wakeOnLAN(const char* macAddress) {
    // Create magic packet
    char magicPacket[102];

    // Add 6 bytes of 0xFF (header)
    for (int i = 0; i < 6; ++i) {
        magicPacket[i] = 0xFF;
    }

    // Repeat the target MAC address 16 times in the magic packet
    for (int i = 6; i < 102; i += 6) {
        sscanf_s(macAddress, "%2hhx:%2hhx:%2hhx:%2hhx:%2hhx:%2hhx",
            &magicPacket[i], &magicPacket[i + 1], &magicPacket[i + 2],
            &magicPacket[i + 3], &magicPacket[i + 4], &magicPacket[i + 5]);
    }

    // Initialize Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed.\n";
        return;
    }

    // Create a UDP socket
    SOCKET udpSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (udpSocket == INVALID_SOCKET) {
        std::cerr << "Error creating socket: " << WSAGetLastError() << "\n";
        WSACleanup();
        return;
    }

    // Set broadcast option
    int broadcastOption = 1;
    if (setsockopt(udpSocket, SOL_SOCKET, SO_BROADCAST, (const char*)&broadcastOption, sizeof(broadcastOption)) == SOCKET_ERROR) {
        std::cerr << "Error setting broadcast option: " << WSAGetLastError() << "\n";
        closesocket(udpSocket);
        WSACleanup();
        return;
    }

    // Set up the address structure
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(9);  // WoL uses port 9
    addr.sin_addr.s_addr = inet_addr("255.255.255.255");  // Broadcast address

    // Send the magic packet
    if (sendto(udpSocket, magicPacket, sizeof(magicPacket), 0, (sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR) {
        std::cerr << "Error sending magic packet: " << WSAGetLastError() << "\n";
    }

    // Cleanup
    closesocket(udpSocket);
    WSACleanup();
}

int main() {
    // Replace "00:11:22:33:44:55" with the target PC's MAC address
    wakeOnLAN("00:11:22:33:44:55");

    return 0;
}
