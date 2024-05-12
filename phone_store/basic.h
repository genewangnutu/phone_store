#include<iostream>
#include<string>
#include<utility>
#include<unordered_map>
#include<fstream>
using namespace std;

class item {
public:
	item() {}
	~item() {}

	virtual void set_id(int) = 0;

	virtual void set_name(string) = 0;

	virtual void add_quantity(int) = 0;

	virtual void set_description(string) = 0;

	virtual int get_id() = 0;

	virtual int get_quantity() = 0;

	virtual string get_name() = 0;

	virtual string get_description() = 0;
};

class basic_menu {
public:

	basic_menu() {}
	~basic_menu() {}

	virtual void run_menu() = 0;

	virtual void back() = 0;
};
