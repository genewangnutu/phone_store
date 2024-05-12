#include"page_product_list.h"

int page_product_list::run_menu() {

	while (menu_lock) {

		system("cls");

		cout << "-----------------This is Product list----------------- \n\n";

		UI_product_list();

		cout << "Function:\n"
			<< "1 [See product spec]" << " 2 [Shopping]" << " 3 [Back]\n";
		int selectior;
		cin >> selectior;

		while (cin.fail()) {
			cout << "Invalid input. Please input correct command:\n";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin >> selectior;
		}

		if (selectior == 1) {
			UI_spec();
		}
		else if (selectior == 2) {
			UI_add_cart();
		}
		else if (selectior == 3) {
			back();
			menu_lock = false;
		}

	}

	menu_lock = true;

	return 0;
}

void page_product_list::back() {

}

void page_product_list::UI_product_list() {
	if (dbs) {
		shared_ptr<const phone> ph;
		printf("%3sID%16sName%12sQuantity\n","","","");
		for (int i = 0; i < dbs->get_size(); i++) {
			ph = dbs->get_data_byIndex(i);
			if (ph) {
				printf("%d%20s%20d\n", ph->get_id(), ph->get_name().c_str(), ph->get_quantity());
			}
		}
	}
}

void page_product_list::UI_spec() {

	while (show_spec_lock) {
		system("cls");

		cout << "See product spec by?\n\n";
		cout << "1 [By ID]" << " 2 [By Name]" << " 3 [Back]\n";
		int show_spec_selectior;
		cin >> show_spec_selectior;
		if (show_spec_selectior == 1) {
			
			cout << "Please input the ID:\n";
			int id;
			clear_cin();
			cin >> id;

			shared_ptr<const phone> ph = dbs->get_data_byID(id);
			UI_spec_by_ID_Name(ph, 1);
			
		}
		else if (show_spec_selectior == 2) {
			cout << "Please input the product name:\n";
			string name;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			getline(cin, name, '\n');

			shared_ptr<const phone> ph = dbs->get_data_byName(name);
			UI_spec_by_ID_Name(ph, 2);
		}
		else if (show_spec_selectior == 3) {
			show_spec_lock = false;
		}
	}

	show_spec_lock = true;
}

void page_product_list::UI_spec_by_ID_Name(shared_ptr<const phone> ph, int mode) {

	while (!ph) {
		
		if (mode == 1) {
			int id;
			cout << "Can't find the Product by ID, please input the correct ID:\n";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin >> id;
			ph = dbs->get_data_byID(id);
		}
		else if (mode == 2) {
			string name;
			cout << "Can't find the Product by Name, please input the correct product name:\n";
			clear_cin();
			getline(cin, name, '\n');
			ph = dbs->get_data_byName(name);
		}
	}
	
	while (show_spec_lock2) {
		system("cls");
		cout << "-----------------Product Specification----------------- \n\n";

		cout << ph->get_description();

		cout << "\n1 [back]\n";
		int show_spec_selectior2;
		cin >> show_spec_selectior2;
		if (show_spec_selectior2 == 1) {
			show_spec_lock2 = false;
		}

	}
	show_spec_lock2 = true;
}

void page_product_list::UI_add_cart() {
	while (show_add_cart_lock) {
		system("cls");

		cout << "-----------------This is Product list----------------- \n\n";

		UI_product_list();

		cout << "\n\n---------------------Buying Cart---------------------\n\n";

		UI_cart_list();

		cout << "Function:\n"
			<< "1 [Add cart by id]" << " 2 [Buy]" << " 3 [back]\n";
		int add_cart_selectior;
		cin >> add_cart_selectior;

		if (add_cart_selectior == 1) {
			UI_cart_add();
		}
		else if (add_cart_selectior == 2) {
			if (dbs && crt) {
				dbs->merge(crt);
			}
		}
		else if(add_cart_selectior==3){
			show_add_cart_lock = false;
		}

	}
	show_add_cart_lock = true;
}

void page_product_list::UI_cart_list() {
	if (crt) {
		unordered_map<int, phone>* mycart = crt->get_cart();
		printf("%3sID%16sName%12sQuantity\n", "", "", "");

		if (mycart) {
			for (auto it : *mycart) {
				printf("%d%20s%20d\n", it.second.get_id(), it.second.get_name().c_str(), it.second.get_quantity());
			}
		}
	}
}

void page_product_list::UI_cart_add() {

	cout << "Which product Id you want to buy:\n";
	int id;
	cin >> id;

	while (!dbs->get_data_byID(id)) {
		cout << "Please input the correct ID, which product Id you want to buy:\n";
		cin >> id;
	}

	cout << "What amounts you want to buy:\n";
	int amounts;
	cin >> amounts;

	phone ph;
	shared_ptr<const phone> dbs_ph = dbs->get_data_byID(id);
	phone *crt_ph = crt->get_cart_byID(id);
	int dbs_amount = 0, crt_amount = 0;

	if (dbs_ph) {
		ph.set_id(id);
		ph.set_name(dbs_ph->get_name());
		dbs_amount = dbs_ph->get_quantity();

		while (amounts > dbs_amount) {
			cout << "Buying amounts is larger than product stocks, please input other amounts:\n";
			cin >> amounts;
		}
	}

	if (crt_ph) {
		crt_amount = crt_ph->get_quantity();

		while ((amounts + crt_amount) > dbs_amount) {
			cout << "Total buying amounts(buying amounts + cart amounts) is larger than product stocks, please input other amounts:\n";
			cin >> amounts;
		}
	}

	ph.set_quantity(amounts);
	crt->cart_add(&ph);
}

void page_product_list::clear_cin() {
	if (cin.fail()) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
}

