#include <bits/stdc++.h>

using namespace std;

class base_class
{
private:
	int m_a;
public:
	base_class() {}
	virtual ~base_class() {}
};

class sub_class:public base_class
{
public:
	sub_class() {};
};

class class_a {};

class class_b
{
public:
	class_b(const class_a& cls_a) {}
};

class class_c
{
public:
	class_c(const class_c& cls_c) {}
};

void print_str(char* str)
{
	str[0] = 'h';
	cout << "string: " << str << endl;
}

int main()
{
	// implicit casting of data type
	double a = 3.5e39;
	float b = a;
	cout << "a: " << a << endl;
	cout << "b: " << b << endl;

	// implicit casting of class
	sub_class* p_sub = new sub_class();
	base_class* p_base = p_sub;

	class_a cls_a;
	class_b cls_b = cls_a;

	delete p_sub;
	p_sub = nullptr;
	p_base = nullptr;

	// explicit casting of data type
	double c = 6.0;
	float d = (float)c;
	// float d = float(c);

	// dynamic cast
	// base_class base_obj;
	// sub_class* ptr = dynamic_cast<sub_class*>(&base_obj);
	// if (ptr == nullptr)
	// {
	//     cout << "dynamic_cast casting failed!" << endl;
	// }
	// sub_class& ref = dynamic_cast<sub_class&>(base_obj);

	// base_class* base_obj = new sub_class;
	// sub_class* ptr = dynamic_cast<sub_class*>(base_obj);
	// sub_class& ref = dynamic_cast<sub_class&>(*base_obj);

	// static cast
	// base_class* base_ptr;
	// sub_class* sub_ptr;
	// sub_class sub_obj;
	// class_a a_obj;

	// base_ptr = static_cast<base_class*>(&sub_obj);
	// sub_ptr = static_cast<sub_class*>(&sub_obj);

	// base_ptr = static_cast<base_class*>(&a_obj);
	// sub_ptr = static_cast<sub_class*>(&a_obj);

	// reinterpret_cast
	// base_class* base_ptr;
	// sub_class* sub_ptr;
	// class_a a_obj;

	// base_ptr = reinterpret_cast<base_class*>(&a_obj);
	// sub_ptr = reinterpret_cast<sub_class*>(&a_obj);

	// base_ptr = reinterpret_cast<base_class*>(0xFF);
	// unsigned long long address = reinterpret_cast<unsigned long long>(&a_obj);

	// const cast
	// const char* str = "Hello World!";
	// print_str(const_cast<char*>(str));
}