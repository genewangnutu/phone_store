#include "basic_item.h"

class phone : public item {
private:
	int id = 0;
	int quantity = 0;
	string name;
	string description;

public:
	phone(){}
	
	phone(int &&input_id, int &&input_quantity, string &&input_name, string &&input_description) : id(move(input_id)),
		quantity(move(input_quantity)), name(move(input_name)), description(move(input_description)){

	}

	void set_id(int input_id);

	void set_name(string input_name);

	void add_quantity(int input_quantity);

	void set_quantity(int input_quantity);

	void set_description(string input_description);

	int get_id();

	const int get_id() const;

	int get_quantity();

	const int get_quantity() const;

	string get_name();

	const string get_name() const;

	string get_description();

	const string get_description() const;
};
