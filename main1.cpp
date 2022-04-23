#include "std_lib_facilities.h"

class Token {
public:
	char kind;
	double value;

	Token(char c, double d)
		:kind(c), value(d) {}
	Token(char c)
		:kind(c), value() {}

	Token get();

private:

};
Token Token::get() {
	char c;
	cin >> c;
	switch (c) {
	case'0':case'1':case'2':case'3':case'4':case'5':case'6':case'7':case'8':case'9':case'.':
		cin.putback(c);
		double d;
		cin >> d;
		return Token('N', d);
	case '+': case '-':case '*': case '/':case '%': case '(':case ')':
		return Token(c);
	default: error("not Token");
	}
}

Token ts('0');

double expression();

double primary() {
	Token t = ts.get();
	switch (t.kind) {
	case '(': {
		double d = expression();
		char c;
		cin >> c;
		if (c != ')') error("should close with ')'");
		return d;
	}

	case 'N': return t.value;
	default:
		string errstr = "You should enter 'Number' not '";
		errstr.push_back(t.kind);
		errstr.push_back('\'');
		error(errstr);
	}
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
		{
			double p = primary();
			if (p == 0) error("Can't divided 0");
			left /= primary();
			break;
		}
		default: return left;
		}
	}
}
double expression() {
	double left = term();
	while (true) {
		Token t = ts.get();
		switch (t.kind) {
		case '+': left += term(); break;
		case '-': left -= term(); break;
		default: return left;
		}
	}
}





int main() try {
	while (true)
	{
		cout << expression() << endl;
	}



}
catch (runtime_error& e) {
	cout << e.what() << endl;
}
