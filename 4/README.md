# Function Template
使用 function template 可以避免重複相同演算法，不同變數型態的程式
```
template<class T>
// template<typename T> also works!
void my_swap(T& a, T& b)
{
    T temp = a;
    a = b;
    b = temp;
}

int a = 5;
int b = 6;
printf("a: %d, b: %d\n", a, b);
my_swap<int>(a, b);
printf("a: %d, b: %d\n", a, b);
```
```
a: 5, b: 6
a: 6, b: 5
```
如果變數型態都正確，程式會優先選擇 overload function
```
template<class T1, class T2>
T1 my_max(T1& a, T2& b)
{
    cout << "use template function" << endl;
    return (a > b) ? a : b;
}

int my_max(int &a, int& b)
{
    cout << "use overload function" << endl;
    return (a > b) ? a : b;
}

my_max(a, b);
my_max<int, int>(a, b);
my_max(a, c);
```
```
use overload function
use template function
use template function
```
## Specialize template function (special case for explicit instantiation)
```
template<>
void my_swap(double& a, double& b)
{
    cout << "specialize template function" << endl;
    double temp = a;
    a = b;
    b = temp;
}
```
## Implicit Instantiation & Explicit Instantiation
### Implicit Instantiation
```
my_swap<int>(a, b);
```
### Explicit Instantiation
```
template void my_swap<int>(a, b);
```

|方式|優點|缺點|
|:-:|:-:|:-:|
|Explicit Instantiation|1.只生成特定模板<br> 2. 減少跨檔案的重複實例|1. 需要自行明確指定模板的參數<br>2. 減少程式碼的靈活度
|Implicit Instantiation|1. 自動生成模板的實例<br>2. 增強靈活性<br>|1. 可能導致有重複的實例<br>2. 在大型專案中，可能需要較長的編譯時間|

# Class Template
## Specialized template class
specialized template class 不會從 template class 繼承，
因此在 `class my_vector<string>` 中，`output()` 需要重新實現
```
template<typename T>
class my_vector
{
private:
    T m_vec[3];
public:
    my_vector(T m_0, T m_1, T m_2)
    {
        m_vec[0] = m_0;
        m_vec[1] = m_1;
        m_vec[2] = m_2;
    }

    void output()
    {
        for (int i = 0; i < 3; i++)
        {
            cout << m_vec[i] << " ";
        }
        cout << endl;
    }
};

// specialize template class
template<>
class my_vector<string>
{
private:
    string m_vec[4];
public:
    my_vector(string m_0, string m_1, string m_2, string m_3)
    {
        m_vec[0] = m_0;
        m_vec[1] = m_1;
        m_vec[2] = m_2;
        m_vec[3] = m_3;
    }
};

my_vector<int> data_0(0, 1, 2);
my_vector<char> data_1('a', 'b', 'c');
my_vector<string> data_2("abc", "def", "ghi", "jkl");

data_2.output();
```
```
error: ‘class my_vector<std::__cxx11::basic_string<char> >’ has no member named ‘output’
   49 |         data_2.output();
      |                ^~~~~~
```
## Partially specialized template class
```
template<typename T1, typename T2>
class my_class
{
private:
    T1 first;
    T2 second;
public:
    my_class(T1 a, T2 b): first(a), second(b) {}
};

template<typename T2>
class my_class<int, T2>
{
private:
    int first;
    T2 second;
public:
    my_class(int a, T2 b): first(a), second(b) {}
    void output()
    {
        cout << "partially specialized template class my_class<int, T2>" << endl;
    }
};

template<typename T1>
class my_class<T1, float>
{
private:
    T1 first;
    float second;
public:
    my_class(T1 a, float b): first(a), second(b) {}
    void output()
    {
        cout << "partially specialized template class my_class<T1, float>" << endl;
    }
};

my_class<int, char> data_3(0, 'a');
my_class<string, float> data_4("abc", 0.0);

data_3.output();
data_4.output();
```
```
partially specialized template class my_class<int, T2>
partially specialized template class my_class<T1, float>
```
如果呼叫 `my_class<int, float> data_5(0, 0.0)`

```
error: ambiguous template instantiation for ‘class my_class<int, float>’
   97 |         my_class<int, float> data_5(0, 0.0);
      |
```
compiler 無法決定該用哪個 template，因此需要再額外創建一個 `class my_class<int, float>` 的模板
```
template<>
class my_class<int, float>
{
private:
    int first;
    float second;
public:
    my_class(int a, float b): first(a), second(b) {}
    void output()
    {
        cout << "partially specialized template class my_class<int, float>" << endl;
    }
};

my_class<int, float> data_5(0, 0.0);
data_5.output();
```
```
partially specialized template class my_class<int, float>
```
## Specialized template class for pointer
```
template<typename T1, typename T2>
class my_class<T1*, T2*>
{
private:
    T1* first;
    T2* second;
public:
    my_class(T1* a, T2* b): first(a), second(b) {}
    void output()
    {
        cout << "specialized template class for pointer my_class<T1*, T2*>" << endl;
    }
};

int* ptr_1 = new int;
int* ptr_2 = new int;
my_class<int*, int*> data_6(ptr_1, ptr_2);

data_6.output();
```
```
specialized template class for pointer my_class<T1*, T2*>
```
## None-type parameter
`my_array` 可以透過 `my_array<int, n>` 創建，其中 `n` 是常數型態

如果 `template<typename T = float, int N = 5>` 有預設的模板，可以直接 `my_array<>` 來使用模板
```
// none-type parameter
template<typename T = float, int N = 5>
class my_array
{
private:
    T m_arr[N];
public:
    my_array(T arr[N])
    {
        for (int i = 0; i < N; i++)
        {
            m_arr[i] = arr[i];
        }
    }
    void output()
    {
        for (int i = 0; i < N; i++)
        {
            cout << m_arr[i] << " ";
        }
        cout << endl;
    }
};

int arr_0[5] = {0, 1, 2, 3, 4};
double arr_1[5] = {0.0, 1.0, 2.0, 3.0, 4.0};

const int n_1 = 5;
int n_2 = 5;

my_array<int, 5> data_7(arr_0);
// n 是常數型態
my_array<int, n_1> data_8(arr_0);
// n_2 需要是常數型態
// my_array<int, n_2> data_9(arr_0);

// int, 5
my_array<> data_10(arr_0);
// double, 5
my_array<double> data_11(arr_1);
data_7.output();
```
```
0 1 2 3 4
```
```
error: the value of ‘n_2’ is not usable in a constant expression
  170 |         my_array<int, n_2> data_9(arr_0);
      |                          ^
note: ‘int n_2’ is not const
  166 |         int n_2 = 5;
      |             ^~~
```
## Template template parameter
```
template<template <typename> typename container, typename T>
class wrapper
{
private:
    container<T> m_container;
public:
    wrapper(const container<T>& o): m_container(o) {}
    void output()
    {
        for (auto m_c: m_container)
        {
            cout << m_c << " ";
        }
        cout << endl;
    }

};

vector<int> vec = {0, 1, 2, 3, 4, 5};
wrapper<vector, int> data_12(vec);
data_12.output();
```
```
0 1 2 3 4 5
```