#include <bits/stdc++.h>

using namespace std;

double add(double a, double b)
{
	return a + b;
}

struct linear_function
{
	double a_;
	double b_;
	double output_y(double x)
	{
		return a_ * x + b_;
	}
};

struct sub
{
	double operator()(double a, double b)
	{
		return a - b;
	}
};


int main()
{
	function<double(double, double)> func_0 = add;
	double result_0 = func_0(2.1, 3.2);
	cout << result_0 << endl;

	function<double(linear_function&, double)> func_1 = &linear_function::output_y;
	linear_function l{2.0, 3.5};
	double result_1 = func_1(l, 6);
	cout << result_1 << endl;

	function<double(linear_function&)> func_2 = &linear_function::a_;
	cout << func_2(l) << endl;

	unordered_map<char, function<double(double, double)>> my_map;
	// general function
	my_map['+'] = add;
	// struct function
	my_map['-'] = sub();
	// lambda expression function
	my_map['*'] = [](double a, double b) -> double {return a * b;};

	cout << my_map['+'](4.0, 2.0) << endl;
	cout << my_map['-'](4.0, 2.0) << endl;
	cout << my_map['*'](4.0, 2.0) << endl;
}