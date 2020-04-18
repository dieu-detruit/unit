# unit
Boost.Unitsがconstexprに対応していなくて不便だったので書いた

## 使い方

- unit/float.hpp, unit/double.hpp, unit/long_double.hpp のいずれかをincludeします。数値型がそれぞれの名前に対応した単位型が使えるようになります。
- 使い方自体はサンプルそのものです。

```cpp
#include <unit/double.hpp>

int main()
{
    using namespace Unit;
    
    Length x = 1.0_km;
    Vel v = 1.0_m / 1.0_s;

    Angle angle = 1.0_rad;
    Phase phi = 1.0_rad;
  
    Length amp = 1.0_m;
    // 無次元量に対してはsin, cos, tanのラッパが用意されています
    Length wave = amp * sin(phi); 

    Energy E = 1.0_MJ;
    
    std::cout << x << std::endl;
    std::cout << v << std::endl;
    std::cout << E << std::endl;

    return 0;
}
```
