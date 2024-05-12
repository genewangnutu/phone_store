#include "view_manager.h"

menu::menu(data_base *p_dbs, cart *p_crt) {
	dbs = p_dbs;
	crt = p_crt;
	page_main = new page_main_menu(p_dbs, p_crt);
	page_p_list = new page_product_list(p_dbs, p_crt);
	page_stocks = new page_stock(p_dbs, p_crt);
}

menu::~menu() {
	
	if (page_main) {
		delete page_main;
		page_main = NULL;
	}

	if (page_p_list) {
		delete page_p_list;
		page_p_list = NULL;
	}

	if (page_stocks) {
		delete page_stocks;
		page_stocks = NULL;
	}
}

int menu::run_menu() {
	
	while (menu_lock) {
		system("cls");

		selector = page_main->run_menu();
		
		if (selector == 1) {
			//1_Product List
			page_p_list->run_menu();
		}
		else if (selector == 2) {
			//2_Stock
			page_stocks->run_menu();
		}
		else if (selector == 3) {
			//3_Exit
			back();
			menu_lock = false;
		}
	}

	return 0;
}

void menu::back() {

}
