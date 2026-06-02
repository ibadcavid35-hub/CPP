#include <iostream>
#include <string>

using namespace std;

class Account;

//class Transaction
class Transaction {
public:
	string date;
	double amount;
	string type;
	Transaction(): date(""),amount(0.0),type(""){}
	//Param constructor
	Transaction(string date, double amount, string type) {
		this->date = date;
		this->amount = amount;
		this->type = type;
	}


	//ostream
	friend ostream& operator<<(ostream& print, Transaction& obj) {
		string sithdep = (obj.type == "Deposit") ? "+" : "-";
		print << "[" << obj.date << "] " << obj.type << " --- " << sithdep << obj.amount << " AZN\n";
		return print;
	}
};

//class Auditor
class Auditor {
public:
	void generateReport(Account& acc);
	void sendEmail(string msg) {
		cout << msg;
	}
};

//class Account
class Account {
private:
	string owner;
	double balance;
	string accountNumber;
	friend void transfer(Account& from, Account& to, double amount);
	Transaction history[50];
	friend class Bank; //Bank friend class
	int historyCount = 0;
public: 

	friend void Auditor::generateReport(Account& acc);
	//Default constructor
	Account() :balance(0.0) {}
	//Param constructor
	Account(string owner, string accNo, double balance) {
		this->owner = owner;
		this->accountNumber = accNo;
		this->balance = balance;
	}

	//Deposit
	void deposit(double amount) {
		if (amount < 0) {
			cout << "Mebleg menfi ola bimez.\n";
			return;
		}
		this->balance += amount;
		if (historyCount < 50) {
			history[historyCount++] = Transaction("07-05-2026", amount, "Deposit");
		}
	}

	//Withdraw
	void withdraw(double amount) {
		if (amount > this->balance) {
			cout << "Balansda yeterli mebleg yoxdur.\n";
			return;
		}
		if (amount < 0) {
			cout << "Mebleg menfi ola bimez.\n";
			return;
		}
		this->balance -= amount;
		if (historyCount < 50) {
			history[historyCount++] = Transaction("07-05-2026", amount, "Withdraw");
		}
	}
	//ostream
	friend ostream& operator<<(ostream& print, Account& obj) {
		print << "[" << obj.accountNumber << "] " << obj.owner << " --- Balans: " << obj.balance << " AZN\n";
		return print;
	}
	//istream
	friend istream& operator>>(istream& input, Account& obj) {
		cout << "Owner: ";
		input.ignore();
		getline(input, obj.owner);
		cout << "AccountNumber: ";
		getline(input, obj.accountNumber);
		cout << "Balance: ";
		input >> obj.balance;
		cout << endl;
		return input;
	}

};


//Transfer
void transfer(Account& from, Account& to, double amount) {
	if (amount < 1) {
		cout << "En az 1 AZN olmalidir.\n";
		return;
	}
	if (amount > from.balance) {
		cout << "Balansda yeterli mebleg yoxdur.\n";
		return;
	}
	from.balance -= amount;
	to.balance += amount;
	cout << "Vesaiti gonderen: " << from.owner << endl;
	cout << "Vesaiti alan: " << to.owner << endl;
	cout << "Vesait: " << amount << " AZN" << endl;
	cout << "Vesaiti veeren shexsin balans: " << from.balance << " AZN" << endl;
	cout << "Vesaiti alan shexsin balans: " << to.balance << " AZN" << endl;
}


//Bank class
class Bank {
public:
	//print All Accounts
	void printAllAccounts(Account accounts[], int n) {
		cout << "\n--- Bankdaki Hesablar ---\n";
		for (int i = 0;i < n;i++) {
			cout << accounts[i] << endl;
		}
		cout << endl << endl;
	}

	void findRichest(Account accounts[], int n) {
		double max = accounts[0].balance;
		string own = accounts[0].owner;
		for (int i = 0;i < n;i++) {
			if (accounts[i].balance > max) {
				max = accounts[i].balance;
				own = accounts[i].owner;
			}
		}
		cout << "Varli shexs: " << own << endl << "Balans: " << max << " AZN\n";
	}

	void printHistory(Account& acc) {
		cout << "\n=== " << acc.accountNumber << " Emeliyyat tarixi ===\n";
		for (int i = 0;i < acc.historyCount;i++) {
			cout << acc.history[i] << endl;
		}
		cout << "Cemi emiliyyat: " << acc.historyCount << endl;
		cout << "===================================\n";
	}

	//Apply Interest
	void applyInterest(Account& acc, double rate) {
		acc.balance += (acc.balance * rate) / 100;
	}

	//Get Total Balance
	double getTotalBalance(Account accounts[], int n) {
		double totalbal = 0.0;
		for (int i = 0;i < n;i++) {
			totalbal += accounts[i].balance;
		}
		return totalbal;
	}
};

//Hesabat
void Auditor::generateReport(Account& acc) {
	cout << "===Audit Hesabati===\n";
	cout << "Hesab: " << acc.accountNumber << endl ;
	cout << "Sahib: " << acc.owner << endl;
	cout << "Balans: " << acc.balance << " AZN" << endl;
	cout << "Status: Aktiv" << endl;
	cout << "=======================\n";
}

int main() {
	Account accounts[2];
	Bank b;
	Auditor a;
	cin >> accounts[0];
	cin >> accounts[1];
	cout << accounts[0];
	cout << accounts[1];
	accounts[0].deposit(20); //deposit
	cout << accounts[0];
	accounts[1].withdraw(20); //withdraw
	cout << accounts[1];
	double totalbalans = b.getTotalBalance(accounts, 2);
	cout << "\nTotal balans: " << totalbalans << endl; //total balans
	b.applyInterest(accounts[0], 30); //rate
	cout << accounts[0];
	b.printAllAccounts(accounts, 2); //print all accounts
	transfer(accounts[0], accounts[1], 20);//transfer
	a.generateReport(accounts[0]); //Generate report
	b.printHistory(accounts[0]);//Emeliyyatlar
	b.printHistory(accounts[1]);//Emeliyyatlar
	b.findRichest(accounts, 2);//Find richest

	

	return 0;
}