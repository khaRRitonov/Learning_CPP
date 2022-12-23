#include <iostream>
#include <string>
#include <math.h>
#include <algorithm>
#include <vector>

#include "winsock.h"

using namespace std;

void error(string s);
void error(string s1, string s2);
void simple_error(string s);

const char number = '8';
const char quit = 'q';
const char print = ';';
const string promt = "> ";
const string result = "= ";

const char name = 'a';
const char let = 'L';
const string declkey = "let";

class Variable {
public:
	Variable(string s, double v) : name(s), value(v) {}
	string name;
	double value;
};

class Token {
public:
	Token(char c) : kind(c), value(0) {};
	Token(char c, double v) : kind(c), value(v) {};
	Token(char c, string s) : kind(c), name(s), value(0) {};
	char kind;
	double value;
	string name;
};

class Token_stream {
public:
	Token get();
	void putback(Token t);
	Token get2();
	void ignor(char c);
private:
	bool full{ false };
	Token buffer = {'0'};
};
