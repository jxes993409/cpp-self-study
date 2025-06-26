# Lambda Expression
```
[capture clause](parameter list) optional specification -> trailing-return-type
{
    /* lambda body */
};
```
## lamda expression example
lambda expressions 能讓程式更加簡潔
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
1. `capture by reference` 可以保證當數值更新時，在 lambda expression 中的值也會更新
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
2. `capture by value` 的變數是常數型態，不能在 lambda function 中對它修改
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
增加 `mutable` 便可允許常數型態的變數在 lambda function 中更新，並且不會影響變數本身的值
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
1. `[=]` 以 `value` 擷取
2. `[&]` 以 `reference` 擷取
3. `[&, =var]` 以 `reference` 為擷取預設，特定變數以 `value` 擷取
4. `[=, &var]` 以 `value` 為擷取預設，特定變數以 `reference` 擷取
5. `[=, =var]` 與 `[&, &var]` 是不合法的，因為預設跟特定的擷取方式是一樣的
## capture by reference out of scope
擷取的變數已經不存在，可能會導致無法預期的行為發生
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
1. `[this]` 以 `reference` 擷取
2. `[*this]` 以 `value` 擷取，如果需要修改成員內容，在 lambda 表達式增加 `mutable`
3. `[=], [&], [&, this]` 皆以 `reference` 擷取 `this`
4. `[=, *this]` 從 C++ 17 開始支援
5. `[=, this]` 從 C++ 20 開始支援
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