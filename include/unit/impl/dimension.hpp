#pragma once

namespace Unit
{

/*
 * Dimension of SI Base Units
 * 
 * L :      Length
 * M :      Mass
 * T :      Time
 * Theta :  Thermodynamic Temeprature
 * N :      Amount of Substances
 * I :      Current
 * J :      Luminous Intensity
 *
 */


template <int L, int M, int T, int Theta, int N, int I, int J>
struct Dim {

    template <int L_, int M_, int T_, int Theta_, int N_, int I_, int J_>
    Dim<L + L_, M + M_, T + T_, Theta + Theta_, N + N_, I + I_, J + J_> operator*(const Dim<L_, M_, T_, Theta_, N_, I_, J_>& rhs)
    {
        return {};
    }

    template <int L_, int M_, int T_, int Theta_, int N_, int I_, int J_>
    Dim<L - L_, M - M_, T - T_, Theta - Theta_, N - N_, I - I_, J - J_> operator/(const Dim<L_, M_, T_, Theta_, N_, I_, J_>& rhs)
    {
        return {};
    }
};

using DimensionLess = Dim<0, 0, 0, 0, 0, 0, 0>;

namespace Impl
{
template <class T>
struct get_dimensions {
};

template <int L_, int M_, int T_, int Theta_, int N_, int I_, int J_>
struct get_dimensions<Dim<L_, M_, T_, Theta_, N_, I_, J_>> {
    static constexpr int L = L_;
    static constexpr int M = M_;
    static constexpr int T = T_;
    static constexpr int Theta = Theta_;
    static constexpr int N = N_;
    static constexpr int I = I_;
    static constexpr int J = J_;
};

}  // namespace Impl

}  // namespace Unit
