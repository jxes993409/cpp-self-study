# Unique pointer
`unique_ptr` class template
```
template<class T, class Deleter = std::default_delete<T>>
class unique_ptr;
```
`unique_ptr` cannot point two pointer to same object
```
class linear_line
{
private:
    float a_;
    float b_;
public:
    linear_line(float a, float b): a_(a), b_(b) {}
    ~linear_line()
    {
        cout << "~linear_line()" << endl;
    }
    float output_y(float x)
    {
        return a_ * x + b_;
    }
};

unique_ptr<linear_line> u_ptr_0(new linear_line(2.0, 3.0));
unique_ptr<linear_line> u_ptr_1 = u_ptr_0;
```
```
error: use of deleted function ‘std::unique_ptr<_Tp, _Dp>::unique_ptr(const std::unique_ptr<_Tp, _Dp>&) [with _Tp = linear_line; _Dp = std::default_delete<linear_line>]’
   25 |         unique_ptr<linear_line> u_ptr_1 = u_ptr_0;
      |                                           ^~~~~~~
```
Create `unique_ptr`
```
unique_ptr<linear_line> u_ptr_0(new linear_line(2.0, 3.0));
unique_ptr<linear_line> u_ptr_1 = make_unique<linear_line>(3.0, 4.0);
```
Like a normal pointer, use `operator->` to access class functions or members
```
cout << u_ptr_0->output_y(5.0) << endl;
cout << u_ptr_1->output_y(5.0) << endl;
```
```
13
19
```
`unique_ptr` manages memory automatically
```
~linear_line()
~linear_line()
```
These operations will delete the objects they manage

1. `std::move`
2. point to `nullptr`
3. reset `unique_ptr`
```
unique_ptr<linear_line> u_ptr_2(new linear_line(2.0, 3.0));
unique_ptr<linear_line> u_ptr_3(new linear_line(2.0, 3.0));
unique_ptr<linear_line> u_ptr_4(new linear_line(2.0, 3.0));
// std::move
u_ptr_2 = move(u_ptr_0);
// point to nullptr
u_ptr_3 = nullptr;
// unique_ptr.reset, will delete object first and create new object
u_ptr_4.reset(new linear_line(2.0, 3.0));
```
For example, sorting normal objects involves copy overhead, but pointers only need to copy addresses, which reduces the overhead

With a minor performance trade-off, `unique_ptr` automatically manages memory, making the program safer
```
struct package
{
    int m_id;
    char data[1000];
    package(int id): m_id(id) {}
};

struct compare
{
    bool operator()(const package& a, const package& b)
    {
        return a.m_id > b.m_id;
    }
    bool operator()(const unique_ptr<package>& a, const unique_ptr<package>& b)
    {
        return a->m_id > b->m_id;
    }
    bool operator()(const package* a, const package* b)
    {
        return a->m_id > b->m_id;
    }
};

vector<int> vec_id;
for (int i = 0; i < 10000; i++)
{
    vec_id.emplace_back(rand() % 100000);
}
```
## normal method
```
vector<package> vec_packages;
for (int i = 0; i < 10000; i++)
{
    vec_packages.emplace_back(package(vec_id[i]));
}

// sort vector
sort(vec_packages.begin(), vec_packages.end(), compare());
```
## unique_ptr
```
vector<unique_ptr<package>> vec_u_ptr_packages;
for (int i = 0; i < 10000; i++)
{
    vec_u_ptr_packages.emplace_back(unique_ptr<package>(new package(vec_id[i])));
}

// sort vector
sort(vec_u_ptr_packages.begin(), vec_u_ptr_packages.end(), compare());
```
## normal pointer
```
vector<package*> vec_ptr_packages;
for (int i = 0; i < 10000; i++)
{
    vec_ptr_packages.emplace_back(new package(vec_id[i]));
}

// sort vector
sort(vec_ptr_packages.begin(), vec_ptr_packages.end(), compare());
```
## Execution time table (with -O2 argument)
||normal method (µs)|unique_ptr (µs)|normal pointer (µs)|
|:-:|:-:|:-:|:-:|
|1|5465|573|620|
|2|5280|643|594|
|3|5580|667|586|
|4|5409|584|596|
|5|5009|604|612|
# Shared pointer
Compared to `unique_ptr`, `shared_ptr` can point to same object

`use_count()` can be used to determine how many pointers point to the same object

`unique()` can be used to determine which pointers is the only one pointing to the object
```
shared_ptr<linear_line> s_ptr_0(new linear_line(2.0, 3.0));
shared_ptr<linear_line> s_ptr_1 = s_ptr_0;
shared_ptr<linear_line> s_ptr_2(s_ptr_0);

cout << s_ptr_0.use_count() << endl;
cout << s_ptr_0.unique() << endl;
```
```
3
0
```
`shared_ptr` support `dynamic_pointer_cast`, `static_pointer_cast` and `const_pointer_cast`
```
class base
{
public:
    virtual ~base() {}
};

class derive:public base
{

};

shared_ptr<base> s_ptr_3(new derive());
shared_ptr<derive> s_ptr_4 = dynamic_pointer_cast<derive>(s_ptr_3);
shared_ptr<base> s_ptr_5 = static_pointer_cast<base>(s_ptr_4);

cout << s_ptr_3.use_count() << endl;
```
```
3
```
When using `shared_ptr`, avoid circular references, as they can cause memory leaks

In this case, `person._partner.use_count()` cannot be zero

Hence, the object cannot be deleted
```
class person
{
public:
    person(const string& name): _name(name)
    {
        cout << _name << " person()" << endl;
    }
    ~person()
    {
        cout << _name << " ~person()" << endl;
    }
    void set_partner(const shared_ptr<person>& other)
    {
        _partner = other;
    }
private:
    string _name;
    shared_ptr<person> _partner;
};

vector<shared_ptr<person>> vec_person;
vec_person.emplace_back(shared_ptr<person>(new person("ABC")));
vec_person.emplace_back(shared_ptr<person>(new person("DEF")));
vec_person.emplace_back(shared_ptr<person>(new person("GHI")));

vec_person[0]->set_partner(vec_person[1]);
vec_person[1]->set_partner(vec_person[2]);
vec_person[2]->set_partner(vec_person[0]);
```
```
ABC person()
DEF person()
GHI person()
```
Replace `shared_ptr<person> _partner` with `weak_ptr<person> _partner`
```
ABC person()
DEF person()
GHI person()
ABC ~person()
DEF ~person()
GHI ~person()
```
1. access valid `shared_ptr`
2. Check if the object is valid.<br>If `weak_ptr.lock()` returns `nullptr`, it means the object pointed to by `weak_ptr` has been deleted
3. Avoid race condition<br>In multithreaded conditions, `weak_ptr.lock()` is an atomic operation that can prevent race conditions
```
weak_ptr<base> w_ptr_0;
{
    shared_ptr<base> s_ptr_6(new base());
    shared_ptr<base> s_ptr_7 = s_ptr_6;
    w_ptr_0 = s_ptr_6;
    shared_ptr<base> s_ptr_8 = w_ptr_0.lock();

    cout << "in scope: " << s_ptr_8 << endl;
}
shared_ptr<base> s_ptr_8 = w_ptr_0.lock();
cout << "out scope: " << s_ptr_8 << endl;
```
```
in scope: 0x55da7079e4e0
out scope: 0
```
1. Create shared_ptr (use_count +1)<br>![image_0](img/0.png)
2. Create weak_ptr (weak_count +1)<br>If use_count > 0, it means the object exists, and the `weak_ptr` can observe the object<br>![image_1](img/1.png)
3. Delete shared_ptr (use_count -1)<br>When leaving the scope, the `shared_ptr` is deleted<br>If `use_count = 0`, it means the object has been destructed<br>![image_2](img/2.png)
4. Delete weak_ptr (weak_count -1)<br>When leaving the scope, the `weak_ptr` and `control block` are deleted<br>![image_3](img/3.png)