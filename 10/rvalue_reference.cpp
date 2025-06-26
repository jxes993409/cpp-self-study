#include <bits/stdc++.h>

using namespace std;

void func1(int& a)
{
	cout << "lv ref" << endl;
}

void func1(int&& a)
{
	cout << "rv ref" << endl;
}

template<typename T>
void func2(T&& a)
{
	func1(forward<T>(a));
}

class CharBuffer
{
public:
	CharBuffer(size_t n_size): m_buff(new char[n_size]), m_size(n_size)
	{
		cout << "base constructor" << endl;
	}
	CharBuffer(const CharBuffer& other): m_buff(new char[other.m_size]), m_size(other.m_size)
	{
		cout << "copy constructor" << endl;
		memcpy(m_buff, other.m_buff, m_size);
	}
	CharBuffer& operator=(const CharBuffer& other)
	{
		if (this == &other)
		{
			return *this;
		}
		delete [] m_buff;
		m_size = other.m_size;
		m_buff = new char[m_size];

		memcpy(m_buff, other.m_buff, m_size);

		cout << "copy assignment operator" << endl;

		return *this;
	}
	CharBuffer(CharBuffer&& other): m_buff(other.m_buff), m_size(other.m_size)
	{
		other.m_buff = nullptr;
		other.m_size = 0;
		cout << "move constructor" << endl;
	}
	CharBuffer& operator=(CharBuffer&& other)
	{
		if (this == &other)
		{
			return *this;
		}

		delete [] m_buff;
		m_buff = other.m_buff;
		m_size = other.m_size;

		other.m_buff = nullptr;
		other.m_size = 0;

		cout << "move assignment operator" << endl;
		
		return *this;
	}
	~CharBuffer()
	{
		delete [] m_buff;
		m_buff = nullptr;
		cout << "destructor" << endl;
	}

	size_t get_size()
	{
		return m_size;
	}
private:
	char* m_buff;
	size_t m_size;
};

struct Array
{
	int data[100];
};

CharBuffer generate(size_t n)
{
	return CharBuffer(n);
}

CharBuffer generate_nv(size_t n)
{
	CharBuffer buf(n);
	cout << &buf << endl;
	return buf;
}

CharBuffer& assign(CharBuffer& src, CharBuffer& dst)
{
	dst = src;
	return dst;
}

CharBuffer& assign(CharBuffer&& src, CharBuffer& dst)
{
	dst = src;
	return dst;
}

int main()
{
	int a = 6;
	func1(a);
	func1(6);

	CharBuffer buf1{CharBuffer(100)};
	CharBuffer buf2 = generate(100);    // return value optimization (RVO)
	CharBuffer buf3 = generate_nv(100); // named return value optimization (NRVO)
	cout << &buf3 << endl;
	CharBuffer buf4 = move(buf1);

	unique_ptr<Array> ptr1 = make_unique<Array>();
	cout << ptr1.get() << endl;
	unique_ptr<Array> ptr2 = move(ptr1);
	cout << "--- after move ---" << endl;
	cout << ptr1.get() << endl;
	cout << ptr2.get() << endl;

	vector<CharBuffer> vec;
	vec.reserve(5);

	cout << "--- push back ---" << endl;
	vec.push_back(CharBuffer(100));
	cout << "--- push back ---" << endl;

	cout << "--- emplace back ---" << endl;
	vec.emplace_back(100);
	cout << "--- emplace back ---" << endl;

	assign(move(buf1), buf2);

	func2(4);
	func2(a);
}