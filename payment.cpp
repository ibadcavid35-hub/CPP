#include <iostream>
using namespace std;

class Payment {
public:
	virtual void pocessPayment(double amount) = 0;
	virtual void validatePayment() = 0;
	virtual void getPaymentType() = 0;
	virtual void showReceipt() {
		cout << "Receipt\n";
	}
	virtual void logTransaction() {
		cout << "Payment History\n";
	}

	virtual ~Payment() = 0;
};

Payment::~Payment() {
	cout << "[Payment] odeme sinfi silindi\n";
}

class CashPayment :public Payment {
public:
	void pocessPayment(double amount) override {
		cout << "[Negd] " << amount << " AZN odendi.\n";
	}
	void validatePayment() {
		cout << "Pul etibarlidir.\n";
	}
	void getPaymentType() {
		cout << "Bu nagd odenisdir.\n";
	}

	~CashPayment() {
		cout << "[Cash] odeme sinfi silindi\n";
	}
};

class CardPayment :public Payment {
public:
	void pocessPayment(double amount) override final {
		cout << "[Kart] 5239 1517 4532 5465 ile " << amount << " AZN odendi.\n";
	}
	void validatePayment() {
		cout << "Kartda yeterince mebleg var.\n";
	}
	void getPaymentType() {
		cout << "Bu kartla odenisdir.\n";
	}

	void logTransaction() {
		cout << "Card History\n";
	}

	~CardPayment() {
		cout << "[Card] odeme sinfi silindi\n";
	}

};

class OnlinePayment :public Payment {
public:
	void pocessPayment(double amount) override {
		cout << "[Online] PayPal ile " << amount << " AZN odendi.\n";
	}
	void validatePayment() {
		cout << "Hesab aktivdir.\n";
	}
	void getPaymentType() {
		cout << "Bu onlayn odenisdir.\n";
	}
	~OnlinePayment() {
		cout << "[Online] odeme sinfi silindi\n";
	}
};

class PremiumCardPayment : public CardPayment {
public:
	//void pocessPayment(double amount) override {
	//	cout << "[Online] PayPal ile " << amount << " AZN odendi.\n"; XETA!!!
	//}
};

int main() {
	Payment* payments[3];

	payments[0] = new CashPayment();
	payments[1] = new CardPayment();
	payments[2] = new OnlinePayment();

	double amo = 300.0;
	for (int i = 0;i < 3;i++) {
		payments[i]->pocessPayment(amo);
		payments[i]->getPaymentType();
		payments[i]->validatePayment();
		payments[i]->showReceipt();
		cout << endl;
		amo += 100.0;
	}

	payments[1]->logTransaction();
	//Virtual keywordu olmasaydi proqram bir pointerin gosterdiyi obyektin hansi sinife aid oldugunu
	//ve hansi metodu cagirmali oldugunu bilmezdi.
	for (int i = 0;i < 3;i++) {
		delete[] payments[i];
	}

	return 0;
}