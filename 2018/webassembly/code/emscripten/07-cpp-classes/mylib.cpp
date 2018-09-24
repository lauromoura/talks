#include <emscripten/bind.h>

#include <stdio.h>
#include <cmath>

class Vector {
public:
    Vector(int x, int y) : x(x), y(y) {}

    ~Vector() { printf("Good bye, world!\n"); }

    double length() const {
        return sqrt(x*x + y*y);
    }

    int getX() const { return x; }
    int getY() const { return y; }
    void setX(int v) { x = v; }
    void setY(int v) { y = v; }

private:
    int x, y;
};

using namespace emscripten;

EMSCRIPTEN_BINDINGS(mylib) {
    class_<Vector>("Vector")
        .constructor<int, int>()
        .function("length", &Vector::length)
        .property("x", &Vector::getX, &Vector::setX)
        .property("y", &Vector::getY, &Vector::setY);
}
