#ifndef BASIC_MENU_H_
#define BASIC_MENU_H_
#include"basic_menu.h"
#endif

#ifndef DATA_BASE_H_
#define DATA_BASE_H_
#include"data_base.h"
#endif

class page_stock : public basic_menu {
private:
	bool menu_lock = true;
	bool show_stock_lock = true;
	bool show_stock_exist_lock = true;
public:
	data_base *dbs;
	cart *crt;

public:
	page_stock(data_base *p_dbs, cart *p_crt) { dbs = p_dbs; crt = p_crt; }
	~page_stock(){}

	int run_menu();
	void back();
	void UI_product_list();
	void UI_stock_exist_item(int id);
	void UI_stock_new_item();
	void clear_cin();
};
