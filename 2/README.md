# Macro
## define and undefine
```
#define FULL_ARRAY
#undef FULL_ARRAY

#ifdef FULL_ARRAY
    #define MAX_SIZE 100
#else
    #define MAX_SIZE 50
#endif

MAX_SIZE = 50
```
## replace (Use inline as an alternative solution)
```
#define MUL(a, b) a * b

MUL(3, 2)     // 6
MUL(3, 2 + 1) // (3 * 2) + 1 = 7

#define MUL(a, b) (a) * (b)

MUL(3, 2)     // 6
MUL(3, 2 + 1) // (3 * (2 + 1)) = 9

inline int MUL(int a, int b) {return a * b;}

MUL(3, 2)     // 6
MUL(3, 2 + 1) // (3 * (2 + 1)) = 9
```
## stringification operator
`#` operator converts a macro parameter into a string representation
```
#define PRINT(a) cout << #a << " = " << (a) << endl

int a = 5;
PRINT(a * 3 + 6); // a * 3 + 6 = 21
```
## token pasting operator
`##` operatro combine two tokens into one token
```
#define MEMBER(type, a) type m_##a

struct my_struct
{
    MEMBER(int, a);
    MEMBER(char, b);
};

// same as
struct my_struct
{
    int m_a;
    char m_b;
};
```
```
#define PROPERTY(type, member) \
private: \
	type m_##member; \
public: \
	type get_##member() {return m_##member;} \
	void set_##member(type m) {m_##member = m;}

class my_class
{
	PROPERTY(int, a);
	PROPERTY(string, b);
};

// same as
class my_class
{
private:
    int m_a;
pubilc:
    int get_a() {return m_a;}
    void set_a(int m) {m_a = m;}
private:
    string m_b;
public:
    string get_b() {return m_b;}
    void set_b(string m) {m_b = m;}
}
```
## special macro
|macro|data type|explanation|
|:-:|:-:|:-:|
|`__LINE__`|int|code line|
|`__FILE__`|string|file name|
|`__DATE__`|string|compile date|
|`__TIME__`|string|compile time|
```cpp=49
cout << __LINE__ << endl;
cout << __FILE__ << endl;
cout << __DATE__ << endl;
cout << __TIME__ << endl;
```
```
49
macro.cpp
Apr 18 2025
16:25:11
```