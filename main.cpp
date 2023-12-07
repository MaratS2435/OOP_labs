#include <iostream>
#include "Trapezoid.h"
#include "Rhomb.h"
#include "Pentagon.h"
#include "ArrFigure.h"

int main() {
    ArrFigure a;
    Trapezoid t;
    Rhomb r;
    std::cin >> t >> r;
    std::cout << "\n";
    a.Push(&t);
    a.Push(&r);
    a.Centers();
    a.Areas();
    std::cout << a << '\n';
    
    return 0;
}
