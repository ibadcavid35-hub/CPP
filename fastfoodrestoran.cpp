#include <iostream>
#include <cstring>
using namespace std;

class Product {
private:
	int _id = 0;
	char* _name = nullptr;
	char* _description = nullptr;
	double _price = 0;
	short _discount = 0;
public:
	Product(int id, const char* name, const char* description, double price, short discount) {
		_id = id;
		_name = new char[strlen(name) + 1];
		strcpy_s(_name, strlen(name) + 1, name);
		_description = new char[strlen(description) + 1];
		strcpy_s(_description, strlen(description) + 1, description);
		_price = price;
		_discount = discount;
	}

	~Product() {
		delete[] _name;
		delete[] _description;
	}

	int getId() {
		return _id;
	}

	double getDiscountPrice() {
		return _price - (_price * _discount / 100);
	}

	void print() {
		cout << "ID: " << _id << endl;
		cout << "Name: " << _name << endl;
		cout << "Description: " << _description << endl;
		cout << "Price: " << _price << endl;
		cout << "Discount: " << _discount << endl;
		cout << "Discount Price: " << getDiscountPrice() << " AZN" << endl;
	}
};

class Stock {
private:
	char* _name = nullptr;
	Product** _products = nullptr;
	size_t _count = 0;
public:

	Stock(const char* name):_products(nullptr),_count(0) {
		_name = new char[strlen(name) + 1];
		strcpy_s(_name, strlen(name) + 1, name);
	}

	~Stock() {
		delete[] _name;
		for (size_t i = 0;i < _count;i++) {
			delete[] _products[i];
		}
		delete[] _products;
	}

	void addProducts(Product* p) {
		Product** productcount = new Product * [_count + 1];
		for (size_t i = 0;i < _count;i++) {
			productcount[i] = _products[i];
		}
		productcount[_count] = p;
		delete[] _products;
		_products = productcount;
		_count++;
	}

	void print() {
		cout << "\nStock: " << _name << endl;
		for (size_t i = 0;i < _count;i++) {
			cout << "\nProduct " << i + 1 << endl;
			_products[i]->print();
		}
	}
	Product* getProductId(int Id) {
		for (size_t i = 0;i < _count;i++) {
			if (_products[i]->getId() == Id) {
				return _products[i];
			}
		}
		return nullptr;
	}
};

int main() {
	Stock ss("FastFood Restoran");
	ss.addProducts(new Product(1, "Pizza", "Lezzetli", 60, 20));
	ss.addProducts(new Product(2, "Doner", "Isti", 120, 50));
	ss.addProducts(new Product(3, "Burger", "Leziz", 90, 40));
	ss.print();
	Product* p = ss.getProductId(2);
	cout << "\nSearch: \n";
	if (p != nullptr) {
		p->print();
	}
	else cout << "Not Found\n";

	return 0;
}