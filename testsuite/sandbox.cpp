#include <unit/double.hpp>

#include <iostream>

int main()
{

    using namespace Unit;

    Phase phi = 1.0_rad;

    double s = sin(phi);

    Vel v = 1.0_mm / 1.0_s;
    Acc a = 1.0_km / 1.0_s / 1.0_s;
    Energy E = 1.00555_J;

    std::cout << v << std::endl;
    std::cout << a << std::endl;
    std::cout << E << std::endl;

    return 0;
}
