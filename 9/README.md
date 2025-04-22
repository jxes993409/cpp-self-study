# Lambda Expression
```
[capture clause](parameter list) optional specification -> trailing-return-type
{
    /* lambda body */
};
```
## lamda expression example
Using lambda expressions can make code more concise
```
struct _p
{
    int _x;
    int _y;

    int operator()(int a, int b)
    {
        return _x * a + _y * b;
    }
};

int x = 7;
int y = 3;

function<int(int, int)> p_0 = [x, y](int a, int b) -> int
{
    return x * a + y * b;
};

cout << _p{x, y}(10, 20) << endl;

cout << p_0(10, 20) << endl;
```
```
130
130
```
```
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
```
```
before sort: 6 10 11 8 22 33 5 0 -5 9 20 
after sort: 33 22 20 11 10 9 8 6 5 0 -5
```
## Capture clause
### capture by reference / value
1. Capture by reference ensures that when the value is updated, the variable in the lambda expression is also updated
```
function<int(int, int)> p_0 = [x, y](int a, int b) -> int
{
    return x * a + y * b;
};

function<int(int, int)> p_1 = [x, &y](int a, int b) -> int
{
    return x * a + y * b;
};

y = 10;

cout << p_0(10, 20) << endl;

cout << p_1(10, 20) << endl;
```
```
130
270
```
2. The variable captured by value is const type, meaning its value cannot be modified
```
function<int(int, int)> p_0 = [x, y](int a, int b) -> int
{
    x = 10;
    return x * a + y * b;
};
```
```
error: assignment of read-only variable ‘x’
   24 |         x = 10;
      |         ~~^~~~
```
Adding `mutable` allows a const variable to be modified
```
function<int(int, int)> p_2 = [x, y](int a, int b) mutable -> int
{
    x = 10;
    return x * a + y * b;
};

cout << p_2(10, 20) << endl;
```
```
160
```
## Automatically capture
1. `[=]` capture variables by `value`
2. `[&]` capture variables by `reference`
3. `[&, =var]` captures variables by `reference` by default, while specific variables are captured by `value`
4. `[=, &var]` captures variables by `value` by default, while specific variables are captured by `reference`
5. `[=, =var]` and `[&, &var]` are ileagal, because default and specific are same
## capture by reference out of scope
Because the variables captured by reference no longer exist, unexpected results may occur
```
function<int(int, int)> create_lambda()
{
    int _x = 7;
    int _y = 3;

    return [&](int a, int b) -> int {return _x * a + _y * b;};
}
// in main
function<int(int, int)> p_3 = create_lambda();

cout << p_3(10, 20) << endl;
```
```
-1099568934
```
## capture class member
1. `[this]` capture by `reference`
2. `[*this]` capture by `value`. If modification is needed, add `mutable` to the expression
3. `[=], [&], [&, this]` are capture `this` by `reference
4. `[=, *this]` support since C++ 17
5. `[=, this]` support since C++ 20
```
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

lambda_class cls_0(5);
cls_0.print();
```