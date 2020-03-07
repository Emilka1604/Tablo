#include "stack.h"
#include <ctime>
#include <locale>
void main() {
	setlocale(LC_CTYPE, "Rus");
/*	int k = 0;
	while (k < 4) {
		std::cout << "Выберете операцию\n";
		std::cout << "1. Сложение полиномов\n";
		std::cout << "2. Вычитание полиномов\n";
		std::cout << "3. Умножение полиномов\n";
		std::cout << "4. Выход\n";
		std::cout << "Ваш выбор: ";
		std::cin >> k;
		if (k < 4) {
			std::cout << "Введите первый полином: ";
			polynom p;
			std::string s1;
			std::cin >> s1;
			p.parser(s1);
			std::cout << "Введите второй полином: ";
			polynom q;
			std::string s2;
			std::cin >> s2;
			q.parser(s2);
			switch (k) {
			case 1:
				std::cout << "Результат операции сложения: " << (p + q).printp() << "\n";
				break;
			case 2:
				std::cout << "Результат операции вычитания: " << (p - q).printp() << "\n";
				break;
			case 3:
				std::cout << "Результат операции умножения: " << (p * q).printp() << "\n";
				break;
			}
		}




	}*/
	polynom  a,b,c,d,e,f,g,h;
	a.parser("X^2+1");
	b.parser("Y");
	c.parser("Z^8-11");
	d.parser("X");
	e.parser("X^2+Y");
	f.parser("1");
	g.parser("3*Z^5");
	h.parser("X^3+Y^3+Z^3");
	tablo<polynom> t;
	t.push(1, a);
	t.push(2, b);
	t.push(3, c);
	t.push(4, d);
	t.push(5, e);
	t.push(6, f);
	t.push(7, g);
	t.push(8, h);
	t.del(3);
	t.del(1);
	t.del(7);
	t.del(5);
	t.del(6);
	std::cout << t;
}