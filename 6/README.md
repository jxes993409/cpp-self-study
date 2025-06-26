# Type Casting
## Implicit casting
### Implicit casting of data type
當隱式轉換時需要注意 `type A` 與 `type B` 之間的精度，避免造成溢位
```
double a = 3.5e39;
float b = a;
cout << "a: " << a << endl;
cout << "b: " << b << endl;
```
```
a: 3.5e+39
b: inf
```
### Implicit casting of class
```
class base_class
{
private:
    int m_a;
public:
    base_class() {}
};

class sub_class:public base_class
{
public:
    sub_class() {};
};

sub_class* p_sub = new sub_class();
base_class* p_base = p_sub;
```
### Conversion constructor
當使用 `conversion constructor` (轉換建構子) 時，即便兩個 class 之間沒有衍生的關係，還是能將 class A 轉換成 class B
```
class class_a {};

class class_b
{
public:
    class_b(const class_a& cls_a) {}
};

class_a cls_a;
class_b cls_b = cls_a;
```
`copy constructor` 是 `conversion constructor` 的特例
```
class class_c
{
public:
    class_c(const class_c& cls_c) {}
};
```

## Explicit casting
### Dynamic cast
`dynamic cast` (動態轉換) 通常用於 downcasting，從 base class (基類) 轉換到 derived class (衍生類)
* 當編譯時，如果想將 base class 轉換到 derived class，base class 必須是 polymorphism (多型)
* 當執行時，程式會確認能否 downcasting，如果不行，reference 會丟出 `std::bad_cast exception`，pointer 會回傳 `returns nullptr`
```
class base_class
{
private:
    int m_a;
public:
    virtual ~base_class() {}
};

class sub_class:public base_class
{
public:
    sub_class() {};
};

sub_class sub_obj;
```
#### return nullptr
```
sub_class* ptr = dynamic_cast<sub_class*>(&base_obj);
if (ptr == nullptr)
{
    cout << "down casting failed!" << endl;
}
```
```
dynamic_cast casting failed!
```
#### throw std::bad_cast exception
```
sub_class& ref = dynamic_cast<sub_class&>(base_obj);
```
```
terminate called after throwing an instance of 'std::bad_cast'
  what():  std::bad_cast
Aborted (core dumped)
```
#### Example of dynamic cast
```
base_class* base_obj = new sub_class;
sub_class* ptr = dynamic_cast<sub_class*>(base_obj);
sub_class& ref = dynamic_cast<sub_class&>(*base_obj);
```
### Static cast
`static_cast` 通常用在 downcasting 或 upcasting，並且只在編譯時確認轉換是否有效
```
base_class* base_ptr;
sub_class* sub_ptr;
sub_class sub_obj;
class_a a_obj;

base_ptr = static_cast<base_class*>(&sub_obj);
sub_ptr = static_cast<sub_class*>(&sub_obj);

base_ptr = static_cast<base_class*>(&a_obj);
sub_ptr = static_cast<sub_class*>(&a_obj);
```
```
error: invalid ‘static_cast’ from type ‘class_a*’ to type ‘base_class*’
   81 |     base_ptr = static_cast<base_class*>(&a_obj);
      |                ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
error: invalid ‘static_cast’ from type ‘class_a*’ to type ‘sub_class*’
   82 |     sub_ptr = static_cast<sub_class*>(&a_obj);
```
### Reinterpret cast
`reinterpret cast` 可以將 pointer 轉換成任何類型的 pointer，也可將 unsigned long 直接轉換成指標
```
base_class* base_ptr;
sub_class* sub_ptr;
class_a a_obj;

base_ptr = reinterpret_cast<base_class*>(&a_obj);
sub_ptr = reinterpret_cast<sub_class*>(&a_obj);

base_ptr = reinterpret_cast<base_class*>(0xFF);
long address = reinterpret_cast<long>(&a_obj);
```
### Const cast
`const_cast` 可以將資料轉換為常數型態，或移除 constant qualifier (常數限定符)
```
void print_str(char* str)
{
    cout << "string: " << str << endl;
}

const char* str = "Hello World!";
print_str(str);
```
```
error: invalid conversion from ‘const char*’ to ‘char*’ [-fpermissive]
  100 |         print_str(str);
      |                   ^~~
      |                   |
      |                   const char*
```
使用 `const_cast` 即可解決問題
```
print_str(const_cast<char*>(str));
```
```
string: Hello World!
```
常數資料即便移除 constant qualifier 後，仍然不能對內容進行修改
```
void print_str(char* str)
{
    str[0] = 'h';
    cout << "string: " << str << endl;
}

const char* str = "Hello World!";
print_str(const_cast<char*>(str));
```
```
Segmentation fault (core dumped)
```