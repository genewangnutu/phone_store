#include"page_main_menu.h"

/**
mainmenu
show main menu

return n/a
**/
int page_main_menu::run_menu() {

	cout << "Welcome to the kai's online phone store\n\n"
			 << "Function:\n"
			 << "1 [Product List]" << " 2 [Stock]" << " 3 [Exit]\n";
	cin >> selectior;

	while (cin.fail()) {
		cout << "Invalid input. Please input correct command:\n";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> selectior;
	}

	return selectior;

}
/**
back
Do the things before back to previous page.

return n/a
**/
void page_main_menu::back() {

}
