//#include "std_lib_facilities.h"
//
//class Token {
//public:
//	char kind;
//	double value;
//	Token(char c)
//		: kind(c), value(0) {}     // { } 클래스 init 문법 알아야할 피료가 있다.
//	Token(char c, double v)
//		: kind(c), value(v) {}
//};
//
//class Token_stream {
//public:
//	Token_stream();
//	Token get();
//	void putback(Token t);
//private:
//	bool full;
//	Token buffer;
//};
//
//Token_stream::Token_stream()
//	:full(false), buffer(0)    // no Token in buffer
//{
//}
//
//void Token_stream::putback(Token t) {
//	if (full) error("buffer is full");
//	printf("put back : %c \n",t.kind);
//	buffer = t;
//	full = true;
//}
//
//Token Token_stream::get() {
//	if (full) {
//		full = false;
//		return buffer;
//	}
//	else {
//		char c;
//		cin >> c;
//
//		switch (c) {
//		case'0': case'1': case'2': case'3': case'4': case'5': case'6': case'7': case'8': case'9': case'.':
//			cin.putback(c);
//			double v;
//			cin >> v;
//			return Token('N', v);
//		case '(': case ')': case '+': case '-': case '*': case '/':
//			return Token(c);
//		default:
//			error("bad token");
//		}
//	}
//	
//}
//
//double expression();  // + , -
//double term();        // * , /
//double primary();     // 
//
//Token_stream ts;
//
//int main() 
//try
//{
//	while (cin) {
//		cout << "this is expression:" << expression() << endl;
//	}
//}
//catch (runtime_error& e) {
//	cerr << e.what() << endl;
//
//} 
//catch (...) {
//	cerr << "exception \n" << endl;
//}
//
//double expression() {
//	double left = term();
//	while (true) {
//		Token t = ts.get();
//		switch (t.kind) {
//		case '+': left += term(); break;
//		case '-': left -= term(); break;
//		default:
//			ts.putback(t);
//			return left;
//		}
//	}
//	return left;
//}
//double term() {
//	double left = primary();
//	while (true) {
//		Token t = ts.get(); 
//		switch (t.kind) {
//		case '*': left *= primary(); break;
//		case '/': 
//		{
//			double d = primary();
//			if (d == 0) error("Cannot divide by zero");
//			left /= d; break; 
//		}		
//		default:
//			ts.putback(t);
//			return left;
//		}
//	}
//	
//	return left;
//}
//double primary() {
//	Token t = ts.get();
//	switch (t.kind) {
//	case '(': {
//		double d = expression();
//		t = ts.get();
//		if (t.kind != ')') error("')' expected");
//		return d;
//	}
//	case 'N':
//		return t.value;
//	default:
//		error("primary expected");
//	}
//}