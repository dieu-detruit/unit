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
    auto norm = wavefront.norm();
    Phase phase = wavefront.arg();

    DEBUG_LOG(real);
    DEBUG_LOG(imag);
    DEBUG_LOG(conj);
    DEBUG_LOG(norm);
    DEBUG_LOG(phase);

    DEBUG_LOG(std::polar(1.0, 0.5 * 3.14159265358979_rad));
    wavefront *= std::polar(1.0, 0.5 * 3.14159265358979_rad);
    DEBUG_LOG(wavefront);

    Complex<Length> c1 = (1.0 + 2.0i) * 1.0_m;
    Complex<Length> c2 = (2.0 + 3.0i) * 1.0_m;
    Complex<Length> c3 = c1 + c2;
    std::complex<double> c4 = c1 / c2;

    auto n1 = c1.norm();

    DEBUG_LOG(c1);
    DEBUG_LOG(c2);
    DEBUG_LOG(n1);
    DEBUG_LOG(std::sqrt(n1));
    DEBUG_LOG(n1 * 1);

    return 0;
}
