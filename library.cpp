#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

//ENUM Genre
enum Genre {
	FICTION,
	DETECTIVE,
	FANTASY,
	ROMANCE,
	HISTORICAL,
	HORROR
};

//Book Class
class Book {
private:
	char* _name;
	char* _author;
	Genre* _genres;
	int _size;
public:
	int _id;
	static int _counter;
	Book() : _name(nullptr), _author(nullptr), _genres(nullptr), _size(0) {}

	//Constructor with parametr
	Book(const char* name, const char* author, Genre* genres, int size) :Book() {
		_id = _counter++;
		_name = new char[strlen(name) + 1];
		strcpy_s(_name, strlen(name) + 1, name);
		_author = new char[strlen(author) + 1];
		strcpy_s(_author, strlen(author) + 1, author);
		_size = size;
		_genres = new Genre[_size];
		for (int i = 0;i < _size;i++) {
			_genres[i] = genres[i];
		}
	}

	//Deep Copy
	Book(const Book& other) {
		_id = other._id;
		_name = new char[strlen(other._name) + 1];
		strcpy_s(_name, strlen(other._name) + 1, other._name);
		_author = new char[strlen(other._author) + 1];
		strcpy_s(_author, strlen(other._author) + 1, other._author);
		_size = other._size;
		_genres = new Genre[_size];
		for (int i = 0;i < _size;i++) {
			_genres[i] = other._genres[i];
		}
	}

	//Assignment Copy
	Book& operator = (const Book& other) {
		if (this != &other) {
			delete[] _genres;
			delete[] _name;
			delete[] _author;

			_id = other._id;
			_name = new char[strlen(other._name) + 1];
			strcpy_s(_name, strlen(other._name) + 1, other._name);
			_author = new char[strlen(other._author) + 1];
			strcpy_s(_author, strlen(other._author) + 1, other._author);
			_size = other._size;
			_genres = new Genre[_size];
			for (int i = 0;i < _size;i++) {
				_genres[i] = other._genres[i];
			}
		}
		return *this;
	}

	char* getAuthor() const {
		return _author;
	}
	char* getName() const {
		return _name;
	}

	//Destructor

	~Book() {
		delete[] _name;
		delete[] _author;
		delete[] _genres;

		_name = nullptr;
		_author = nullptr;
		_genres = nullptr;
	}

	//get id
	int getId() const {
		return _id;
	}

	void showBookInfo() const {
		cout << "ID: " << _id << endl;
		cout << "Name: " << _name << endl;
		cout << "Author: " << _author << endl;
		cout << "Genres: ";
		for (int i = 0;i < _size;i++) {
			switch (_genres[i]) {
			case FICTION: cout << "FICTION ";break;
			case DETECTIVE: cout << "DETECTIVE ";break;
			case FANTASY:cout << "FANTASY ";break;
			case ROMANCE:cout << "ROMANCE ";break;
			case HISTORICAL:cout << "HISTORCAL ";break;
			case HORROR:cout << "HORROR ";break;
			}
		}
	
		cout << endl;
	}

};

int Book::_counter = 1;
//Library Class
class Library {
public:
	vector<Book>books;
	void addBook(const Book& book) {
		books.push_back(book);
	}

	//Search by Author
	void showBooksByAuhor(const char* author) {
		bool found = false;
		cout << endl << author << " muellifinin kitablari:\n";
		for (const Book& book : books) {
			if (strcmp(book.getAuthor(), author) == 0) {
				cout << "-----------------\n";
				book.showBookInfo();
				cout << "=================\n";
				found = true;
			}
		}
		if (!found) {
			cout << "There are not information about author and his books.\n";

		}
	}

	//Search by Name
	void showBooksByName(const char* name) {
		bool found = false;
		cout << endl << name << " kitabi:\n";
		for (const Book& book : books) {
			if (strcmp(book.getName(), name) == 0) {
				cout << "-----------------\n";
				book.showBookInfo();
				cout << "=================\n";
				found = true;
			}
		}
		if (!found) {
			cout << "There are not information about book.\n";

		}
	}

	//Search By Id
	void showBookbyId(int id) {
		cout << id << " id'si uzre netice:\n";
		bool find = false;
		for (const Book& book : books) {
			if (book.getId() == id) {
				book.showBookInfo();
				cout << "=================\n";
				find = true;
			}
		}
		if (!find) {
			cout << id << " id'si uzre hec bir netice cixmadi.\n";
		}
	}

	void showAllBooks() {
		if (books.empty()) {
			cout << "Library is empty.\n";
			return;
		}

		for (const Book& book : books) {
			book.showBookInfo();
			cout << "=================\n";
		}

	}


};

int main() {
	Genre g1[] = { FICTION, HORROR };
	Genre g2[] = { FANTASY };
	Genre g3[] = { DETECTIVE };
	Book b1("1984", "George Orwell", g1, 2);
	Book b2(b1);
	Book b3;
	Book b4("Harry Potter", "J.K. Rowling", g2, 1);
	Book b5("Sherlock Holmes", "Arthur Conan Doyle", g3, 1);
	Book b6("Animal Farm", "George Orwell", g1, 2);
	b3 = b1;
	Library l;
	l.addBook(b1);
	l.addBook(b2);
	l.addBook(b3);
	l.addBook(b4);
	l.addBook(b5);
	l.addBook(b6);
	l.showAllBooks();
	l.showBooksByAuhor("J.K. Rowling");
	l.showBooksByName("Harry Potter");
	l.showBookbyId(3);
	

	return 0;
}