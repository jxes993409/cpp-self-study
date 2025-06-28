#include <bits/stdc++.h>

using namespace std;

string f1()
{
	return "hello";
}

string& f2()
{
	static string str = "hello";
	return str;
}

string&& f3(string& s3)
{
	return move(s3);
}

decltype(auto) g1(int i)
// int g1(int)
{
	return i;
}

decltype(auto) g2(int i)
// int& g2(int)
{
	return (i);
}

decltype(auto) g3(int &i)
// int& g3(int&)
{
	return (i);
}

decltype(auto) g4(int i)
// int g4(int)
{
	return (i + 1);
}

int main()
{
	int x = 4;
	int& rx = x;
	decltype(rx) dx = x;
	auto ax = x;

	dx = 6;
	cout << "x: " << x << endl;
	ax = 8;
	cout << "x: " << x << endl;

	int y = 4;
	decltype((y)) dy = y;

	decltype(f1()) s1;              // string
	decltype(f2()) s2 = s1;         // string &
	decltype(f3(s1)) s3 = move(s1); // string &&

	decltype(s1 + "world") s4;            // string
	decltype(s1.append("world")) s5 = s1; // string&

	decltype(auto) s6 = s1 + "world";       // string
	decltype(auto) s7 = s1.append("world"); // string&
}