#include <bits/stdc++.h>

using namespace std;

union my_union
{
	long data1;
	char data2[6];
	struct
	{
		char data3_1;
		char data3_1;
		short data3_2;
	} data3;
};

int main()
{
	// max size of the data1, data2, data3
	printf("size of my_union: %ld", sizeof(my_union));

	my_union union_1;
	union_1.data1 = 0xFFFF;
	union_1.data3 = {'a', 'b', 0xFF};
}