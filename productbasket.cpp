#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

//enum Category
enum Category {
	FOOD,
	BEVERAGES,
	CLEANING,
	PERSONALCARE,
	SNACK,
	HEALTH,
	HOUSEHOLD,
	BABYPRODUCTS
};

//Product class 

class Product {
private:
	int _id;
	char* _name;
	double _price;
	Category* _category;
	double _discount;
	int _count;
	int _catsize;
public:
	bool _isinStock;
	static int _counter;
	Product() : _name(nullptr), _price(0), _category(nullptr),
		_discount(0), _count(0), _catsize(0), _isinStock(false) {
	};

	Product(const char* name, double price, Category* category,
		double discount, int count, int catsize) {
		_id = _counter++;
		_name = new char[strlen(name) + 1];
		strcpy_s(_name, strlen(name) + 1, name);
		_price = price;
		_catsize = catsize;
		_category = new Category[_catsize];
		for (int i = 0;i < _catsize;i++) {
			_category[i] = category[i];
		}
		_discount = discount;
		_count = count;

	}

	Product(const Product& other) {
		_id = other._id;
		_name = new char[strlen(other._name) + 1];
		strcpy_s(_name, strlen(other._name) + 1, other._name);
		_price = other._price;
		_catsize = other._catsize;
		_category = new Category[_catsize];
		for (int i = 0;i < _catsize;i++) {
			_category[i] = other._category[i];
		}
		_discount = other._discount;
		_count = other._count;

	}

	Product& operator=(const Product& other) {
		if (this != &other) {
			delete[] _name;
			delete[] _category;

			_id = other._id;
			_name = new char[strlen(other._name) + 1];
			strcpy_s(_name, strlen(other._name) + 1, other._name);
			_price = other._price;
			_catsize = other._catsize;
			_category = new Category[_catsize];
			for (int i = 0;i < _catsize;i++) {
				_category[i] = other._category[i];
			}
			_discount = other._discount;
			_count = other._count;

		}
		return *this;
	}

	~Product() {
		delete[] _category;
		delete[] _name;
		_category = nullptr;
		_name = nullptr;
	}



	char* getName() const {
		return _name;
	}

	double getPrice() const {
		return _price;
	}

	void getCategory(Category cat) const {
		switch (cat) {
		case FOOD: cout << "FOOD";break;
		case BEVERAGES: cout << "BEVERAGES";break;
		case CLEANING: cout << "CLEANING";break;
		case PERSONALCARE: cout << "PERSONAL CARE";break;
		case SNACK: cout << "SNACK";break;
		case HEALTH: cout << "HEALTH";break;
		case HOUSEHOLD: cout << "HOUSE HOLD";break;
		case BABYPRODUCTS: cout << "BABY PRODUCTS";break;
		}
	}


	bool operator>(Product& other) const {
		return this->getPrice() > other.getPrice();
	}

	static void compareProducts(Product& p1, Product& p2) {
		if (p1 > p2) {
			cout << "P1 bahadir.\n";
		}
		else if (p2 > p1) { cout << "P2 bahadir.\n"; }
		else cout << "Beraberdir\n";
	}

	bool isInStock() const {
		return _count > 0;
	}

	//Vergi

	Product& operator++() {
		this->_price += 50;
		return *this;
	}

	int getId() {
		return _id;
	}

	double getFinalPrice() const {
		return _price - (_price * _discount / 100);
	}

	int getProductCount() const {
		return _count;
	}

	int getCategoryCount() const {
		return _catsize;
	}

	//Faiz

	Product operator-() {
		this->_discount += 10;
		if (this->_discount > 100)
			this->_discount = 100;
		return *this;
	}



	void showProducts() {
		cout << "ID: " << getId() << endl;
		cout << "Name: " << getName() << endl;
		cout << "Price: " << getPrice() << endl;
		cout << "Final price: " << getFinalPrice() << endl;
		cout << "Categories: ";
		for (int i = 0; i < _catsize; i++) {
			getCategory(_category[i]);
			cout << " ";
		}
		cout << endl;
		cout << "Stockdadir: " << (isInStock() ? "Movcuddur" : "Movcud deyil") << endl;
		cout << "Count: " << getProductCount() << endl;
		cout << endl;

	};

	//Move constructor

	Product(Product&& other) noexcept
		: _id(other._id),
		_name(other._name),
		_price(other._price),
		_category(other._category),
		_discount(other._discount),
		_count(other._count),
		_catsize(other._catsize),
		_isinStock(other._isinStock)
	{
		other._name = nullptr;
		other._category = nullptr;

		other._id = 0;
		other._price = 0;
		other._discount = 0;
		other._count = 0;
		other._catsize = 0;
		other._isinStock = false;
	}

};

int Product::_counter = 1;

//Basket Class
class Basket {
public:
	vector<Product> _products;
	int _totalProductCount;
	double _totalPrice;

	void addProduct(Product& p) {
		_products.push_back(p);

	}

	//Add Product
	Basket& operator*(Product& p) {
		_products.push_back(p);
		return *this;
	}

	Basket() :_totalPrice(0), _totalProductCount(0) {}

	int getTotalProcutCount() {
		for (Product& pro : _products) {
			_totalProductCount += pro.getProductCount();
		}
		return _totalProductCount;
	}

	double getTotalPrice() {
		for (Product& pro : _products) {
			_totalPrice += pro.getPrice();
		}
		return _totalPrice;
	}

	void showAllProducts() {
		if (_products.empty()) {
			cout << "Product yoxdu.\n";
			return;
		}
		for (Product& product : _products) {
			product.showProducts();
		}
	}
};

int main() {
	Category cat[] = { FOOD, SNACK };

	Product p1("Burger", 100, cat, 0, 5, 2);
	Product p3("Pizza", 120, cat, 0, 0, 2);

	Product p2 = -p1; //Faiz
	Product p4 = ++p1; //Vergi
	Product p5 = move(p3); //move

	Product p6("Doner", 80, cat, 0, 100, 2);
	
	Basket b;
	b.addProduct(p1);
	b.addProduct(p2);
	b.addProduct(p4);
	b.addProduct(p5);
	b* p6; //add product by operator

	b.showAllProducts();

	Product::compareProducts(p1, p3); //compare products

	cout << "Total product count: " << b.getTotalProcutCount() << endl;
	cout << "Total product Price: " << b.getTotalProcutCount() << endl;



	return 0;
}