#include <bits/stdc++.h>

using namespace std;

struct my_struct
{
	float weight;
	float calculate(float a, float b)
	{
		return weight * a + weight * b;
	}
	my_struct& operator+=(float a)
	{
		weight += a;
		return *this;
	}
	void print_weight()
	{
		cout << "weight: " << weight << endl;
	}
};

int main()
{
	my_struct data_0{2.0};

	function<float(my_struct&, float, float)> mem_fn_0 = mem_fn(&my_struct::calculate);
	float result_0 = mem_fn_0(data_0, 2.0, 3.0);
	cout << result_0 << endl;

	function<my_struct&(my_struct&, float)> mem_fn_1 = mem_fn(&my_struct::operator+=);
	my_struct data_1 = mem_fn_1(data_0, 2.0);
	data_1.print_weight();
}