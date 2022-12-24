#include "./Graph_lib/Simple_window.h"
#include "./Graph_lib/Graph.h"
#include <Windows.h>

using namespace Graph_lib;

int main() {
	try {
		ShowWindow(GetConsoleWindow(), SW_HIDE);

		Point p1(100, 100);
		Simple_window win(p1, 509, 400, "Window");
		Graph_lib::Polygon poly;
		poly.add(Point(300, 200));
		poly.add(Point(350, 100));
		poly.add(Point(400, 200));
		poly.set_color(Color::red);
		poly.set_style(Line_style(Line_style::dash, 4));

		Axis xa{ Axis::x, Point(20, 350), 280, 10, "x axis" };
		Axis ya{ Axis::y, Point(20, 350), 280, 10, "y axis" };
		xa.set_color(Color::black);
		ya.set_color(Color::black);
		ya.label.set_color(Color::blue);

		Function sine{ sin, 0, 50, Point{20, 150}, 1000, 50, 50 };
		sine.set_color(Color::black);

		Graph_lib::Rectangle r{ Point{200, 200}, 100, 50 };
		r.set_color(Color::blue);
		r.set_fill_color(Color::yellow);

		Closed_polyline poly_rect;
		poly_rect.add(Point{ 100, 50 });
		poly_rect.add(Point{ 200, 50 });
		poly_rect.add(Point{ 200, 100 });
		poly_rect.add(Point{ 100, 100 });
		poly_rect.add(Point{ 50, 75 });
		poly_rect.set_color(Color::black);
		poly_rect.set_style(Line_style(Line_style::dash, 2));
		poly_rect.set_fill_color(Color::green);

		Text t{ Point{150, 300}, "Hello, graphical world!" };
		t.set_font(Font::times_bold);
		t.set_font_size(20);
		t.set_color(Color::black);

		//Image im{ Point{0, 0}, "logotip.jpg" };

		//win.attach(im);

		ostringstream oss;
		oss << "screen size: " << x_max() << "*" << y_max() << "; window size: " << win.x_max() << "*" << win.y_max();
		Text sizes{ Point{100, 20}, oss.str() };
		sizes.set_color(Color::black);

		win.attach(sizes);

		win.attach(t);

		win.attach(poly_rect);

		win.attach(r);

		win.attach(sine);

		win.attach(ya);
		win.attach(xa);

		win.attach(poly);

		int a = 4;
		int b = 4;
		double m = 0.5;
		double n = 0.5;
		int N = 150;

		exercise_12(a, b, m, n, N);
		exercise_11();

		win.wait_for_button();

		return 0;
	}
	catch (exception& e) {
		cerr << "Error: " << e.what() << endl;
		return 1;
	}
	catch (...) {
		cerr << "Error: something went wrong" << endl;
		return 2;
	}
}