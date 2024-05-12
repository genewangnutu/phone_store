#include"page_stock.h"

int page_stock::run_menu() {
	while (menu_lock) {

		system("cls");

		cout << "-----------------This is Product list----------------- \n\n";

		UI_product_list();

		cout << "1 [Stock by ID]" << " 2 [Stock new item]" << " 3 [Back]\n";
		int selectior;
		cin >> selectior;

		if (selectior == 1) {

			cout << "Please input the ID of product you want to stock:\n";
			int id;
			clear_cin();
			cin >> id;

			UI_stock_exist_item(id);
		}
		else if (selectior == 2) {
			UI_stock_new_item();
		}
		else if (selectior == 3) {
			back();
			menu_lock = false;
		}

	}

	menu_lock = true;

	return 0;
}

void page_stock::back() {

}

void page_stock::UI_product_list() {
	if (dbs) {
		shared_ptr<const phone>ph;
		printf("%3sID%16sName%12sQuantity\n", "", "", "");
		for (int i = 0; i < dbs->get_size(); i++) {
			ph = dbs->get_data_byIndex(i);
			if (ph) {
				printf("%d%20s%20d\n", ph->get_id(), ph->get_name().c_str(), ph->get_quantity());
			}
		}
	}
}

void page_stock::UI_stock_exist_item(int id) {
	while (!dbs->is_product_exist(id)) {
		cout << "Can't find the Product by ID, please input the correct ID:\n";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> id;
	}

	cout << "Please input the amounts you want to stock:\n";
	int amounts; 
	cin >> amounts;
	while (cin.fail()) {
		cout << "Invalid input. Please input correct amounts:\n";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> amounts;
	}

	dbs->update_exist_data(id, amounts);
}

void page_stock::UI_stock_new_item() {

	phone ph;
	system("cls");
	cout << "Please give a ID of product you want to stock:\n";
	int id;
	clear_cin();
	cin >> id;
	while (cin.fail()) {
		cout << "Invalid input. Please input correct ID(number):\n";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> id;
	}
	ph.set_id(id);

	system("cls");
	cout << "Please give a name for the product you want to stock:\n";
	string name;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(cin, name, '\n');
	ph.set_name(name);

	system("cls");
	cout << "Please input the amounts you want to stock:\n";
	int quantity;
	clear_cin();
	cin >> quantity;
	while (cin.fail()) {
		cout << "Invalid input. Please input correct amounts(number):\n";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> quantity;
	}
	ph.set_quantity(quantity);

	system("cls");
	cout << "Please describe about the product you want to stock, please input end and enter when you finish:\n";
	string whole_des = name + "\n", cur_des;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(cin, cur_des);
	while (cur_des != "end") {
		whole_des += cur_des + "\n";
		getline(cin, cur_des);
	}
	ph.set_description(whole_des);

	dbs->update_new_data(&ph);
	dbs->set_size(dbs->get_size() + 1);
}

void page_stock::clear_cin() {
	if (cin.fail()) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
}
