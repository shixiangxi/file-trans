// client.cpp
#include "file_transfer.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#define _WIN32_WINNT 0x0601
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")  //加载 ws2_32.dll

void client_send_file(const std::string& filename) {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    SOCKET sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    sockaddr_in sockAddr;
    memset(&sockAddr, 0, sizeof(sockAddr));
    sockAddr.sin_family = PF_INET;
    sockAddr.sin_port = htons(1234);
    inet_pton(AF_INET, "127.0.0.1", &(sockAddr.sin_addr)); // 服务端的ip地址 默认是1234端口

    connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));

    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    if (!file) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    auto size = file.tellg();
    file.seekg(0, std::ios::beg);
    std::vector<char> buffer(size);
    if (file.read(buffer.data(), size)) {
        send(sock, buffer.data(), buffer.size(), 0);
    }
    else {
        std::cerr << "Failed to read file: " << filename << std::endl;
    }

    closesocket(sock);
    WSACleanup();
}
int main() {
    client_send_file("1.txt");//发送的文件名
    return 0;
}