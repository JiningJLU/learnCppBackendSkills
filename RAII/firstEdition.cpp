#include <winsock2.h>
#include <stdio.h>

#pragma comment(lib, "ws2_32.lib")

int main(int argc, char* argv[]) {
    // 初始化socket库
    WORD wVersionRequested = MAKEWORD(2,2);
    WSADATA wsaData;
    int err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0) {
        WSACleanup();
        return 1;
    }
    // 这两行干嘛用？
    if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
        WSACleanup();
        return 1;
    }

    // 创建用于监听的socket
    SOCKET sockSrv = socket(AF_INET, SOCK_STREAM, 0);
    if (sockSrv == -1) {
        WSACleanup();
        return 1;
    }

    SOCKADDR_IN addrSrv;
    addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
    addrSrv.sin_family = AF_INET;
    addrSrv.sin_port = htons(6000); 

    // 绑定socket, 监听6000端口
    if (bind(sockSrv, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR)) == -1) {
        closesocket(sockSrv);
        WSACleanup();
        return 1;
    }

    // 启动监听, 准备接收客户端的连接请求
    // 15是什么?
    if (listen(sockSrv, 15) == -1) {
        closesocket(sockSrv);
        WSACleanup();
        return 1;
    }

    SOCKADDR_IN addrClient;
    int len = sizeof(SOCKADDR);
    char msg[] = "Hello World!";
    while (true) {
        // 等待客户端请求的到来, 如果有客户端连接, 则接收连接
        SOCKET sockClient = accept(sockSrv, (SOCKADDR*)&addrClient, &len);
        if (sockClient == -1) {
            break;
        }
        // 向客户端发送"HelloWorld"消息(0是什么?)
        send(sockClient, msg, strlen(msg), 0);
        closesocket(sockClient);
    }
    closesocket(sockSrv);
    WSACleanup();
    return 0;
}