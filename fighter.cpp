#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
class Fighter {
public:
	string name;
	short health;
	short damage;

	void attack(Fighter& enemy) {
		while (damage < 10 || damage > 30) {
			cout << "10-30 arasi damage daxil edin: ";
			cin >> damage;
		}
		enemy.health -= damage;
		if (enemy.health <= 0) {
			enemy.health = 0;
			cout << "\n" << name << " qazandi.\n";
			return;
		}
	}
};
int main() {
	srand(time(NULL));
	Fighter A, B;
	A.health = 100;
	B.health = 100;
	B.name = "Enemy";
	cout << "Name: ";
	cin >> A.name;
	while (true) {
		cout << "\nA damage: ";
		cin >> A.damage;
		A.attack(B);
		cout << A.name << " " << A.damage << " damage zerbe vurdu!\n";
		cout << B.name << " health : " << B.health << endl;
		if (B.health <= 0) break;
		B.damage = (rand() % 21) + 10;
		cout << "B damage: " << B.damage << endl;
		B.attack(A);
		cout << B.name << " " << B.damage << " damage zerbe vurdu!\n";
		cout << A.name << " health: " << A.health << endl;
		if (A.health <= 0)break;
	}

	return 0;
}