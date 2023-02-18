
void func1() {}

void func2() {}

void func3() {}

int main() {
    int type = 0;
    switch (type)
    {
    case 1:
        func1();
        // 这个位置缺少break语句, 且没有fallthrough标注,
        // 可能是一个逻辑错误, 在编译时编译器可能会给出警告, 以提醒修改
    case 2:
        func2();    
        // 这里也缺少break语句, 但是使用了fallthrough标注,
        // 说明是开发者有意而为之的, 编译器不会给出任何警告
    [[fallthrough]];
    case 3:
        func3();
    default:
        break;
    }
    return 0;
}