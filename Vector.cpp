#include <iostream>
#include "Vector.h"

using namespace std;

Vector::Vector (): v(new double[3]), N(3) {} //проблема в создании матрицы - число столбцов фиксировано и равно 3

Vector::Vector (unsigned int a): v(new double[a]), N(a) {}

Vector::Vector(const Vector& b): Vector(b.N) {
    for (unsigned int i = 0; i < N; i++) {
        v[i] = b.v[i];
    }
}

unsigned int Vector::Get_N() {
    return N;
}

void Vector::Set_fill() {
    for (unsigned int i = 0; i < N; i++) {
        cin>>v[i];
    }
}

void Vector::Set_fill(double* x) {
    for (unsigned int i = 0; i < N; i++) {
        v[i] = x[i];
    }
}

void Vector::Cout_Vector() {
    cout<<"||";
    for (unsigned int i = 0; i < N-1; i++) {
        cout<<v[i]<<" ";
    }
    cout<<v[N-1];
    cout<<"||"<<endl;
}

Vector& Vector::operator= (const Vector& b) {
    if (N == b.N) {
        if (this == &b) {
            return *this;
        }
    for (unsigned int i = 0; i < N; i++) {
        v[i] = b.v[i];
    }
    return *this;
    }
}

Vector::~Vector () {
    delete []v;
}

Vector o(unsigned int a) {
    Vector c = Vector(a);
    for (unsigned int i = 0; i < a; i++) {
        c.v[i] = 0;
    }
    return c;
}

Vector operator+ (Vector a, Vector b){
    unsigned int x = a.Get_N();
    unsigned int y = b.Get_N();
    if (x == y) {
        Vector c = Vector(x);
        for (unsigned int i = 0; i < x; i++) {
            c.v[i] = a.v[i] + b.v[i];
        }
    return c;
    }
}

Vector operator- (Vector a, Vector b) {
    unsigned int x = a.Get_N();
    unsigned int y = b.Get_N();
    if (x == y) {
        Vector c = Vector(x);
        for (unsigned int i = 0; i < x; i++) {
            c.v[i] = a.v[i] - b.v[i];
        }
    return c;
    }
}

bool operator== (Vector a, Vector b) {
    unsigned int x = a.Get_N();
    unsigned int y = b.Get_N();
    if (x == y) {
        bool q = true;
        for (unsigned int i = 0; i < x; i++) {
            q = q && (a.v[i] == b.v[i]);
        }
        return q;
    }
    return false;
}

Vector operator* (double a, Vector b) {
    unsigned int x = b.Get_N();
    Vector c = Vector(x);
    for (unsigned int i = 0; i < x; i++) {
        c.v[i] = a*b.v[i];
    }
    return c;
}

Vector operator/ (Vector b, double a) {
    return (1.0/a)*b;
}
