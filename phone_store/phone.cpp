#include"phone.h"


void phone::set_id(int input_id) {
	id = input_id;
}

void phone::set_name(string input_name) {
	name = input_name;
}

void phone::add_quantity(int input_quantity) {
	quantity += input_quantity;
}

void phone::set_quantity(int input_quantity) {
	quantity = input_quantity;
}

void phone::set_description(string input_description) {
	description = input_description;
}

int phone::get_id() {
	return id;
}

const int phone::get_id() const{
	return id;
}

int phone::get_quantity() {
	return quantity;
}

const int phone::get_quantity() const{
	return quantity;
}

string phone::get_name() {
	return name;
}

const string phone::get_name() const{
	return name;
}

string phone::get_description() {
	return description;
}

const string phone::get_description() const{
	return description;
}
