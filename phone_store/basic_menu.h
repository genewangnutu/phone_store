#include<iostream>
#include<cctype>
#include<string>
using namespace std;

class basic_menu {
public:

	basic_menu(){}
	~basic_menu(){}

	virtual int run_menu() = 0;

	virtual void back() = 0;
};
