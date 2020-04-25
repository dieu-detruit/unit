#include <unit/double.hpp>

#include <cmath>
#include <iostream>

int main()
{

    using namespace Unit;

    Phase phi = 1.0_rad;

    double s = std::sin(phi);

    Velocity v = 1.0_mm / 1.0_s;
    Velocity v2 = 1.0_mm / 1.0_s + v;
    Acceleration a = 1.0_km / 1.0_s / 1.0_s;
    auto I = 1.0e+3_cd;

    Energy E = 1.0_keV;

    auto rtE = E.sqrt();

    std::cout << v << std::endl;
    std::cout << a << std::endl;
    std::cout << E << std::endl;
    std::cout << rtE << std::endl;

    return 0;
}
