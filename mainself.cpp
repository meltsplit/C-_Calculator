#include "std_lib_facilities.h"



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
	Token_stream()
		: full(false), buffer(0) {}
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
			return Token('N', d);   // �ٽ�. class���� public���� �������� ������ Token�� ���� ������ �� ����.
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
		default: // �ƹ����� ���� ��?
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
		default: // *�� ���� ��  Ȥ�� ���� ���� ���� ��  primary = > ���Ⱑ �ִٴ� ��.
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
		
	case 'N':
		return t.value;
	default:
		error("You should input 'number' or '(expression) first.'");
	}

}

int main() try{
	while (cin) {
		Token t = ts.get();
		while(t.kind == ';') t = ts.get();
		if (t.kind == 'q') break;
		ts.putback(t);
		cout << "= " << expression() << endl;
	}
}
catch(exception &e) {
	cout << e.what() << endl;
}