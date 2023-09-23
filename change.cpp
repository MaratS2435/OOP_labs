#include "change.h"
#include <string>

std::string change(std::string s) {
    for (unsigned i = 0; i < s.length(); ++i) {
        if (s[i] == 'a') {
            s[i] = 'b';
        } else if (s[i] == 'b') {
            s[i] = 'a';
        };
    };

    return s;
}