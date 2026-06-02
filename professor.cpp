#include <iostream>
using namespace std;

#define maxsize 50

class Person {
private:
	string _name;
	short _age;
	string _email;
public:
	Person(string name, short age, string email) :_name(name), _age(age), _email(email) {}

	string getName() {
		return _name;
	}

	short getAge() {
		return _age;
	}

	string getEmail() {
		return _email;
	}

	virtual void showInfo() {
		cout << "[" << _name << "] | Age: " << _age << " | Email: " << _email << endl;
	}

	virtual ~Person() {}
};

class Student :public Person {
public:
	string id;
	float gpa;

	Student(string name, short age, string email, string id, float gpa) :Person(name, age, email) {
		this->id = id;
		this->gpa = gpa;
	}

	virtual void showInfo() override {
		cout << "[Student] " << getName() << " | Age: " << getAge() <<
		" | ID: " << this->id << " | GPA: " << this->gpa << endl;
	}

};


class Professor :public Person {
public:
	string title;
	string field;

	Professor(string name, short age, string email, string title, string field) :Person(name, age, email) {
		this->title = title;
		this->field = field;
	}

	virtual void showInfo() override {
		cout << "[Professor] " << getName() << " | Age: " << getAge() <<
		" | Field: " << this->field << " | Title: " << this->title << endl;
	}
};

class Address {
public:
	string city;
	string street;
	string house_number;

	Address() :city(""), street(""), house_number("") {}

	Address(string city, string street, string house_number) {
		this->city = city;
		this->street = street;
		this->house_number = house_number;
	}

	friend ostream& operator<<(ostream& print, const Address& obj) {
		print << "[" << obj.city << "] | [" << obj.street << "] | [" << obj.house_number << "]\n";
		return print;

	}
};

class University {
public:
	string uniname;
	Address address;

	University(string uniname, Address address) {
		this->uniname = uniname;
		this->address = address;
	}

	friend ostream& operator<<(ostream& print, const University& obj) {
		print << "[" << obj.uniname << "] | [" << obj.address.city << "] | [" << obj.address.street << "]\n";
		return print;

	}
};

class Schedule {
public:
	void addClass(string lesson, string time) {
		cout << lesson << " : " << time << endl;
	}
};

class Department {
public:
	string faculty;
	Schedule schedule; 
	Professor* professors[maxsize];
	int count = 0;

	Department(string fac) :faculty(fac) {}
	void addProfessor(Professor* p) {
		if (count < maxsize) {
			professors[count++] = p;
		}
	}

	void showAllProfessors() {
		cout << "\n=== Professors of University ===\n";
		for (int i = 0;i < count;i++) {
			professors[i]->showInfo();
		}
		cout << "===================================\n";
	}

	~Department() {}
};

class Course {
public:
	string course_name;
	short credit;
	Professor* prof;

	Course(string cname, short credit, Professor* prof) {
		this->course_name = cname;
		this->credit = credit;
		this->prof = prof;
	}


	friend ostream& operator<<(ostream& print, const Course& obj) {
		print << "[" << obj.course_name << "] | Credit: [" << obj.credit << "] | Professor: "
		<< obj.prof->getName() << endl;
		return print;
	}
};

int main() {
	Person* p1 = new Person("Tahir Salmanov", 45, "tahirsalman12@gmail.com");
	Person* s1 = new Student("Tural Orucov", 23, "turaloruc@gmail.com", "STU-1001", 89.9);
	Professor pr1("Taleh Salehov", 65, "talhsalehv@gmail.com", "Docent", "Philosophy");
	Professor pr2("Elshad Musayev", 56, "elsadmusayv3@gmail.com", "Docent", "Mathematics");
	Professor pr3("Fateh Isgenderli", 46, "isgenderlifatv@gmail.com", "Docent", "Mathematics");
	Professor pr4("Fuad Eliyev", 86, "fuadsadelyv@gmail.com", "Docent", "Mathematics");
	p1->showInfo();
	s1->showInfo();
	Department math("Mathematic Faculty");
	math.addProfessor(&pr1);
	math.addProfessor(&pr2);
	math.addProfessor(&pr3);
	math.addProfessor(&pr4);
	math.showAllProfessors();
	
	Address ad1("Baku", "Elmler", "0555554545");
	Course c1("Calculus", 6, &pr1);
	Course c2("Quantum Physics", 5, &pr2);

	University uni("Azerbaijan Technical University",ad1);
	cout << uni;
	delete p1;
	delete s1;


	return 0;
}