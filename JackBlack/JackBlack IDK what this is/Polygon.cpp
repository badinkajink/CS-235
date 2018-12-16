//
// Created by WilliamUSER on 11/1/2017.
//

// derived classes
#include <iostream>
#include <stack>

using namespace std;

enum PolyType {RECT, ANGLE};

class Polygon {
protected:
    int width, height;
public:
    PolyType type;
    void set_values (int a, int b)
    { width=a; height=b;}
};

class Rectangle: public Polygon {
    int length;
public:
    int area ()
    { return width * height; }
};

class Triangle: public Polygon {
    string name1, name2;
public:
    int area ()
    { return width * height / 2; }
};

/*
int main () {
    Rectangle rect, rect2;
    Triangle trgl, trgl2;
    rect.set_values (4,5);
    rect.type = RECT;
    trgl.set_values (4,5);
    trgl.type = ANGLE;
    cout << rect.area() << '\n';
    cout << trgl.area() << '\n';

    rect2.set_values (8,10);
    rect2.type = RECT;
    trgl2.set_values (8,10);
    trgl2.type = ANGLE;
    cout << rect2.area() << '\n';
    cout << trgl2.area() << '\n';

    std::stack<Polygon> mystack;

    mystack.push((Polygon(rect)));
    mystack.push((Polygon(trgl)));
    mystack.push((Polygon(rect2)));
    mystack.push((Polygon(trgl2)));

    std::cout << "Popping out elements...\n";
    while (!mystack.empty())
    {
        Polygon poly = mystack.top();

        if (poly.type == RECT ) {
            Rectangle *rec = (Rectangle*)&poly;
            cout << rec->area() << '\n';

        } else if (poly.type == ANGLE) {
            Triangle *tri = (Triangle *)&poly;
            cout << tri->area() << '\n';
        }
        mystack.pop();
    }

    return 0;
}
*/