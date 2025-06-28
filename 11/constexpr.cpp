#include <bits/stdc++.h>

using namespace std;

class Complex
{
public:
	constexpr Complex(double r = 0, double i = 0): _r(r), _i(i) {}
	constexpr double get_r() const
	{
		return _r;
	}
	constexpr double get_i() const
	{
		return _i;
	}
	constexpr void set_r(double r)
	{
		_r = r;
	}
	constexpr void set_i(double i)
	{
		_i = i;
	}
private:
	double _r;
	double _i;
};

constexpr Complex multi(const Complex& a, const Complex& b)
{
	Complex res;
	res.set_r(
		a.get_r() * b.get_r() -
		a.get_i() * b.get_i()
	);
	res.set_i(
		a.get_r() * b.get_r() +
		a.get_i() * b.get_i()
	);

	return res;
}

int main()
{
	constexpr Complex p1(1.5, 2.3);
	constexpr Complex p2(2.6, 3.5);

	constexpr Complex p3 = multi(p1, p2);

	return 0;
}