////
//// This is example code from Chapter 6.6 "Trying the first version" of
//// "Software - Principles and Practice using C++" by Bjarne Stroustrup
////
//
//#include "std_lib_facilities.h"
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
//Token get_token()    // read a token from cin
//{
//    char ch;
//    cin >> ch;    // note that >> skips whitespace (space, newline, tab, etc.)
//
//    switch (ch) {
//    case '(': case ')': case '+': case '-': case '*': case '/':
//        return Token(ch);        // let each character represent itself
//    case '.':
//    case '0': case '1': case '2': case '3': case '4':
//    case '5': case '6': case '7': case '8': case '9':
//    {
//        cin.putback(ch);         // put digit back into the input stream
//        double val;
//        cin >> val;              // read a floating-point number
//        return Token('8', val);   // let '8' represent "a number"
//    }
//    default:
//        error("Bad token");
//    }
//}
//
//int main()
//try {
//    while (1)
//    {
//        Token t = get_token();
//        cout << "Token: kind=" << t.kind << ", value=" << t.value << endl;
//    }
//    keep_window_open("~0");
//}
//catch (exception& e) {
//    cerr << e.what() << endl;
//    keep_window_open("~1");
//    return 1;
//}
//catch (...) {
//    cerr << "exception \n";
//    keep_window_open("~2");
//    return 2;
//}
