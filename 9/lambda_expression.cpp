#include <bits/stdc++.h>

using namespace std;

class lambda_class
{
private:
    int m_id;
public:
    lambda_class(int id): m_id(id) {}
    void print()
    {
        [this]() -> void
        {
            m_id++;
            cout << "id: " << m_id << endl;
        }();
    }
    void _print()
    {
        [*this]() mutable -> void
        {
            m_id++;
            cout << "id: " << m_id << endl;
        }();
    }
};

struct _p
{
    int _x;
    int _y;

    int operator()(int a, int b)
    {
        return _x * a + _y * b;
    }
};

function<int(int, int)> create_lambda()
{
    int _x = 7;
    int _y = 3;

    return [&](int a, int b) -> int {return _x * a + _y * b;};
}

int main()
{
    int x = 7;
    int y = 3;

    function<int(int, int)> p_0 = [x, y](int a, int b) -> int
    {
        return x * a + y * b;
    };

    function<int(int, int)> p_1 = [x, &y](int a, int b) -> int
    {
        return x * a + y * b;
    };

    function<int(int, int)> p_2 = [x, y](int a, int b) mutable -> int
    {
        x = 10;
        return x * a + y * b;
    };
    
    // cout << _p{x, y}(10, 20) << endl;
    
    // y = 10;

    // cout << p_0(10, 20) << endl;
    
    // cout << p_1(10, 20) << endl;

    // cout << p_2(10, 20) << endl;
    
    // function<int(int, int)> p_3 = create_lambda();

    // cout << p_3(10, 20) << endl;

    vector<int> numbers{6, 10, 11, 8, 22, 33, 5, 0, -5, 9, 20};
    cout << "before sort: ";
    for(int number: numbers)
    {
        cout << number << " ";
    }
    cout << endl;
    sort(numbers.begin(), numbers.end(), [](int a, int b) -> bool {return a > b;});
    cout << "after sort: ";
    for(int number: numbers)
    {
        cout << number << " ";
    }
    cout << endl;

    lambda_class cls_0(5);
    cls_0._print();
}