#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

//geeksforgeek den arasdiracam.
class FileException :public exception {           
private:
	string _file;
public:
	FileException(string file) :_file(file) {}

	const char* what() const noexcept override {
		return "File could not be opened.\n";
	}
};

class StudentNotFoundException :public exception {
private:
	string _id;
public:
	StudentNotFoundException(string id) :_id(id) {}

	const char* what() const noexcept override {
		return "Student could not be opened.\n";
	}
};

class Course {                          
private:
	string _name;
	string _kod;
	short _kredit;
public: 
	Course() :_name(""), _kod(""), _kredit(0) {}   
	~Course() {}                    
	string getName() {
		return _name;
	}

	string getKod() {
		return _kod;
	}

	short getKredit() {
		return _kredit;
	}

	friend istream& operator>>(istream& input, Course& obj) {
		cout << "Course name: "; input >> obj._name;
		cout << "Kod: "; input >> obj._kod;
		cout << "Kredit: "; input >> obj._kredit;
		return input;
	}

	friend ostream& operator<<(ostream& print, const Course& obj) {
		print << "Course name: " << obj._name << endl << "Kod: " <<
		obj._kod << endl << "Kredit: " << obj._kredit << endl;
		return print;
	}
};

enum QeydDersler {
	Math,
	Biology,
	Chemistry,
	Physics
};

string getDers(QeydDersler qd) {
	switch (qd) {
	case Math: return "Math";
	case Biology: return "Biology";
	case Chemistry: return "Chemistry";
	case Physics: return "Physics";
	default: return "Unknown";
	}
}

class Student {
private:
	string _name;
	string _id;
	short _ders_sayi;
	QeydDersler* _dersler;
	float* _qiymetler;
public:
	Student() :_name(""), _id(""), _dersler(nullptr), _qiymetler(nullptr), _ders_sayi(0) {}
	~Student() { delete[] _dersler; delete[] _qiymetler; }

	Student(const Student& other) {
		_name = other._name;
		_id = other._id;
		_ders_sayi = other._ders_sayi;
		if (other._dersler != nullptr) {
			_dersler = new QeydDersler[_ders_sayi];
			for (short int i = 0;i < _ders_sayi;i++) {
				_dersler[i] = other._dersler[i];
			}
		}
		else _dersler = nullptr;

		if (other._qiymetler != nullptr) {
			_qiymetler = new float[_ders_sayi];
			for (short int i = 0;i < _ders_sayi;i++) {
				_qiymetler[i] = other._qiymetler[i];
			}
		}
		else _qiymetler = nullptr;
	}

	Student& operator=(const Student& other) {
		if (this != &other) {
			delete[] _dersler;
			delete[] _qiymetler;

			_name = other._name;
			_id = other._id;
			_ders_sayi = other._ders_sayi;
			if (other._dersler != nullptr) {
				_dersler = new QeydDersler[_ders_sayi];
				for (short int i = 0;i < _ders_sayi;i++) {
					_dersler[i] = other._dersler[i];
				}
			}
			else _dersler = nullptr;

			if (other._qiymetler != nullptr) {
				_qiymetler = new float[_ders_sayi];
				for (short int i = 0;i < _ders_sayi;i++) {
					_qiymetler[i] = other._qiymetler[i];
				}
			}
			else _qiymetler = nullptr;
		}
		return *this;
	}

	string getID() {
		return _id;
	}

	string getName() {
		return _name;
	}

	short getDersSayi() {
		return _ders_sayi;
	}

	float* getQiymetler() {
		return _qiymetler;
	}

	friend istream& operator>>(istream& input, Student& obj) {
		cout << "Student name: "; getline(input, obj._name);
		cout << "ID: ";input >> obj._id;
		while (true) {
			cout << "Ders sayi: ";
			if (input >> obj._ders_sayi && obj._ders_sayi >= 1 && obj._ders_sayi <= 4) break;
			cout << "Yalniz 1-4 araliginda!\n";
			input.clear();
			input.ignore(1000, '\n');
		}
		if (obj._dersler != nullptr) delete[] obj._dersler;
		if (obj._qiymetler != nullptr) delete[] obj._qiymetler;
		obj._dersler = new QeydDersler[obj._ders_sayi];
		obj._qiymetler = new float[obj._ders_sayi];
		for (short int i = 0;i < obj._ders_sayi;i++) {
			obj._dersler[i] = (QeydDersler)i;
			while (true) {
				cout << "Qiymet (0-100): ";
				if (input >> obj._qiymetler[i] && obj._qiymetler[i] >= 0 && obj._qiymetler[i] <= 100) break;
				else cout << "Yalniz 0-100 araliginda.\n";
				input.clear();
				input.ignore(1000, '\n');
			}
			input.clear();
			input.ignore(1000, '\n');
		}
		return input;
	}


	friend ostream& operator<<(ostream& print, const Student& obj) {
		print << obj._id << ", " << obj._name << ", ";
		for (short int i = 0;i < obj._ders_sayi; i++) {
			print << getDers(obj._dersler[i]) << " : " << obj._qiymetler[i] << ", ";
		}
		print << ". \n";
		return print;
	}
};

class StudentRegistry {
private:
	vector<Student> students;
public:
	void loadFromFile(string fname) {
		ifstream rfile(fname);
		if (!(rfile.is_open())) throw FileException(fname);
		else {
			string line;
			while (getline(rfile, line)) {
				cout << line << endl;
			}
			rfile.close();
		}
	}

	void saveToFile(string fname) {
		ofstream wfile(fname);
		if(!(wfile.is_open())) throw FileException(fname);
		else {
			for (int i = 0;i < students.size();i++) {
				wfile << students[i];
			}
			wfile.close();
		}
	}

	void addStudent(const Student& s) {
		students.push_back(s);
	}

	void findStudent(string id) {
		bool found = false;
		cout << "\n========= AXTARILAN TELEBE ========= \n";
		for (auto& student : students) {
			if (id == student.getID()) {
				cout << student;
				found = true;
				break;
			}
			else {
				found = false;
				throw StudentNotFoundException(id);
			}
		}
		cout << "=================================== \n\n";
		if (!found) cout << "Bele bir telebe yoxdur.\n";
	}


	void generateReport() {
		cout << "\n========= TELEBE HESABATI ========= \n";
		for (auto& student : students) {
			float cem = 0;
			for (int i = 0;i < student.getDersSayi();i++) {
				cem += student.getQiymetler()[i];
			}
			float ort = cem / student.getDersSayi();
			cout << student.getID() << " " << student.getName() << " Ort: " << ort << endl;
		}
		cout << "=================================== \n\n";
	}

	void exportFormatted(string fname) {
		ofstream wfile(fname);
		if (!(wfile.is_open())) throw FileException(fname);
		else {
			wfile << "Ad" << setw(10) << "ID" << setw(10) << "Ort.Bal\n";
			wfile << "------------------------------------------\n";
			for (auto& student : students) {
				float cem = 0;
				for (int i = 0;i < student.getDersSayi();i++) {
					cem += student.getQiymetler()[i];
				}
				float ort = cem / student.getDersSayi();
				wfile << student.getName() << setw(10) << student.getID() << setw(10) << ort << endl;
			}
			wfile.close();
		}

		ifstream rfile(fname);
		if (!(rfile.is_open())) throw FileException(fname);
		else {
			string line;
			while (getline(rfile, line)) {
				cout << line << endl;
			}
		}
		rfile.close();
	}

	void getFileSize(string fname) {
		ifstream rfile(fname);
		if (!(rfile.is_open())) throw FileException(fname);
		else {
			rfile.seekg(0, ios::end);
			float size = rfile.tellg();
			rfile.close();
			cout << "Size of file: " << size << endl;
		}
	}

};

int main() {
	Student s1, s2, s3;
	StudentRegistry stureg;

	cin >> s1;
	cin >> s2;
	cin >> s3;

	ofstream wfile("students.txt");
	if (wfile.is_open()) {
		wfile << s1;
		wfile.close();
	}

	ifstream rfile("students.txt");
	if (rfile.is_open()) {
		string line;
		while (getline(rfile, line)) {
			cout << line << endl;
		}
		rfile.close();
	}

	try {
		stureg.addStudent(s1);
		stureg.addStudent(s2);
		stureg.addStudent(s3);
		stureg.saveToFile("students3.txt");
		stureg.loadFromFile("students3.txt");
		stureg.findStudent("STU-1001");
		stureg.exportFormatted("students3.txt");
	}
	catch (FileException& err) {
		cout << "FilelException: " << err.what();
	}
	catch (StudentNotFoundException& err) {
		cout << "StudentNotFoundException: " << err.what();
	}
	stureg.generateReport();
	stureg.getFileSize("students3.txt");
	return 0;
}