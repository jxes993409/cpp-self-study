# Namespace
Using a namespace can help avoid conflicts with functions that have the same name in other files
```
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

using namespace space_0;
// same as int max_num = space_0::my_max(5, 6);
int max_num = my_max(5, 6);
```
```
namespace space_0 my_max
```
## Global space
```
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

using namespace space_0;
int max_num = ::my_max(5, 6);
```
```
namespace global space my_max
```
When variables have the same name, the namespace should be explicitly declared
```
int a = 1;
namespace space_2
{
    int a = 2;
    namespace space_3
    {
        int a = 3;
    }
}

cout << "::a = " << ::a << endl;
cout << "space_2::a = " << space_2::a << endl;
cout << "space_2::space_3::a = " << space_2::space_3::a << endl;
```
```
::a = 1
space_2::a = 2
space_2::space_3::a = 3
```

# Exception
## Try & Catch
`try` statement can be followed by multiple `catch` blocks

Among them, a more general catch block will have lower priority
```
try
{
    /* code */
}
catch (Type e)
{
    /* code */
}
```
```
// not recommended to use catch blocks that are unable to process the exceptions they catch
catch(...)
{

}
```
## Throw
The data type of `throw` can be of any type, but using a class derived from `exception` or inheriting from it is recommended.
### const char*
```
try
{
    throw "this is an exception";
}
catch(const char* e)
{
    cout << e << endl;
}
```
```
this is an exception
```
### int
```
try
{
    throw 0;
}
catch(int e)
{
    cout << e << endl;
}
```
```
0
```
### struct
```
struct my_exception_struct
{
    string message;
    unsigned int error_code;
};

try
{
    throw my_exception_struct{"this is an exception_struct", 20};
}
catch(my_exception_struct& e)
{
    cout << e.message << ", " << e.error_code << endl;
}
```
```
this is an exception_struct, 20
```
### function pointer
```
string my_exception_function()
{
    return "this is an exception function";
}

try
{
    throw my_exception_function;
}
catch(string(*e)())
{
    cout << e() << endl;
}
```
```
this is an exception function
```