# Struct
## create struct
```
struct Student
{
    string name;
    string id;
    short gender;
};
```
## construct struct
```
struct Student student_0 = {"Tom", "000", 0};
Student student_1 = {"Tom", "000", 0};

// 建構 Student，並將變數初始化為 0
Student student_2 = {};

// 建構 Student 的指標
Student* student_3 = new Student{"Tom", "000", 0};
```

`.`的優先級比`*`還高
```
(*student_3).name (v)
*student_3.name   (x)
```

## 指定每個資料的 bit 大小
```
// 所有變數型態都要相同
struct Input_data
{
    unsigned int ready: 1;
    unsigned int valid: 1;
    unsigned int data1: 4;
    unsigned int data2: 4;
};

Input_data x = {0, 1, 14, 14};
```

# Union
## create union
```
union my_union
{
    long data1;
    char data2[6];
    struct data3
    {
        char data3_1;
        char data3_1;
        short data3_2;
    };
};
```
## construct union
Union 中的資料共用相同的記憶體空間，因此 `union_1.data3 = {'a', 'b', 0xFF}` 會覆寫 `union_1.data1 = 0xFFFF`
```
my_union union_1;
union_1.data1 = 0xFFFF;
union_1.data3 = {'a', 'b', 0xFF};
```

# Enum
## create enum class (avoid conflict)
使用 `enum class` 取代 `enum`
```
enum class color_type_1
{
    red,
    blue,
    yellow,
    green
};

enum class color_type_2
{
    red,
    black,
    white,
    green
};
```
```
error: ‘red’ conflicts with a previous declaration
   15 |     red,
      |     ^~~
ote: previous declaration ‘color_type_1 red’
    7 |     red,
      |     ^~~
error: ‘green’ conflicts with a previous declaration
   18 |     green
      |     ^~~~~
note: previous declaration ‘color_type_1 green’
   10 |     green
      |     ^~~~~
```
## construct enum class
```
color_type_1 color;
color = color_type_1::red;
```