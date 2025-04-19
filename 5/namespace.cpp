#include <bits/stdc++.h>

using namespace std;

namespace space_0
{
    int my_max(int a, int b)
    {
        cout << "namespace space_0 my_max" << endl;
        return (a > b) ? a : b;
    }
}

namespace space_1
{
    int my_max(int a, int b)
    {
        cout << "namespace space_1 my_max" << endl;
        return (a > b) ? a : b;
    }
}

int my_max(int a, int b)
{
    cout << "namespace global space my_max" << endl;
    return (a > b) ? a : b;
}

int a = 1;
namespace space_2
{
    int a = 2;
    namespace space_3
    {
        int a = 3;
    }
}

int main()
{
    using namespace space_0;
    // same as int max_num = space_0::my_max(5, 6);
    
    // this will use global space my_max
    int max_num = ::my_max(5, 6);

    cout << "::a = " << ::a << endl;
    cout << "space_2::a = " << space_2::a << endl;
    cout << "space_2::space_3::a = " << space_2::space_3::a << endl;
}