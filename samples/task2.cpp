#include "stack.h"
#include <ctime>
#include <locale>
void main() {
	setlocale(LC_CTYPE, "Rus");
	Table<std::string>* a;
	Ordered_table<std::string> b;
	a = &b;
	a->insert(2, "Собака");
	a->insert(3, "Кошка");
	a->insert(1, "Птица");
	a->insert(10, "Слон");
	a->insert(5, "Жираф");
	a->insert(4, "Лиса");
	a->remove(2);
	std::cout << *a;
}