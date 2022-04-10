//#include <iostream>
//using namespace std;
//
//inline void error(const string& s)
//{
//	throw runtime_error(s);
//}
//
//class Token {
//public:
//    char kind;        // what kind of token
//    double value;     // for numbers: a value 
//    Token(char ch)    // make a Token from a char
//        :kind(ch), value(0) { }    
//    Token(char ch, double val)     // make a Token from a char and a double
//        :kind(ch), value(val) { }
//};
//
//class Token_stream {
//public: 
//    Token_stream();   // make a Token_stream that reads from cin
//    Token get();      // get a Token (get() is defined elsewhere)
//    void putback(Token t);    // put a Token back
//private:
//    bool full;        // is there a Token in the buffer?
//    Token buffer;     // here is where we keep a Token put back using putback()
//};
//
//Token_stream::Token_stream()
//:full(false), buffer(0)    // no Token in buffer
//{
//}
//
//void Token_stream::putback(Token t)
//{
//    if (full) error("putback() into a full buffer");
//    buffer = t;       // copy t to buffer
//    full = true;      // buffer is now full
//}
//
//Token Token_stream::get()
//{
//    if (full) {       // do we already have a Token ready?
//        // remove token from buffer
//        full=false;
//        return buffer;
//    } 
//
//    char ch;
//    cin >> ch;    // note that >> skips whitespace (space, newline, tab, etc.)
//
//    switch (ch) {
//		case ';':
//		case 'q':		
//    case '(': case ')': case '+': case '-': case '*': case '/': 
//        return Token(ch);        // let each character represent itself
//    case '.':
//    case '0': case '1': case '2': case '3': case '4':
//		case '5': case '6': case '7': case '8': case '9':
//        {    
//            cin.putback(ch);         // put digit back into the input stream
//            double val;
//            cin >> val;              // read a floating-point number
//            return Token('8',val);   // let '8' represent "a number"
//        }
//    default:
//        error("Bad token");
//    }
//}
//
//Token_stream ts;        // provides get() and putback()
//
//double expression();
//
//// deal with numbers and parentheses
//double primary()
//{
//    Token t = ts.get();
//    switch (t.kind) {
//    case '(':    // handle '(' expression ')'
//        {    
//            double d = expression();
//            t = ts.get();
//            if (t.kind != ')') error("')' expected");
//            return d;
//        }
//    case '8':            // we use '8' to represent a number
//        return t.value;  // return the number's value
//    default:
//        error("primary expected");
//    }
//}
//
//// deal with *, /, and %
//double term()
//{
//    double left = primary();
//
//    while(true) {
//		Token t = ts.get();        // get the next token from token stream
//		switch (t.kind) {
//        case '*':
//            left *= primary();
//			break;
//
//        case '/':
//            {    
//                double d = primary();
//                if (d == 0) error("divide by zero");
//                left /= d; 
//                break;
//            }
//        default: 
//            ts.putback(t);     // put t back into the token stream
//            return left;
//        }
//    }
//}
//
//// deal with + and -
//double expression()
//{
//    double left = term();      // read and evaluate a Term
//
//    while(true) {    
//		Token t = ts.get();        // get the next token from token stream
//		switch(t.kind) {
//        case '+':
//            left += term();    // evaluate Term and add       
//			break;
//        case '-':
//            left -= term();    // evaluate Term and subtract
//            break;
//        default: 
//            ts.putback(t);     // put t back into the token stream
//            return left;       // finally: no more + or -: return the answer
//        }
//    }
//}
//
//int main()
//try {
//		double val = 0;
//	while(cin){
//		Token t = ts.get();
//		while (t.kind == ';') t = ts.get();
//		if (t.kind == 'q') break;
//		ts.putback(t);
//		cout << "= " << expression() << endl;
//	}
//}
//catch (exception& e) {
//    cerr << e.what() << endl;
//    return 1;
//}
//catch (...) {
//    cerr << "exception \n";
//    return 2;
//}
