#include <iostream>

[[deprecated("use funcY instead")]] void funcX() {

}

int main() {
    funcX();
    return 0;
}