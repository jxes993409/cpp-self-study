# Operator Overload
## operator <<
```
ostream& operator<<(ostream& o, vector<int>& numbers)
{
    o << "output: ";
    for (int number: numbers)
    {
        o << number << " ";
    }
    return o;
}

vector<int> numbers{2, 4, 6, 8, 10};
cout << numbers << endl;
// 與下方相同
operator<<(cout, numbers) << endl;
```
```
output: 2 4 6 8 10
```

## operator +, -, *, /
```
class my_complex
{
private:
    float r;
    float i;
public:
    my_complex(float real, float imaginary): r(real), i(imaginary) {};
    my_complex operator+(const my_complex& other)
    {
        return my_complex(this->r + other.r, this->i + other.i);
    }
    my_complex operator+(float r)
    {
        return my_complex(this->r + r, this->i);
    }
    friend my_complex operator+(float r, my_complex& cplex)
    {
        return cplex + r;
    }
    friend ostream& operator<<(ostream& o, my_complex& cplex)
    {
        o << "real: " << cplex.r << endl;
        o << "imaginary: " << cplex.i << endl;

        return o;
    }
};

my_complex data_0(5.0, 6.0);
my_complex data_1(0.3, 0.2);
my_complex data_2 = data_0 + data_1;
// same as
my_complex data_2 = data_0.operator+(data_1);

data_2 = data_2 + 1.5;
// same as
// data_2 = data_2.operator+(1.5);

// illegal, need frinend function
data_2 = 1.5 + data_2;

cout << data_2;
```
```
real: 5.3
imaginary: 6.2
```

## operator ++
`++num` 與 `num++` 不同
* `++num` 中的 function 直接將物件 `num + 1` 後回傳 `this` 即可
* `num++` 需要先創建一個原本的物件 `temp` 保留原本的值，並呼叫 `++num` 的 function 將 `num + 1` 後，再回傳 `++num` 前的物件，即 `temp`

```
class my_int
{
public:
    int num;
public:
    my_int(): num(0) {}
    // ++num;
    my_int& operator++()
    {
        num++;
        cout << "++num" <<endl;
        return *this;
    }
    // num++;
    my_int operator++(int)
    {
        my_int temp = *this;
        operator++();
        cout << "num++" <<endl;
        return temp;
    }
    void output()
    {
        cout << num << endl;
    }
};

my_int data_3;
(++data_3).output();
(data_3++).output();
```
```
++num
1
++num
num++
1
```
## operator []
```
class my_array
{
private:
    vector<int> numbers;
public:
    my_array(vector<int> vec): numbers(vec) {}
    int operator[](int i)
    {
        int size = numbers.size();
        assert(i < size && i > -size);

        if (i < 0)
        {
            return numbers[size + i];
        }
        else
        {
            return numbers[i];
        }
    }
};

my_array data_4(numbers);

cout << data_4[-1] << endl;
```
```
10
```
## operator ()
```
struct linear_function
{
    float a;
    float b;
    float operator()(double x)
    {
        return a * x + b;
    }
};

linear_function data_5{2.0, 5.0};

cout << data_5(6.0) << endl;
```
```
17
```

## operator ->
```
class local_ptr
{
private:
    linear_function* m_ptr;
public:
    local_ptr(linear_function* p): m_ptr(p) {}
    ~local_ptr()
    {
        if (m_ptr != nullptr)
        {
            delete m_ptr;
            m_ptr = nullptr;
        }
    }
    linear_function* operator->() {return m_ptr;}
    // 刪除 ptr_1 = ptr_2 的操作，避免指向同個地址
    local_ptr(const local_ptr&) = delete;
    // 刪除 ptr_1(ptr_2) 的操作，避免指向同個地址
    local_ptr& operator=(const local_ptr&) = delete;
};

local_ptr ptr(new linear_function{2.0, 5.0});
ptr->a = 6.0;
// same as
// ptr.m_ptr->a = 6.0;
```