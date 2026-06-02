#include <iostream>
using namespace std;

class Vehicle {
public:
	string brand;
	int speed;

	Vehicle(string b, int s) :brand(b), speed(s) {}
	virtual void showInfo() {
		cout << "Brand: " << brand << " | Speed: " << speed << endl;
	}
};

class Car :virtual public Vehicle {
public:
	
	Car(string b, int s) :Vehicle(b, s) {}
	void drive() {
		cout << "Mashin surmeye basladi..\n";
	}
};

class Boat :virtual public Vehicle {
public:
	Boat(string b, int s) :Vehicle(b, s) {}
	void sail() {
		cout << "Gemi yelken acdi..\n";
	}
};

class AmphibiousVehicle :public Car, public Boat {
public:
	AmphibiousVehicle(string b, int s) :Vehicle(b, s), Car(b,s),Boat(b,s) {}
	void showInfo() override {
		cout << "Brand: " << brand << " | Speed: " << speed << endl;
		drive();
		sail();
	}
};

int main() {
	AmphibiousVehicle av("Mercedes",400);
	av.showInfo();
	return 0;
}
// virtual inheritance olmasaydi diamond problemi bas vererdi. Yeni iki toreme class ortaq base classdan 
// torendiyi ucun ve diger classda bu iki toreme classdan torendiyi ucun ve her iki toreme classda eyni metod
//oldugu ucun kompilyator chashbash qalacaqdi. Buda diamond problemi adlanir.