#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

//Exception class
class DoctorNotFoundException :public exception {
public:
	const char* what() const noexcept override {
		return "Doctor not found.\n";
	}
};

class PatientNotFoundException :public exception{
public:
	const char* what() const noexcept override {
		return "Patient not found.\n";
	}
};

class RoomFullException :public exception {
public:
	const char* what() const noexcept override {
		return "The room is full.\n";
	}
};

class InvalidAppointmentException :public exception {
public:
	const char* what() const noexcept override {
		return "Appointment history is not found.\n";
	}
};

class InsufficientFundsException :public exception {
public:
	const char* what() const noexcept override {
		return "There is not enough money in the balance.\n";
	}
};

class FileException :public exception {
public:
	const char* what() const noexcept override {
		return "File operation failed.\n";
	}
};

class Person {
protected:
	string _name;
	string _surname;
	string _birth_date;
	string _phone_number;
	string _email;
public:
	Person(string name, string surname, string birth_date, string phone_number, string email):
	_name(name),_surname(surname),_birth_date(birth_date),_phone_number(phone_number),_email(email) {}

	virtual ~Person() {}

	string getName() const {
		return _name;
	}

	string getSurname() const {
		return _surname;
	}

	virtual void getInfo() = 0;
};

class Patient :public Person {
private:
	string _passport_number;
	string _blood_type;
	string _medical_history;
	bool _insurance;
public:
	Patient(string name, string surname, string birth_date, string phone_number, string email,
		string passport_number, string blood_type, string medical_history, bool insurance) :
		Person(name, surname, birth_date, phone_number, email),_passport_number(passport_number),
	_blood_type(blood_type),_medical_history(medical_history),_insurance(insurance) {}

	~Patient() {}


	string getPassportNumber() const { return _passport_number; }

	string getBloodType() const { return _blood_type; }

	string getMedicalHistory() const { return _medical_history; }

	bool getInsurance() const { return _insurance; }

	void getInfo() override {
		cout << "\n\033[33m===== PATIENT INFO =====\033[0m\n";
		cout << "\033[36mName:\033[0m " << _name << endl;
		cout << "\033[36mSurname:\033[0m " << _surname << endl;
		cout << "\033[36mBirth date:\033[0m " << _birth_date << endl;
		cout << "\033[36mPhone number:\033[0m " << _phone_number << endl;
		cout << "\033[36mEmail:\033[0m " << _email << endl;
		cout << "\033[36mPassport number:\033[0m " << getPassportNumber() << endl;
		cout << "\033[36mBlood type:\033[0m " << getBloodType() << endl;
		cout << "\033[36mMedical history:\033[0m " << getMedicalHistory() << endl;
		cout << "\033[36mHas insurance: \033[0m"; cout << (getInsurance() ? "Exist\n" : "Not exist\n");
		cout << "\033[33m========================\033[0m\n";
	}

	void loadAll(string fname) {
		ifstream rfile(fname);
		if (!rfile.is_open()) throw FileException();
		else {
			string line;
			while (getline(rfile, line)) {
				cout << line << endl;
			}
			rfile.close();
		}
	}

	void saveAll(string fname) {
		ofstream wfile(fname, ios::app);
		if (!wfile.is_open()) throw FileException();
		else {
			wfile << _name << " " << _surname << " | Birth Date: " << _birth_date << " | Blood: " << _blood_type << " | Email: " << _email << endl;
		}
	}
};

class Staff :public Person {
private:
	string _employee_number;
	string _position;
	string _start_date;
	double _salary;
public:
	Staff(string name, string surname, string birth_date, string phone_number, string email,
		string employee_number, string position, string start_date, double salary) :
		Person(name, surname, birth_date, phone_number, email), _employee_number(employee_number),
		_position(position), _start_date(start_date), _salary(salary) {}

	~Staff() {}


	string getEmployeeNumber() const { return _employee_number; }

	string getPosition() const { return _position; }

	string getStartDate() const { return _start_date; }

	double getSalary() const { return _salary; }

	void getInfo() override {
		cout << "\n\033[33m===== Staff Info =====\033[0m\n";
		cout << "\033[36mName: \033[0m" << _name << endl;
		cout << "\033[36mSurname:\033[0m " << _surname << endl;
		cout << "\033[36mBirth date:\033[0m " << _birth_date << endl;
		cout << "\033[36mPhone number:\033[0m " << _phone_number << endl;
		cout << "\033[36mEmail:\033[0m " << _email << endl;
		cout << "\033[36mEmployee number:\033[0m " << getEmployeeNumber() << endl;
		cout << "\033[36mPosition:\033[0m " << getPosition() << endl;
		cout << "\033[36mStart date:\033[0m " << getStartDate() << endl;
		cout << "\033[36mSalary:\033[0m " << getSalary() << " $" << endl;
		cout << "\033[33m======================\033[0m\n";
	}
};

class Doctor :public Staff {
private:
	string _specialty;
	string _license_number;
	string _reception_hours;
public:
	Doctor(string name, string surname, string birth_date, string phone_number, string email,
		string employee_number, string position, string start_date, double salary,
		string speciality, string license_number, string reception_hours) :
		Staff(name, surname, birth_date, phone_number, email, employee_number, position, start_date, salary),
		_specialty(speciality), _license_number(license_number), _reception_hours(reception_hours) {}

	~Doctor() {}

	string getSpecialty() const { return _specialty; }

	string getLicenseNumber() const { return _license_number; }

	string getReceptionHours() const { return _reception_hours; }

	void getInfo() override {
		cout << "\n\033[33m===== Doctor Info =====\033[0m\n";
		cout << "\033[36mName:\033[0m " << _name << endl;
		cout << "\033[36mSurname:\033[0m " << _surname << endl;
		cout << "\033[36mBirth date:\033[0m " << _birth_date << endl;
		cout << "\033[36mPhone number:\033[0m " << _phone_number << endl;
		cout << "\033[36mEmail:\033[0m " << _email << endl;
		cout << "\033[36mEmployee number:\033[0m " << getEmployeeNumber() << endl;
		cout << "\033[36mPosition:\033[0m " << getPosition() << endl;
		cout << "\033[36mStart date:\033[0m " << getStartDate() << endl;
		cout << "\033[36mSalary:\033[0m " << getSalary() << " $" << endl;
		cout << "\033[36mSpeciality:\033[0m " << getSpecialty() << endl;
		cout << "\033[36mLicense number:\033[0m " << getLicenseNumber() << endl;
		cout << "\033[36mReception hours:\033[0m " << getReceptionHours() << endl;
		cout << "\033[33m=======================\033[0m\n";
	}

	void loadAll(string fname) {
		ifstream rfile(fname);
		if (!rfile.is_open()) throw FileException();
		else {
			string line;
			while (getline(rfile, line)) {
				cout << line << endl;
			}
			rfile.close();
		}
	}

	void saveAll(string fname) {
		ofstream wfile(fname, ios::app);
		if (!wfile.is_open()) throw FileException();
		else {
			wfile <<"Dr." << _name << " " << _surname << " | Birth Date: " << _birth_date
				<<" | License number: " << _license_number << " | Specialty: " << _specialty << " | Email: " << _email << endl;
		}
	}
};

class Nurse :public Staff {
private:
	string _department;
public:
	struct Queue {
		string day;
		string queue;
		string nurse;
	};
	Queue _schedule[7];
	Nurse(string name, string surname, string birth_date, string phone_number, string email,
		string employee_number, string position, string start_date, double salary,
		string department, Queue schedule[7]) :
		Staff(name, surname, birth_date, phone_number, email, employee_number, position, start_date, salary),
		_department(department) {
		for (short int i = 0;i < 7;i++) {
			_schedule[i] = schedule[i];
		}
	}

	~Nurse() {}

	string getDepartment() const { return _department; }

	void getInfo() override {
		cout << "\n\033[33m===== Nurse Info =====\033[0m\n";
		cout << "\033[36mName:\033[0m " << _name << endl;
		cout << "\033[36mSurname:\033[0m " << _surname << endl;
		cout << "\033[36mBirth date:\033[0m " << _birth_date << endl;
		cout << "\033[36mPhone number:\033[0m " << _phone_number << endl;
		cout << "\033[36mEmail:\033[0m " << _email << endl;
		cout << "\033[36mEmployee number:\033[0m " << getEmployeeNumber() << endl;
		cout << "\033[36mPosition:\033[0m " << getPosition() << endl;
		cout << "\033[36mStart date:\033[0m " << getStartDate() << endl;
		cout << "\033[36mSalary:\033[0m " << getSalary() << " $" << endl;
		cout << "\033[36m\033[34mDepartment:\033[0m " << getDepartment() << endl;
		cout << "\033[33m======================\033[0m\n";
	}

	void getSchedule() const{
		for (short int i = 0;i < 7;i++) {
			cout << _schedule[i].day << " | " << _schedule[i].queue << " | " << _schedule[i].nurse << endl;
		}
	}
};

class Prescription {
private:
	class Medication {
	public:
		string pill;
		float dose;
		short number_of_intakes;
		Medication(string p, float d, short n) :pill(p), dose(d), number_of_intakes(n) {}
	};
	vector<Medication> _medication;
public:
	Prescription() {}
	~Prescription() {}

	void addMedication(string pill, float dose, short intakes) {
		_medication.push_back(Medication(pill, dose, intakes));
	}

	void showPrescription() const {
		if (_medication.empty()) {
			cout << "No medication has been prescribed.\n";
			return;
		}
		cout << "\033[35mPrescribed medications\033[0m\n";
		for (const auto& med : _medication) {
			cout << " \033[36m" << med.pill << "\033[0m\033[36m | Dose:\033[0m " << med.dose << "mg | " << med.number_of_intakes << " times/day\n";
		}
	}

};

class Appointment {
public:
	enum Status {
		Scheduled,
		InProgress,
		Completed,
		Cancelled
	};
private:
	Doctor* _doctor;
	Patient* _patient;
	string _date;
	string _hour;
	Status _status;
	Prescription _prescription;
public:
	Appointment(Doctor* doctor, Patient* patient, string date, string hour) :_doctor(doctor), _patient(patient), _date(date),
		_hour(hour), _status(Scheduled) {
	}

	~Appointment() {}


	const Doctor* getDoctor() const { return _doctor; }

	const Patient* getPatient() const { return _patient; }

	string getDate() const { return _date; }

	string getHour() const { return _hour; }

	const Prescription& getPrescription() const { return _prescription; }

	void completeAppointment(const Prescription& p) {
		_status = Completed;
		_prescription = p;
	}
	string getStatus() {
		switch (_status) {
		case Scheduled: return "Scheduled";
		case InProgress: return "InProgress";
		case Completed: return "Completed";
		case Cancelled: return "Cancelled";
		default: return "Unknown";
		}
	}

	void loadAll(string fname) {
		ifstream rfile(fname);
		if (!rfile.is_open()) throw FileException();
		else {
			string line;
			while (getline(rfile, line)) {
				cout << line << endl;
			}
			rfile.close();
		}
	}

	void saveAll(string fname) {
		ofstream wfile(fname, ios::app);
		if (!wfile.is_open()) throw FileException();
		else {
			wfile << _hour << " " << _patient->getName() << " " << _patient->getSurname()
			<< " -> Dr." << _doctor->getName() << " " << _doctor->getSurname() << " [" << getStatus() << "]\n";
		}
	}
};

class Room {
public:
	enum RoomType {
		General,
		ICU,
		Surgery,
		Recovery
	};
private:
	short _number;
	RoomType _room_type;
	short _capacity;
	vector<Patient*> _patients;
public:
	Room(short n, RoomType r, short c) :_number(n), _room_type(r), _capacity(c) {}
	~Room() {}
	short getNumber() const { return _number; }


	short getCapacity() const { return _capacity; }

	int getPatientCount() { return _patients.size(); }


	string getRoomType() const {
		switch (_room_type) {
		case General: return "General";
		case ICU: return "ICU";
		case Surgery: return "Surgery";
		case Recovery: return "Recovery";
		default: return "Unknown";
		}
	}

	void addPatient(Patient* pat) {
		if (_patients.size() >= _capacity){
			throw RoomFullException();
		}
		_patients.push_back(pat);
		cout << "\033[36mThe patient entered the "<< getRoomType()<< " room number "<< _number<<"\033[0m\n";
	}

};

class Department {
private:
	string _name;
	string _specialty;
	vector<Doctor*> _doctors;
	vector<Room> _rooms;
public:
	Department(string name, string specialty) :
		_name(name), _specialty(specialty) {}
	~Department() {}

	void addDoctor(Doctor* doc) { _doctors.push_back(doc); }

	void addRoom(const Room& room) { _rooms.push_back(room); }
};

class Payment {
private:
	double _amount;
	string _date;
	string _payment_status;
	double _balance;
public:
	Payment(double amount, string date, string ps, double balance) :_amount(amount), _date(date), _payment_status(ps), _balance(balance) {}
	virtual ~Payment() {}

	virtual void processPayment() = 0;

	void setPaymentStatus(string payment_status) { this->_payment_status = payment_status; }

	string getPaymentStatus() { return _payment_status; }

	double getAmount() const { return _amount; }

	double getBalance() { return _balance; }

	void loadAll(string fname) {
		ifstream rfile(fname);
		if (!rfile.is_open()) throw FileException();
		else {
			string line;
			while (getline(rfile, line)) {
				cout << line;
			}
			rfile.close();
		}
	}

	void saveAll(string fname) {
		ofstream wfile(fname, ios::app);
		if (!wfile.is_open()) throw FileException();
		else {
			wfile << "Date: " << _date << " | Amount: " << _amount << " $\n";
		}
	}

};

class CashPayment :public Payment {
public:
	CashPayment(double amount, string date, string ps, double balance) :Payment(amount, date, ps, balance) {}
	void processPayment() override {
		if (getAmount() > getBalance()) {
			throw InsufficientFundsException();
		}
		string p = "\033[36mPaid by Cash.\033[0m\n";
		setPaymentStatus(p);
		cout << getPaymentStatus();
	}

};

class CardPayment :public Payment {
public:
	CardPayment(double amount, string date, string ps, double balance) :Payment(amount, date, ps, balance) {}
	void processPayment() override {
		if (getAmount() > getBalance()) {
			throw InsufficientFundsException();
		}
		string p = "\033[36mPaid by Card.\033[0m\n";
		setPaymentStatus(p);
		cout << getPaymentStatus();
	}
};

class InsurancePayment :public Payment {
private:
	double _paymentByInsurance;
	double _paymentByPatient;
public:
	InsurancePayment(double amount, string date, string ps, double balance) :Payment(amount, date, ps, balance) {
		_paymentByInsurance = amount * 0.8;
		_paymentByPatient = amount * 0.2;
	}
	void processPayment() override {
		if (_paymentByPatient > getBalance()) {
			throw InsufficientFundsException();
		}
		string p = "\033[36mPaid by Insurance.\033[0m\n";
		setPaymentStatus(p);
		cout << getPaymentStatus();
	}

};

struct QueueNode {
	Patient* patient;
	QueueNode* next;
	QueueNode(Patient* pat) :patient(pat), next(nullptr) {}
};

class AppointmentQueue {
private:
	QueueNode* _front;
	QueueNode* _rear;
public:
	AppointmentQueue() :_front(nullptr), _rear(nullptr) {}

	bool isEmpty() const {
		return _front == nullptr;
	}

	void addPatient(Patient* pat) {
		QueueNode* newNode = new QueueNode(pat);
		if (isEmpty()) {
			_front = _rear = newNode;
			return;
		}
		_rear->next = newNode;
		_rear = newNode;
	}

	void toTakeOutOfPatient() {
		if (isEmpty()) {
			throw PatientNotFoundException();
			return;
		}
		QueueNode* temp = _front;
		_front = _front->next;
		delete temp;
	}

	Patient* currentPatient() {
		if (isEmpty()) {
			throw PatientNotFoundException();
			return nullptr;
		}
		return _front->patient;
	}

	~AppointmentQueue() {
		while (!isEmpty()) {
			toTakeOutOfPatient();
		}
	}
};

struct AppointmentNode {
	Appointment data;
	AppointmentNode* next;
	AppointmentNode(const Appointment& app) :data(app), next(nullptr) {}
};

class PatientHistory {
private:
	AppointmentNode* _head;
public:
	PatientHistory() :_head(nullptr) {}
	~PatientHistory() {
		AppointmentNode* current = _head;
		while (current != nullptr) {
			AppointmentNode* nextNode = current->next;
			delete current;
			current = nextNode;
		}
		_head = nullptr;
	}

	void addAppointment(const Appointment& app) {
		AppointmentNode* newNode = new AppointmentNode(app);
		if (_head == nullptr) {
			_head = newNode;
			return;
		}
		AppointmentNode* temp = _head;
		while (temp->next != nullptr) {
			temp = temp->next;
		}
		temp->next = newNode;
	}

	void printHistory(string passportNum) const {
		if (_head == nullptr) {
			cout << "The history is empty.\n";
			return;
		}
		AppointmentNode* temp = _head;
		bool found = false;
		while (temp != nullptr) {
			if (temp->data.getPatient()->getPassportNumber() == passportNum) {
				cout << temp->data.getDate() << " - " << temp->data.getPatient()->getName() << " -> Dr."
					<< temp->data.getDoctor()->getName() << " [" << temp->data.getStatus() << "]\n";
				found = true;
			}
			temp = temp->next;
		}
		if (!found) {
			throw InvalidAppointmentException();
		}
	}
};

class Hospital {
private:
	string _hname;
	class Address {
	public:
		string city;
		string street;
	};
	Address _address;
	vector<Doctor*> _doctors;
	vector<Patient*> _patients;
	vector<Nurse*> _nurses;
	vector<Department> _departments;
	AppointmentQueue _waitingQueue;
	PatientHistory _patientHistory;
	double _budget = 90000.0;

public:
	Hospital(string hname, string city, string street) :_hname(hname) {
		_address.city = city;
		_address.street = street;
	}
	~Hospital() {}

	void addAppointmentToHospital(const Appointment& app) {
		_patientHistory.addAppointment(app);
	}

	void showPatientHistory(string passportNum) {
		_patientHistory.printHistory(passportNum);
	}

	double getBudget() { return _budget; }

	void addDoctors(Doctor* doc) { _doctors.push_back(doc); }

	void addNurses(Nurse* nur) { _nurses.push_back(nur); }

	void addPatients(Patient* pat) { _patients.push_back(pat); }

	void addDepartment(const Department& dep) { _departments.push_back(dep); }

	void addAppointment(const Appointment& app) { _patientHistory.addAppointment(app); }

	void addPatientToQueue(Patient* pat) {
		_waitingQueue.addPatient(pat);
		cout << pat->getName() << " " << pat->getSurname() << " novbeye elave edildi.\n";
	}

	void callNextPatient() {
		if (_waitingQueue.isEmpty()) {
			cout << "There is no one in line.\n";
			return;
		}
		Patient* pat = _waitingQueue.currentPatient();
		cout << "\033[35mNext Patient: \033[0m" << pat->getName() << " " << pat->getSurname() << endl;
		_waitingQueue.toTakeOutOfPatient();
	}

	void processPayment(Payment* pay) {
		if (pay == nullptr) return;
		try {
			pay->processPayment();
			cout << "\033[36mPayment made:\033[0m " << pay->getAmount() << " \033[36m$\033[0m\n";
			_budget += pay->getAmount();
		}
		catch (const InsufficientFundsException& err) {
			cout << err.what() << endl;
		}

		delete pay;
	}

	Doctor* findDoctorByName(string name) {
		for (Doctor* doctor : _doctors) {
			if (doctor->getName() == name) {
				cout << "\033[35mThe doctor found:\033[0m " << doctor->getName() << " " << doctor->getSurname() << endl;
				return doctor;
			}
		}
		throw DoctorNotFoundException();
	}

};

template <typename T>
class MedicalCollection {
private:
	vector<T*> data;
public:
	MedicalCollection() {}
	void add(T* dat) {
		data.push_back(dat);
	}

	void remove(T* dat) {
		for (size_t i = 0;i < data.size();i++) {
			if (data[i] == dat) {
				data.erase(data.begin() + i);
				return;
			}
		}
	}

	void printAll() {
		if (data.empty()) { cout << "Collection is empty.\n"; return; }
		for (size_t i = 0;i < data.size();i++) {
			if (data[i] != nullptr) {
				data[i]->getInfo();
			}
		}
	}
};


int main() {
	cout << "\n\033[42m==================================\n";
	cout << "==          YASHA CLINIC        ==\n";
	cout << "==================================\033[0m\n";
	Hospital myHospital("Yasha clinic", "Baku", "Insaatcilar");
	//Departamentler
	Department cardiology("Cardiology", "Cardiolog");
	Department pediatrics("Pediatrics", "Pediatrician");
	Department generalsurgery("General surgery", "Plastic surgery");
	//Otaqlar
	Room room1(101, Room::ICU, 1);
	Room room2(102, Room::General, 2);
	Room room3(103, Room::Recovery, 1);
	Room room4(104, Room::Surgery, 1);

	myHospital.addDepartment(cardiology);
	myHospital.addDepartment(pediatrics);
	myHospital.addDepartment(generalsurgery);
	cardiology.addRoom(room1);
	cardiology.addRoom(room2);
	pediatrics.addRoom(room3);
	generalsurgery.addRoom(room4);

	Person* perdoc1 = new Doctor("Vaqif", "Aqayev", "1980-05-12", "0501234567", "vaqifaqayev@gmail.com",
		"DOC001", "Cardiolog", "2020-01-01", 3500.0, "Cardiology", "LIC12345", "09:00-17:00");
	Person* perdoc2 = new Doctor("Leyla", "Memmedova", "1991-04-25", "+994702223344", "leylamemmedv3@gmail.com",
		"DOC02", "Pediatrician", "2021-02-10", 2800.0, "Pediatrics", "LIC44556", "13:00-19:00");
	Person* perdoc3 = new Doctor("Elnur", "Qasimov", "1976-05-12", "+994556734583", "elnurqasim23@gmail.com",
		"DOC03", "Surgery", "2015-01-03", 4500.0, "General surgery", "LIC99887", "09:00-16:00");

	// dynamic cast
	Doctor* doc1 = dynamic_cast<Doctor*>(perdoc1);
	Doctor* doc2 = dynamic_cast<Doctor*>(perdoc2);
	Doctor* doc3 = dynamic_cast<Doctor*>(perdoc3);

	//cedvel
	Nurse::Queue schedule[7] =
	{
		{"Bazar ertesi", "09:00-15:00", "Ayan"},
		{"Tuesday", "20:00-08:00", "Gunel"},
		{"Wednesday", "08:00-16:00", "Nigar"},
		{"Thursday", "09:00-18:00", "Lala"},
		{"Friday", "14:00-22:00", "Fidan"},
		{"Saturday", "00:00-12:00", "Nermin"},
		{"Sunday", "12:00-18:00", "Shebnem"}
	};

	//Tibb bacilari
	Nurse* nurse1 = new Nurse("Ayan", "Memmedova", "1995-08-23", "+994709876543", "ayan@mail.com",
		"NUR001", "Nurse", "2022-03-15", 1200.0, "Cardiology", schedule);
	Nurse* nurse2 = new Nurse("Gunel", "Sherifova", "1993-03-12", "+994704356542", "gunel@mail.com",
		"NUR002", "Nurse", "2022-03-15", 1200.0, "Cardiology", schedule);
	Nurse* nurse3 = new Nurse("Nigar", "Ramazanova", "1995-08-23", "+994709874345", "nigar@mail.com",
		"NUR003", "Nurse", "2022-03-15", 1200.0, "Cardiology", schedule);
	Nurse* nurse4 = new Nurse("Lala", "Huseynli", "1995-08-23", "+994559843543", "lala@mail.com",
		"NUR004", "Nurse", "2022-03-15", 1200.0, "General surgery", schedule);
	Nurse* nurse5 = new Nurse("Fidan", "Nesibova", "1995-08-23", "+994704836543", "fidan@mail.com",
		"NUR005", "Nurse", "2022-03-15", 1200.0, "Pediatrics", schedule);
	Nurse* nurse6 = new Nurse("Nermin", "Memmedova", "1995-08-23", "+994509876543", "nermin@mail.com",
		"NUR006", "Nurse", "2022-03-15", 1200.0, "General surgery", schedule);
	Nurse* nurse7 = new Nurse("Shebnem", "Verdiyeva", "1995-08-23", "+994559876543", "shebnem@mail.com",
		"NUR007", "Nurse", "2022-03-15", 1200.0, "Pediatrics", schedule);

	myHospital.addDoctors(doc1);
	myHospital.addDoctors(doc2);
	myHospital.addDoctors(doc3);
	cardiology.addDoctor(doc1);
	pediatrics.addDoctor(doc2);
	generalsurgery.addDoctor(doc3);
	myHospital.addNurses(nurse1);
	myHospital.addNurses(nurse2);
	myHospital.addNurses(nurse3);
	myHospital.addNurses(nurse4);
	myHospital.addNurses(nurse5);
	myHospital.addNurses(nurse6);
	myHospital.addNurses(nurse7);

	// add doctors to file
	try {
		doc1->saveAll("doctors.csv");
		doc2->saveAll("doctors.csv");
		doc3->saveAll("doctors.csv");
	}
	catch (const FileException& e) {
		cout << e.what();
	}

	//Xesteler
	Patient* pat1 = new Patient("Ali", "Aliyev", "2001-02-09", "+994554443322", "ali@gmail.com",
		"AZE1234567", "A+", "Yoxdur", true);
	Patient* pat2 = new Patient("Tural", "Ceferov", "1993-12-19", "+994704443322", "tural@gmail.com",
		"AZE1234564", "B-", "Yoxdur", true);
	Patient* pat3 = new Patient("Aysel", "Orucova", "1991-03-13", "+994704434322", "aysel@gmail.com",
		"AZE1254764", "A+", "Yoxdur", true);

	
	myHospital.addPatients(pat1);
	myHospital.addPatients(pat2);

	cout << "\n\033[33m=== ADD TO QUEUE ===\033[0m\n";
	myHospital.addPatientToQueue(pat1);
	myHospital.addPatientToQueue(pat2);

	cout << "\n\033[33m=== CALLING PATIENTS ===\033[0m\n";
	myHospital.callNextPatient();
	myHospital.callNextPatient();

	cout << "\n\033[33m=== OPERATION ROOM ===\033[0m\n";
	room4.addPatient(pat3);

	// add patient to file
	try {
		pat1->saveAll("patients.csv");
		pat2->saveAll("patients.csv");
	}
	catch (const FileException& e) {
		cout << e.what();
	}

	// Muayine
	cout << "\n\033[33m=== APPOINTMENT ===\033[0m\n";
	Appointment app1(doc1, pat1, "2026-05-29", "14:00");
	Appointment app2(doc2, pat2, "2026-03-29", "10:00");

	//Muayine resepti
	Prescription pres1;
	pres1.addMedication("Aspirin", 100.0, 1);
	pres1.addMedication("Amoxicillin", 100.0, 1); 

	Prescription pres2;
	pres2.addMedication("Paracetamol", 250.0, 2);

	//Muayine tamamlandi
	app1.completeAppointment(pres1);
	app2.completeAppointment(pres2);

	//Resptleri goster
	pres1.showPrescription();
	pres2.showPrescription();

	myHospital.addAppointmentToHospital(app1);
	myHospital.addAppointmentToHospital(app2);

	try {
		app1.saveAll("appointments.csv");
		app2.saveAll("appointments.csv");
		cout << "The examination was recorded in the file.\n";
	}
	catch (const FileException& e) {
		cout << e.what();
	}

	cout << "\n\033[33m=== PAYMENT ===\033[0m\n";
	// Ugursuz odenis
	cout << "\033[31m--- Unsuccessful payment ---\033[0m\n";
	Payment* failedPay1 = new CardPayment(50.0, "2026-05-29", "Pending", 20.0);
	Payment* failedPay2 = new InsurancePayment(50.0, "2026-05-29", "Pending", 2.0);
	myHospital.processPayment(failedPay1);
	myHospital.processPayment(failedPay2);

	// Ugurlu odenis
	cout << "\n\033[32m--- Successful payment ---\033[0m\n";
	Payment* successPay1 = new CardPayment(50.0, "2026-05-29", "Pending", 100.0);
	Payment* successPay2 = new InsurancePayment(50.0, "2026-05-29", "Pending", 100.0);
	myHospital.processPayment(successPay1);
	myHospital.processPayment(successPay2);
	cout << "\033[36mHospital budget: \033[0m" << myHospital.getBudget() << " $\n";

	// Doctor tapilmadi error
	cout << "\n\033[33m--- Doctor Search ---\033[0m\n";
	try {
		Doctor* foundDoc = myHospital.findDoctorByName("Elnur");
	}
	catch (const DoctorNotFoundException& e) {
		cout << "Error: " << e.what();
	}

	cout << "\n\033[33m--- Patient History ---\033[0m\n";
	myHospital.showPatientHistory("AZE1234567");

	//Tibb bacilari novbe cedveli
	MedicalCollection<Nurse> nurseCollection;
	nurseCollection.add(nurse1);
	nurseCollection.add(nurse7);
	nurseCollection.printAll();

	cout << "\n\033[33m=== QUEUE SCHEDULE ===\033[0m\n";
	nurse1->getSchedule();

	// template
	cout << "\n\033[33m=== TEMPLATE ===\033[0m\n";
	MedicalCollection<Doctor> doctorCollection;
	doctorCollection.add(doc1);
	doctorCollection.add(doc2);
	doctorCollection.add(doc3);
	doctorCollection.remove(doc2); //remove
	doctorCollection.printAll();

	// clean memory
	delete doc1;
	delete doc2;
	delete doc3;

	delete nurse1;
	delete nurse2;
	delete nurse3;
	delete nurse4;
	delete nurse5;
	delete nurse6;
	delete nurse7;

	delete pat1;
	delete pat2;
	delete pat3;

	return 0;
}