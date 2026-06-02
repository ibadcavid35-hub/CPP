#include <iostream>
#include <cstring>
using namespace std;

enum Level {
	EASY,
	MEDIUM,
	HARD
};

class Question {
private:
	char* _questionText;
	char** _answers;
	Level _level;
	short _answerId;
	short _answerCount = 4;
public:

	//Default Constructor

	Question() :_questionText(nullptr), _answers(nullptr),_answerId(0), _level(EASY), _answerCount(4) {}

	//Parametr Construcotr

	Question(const char* questiontext,const char** answers,Level level,short answerid){
		this->_questionText = new char[strlen(questiontext) + 1];
		strcpy_s(this->_questionText, strlen(questiontext) + 1, questiontext);
		this->_answers = new char*[_answerCount];
		for (int i = 0;i < _answerCount;i++) {
			_answers[i] = new char[strlen(answers[i]) + 1];
			strcpy_s(_answers[i], strlen(answers[i]) + 1, answers[i]);
		}
		this->_level = level;
		this->_answerId = answerid;
	}

	//Copy Constructor

	Question(const Question& other) {
		_answerCount = other._answerCount;
		if (other._questionText) {
			_questionText = new char[strlen(other._questionText) + 1];
			strcpy_s(_questionText, strlen(other._questionText) + 1, other._questionText);
		}
		else {
			_questionText = nullptr;
		}

		if(other._answers){
			_answers = new char* [_answerCount];
			for (int i = 0;i < _answerCount;i++) {
				_answers[i] = new char[strlen(other._answers[i]) + 1];
				strcpy_s(_answers[i], strlen(other._answers[i]) + 1, other._answers[i]);
			}
		}
		else {
			_answers = nullptr;
		}

		_level = other._level;
		_answerId = other._answerId;
	}

	//Destructor
	
	~Question() {
		delete[] _questionText;
		if (_answers != nullptr) {
			for (int i = 0; i < _answerCount; i++) {
				delete[] _answers[i];
			}
			delete[] _answers;
		}
		_answers = nullptr;
		_questionText = nullptr;
	}

	//Print Answers
	void printAnswers() const {
		if (_answers == nullptr) return;

		for (int i = 0; i < _answerCount; i++) {
			cout << i << ") " << _answers[i] << endl;
		}
	}

	//Check Answers
	bool checkAnswer(int userAnswer) const {
		return userAnswer == _answerId;
	}

	//Assignment Constructor

	Question& operator=(const Question& other) {
		if (this != &other) {

			delete[] _questionText;

			if (_answers != nullptr) {
				for (int i = 0;i < _answerCount;i++) {
					delete[] _answers[i];
				}
				delete[] _answers;
			}

			_answerCount = other._answerCount;

			if (other._questionText) {
				_questionText = new char[strlen(other._questionText) + 1];
				strcpy_s(_questionText, strlen(other._questionText) + 1, other._questionText);
			}
			else {
				_questionText = nullptr;
			}

			if (other._answers) {
				_answers = new char* [_answerCount];
				for (int i = 0;i < _answerCount;i++) {
					_answers[i] = new char[strlen(other._answers[i]) + 1];
					strcpy_s(_answers[i], strlen(other._answers[i]) + 1, other._answers[i]);
				}
			}
			else {
				_answers = nullptr;
			}

			_level = other._level;
			_answerId = other._answerId;
		}
		return *this;
	}

	string getLevel(Level q) const {
		switch (q) {
		case EASY:return "EASY";
		case MEDIUM:return "MEDIUM";
		case HARD:return "HARD";
		default: return "";
		}
		
	}

	//Suallar eynidirmi?

	bool operator==(const Question& other) const{
		return strcmp(this->_questionText, other._questionText) == 0;
	}

	//Cap etmek
	 
	friend ostream& operator<<(ostream& print, const Question& q) {
		print << q._questionText << " " << q.getLevel(q._level) << endl;
		return print;
	}

};

class Quiz {
	Question* _questionList;
	int _totalQuestions;
	const int _minPassRating = 51;

public:

	//Default Constructor

	Quiz():_questionList(nullptr),_totalQuestions(0) {}

	//Paramet Constructor
	Quiz(Question* question, int total) {
		_totalQuestions = total;
		_questionList = new Question[_totalQuestions];
		for (int i = 0;i < _totalQuestions;i++) {
			_questionList[i] = question[i];
		}
	}

	//Copy Constructor
	Quiz(const Quiz& other) {
		_totalQuestions = other._totalQuestions;
		_questionList = new Question[_totalQuestions];
		for (int i = 0;i < _totalQuestions;i++) {
			_questionList[i] = other._questionList[i];
		}
	}

	//Assignment Constructor
	Quiz& operator=(const Quiz& other) {
		if (this != &other) {
			delete[] _questionList;

			_totalQuestions = other._totalQuestions;
			_questionList = new Question[_totalQuestions];
			for (int i = 0;i < _totalQuestions;i++) {
				_questionList[i] = other._questionList[i];
			}
		}
		return *this;
	}

	//Add Question
	void addQuestion(const Question& q) {
		Question* temp = new Question[_totalQuestions + 1];
		for (int i = 0;i < _totalQuestions;i++) {
			temp[i] = _questionList[i];
		}

		temp[_totalQuestions] = q;
		delete[] _questionList;
		_questionList = temp;
		_totalQuestions++;
	}

	//Destructor
	~Quiz() {
		delete[] _questionList;
		_questionList = nullptr;
	}

	void run() {
		if (_totalQuestions == 0) {
			cout << "Sual yoxdur!\n";
			return;
		}
		int correctCount = 0;

		for (int i = 0; i < _totalQuestions; i++) {

			cout << "\nSual " << i + 1 << ":\n";
			cout << _questionList[i];

			_questionList[i].printAnswers();

			int userAnswer;
			cout << "Cavabinizi daxil edin (0-3): ";
			cin >> userAnswer;

			if (_questionList[i].checkAnswer(userAnswer)) {
				cout << "Dogru cavab!\n";
				correctCount++;
			}
			else {
				cout << "Yanlis cavab!\n";
			}
		}

		int score = (correctCount * 100) / _totalQuestions;

		cout << "\nNeticeniz: " << score << "%" << endl;
		if (score >= _minPassRating)
			cout << "Kecdiniz.\n";
		else
			cout << "Kesildiniz.\n";
	}


};

int main() {

	const char* a1[4] = { "Baku", "Ganja", "Sumqayit", "Shaki" };
	const char* a2[4] = { "2", "4", "6", "8" };

	Question q1("Azerbaycanin paytaxti hansidir?", a1, EASY, 0);
	Question q2("2+2=?", a2, EASY, 1);

	Quiz quiz;
	quiz.addQuestion(q1);
	quiz.addQuestion(q2);

	
	quiz.run();
	cout << endl;

	if (q1 == q2) {
		cout << "Eynu sual.\n";

	}
	else cout << "Eyni sual deyil.\n";

	return 0;
}