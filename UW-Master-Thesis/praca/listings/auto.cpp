int x1;                     // potentially uninitialized

auto x2;                    // error! initializer required

auto x3 = 0;                // fine, x3's value is well-defined
