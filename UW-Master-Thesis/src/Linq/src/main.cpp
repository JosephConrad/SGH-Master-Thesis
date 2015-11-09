
#include <iostream>
#include <vector>

#include <A/A.h>

using namespace std;

int main()
{
    std::cout << "Foo main" << std::endl;
    auto print = [](vector<int>& list){ cout << "List: "; for (int x : list) cout << x << " "; cout << endl;};

    cout << "10 naturals" << endl;
    auto result = SELECT([](int x){ return x; }) FROM(Naturals()) LIMIT(10);
    print(result);

//    cout << "Distinct test" << endl;
//    result = SELECT([](int x, int y){ return x+y; }) FROM(Naturals(), Naturals())
//    WHERE([](int x, int y){ return (x*x + y*y < 25); }) DISTINCT LIMIT(10);
//    print(result);
//
//    cout << "Intersection" << endl;
    vector<int> ints = {11,2,1,5,6,7};
    print(ints);
//    vector<int> ints2 = {3,4,5,7,8,11};
//
//    result = SELECT([](int x, int y){ return x; })
//    FROM(ints, ints2)
//    WHERE([](int x, int y){ return (x == y); }) SORT NOLIMIT;
//    print(result);
//
//    // Simple map operation as list comprehension
//    cout << "Map" << endl;
//    result = SELECT([](int x){ return x + 5; }) FROM(ints) NOLIMIT;
//    print(result);
//
//    cout << "Pythagorean Triplets" << endl;
//    SelectContinuation state;
//
//    auto lazypyth = LAZYSELECT([&](int x, int y, int z){ return make_tuple(z,y,x); })
//    FROM(Naturals(1,100000000),
//         [](int x){ return Naturals(1,x); },
//         [](int x,int y){ return Naturals(1,y); })
//    WHERE([&](int x, int y, int z){  return x*x == y*y + z*z; })
//    LAZY(state) LIMIT(5);
//
//    auto pyth = lazypyth();
//    cout << "Part1:" << endl;
//    for (auto line: pyth) cout << " -> " << get<0>(line) << " " << get<1>(line) << " " << get<2>(line) << endl;
//    pyth = lazypyth();
//    cout << "Part2:" << endl;
//    for (auto line: pyth) cout << " -> " << get<0>(line) << " " << get<1>(line) << " " << get<2>(line) << endl;

    return 0;
}
