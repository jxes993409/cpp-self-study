#include <bits/stdc++.h>

using namespace std;

#define FULL_ARRAY
// #undef FULL_ARRAY

#ifdef FULL_ARRAY
	#define MAX_SIZE 100
#else
	#define MAX_SIZE 50
#endif

#define MUL(a, b) a * b
// #define MUL(a, b) (a) * (b)
// inline int MUL(int a, int b) {return a * b;}

#define PRINT(a) cout << #a << " = " << (a) << endl

#define MEMBER(type, a) type m_##a

struct my_struct
{
	MEMBER(int, a);
	MEMBER(char, b);
};

#define PROPERTY(type, member) \
private: \
	type m_##member; \
public: \
	type get_##member() {return m_##member;} \
	void set_##member(type m) {m_##member = m;}

class my_class
{
	PROPERTY(int, a);
	PROPERTY(string, b);
};

int main()
{
	cout << MUL(3, 2) << endl;     // 6
	cout << MUL(3, 2 + 1) << endl; // (3 * 2) + 1 = 7

	int a = 5;
	PRINT(a * 3 + 6);

	cout << __LINE__ << endl;
	cout << __FILE__ << endl;
	cout << __DATE__ << endl;
	cout << __TIME__ << endl;
}