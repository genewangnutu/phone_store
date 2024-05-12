#ifndef BASIC_MENU_H_
#define BASIC_MENU_H_
#include"basic_menu.h"
#endif

#ifndef DATA_BASE_H_
#define DATA_BASE_H_
#include"data_base.h"
#endif

class page_main_menu : public basic_menu {
private:
	int selectior = 0;

public:
	data_base *dbs;
	cart *crt;

	page_main_menu(data_base *p_dbs, cart *p_crt) {
		dbs = p_dbs; 
		crt = p_crt; 
	}
	~page_main_menu() {}
	int run_menu();
	void back();
};

