#include <iostream>
#include <cmath>
using namespace std;

struct ShapeVtable;

struct Shape
{
    ShapeVtable* vtable;
};

struct ShapeVtable
{
    double (*GetArea) (Shape*);
};

double GetArea(Shape* shape)
{
    return shape->vtable->GetArea(shape);
}

struct Circle
{
    Shape parent;
    double radius;
};

double CircleGetArea(Circle* circle)
{
    return 3.14 * (pow(circle->radius, 2));
}
ShapeVtable circle_vtable=
        {
                (double (*) (Shape*)) CircleGetArea
        };
void CircleInitialize(Circle* circle, double radius)
{
    circle->parent.vtable=&circle_vtable;
    circle->radius = radius;
}

struct Rectangle
{
    Shape parent;
    double width;
    double height;
};

double RectangleGetArea(Rectangle* rectangle)
{
    return rectangle->width * rectangle->height;
}

ShapeVtable rectangle_vtable=
        {
                (double (*)(Shape*)) RectangleGetArea
        };

void RectangleInitialize(Rectangle* rectangle, double width, double height)
{
    rectangle->parent.vtable=&rectangle_vtable;
    rectangle->width = width;
    rectangle->height = height;
}

struct Triangle
{
    Shape parent;
    double sideA;
    double sideB;
    double sideC;
};

double TriangleGetArea(Triangle* triangle)
{
    double d = (triangle->sideA + triangle->sideB + triangle->sideC) / 2;
    return sqrt(d * (d - triangle->sideA) * (d - triangle->sideB) * (d - triangle->sideC));
}

ShapeVtable triangle_vtable=
        {
                (double (*) (Shape*)) TriangleGetArea
        };
void TriangleInitialize(Triangle* triangle, double sideA, double sideB, double sideC)
{
    triangle->parent.vtable=&triangle_vtable;
    triangle->sideA = sideA;
    triangle->sideB = sideB;
    triangle->sideC = sideC;
}
int main() {

    Circle circle;
    CircleInitialize(&circle, 10); // circle with radius 10

    Rectangle rectangle;
    RectangleInitialize(&rectangle, 3, 5); // rectangle with width 3 and height 5

    Triangle triangle;
    TriangleInitialize(&triangle, 7, 4, 12); // triangle with side lengths: 7, 4, 12

    Shape* shapes[3];
    shapes[0] = (Shape*)&circle;
    shapes[1] = (Shape*)&rectangle;
    shapes[2] = (Shape*)&triangle;

    double total_area = 0;

    int i;
    for(i=0; i<3; i++)
    {
        double d = GetArea(shapes[i]);
        total_area+=d;
    }

    cout << total_area << endl; // check if the value is correct.

    return 0;
}

