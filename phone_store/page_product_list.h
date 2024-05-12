#ifndef BASIC_MENU_H_
#define BASIC_MENU_H_
#include"basic_menu.h"
#endif

#ifndef DATA_BASE_H_
#define DATA_BASE_H_
#include"data_base.h"
#endif

class page_product_list : public basic_menu {
private:
	bool menu_lock = true;
	bool show_spec_lock = true;
	bool show_spec_lock2 = true;
	bool show_add_cart_lock = true;

public:
	data_base *dbs;
	cart *crt;

public:
	page_product_list(data_base *p_dbs, cart *p_crt) { dbs = p_dbs; crt = p_crt; }
	~page_product_list() {}

	int run_menu();
	void back();
	void UI_product_list();
	void UI_spec();
	void UI_spec_by_ID_Name(shared_ptr<const phone> ph, int mode);
	void UI_add_cart();
	void UI_cart_list();
	void UI_cart_add();
	void clear_cin();
};
