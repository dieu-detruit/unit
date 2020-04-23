#include <unit/double.hpp>

#include <iostream>

#define DEBUG_LOG(var) std::cout << #var ": " << var << std::endl;

int main()
{
    using namespace Unit;

    Complex<Length> wavefront{2.0_m, 2.0_m};

    DEBUG_LOG(wavefront);

    Length real = wavefront.real();
    Length imag = wavefront.imag();
    Complex<Length> conj = wavefront.conj();
    Length norm = wavefront.norm();
    Phase phase = wavefront.arg();

    DEBUG_LOG(real);
    DEBUG_LOG(imag);
    DEBUG_LOG(conj);
    DEBUG_LOG(norm);
    DEBUG_LOG(phase);

    Complex mul = (5.0 + 3.0_j) * (1.0 + 1.0_j);
    DEBUG_LOG(mul);

    DEBUG_LOG(polar(1.0, 0.5 * 3.14159265358979_rad));
    wavefront *= polar(1.0, 0.5 * 3.14159265358979_rad);
    DEBUG_LOG(wavefront);

    Complex c1 = 1.0 + 2.0_i;
    Complex c2 = 2.0 + 3.0_j;
    Complex c3 = c1 + c2;
    Complex c4 = c1 / c2;

    double n1 = c1.norm();
    double n2 = c2.norm_square();

    DEBUG_LOG(c1);
    DEBUG_LOG(c2);
    DEBUG_LOG(n1);
    DEBUG_LOG(n2);

    return 0;
}
