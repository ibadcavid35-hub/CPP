#include <iostream>
#include <cstring>
using namespace std;
class Person {
private:
    char* name;
    int age;
    bool isMan;
public:
    Person(const char* name, int age, bool isMan) {
        this->name = new char[strlen(name) + 1];
        strcpy_s(this->name, strlen(name) + 1, name);
        this->age = age;
        this->isMan = isMan;
    }
    ~Person() {
        delete[] name;
    }
    const char* getName() {
        return name;
    }
    int getAge() {
        return age;
    }
    bool getIsMan() { 
        return isMan;
    }
};
class Employee: public Person {
public:
    int id;
    float salary;
    char* position;
    static int numberOfMan;
    static int numberOfWoman;
    static int nthEmployee;

    Employee(const char* n, int a, bool m,float sal,const char* position) :Person(n, a, m),salary(sal) {
        this->position = new char[strlen(position) + 1];
        strcpy_s(this->position,strlen(position)+1 ,position);
        if (m) {
            numberOfMan++;
        }
        else {
            numberOfWoman++;
        }
        nthEmployee++;
        id = nthEmployee;
    }
    ~Employee() {
        delete[] position;
    }
    
    int getTotalEmployees() {
        return numberOfMan + numberOfWoman;
    }
    double getManRatio() {
        return (numberOfMan * 100.0) / (numberOfMan + numberOfWoman);
    }
    double getWomanRatio() {
        return (numberOfWoman * 100.0) / (numberOfMan + numberOfWoman);
    }
    void printInfo() {
        cout << "---- Employee #" << id << " ----" << endl;
        cout << "Name: " << getName() << endl;
        cout << "Age: " << getAge() << endl;
        cout << "Gender: " << (getIsMan() ? "Male" : "Female") << endl;
        cout << "Salary: " << salary << endl;
        cout << "Position: " << position << endl;
        cout << "Birth: " << 2026-getAge() << endl;
        cout << endl;
    }
};
int Employee::numberOfMan = 0;
int Employee::numberOfWoman = 0;
int Employee::nthEmployee = 0;
int main()
{
    Employee e1("Tural", 30, true, 1200, "Isci");
    Employee e2("Arif", 24, true, 1500, "Pro Isci");
    Employee e3("Lale", 25, false, 1000, "HR");

    e1.printInfo();
    e2.printInfo();
    e3.printInfo();

    cout << "\nTotal: " << e1.getTotalEmployees() << endl;
    cout << "Kishi faizi: " << e1.getManRatio() << "%" << endl;
    cout << "Qadin faizi: " << e1.getWomanRatio() << "%" << endl;

    return 0;
}