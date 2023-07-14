#include <iostream>

#include "Position.hpp"

#define ASSERT_EQUAL(value, target) if((value) != (target)) { \
                                        std::cerr << #value << " is not equal to " << #target; \
                                        std::cerr << " real value is " << (value); \
                                        std::cerr << ' ' << __FILE__ << ":" << __LINE__ << std::endl; \
                                    }

int main()
{
    Position a;
    Position b(1, 2);
    Position c = b.add(-1, -2);
    ASSERT_EQUAL(b.safeToAdd(-1, 5), true);
    ASSERT_EQUAL(b.safeToAdd(-2, 5), false);
    ASSERT_EQUAL(b.safeToAdd(-1, 6), false);
    ASSERT_EQUAL(c, a);
    ASSERT_EQUAL(b, 17);
    ASSERT_EQUAL(a, 0);
    return 0;
}