#include"data_base.h"

/**

Get the cart data.

param:
return:unordered_map<int, phone>*
**/
unordered_map<int, phone>* cart::get_cart() {
	return &buy_cart;
}

/**

Get the cart data by Id.

param: id - the id which will link to the cart data.
return:unordered_map<int, phone>*
**/
phone* cart::get_cart_byID(int id) {
	phone *ph = NULL;
	if (buy_cart.find(id) != buy_cart.end()) {
		ph = &buy_cart[id];
	}
	return ph;
}

/**

Add new product to the cart.

param: id - the id which will link to the data of cart hash table.
return:
**/
void cart::cart_add(phone *ph) {
	int id = ph->get_id();
	if (buy_cart.find(id) == buy_cart.end()) {
		phone cart_ph;
		cart_ph.set_id(id);
		cart_ph.set_name(ph->get_name());
		cart_ph.add_quantity(ph->get_quantity());
		buy_cart[id] = cart_ph;
	}
	else {
		buy_cart[id].add_quantity(ph->get_quantity());
	}
}

/**

Edit and update the cart.

param: id - the id which will link to the data of cart hash table.
return:
**/
void cart::cart_update(phone *ph) {
	if (ph) {
		phone cart_ph;
		int id = ph->get_id();
		int quantity = ph->get_quantity();

		if (quantity == 0) {
			buy_cart.erase(id);
		}
		else {
			cart_ph.set_id(ph->get_id());
			cart_ph.set_name(ph->get_name());
			cart_ph.set_quantity(ph->get_quantity());

			buy_cart[ph->get_id()] = cart_ph;
		}
	}
}

/**

Clear the cart.

param: 
return:
**/
void cart::cart_delete() {
	buy_cart.clear();
}

/**

Get the current cart amounts

param: 
return:
**/
int cart::get_cart_amounts() {
	return cart_amounts;
}

/**

Read the info of file database's category, the category record the 
format of whole file database like what kind of file should be 
read.

param: 
return:
**/
bool file_io::init_category() {
	ifstream file(path + category);

	if (!file.is_open()) {
		return false;
	}
	
	getline(file, file_id);
	getline(file, file_stock);
	file.close();

	return true;
}

/**

Read the file database by category format, read the id file and 
stocks file, update the item data to the local database.

param:	total_amounts - the address of total amounts of species item.
		product_Index_id - the address of the hash table link index to id.
		product_Name_id - the address of the hash table link name to id.
		product_data - the address of the hash table link id to phone.
return:	bool
**/
bool file_io::read_database(int &total_amounts, unordered_map<int, int> &product_Index_id,
	unordered_map<string, int> &product_Name_id,
	unordered_map<int, phone> &product_data){
	
	//Read the id and name.
	ifstream idfile(path + file_id);

	if (!idfile.is_open()) {
		cout << "Can't open the id file." << endl;
		return false;
	}

	int count = 0;
	string readline_total, readline_id, readline_name;
	getline(idfile, readline_total);
	total_amounts = stoi(readline_total);

	while (getline(idfile, readline_id, ',') && getline(idfile, readline_name, ',')) {
		int id = stoi(readline_id);
		product_Index_id[count++] = id;
		product_Name_id[readline_name] = id;
		product_data[id].set_id(id);
		product_data[id].set_name(readline_name);
	}

	idfile.close();

	//Read stocks.
	ifstream stockfile(path + file_stock);

	if (!stockfile.is_open()) {
		cout << "Can't open the stocks file." << endl;
		return false;
	}

	string readline_stocks;
	while (getline(stockfile, readline_id, ',') && getline(stockfile, readline_stocks, ',')) {
		int id = stoi(readline_id);
		product_data[id].add_quantity(stoi(readline_stocks));
	}

	stockfile.close();

	//Read descriptions
	ifstream desfile;
	for (auto des_read_it : product_Index_id) {
		int id = des_read_it.second;
		string des_file_name = to_string(id) + ".txt";

		desfile.open(path + des_file_name, ifstream::in);
		if (!desfile.is_open()) {
			cout << "Can't open the des file." << endl;
			return false;
		}


		string readline_whole_des = "";
		string readline_des;
		while (getline(desfile, readline_des)) {
			readline_whole_des += readline_des + "\n";
		}

		product_data[id].set_description(readline_whole_des);

		desfile.close();
	}

	return true;
}

/**

Update the local database's data to the file database, this function 
will called before the program end. 

param:	product_data - the address of the hash table link id to phone.
return:	bool
**/
bool file_io::update_database(unordered_map<int, phone> &product_data) {

	//Update the id.txt && stock.txt
	ofstream fout_id(path + file_id);

	if (fout_id.is_open()) {
		fout_id << product_data.size() << endl;

		for (auto it : product_data) {
			fout_id << it.second.get_id() << "," << it.second.get_name() << "," << endl;
		}
	}

	fout_id.close();

	//Update the stock.txt
	ofstream fout_stocks(path + file_stock);

	if (fout_stocks.is_open()) {
		for (auto it : product_data) {
			fout_stocks << it.second.get_id() << "," << it.second.get_quantity() << "," << endl;
		}
	}

	fout_stocks.close();

	//Update specific descriptions by ID.
	for (auto it : product_data) {
		string des_file_name = to_string(it.second.get_id()) + ".txt";
		ofstream fout_des(path + des_file_name);
		if (fout_des.is_open()) {
			fout_des << it.second.get_description();
		}

		fout_des.close();
	}

	return true;
}

/**

Do the local database initialization, read the whole data from file
database step by step.

param:	
return:	bool
**/
bool data_base::init() {
	
	bool read_status = fio.init_category();

	if (!read_status) {
		return false;
	}

	read_status = fio.read_database(total_size, product_Index_id, product_Name_id, product_data);

	if (!read_status) {
		return false;
	}

	return true;
}

/**

Update the local database data to the file database, this will called
in the program ending preprocess.

param:
return:	bool
**/
bool data_base::update() {
	bool write_status = fio.update_database(product_data);
	return write_status;
}

/**

Merge the cart data to the local database, which means some item's 
quantity will update because the reduced of cart data quantity.

param:	crt - Object cart.
return:	
**/
void data_base::merge(cart *crt) {

	unordered_map<int, phone>* buy_cart = crt->get_cart();

	for (auto it : *buy_cart) {
		int p_quantity = product_data[it.first].get_quantity();
		product_data[it.first].set_quantity(p_quantity - it.second.get_quantity());
	}

	buy_cart->clear();
}

/**

Check the product data in the local database exist or not by id.

param:	id - product id.
return:	bool
**/
bool data_base::is_product_exist(int id) const{
	if (product_data.find(id) != product_data.end()) {
		return true;
	}
	return false;
}

/**

Check the product data in the local database exist or not by name.

param:	name - product name.
return:	bool
**/
bool data_base::is_product_exist(string name) const{
	if (product_Name_id.find(name) != product_Name_id.end()) {
		return true;
	}
	return false;
}

/**

Get the local database's data address by id.

param:	id - product id.
return:	shared_ptr<const phone>
**/
shared_ptr<const phone> data_base::get_data_byID(int id) const{
	if (is_product_exist(id)) {
		shared_ptr<const phone> ph = make_shared<const phone>(product_data.at(id));
		return ph;
	}
	return NULL;
}

/**

Get the local database's data address by name.

param:	id - product name.
return:	shared_ptr<const phone>
**/
shared_ptr<const phone> data_base::get_data_byName(string name) const{
	if (is_product_exist(name)) {
		const int id = product_Name_id.at(name);
		shared_ptr<const phone> ph = make_shared<const phone>(product_data.at(id));
		return ph;
	}
	return NULL;
}

/**

Get the local database's data address by index.

param:	id - product index.
return:	shared_ptr<const phone>
**/
shared_ptr<const phone> data_base::get_data_byIndex(int index) const{
	
	auto it = product_Index_id.find(index);

	if (it != product_Index_id.end()) {
		shared_ptr<const phone> ph = make_shared<const phone>(product_data.at(it->second));
		return ph;
	}

	return NULL;
}

/**

Update the new data.

param:	ph - the pointer of phone object.
return:
**/
void data_base::update_new_data(phone* ph) {
	int id = ph->get_id();
	int quantity = ph->get_quantity();
	string name = ph->get_name();
	string des = ph->get_description();
	product_Index_id[product_Index_id.size()] = id;
	product_Name_id[name] = id;
	product_data[id].set_id(id);
	product_data[id].set_name(name);
	product_data[id].set_description(des);
	product_data[id].set_quantity(quantity);
}

void data_base::update_exist_data(int id, int amount) {
	phone *ph = &product_data[id];
	ph->add_quantity(amount);
}

int data_base::get_size() {
	return total_size;
}

void data_base::set_size(int size) {
	total_size = size;
}

