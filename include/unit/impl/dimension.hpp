#pragma once

namespace Unit
{

template <int M, int K, int S, int A>
struct Dim {

    template <int M_, int K_, int S_, int A_>
    Dim<M + M_, K + K_, S + S_, A + A_> operator*(const Dim<M_, K_, S_, A_>& rhs)
    {
        return {};
    }

    template <int M_, int K_, int S_, int A_>
    Dim<M - M_, K - K_, S - S_, A - A_> operator/(const Dim<M_, K_, S_, A_>& rhs)
    {
        return {};
    }
};

using DimensionLess = Dim<0, 0, 0, 0>;

}  // namespace Unit
