#include <bits/stdc++.h>

using namespace std;

template<typename T>
class my_vector
{
private:
	T m_vec[3];
public:
	my_vector(T m_0, T m_1, T m_2)
	{
		m_vec[0] = m_0;
		m_vec[1] = m_1;
		m_vec[2] = m_2;
	}
	void output()
	{
		for (int i = 0; i < 3; i++)
		{
			cout << m_vec[i] << " ";
		}
		cout << endl;
	}
};

// specialize template class
template<>
class my_vector<string>
{
private:
	string m_vec[4];
public:
	my_vector(string m_0, string m_1, string m_2, string m_3)
	{
		m_vec[0] = m_0;
		m_vec[1] = m_1;
		m_vec[2] = m_2;
		m_vec[3] = m_3;
	}
};

// partially specialized template class
template<typename T1, typename T2>
class my_class
{
private:
	T1 first;
	T2 second;
public:
	my_class(T1 a, T2 b): first(a), second(b) {}
};

template<typename T2>
class my_class<int, T2>
{
private:
	int first;
	T2 second;
public:
	my_class(int a, T2 b): first(a), second(b) {}
	void output()
	{
		cout << "partially specialized template class my_class<int, T2>" << endl;
	}
};

template<typename T1>
class my_class<T1, float>
{
private:
	T1 first;
	float second;
public:
	my_class(T1 a, float b): first(a), second(b) {}
	void output()
	{
		cout << "partially specialized template class my_class<T1, float>" << endl;
	}
};

template<>
class my_class<int, float>
{
private:
	int first;
	float second;
public:
	my_class(int a, float b): first(a), second(b) {}
	void output()
	{
		cout << "partially specialized template class my_class<int, float>" << endl;
	}
};

// specialize template class for pointer
template<typename T1, typename T2>
class my_class<T1*, T2*>
{
private:
	T1* first;
	T2* second;
public:
	my_class(T1* a, T2* b): first(a), second(b) {}
	void output()
	{
		cout << "specialized template class for pointer my_class<T1*, T2*>" << endl;
	}
};

// none-type parameter
template<typename T = int, int N = 5>
class my_array
{
private:
	T m_arr[N];
public:
	my_array(T arr[N])
	{
		for (int i = 0; i < N; i++)
		{
			m_arr[i] = arr[i];
		}
	}
	void output()
	{
		for (int i = 0; i < N; i++)
		{
			cout << m_arr[i] << " ";
		}
		cout << endl;
	}
};

template<template <typename T> typename container, typename T>
class wrapper
{
private:
	container<T> m_container;
public:
	wrapper(const container<T>& o): m_container(o) {}
	void output()
	{
		for (auto m_c: m_container)
		{
			cout << m_c << " ";
		}
		cout << endl;
	}

};

int main()
{
	my_vector<int> data_0(0, 1, 2);
	my_vector<char> data_1('a', 'b', 'c');
	my_vector<string> data_2("abc", "def", "ghi", "jkl");

	// data_2.output();

	my_class<int, char> data_3(0, 'a');
	my_class<string, float> data_4("abc", 0.0);
	
	data_3.output();
	data_4.output();

	my_class<int, float> data_5(0, 0.0);

	data_5.output();

	int* ptr_1 = new int;
	int* ptr_2 = new int;
	my_class<int*, int*> data_6(ptr_1, ptr_2);

	data_6.output();
	
	delete ptr_1;
	ptr_1 = nullptr;
	delete ptr_2;
	ptr_2 = nullptr;
	
	int arr_0[5] = {0, 1, 2, 3, 4};
	double arr_1[5] = {0.0, 1.0, 2.0, 3.0, 4.0};
	
	const int n_1 = 5;
	int n_2 = 5;
	
	my_array<int, 5> data_7(arr_0);
	// n can be const type
	my_array<int, n_1> data_8(arr_0);
	// n_2 must be constant type
	// my_array<int, n_2> data_9(arr_0);
	
	// int, 5
	my_array<> data_10(arr_0);
	// double, 5
	my_array<double> data_11(arr_1);
	
	data_7.output();

	vector<int> vec = {0, 1, 2, 3, 4, 5};
	wrapper<vector, int> data_12(vec);
	data_12.output();
}