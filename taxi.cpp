#include <iostream>
using namespace std;
class Taxi {
private:
	float baseFare = 3;
	float perKm = 0.5;
public:
	float distance;

	float clculateFare(float distance) {
		float mebleg;
		mebleg = baseFare + (perKm * distance);
		return mebleg;
	}
};
int main() {
	Taxi t1;
	cout << "Gedecek mekanin mesafesi: ";
	cin >> t1.distance;
	cout << "Umumi mebleg: " << t1.clculateFare(t1.distance) << " AZN" << endl;
	return 0;
}