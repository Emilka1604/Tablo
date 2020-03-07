#pragma once
#include <iostream>
#include <vector>
#include <exception>
#include <string>
#include <algorithm>
template<typename T>
int PARTITION(T* a, int left, int right) {
	T b;
	T k = a[right];
	int i = left - 1;
	int j = left;
	while (j < right) {
		if (a[j] <= k) {
			i++;
			b = a[i];
			a[i] = a[i + 1];
			a[i + 1] = b;
			//std::swap(a[i], a[j]);
		}
		j++;
	}
	//std::swap(k, a[i + 1]);
	b = a[k];
	a[k] = a[i + 1];
	a[i + 1] = b;
	return i + 1;
}
template<typename T>
void qsort(T* a, int left, int right )
{
	if (right > left) {
		int q = PARTITION(a, left, right);
		qsort(a, left, q - 1);
		qsort(a, q + 1, right);
	}
}
template<typename T>
std::vector<T> Qsort(std::vector<T> v) {
	if (v.size() != 0) {
		int k = v.size() / 2;
		std::vector<T> vm;
		std::vector<T> vb;
		int i;
		for (i = 0; i < v.size(); i++) {

			if (v[i] < v[k])
				vm.push_back(v[i]);
			else
				if (i != k)
					vb.push_back(v[i]);

		}
		if (vm.size() > 1 || vb.size() > 1) {
			std::vector<T> v1 = Qsort(vm);
			std::vector<T> v2 = Qsort(vb);
			v1.push_back(v[k]);
			for (i = 0; i < v2.size(); i++)
				v1.push_back(v2[i]);
			return v1;
		}
		else {
			vm.push_back(v[k]);
			for (i = 0; i < vb.size(); i++)
				vm.push_back(vb[i]);
			return vm;
		}
	}
}

template<class T>
class List {
private:
	template<class T>
	class Node
	{
	public:
		Node<T>* next;
		T data;
		Node(T data = T(), Node* next = nullptr) {
			this->next = next;
			this->data = data;
		}
	};
	Node<T>* head;
	int size;

public:
	class iterator {
	private:
		Node<T>* elem;
	public:
		iterator() {
			elem = nullptr;
		}
		iterator(Node<T>* elem) { this->elem = elem; }
		void operator++(int) { elem = elem->next; }
		T& operator*() { return elem->data; }
		bool operator==(iterator it) {
			return (this->elem == it.elem);
		}
		bool operator!=(iterator it) { return !(this->operator==(it)); }
		iterator& operator=(iterator it) {
			elem = it.elem;
			return *this;
		}
		void swap( iterator& it2) {
			List<T>::iterator it;
			it = *this;
			*this = it2;
			it2 = it;
		}
		friend class List;
	};
	List();
	List(int n);
	void insert(iterator& it, T data) {
		Node<T>* a = new Node<T>;
		a = it.elem->next;
		Node<T>* tmp = new Node<T>(data, a);
		it.elem->next = tmp;
		size++;
	}
	void remove(iterator& it) {
		Node<T>* a = new Node<T>;
		a = it.elem->next->next;
		delete[] it.elem->next;
		it.elem->next = a;
		size--;
	}
	iterator begin() {
		auto it = iterator(head);
		return it;
	}
	iterator end() {
		auto it = List<T>::iterator(NULL);
		return it;
	}
	~List();
	void push_back( T);
	void push_begin(T);
	void delete_back();
	void delete_begin();
	int getsize() { return size; }
	bool operator==(List<T>&);
	List(List<T>&);
	List<T>& operator=(List<T>&);
};
template<class T>
List<T>::List() {
	head = nullptr;
	size = 0;
}
template<class T>
List<T>::List(int n) {
	size = n;
	head = new Node<T>;
	Node<T>* tmp = head;
	for (int i = 1; i < size; i++) {
		Node<T>* tmp2 = new Node<T>;
		tmp->next = tmp2;
		tmp = tmp2;
	}
	tmp->next = nullptr;

}
template<class T>
List<T>::~List() {
	if (head != nullptr) {
		Node<T>* a = head;
		if (a->next != nullptr) {
			Node<T>* b;
			while (a->next != nullptr) {
				b = a;
				a = a->next;
				delete[] b;
			}
			delete[] a;
		}
		else
			delete[] a;
	}
}
template<class T>
void List<T>::push_back(T data) {
	if (size == 0)
		head = new Node<T>(data);

	else {
		Node<T>* tmp = this->head;
		while (tmp->next != NULL) {
			tmp = tmp->next;
		}
		tmp->next = new Node<T>(data);
	}
	size++;
}
template<class T>
void List<T>::push_begin(T data) {
	if (size == 0) {
		head = new Node<T>(data);
	}
	else {
		Node<T>* tmp = new Node<T>(data, head);
		head = tmp;
	}
	size++;
}
template<class T>
void List<T>::delete_back() {
	if (size == 0) {
		std::exception ex("Empty list");
		throw ex;
	}
	else {
		Node<T>* tmp = head;
		if (tmp->next != nullptr) {
			tmp = tmp->next;
			Node<T>* tmp1 = head;
			while (tmp->next != nullptr) {
				tmp = tmp->next;
				tmp1 = tmp1->next;
			}
			delete[] tmp;
			tmp1->next = nullptr;
			size--;
		}
		else {
			delete[] tmp;
			size--;
			head = nullptr;
		}
	}
}
template<class T>
void List<T>::delete_begin() {
	if (size == 0) {
		std::exception ex("Empty list");
		throw ex;
	}
	else {
		Node<T>* a = head;
		head = head->next;
		delete[] a;
		size--;
	}
}
template<class T>
bool List<T>::operator==(List<T>& lst) {
	if (this == &lst)
		return true;
	else {
		bool a = false;
		if (size == lst.size) {
			if (size == 0)
				a = true;
			else {
				int sum = 0;
				List<T>::iterator it_this(begin());
				List<T>::iterator it_lst(lst.begin());
				while (it_this != end()) {
					if ((*it_this) == (*it_lst))
						sum++;
					it_this++;
					it_lst++;
				}
				if (size == sum)
					a = true;

			}
		}
		return a;
	}
}
template<class T>
List<T>::List(List<T>& lst) {
	if (lst.head == nullptr) {
		head == nullptr;
		size = 0;
	}
	else {
		size = lst.size;
		List<T>::iterator it = lst.begin();
		head = new Node<T>(*it);
		Node<T>* tmp = head;
		it++;
		while (it != lst.end()) {
			tmp->next = new Node<T>(*it);
			tmp = tmp->next;
			it++;
		}
		tmp->next = nullptr;
	}
}
template<class T>
List<T>& List<T>::operator=(List<T>& lst) {
	while (size != 0) {
		this->delete_back();
	}
	if(lst.size != 0) {
		size = lst.size;
		List<T>::iterator it = lst.begin();
		head = new Node<T>(*it);
		Node<T>* tmp = head;
		it++;
		while (it != lst.end()) {
			tmp->next = new Node<T>(*it);
			tmp = tmp->next;
			it++;
		}
		tmp->next = nullptr;
	}
	return *this;
}
template<typename T>
T& middle_elem(List<T>& lst) {   //Задача найти средний элемент в списке
	List<T>::iterator it1 = lst.begin();
	List<T>::iterator it2 = lst.begin();
	if (it1 != lst.end()) {
		it1++;
		if (it1 == lst.end())
			return *it2;
		else {
			while (it1 != lst.end()) {
				it2++;
				it1++;
				if (it1 == lst.end())
					break;
				it1++;
			}
			return *it2;
		}
	}
	else {
		std::exception ex("Empty list");
		throw ex;
	}
}
template<typename T>
T& k_elem(List<T>& lst, int k){  //Задача найти k-й элемент с конца
	List<T>::iterator it1 = lst.begin();
	List<T>::iterator it2 = lst.begin();
	if (it1 != lst.end()) {
		for (int i = 0; i < k - 1; i++) {
			it1++;
			if (it1 == lst.end()) {
				std::exception ex("k < size");
				throw ex;
			}
		}
		it1++;
		while (it1 != lst.end()) {
			it2++;
			it1++;
		}
		return *it2;

		
	}
	else {
		std::exception ex("Empty list");
		throw ex;
	}
}
class elem {
	private:
		std::string name;
		char value;
public:
	elem(std::string name , char value) {
		this->name = name;
		this->value = value;
	}
	std::string getname() {
		return name;
	}
	char getvalue() {
		return value;
	}
};
class polynom {
private:
	class link {
	public:
		double coeff;
		int degnum;
		int factor;
		link() {
			coeff = 1;
			degnum = 0;
			factor = 0;
		}
		void clean() {
			coeff = 1;
			degnum = 0;
			factor = 0;
		}
		void setfactor(elem& el) {
			if (el.getvalue() == 'X')
				factor = 100;
			else
				if (el.getvalue() == 'Y')
					factor = 10;
				else
					factor = 1;

		}
		void printlnk() {
			std::cout << coeff << " " << degnum << "\n";
		}
		bool operator>(link lnk) {
			if (degnum > lnk.degnum)
				return true;
			else
				return false;
		}
		bool operator==(link l) {
			if (degnum == l.degnum)
				return true;
			else
				return false;
		}
		friend std::vector<link> bubble(std::vector<link> v) {
			for (int i = 0; i < v.size() - 1; i++) {
				for (int j = 0; j < v.size() - i - 1; j++)
					if (v[j] > v[j + 1]) {
						link temp;
						temp = v[j];
						v[j] = v[j + 1];
						v[j + 1] = temp;

					}
			}
			return v;
		}
		link& operator=(link l) {
			degnum = l.degnum;
			factor = l.factor;
			coeff = l.coeff;
			return *this;
		}
		friend polynom;
	};
	std::vector<elem> v;
	List<link> lst;
	link lnk;
	int faza;
public:


	polynom() {
		for (int i = 0; i < 10; i++) {
			elem a("num", std::to_string(i)[0]);
			v.push_back(a);
		}
		v.push_back(elem("oper", '+'));
		v.push_back(elem("oper", '-'));
		v.push_back(elem("oper", '*'));
		v.push_back(elem("var", 'X'));
		v.push_back(elem("var", 'Y'));
		v.push_back(elem("var", 'Z'));
		v.push_back(elem("null", '\0'));
		faza = 0;
	}
	elem& find(char s) {
		for (int i = 0; i < v.size(); i++) {
			if (v[i].getvalue() == s)
				return v[i];
		}
		std::exception ex("Unknown symbol");
		throw ex;
	}
	void print() {
		List<link>::iterator it = lst.begin();
		for (; it != lst.end(); it++)
			(*it).printlnk();

	}



	void parser(std::string str) {
		int state = 0;
		int i = 0;
		if (find(str[i]).getvalue() == '-') {
			if (str[i + 1] == '\0')
				state = 2;
			lnk.coeff *= (-1);
			i++;

		}
		while (state < 2) {
			switch (state) {
			case 0:
				if (find(str[i]).getname() == "num") {
					size_t l;
					double res = std::stod(&str[i], &l);
					i += l;
					lnk.coeff *= res;
					state = 1;
				}
				else
					if (find(str[i]).getname() == "var") {
						lnk.setfactor(find(str[i]));
						if (str[i + 1] == '^') {
							i++;
							if (find(str[i + 1]).getname() == "num") {
								i++;
								std::string s;
								s += str[i];
								lnk.degnum += lnk.factor * (std::stoi(s));
								i++;
								state = 1;
							}
							else
								state = 2;


						}
						else {
							lnk.degnum += lnk.factor;
							i++;
							state = 1;
						}
					}
					else
						if (str[i] == '\0') {
							lnk.coeff = 0;
							lst.push_back(lnk);
							state = 3;
						}
						else {
							state = 2;
						}
				break;


			case 1:
				if (str[i] == '*') {
					i++;
					if (str[i] == '\0')
						state = 2;
					else
						if (find(str[i]).getname() == "num")
							state = 2;
						else
							state = 0;

				}
				else
					if (find(str[i]).getname() == "oper") {
						if (str[i + 1] == '\0')
							state = 2;
						lst.push_back(lnk);
						lnk.clean();
						if (str[i] == '+') {
							i++;
							state = 0;
						}
						else {
							lnk.coeff *= (-1);
							i++;
							state = 0;
						}
					}
					else
						if (str[i] == '\0') {
							state = 3;
							lst.push_back(lnk);
							lnk.clean();
						}
						else
							state = 2;
				break;
			}
		}

		if (state == 2) {
			std::exception ex("Not correct string");
			throw ex;
		}
		else {
			std::vector<link> vec;
			List<link> lst1;
			List<link>::iterator it1 = lst.begin();
			while (it1 != lst.end()) {
				vec.push_back(*it1);
				it1++;
			}
			vec = bubble(vec);
			for (int i = 0; i < vec.size(); i++)
				lst1.push_back(vec[i]);
			lst = lst1;
			this->cast();


		}
	}

	void cast() {
		faza = 1;
		if (lst.getsize() != 1) {
			List<link> lst1;
			List<link>::iterator it1 = lst.begin();
			lst1.push_back(*it1);
			List<link>::iterator it2 = lst1.begin();
			it1++;
			while (it1 != lst.end()) {
				if (*it1 == *it2) {
					(*it2).coeff += (*it1).coeff;
					it1++;
				}
				else {
					lst1.push_back(*it1);
					it1++;
					it2++;
				}
			}
			lst = lst1;
		}
		//faza = 2;
	}

	polynom operator+(polynom& p) {
		if ((faza == 1) && (p.faza == 1)) {
			polynom q;
			List<link>::iterator it1 = lst.begin();
			List<link>::iterator it2 = p.lst.begin();
			link l;
			List<link> lst1;
			l.coeff = 0;
			while (it1 != lst.end()) {
				if ((*it1).degnum < (*it2).degnum) {
					l.coeff += (*it1).coeff;
					l.degnum = (*it1).degnum;
					lst1.push_back(l);
					it1++;
					l.coeff = 0;
				}
				else
					if ((*it1).degnum == (*it2).degnum) {
						l.coeff = (*it1).coeff;
						l.degnum = (*it1).degnum;
						it1++;
						if (it1 != lst.end())
							it1.swap(it2);


					}
					else
						it1.swap(it2);
			}
			while (it2 != lst.end()) {
				l.coeff += (*it2).coeff;
				l.degnum = (*it2).degnum;
				lst1.push_back(l);
				l.coeff = 0;
				it2++;
			}
			q.lst = lst1;
			q.faza = 1;
			return q;
		}
		else {
			std::exception ex("operation not available");
			throw ex;
		}
	}

	polynom operator-(polynom& p) {
		if ((faza == 1) && (p.faza == 1)) {
			List<link>::iterator it = p.lst.begin();
			while (it != p.lst.end()) {
				(*it).coeff *= (-1);
				it++;
			}
			return (*this + p);
		}
	}


	polynom operator*(polynom& p) {
		if ((faza == 1) && (p.faza == 1)) {
			int i;
			polynom q;
			List<link> lst1;
			link l;
			List<link>::iterator it1 = lst.begin();
			List <link>::iterator it2 = p.lst.begin();
			for (; it1 != lst.end(); it1++) {
				for (; it2 != p.lst.end(); it2++) {
					l.coeff = (*it1).coeff * (*it2).coeff;
					int a = (*it1).degnum;
					int b = (*it2).degnum;
					for (i = 100; i != 0; i/=10) {
						if (a / i + b / i > 9) {
							std::exception ex("Big deg");
							throw ex;
						}
						a -= (a / i) * i;
						b -= (b / i) * i;

					}
					l.degnum = (*it1).degnum + (*it2).degnum;
					lst1.push_back(l);
				}
			}
			q.lst = lst1;
			q.cast();
			return q;

		}
		else {
			std::exception ex("operation not available");
			throw ex;
		}
	}

	friend std::ostream& operator<<(std::ostream& ostr, polynom& p ) {
		if ((p.faza == 1)) {
			std::string str;
			int a;
			List<link>::iterator it = p.lst.begin();
			while (it != p.lst.end()) {
				if (std::abs((*it).coeff) == 1) {
					if ((*it).coeff < 0)
						if ((*it).degnum != 0)
							str += '-';
						else
							str += std::to_string((*it).coeff);
					else
						if ((*it).degnum == 0)
							str += std::to_string((*it).coeff);
				}
				else
					if ((*it).coeff != 0) {
						str += std::to_string((*it).coeff);
						if ((*it).degnum != 0)
							str += '*';
					}
				if ((*it).coeff != 0) {
					if ((*it).degnum / 100 != 0) {
						if ((*it).degnum / 100 == 1) {
							str += 'X';
							if ((*it).degnum % 100 != 0)
								str += '*';
						}
						else {
							str += 'X';
							str += '^';
							str += std::to_string((*it).degnum / 100);
							if ((*it).degnum % 100 != 0)
								str += '*';
						}
					}
					a = (*it).degnum % 100;
					if (a / 10 != 0) {
						if (a / 10 == 1) {
							str += 'Y';
							if (a % 10 != 0)
								str += '*';
						}
						else {
							str += 'Y';
							str += '^';
							str += std::to_string(a / 10);
							if (a % 10 != 0)
								str += '*';
						}
					}
					a = a % 10;
					if (a != 0) {
						if (a == 1) {
							str += 'Z';
						}
						else {
							str += 'Z';
							str += '^';
							str += std::to_string(a);
						}
					}
				}
				it++;
				if (it != p.lst.end() && (*it).coeff > 0)
					if(!str.empty())
					str += '+';
			}
			if (str.empty())
				str += '0';
			ostr << str;
			return ostr;
		}
	
		else {
			std::exception ex("operation not available");
			throw ex;
		}
	}


};
template<class T>
class cell {
private:
	T data;
	int key;
public:
	int getkey() {
		return key;
	}
	T& getdata() {
		return data;
	}
	cell(int key = 0, T data = T()) {
		this->key = key;
		this->data = data;
	}
};
template<class T>
class tablo {
private:
	cell<T>* mas;
	int size;
	int Msize;
public:
	int getsize() {
		return size;
	}
	tablo() {
		size = 0;
		Msize = 6;
		cell<T>* mas1 = new cell<T>[6];
		mas = mas1;
	}
	cell<T>* search(int key) {
		for (int i = 0; i < size; i++) {
			if ( mas[i].getkey() == key )
				return &mas[i];
		}
		return NULL;
	}
	void push(int key, T data) {
		if (search(key)) {
			std::exception ex("Ключ не уникален");
			throw ex;
		}
		cell<T> c(key, data);
		if (size < Msize) {
			mas[size] = c;
		}
		else {
			Msize = Msize / 2 * 3;
			cell<T>* mas1 = new cell<T>[Msize];
				for (int i = 0; i < size; i++)
					mas1[i] = mas[i];
			mas1[size] = c;
			delete [] mas;
			mas = mas1;
		}
		size++;

	}
	T& getelem (int key) {
		cell<T>* a = search(key);
		if (!a) {
			std::exception ex("Данного элемента нет в таблице");
			throw ex;
		}
		return a->getdata;
	}
	friend std::ostream& operator<<(std::ostream& ostr, tablo& t) {
		ostr << "Ключ" << "     " << "Значение" << '\n' << '\n';
		for (int i = 0; i < t.getsize(); i++) 
			ostr << t.mas[i].getkey() << "     " << t.mas[i].getdata()<<'\n'<<'\n';
		return ostr;
	}
	void del(int key) {
		cell<T>* a = search(key);
		if (!a) {
			std::exception ex("Данного элемента нет в таблице");
			throw ex;
		}
		cell<T>* b = new cell<T>;
		*b = *a;
		*a = mas[size - 1];
		mas[size - 1] = *b;
		if (size == Msize / 2 && Msize > 6) {
			size--;
			Msize = size / 2 * 3;
			cell<T>* mas1 = new cell<T>[Msize];
			for (int i = 0; i < size; i++)
				mas1[i] = mas[i];
			delete[] mas;
			mas = mas1;
		}
		else
			size--;
	}



};