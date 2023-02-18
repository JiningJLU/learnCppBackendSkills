#include <winsock2.h>
#include <stdio.h>

#pragma comment(lib, "ws2_32.lib")

int main(int argc, char* argv[]) {

    // 注意: 由于goto语句不能跳过变量定义，所以在这里提前定义下文需要用到的变量
    SOCKET sockSrv;
    SOCKADDR_IN addrSrv;
    SOCKADDR_IN addrClient;
    int len = sizeof(SOCKADDR);
    char msg[] = "Hello World!";

    // 初始化socket库
    WORD wVersionRequested = MAKEWORD(2,2);
    WSADATA wsaData;
    int err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0) {
        // 这里为什么不cleanup?
        return 1;
    }
    // 这两行干嘛用？
    if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
        goto cleanup2;
        return 1;
    }

    // 创建用于监听的socket
    sockSrv = socket(AF_INET, SOCK_STREAM, 0);
    if (sockSrv == -1) {
        goto cleanup2;
        return 1;
    }

    addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
    addrSrv.sin_family = AF_INET;
    addrSrv.sin_port = htons(6000);

    // 绑定socket, 监听6000端口
    if (bind(sockSrv, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR)) == -1) {
        goto cleanup1;
        return 1;
    }

    // 启动监听, 准备接收客户端的连接请求
    // 15是什么?
    if (listen(sockSrv, 15) == -1) {
        goto cleanup1;
        return 1;
    }

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

cleanup1:
    closesocket(sockSrv);

cleanup2:
    WSACleanup();

    return 0;
}