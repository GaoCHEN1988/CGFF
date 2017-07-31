#ifndef COMMON_H
#define COMMON_H

#include <functional>

namespace CGFF {
    
// Common defines
#define BIT(x) (1 << x)

#define METHOD_1(x) std::bind(x, this, std::placeholders::_1)
#define CGFF_METHOD(x) METHOD_1(x)

}
#endif