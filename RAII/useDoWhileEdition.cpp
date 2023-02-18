/*
    在这个例子中，通过do-while和break进行逻辑控制，使得资源回收全部可以在循环结束的位置进行，不用在每个err的地方都回收。
*/
#include <winsock2.h>
#include <stdio.h>

#pragma comment(lib, "ws2_32.lib")

int main(int argc, char* argv[]) {
    // 初始化socket库
    WORD wVersionRequested = MAKEWORD(2,2);
    WSADATA wsaData;
    int err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0) {
        return 1;
    }

    SOCKET sockSrv = -1;
    do {
        if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
            break;
        }
        // 创建用于监听的socket
        SOCKET sockSrv = socket(AF_INET, SOCK_STREAM, 0);
        if (sockSrv == -1) {
            return 1;
        }
        SOCKADDR_IN addrSrv;
        addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
        addrSrv.sin_family = AF_INET;
        addrSrv.sin_port = htons(6000);
        // 绑定socket, 监听6000端口
        if (bind(sockSrv, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR)) == -1) {
            break;
        }
        // 启动监听, 准备接收客户端的连接请求
        if (listen(sockSrv, 15) == -1) {
            break;
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
    } while(0);

    if (sockSrv != -1) {
        closesocket(sockSrv);
    }
    WSACleanup();
    return 0;
}