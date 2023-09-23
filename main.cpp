#include <iostream>
#include <string>
#include "change.h"

int main() {
    std::string s;
    std::cin >> s;
    s = change(s);
    std::cout << s;
    return 0;
}