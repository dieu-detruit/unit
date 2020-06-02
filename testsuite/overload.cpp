#include <unit/double.hpp>

#include <iostream>

#define DEBUG_LOG(var) std::cout << #var ": " << var << std::endl;

int main()
{
    using namespace Unit;

    Complex<Length> wavefront{2.0_m, 2.0_m};

    DEBUG_LOG(wavefront);

    Length real = std::real(wavefront);
    Length imag = std::imag(wavefront);
    Complex<Length> conj = std::conj(wavefront);
    Phase arg = std::arg(wavefront);
    Length norm = std::norm(wavefront);
    Length abs = std::abs(wavefront);

    DEBUG_LOG(conj);
    DEBUG_LOG(real);
    DEBUG_LOG(imag);
    DEBUG_LOG(arg);
    DEBUG_LOG(norm);
    DEBUG_LOG(abs);

    Phase hoge = std::polar(1.0_rad, 1.0_rad);

    return 0;
}
