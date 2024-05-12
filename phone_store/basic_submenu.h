#include<iostream>
#include<string>
using namespace std;

class basic_submenu {
public:

	basic_submenu() {}
	~basic_submenu() {}

	virtual void run_menu() = 0;

	virtual void back() = 0;
};
