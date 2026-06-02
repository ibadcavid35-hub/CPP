#include <iostream>
using namespace std;

class Aircraft {
public:
	string type;
	string registration_number;
	string model;
	int max_passenger_count;
	int max_flight_distance;
	Aircraft(string t, string r, string m, int mp, int mf) :
	type(t), registration_number(r), model(m), max_passenger_count(mp), max_flight_distance(mf) {}

	virtual void fly() = 0;
	virtual void land() = 0;
	virtual void getType() = 0;

	virtual void showInfo() {
		cout << "\n==== [" << type << "] Info ====\n";
		cout << "Registration number: " << registration_number << endl;
		cout << "Model: " << model << endl;
		cout << "Max Passenger count: " << max_passenger_count << endl;
		cout << "Max Flight distance: " << max_flight_distance << endl;
		cout << "================================\n";
	}

	virtual ~Aircraft() = 0;
};

Aircraft::~Aircraft() {
	cout << "Aircraft abstraction classi silindi.\n";
}

class PassangerPlane :public Aircraft {
public:
	int biznesclass;

	PassangerPlane(string t, string r, string m, int mp, int mf, int b) 
	:Aircraft(t, r, m, mp, mf), biznesclass(b) {}

	void fly() override {
		cout << "Sernisin teyyaresi [" << model << "] ucucu\n";
	}

	void land() override {
		cout << "Sernisin teyyaresi enis etdi.\n";
	}

	void getType() override {
		cout << "Type: Passanger Plane.\n";
	}

	virtual void showInfo() override {
		cout << "\n==== [" << type << "] Info ====\n";
		cout << "Registration number: " << registration_number << endl;
		cout << "Model: " << model << endl;
		cout << "Max Passenger count: " << max_passenger_count << endl;
		cout << "Bizness class: " << biznesclass << endl;
		cout << "Econom class: " << max_passenger_count - biznesclass << endl;
		cout << "Max Flight distance: " << max_flight_distance << " km" << endl;
		cout << "================================\n";
	}
};

class CargoPlane :public Aircraft {
public:
	string company;

	CargoPlane(string t, string r, string m, int mp, int mf, string c) :
		Aircraft(t, r, m, mp, mf), company(c) {}

	void fly() override {
		cout << "Yuk teyyaresi [" << model << "] malu ile ucucu\n";
	}

	void land() override {
		cout << "Yuk teyyaresi enis etdi.\n";
	}

	void getType() override {
		cout << "Type: Cargo Plane.\n";
	}

	virtual void showInfo() override {
		cout << "\n==== [" << type << "] Info ====\n";
		cout << "Company: " << company << endl;
		cout << "Registration number: " << registration_number << endl;
		cout << "Model: " << model << endl;
		cout << "Max Passenger count: " << max_passenger_count << endl;
		cout << "Max Flight distance: " << max_flight_distance << " km" << endl;
		cout << "================================\n";
	}
};

class PrivateJet :public Aircraft {
public:
	string owner;

	PrivateJet(string t, string r, string m, int mp, int mf, string o) :
		Aircraft(t, r, m, mp, mf), owner(o) {}

	void fly() override {
		cout << "Ozel jet [" << model << "] - [" << owner << "] ucun ucucu\n";
	}

	void land() override {
		cout << "Ozel jet enis etdi.\n";
	}

	void getType() override {
		cout << "Type: Private Jet.\n";
	}
	virtual void showInfo() override {
		cout << "\n==== [" << type << "] Info ====\n";
		cout << "Registration number: " << registration_number << endl;
		cout << "Model: " << model << endl;
		cout << "Owner: " << owner << endl;
		cout << "Max Passenger count: " << max_passenger_count << endl;
		cout << "Max Flight distance: " << max_flight_distance << " km" << endl;
		cout << "================================\n";
	}
};

enum Sinif {
	ECONOMY,
	BUSINESS,
	FIRST
};

class Ticket;
class Passanger {
public:
	string passanger_name;
	string passport_number;
	double balance;

	Passanger(string p1, string p2, double b) :passanger_name(p1), passport_number(p2), balance(b) {}

	void buyTicket(Ticket& t);

	friend ostream& operator<<(ostream& print, const Passanger& p) {
		print << "[" << p.passanger_name << "] " <<
			"[" << p.passport_number << "]" << " Balance: " << p.balance << " AZN\n";
		return print;
	}

};

class Ticket {
public:
	Passanger pas;
	string ticket_number;
	string flight_number;
	Sinif sinif;
	double price;

	friend class Passanger;
	friend void Passanger::buyTicket(Ticket& t);

	struct Seat {
		string sira_nomresi;
		char yer_herfi;
	};

	Seat seat;

	string sinifsec(Sinif s) const {
		switch (s) {
		case ECONOMY: return "ECONOMY";
		case BUSINESS: return "BUSINESS";
		case FIRST: return "FIRST";
		default: return "UNKNOWN";
		}
	}

	Ticket(Passanger& p, string t, string f, Sinif s, double pr) :
		pas(p), ticket_number(t), flight_number(f), sinif(s), price(pr) {}

	friend ostream& operator<<(ostream& print, const Ticket& t) {
		print << t.pas << "Ticket number: " << t.ticket_number << " | Flight number: " << t.flight_number <<
		"\nClass: " << t.sinifsec(t.sinif) << " | Sira nomresi: " << t.seat.sira_nomresi << " | Yer herfi: " << t.seat.yer_herfi
		<< "\nPrice: " << t.price << " AZN\n";
		return print;
	}

};

void Passanger::buyTicket(Ticket& t) {
	if (t.price < 0) {
		cout << "Mebleg menfi ola bilmez.\n";
		return;
	}
	if (t.price > balance) {
		cout << "Balans kifayt deyil.\n";
		return;
	}
	else {
		balance -= t.price;
	}
}

enum Status {
	SCHEDULED,
	BOARDING,
	INFLIGHT,
	LANDED,
	CANCELLED
};

class Flight {
public:
	string flight_number;
	Aircraft* airc;
	string kalkiscity;
	string eniscity;
	string kalkissaati;
	Status status;
	Ticket* sernisinler[220];
	int countser = 0;

	string getStatus(Status s) const {
		switch (s) {
		case SCHEDULED: return "SCHEDULED";
		case BOARDING: return "BOARDING";
		case INFLIGHT: return "INFLIGHT";
		case LANDED: return "LANDED";
		case CANCELLED: return "CANCELLED";
		default: return "UNKNOWN";
		}
	}

	Flight(string fn, Aircraft* a, string k, string e, string ka, Status s) :flight_number(fn)
		, airc(a),kalkiscity(k), eniscity(e), kalkissaati(ka), status(s) {}

	~Flight() {
		delete airc;
	}

	void addPassanger(Ticket& t) {
		if (countser < 50) {
			sernisinler[countser] = &t;
			countser++;
		}
		else {
			cout << "Flight full.\n";
		}
	}

	void departFly() {
		if (status == CANCELLED) {
			cout << flight_number << " nomreli ucus legv edildiyinen teyyare uca bilmez.\n";
			return;
		}
		status = INFLIGHT;
		cout << "Teyyare ucusa baslayir!\n";
		airc->fly();
	}

	void landFlight() {
		if (status == INFLIGHT) {
			cout << "Teyyare enis edir...\n";
			status = LANDED;
			cout << "Teyyare enis etdi!\n";
			airc->land();
		}
	}

	void cancelFlight() {
		if (status == SCHEDULED) {
			cout << "Ucus legv edilir!\n";
			status = CANCELLED;
		}
	}

	void showManifest() {
		cout << "\n===Sernisinler===\n";
		for (int i = 0;i < countser;i++) {
			cout << i + 1 << ". " << *(sernisinler[i]) << endl;
			cout << "-----------------------------\n";
		}
		cout << "=====================\n";
	}

	friend ostream& operator<<(ostream& print, const Flight& fl) {
		print << "[" << fl.flight_number << "] " << fl.kalkiscity << " -> " << fl.eniscity << endl <<
			"Teyyare: " << fl.airc->model << " | Sernisin: " << fl.countser << '/' << fl.airc->max_passenger_count << endl
			<< "Status: " << fl.getStatus(fl.status) << endl;
		return print;
	}
	
};

class Airport {
public:
	class Adress {
	public:
		string havalimanadi;
		string city;

		Adress(string h, string c) :havalimanadi(h), city(c) {}
	};
	Adress address;

	Aircraft* teyyareler[50];
	Flight* flights[50];
	int acount = 0;
	int fcount = 0;

	Airport(Adress a, Aircraft* tey, Flight* fl) :address(a), teyyareler(tey), flights(fl) {}

	void addAircraft(Aircraft* tey) {
		if (acount >= 50) {
			cout << "Full\n";
			return;
		}
		teyyareler[acount++] = tey;
		cout << "[" << tey->model << "]\n";
	}

	void addFlight(Flight* fl) {
		if (fcount >= 50) {
			cout << "Full.\n";
			return;
		}
		flights[fcount++] = fl;
		cout << "[" << fl->flight_number << "]\n";
	}

	void showAllFlights() const {
		cout << "\n===== Flights ===\n";
		for (int i = 0; i < fcount; i++) {
				cout << *flights[i] << "\n";
		}
	}

};

template <typename T>
class FlightBoard {
public:
	T board[50];
	int count = 0;

	FlightBoard() :count(0) {}

	void add(T element) {
		if (count < 50) {
			board[count] = element;
			count++;
		}
		else {
			cout << "Board is full!\n";
		}
	}

	T getByIndex(int index) {
		if (index >= 0 && index < count) {
			return board[index];
		}
		else {
			cout << "Yanlish indeks.\n";
			return T();
		}
	}

	void printAll() {
		cout << "\n===Uchush cedveli===\n";
		for (int i = 0;i < count;i++) {
			cout << *(board[i]) << endl;
		}
		cout << "===================\n";
	}
};



int main() {
	Aircraft* ar1 = new PassangerPlane("Passanger Plane", "N949AK", "Boeing 737 MAX 9", 220, 6570, 16);
	ar1->fly();
	ar1->land();
	ar1->getType();
	ar1->showInfo();
	Passanger p1("Elvin Memmedov", "C04578231", 2930.45);
	Passanger p2("Qasim Memmedov", "C04578231", 2930.45);
	Passanger p3("Tural Memmedov", "C04578231", 2930.45);
	Ticket t1(p1, "176-4829175630", "J2 823", FIRST, 487.90);
	Ticket t2(p2, "176-4829175630", "J2 823", ECONOMY, 487.90);
	Ticket t3(p3, "176-4829175630", "J2 823", BUSINESS, 487.90);
	t1.seat.sira_nomresi = "18F";
	t1.seat.yer_herfi = 'F';
	cout << t1;
	Flight f1("AZ4721", ar1, "Baku", "Istanbul", "19:00", INFLIGHT);
	Flight f2("AZ4721", ar1, "Baku", "Istanbul", "19:00", CANCELLED);
	f1.addPassanger(t1);
	f1.addPassanger(t2);
	f1.addPassanger(t3);
	cout << f1;
	f1.showManifest();
	FlightBoard<Flight*> ucusLovhesi;
	ucusLovhesi.add(&f1);
	ucusLovhesi.add(&f2);
	ucusLovhesi.printAll();
	Airport::Adress adr1("Haydar Aliyev Airport", "Baku");
	Airport aer1(adr1, ar1, &f1);
	aer1.addAircraft(ar1);
	aer1.addFlight(&f1);
	aer1.showAllFlights();
	


	return 0;
}