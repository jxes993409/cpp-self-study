#include <bits/stdc++.h>

using namespace std;

int sum(int a, int b, int c)
{
	cout << "a: " << a << ", " << "b: " << b << ", " << "c: " << c;
	return a + b + c;
}

int main()
{
	function<int()> bind_fn_0 = bind(sum, 1, 2, 3);
	int result_0 = bind_fn_0();
	cout << ", result_0: " << result_0 << endl;

	function<int(int)> bind_fn_1 = bind(sum, 1, placeholders::_1, 3);
	int result_1 = bind_fn_1(5);
	cout << ", result_1: " << result_1 << endl;

	int n_2 = 7;
	function<int()> bind_fn_2 = bind(sum, 1, n_2, 3);
	n_2 = 9;
	int result_2 = bind_fn_2();
	cout << ", result_2: " << result_2 << endl;

	int n_3 = 7;
	function<int()> bind_fn_3 = bind(sum, 1, cref(n_3), 3);
	n_3 = 9;
	int result_3 = bind_fn_3();
	cout << ", result_3: " << result_3 << endl;
}