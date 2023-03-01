// nodiscard指返回值不要忽略
[[nodiscard]] int connect(const char *address, short port)
{
    return 0;
}
int main()
{
    connect("127.0.0.1", 9999);
    return 0;
}