#include <iostream>
#include <memory>

class Socket{
public:
    Socket(){}
    ~Socket(){}
    void close(){}        
};

//unik ptr可以自定义资源回收函数，实现复杂析构。
int main() {
    auto deleter = [](Socket* pSocket) {
        // 关闭句柄
        pSocket -> close();
        delete pSocket;
    };
    std::unique_ptr<Socket, decltype(deleter)> spSocket(new Socket(), deleter);
}