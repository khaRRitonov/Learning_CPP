#include "Header.h"

vector<Variable> var_table;

double expression(Token_stream& ts);

//-------- Variable add ---------------------

double get_value(string s) {
	for (const Variable& v : var_table) {
		if (v.name == s)
			return v.value;
	}
	error("get: неопределЄнна€ переменна€ ", s);
}

void set_value(string s, double d) {
	for (Variable& v : var_table) {
		if (v.name == s) {
			v.value = d;
			return;
		}
	}
	error("set: неопределЄнна€ переменна€ ", s);
}

bool is_declared(string var) {
	for (const Variable& v : var_table) {
		if (v.name == var)
			return true;
	}
	return false;
}

void define_name(string var, double val) {
	if (is_declared(var))
		set_value(var, val);
	var_table.push_back(Variable(var, val));
}

//-------- end Variable add ----------------------------

double declaration(Token_stream& ts) {
	Token t = ts.get();
	if (t.kind != name)
		error("ожидаетс€ им€ переменной");
	string var_name = t.name;

	Token t2 = ts.get();
	if (t2.kind != '=')
		error("пропущен символ = в объ€вдении ", var_name);
	double d = expression(ts);
	define_name(var_name, d);
	return d;
}

double statement(Token_stream& ts) {
	Token t = ts.get();
	switch (t.kind) {
	case let:
		return declaration(ts);
	default:
		ts.putback(t);
		return expression(ts);
	}
}

double primary(Token_stream& ts) {
	Token t = ts.get();
	switch (t.kind) {
	case '(': {
		double d = expression(ts);
		t = ts.get();
		if (t.kind != ')')
			error("требуетc€ )");
		return d;
	}
	case name:
		return get_value(t.name);
	case number: 
		return t.value;
	case '-':
		return -primary(ts);
	case '+':
		return primary(ts);
	default:
		simple_error("требуетс€ первичное выражение");
	}

}

double term(Token_stream& ts) {
	double left = primary(ts);
	Token t = ts.get();
	while (true) {
		switch (t.kind) {
		case '*':
			left *= primary(ts);
			t = ts.get();
			break;
		case '/': 
		{
			double d = primary(ts);
			if (d == 0)
				error("деление на ноль");
			else
				left /= d;
			t = ts.get();
			break;
		}
		case '%':
		{
			double d = primary(ts);
			if (d == 0)
				error("деление на ноль");
			left = fmod(left, d);
			t = ts.get();
			break;
		}
		}
		ts.putback(t);
		return left;
	}
}

double expression(Token_stream& ts) {
	double left = term(ts);
	Token t = ts.get();
	while (true) {
		switch (t.kind) {
		case '+':
			left += term(ts);
			t = ts.get();
			break;
		case '-':
			left -= term(ts);
			t = ts.get();
			break;
		}
		ts.putback(t);
		return left;
	}
}

void calculate(Token_stream& ts) {
	while (cin) {
		try {
			cout << promt;
			Token_stream ts;
			Token t = ts.get();
			while (t.kind == print)
				t = ts.get();
			if (t.kind == quit)
				return;

			ts.putback(t);
			cout << result << statement(ts) << endl;
		}
		catch (exception& e) {
			cerr << "Error: " << e.what() << endl;
			ts.ignor(print);
		}
	}
}

int main() {
	setlocale(LC_ALL, "RUS");
	try {
		Token_stream ts;
		define_name("g", 5.0);
		calculate(ts);
		return 0;
	}
	catch (exception& e) {
		cerr << "Error: " << e.what() << endl;
		return 1;
	}
	catch (...) {
		cerr << "Error: неизвестна€ ошибка" << endl;
		return 2;
	}
}