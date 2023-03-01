#include<iostream>
#include<memory>

class A : public std::enable_shared_from_this<A> {
public:
    A() {
        std::cout << "A constructor" << std::endl;
    }
    ~A() {
        std::cout << "A destructor" << std::endl;
    }
    std::shared_ptr<A> getSelf() {
        // 返回包含this的share ptr
        return shared_from_this();
    }
    // A对象最好别持有自己的share ptr，否则用不好会内存泄漏。建议用weak ptr.
};

int main() {
    // 注意这里是堆内存。不能共享栈内存。智能指针只能管理堆内存。
    std::shared_ptr<A> sp1(new A());
    std::shared_ptr<A> sp2 = sp1->getSelf();
    std::cout << "use count: " << sp1.use_count() << std::endl;
    return 0;
}