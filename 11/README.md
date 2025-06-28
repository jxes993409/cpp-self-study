# Constexpr
constexpr 主要目的是將能在編譯時能完成的計算，從執行時提前到編譯時，以提升程式運行的效能
## Examples
* 透過 `constexpr`，即便是函式的呼叫也能用在如陣列大小的設定
```
constexpr size_t multi(size_t a, size_t b)
{
    return a * b;
}

array<int, multi(6, 6)> arr;
```
* class 也可加上 constexpr，如下面的範例
```
class Complex
{
public:
    constexpr Complex(double r = 0, double i = 0): _r(r), _i(i) {}
    constexpr double get_r() const
    {
        return _r;
    }
    constexpr double get_i() const
    {
        return _i;
    }
    constexpr void set_r(double r)
    {
        _r = r;
    }
    constexpr void set_i(double i)
    {
        _i = i;
    }
private:
    double _r;
    double _i;
};

constexpr Complex multi(const Complex& a, const Complex& b)
{
    Complex res;
    res.set_r(
        a.get_r() * b.get_r() -
        a.get_i() * b.get_i()
    );
    res.set_i(
        a.get_r() * b.get_r() +
        a.get_i() * b.get_i()
    );

    return res;
}

constexpr Complex p1(1.5, 2.3);
constexpr Complex p2(2.6, 3.5);

Complex p3 = multi(p1, p2);
```

# Decltype
## Decltype(var)
相較於 `auto`，`decltype()` 可以保留變數的 const, volatile 以及 reference 的特性
### Examples
* auto 只會保留變數型態 (int)，不會保留 const 的限定符 (qualifier)
```
const int x = 4;
decltype(x) dx = x;
auto ax = x;

dx = 5;
ax = 5;
```
```
decltype.cpp: In function ‘int main()’:
decltype.cpp:12:8: error: assignment of read-only variable ‘dx’
   12 |     dx = 5;
      |     ~~~^~~
```
* auto 只會保留變數型態 (int)，不會保留 reference 的特性
```
int x = 4;
int& rx = x;
decltype(rx) dx = x;
auto ax = x;

dx = 6;
cout << "x: " << x << endl;
ax = 8;
cout << "x: " << x << endl;
```
```
x: 6
x: 6
```
## Decltype(expr)
相較於變數，表達式會依據下方的表格來決定變數屬於哪種類型
|表達式類型|結果|
|:-:|:-:|
|lvalue|類型的左值引用|
|prvalue|類型|
|xvalue|類型的右值引用|
### Examples
* 當表達式是函式時，它的資料型態變是函式回傳的值
```
decltype(f1()) s1;              // string
decltype(f2()) s2 = s1;         // string &
decltype(f3(s1)) s3 = move(s1); // string &&

decltype(s1 + "world") s4;            // string
decltype(s1.append("world")) s5 = s1; // string&
```
## Decltype(auto)
### Examples
* `decltype(auto)` 即將右邊的表達式做為 auto 的型態
```
decltype(auto) s6 = s1 + "world";       // string
decltype(auto) s7 = s1.append("world"); // string&
```
* g2 的問題為回傳一個無效的引用
```
decltype(auto) g1(int i)
// int g1(int)
{
    return i;
}

decltype(auto) g2(int i)
// int& g2(int)
{
    return (i);
}

decltype(auto) g3(int &i)
// int& g3(int&)
{
    return (i);
}

decltype(auto) g4(int i)
// int g4(int)
{
    return (i + 1);
}
```