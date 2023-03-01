#include <iostream>
#include <list>

class Test {
public:
    Test(int a, int b, int c) {
        ma = a;
        mb = b;
        mc = c;
        std::cout << "Test constructed." << std::endl;
    }

    ~Test() {
        std::cout << "Test destructed." << std::endl;
    }

    Test(const Test& rhs) {
        if (this == &rhs) {
            return;
        }
        this -> ma = rhs.ma;
        mb = rhs.mb;
        mc = rhs.mc;
        std::cout << "Test copy-constructed." << std::endl;
    }
private:
    int ma;
    int mb;
    int mc;        
};

int main() {
    std::list<Test> collections;
    for (int i=0; i<10; i++) {
        // 下面的过程调用3次函数
        // 1. 构造函数 2.拷贝构造函数(push back里) 3. t的析构函数
        Test t(i, i*2, i*3);
        collections.push_back(t);
    }
    for (int i=0; i<10; i++) {
        // 只调用一次构造函数
        collections.emplace_back(i, 2*i, 3*i);
    }
}