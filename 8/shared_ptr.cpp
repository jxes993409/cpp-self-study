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

class base
{
public:
	virtual ~base() {}
};

class derive:public base
{

};

class person
{
public:
	person(const string& name): _name(name)
	{
		cout << _name << " person()" << endl;
	}
	~person()
	{
		cout << _name << " ~person()" << endl;
	}
	void set_partner(const shared_ptr<person>& other)
	{
		_partner = other;
	}
private:
	string _name;
	weak_ptr<person> _partner;
};

int main()
{
	shared_ptr<linear_line> s_ptr_0(new linear_line(2.0, 3.0));
	shared_ptr<linear_line> s_ptr_1 = s_ptr_0;
	shared_ptr<linear_line> s_ptr_2(s_ptr_0);

	cout << s_ptr_0.use_count() << endl;
	cout << s_ptr_0.unique() << endl;

	shared_ptr<base> s_ptr_3(new derive());
	shared_ptr<derive> s_ptr_4 = dynamic_pointer_cast<derive>(s_ptr_3);
	shared_ptr<base> s_ptr_5 = static_pointer_cast<base>(s_ptr_4);

	cout << s_ptr_3.use_count() << endl;

	vector<shared_ptr<person>> vec_person;
	vec_person.emplace_back(shared_ptr<person>(new person("ABC")));
	vec_person.emplace_back(shared_ptr<person>(new person("DEF")));
	vec_person.emplace_back(shared_ptr<person>(new person("GHI")));

	vec_person[0]->set_partner(vec_person[1]);
	vec_person[1]->set_partner(vec_person[2]);
	vec_person[2]->set_partner(vec_person[0]);

	weak_ptr<base> w_ptr_0;
	{
		shared_ptr<base> s_ptr_6(new base());
		shared_ptr<base> s_ptr_7 = s_ptr_6;
		w_ptr_0 = s_ptr_6;
		shared_ptr<base> s_ptr_8 = w_ptr_0.lock();

		cout << "in scope: " << s_ptr_8 << endl;
	}
	shared_ptr<base> s_ptr_8 = w_ptr_0.lock();
	cout << "out scope: " << s_ptr_8 << endl;
}