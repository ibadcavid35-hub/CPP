#include <iostream>;
#include <cstdlib>
#include <ctime>
using namespace std;
class Device {
public:
	short battery;
	void use() {
		short neg = rand() % 11;
		if (battery > neg) {
			battery-=neg;
			cout << battery;
		}
		else {
			cout << "Telfon sondu.\n";
		}
	}
	void charge() {
		short pos = rand() % 11;
		if (battery >= 0 && battery <= (100 - pos)) {
			battery += pos;
			cout << battery;
		}
		else {
			cout << "Bateriya doludu.\n";
		}
	}
	void fullCahrge(){
		if (battery < 100) {
			battery = 100;
			cout << battery;
		}
	}
};
int main() {
	srand(time(0));
	Device d;
	d.battery = rand() % 101;
	char secim;
	while (true) {
		cout << "\nUse-u\n";
		cout << "Cahrge-c\n";
		cout << "Full Cahrge-f\n";
		cout << "Exit-e\n";
		cin >> secim;
		switch (secim) {
		case 'u':
			d.use();
			break;
		case 'c':
			d.charge();
			break;
		case 'f':
			d.fullCahrge();
			break;
		case 'e':
			cout << "EXIT...\n";
			return 0;
		default:
			cout << "Wrong..\n";

		}
	}
	return 0;
}