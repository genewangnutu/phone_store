#include"phone.h"

class cart {
private:
	int cart_amounts = 0;
	unordered_map<int, phone>buy_cart;//ID-Buying Amount cart map.
public:
	unordered_map<int, phone>*get_cart();

	phone* get_cart_byID(int id);

	void cart_add(phone *ph);

	void cart_update(phone *ph);

	void cart_delete();

	int get_cart_amounts();
};

class file_io {
private:
	const string path = "C:../file/";
	const string category = "category.txt";
	string file_id;
	string file_stock;
	string file_description;
public:

	bool init_category();

	bool read_database(int &total_amounts, unordered_map<int, int> &product_Index_id,
		unordered_map<string, int> &product_Name_id,
		unordered_map<int, phone> &product_data);

	bool update_database(unordered_map<int, phone> &product_data);
};

class data_base {
private:
	file_io fio;
	int total_size = 0;
	unordered_map<int, int>product_Index_id; // Index-ID hash map.
	unordered_map<string, int>product_Name_id; // Name-ID hash map.
	unordered_map<int, phone>product_data; // ID-Data hash map.

public:

	data_base() {}

	bool init();

	bool update();

	void merge(cart *crt);

	bool is_product_exist(int id) const;

	bool is_product_exist(string name) const;

	shared_ptr<const phone> get_data_byID(int id) const;

	shared_ptr<const phone> get_data_byName(string name) const;

	shared_ptr<const phone> get_data_byIndex(int index) const;

	void update_new_data(phone* ph);

	void update_exist_data(int id, int amount);

	int get_size();

	void set_size(int size);
};

