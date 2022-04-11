#include "std_lib_facilities.h"

const char NUMBER = 'N';
const char QUIT = 'q';
const char ENDPRINT = ';';
const string PROMPT = "> ";
const string RESULT = "= ";



class Token{
public:
	char kind;
	double value;
	Token(char ch)
		: kind(ch), value(0) {}
	Token(char ch, double val)
		: kind(ch), value(val) {}
};

class Token_stream{
private:
	bool full;
	Token buffer;
public:
	Token get();
	void putback(Token t);
	void ignore(char c);
	Token_stream()
		: full(false), buffer(0) {} //buffer(0)의 의미
};

Token Token_stream::get() {
	if (full) { 
		full = false;
		return buffer; 
	}
	else {
		char c;
		cin >> c;

		switch (c) {
		case'0': case'1': case'2': case'3': case'4': case'5': case'6': case'7': case'8': case'9': case'.':
			cin.putback(c);
			double d;
			cin >> d;
			return Token(NUMBER, d);   // 핵심. class에서 public으로 선언하지 않으면 Token에 값을 대입할 수 없다.
		case '(': case ')': case '+': case '-': case '*': case '/': case';': case'q':
			return Token(c);
		default:
			error("Bad Token");
		}
	}
}
void Token_stream::putback(Token t) {
	if (full) {
		error("buffer is full");
	}
	else {
		buffer = t;
		full = true;
	}
}

void Token_stream::ignore(char c) {
	if (full && c == buffer.kind) {
		full = false;
		return;
	}
	full = false;

	char ch = 0;
	while (cin >> ch)
		if (ch == c) return;
}

Token_stream ts = Token_stream();

double expression();
double term();
double primary();

double expression() { /// + 
	double left = term();
	while (true) {
		Token t = ts.get();
		switch (t.kind) {
		case '+':
			left += term();
			break;
		case '-':
			left -= term();
			break;
		default: // 아무값이 없을 때?
			ts.putback(t);
			return left;
		}
	}
	
	return left;
}
double term() {
	double left = primary();
	while (true) {
		Token t = ts.get();
		switch (t.kind) {
		case '*': 
			left *= primary(); 
			break;
		case '/': 
			left /= primary();
			break;
		default:                    // *을 만날 때  혹은 하위 계층 만날 때  primary = > 띄어쓰기가 있다는 것.
			ts.putback(t);
			return left;
		}
	}
}

double primary() {
	Token t = ts.get();
	switch (t.kind) {
	case '(': 
	{
		double t2 = expression();
		char c;
		cin >> c;
		if (c != ')') { error(" ')'  is needed."); }
		return t2;
	}
		
	case NUMBER:
		return t.value;
	default:
		error("You should input 'number' or '(expression) first.'");
	}

}



void clean_up_mess() {
	ts.ignore(ENDPRINT);
}

void calculate() {
	while (cin) try{
		cout << PROMPT;
		Token t = ts.get();
		while (t.kind == ENDPRINT) t = ts.get();
		if (t.kind == QUIT) return;
		ts.putback(t);
		cout << RESULT << expression() << endl;
	}
	catch (exception& e) {
		cout << e.what() << endl;
		clean_up_mess();
	}
}

int main() try {
	calculate();
	return 0;
}
catch (...) {
	cerr << "exceprion \n";
	return 2;
}
