#include <bits/stdc++.h>

using namespace std;

// template<class T>
template<typename T>
void my_swap(T& a, T& b)
{
	T temp = a;
	a = b;
	b = temp;
}

// specialize template function
template<>
void my_swap(double& a, double& b)
{
	cout << "specialize template function" << endl;
	double temp = a;
	a = b;
	b = temp;
}

// Explicit Instantiation
template void my_swap<int>(int& a, int& b);

template<class T1, class T2>
T1 my_max(T1& a, T2& b)
{
	cout << "use template function" << endl;
	return (a > b) ? a : b;
}

int my_max(int &a, int& b)
{
	cout << "use overload function" << endl;
	return (a > b) ? a : b;
}

int main()
{
	int a = 5;
	int b = 6;
	short c = 7;
	printf("a: %d, b: %d\n", a, b);
	// Implicit Instantiation
	my_swap<int>(a, b);
	printf("a: %d, b: %d\n", a, b);
	my_max(a, b);
	my_max<int, int>(a, b);
	my_max(a, c);
}