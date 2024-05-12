#include<iostream>
#include<thread>
#include"view_manager.h"

using namespace std;

int main(void) {
	data_base bds;
	cart crt;
	//Init the database.
	thread data_init(&data_base::init, &bds);
	data_init.join();

	//Run menu UI.
	menu *mu = new menu(&bds, &crt);
	thread tt(&menu::run_menu, mu);
	tt.join();

	if (mu) {
		delete mu;
		mu = NULL;
	}

	//Update database before exit.
	thread data_update(&data_base::update, &bds);
	data_update.join();

	system("pause");
	return 0;
}