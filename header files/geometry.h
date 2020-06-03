//
//  geometry.h
//  Final_FLIGHT_SIM
//
//  Created by PRATIK SANNAKKI on 15/05/19.
//  Copyright © 2019 PRATIK SANNAKKI. All rights reserved.
//

// Classes and utility functions for three-dimensional Points, Vectors,
// Planes, and Rays.

#ifndef GEOMETRY_H_
#define GEOMETRY_H_

#include <cmath>

class Point;
class Vector;
class Plane;
class Ray;


inline bool equal(double x, double y, double epsilon = 0.000001) {
    return fabs(x - y) <= epsilon;
}

class Vector {
public:
    double i, j, k;
    Vector(double i = 0, double j = 0, double k = 0): i(i), j(j), k(k) {}
    Vector(Point p);
    Vector operator +(Vector v) {return Vector(i + v.i, j + v.j, k + v.k);}
    Vector& operator +=(Vector v) {i += v.i; j += v.j; k += v.k; return *this;}
    Vector operator -(Vector v) {return Vector(i - v.i, j - v.j, k - v.k);}
    Vector& operator -=(Vector v) {i -= v.i; j -= v.j; k -= v.k; return *this;}
    Vector operator -() {return Vector(-i, -j, -k);}
    double dot(Vector v) {return i * v.i + j * v.j + k * v.k;}
    Vector cross(Vector);
    Vector operator *(double c) {return Vector(i * c, j * c, k * c);}
    friend Vector operator *(double c, Vector v) {return v * c;}
    Vector& operator *=(Vector v) {i *= v.i; j *= v.j; k *= v.k; return *this;}
    Vector operator /(double c) {return Vector(i / c, j / c, k / c);}
    Vector& operator /=(double c) {i /= c; j /= c; k /= c; return *this;}
    double magnitude() {return sqrt(this->dot(*this));}
    friend Vector unit(Vector v) {return v / v.magnitude();}
    friend void normalize(Vector& v) {v /= v.magnitude();}
    friend double cosine(Vector u, Vector v) {return unit(u).dot(unit(v));}
    bool isPerpendicularTo(Vector v) {return equal(this->dot(v), 0);}
    bool isParallelTo(Vector v) {return equal(cosine(*this, v), 1.0);}
    Vector projectionOnto(Vector v) {return this->dot(unit(v)) * unit(v);}
    Vector reflectionAbout(Vector v) {return 2 * projectionOnto(v) - *this;}
};


class Point {
public:
    double x, y, z;
    Point(double x = 0, double y = 0, double z = 0): x(x), y(y), z(z) {}
    Point operator +(Vector v) {return Point(x + v.i, y + v.j, z + v.k);}
    Point& operator +=(Vector v) {x += v.i; y += v.j; z += v.k; return *this;}
    Vector operator -(Point p) {return Vector(x - p.x, y - p.y, z - p.z);}
    double distanceTo(Point p) {return (p - *this).magnitude();}
    double distanceTo(Plane);
};


class Plane {
public:
    double a, b, c, d;
    Plane(double a = 0, double b = 0, double c = 1, double d = 0);
    Plane(Point p1, Point p2, Point p3);
    Vector normal() {return Vector(a, b, c);}
};



class Ray {
public:
    Point origin;
    Vector direction;
    Ray(Point origin, Vector direction): origin(origin), direction(direction) {}
    Point operator()(double u) {return origin + u * direction;}
};



inline Vector::Vector(Point p): i(p.x), j(p.y), k(p.z) {
}

inline Vector Vector::cross(Vector v) {
    return Vector(j * v.k - k * v.j, k * v.i - i * v.k, i * v.j - j * v.i);
}

inline Plane::Plane(double a, double b, double c, double d):
a(a), b(b), c(c), d(d)
{
}

inline double Point::distanceTo(Plane P) {
    return fabs(P.a * x + P.b * y + P.c * z + P.d) / P.normal().magnitude();
}

inline Plane::Plane(Point p1, Point p2, Point p3) {
    Vector n = (p2 - p1).cross(p3 - p1);
    a = n.i;
    b = n.j;
    c = n.k;
    d = -(Vector(p1).dot(n));
}

#endif
