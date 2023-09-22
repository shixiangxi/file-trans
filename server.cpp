#include "file_transfer.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <time.h>
using namespace std;

string transs(time_t timeStamp) {
    struct tm* timeinfo = nullptr;
    char buffer[80];
    timeinfo = localtime(&timeStamp);
    strftime(buffer, 80, "%Y-%m-%d-%H-%M-%S", timeinfo);
    return string(buffer);
}

void server_receive_file() {
    int server_sock = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(1234);
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(server_sock, (struct sockaddr*)&server_address, sizeof(server_address));
    listen(server_sock, 20);

    struct sockaddr_in client_address;
    socklen_t client_len = sizeof(client_address);

    while (true) {
        int client_sock = accept(server_sock, (struct sockaddr*)&client_address, &client_len);

        char buffer[1024];
        ssize_t len;
        time_t now = time(0);
        string filename = transs(now) + ".txt";  // 直接将now变量传入transs函数
        ofstream file(filename, ios::binary);

        while ((len = recv(client_sock, buffer, sizeof(buffer), 0)) > 0) {
            file.write(buffer, len);
        }

        close(client_sock);
        file.close();
    }

    close(server_sock);
}

int main() {
    server_receive_file();
    return 0;
}
