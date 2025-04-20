#include <bits/stdc++.h>

using namespace std;

struct Student
{
	string name;
	string id;
	short gender;
};

// typedef
typedef struct _Student
{
	string name;
	string id;
	short gender;
} Studet;

struct Input_data
{
	unsigned int ready: 1;
	unsigned int valid: 1;
	unsigned int data1: 4;
	unsigned int data2: 4;
};

int main()
{
	struct Student student_0 = {"Tom", "000", 0};
	Student student_1 = {"Tom", "000", 0};
	// initialize all variable to 0
	Student student_2 = {};

	// construct by pointer
	Student* student_3 = new Student{"Tom", "000", 0};

	student_3->name;
	(*student_3).name;

	delete student_3;
	student_3 = nullptr;

	Input_data x = {0, 1, 14, 14};

	return 0;
}