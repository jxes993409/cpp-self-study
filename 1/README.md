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

// initialize all variable to 0
Student student_2 = {};

// construct by pointer
Student* student_3 = new Student{"Tom", "000", 0};
```

The priority `.` is higher than `*`.
```
(*student_3).name (v)
*student_3.name   (x)
```

## split data by bit
```
// data type should be same
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
Every instance use same memory space
`union_1.data3 = {'a', 'b', 0xFF}` will overwrite `union_1.data1 = 0xFFFF`
```
my_union union_1;
union_1.data1 = 0xFFFF;
union_1.data3 = {'a', 'b', 0xFF};
```

# Enum
## create enum class (avoid conflict)
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