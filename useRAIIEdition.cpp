#include <winsock2.h>
#include <stdio.h>

#pragma comment(lib, "ws2_32.lib")

class ServerSocket {
public:
    ServerSocket() {
        m_bInit = false;
        m_ListenSocket = -1;
    }
    ~ServerSocket() {
        if (m_ListenSocket != -1)::closesocket(m_ListenSocket);
        if (m_bInit)::WSACleanup();
    }
    bool DoInit() {
        // 初始化socket库
        WORD wVersionRequested = MAKEWORD(2,2);
        WSADATA wsaData;
        int err = WSAStartup(wVersionRequested, &wsaData);
        if (err != 0) {
            return false;
        }
        if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
            return false;
        }
        m_bInit = true;

        // 创建用于监听的socket
        m_ListenSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (m_ListenSocket == -1) {
            return false;
        }
        return true;
    }

    bool DoBind(const char* ip, short port = 6000) {
        SOCKADDR_IN addrSrv;
        addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
        addrSrv.sin_family = AF_INET;
        addrSrv.sin_port = htons(6000); 
        // 绑定socket, 监听6000端口
        if (::bind(m_ListenSocket, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR)) == -1) {
            return false;
        }
        return true;
    }
    bool DoListen(int backlog = 15) {
        if (::listen(m_ListenSocket, backlog) == -1) {
            return false;
        }
        return true;
    }

    bool DoAccept() {
        SOCKADDR_IN addrClient;
        int len = sizeof(SOCKADDR);
        char msg[] = "Hello World!";
        while (true) {
            // 等待客户端请求的到来, 如果有客户端连接, 则接收连接
            SOCKET sockClient = accept(m_ListenSocket, (SOCKADDR*)&addrClient, &len);
            if (sockClient == -1) {
                break;
            }
            // 向客户端发送"HelloWorld"消息(0是什么?)
            ::send(sockClient, msg, strlen(msg), 0);
            ::closesocket(sockClient);
        }
        return false;
    }
private:
    bool m_bInit;  
    SOCKET m_ListenSocket;  
};

int main(int argc, char* argv[]) {
    ServerSocket serverSocket;
    if (!serverSocket.DoInit()) {
        return false;
    }

    if (!serverSocket.DoBind("0.0.0.0", 6000)) {
        return false;
    }

    if (!serverSocket.DoListen(15)) {
        return false;
    }

    if (!serverSocket.DoAccept()) {
        return false;
    }
    return 0;
}