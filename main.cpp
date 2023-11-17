#include <iostream>
#include "Five.h"

using namespace std;

int main() {
    Five empt;
    cout << empt << " Empty..."<< endl;
 
    Five a(5, 10);
    cout << a << endl;
    string str;
    cin >> str;
    Five b = {4, 10, 12};
    Five c = str;
    if (b != c) cout << b << " and " << c << " are not equal and their sum is " << b + c << endl;
    
    Five d = string("000000000004");
    Five f = string("01");
    cout << d << endl;
    cout << f << endl;
    cout << d - f << endl;
    cout << d + f << endl;

return 0;
}