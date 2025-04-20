#include <bits/stdc++.h>

using namespace std;

class linear_line
{
private:
	float a_;
	float b_;
public:
	linear_line(float a, float b): a_(a), b_(b) {}
	~linear_line()
	{
		cout << "~linear_line()" << endl;
	}
	float output_y(float x)
	{
		return a_ * x + b_;
	}
};

struct package
{
	int m_id;
	char data[1000];
	package(int id): m_id(id) {}
};

struct compare
{
	bool operator()(const package& a, const package& b)
	{
		return a.m_id > b.m_id;
	}
	bool operator()(const unique_ptr<package>& a, const unique_ptr<package>& b)
	{
		return a->m_id > b->m_id;
	}
	bool operator()(const package* a, const package* b)
	{
		return a->m_id > b->m_id;
	}
};

int main()
{
	// unique_ptr<linear_line> u_ptr_0(new linear_line(2.0, 3.0));
	// unique_ptr<linear_line> u_ptr_1 = u_ptr_0;

	unique_ptr<linear_line> u_ptr_0(new linear_line(2.0, 3.0));
	unique_ptr<linear_line> u_ptr_1 = make_unique<linear_line>(3.0, 4.0);
	cout << u_ptr_0->output_y(5.0) << endl;
	cout << u_ptr_1->output_y(5.0) << endl;

	unique_ptr<linear_line> u_ptr_2(new linear_line(2.0, 3.0));
	unique_ptr<linear_line> u_ptr_3(new linear_line(2.0, 3.0));
	unique_ptr<linear_line> u_ptr_4(new linear_line(2.0, 3.0));
	// std::move
	u_ptr_2 = move(u_ptr_0);
	// point to nullptr
	u_ptr_3 = nullptr;
	// unique_ptr.reset, will delete object first and create new object
	u_ptr_4.reset(new linear_line(2.0, 3.0));

	vector<int> vec_id;
	for (int i = 0; i < 10000; i++)
	{
		vec_id.emplace_back(rand() % 100000);
	}

	vector<package> vec_packages;
	for (int i = 0; i < 10000; i++)
	{
		vec_packages.emplace_back(package(vec_id[i]));
	}

	auto start_0 = chrono::high_resolution_clock::now();

	// sort vector
	sort(vec_packages.begin(), vec_packages.end(), compare());

	auto end_0 = chrono::high_resolution_clock::now();
	chrono::microseconds elapsed_0 = chrono::duration_cast<chrono::microseconds>(end_0 - start_0);
	cout << elapsed_0.count() << " microseconds" << endl;

	vector<unique_ptr<package>> vec_u_ptr_packages;
	for (int i = 0; i < 10000; i++)
	{
		vec_u_ptr_packages.emplace_back(unique_ptr<package>(new package(vec_id[i])));
	}

	auto start_1 = chrono::high_resolution_clock::now();

	// sort vector
	sort(vec_u_ptr_packages.begin(), vec_u_ptr_packages.end(), compare());

	auto end_1 = chrono::high_resolution_clock::now();
	chrono::microseconds elapsed_1 = chrono::duration_cast<chrono::microseconds>(end_1 - start_1);
	cout << elapsed_1.count() << " microseconds" << endl;

	vector<package*> vec_ptr_packages;
	for (int i = 0; i < 10000; i++)
	{
		vec_ptr_packages.emplace_back(new package(vec_id[i]));
	}

	auto start_2 = chrono::high_resolution_clock::now();

	// sort vector
	sort(vec_ptr_packages.begin(), vec_ptr_packages.end(), compare());

	auto end_2 = chrono::high_resolution_clock::now();
	chrono::microseconds elapsed_2 = chrono::duration_cast<chrono::microseconds>(end_2 - start_2);
	cout << elapsed_2.count() << " microseconds" << endl;

	for (int i = 0; i < 10000; i++)
	{
		delete vec_ptr_packages[i];
		vec_ptr_packages[i] = nullptr;
	}
}