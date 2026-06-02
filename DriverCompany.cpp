#include <iostream>
#include <vector>



using namespace std;
class Company;
class Passenger;
class Driver {
private:
	string _name;
	string _lisence;
	double _totalincome;
	int _totaltrip;

	friend void completeTrip(Driver& d, Company& c, Passenger& p, double km);
public:
	//Default constructor
	Driver() :_name(""), _lisence(""), _totalincome(0.0), _totaltrip(0) {}

	//Param constructor
	Driver(string name, string lisence, double totalincome, int totaltrip) {
		this->_name = name;
		this->_lisence = lisence;
		this->_totalincome = totalincome;
		this->_totaltrip = totaltrip;
	}

	//Set Income
	void setIncome(double Income) {
		_totalincome = Income;
	}
	
	//Total Income
	double getTotalIncome() {
		return _totalincome;
	}

	//AcceptTrip
	void acceptTrip() {
		cout << "Sifaris qebul edildi.\n";
		_totalincome += 20;
	}

	//Show Driver Info
	void showDriverInfo() {
		cout << "Name: " << _name << endl;
		cout << "Lisence: " << _lisence << endl ;
		cout << "Total Income: " << getTotalIncome() << endl;
		cout << "Total trip: " << _totaltrip << endl;
		cout << "--------------------------------------\n";
	}

	friend ostream& operator<<(ostream& print, const Driver& d) {
		print << "[" << d._name << "] Lisenziya: " << d._lisence << " | Qazanc: " << d._totalincome <<
			" AZN | Sefer: " << d._totaltrip << endl;
		return print;
	}

	


	
};

class Company {
private:
	string _companyName;
	int _komisyon;
	vector<Driver> _Drivers;
	int _countd;

	friend void completeTrip(Driver& d, Company& c, Passenger& p, double km);
public:
	//Default constructor
	Company() :_companyName(""), _komisyon(20) {}

	//Param constructor
	Company(string companyname, int komisyon) {
		this->_companyName = companyname;
		this->_komisyon = komisyon;
	}

	//Add Drivers
	void addDriver(Driver& d) {
		double orginalIncome = d.getTotalIncome();
		double komIncome = orginalIncome - ((orginalIncome * _komisyon) / 100.0);
		d.setIncome(komIncome);
		_Drivers.push_back(d);
		_countd++;
	}

	//Show drivers
	void showDirvers() {
		cout << "\033[31mDrivers of " << _companyName << " Company\033[0m" << endl;
		for (auto& driver : _Drivers) {
			driver.showDriverInfo();
		}
	}

	//<<
	friend ostream& operator<<(ostream& print, const Company& obj) {
		print << "[" << obj._companyName << "] Komisyon: " << obj._komisyon <<
		" % | Surucu sayi: " <<
		obj._countd << endl;
		return print;
	}
};

class Passenger {
private:
	string _passangerName;
	double _balance;

	friend void completeTrip(Driver& d, Company& c, Passenger& p, double km);

public:
	//Default constructor
	Passenger():_passangerName(""),_balance(0.0){}

	//Param construtor
	Passenger(string passangername, double balance) {
		this->_passangerName = passangername;
		this->_balance = balance;
	}

	void pay(double km) {
		double price = km * 0.5;
		if (price > _balance) {
			cout << "Yeterli mebleg yoxdur.\n";
			return;
		}
		_balance -= price;
	}

	friend ostream& operator<<(ostream& print, const Passenger& p) {
		print << "[" << p._passangerName << "] | Balance: " << p._balance << " AZN\n";
		return print;
	}
};

//Complete Trip
void completeTrip(Driver& d, Company& c, Passenger& p, double km) {
	double price = km * 0.5;
	if (price > p._balance) {
		cout << "\033[31mYeterli mebleg yoxdur.\033[0m\n";
		return;
	}
	p._balance -= price;
	double odenilecek = price;
	double compay = (odenilecek * c._komisyon) / 100.0;
	double driverpay = odenilecek - ((odenilecek * c._komisyon) / 100.0);
	cout << "\033[32m---Sefer Tamamlandi---\033[0m\n";
	cout << "Surucu: " << d._name << endl;
	cout << "Sernisin: " << p._passangerName << endl;
	cout << "Mesafe: " << km << " km\n";
	cout << "Umumi: " << price << " AZN\n";
	cout << c._companyName << " pay: " << compay << " AZN(20%)\n";
	cout << "Driver Pay: " << driverpay << " AZN\n";
	cout << "-------------------\n";
	cout << "[" << d._name << "] Lisenziya: " << d._lisence << " | Qazanc: " 
	<< driverpay << " AZN | Total Sefer: " << d._totaltrip << endl;
	cout << "[" << p._passangerName << "] Balans: " << p._balance << " AZN\n";
	cout << "[" << c._companyName << "] Komisyon: " << c._komisyon << " % | Surucu sayi: " << c._countd << endl;
	
}

template <typename T>
class BoltPool {
public:
	vector <T> Pool;

	

	void add(T a) {
		Pool.push_back(a);
	}

	void show() {
		for (const auto& a : Pool) {
			cout << a << endl;
		}
	}

	void remove() {
		Pool.clear();
		cout << "Hovuz Bosaldildi.\n";
	}
};

int main() {
	//Drivers
	Driver d1("Kamil Nebizade", "AZ-1023", 340.00, 25);
	Driver d2("Tural Abiszade", "AZ-1098", 546.40, 34);
	Driver d3("Vasif Zeynalov", "AZ-1056", 140.26, 16);
	Driver d4("Akif Agali", "AZ-1032", 321.00, 23);
	
	cout << d1;
	//Company
	Company c1("Bolt", 20);
	Company c2("Yango", 30);
	//Passengers
	Passenger p1("Vuqar Ramazanov", 320);
	cout << p1;
	p1.pay(9);
	cout << p1;
	//Add drivers to company
	c1.addDriver(d1);
	c1.addDriver(d2);
	c2.addDriver(d3);
	c2.addDriver(d4);
	//Show  drivers of company
	cout << c1;
	cout << c2;
	cout << endl;
	c1.showDirvers();
	c2.showDirvers();
	//d1.acceptTrip();
	//Complete Trip
	completeTrip(d1, c1, p1, 120.8);
	BoltPool<Driver> bp1;
	BoltPool<Passenger> bp2;
	bp1.add(d1);
	bp1.add(d2);
	bp1.add(d3);
	bp2.add(p1);
	cout << "\nHovuz sakinleri\n";
	bp1.show();
	bp2.show();
	bp1.remove();
	bp2.remove();

	return 0;
}