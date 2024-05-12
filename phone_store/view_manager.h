#include"page_main_menu.h"
#include"page_product_list.h"
#include"page_stock.h"

#ifndef BASIC_MENU_H_
#define BASIC_MENU_H_
#include"basic_menu.h"
#endif

#ifndef DATA_BASE_H_
#define DATA_BASE_H_
#include"data_base.h"
#endif

class menu : public basic_menu{
private:
	bool menu_lock = true;
	int selector = 0;

public:
	page_main_menu *page_main = NULL;
	page_product_list *page_p_list = NULL;
	page_stock *page_stocks = NULL;
	data_base *dbs;
	cart *crt;

	menu(data_base *p_dbs, cart *p_crt);
	~menu();

	int run_menu();
	void back();
};
