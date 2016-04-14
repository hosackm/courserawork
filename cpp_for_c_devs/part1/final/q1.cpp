#include <iostream>

int main(){
    int a = 2, b = -3, c = 2;
    bool tval1 = false, tval2 = true;
    char ch = 'b';

    std::cout << "b + c * a = " << b + c * a << std::endl;
    std::cout << "c % 5 / 2 = " << c % 5 / 2 << std::endl;
    std::cout << "-a * c++ = " << -a * c++ << std::endl;
    std::cout << "tval1 && tavl2 = " << (tval1 && tval2) << std::endl;

    return 0;
}