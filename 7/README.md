# std::function
`std::function` class template
```
template<class R, class... Args>
class function<R(Args...)>;
```
`std::function` example
```
double add(double a, double b)
{
    return a + b;
}

function<double(double, double)> func_0 = add;
double result = func_0(2.1, 3.2);
cout << result << endl;
```
```
5.3
```
`std::function` 可以封裝 struct 或 class 的 function
```
struct linear_function
{
    double a_;
    double b_;
    double output_y(double x)
    {
        return a_ * x + b_;
    }
};

function<double(linear_function&, double)> func_1 = &linear_function::output_y;
linear_function l{2.0, 3.5};
double result_1 = func_1(l, 6);
cout << result_1 << endl;
```
```
15.5
```
`std::function` 可以封裝 struct 或 class 的 member
```
function<double(linear_function&)> func_2 = &linear_function::a_;
cout << func_2(l) << endl;
```
```
2
```
`std::function` 可以實現 type erasure (類型擦除)，並使用統一個介面 `operator()` 來呼叫函數
```
double add(double a, double b)
{
    return a + b;
}

struct sub
{
    double operator()(double a, double b)
    {
        return a - b;
    }
};

unordered_map<char, function<double(double, double)>> my_map;
// general function
my_map['+'] = add;
// struct function
my_map['-'] = sub();
// lambda expression function
my_map['*'] = [](double a, double b) -> double {return a * b;};

cout << my_map['+'](4.0, 2.0) << endl;
cout << my_map['-'](4.0, 2.0) << endl;
cout << my_map['*'](4.0, 2.0) << endl;
```
```
6
2
8
```

# std::mem_fn
`std::mem_fn` function template
```
template<class M, class T>
mem_fn(M T::*pm) noexcept;
```
相較於 `std::function`，`std::mem_fn` 僅用於封裝 struct 或 class 的 function
```
struct my_struct
{
    float weight;
    float calculate(float a, float b)
    {
        return weight * a + weight * b;
    }
    my_struct& operator+=(float a)
    {
        weight += a;
        return *this;
    }
    void print_weight()
    {
        cout << "weight: " << weight << endl;
    }
};

my_struct data_0{2.0};
function<float(my_struct&, float, float)> mem_fn_0 = mem_fn(&my_struct::calculate);
float result_0 = mem_fn_0(data_0, 2.0, 3.0);
cout << result_0 << endl;

function<my_struct&(my_struct&, float)> mem_fn_1 = mem_fn(&my_struct::operator+=);
my_struct data_1 = mem_fn_1(data_0, 2.0);
data_1.print_weight();
```
```
10
weight: 4
```
# std::bind
`std::bind` function template
```
template<class F, class... Args>
bind(F&&,  Args&&... args);
```
`std::bind` example
```
int sum(int a, int b, int c)
{
    cout << "a: " << a << ", " << "b: " << b << ", " << "c: " << c;
    return a + b + c;
}

function<int()> bind_fn_0 = bind(sum, 1, 2, 3);
int result_0 = bind_fn_0();
cout << ", result_0: " << result_0 << endl;
```
```
a: 1, b: 2, c: 3, result_0: 6
```
如果想動態調整參數，可以使用 `std::placeholders`
```
function<int(int)> bind_fn_1 = bind(sum, 1, placeholders::_1, 3);
int result_1 = bind_fn_1(5);
cout << ", result_1: " << result_1 << endl;
```
```
a: 1, b: 5, c: 3, result_1: 9
```
將變數作為參數時，`bind_fn` 的結果不會隨著變數的值改變
```
int n_2 = 7;
function<int()> bind_fn_2 = bind(sum, 1, n_2, 3);
n_2 = 9;
int result_2 = bind_fn_2();
cout << ", result_2: " << result_2 << endl;
```
```
a: 1, b: 7, c: 3, result_2: 11
```
可以使用 `std::cref()` 來解決上面的問題
```
int n_3 = 7;
function<int()> bind_fn_3 = bind(sum, 1, cref(n_3), 3);
n_3 = 9;
int result_3 = bind_fn_3();
cout << ", result_3: " << result_3 << endl;
```
```
a: 1, b: 9, c: 3, result_3: 13
```