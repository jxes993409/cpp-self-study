# Type Casting
## Implicit casting
### Implicit casting of data type
Be careful about the precision differences between `type A` and `type B`, may cause overflow
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
Using a `conversion constructor`, even if there is no derived relationship between two classes, it is still possible to cast an object from class A to class B
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
`copy constructor` is a special case of `conversion constructor`
```
class class_c
{
public:
    class_c(const class_c& cls_c) {}
};
```

## Explicit casting
### Dynamic cast
`dynamic_cast` is often used for downcasting in a base class to derived class hierarchy

When compiling, if a base class is cast to a derived class, the base class must be a polymorphic class

When executing, the program checks whether downcasting is possible. If not, it throws a `std::bad_cast exception` for references and `returns nullptr` for pointers
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
`static_cast` is often used for downcasting and upcasting, and only checks the validity of the cast at compile time
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
`reinterpret cast` can convert a pointer to any other pointer type and can also cast an unsigned long to a pointer
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
`const_cast` can convert data to a constant type or remove its constant qualifier
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
Use `const_cast`
```
print_str(const_cast<char*>(str));
```
```
string: Hello World!
```
However, even if the constant qualifier is removed from the data, it still cannot be modified
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