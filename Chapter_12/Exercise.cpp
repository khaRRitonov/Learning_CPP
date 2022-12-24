#include "./Graph_lib/Simple_window.h"
#include "./Graph_lib/Graph.h"

double sgn(double d)
{
    if (d > 0) return 1;
    else if (d < 0) return -1;
    else return 0;
}

void exercise_12(int a, int b, double m, double n, int N) {
    const double pi = 3.14159;
    a = 50 * a;   
    b = 50 * b;

    Point tl(450, 200);
    Simple_window win(tl, a * 2 + 20, b * 2 + 20, "Superellipse");

    vector<Point> points;

    for (double theta = 0; theta < 2 * pi; theta += 2 * pi / N) {
        double x = pow(abs(cos(theta)), 2 / m) * a * sgn(cos(theta)) + a + 10;
        double y = pow(abs(sin(theta)), 2 / n) * b * sgn(sin(theta)) + b + 10;
        points.push_back(Point(x, y));
    }

    Open_polyline super;
    for (int i = 0; i < points.size(); ++i) {
        super.add(points[i]);
        super.set_color(Color::blue);
        //super.set_style(Line_style(Line_style::solid, 3));
    }
    super.set_fill_color(Color::blue);
    win.attach(super);
    win.wait_for_button();
}

void exercise_11() {
    Simple_window win(Point{ 200, 200 }, 480, 430, "Exercise 11");

    Closed_polyline hexagon;
    hexagon.add(Point(140, 40));
    hexagon.add(Point(40, 214));
    hexagon.add(Point(140, 388));
    hexagon.add(Point(340, 388));
    hexagon.add(Point(440, 214));
    hexagon.add(Point(340, 40));
    hexagon.set_color(Color::green);
    hexagon.set_fill_color(Color::green);
    win.attach(hexagon);

    Closed_polyline pentagon;
    pentagon.add(Point(140, 40));
    pentagon.add(Point(78, 230));
    pentagon.add(Point(240, 358));
    pentagon.add(Point(402, 230));
    pentagon.add(Point(340, 40));
    pentagon.set_color(Color::blue);
    pentagon.set_fill_color(Color::blue);
    win.attach(pentagon);

    Graph_lib::Rectangle square{ Point{140, 40}, 200, 200 };
    square.set_color(Color::red);
    square.set_fill_color(Color::red);
    win.attach(square);

    Graph_lib::Polygon tri;
    tri.add(Point(140, 40));
    tri.add(Point(340, 40));
    tri.add(Point(240, 212));
    tri.set_color(Color::yellow);
    tri.set_fill_color(Color::yellow);
    win.attach(tri);

    win.wait_for_button();
}