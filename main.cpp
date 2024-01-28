#include <iostream>
#include "Trapezoid.h"
#include "Rhomb.h"
#include "Pentagon.h"
#include "Array.h"

int main() {
    Array<Figure<double>*> a;
    Trapezoid<double> t;
    Rhomb<double> r;
    std::cin >> t >> r;
    std::cout << "\n";
    a.Push(&t);
    a.Push(&r);
    
    return 0;
}
