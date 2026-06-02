#include <iostream>
using namespace std;
class Car {
public:
	string brand;
	string model;
	short speed;
private:
	bool isAvailable = true;
public:
	void rent() {
		if (isAvailable) {
			cout << "Mashin ugurla icareye verildi.\n";
			isAvailable = false;
		}
		else {
			cout << "Bu mashin artiq icarededir.\n";
		}
	}

	void returnCar() {
		if (!isAvailable) {
			cout << "Mashin geri qaytaildi.\n";
			isAvailable = true;
		}
		else {
			cout << "Mahin zaten bosdur.\n";
		}
	}
	void showStatus() {
		cout << "\033[1;32m========================\n";
		cout << "==" << brand << "Info==" << endl;
		cout << "=============================\033[0m\n";
		cout << "Brand: " << brand << endl;
		cout << "Model: " << model << endl;
		cout << "Speed: " << speed << endl;
		if (isAvailable) cout << "Icareye hazirdir.\n";
		else cout << "Tesufki masin icareye verilib.\n";
	}

	void add() {
		cout << "Brand: ";
		cin >> brand;
		cout << "Model: ";
		cin >> model;
		cout << "Speed: ";
		cin >> speed;
		while (speed < 0 || speed >250) {
			if (speed < 0) {
				cout << "0-dan kichik ola bilmez.\n";
				cin >> speed;
			}
			else if (speed > 250) {
				cout << "250-den chox ola bilmez.\n";
				cin >> speed;
			}
		}
	}
};

int main() {
	Car Mers,Bmw;
	Mers.add();
	Mers.showStatus();
	Mers.rent();
	Mers.returnCar();
	return 0;
}
