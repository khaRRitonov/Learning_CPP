#include "Header.h"
//--------------------------------------------------------------------------

void Token_stream::putback(Token t) {
	if (full)
		error("буфер переполнен");
	buffer = t;
	full = true;
}

Token Token_stream::get() {
	if (full) {
		full = false;
		return buffer;
	}
	char ch;
	cin >> ch;
	switch (ch) {
	case quit: 
	case print:
	case '=':
	case '+': 
	case '-': 
	case '*': 
	case '/':
	case '(': 
	case ')': 
	case '%':
		return Token(ch);
	case '.':
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
	{
		cin.putback(ch);
		double val;
		cin >> val;
		return Token(number, val);
	}
	default:
		if (isspace(ch)) {
			return Token(print);
		}
		if (isalpha(ch)) {
			string s;
			s += ch;
			while (cin.get(ch) && (isalpha(ch) || isdigit(ch)))
				s += ch;
			cin.putback(ch);
			if (s == declkey)
				return Token{ let };
			return Token{ name, s };
		}
		error("неизвестный символ");
	}
}

void Token_stream::ignor(char c) {
	if (full && c == buffer.kind) {
		full = false;
		return;
	}
	full = false;
	char ch = 0;
	while (cin >> ch)
		if (ch == c)
			return;
}

Token Token_stream::get2() {
	if (full) {
		full = false;
		return buffer;
	}
	char ch;
	cin >> ch;
	switch (ch) {
	case ';':
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
	{
		return Token(ch);
	}
	default:
		error("неизвестный символ");
	}
}
