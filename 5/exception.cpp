#include <bits/stdc++.h>

using namespace std;

struct my_exception_struct
{
	string message;
	unsigned int error_code;
};

string my_exception_function()
{
	return "this is an exception function";
}

int main()
{
	try
	{
		throw "this is an exception";
	}
	catch(const char* e)
	{
		cout << e << endl;
	}

	try
	{
		throw 0;
	}
	catch(int e)
	{
		cout << e << endl;
	}
	
	try
	{
		throw my_exception_struct{"this is an exception_struct", 20};
	}
	catch(my_exception_struct& e)
	{
		cout << e.message << ", " << e.error_code << endl;
	}
	
	try
	{
		throw my_exception_function;
	}
	catch(string(*e)())
	{
		cout << e() << endl;
	}
	catch(...)
	{
		throw;
	}
}
